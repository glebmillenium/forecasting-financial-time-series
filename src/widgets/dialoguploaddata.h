#ifndef DIALOGUPLOADDATA_H
#define DIALOGUPLOADDATA_H

#include "../core/interactionwithnetwork.h"
#include <QDialog>
#include <QStandardItemModel>
#include <QString>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>

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
    /**
     * @brief model
     *   Матричный массив, связанный
     *   в последствии с таблицей
     *   типа QTableView
     */
    QStandardItemModel *model;

private slots:
    void on_Upload_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

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
