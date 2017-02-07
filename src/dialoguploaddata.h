#ifndef DIALOGUPLOADDATA_H
#define DIALOGUPLOADDATA_H

#include <QDialog>
#include <QStandardItemModel>
#include "interactionwithnetwork.h"

namespace Ui {
class DialogUploadData;
}

class DialogUploadData : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUploadData(QWidget *parent = 0);
    ~DialogUploadData();

private slots:
    void on_Upload_clicked();

private:
    Ui::DialogUploadData *ui;
    QStandardItemModel *model;
};

#endif // DIALOGUPLOADDATA_H
