#ifndef CLIENTE_H
#define CLIENTE_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include "nuevatarea.h"

class Cliente : public QObject
{
    Q_OBJECT
public:
    explicit Cliente(QObject *parent = nullptr);
    void setSocket(int descriptor);
signals:

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void TaskResult(int Numero);

private:
    QTcpSocket *socket;

};

#endif // CLIENTE_H
