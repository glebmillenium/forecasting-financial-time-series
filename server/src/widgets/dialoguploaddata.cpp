#include "dialoguploaddata.h"
#include "ui_dialoguploaddata.h"
#include <QDebug>


using namespace std;

/**
 * @brief DialogUploadData::DialogUploadData
 * Конструктор, для создания содержимого
 * диалогового окна
 *
 * @param parent
 */
DialogUploadData::DialogUploadData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUploadData)
{
    addItems();
}

/**
 * @brief DialogUploadData::addItems
 *   Метод, для добавления
 *   элементов (строк)
 *   в таблицу
 *
 * @var    void
 * @return void
 */
void DialogUploadData::addItems()
{
    ui->setupUi(this);
    ui->UrlOrPath->setText(
                "https://www.quandl.com/api/v3/datasets/CHRIS/ICE_B1.csv?api_key=A8BF6LxL-pz3f-5fZ3sy&transform=rdiff");
}

/**
 * @brief DialogUploadData::~DialogUploadData
 * Деконструктор класса
 */
DialogUploadData::~DialogUploadData()
{
    delete ui;
}

/**
 * @brief DialogUploadData::showing
 *   Метод, для показа
 *   графического окна
 *
 * @param url путь к интернет ресурсу,
 *   для скачивания данных в виде
 *   csv файла
 */
void DialogUploadData::showing(QString url, QString fileName)
{
    this->ui->listWidget->clear();
    this->fileName = fileName;
    model = new QStandardItemModel();
    ui->tableView->setModel(model);
    if(url.compare("") != 0)
    {
        ui->UrlOrPath->setText(url);
    }
    this->show();
}

/**
 * @brief DialogUploadData::on_Upload_clicked
 *   Событие, вызываемого кликом по кнопке
 *   "Upload". Осуществляет загрузку данных
 *   с удаленного хранилища, и заполнение
 *   таблицы
 *
 * @param  void
 * @return void
 */
void DialogUploadData::on_Upload_clicked()
{
    const char* fileName = "file.csv";
    InteractionWithNetwork::getQuandlData(ui->UrlOrPath->text().toUtf8().constData(), fileName);

    int countColumns = InteractionWithNetwork::countColumnsInTable(fileName);
    model = new QStandardItemModel(InteractionWithNetwork::countRowsInTable(fileName),
                                   countColumns);
    QStringList listColumns = InteractionWithNetwork::setNameColumns(model, fileName);

    for(int i = 0; i < listColumns.size(); i++)
    {
        QListWidgetItem *item = new QListWidgetItem;
        item->setData( Qt::DisplayRole, listColumns[i] );
        item->setData( Qt::CheckStateRole, !Qt::Checked);
        ui->listWidget->addItem(item);
    }

    InteractionWithNetwork::fillingTable(fileName, model, this);
    ui->tableView->setModel(model);
}

void DialogUploadData::on_buttonBox_accepted()
{
    for(int i = ui->listWidget->count() - 1 ; i >= 0 ; i--)
    {
        if(!(ui->listWidget->item(i)->checkState() == Qt::Checked))
        {
            model->removeColumn(i);
        }
    }
    ui->tableView->setModel(model);
    writeToFile("file.csv");
    char* str = new char[256];

    sprintf(str, "mv file.csv %s", this->fileName.toStdString().c_str());
    system(str);
}

void DialogUploadData::writeToFile(char* file)
{
    fstream out;
    out.open(file, ios::out);
    for(int i = 0; i < model->columnCount(); i++)
    {
        out << model->headerData(i, Qt::Horizontal).toString().toStdString().c_str();
        if(i != (model->columnCount() - 1))
        {
            out << ",";
        }

    }
    out << "\n";
    for(int i = 0; i < model->rowCount(); i++)
    {
        for(int j = 0; j < model->columnCount(); j++)
        {
            out << model->item(i, j)->text().toStdString().c_str();
            if(j != model->columnCount() - 1)
            {
                out << ",";
            }
        }
        if(i != (model->rowCount() - 1))
        {
            out << "\n";
        }
    }
    out.close();
}

void DialogUploadData::on_buttonBox_rejected()
{
    remove("file.csv");
}
