#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractSocket>
namespace Ui {
class MainWindow;
}

class QTcpSocket;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void readTcpData();
    void connectTcp();
    void error(QAbstractSocket::SocketError socketError);
private:
    Ui::MainWindow *ui;
    QTcpSocket *_pSocket;

};

#endif // MAINWINDOW_H
