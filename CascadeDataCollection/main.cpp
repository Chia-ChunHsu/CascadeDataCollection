#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setWindowTitle("Data Collection");
    qRegisterMetaType<cv::Mat>("cv::Mat");
    return a.exec();
}
