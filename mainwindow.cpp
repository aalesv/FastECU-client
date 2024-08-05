// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QtGui/QIntValidator>

QString now()
{
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
    return formattedTime;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , startup(new Startup("", this))
    , progress_bar(new QProgressBar(this))
{
    ui->setupUi(this);
    //Init config groupbox
    ui->lineEdit_broker_address->setText(peerAddress);
    ui->lineEdit_broker_port->setText( QString::number(peerPort) );
    ui->lineEdit_broker_port->setValidator( new QIntValidator(1, 65535, this) );
    ui->plainTextEdit_logs->setReadOnly(true);
    update_ui();
    statusBar()->addWidget(progress_bar);
    QObject::connect(startup, &Startup::log, this, &MainWindow::log);
    QObject::connect(startup, &Startup::set_progressbar_value,
                     this, &MainWindow::set_progressbar_value);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_ui(void)
{
    ui->lineEdit_broker_address->setDisabled(connectionStarted);
    ui->lineEdit_broker_port->setDisabled(connectionStarted);
    ui->pushButton_connect->setDisabled(connectionStarted);
    ui->pushButton_disconnect->setEnabled(connectionStarted);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    int width = e->size().width();
    int margin;
    QSize size;

    margin = ui->groupBox_broker_config->geometry().x();
    size = ui->groupBox_broker_config->size();
    size.setWidth(width - 2*margin);
    ui->groupBox_broker_config->resize(size);

    margin = ui->plainTextEdit_logs->geometry().x();
    size = ui->plainTextEdit_logs->size();
    size.setWidth(width - 2*margin);

    int height = e->size().height();
    margin = ui->plainTextEdit_logs->geometry().y();
    //Height of status bar is about 20 by default
    size.setHeight(height - margin - 40);
    ui->plainTextEdit_logs->resize(size);
}

void MainWindow::on_pushButton_connect_released()
{
    connectionStarted = true;
    update_ui();
    QString peer = peerAddress+":"+QString::number(peerPort);
    qDebug() << "Connecting to " << peer;
    log("Connecting to " + peer);
    startup->setPeerAddress(peer);
    startup->start();
}

void MainWindow::on_pushButton_disconnect_released()
{
    connectionStarted = false;
    update_ui();
    log("Closing connection to "+peerAddress+":"+QString::number(peerPort));
    startup->stop();
    set_progressbar_value(0);
}

void MainWindow::on_lineEdit_broker_address_textChanged(const QString &arg1)
{
    peerAddress = arg1;
}

void MainWindow::on_lineEdit_broker_port_textChanged(const QString &arg1)
{
    peerPort = arg1.toInt();
}

void MainWindow::log(QString message)
{
    ui->plainTextEdit_logs->appendPlainText(now()+" "+message);
}

void MainWindow::set_progressbar_value(int value)
{
    progress_bar->setValue(value);
}
