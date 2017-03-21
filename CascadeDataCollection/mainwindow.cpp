#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->checkBox_Rotation,SIGNAL(stateChanged(int)),this,SLOT(checkBoxRotationChange(int)));
    connect(ui->checkBox_Light,SIGNAL(stateChanged(int)),this,SLOT(checkBoxLightChange(int)));
    connect(ui->checkBox_Deformation,SIGNAL(stateChanged(int)),this,SLOT(checkBoxDeformationChange(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkBoxRotationChange(int state)
{
    switch (state) {
    case Qt::Unchecked:
        ui->spinBox_Rotation->setEnabled(false);
        ui->spinBox_Rotation->setValue(0);
        break;
    case Qt::Checked:
        ui->spinBox_Rotation->setEnabled(true);
        ui->spinBox_Rotation->setValue(100);
        break;
    }
    ui->generateButton->setEnabled(ui->spinBox_Deformation->isEnabled() || ui->spinBox_Rotation->isEnabled() || ui->spinBox_Light->isEnabled()|| ui->spinBox_NegativeGenerate->isEnabled());
}

void MainWindow::checkBoxLightChange(int state)
{
    switch (state) {
    case Qt::Unchecked:
        ui->spinBox_Light->setEnabled(false);
        ui->spinBox_Light->setValue(0);
        break;
    case Qt::Checked:
        ui->spinBox_Light->setEnabled(true);
        ui->spinBox_Light->setValue(100);
        break;
    }
    ui->generateButton->setEnabled(ui->spinBox_Deformation->isEnabled() || ui->spinBox_Rotation->isEnabled() || ui->spinBox_Light->isEnabled()|| ui->spinBox_NegativeGenerate->isEnabled());
}

void MainWindow::checkBoxDeformationChange(int state)
{
    switch (state) {
    case Qt::Unchecked:
        ui->spinBox_Deformation->setEnabled(false);
        ui->spinBox_Deformation->setValue(0);
        break;
    case Qt::Checked:
        ui->spinBox_Deformation->setEnabled(true);
        ui->spinBox_Deformation->setValue(100);
        break;
    }
    ui->generateButton->setEnabled(ui->spinBox_Deformation->isEnabled() || ui->spinBox_Rotation->isEnabled() || ui->spinBox_Light->isEnabled()|| ui->spinBox_NegativeGenerate->isEnabled());
}

void MainWindow::on_generateButton_clicked()
{
    //do something
    ui->LogTextBrowser->append("Initial...");
    ui->LogTextBrowser->append("------------------------------");
    ui->LogTextBrowser->append("Parameter Setting: \n");
    ui->LogTextBrowser->append("Positive Data");

    int PosNum = 0;
    int RotateNum = ui->spinBox_Rotation->isEnabled()? ui->spinBox_Rotation->value():0;
    int LightNum = ui->spinBox_Light->isEnabled()? ui->spinBox_Light->value():0;
    int DeformationNum = ui->spinBox_Deformation->isEnabled()? ui->spinBox_Deformation->value():0;
    PosNum = RotateNum+LightNum+DeformationNum;

    QString posGenerate;
    bool posEnable;
    PosNum!=0&&posListNames.size()>0?posGenerate = "True": posGenerate ="False";
    PosNum!=0&&posListNames.size()>0?posEnable = true: posEnable =false;
    if(!QDir("newData").exists())
        QDir().mkdir("newData");

    if(!QDir("newData/Pos").exists())
        QDir().mkdir("newData/Pos");

    if(posEnable)
    {
        posfile = new QFile("newData/Pos/Info.txt");
        if(!posfile->open(QIODevice::WriteOnly))
        {
            ui->LogTextBrowser->append("Error occured in Open Info.txt File");
            return;
        }
        postext = new QTextStream(posfile);
    }

    ui->LogTextBrowser->append("Need To Generate: "+posGenerate);
    ui->LogTextBrowser->append("Total Pos Num: "+QString::number(PosNum));
    ui->LogTextBrowser->append("Rotate Data Num: "+QString::number(RotateNum));
    ui->LogTextBrowser->append("Light Data Num: "+QString::number(LightNum));
    ui->LogTextBrowser->append("Deformation Data Num: "+QString::number(DeformationNum));

    QString negGenerate;
    bool negEnable;
    int negNum = ui->spinBox_NegativeGenerate->value();
    negNum!=0&&negListNames.size()>0?negGenerate = "True": negGenerate ="False";
    negNum!=0&&negListNames.size()>0?negEnable = true: negEnable = false;

    if(!QDir("newData/Neg").exists())
        QDir().mkdir("newData/Neg");
    if(negEnable)
    {
        negfile = new QFile("newData/Neg/Info.txt");
        if(!negfile->open(QIODevice::WriteOnly))
        {
            ui->LogTextBrowser->append("Error occured in Open Info.txt File");
            return;
        }
        negtext = new QTextStream(negfile);
    }
    ui->LogTextBrowser->append("\nNegative Data");
    ui->LogTextBrowser->append("Need To Generate: "+negGenerate);
    ui->LogTextBrowser->append("Total Neg Num: "+QString::number(negNum));

    pos_name = 0;
    neg_name = 0;
    generateData = new GenerateData(posListNames,posEnable,RotateNum,LightNum,DeformationNum,negListNames,negEnable,negNum);
    connect(generateData,SIGNAL(sendProgress(int)),this,SLOT(getProgress(int)));
    connect(generateData,SIGNAL(sendLog(QString)),this,SLOT(getLog(QString)));
    connect(generateData,SIGNAL(sendStorePosImage(cv::Mat)),this,SLOT(getPosImage(cv::Mat)));
    connect(generateData,SIGNAL(sendStoreNegImage(cv::Mat)),this,SLOT(getNegImage(cv::Mat)));

    connect(generateData,SIGNAL(finished()),this,SLOT(processingEnding()));
    generateData->start();

}


void MainWindow::on_NegativeLoadButton_clicked()
{
    QStringList listNames = QFileDialog::getOpenFileNames(this,
                                                          "Select one or more negative files to open",
                                                          QDir::currentPath(),
                                                          "Images (*.png *.bmp *.jpg)");
    if(listNames.isEmpty())
        return;
    negListNames = listNames;
    ui->NegativeLineEdit->setText(negListNames[0]);
    ui->spinBox_NegativeGenerate->setEnabled(true);
    ui->generateButton->setEnabled(ui->spinBox_Deformation->isEnabled() || ui->spinBox_Rotation->isEnabled() || ui->spinBox_Light->isEnabled()|| ui->spinBox_NegativeGenerate->isEnabled());

}

void MainWindow::on_PositiveLoadButton_clicked()
{
    QStringList listNames = QFileDialog::getOpenFileNames(this,
                                                         "Select one or more positive files to open",
                                                         QDir::currentPath(),
                                                         "Images (*.png *.bmp *.jpg)");
    if(listNames.isEmpty() )
        return;
    posListNames = listNames;
    ui->PositiveLineEdit->setText(posListNames[0]);
}

void MainWindow::getLog(QString str)
{
    ui->LogTextBrowser->append(str);
}

void MainWindow::getProgress(int progress)
{
    ui->progressBar->setValue(progress);
}

void MainWindow::getPosImage(cv::Mat pos)
{
    QString file = QDir::currentPath()+"/newData/Pos/"+QString::number(pos_name)+".jpg";
    cv::imwrite(file.toStdString(),pos);
    pos_name++;
    ui->LogTextBrowser->append("Save as"+file);
    if(postext)
        postext->operator <<(file)<<" 1 0 0 "<<pos.cols<<" "<<pos.rows<<"\n";
}

void MainWindow::getNegImage(cv::Mat neg)
{
    QString file = QDir::currentPath()+"/newData/Neg/"+QString::number(neg_name)+".jpg";
    cv::imwrite(file.toStdString(),neg);
    neg_name++;
    ui->LogTextBrowser->append("Save as"+file);
    if(negtext)
        negtext->operator <<(file)<<"\n";//<<" 1 0 0 "<<neg.cols<<" "<<neg.rows<<"\n";
}

void MainWindow::processingEnding()
{
    if(posfile)
        posfile->close();
    if(negfile)
        negfile->close();
    pos_name = 0;
    neg_name = 0;
    ui->LogTextBrowser->append("Done");
}
