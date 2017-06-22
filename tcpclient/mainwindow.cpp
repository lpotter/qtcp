#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QAbstractSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _pSocket(0)
{
    ui->setupUi(this);
    ui->textEdit->ensureCursorVisible();
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(connectTcp()));

    QTimer::singleShot(5000,this,SLOT(connectTcp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectTcp()
{
    qDebug() << Q_FUNC_INFO;
    QByteArray data = "blah balh";
    if (!_pSocket) {
        _pSocket = new QTcpSocket(this);
        connect( _pSocket, SIGNAL(readyRead()), SLOT(readTcpData()));
        connect( _pSocket, SIGNAL(error(QAbstractSocket::SocketError)),
                 SLOT(error(QAbstractSocket::SocketError)));
    }

    _pSocket->connectToHost(QHostAddress::LocalHost, 1234);
    if( _pSocket->waitForConnected(-1)) {
        _pSocket->write(data);
    } else {
        qDebug() << Q_FUNC_INFO << _pSocket->errorString();
        ui->textEdit->insertPlainText( _pSocket->errorString() +"\n");
    }
}

void MainWindow::readTcpData()
{
    QByteArray data = _pSocket->readAll();
    qDebug() << Q_FUNC_INFO << data;
    QString incomingStr = "From tcpServer: " + data + "\n";
    ui->textEdit->insertPlainText(incomingStr);
}

void MainWindow::error(QAbstractSocket::SocketError socketError)
{
    qDebug() << Q_FUNC_INFO << socketError;
}
