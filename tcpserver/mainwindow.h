#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startServer();
public slots:
  void acceptConnection();
  void startRead();

  void acceptError(QAbstractSocket::SocketError socketError);
//protected:
//    void incomingConnection(int socketDescriptor);
private:
    Ui::MainWindow *ui;
     QTcpSocket* client;
     QTcpServer server;
};

#endif // MAINWINDOW_H
