/********************************************************************************
** Form generated from reading UI file 'dialoguploaddata.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGUPLOADDATA_H
#define UI_DIALOGUPLOADDATA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_DialogUploadData
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *ButtonAddRow;
    QLabel *label_2;
    QTableView *tableView;
    QComboBox *Mark;
    QComboBox *TypeUpload;
    QComboBox *TypeMaterial;
    QPushButton *Upload;
    QLineEdit *UrlOrPath;
    QPushButton *ButtonDeleteRow;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label;
    QPushButton *ButtonPasteRow;
    QListWidget *listWidget;

    void setupUi(QDialog *DialogUploadData)
    {
        if (DialogUploadData->objectName().isEmpty())
            DialogUploadData->setObjectName(QStringLiteral("DialogUploadData"));
        DialogUploadData->resize(470, 363);
        buttonBox = new QDialogButtonBox(DialogUploadData);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(290, 320, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        ButtonAddRow = new QPushButton(DialogUploadData);
        ButtonAddRow->setObjectName(QStringLiteral("ButtonAddRow"));
        ButtonAddRow->setGeometry(QRect(380, 120, 80, 21));
        label_2 = new QLabel(DialogUploadData);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(350, 10, 40, 16));
        tableView = new QTableView(DialogUploadData);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 110, 361, 151));
        Mark = new QComboBox(DialogUploadData);
        Mark->setObjectName(QStringLiteral("Mark"));
        Mark->setGeometry(QRect(350, 30, 111, 22));
        TypeUpload = new QComboBox(DialogUploadData);
        TypeUpload->setObjectName(QStringLiteral("TypeUpload"));
        TypeUpload->setGeometry(QRect(10, 30, 141, 22));
        TypeMaterial = new QComboBox(DialogUploadData);
        TypeMaterial->setObjectName(QStringLiteral("TypeMaterial"));
        TypeMaterial->setGeometry(QRect(170, 30, 151, 22));
        Upload = new QPushButton(DialogUploadData);
        Upload->setObjectName(QStringLiteral("Upload"));
        Upload->setGeometry(QRect(351, 80, 111, 21));
        QFont font;
        font.setStyleStrategy(QFont::PreferDefault);
        Upload->setFont(font);
        Upload->setLayoutDirection(Qt::LeftToRight);
        UrlOrPath = new QLineEdit(DialogUploadData);
        UrlOrPath->setObjectName(QStringLiteral("UrlOrPath"));
        UrlOrPath->setGeometry(QRect(170, 80, 151, 22));
        ButtonDeleteRow = new QPushButton(DialogUploadData);
        ButtonDeleteRow->setObjectName(QStringLiteral("ButtonDeleteRow"));
        ButtonDeleteRow->setGeometry(QRect(380, 180, 80, 22));
        label_3 = new QLabel(DialogUploadData);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(170, 60, 111, 16));
        label_4 = new QLabel(DialogUploadData);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 10, 151, 21));
        label = new QLabel(DialogUploadData);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(170, 10, 65, 16));
        ButtonPasteRow = new QPushButton(DialogUploadData);
        ButtonPasteRow->setObjectName(QStringLiteral("ButtonPasteRow"));
        ButtonPasteRow->setGeometry(QRect(380, 150, 80, 22));
        listWidget = new QListWidget(DialogUploadData);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(15, 271, 261, 71));

        retranslateUi(DialogUploadData);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogUploadData, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogUploadData, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogUploadData);
    } // setupUi

    void retranslateUi(QDialog *DialogUploadData)
    {
        DialogUploadData->setWindowTitle(QApplication::translate("DialogUploadData", "Dialog", Q_NULLPTR));
        ButtonAddRow->setText(QApplication::translate("DialogUploadData", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        label_2->setText(QApplication::translate("DialogUploadData", "\320\234\320\260\321\200\320\272\320\260", Q_NULLPTR));
        Upload->setText(QApplication::translate("DialogUploadData", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", Q_NULLPTR));
        ButtonDeleteRow->setText(QApplication::translate("DialogUploadData", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogUploadData", "<html><head/><body><p>url/\320\277\321\203\321\202\321\214 \320\272 \321\204\320\260\320\271\320\273\321\203</p></body></html>", Q_NULLPTR));
        label_4->setText(QApplication::translate("DialogUploadData", "<html><head/><body><p>\320\242\320\270\320\277 \320\267\320\260\320\263\321\200\321\203\320\267\320\272\320\270 \320\264\320\260\320\275\320\275\321\213\321\205</p></body></html>", Q_NULLPTR));
        label->setText(QApplication::translate("DialogUploadData", "\320\242\320\270\320\277 \321\201\321\213\321\200\321\214\321\217", Q_NULLPTR));
        ButtonPasteRow->setText(QApplication::translate("DialogUploadData", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogUploadData: public Ui_DialogUploadData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGUPLOADDATA_H
