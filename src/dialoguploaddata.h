#ifndef DIALOGUPLOADDATA_H
#define DIALOGUPLOADDATA_H

#include "interactionwithnetwork.h"
#include <QDialog>
#include <QStandardItemModel>
#include <QString>
#include <QtWidgets>

namespace Ui {
class DialogUploadData;
}

/**
 * @brief The DialogUploadData class
 *   Класс для развёртывания графического
 *   пользовательского интерфейса
 *   скачивания дополнительных данных
 *   с удаленных хранилищ типа
 *   statista, quandl
 *
 * @basename QDialog
 *
 * @license irgups
 * @author An Gleb
 */
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
    /**
     * @brief ui
     *   Указатель на элементы графического
     *   интерфейса
     *
     * @var Ui::DialogUploadData
     */
    Ui::DialogUploadData *ui;

    /**
     * @brief model
     *   Матричный массив, связанный
     *   в последствии с таблицей
     *   типа QTableView
     */
    QStandardItemModel *model;

    /**
     * @brief addItems
     *   Метод, для добавления
     *   элементов (строк)
     *   в таблицу
     *
     * @var void
     * @return void
     */
    void addItems();
};

#endif // DIALOGUPLOADDATA_H
