#include "servidor.h"

Servidor::Servidor(QObject *parent) : QTcpServer(parent)
{

}

void Servidor:: inicioServidor()
{
    if(!listen(QHostAddress::Any,1234))
    {
        qDebug() <<"error de coneccion";
    }
    else
    {
        qDebug() <<"conexion exitosa!";
    }
}

void Servidor::incomingConnection(qintptr handle)
{
    Cliente *cliente=new Cliente(this);
    cliente->setSocket(handle);

}
