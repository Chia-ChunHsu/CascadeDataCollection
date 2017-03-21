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
    emit sendLog("Generating Negative Data ia Completed!");
}

cv::Mat GenerateData::RotateImage()
{
    //Choose the target Image randomly
    int targetImageID = rand()%_posList.size();
    //Load Target Image
    cv::Mat targetImage = cv::imread(_posList[targetImageID].toStdString(),cv::IMREAD_COLOR);
    //Randonly choose rotate angle
    int angle = rand()%61; //Set 0 as -30 degrees, and set 59 as +30 degrees
    //double scale = double(rand()%20)*0.1+;
    double scale = 1.0;
    cv::Mat result;
    cv::Point center(targetImage.cols/2,targetImage.rows/2);
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center,angle-30,scale);
    cv::warpAffine(targetImage,result,rotationMatrix,cv::Size(targetImage.cols,targetImage.rows*1.3));
    return result;
}

cv::Mat GenerateData::LightImage()
{
    cv::Mat result;
    int targetImageID = rand()%_posList.size();
    //Load Target Image
    cv::Mat targetImage = cv::imread(_posList[targetImageID].toStdString(),cv::IMREAD_COLOR);
    double alpha = double(rand()%20)*0.1+1.0;
    double beta = double(rand()%101);
    targetImage.convertTo(result,-1,alpha,beta);
    return result;
}

cv::Mat GenerateData::DeformationImage()
{
    //Choose ID
    int targetImageID = rand()%_posList.size();
    //Load Target Image
    cv::Mat targetImage = cv::imread(_posList[targetImageID].toStdString(),cv::IMREAD_COLOR);
    cv::Point2f srcTri[3];
    cv::Point2f dstTri[3];
    cv::Mat warpMat(2,3,CV_32FC1)   ;
    cv::Mat warpDst =cv::Mat::zeros(targetImage.rows,targetImage.cols,targetImage.type());

    srcTri[0] = cv::Point2f(0,0);
    srcTri[1] = cv::Point2f(targetImage.cols-1.f,0);
    srcTri[2] = cv::Point2f(0,targetImage.rows-1.f);

    float x0,y0;
    float x1,y1;
    float x2,y2;
    x0 = float(rand()%30*0.01)+0.0;
    x1 = float(rand()%20*0.01)+0.8;
    x2 = float(rand()%30*0.01)+0.0;
    y0 = float(rand()%30*0.01)+0.0;
    y1 = float(rand()%30*0.01)+0.0;
    y2 = float(rand()%20*0.01)+0.8;

    dstTri[0] = cv::Point2f( targetImage.cols*x0, targetImage.rows*y0 );
    dstTri[1] = cv::Point2f( targetImage.cols*x1, targetImage.rows*y1 );
    dstTri[2] = cv::Point2f( targetImage.cols*x2, targetImage.rows*y2 );

    warpMat = cv::getAffineTransform(srcTri,dstTri);
    cv::warpAffine(targetImage,warpDst,warpMat,warpDst.size());

    return warpDst;
}

cv::Mat GenerateData::NegImage()
{
    cv::Mat result;
    //Choose ID
    int targetImageID = rand()%_negList.size();
    //Load Target Image
    cv::Mat targetImage = cv::imread(_negList[targetImageID].toStdString(),cv::IMREAD_COLOR);
    //Random Size, Random Case
    cv::Size size(rand()%targetImage.cols,rand()%targetImage.rows);
    int x = rand()%(targetImage.cols-size.width);
    int y = rand()%(targetImage.rows-size.height);
    cv::Rect ROI(x,y,size.width,size.height);
    result = targetImage(ROI).clone();
    return result;
}
