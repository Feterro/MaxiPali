#ifndef NUEVOSERVIDOR_H
#define NUEVOSERVIDOR_H

#include <QObject>
#include <QTcpServer>

class NuevoServidor:public QTcpServer
{
    Q_OBJECT
   public:
       explicit NuevoServidor(QObject *parent = 0);
       void startServer();
   signals:

   public slots:

   protected:
       void incomingConnection(qintptr socketDescriptor);
};

#endif // NUEVOSERVIDOR_H
