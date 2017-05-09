/********************************************************************************
** Form generated from reading UI file 'viewdata.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWDATA_H
#define UI_VIEWDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewData
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget;
    QComboBox *Asix_X;
    QComboBox *Asix_Y;
    QLabel *label_3;
    QLabel *label_5;
    QWidget *tab_2;
    QTableView *tableView;
    QPushButton *pushButton;
    QDateEdit *dateEdit;
    QPushButton *ButtonAddRow;
    QPushButton *ButtonDeleteRow;
    QPushButton *ButtonPasteRow;
    QPushButton *ButtonUploadData;
    QProgressBar *progressBar;
    QLabel *label_2;
    QComboBox *Mark;
    QComboBox *TypeUpload;
    QLabel *label_4;
    QComboBox *TypeMaterial;
    QLabel *label;

    void setupUi(QWidget *ViewData)
    {
        if (ViewData->objectName().isEmpty())
            ViewData->setObjectName(QStringLiteral("ViewData"));
        ViewData->resize(602, 430);
        tabWidget = new QTabWidget(ViewData);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 70, 551, 341));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        widget = new QWidget(tab);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 521, 291));
        Asix_X = new QComboBox(widget);
        Asix_X->setObjectName(QStringLiteral("Asix_X"));
        Asix_X->setGeometry(QRect(420, 20, 86, 25));
        Asix_Y = new QComboBox(widget);
        Asix_Y->setObjectName(QStringLiteral("Asix_Y"));
        Asix_Y->setGeometry(QRect(420, 60, 86, 25));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(370, 20, 41, 16));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(370, 60, 41, 17));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tableView = new QTableView(tab_2);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 10, 441, 261));
        pushButton = new QPushButton(tab_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 280, 191, 22));
        dateEdit = new QDateEdit(tab_2);
        dateEdit->setObjectName(QStringLiteral("dateEdit"));
        dateEdit->setGeometry(QRect(350, 280, 85, 23));
        ButtonAddRow = new QPushButton(tab_2);
        ButtonAddRow->setObjectName(QStringLiteral("ButtonAddRow"));
        ButtonAddRow->setGeometry(QRect(460, 20, 80, 22));
        ButtonDeleteRow = new QPushButton(tab_2);
        ButtonDeleteRow->setObjectName(QStringLiteral("ButtonDeleteRow"));
        ButtonDeleteRow->setGeometry(QRect(460, 80, 80, 22));
        ButtonPasteRow = new QPushButton(tab_2);
        ButtonPasteRow->setObjectName(QStringLiteral("ButtonPasteRow"));
        ButtonPasteRow->setGeometry(QRect(460, 50, 80, 22));
        ButtonUploadData = new QPushButton(tab_2);
        ButtonUploadData->setObjectName(QStringLiteral("ButtonUploadData"));
        ButtonUploadData->setGeometry(QRect(460, 110, 81, 81));
        QFont font;
        font.setStyleStrategy(QFont::PreferDefault);
        ButtonUploadData->setFont(font);
        ButtonUploadData->setLayoutDirection(Qt::LeftToRight);
        tabWidget->addTab(tab_2, QString());
        progressBar = new QProgressBar(ViewData);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setGeometry(QRect(490, 30, 95, 22));
        progressBar->setValue(100);
        progressBar->setTextVisible(true);
        label_2 = new QLabel(ViewData);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(350, 10, 51, 16));
        Mark = new QComboBox(ViewData);
        Mark->setObjectName(QStringLiteral("Mark"));
        Mark->setGeometry(QRect(350, 30, 111, 22));
        TypeUpload = new QComboBox(ViewData);
        TypeUpload->setObjectName(QStringLiteral("TypeUpload"));
        TypeUpload->setGeometry(QRect(10, 30, 141, 22));
        label_4 = new QLabel(ViewData);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 10, 151, 21));
        TypeMaterial = new QComboBox(ViewData);
        TypeMaterial->setObjectName(QStringLiteral("TypeMaterial"));
        TypeMaterial->setGeometry(QRect(170, 30, 151, 22));
        label = new QLabel(ViewData);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 10, 81, 16));

        retranslateUi(ViewData);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ViewData);
    } // setupUi

    void retranslateUi(QWidget *ViewData)
    {
        ViewData->setWindowTitle(QApplication::translate("ViewData", "Form", Q_NULLPTR));
#ifndef QT_NO_ACCESSIBILITY
        tab->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        label_3->setText(QApplication::translate("ViewData", "\320\236\321\201\321\214 X", Q_NULLPTR));
        label_5->setText(QApplication::translate("ViewData", "\320\236\321\201\321\214 Y", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ViewData", "\320\223\321\200\320\260\321\204\320\270\320\272", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ViewData", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\265\320\271\321\200\320\276\320\275\320\275\321\203\321\216 \321\201\320\265\321\202\321\214", Q_NULLPTR));
        ButtonAddRow->setText(QApplication::translate("ViewData", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        ButtonDeleteRow->setText(QApplication::translate("ViewData", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", Q_NULLPTR));
        ButtonPasteRow->setText(QApplication::translate("ViewData", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        ButtonUploadData->setText(QApplication::translate("ViewData", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214\n"
"\320\275\320\276\320\262\321\213\320\265 \n"
"\320\264\320\260\320\275\320\275\321\213\320\265\n"
"\320\270\320\267 \320\262\320\275\320\265", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ViewData", "\320\242\320\260\320\261\320\273\320\270\321\206\320\260", Q_NULLPTR));
        label_2->setText(QApplication::translate("ViewData", "\320\234\320\260\321\200\320\272\320\260", Q_NULLPTR));
        label_4->setText(QApplication::translate("ViewData", "<html><head/><body><p>\320\242\320\270\320\277 \320\267\320\260\320\263\321\200\321\203\320\267\320\272\320\270 \320\264\320\260\320\275\320\275\321\213\321\205</p></body></html>", Q_NULLPTR));
        label->setText(QApplication::translate("ViewData", "\320\242\320\270\320\277 \321\201\321\213\321\200\321\214\321\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ViewData: public Ui_ViewData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWDATA_H
