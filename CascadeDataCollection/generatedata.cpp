#include "generatedata.h"

GenerateData::GenerateData(QStringList posList, bool posEnable, int RotateNum, int LightNum, int DeformationNum, QStringList negList, bool negEnable, int negNum, QString path)
{
    _posList = posList;
    _posEnable = posEnable;
    _RotatePosNum = RotateNum;
    _LightPosNum = LightNum;
    _DeformationNum = DeformationNum;
    _negList = negList;
    _negEnable = negEnable;
    _NegNum = negNum;
    srand((unsigned)time(NULL));
    _path = path;
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
        QFile posfile("newData/Pos/Info.txt");
        if(!posfile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug()<<"Cannot open Pos Info.txt";
            //return;
        }
        QTextStream postext(&posfile);
//        QFile *negfile = 0;
//        QTextStream *negtext = 0;
        QString file;
        double gap = 100.0/posTotal;
        for(int i=0;i<posTotal;i++)
        {
            file = _path+"/newData/Pos/"+QString::number(i)+".jpg";
            cv::Mat image;

            if(i<_RotatePosNum)
            {
                //Case Rotation
                image = RotateImage().clone();
                cv::imwrite(file.toStdString(),image);
                postext<<file<<" 1 0 0 "<<image.cols<<" "<<image.rows<<"\n";

                //emit sendStorePosImage(RotateImage());
            }
            else if(i<_RotatePosNum+_LightPosNum)
            {
                //Case Light
                image = LightImage().clone();
                cv::imwrite(file.toStdString(),image);
                postext<<file<<" 1 0 0 "<<image.cols<<" "<<image.rows<<"\n";

                //emit sendStorePosImage(LightImage());
            }
            else
            {
                //Case Deformation
                image = DeformationImage().clone();
                cv::imwrite(file.toStdString(),image);
                postext << file <<" 1 0 0 " << image.cols <<" "<<image.rows<< endl;

                //emit sendStorePosImage(DeformationImage());
            }

            emit sendStorePosImage(file);
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
    if(_negEnable)
    {
        QFile negfile("newData/Neg/Info.txt");


        if(!negfile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qDebug()<<"Cannot open Neg Info.txt";
            //return;
        }
        QTextStream negtext(&negfile);
        emit sendProgress(0);
        emit sendLog("Start to generate Negative Data");
        double negGap = 100.0/_NegNum;
        for(int i = 0;i<_NegNum;i++)
        {
            cv::Mat image = NegImage();
            QString file = _path+"/newData/Neg/"+QString::number(i)+".jpg";
            //Randomly Cut Image for Gererating much negative data
            negtext<< file <<endl;

            cv::imwrite(file.toStdString(),image);

            emit sendStoreNegImage(file);
            emit sendProgress(i*negGap);

        }

        emit sendProgress(100);
        negfile.close();
    }

    emit sendLog("Generating Negative Data ia Completed!");
    emit sendCompleted();
}

cv::Mat GenerateData::RotateImage()
{
    //Choose the target Image randomly
    int targetImageID = rand()%_posList.size();
    //Load Target Image
    cv::Mat targetImage = cv::imread(_posList[targetImageID].toStdString(),cv::IMREAD_COLOR);
    //Randonly choose rotate angle

    int angle = rand()%(s_angle*2+1); //Set 0 as -30 degrees, and set 59 as +30 degrees

    cv::Point center(targetImage.cols/2,targetImage.rows/2);
    cv::Mat rotationMatrix = cv::getRotationMatrix2D(center,angle-s_angle,1.0);
    cv::Mat result;
    cv::warpAffine(targetImage,result,rotationMatrix,cv::Size(targetImage.cols,targetImage.rows*1.3));
    return result;
}

cv::Mat GenerateData::LightImage()
{
    int targetImageID = rand()%_posList.size();
    //Load Target Image
    cv::Mat targetImage = cv::imread(_posList[targetImageID].toStdString(),cv::IMREAD_COLOR);
    double alpha = double(rand()%10)*0.1+1.0;
    double beta = double(rand()%51);
    cv::Mat result;
    targetImage.convertTo(result,-1,alpha,beta);
    return result;
}

cv::Mat GenerateData::DeformationImage()
{
    //Choose ID
    int targetImageID = rand()%_posList.size();
    //Load Target Image
    cv::Mat targetImage = cv::imread(_posList[targetImageID].toStdString(),cv::IMREAD_COLOR);

    cv::Point2f *srcTri = (cv::Point2f *)malloc(sizeof(cv::Point2f)*3);
    cv::Point2f *dstTri = (cv::Point2f *)malloc(sizeof(cv::Point2f)*3);
    //cv::Point2f srcTri[3];
    //cv::Point2f dstTri[3];
    //cv::Mat warpMat(2,3,CV_32FC1);
    cv::Mat warpMat(2,3,CV_32FC1);
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

    free(srcTri);
    free(dstTri);
    return warpDst;
}

cv::Mat GenerateData::NegImage()
{
    //Choose ID
    int targetImageID = rand()%_negList.size();
    //Load Target Image
    cv::Mat targetImage = cv::imread(_negList[targetImageID].toStdString(),cv::IMREAD_COLOR);
    //Random Size, Random Case
    cv::Size size(rand()%(targetImage.cols-10)+10,rand()%(targetImage.rows-10)+10);
    int x = rand()%(targetImage.cols-size.width);
    int y = rand()%(targetImage.rows-size.height);
    cv::Rect ROI(x,y,size.width,size.height);
    cv::Mat result = targetImage(ROI).clone();
    return result;
}
