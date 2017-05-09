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
    QTableView *tableView;
    QPushButton *Upload;
    QLineEdit *UrlOrPath;
    QPushButton *ButtonDeleteRow;
    QLabel *label_3;
    QPushButton *ButtonPasteRow;
    QListWidget *listWidget;

    void setupUi(QDialog *DialogUploadData)
    {
        if (DialogUploadData->objectName().isEmpty())
            DialogUploadData->setObjectName(QStringLiteral("DialogUploadData"));
        DialogUploadData->resize(488, 308);
        buttonBox = new QDialogButtonBox(DialogUploadData);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(290, 269, 171, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        ButtonAddRow = new QPushButton(DialogUploadData);
        ButtonAddRow->setObjectName(QStringLiteral("ButtonAddRow"));
        ButtonAddRow->setGeometry(QRect(380, 69, 80, 21));
        tableView = new QTableView(DialogUploadData);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(10, 59, 361, 151));
        Upload = new QPushButton(DialogUploadData);
        Upload->setObjectName(QStringLiteral("Upload"));
        Upload->setGeometry(QRect(351, 29, 111, 21));
        QFont font;
        font.setStyleStrategy(QFont::PreferDefault);
        Upload->setFont(font);
        Upload->setLayoutDirection(Qt::LeftToRight);
        UrlOrPath = new QLineEdit(DialogUploadData);
        UrlOrPath->setObjectName(QStringLiteral("UrlOrPath"));
        UrlOrPath->setGeometry(QRect(20, 29, 301, 22));
        ButtonDeleteRow = new QPushButton(DialogUploadData);
        ButtonDeleteRow->setObjectName(QStringLiteral("ButtonDeleteRow"));
        ButtonDeleteRow->setGeometry(QRect(380, 129, 80, 22));
        label_3 = new QLabel(DialogUploadData);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 10, 121, 16));
        ButtonPasteRow = new QPushButton(DialogUploadData);
        ButtonPasteRow->setObjectName(QStringLiteral("ButtonPasteRow"));
        ButtonPasteRow->setGeometry(QRect(380, 99, 80, 22));
        listWidget = new QListWidget(DialogUploadData);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(15, 220, 261, 71));

        retranslateUi(DialogUploadData);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogUploadData, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogUploadData, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogUploadData);
    } // setupUi

    void retranslateUi(QDialog *DialogUploadData)
    {
        DialogUploadData->setWindowTitle(QApplication::translate("DialogUploadData", "Dialog", Q_NULLPTR));
        ButtonAddRow->setText(QApplication::translate("DialogUploadData", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        Upload->setText(QApplication::translate("DialogUploadData", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", Q_NULLPTR));
        ButtonDeleteRow->setText(QApplication::translate("DialogUploadData", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", Q_NULLPTR));
        label_3->setText(QApplication::translate("DialogUploadData", "<html><head/><body><p>url/\320\277\321\203\321\202\321\214 \320\272 \321\204\320\260\320\271\320\273\321\203</p></body></html>", Q_NULLPTR));
        ButtonPasteRow->setText(QApplication::translate("DialogUploadData", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DialogUploadData: public Ui_DialogUploadData {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGUPLOADDATA_H
