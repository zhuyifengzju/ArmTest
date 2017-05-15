#ifndef UDP_H
#define UDP_H

#include <QtNetwork/QUdpSocket>
#include <QHostAddress>
#include <QThread>
#include <vector>
#include <string>

#pragma once
class Client: public QThread
{
    Q_OBJECT
public:
        explicit Client(QObject *parent =0);
        ~Client();
        void run();
        int ClientStart;
        void InitSocket();
        int getFlag(){return flag;}
        void setFlag(int i){flag = i;}
        void send();
        QUdpSocket *udpSocket;
        void getPositionx(std::vector<double> &v);
        void getPositiony(std::vector<double> &v);
        void getPositionz(std::vector<double> &v);
        void getAction_norm(double&,double&,double&);
        void getAction_vel(double&,double&,double&);

        private slots:
        void Recv();

private:
        std::vector<std::string> v;
        int flag=1;
        std::vector<double> x,y,z;
        double normx,normy,normz;
        double velx,vely,velz;
signals:
        void dataReceived();


};


/*
#include <QtNetwork/QUdpSocket>
#include <QHostAddress>
#include <QThread>
#include <vector>
#include <string>

#pragma once

class Client: public QObject
{
    Q_OBJECT
public:
        void InitSocket();
        int getFlag(){return flag;}
private slots:
        void Recv();

private:
        std::vector<std::string> v;
        int flag=1;

};
*/

#endif // UDP_H
