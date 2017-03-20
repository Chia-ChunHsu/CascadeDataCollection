#include "generatedata.h"

GenerateData::GenerateData(QStringList posList, bool posEnable, int RotateNum, int LightNum, int DeformationNum, QStringList negList, bool negEnable, int negNum)
{
    _posList = posList;
    _posEnable = posEnable;
    _RotatePosNum = RotateNum;
    _LightPosNum = LightNum;
    _DeformationNum = DeformationNum;
    _negList = negList;
    _negEnable = negEnable;
    _NegNum = negNum;
}

void GenerateData::run()
{
    emit sendLog("Start Generate Data...");
    //Reset the Progress
    emit sendProgress(0);
    //Setting Positive Data Generation
    int posTotal = _RotatePosNum + _LightPosNum + _DeformationNum;

    if(_posEnable)
    {
        double gap = 100.0/posTotal;
        for(int i=0;i<posTotal;i++)
        {
            if(i<_RotatePosNum)
            {
                //Case Rotation
                emit sendStorePosImage(RotateImage());
            }
            else if(i<_RotatePosNum+_LightPosNum)
            {
                //Case Light
                emit sendStorePosImage(LightImage());
            }
            else
            {
                //Case Deformation
                emit sendStorePosImage(DeformationImage());
            }
            emit sendProgress(i*gap);
        }
    }
    else
    {
        emit sendLog("Do not need to generate Positive Data");
    }
    emit sendProgress(100);
    emit sendLog("Generating Positive Data ia Completed!");
    //Setting Negative Data Generation
    emit sendProgress(0);
    emit sendLog("Start to generate Negative Data");
    double negGap = 100.0/_NegNum;
    for(int i = 0;i<_NegNum;i++)
    {
        //Randomly Cut Image for Gererating much negative data
        emit sendStoreNegImage(NegImage());
        emit sendProgress(i*negGap);
    }
    emit sendProgress(100);
}

cv::Mat GenerateData::RotateImage()
{
    //Choose the target Image randomly
    int targetImageID = rand()%_posList.size();
    //Load Target Image
    cv::Mat targetImage = cv::imread(_posList[targetImageID].toStdString(),cv::IMREAD_COLOR);
    //Randonly choose rotate angle
    int angle = rand()%60; //Set 0 as -30 degrees, and set 59 as +30 degrees
    cv::Mat result;
    cv::Point center(targetImage.cols/2,targetImage.rows/2);
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center,angle,1.0);
    cv::warpAffine(targetImage,result,rotationMatrix,cv::Size(targetImage.cols*1.2,targetImage.rows*1.2));
    return result;
}

cv::Mat GenerateData::LightImage()
{
    cv::Mat temp;
    return temp;
}

cv::Mat GenerateData::DeformationImage()
{
    cv::Mat temp;
    return temp;
}

cv::Mat GenerateData::NegImage()
{
    cv::Mat temp;
    return temp;
}
