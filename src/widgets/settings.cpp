#include "settings.h"
#include "ui_settings.h"
#include "core/defs.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->passwordDB->setEchoMode(QLineEdit::Password);
    ui->passwordDB->setInputMethodHints(Qt::ImhHiddenText| Qt::ImhNoPredictiveText|Qt::ImhNoAutoUppercase);
    ui->errorLearning->setText(QString::number(errorLearning));
    ui->loginDB->setText(QString::fromUtf8(loginDB));
    ui->passwordDB->setText(QString::fromUtf8(passwordDB));
    ui->schemeDB->setText(QString::fromUtf8(schemeDB));
    ui->errorLearning->setValidator( new QIntValidator(0, 100, this) );
}

Settings::~Settings()
{
    delete ui;
}
