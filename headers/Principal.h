#ifndef PRINCIPAL_H
#define PRINCIPAL_H
#include "Cola.h"
using namespace std;
class Principal
{
    public:
        Principal(){
        }
        bool validarCliente(ArbolB cliente, string ced);
        void escogerPasillo(arbolPas pasillo);
        void escogerProducto(arbolPas pasillo, string codPas);
        void escogerMarca(arbolPas pasillos,string codPas,string codProd);
        void comprar(arbolPas pasillos);
        bool validarAdministrador(ArbolB administrador, string cod);
        void agregarCola(ArbolB cliente, string cedula);
    private:
        colaCliente cola;
};

#endif // PRINCIPAL_H
