#ifndef NUEVOHILO_H
#define NUEVOHILO_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class NuevoHilo:public QThread
{
public:
    NuevoHilo();
    Q_OBJECT
    public:
        explicit NuevoHilo(qintptr ID, QObject *parent = 0);

        void run();

    signals:
        void error(QTcpSocket::SocketError socketerror);

    public slots:
        void readyRead();
        void disconnected();

    private:
        QTcpSocket *socket;
        qintptr socketDescriptor;
};

#endif // NUEVOHILO_H
