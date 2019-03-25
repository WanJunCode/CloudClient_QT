#ifndef TESTER_H
#define TESTER_H

#include <QObject>
#include <string>
#include <pthread.h>
#include "mainwindow.h"
#include "net_tool.h"
#include <QObject>
#include <QDebug>
#include <QString>

class MainWindow;

class Client : public QObject{
        Q_OBJECT
private:
    typedef struct message
    {
        uint8_t identity; // 0x7E
        uint16_t length;
    } __attribute__((packed)) echo_message_t;

public:
    Client(std::string ip,int port,MainWindow *win);
    ~Client();
    bool connectServer(std::string ip,int port);
    size_t send(std::string message);
    void recv();
    void disConnect();
    bool status(){
        return isConnected;
    }
private:
    static void *receiveTrd(void *args);

private:
    std::string ip_;
    int port_;
    MainWindow *w;
    bool isConnected;
    NET::remote_client client_;
    pthread_t receiveThread;

signals:
    void msgSig(QString str);

public slots:
    void sloMsg(QString str);
};

#endif // TESTER_H
