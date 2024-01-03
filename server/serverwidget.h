#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H
#include "ServerSocket.h"
#include <QDialog>

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QDialog
{
    Q_OBJECT

public:
    explicit ServerWidget(QWidget *parent = nullptr);
    ~ServerWidget();

private:
    Ui::ServerWidget *ui;
};

#endif // SERVERWIDGET_H
