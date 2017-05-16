#ifndef CREATENETWORK_H
#define CREATENETWORK_H

#include <QWidget>

namespace Ui {
class CreateNetwork;
}

class CreateNetwork : public QWidget
{
    Q_OBJECT

public:
    explicit CreateNetwork(QWidget *parent = 0);
    ~CreateNetwork();

private:
    Ui::CreateNetwork *ui;
};

#endif // CREATENETWORK_H
