#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpServer>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->ensureCursorVisible();
    startServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startServer()
{
    connect(&server, SIGNAL(newConnection()),
        this, SLOT(acceptConnection()));
    connect(&server, SIGNAL(acceptError(QAbstractSocket::SocketError)),
        this, SLOT(acceptError(QAbstractSocket::SocketError)));

    if (!server.listen(QHostAddress::LocalHost,2345)) {
        qDebug() << "Could not start server" << server.errorString();
        ui->textEdit->insertPlainText("Could not start server " + server.errorString());
    } else {
        qDebug() << "Listening...";
        ui->textEdit->insertPlainText( "Listening...localhost 2345\n");
    }
}

void MainWindow::startRead()
{
    QByteArray buffer = client->readAll();
    qDebug() << buffer;
    QString incomingStr = "From tcpClient: " + buffer + "\n";
    ui->textEdit->insertPlainText(incomingStr);

    QByteArray data = "foo foo bee";
    client->write(data);

    client->close();
}

void MainWindow::acceptConnection()
{

    client = server.nextPendingConnection();
    qDebug() << Q_FUNC_INFO << client->isValid() << client->isOpen() << client->isWritable();

    connect(client, SIGNAL(readyRead()),
            this, SLOT(startRead()));
    startRead();
}

void MainWindow::acceptError(QAbstractSocket::SocketError socketError)
{
    qDebug() << Q_FUNC_INFO << socketError;
}
