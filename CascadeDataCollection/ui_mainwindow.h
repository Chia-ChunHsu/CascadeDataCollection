/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QPushButton *generateButton;
    QProgressBar *progressBar;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QLineEdit *PositiveLineEdit;
    QPushButton *PositiveLoadButton;
    QCheckBox *checkBox_Rotation;
    QCheckBox *checkBox_Light;
    QCheckBox *checkBox_Deformation;
    QSpinBox *spinBox_Rotation;
    QSpinBox *spinBox_Light;
    QSpinBox *spinBox_Deformation;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLineEdit *NegativeLineEdit;
    QPushButton *NegativeLoadButton;
    QSpinBox *spinBox_NegativeGenerate;
    QTextBrowser *LogTextBrowser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(450, 498);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        generateButton = new QPushButton(centralWidget);
        generateButton->setObjectName(QStringLiteral("generateButton"));
        generateButton->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(generateButton->sizePolicy().hasHeightForWidth());
        generateButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(generateButton, 2, 0, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout->addWidget(progressBar, 2, 1, 1, 1);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        PositiveLineEdit = new QLineEdit(groupBox_2);
        PositiveLineEdit->setObjectName(QStringLiteral("PositiveLineEdit"));

        gridLayout_3->addWidget(PositiveLineEdit, 0, 0, 1, 1);

        PositiveLoadButton = new QPushButton(groupBox_2);
        PositiveLoadButton->setObjectName(QStringLiteral("PositiveLoadButton"));

        gridLayout_3->addWidget(PositiveLoadButton, 0, 1, 1, 1);

        checkBox_Rotation = new QCheckBox(groupBox_2);
        checkBox_Rotation->setObjectName(QStringLiteral("checkBox_Rotation"));

        gridLayout_3->addWidget(checkBox_Rotation, 1, 0, 1, 1);

        checkBox_Light = new QCheckBox(groupBox_2);
        checkBox_Light->setObjectName(QStringLiteral("checkBox_Light"));

        gridLayout_3->addWidget(checkBox_Light, 2, 0, 1, 1);

        checkBox_Deformation = new QCheckBox(groupBox_2);
        checkBox_Deformation->setObjectName(QStringLiteral("checkBox_Deformation"));

        gridLayout_3->addWidget(checkBox_Deformation, 3, 0, 1, 1);

        spinBox_Rotation = new QSpinBox(groupBox_2);
        spinBox_Rotation->setObjectName(QStringLiteral("spinBox_Rotation"));
        spinBox_Rotation->setEnabled(false);
        spinBox_Rotation->setMinimum(100);
        spinBox_Rotation->setMaximum(1000);

        gridLayout_3->addWidget(spinBox_Rotation, 1, 1, 1, 1);

        spinBox_Light = new QSpinBox(groupBox_2);
        spinBox_Light->setObjectName(QStringLiteral("spinBox_Light"));
        spinBox_Light->setEnabled(false);
        spinBox_Light->setMinimum(100);
        spinBox_Light->setMaximum(1000);

        gridLayout_3->addWidget(spinBox_Light, 2, 1, 1, 1);

        spinBox_Deformation = new QSpinBox(groupBox_2);
        spinBox_Deformation->setObjectName(QStringLiteral("spinBox_Deformation"));
        spinBox_Deformation->setEnabled(false);
        spinBox_Deformation->setMinimum(100);
        spinBox_Deformation->setMaximum(1000);

        gridLayout_3->addWidget(spinBox_Deformation, 3, 1, 1, 1);


        gridLayout->addWidget(groupBox_2, 0, 0, 1, 2);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        NegativeLineEdit = new QLineEdit(groupBox);
        NegativeLineEdit->setObjectName(QStringLiteral("NegativeLineEdit"));

        gridLayout_2->addWidget(NegativeLineEdit, 0, 0, 1, 2);

        NegativeLoadButton = new QPushButton(groupBox);
        NegativeLoadButton->setObjectName(QStringLiteral("NegativeLoadButton"));
        NegativeLoadButton->setMaximumSize(QSize(113, 16777215));

        gridLayout_2->addWidget(NegativeLoadButton, 0, 2, 1, 1);

        spinBox_NegativeGenerate = new QSpinBox(groupBox);
        spinBox_NegativeGenerate->setObjectName(QStringLiteral("spinBox_NegativeGenerate"));
        spinBox_NegativeGenerate->setEnabled(false);
        spinBox_NegativeGenerate->setMinimum(100);
        spinBox_NegativeGenerate->setMaximum(1000);

        gridLayout_2->addWidget(spinBox_NegativeGenerate, 1, 2, 1, 1);


        gridLayout->addWidget(groupBox, 1, 0, 1, 2);

        LogTextBrowser = new QTextBrowser(centralWidget);
        LogTextBrowser->setObjectName(QStringLiteral("LogTextBrowser"));

        gridLayout->addWidget(LogTextBrowser, 3, 0, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 450, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        generateButton->setText(QApplication::translate("MainWindow", "Generate", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Positive Data Generate", Q_NULLPTR));
        PositiveLoadButton->setText(QApplication::translate("MainWindow", "Positive Images Folder", Q_NULLPTR));
        checkBox_Rotation->setText(QApplication::translate("MainWindow", "Rotation", Q_NULLPTR));
        checkBox_Light->setText(QApplication::translate("MainWindow", "Light Change between + 30 Degrees and - 30 Degrees", Q_NULLPTR));
        checkBox_Deformation->setText(QApplication::translate("MainWindow", "3D Deformation Maximum Angles 30 Degrees", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Negative Data Generate", Q_NULLPTR));
        NegativeLoadButton->setText(QApplication::translate("MainWindow", "Negative URL Folder", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
