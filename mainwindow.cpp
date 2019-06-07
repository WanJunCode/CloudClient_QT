#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    if(client_ != NULL){
        delete client_;
    }
    delete ui;
}

void MainWindow::on_pushButtonLink_clicked()
{
    std::string ip = ui->lineEditAddress->text().toStdString();
    int port = ui->lineEditPort->text().toInt();
    if(client_ == NULL){
        // 初始化
        client_ = new Client(ip,port,this);
        if(client_->status() == true){
            ui->labelStatus->setText("连接成功");
            ui->pushButtonLink->setText("断开");
        }else{
            ui->textEditRecord->setText("连接失败");
        }
    }else if(client_->status() == false){
        bool ret = client_->connectServer(ip,port);
        if(ret == true){
            ui->labelStatus->setText("连接成功");
            ui->pushButtonLink->setText("断开");
        }
    }else{
        // 断开连接
        client_->disConnect();
        ui->labelStatus->setText("未连接");
        ui->pushButtonLink->setText("连接");
    }
}

void MainWindow::on_pushButtonSend_clicked()
{
    std::string msg = ui->textEditSend->toPlainText().toStdString();
    if(client_)
        client_->send(msg);
}

void MainWindow::setMsg(QString msg){
    if(client_->status()==false){
        ui->labelStatus->setText("连接失败");
        ui->pushButtonLink->setText("连接");
    }
    ui->textEditRecord->append(msg);
}

void MainWindow::on_radioButton_clicked()
{
    if(client_){
        if(client_->getProtocal()==Client::ECHO){
            client_->setProtocal(Client::CHAT);
        }else{
            client_->setProtocal(Client::ECHO);
        }
    }
}
