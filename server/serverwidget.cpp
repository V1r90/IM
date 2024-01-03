#include "serverwidget.h"
#include "ui_serverwidget.h"

ServerWidget::ServerWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);
}

ServerWidget::~ServerWidget()
{
    delete ui;
}
