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
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *widget;
    QWidget *tab_2;
    QTableView *tableView;
    QPushButton *pushButton;
    QDateEdit *dateEdit;
    QPushButton *ButtonAddRow;
    QPushButton *ButtonDeleteRow;
    QPushButton *ButtonPasteRow;
    QPushButton *ButtonUploadData;
    QProgressBar *progressBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(579, 428);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../\320\227\320\260\320\263\321\200\321\203\320\267\320\272\320\270/chart02.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 80, 551, 341));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        widget = new QWidget(tab);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 521, 291));
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
        ButtonUploadData->setGeometry(QRect(460, 110, 81, 61));
        QFont font;
        font.setStyleStrategy(QFont::PreferDefault);
        ButtonUploadData->setFont(font);
        ButtonUploadData->setLayoutDirection(Qt::LeftToRight);
        tabWidget->addTab(tab_2, QString());
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setGeometry(QRect(460, 50, 95, 22));
        progressBar->setValue(100);
        progressBar->setTextVisible(true);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\260 \320\264\320\273\321\217 \320\277\321\200\320\276\320\263\320\275\320\276\320\267\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217 \321\200\321\213\320\275\320\276\321\207\320\275\321\213\321\205 \321\206\320\265\320\275", Q_NULLPTR));
#ifndef QT_NO_ACCESSIBILITY
        tab->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\320\223\321\200\320\260\321\204\320\270\320\272", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \320\275\320\265\320\271\321\200\320\276\320\275\320\275\321\203\321\216 \321\201\320\265\321\202\321\214", Q_NULLPTR));
        ButtonAddRow->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        ButtonDeleteRow->setText(QApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214", Q_NULLPTR));
        ButtonPasteRow->setText(QApplication::translate("MainWindow", "\320\222\321\201\321\202\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        ButtonUploadData->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214\n"
"\320\275\320\276\320\262\321\213\320\265 \n"
"\320\264\320\260\320\275\320\275\321\213\320\265\n"
"\320\270\320\267 \320\262\320\275\320\265", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\320\242\320\260\320\261\320\273\320\270\321\206\320\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
