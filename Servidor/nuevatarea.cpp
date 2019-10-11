#include "nuevatarea.h"

nuevaTarea::nuevaTarea()
{

}

void nuevaTarea::run()
{
    qDebug()<<"Tarea iniciada!";

    int numero=100;
    for(int i=0;i<0;i--)
    {
       numero--;
    }
    qDebug()<<"Tarea finalizada!";
    emit Resultado(numero);
}
