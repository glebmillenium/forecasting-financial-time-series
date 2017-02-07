#include "dialoguploaddata.h"
#include "ui_dialoguploaddata.h"

DialogUploadData::DialogUploadData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUploadData)
{
    ui->setupUi(this);
    ui->TypeUpload->addItem("Ссылка url");
    ui->TypeUpload->addItem("Путь к файлу");
    ui->TypeMaterial->addItem("Нефть");
    ui->TypeMaterial->addItem("Газ");
    ui->Mark->addItem("Brent");
    const char* link =
            "https://www.quandl.com/api/v3/datasets/CHRIS/ICE_B1.csv?api_key=A8BF6LxL-pz3f-5fZ3sy&transform=rdiff";
    ui->UrlOrPath->setText(link);
}

DialogUploadData::~DialogUploadData()
{
    delete ui;
}

void DialogUploadData::on_Upload_clicked()
{
    const char* fileName = "file.csv";
    InteractionWithNetwork::getQuandlData(ui->UrlOrPath->text().toUtf8().constData(), fileName);
    model = new QStandardItemModel(InteractionWithNetwork::countRowsInTable(fileName),
                                   InteractionWithNetwork::countColumnsInTable(fileName));
    InteractionWithNetwork::setNameColumns(model, fileName);
    InteractionWithNetwork::fillingTable(fileName, model, this);
    ui->tableView->setModel(model);
}
