#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serialPort(new QSerialPort)
{
    ui->setupUi(this);
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
}


MainWindow::~MainWindow()
{
    delete ui;
    delete serialPort;
}


void MainWindow::on_btnFind_clicked()
{
    ui->cbPorts->clear();
    QList<QSerialPortInfo> serialPorts = QSerialPortInfo::availablePorts();
    if (serialPorts.length() == 0)
    {
        ui->teLog->appendHtml("<font color=red>No port found.</font>");
    }
    else
    {
        ui->teLog->appendHtml("<font color=green>Found ports:</font>");
    }
    for (QSerialPortInfo portInfo : serialPorts)
    {
        ui->cbPorts->addItem(portInfo.portName());
        ui->teLog->appendHtml("<font color=blue>" + portInfo.portName() + "</font>");
    }
}


void MainWindow::on_btnConnect_clicked()
{
    if (serialPort->isOpen())
    {
        serialPort->close();
        ui->teLog->appendHtml("<font color=red>Disconnected.</font>");
        ui->btnConnect->setText("Connect");
    }
    else
    {
        if (ui->cbPorts->currentText().length() == 0)
        {
            ui->teLog->appendHtml("<font color=red>No port selected.</font>");
        }
        else
        {
            serialPort->setPortName(ui->cbPorts->currentText());
            serialPort->open(QIODevice::ReadWrite);
            if (serialPort->isOpen())
            {
                ui->teLog->appendHtml("<font color=green>Connected to " + serialPort->portName() + ".</font>");
                ui->btnConnect->setText("Disconnect");
            }
            else
            {
                ui->teLog->appendHtml("<font color=red>Error connecting to " + serialPort->portName() + ".</font>");
            }
        }
    }
}


