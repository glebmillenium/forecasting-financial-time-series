#include "dialoguploaddata.h"
#include "ui_dialoguploaddata.h"

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
    ui->UrlOrPath->setText("https://www.quandl.com/api/v3/datasets/CHRIS/ICE_B1.csv?api_key=A8BF6LxL-pz3f-5fZ3sy&transform=rdiff");
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
void DialogUploadData::showing(QString url)
{
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

    QVBoxLayout* vbox = new QVBoxLayout;
    QList<QHBoxLayout*> hbox;
    QList<QLabel*> labelArray;
    QList<QCheckBox*> checkboxArray;
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

}

void DialogUploadData::on_buttonBox_rejected()
{

}
