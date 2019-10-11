#include <QCoreApplication>
#include "servidor.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Servidor servidor;
    servidor.inicioServidor();

    return a.exec();
}
