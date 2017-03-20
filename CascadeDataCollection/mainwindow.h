#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMetaType>
#include <generatedata.h>
#include <opencv.hpp>
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

    void getPosImage(cv::Mat pos);

    void getNegImage(cv::Mat neg);

private:
    Ui::MainWindow *ui;
    QStringList posListNames;
    QStringList negListNames;
    GenerateData *generateData;
    int pos_name;
    int neg_name;
};
Q_DECLARE_METATYPE(cv::Mat)
#endif // MAINWINDOW_H
