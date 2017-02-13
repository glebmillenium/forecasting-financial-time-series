#ifndef DIALOGUPLOADDATA_H
#define DIALOGUPLOADDATA_H

#include <QDialog>
#include <QStandardItemModel>
#include "interactionwithnetwork.h"
#include <QString>
#include <QtWidgets>

namespace Ui {
class DialogUploadData;
}

class DialogUploadData : public QDialog
{
    Q_OBJECT

public:
    DialogUploadData(QWidget *parent = 0);
    ~DialogUploadData();
    void showing(QString url = "");

private slots:
    void on_Upload_clicked();

private:
    Ui::DialogUploadData *ui;
    QStandardItemModel *model;
    void addItems();
    QVBoxLayout *vBoxLayout;
};

#endif // DIALOGUPLOADDATA_H
