#ifndef GENERATEDATA_H
#define GENERATEDATA_H

#define s_angle 15
#include <QObject>
#include <QDebug>
#include <QThread>
#include <QFile>
#include <QTextStream>
#include <opencv.hpp>

class GenerateData: public QThread
{
    Q_OBJECT
public:
    GenerateData(QStringList posList,bool posEnable,int RotateNum,int LightNum,int DeformationNum,QStringList negList,bool negEnable,int negNum, QString path);
protected:
    void run();
signals:
    void sendProgress(int);
    void sendLog(QString);
    //    void sendStorePosImage(cv::Mat);
    //    void sendStoreNegImage(cv::Mat);
    void sendStorePosImage(QString);
    void sendStoreNegImage(QString);
    void sendCompleted();
private:
    bool _posEnable;
    bool _negEnable;
    int _RotatePosNum;
    int _LightPosNum;
    int _DeformationNum;
    int _NegNum;
    QStringList _posList;
    QStringList _negList;
    cv::Mat RotateImage();
    cv::Mat LightImage();
    cv::Mat DeformationImage();
    cv::Mat NegImage();

    QString _path;

//    cv::Mat result;

//    int targetImageID;
//    cv::Mat targetImage;
};

#endif // GENERATEDATA_H
