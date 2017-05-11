#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->passwordDB->setEchoMode(QLineEdit::Password);
    ui->passwordDB->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->errorLearning->setValidator( new QIntValidator(0, 100, this) );
    /*ui->errorLearning->setText(QString(app_errorLearning));
    ui->loginDB->setText(QString::fromUtf8(app_loginDB));
    ui->passwordDB->setText(QString::fromUtf8(app_passwordDB));
    ui->schemeDB->setText(QString::fromUtf8(app_schemeDB));*/
}

Settings::~Settings()
{
    delete ui;
}
