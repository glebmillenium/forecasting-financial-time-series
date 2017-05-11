/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QLabel *label;
    QTabWidget *tabWidget;
    QWidget *tab;
    QLabel *label_6;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QComboBox *comboBox;
    QWidget *tab_2;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label_4;
    QLabel *label_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QWidget *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QStringLiteral("Settings"));
        Settings->resize(401, 273);
        label = new QLabel(Settings);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 101, 17));
        tabWidget = new QTabWidget(Settings);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(20, 40, 361, 181));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 50, 151, 41));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 20, 151, 17));
        lineEdit_4 = new QLineEdit(tab);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(190, 60, 151, 25));
        comboBox = new QComboBox(tab);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(190, 10, 151, 25));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tab_2->setAutoFillBackground(false);
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 40, 67, 17));
        lineEdit_2 = new QLineEdit(tab_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(120, 40, 113, 25));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 70, 101, 17));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 10, 67, 17));
        lineEdit_3 = new QLineEdit(tab_2);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(120, 70, 113, 25));
        lineEdit = new QLineEdit(tab_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(120, 10, 113, 25));
        tabWidget->addTab(tab_2, QString());
        buttonBox = new QDialogButtonBox(Settings);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(210, 230, 166, 25));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(Settings);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QWidget *Settings)
    {
        Settings->setWindowTitle(QApplication::translate("Settings", "Form", Q_NULLPTR));
        label->setText(QApplication::translate("Settings", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", Q_NULLPTR));
#ifndef QT_NO_ACCESSIBILITY
        tab->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        label_6->setText(QApplication::translate("Settings", "\320\224\320\276\320\277\321\203\321\201\321\202\320\270\320\274\320\260\321\217 \320\276\321\210\320\270\320\261\320\272\320\260<br> \320\276\320\261\321\203\321\207\320\265\320\275\320\270\321\217 (%)", Q_NULLPTR));
        label_5->setText(QApplication::translate("Settings", "\320\242\320\270\320\277 \320\275\320\265\320\271\321\200\320\276\320\275\320\275\320\276\320\271 \321\201\320\265\321\202\320\270", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Settings", "\320\237\320\265\321\200\321\201\320\265\320\277\321\202\321\200\320\276\320\275", Q_NULLPTR)
         << QApplication::translate("Settings", "\320\240\320\260\320\264\320\270\320\260\320\273\321\214\320\275\320\276-\320\261\320\260\320\267\320\270\321\201\320\275\320\260\321\217", Q_NULLPTR)
         << QApplication::translate("Settings", "\320\240\320\265\320\272\320\272\321\203\321\200\320\265\320\275\321\202\320\275\320\260\321\217", Q_NULLPTR)
        );
        comboBox->setCurrentText(QApplication::translate("Settings", "\320\237\320\265\321\200\321\201\320\265\320\277\321\202\321\200\320\276\320\275", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Settings", "\320\235\320\265\320\271\321\200\320\276\320\275\320\275\320\260\321\217 \321\201\320\265\321\202\321\214", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        tab_2->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        tab_2->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_WHATSTHIS
        tab_2->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_ACCESSIBILITY
        tab_2->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
#ifndef QT_NO_ACCESSIBILITY
        tab_2->setAccessibleDescription(QString());
#endif // QT_NO_ACCESSIBILITY
        label_3->setText(QApplication::translate("Settings", "\320\237\320\260\321\200\320\276\320\273\321\214", Q_NULLPTR));
        label_4->setText(QApplication::translate("Settings", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\221\320\224", Q_NULLPTR));
        label_2->setText(QApplication::translate("Settings", "\320\233\320\276\320\263\320\270\320\275", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Settings", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\270\320\265 \320\272 \320\241\320\243\320\221\320\224", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
