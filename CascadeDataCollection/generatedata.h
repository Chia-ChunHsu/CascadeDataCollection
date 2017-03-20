#ifndef GENERATEDATA_H
#define GENERATEDATA_H

#include <QObject>
#include <QThread>
#include <opencv.hpp>

class GenerateData: public QThread
{
    Q_OBJECT
public:
    GenerateData(QStringList posList,bool posEnable,int RotateNum,int LightNum,int DeformationNum,QStringList negList,bool negEnable,int negNum);
protected:
    void run();
signals:
    void sendProgress(int);
    void sendLog(QString);
    void sendStorePosImage(cv::Mat);
    void sendStoreNegImage(cv::Mat);
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
};

#endif // GENERATEDATA_H
