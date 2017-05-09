#ifndef CHOOSEMENU_H
#define CHOOSEMENU_H

#include <QWidget>
#include "viewdata.h"

namespace Ui {
class ChooseMenu;
}

class ChooseMenu : public QWidget
{
    Q_OBJECT

public:
    explicit ChooseMenu(QWidget *parent = 0);
    ~ChooseMenu();

private slots:
    void on_viewData_clicked();

private:
    Ui::ChooseMenu *ui;
};

#endif // CHOOSEMENU_H
