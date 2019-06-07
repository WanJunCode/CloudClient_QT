#include "tester.h"
#include <unistd.h>
#include <QDebug>
#include <string.h>
#include "chatpackage.h"
Client::Client(std::string ip,int port,MainWindow *win)
    :ip_(ip)
     ,port_(port)
     ,w(win)
     ,isConnected(false)
     ,protocal(ECHO){
    connect(this,SIGNAL(msgSig(QString)),this,SLOT(sloMsg(QString)));
    connectServer(ip_,port_);
}

Client::~Client(){
    if(isConnected == true){
        disConnect();
    }
}

bool Client::connectServer(std::string ip,int port){
    if(isConnected == true){
        return true;
    }
    client_ = NET::Connect(ip.data(),port);
    if(client_.clientfd != 0){
//        创建接受线程
        if(0 != pthread_create(&receiveThread,NULL,receiveTrd,this)){
            qDebug()<<"fail to create receive thread"<<endl;
            return false;
        }
        isConnected = true;
        return true;
    }else
        return false;
}

size_t Client::send(std::string message){
    if(status() == true){
        std::string sendMessage;

//        选择不同的协议
        if(protocal == PROTOCAL::ECHO){
            echo_message_t header{0x7E, htons((uint16_t)message.length())};
            sendMessage.append((char *)(&header), sizeof(header));
            sendMessage.append(message.data(), message.length());
        }else{
            ChatPackage package(ChatPackage::CRYPT_UNKNOW,ChatPackage::DATA_STRING,message.data(),message.length());
            sendMessage.append((char *)package.getRawData(),package.getRawDataLength());
        }

        return write(client_.clientfd,sendMessage.data(),sendMessage.length());
    }
    return 0;
}

void Client::disConnect(){
    if(isConnected == true){
        NET::Close(client_);
        isConnected = false;
        pthread_cancel(receiveThread);
    }
}

bool Client::recv(){
    char buffer[MAXLINE];
    bzero(buffer,sizeof(buffer));
    int length = read(client_.clientfd,buffer,sizeof(buffer));
    if(length == 0){
        qDebug()<<"read length is zero";
        isConnected = false;
        emit msgSig(QString::fromStdString(std::string("")));
        return false;
    }else{
        emit msgSig(QString::fromStdString(std::string(buffer,length)));
        return true;
    }
}

void clean_up(void *args){
    UNUSED(args)
    qDebug()<<"Thread clean up"<<endl;
}

void *Client::receiveTrd(void *args){
    pthread_cleanup_push(clean_up,NULL);
    Client *client =(Client *)args;
    while (true) {
        if(client->recv() == false){
            break;
        }
    }
    pthread_cleanup_pop(1);
}

void Client::sloMsg(QString str){
    w->setMsg(str);
}
