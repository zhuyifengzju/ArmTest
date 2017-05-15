#include "udp.h"
#include <QProcess>
#include <iostream>
using namespace std;

char ToAddress[20] = "127.0.0.1";
char information[20] = "action";
Client::Client(QObject * parent):QThread(parent)
{
       udpSocket = 0;

}

Client::~Client()
{

    udpSocket->deleteLater();
    cout<<8<<endl;
    quit();
    wait();


}

void Client::InitSocket()
{
    flag = 1;
    ClientStart = 0;

 }

void Client::send()
{
    udpSocket->writeDatagram(information, QHostAddress(ToAddress),31500);

}

void Client::run()
{
    cout<<1<<endl;
    udpSocket = new QUdpSocket(this);
     cout<<2<<endl;
    udpSocket->bind(QHostAddress::Any,31600);
     cout<<3<<endl;
    udpSocket->writeDatagram(information, QHostAddress(ToAddress),31500);
     cout<<4<<endl;
    connect(udpSocket, SIGNAL(readyRead()),this,SLOT(Recv()),Qt::DirectConnection);
     cout<<5<<endl;
    exec();
    cout<<6<<endl;
}

 void Client::Recv()
 {
     //while(udpSocket->hasPendingDatagrams())
     //if (this->ClientStart)
     {
         QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        string s;

        for (int i=0;i<datagram.size();i++)
        {
            //printf("%c", datagram.at(i));
            s = s+datagram.at(i);
        }
        int l = s.length();
        if (atoi(s.c_str()))
        {
            cout<<"length:"<<endl;
            vector<double>().swap(x);
            vector<double>().swap(y);
            vector<double>().swap(z);

        }
        else
        if (l<30)
        {
            int d = s.find(' ',0);
            string s1 = s.substr(0,d-1);
            int d1 = s.find(' ',d+1);
            string s2 = s.substr(d+1,d1-1);
            string s3 = s.substr(d1+1,l);
            x.push_back(atof(s1.c_str()));
            y.push_back(atof(s2.c_str()));
            z.push_back(atof(s3.c_str()));
           // cout<< atof(s1.c_str())<<" "<< atof(s2.c_str())<<" "<<atof(s3.c_str())<<endl;

            //cout<<s1<<" "<<s2<<" "<<s3<<endl;
        }
        else
        {
            int d = s.find(' ',0);
            string s1 = s.substr(0,d-1);
            int d1 = s.find(' ',d+1);
            string s2 = s.substr(d+1,d1-1);
            int d2 = s.find(' ',d1+1);
            string s3 = s.substr(d1+1,d2-1);
            d = s.find(' ',d2+1);
            string s4 = s.substr(d2+1,d-1);
            d1 = s.find(' ',d+1);
            string s5 = s.substr(d+1,d1-1);
            string s6 = s.substr(d1+1,l);
            normx = atof(s1.c_str());normy = atof(s2.c_str());normz = atof(s3.c_str());
            velx = atof(s4.c_str());vely = atof(s5.c_str());velz = atof(s6.c_str());
            cout<< normx<<" "<< normy<<" "<<normz<<endl;
            cout<< velx <<" "<< vely <<" "<<velz <<endl;
            cout<<x.size()<<endl;
            //cout<< atof(s1.c_str())<<" "<< atof(s2.c_str())<<" "<<atof(s3.c_str())<<endl;
            //cout<< atof(s4.c_str())<<" "<< atof(s5.c_str())<<" "<<atof(s6.c_str())<<endl;
            //disconnect(udpSocket, SIGNAL(readyRead()),this,SLOT(Recv()));
            flag = 0;
// udpSocket->writeDatagram(information, QHostAddress(ToAddress),31500);
        }


    }
   //  udpSocket->close();
}

void Client::getPositionx(vector<double> &v)
{
    x.swap(v);

}

void Client::getPositiony(vector<double> &v)
{
    y.swap(v);

}

void Client::getPositionz(vector<double> &v)
{
    z.swap(v);

}


void Client::getAction_norm(double& x, double& y, double& z)
{

    x = normx;
    y = normy;
    z = normz;


}
void Client::getAction_vel(double& x, double& y, double& z)
{
    x = velx;
    y = vely;
    z = velz;

}
/*
#include "udp.h"
#include <QProcess>
#include <iostream>
using namespace std;
QUdpSocket *udpSocket;
char ToAddress[20] = "127.0.0.1";

void Client::InitSocket()
{
    //QProcess *proc = new QProcess;
    //proc->start("python ~/socket/UDP/client.py");
    //cout<<"start"<<endl;
    char information[] = "action";
    flag = 1;
    udpSocket = new QUdpSocket(this);
     udpSocket->bind(QHostAddress::Any,31600);
     udpSocket->writeDatagram(information, QHostAddress(ToAddress),31500);
     connect(udpSocket, SIGNAL(readyRead()),this,SLOT(Recv()));

 }


 void Client::Recv()
 {
     //while(udpSocket->hasPendingDatagrams())
     {
         QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        string s;

        for (int i=0;i<datagram.size();i++)
        {
            //printf("%c", datagram.at(i));
            s = s+datagram.at(i);
        }
        int l = s.length();
        if (atoi(s.c_str()))
        {
            cout<<"length:"<<endl;
        }
        else
        if (l<30)
        {
            int d = s.find(' ',0);
            string s1 = s.substr(0,d-1);
            int d1 = s.find(' ',d+1);
            string s2 = s.substr(d+1,d1-1);
            string s3 = s.substr(d1+1,l);
            cout<< atof(s1.c_str())<<" "<< atof(s2.c_str())<<" "<<atof(s3.c_str())<<endl;
            //cout<<s1<<" "<<s2<<" "<<s3<<endl;
        }
        else
        {
            int d = s.find(' ',0);
            string s1 = s.substr(0,d-1);
            int d1 = s.find(' ',d+1);
            string s2 = s.substr(d+1,d1-1);
            int d2 = s.find(' ',d1+1);
            string s3 = s.substr(d1+1,d2-1);
            d = s.find(' ',d2+1);
            string s4 = s.substr(d2+1,d-1);
            d1 = s.find(' ',d+1);
            string s5 = s.substr(d+1,d1-1);
            string s6 = s.substr(d1+1,l);
            cout<< atof(s1.c_str())<<" "<< atof(s2.c_str())<<" "<<atof(s3.c_str())<<endl;
            cout<< atof(s4.c_str())<<" "<< atof(s5.c_str())<<" "<<atof(s6.c_str())<<endl;
            disconnect(udpSocket, SIGNAL(readyRead()),this,SLOT(Recv()));
            flag = 0;
        }


    }
   //  udpSocket->close();
}
*/
