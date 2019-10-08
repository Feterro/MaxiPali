#include <QCoreApplication>
#include "nuevohilo.h"
#include "nuevoservidor.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    NuevoServidor servidor;

    servidor.startServer();

    return a.exec();
}
