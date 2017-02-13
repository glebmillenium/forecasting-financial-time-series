#include "dialoguploaddata.h"
#include "ui_dialoguploaddata.h"

DialogUploadData::DialogUploadData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUploadData)
{
    addItems();
}

void DialogUploadData::addItems()
{
    ui->setupUi(this);
    ui->TypeUpload->addItem("Ссылка url");
    ui->TypeUpload->addItem("Путь к файлу");
    ui->TypeMaterial->addItem("Нефть");
    ui->TypeMaterial->addItem("Газ");
    ui->Mark->addItem("Brent");
    ui->UrlOrPath->setText("https://www.quandl.com/api/v3/datasets/CHRIS/ICE_B1.csv?api_key=A8BF6LxL-pz3f-5fZ3sy&transform=rdiff");
}

DialogUploadData::~DialogUploadData()
{
    delete ui;
}

void DialogUploadData::showing(QString url)
{
    if(url.compare("") != 0)
    {
        ui->UrlOrPath->setText(url);
    }
    this->show();
}

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
