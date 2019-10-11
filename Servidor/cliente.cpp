#include "cliente.h"

Cliente::Cliente(QObject *parent) : QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(10);
}

void Cliente::setSocket(int descriptor)
{
    socket=new QTcpSocket(this);

    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));

    socket->setSocketDescriptor(descriptor);

    qDebug()<< "Cliente conectado!";
}
void Cliente:: connected()
{

}
void Cliente::disconnected()
{
    qDebug()<<"cliente desconectado";
}
void Cliente::readyRead()
{
    qDebug()<<socket->readAll();
    nuevaTarea *tarea=new nuevaTarea;
    tarea->setAutoDelete(true);
    connect(tarea,SIGNAL(Resultado(int)),this,SLOT(TaskResult(int)),Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(tarea);
}
    void Cliente::TaskResult(int Numero)
{
    QByteArray Buffer;

    Buffer.append("\r\nTask dio como resultado: ");
    Buffer.append(QString::number(Numero));

    socket->write(Buffer);
}
