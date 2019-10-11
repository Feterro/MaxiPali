#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "cliente.h"

class Servidor : public QTcpServer
{
    Q_OBJECT
public:
    explicit Servidor(QObject *parent = nullptr);
    void inicioServidor();

protected:
    void incomingConnection(qintptr handle);  //posible error= poner override despues de()

signals:

public slots:
};

#endif // SERVIDOR_H
