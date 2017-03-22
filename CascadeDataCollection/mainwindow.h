#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMetaType>
#include <generatedata.h>
#include <opencv.hpp>
#include <QTextStream>
//#include <quickstore.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void checkBoxRotationChange(int state);

    void checkBoxLightChange(int state);

    void checkBoxDeformationChange(int state);

    void on_generateButton_clicked();

    void on_NegativeLoadButton_clicked();

    void on_PositiveLoadButton_clicked();

    void getLog(QString str);

    void getProgress(int progress);

    void getPosImage(QString file);

    void getNegImage(QString file);

    void processingEnding();

private:
    Ui::MainWindow *ui;
    QStringList posListNames;
//    QString *posListNames;
    QStringList negListNames;
//    QString *negListNames;
    GenerateData *generateData;
    int pos_name;
    int neg_name;
//    QFile *posfile = 0;
//    QTextStream *postext = 0;
//    QFile *negfile = 0;
//    QTextStream *negtext = 0;
    //QuickStore *qstore;
};
Q_DECLARE_METATYPE(cv::Mat)
#endif // MAINWINDOW_H
