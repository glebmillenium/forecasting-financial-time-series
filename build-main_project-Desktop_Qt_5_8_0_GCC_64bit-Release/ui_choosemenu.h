/********************************************************************************
** Form generated from reading UI file 'choosemenu.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHOOSEMENU_H
#define UI_CHOOSEMENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChooseMenu
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *statusServer;
    QLabel *statusR;
    QPushButton *viewData;
    QPushButton *neuralNetwork;
    QPushButton *settings;
    QGroupBox *groupBox;
    QPushButton *viewForecast;
    QPushButton *createNeuralNetwork;

    void setupUi(QWidget *ChooseMenu)
    {
        if (ChooseMenu->objectName().isEmpty())
            ChooseMenu->setObjectName(QStringLiteral("ChooseMenu"));
        ChooseMenu->resize(390, 362);
        label = new QLabel(ChooseMenu);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 40, 111, 17));
        label_2 = new QLabel(ChooseMenu);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 80, 111, 17));
        label_3 = new QLabel(ChooseMenu);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(60, 110, 131, 17));
        statusServer = new QLabel(ChooseMenu);
        statusServer->setObjectName(QStringLiteral("statusServer"));
        statusServer->setGeometry(QRect(200, 80, 67, 17));
        statusR = new QLabel(ChooseMenu);
        statusR->setObjectName(QStringLiteral("statusR"));
        statusR->setGeometry(QRect(200, 110, 67, 17));
        viewData = new QPushButton(ChooseMenu);
        viewData->setObjectName(QStringLiteral("viewData"));
        viewData->setGeometry(QRect(70, 140, 211, 25));
        neuralNetwork = new QPushButton(ChooseMenu);
        neuralNetwork->setObjectName(QStringLiteral("neuralNetwork"));
        neuralNetwork->setGeometry(QRect(70, 180, 211, 25));
        settings = new QPushButton(ChooseMenu);
        settings->setObjectName(QStringLiteral("settings"));
        settings->setGeometry(QRect(250, 30, 89, 25));
        groupBox = new QGroupBox(ChooseMenu);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(60, 210, 231, 111));
        viewForecast = new QPushButton(groupBox);
        viewForecast->setObjectName(QStringLiteral("viewForecast"));
        viewForecast->setGeometry(QRect(10, 70, 211, 25));
        createNeuralNetwork = new QPushButton(groupBox);
        createNeuralNetwork->setObjectName(QStringLiteral("createNeuralNetwork"));
        createNeuralNetwork->setGeometry(QRect(10, 30, 211, 25));

        retranslateUi(ChooseMenu);

        QMetaObject::connectSlotsByName(ChooseMenu);
    } // setupUi

    void retranslateUi(QWidget *ChooseMenu)
    {
        ChooseMenu->setWindowTitle(QApplication::translate("ChooseMenu", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("ChooseMenu", "\320\223\320\273\320\260\320\262\320\275\320\276\320\265 \320\274\320\265\320\275\321\216", Q_NULLPTR));
        label_2->setText(QApplication::translate("ChooseMenu", "\320\241\321\202\320\260\321\202\321\203\321\201 \321\201\320\265\321\200\320\262\320\265\321\200\320\260:", Q_NULLPTR));
        label_3->setText(QApplication::translate("ChooseMenu", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265 \320\272 R:", Q_NULLPTR));
        statusServer->setText(QApplication::translate("ChooseMenu", "TextLabel", Q_NULLPTR));
        statusR->setText(QApplication::translate("ChooseMenu", "TextLabel", Q_NULLPTR));
        viewData->setText(QApplication::translate("ChooseMenu", "\320\237\320\276\321\201\320\274\320\276\321\202\321\200\320\265\321\202\321\214 \320\264\320\260\320\275\320\275\321\213\320\265", Q_NULLPTR));
        neuralNetwork->setText(QApplication::translate("ChooseMenu", "\320\235\320\260\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \320\275\320\265\320\271\321\200\320\276\320\275\320\275\321\203\321\216 \321\201\320\265\321\202\321\214", Q_NULLPTR));
        settings->setText(QApplication::translate("ChooseMenu", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("ChooseMenu", "\320\237\321\200\320\276\320\263\320\275\320\276\320\267\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", Q_NULLPTR));
        viewForecast->setText(QApplication::translate("ChooseMenu", "\320\237\320\276\321\201\320\274\320\276\321\202\321\200\320\265\321\202\321\214 \320\277\321\200\320\276\320\263\320\275\320\276\320\267\321\213", Q_NULLPTR));
        createNeuralNetwork->setText(QApplication::translate("ChooseMenu", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\265\320\271\321\200\320\276\320\275\320\275\321\203\321\216 \321\201\320\265\321\202\321\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ChooseMenu: public Ui_ChooseMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHOOSEMENU_H
