#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include "startup.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void log(QString message);

private slots:
    void on_pushButton_connect_released();
    void on_pushButton_disconnect_released();
    void on_lineEdit_broker_address_textChanged(const QString &arg1);
    void on_lineEdit_broker_port_textChanged(const QString &arg1);
    void update_ui(void);
    void resizeEvent(QResizeEvent *e);
    void set_progressbar_value(int value);

private:
    Ui::MainWindow *ui;
    QString peerAddress = "127.0.0.1";
    int peerPort = 33315;
    bool connectionStarted = false;
    Startup *startup;
    QProgressBar *progress_bar;
};
#endif // MAINWINDOW_H
