#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Radio {
 const int PacketSize = 32;
}

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnFind_clicked();

    void on_btnConnect_clicked();

    void on_serial_rcv();

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;
    QString serialBuffer;
    QString packetBuffer;
};

#endif // MAINWINDOW_H
