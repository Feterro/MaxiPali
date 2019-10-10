
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#ifndef ARBOLB_ARBOLB_H
#define ARBOLB_ARBOLB_H
#include <cstdlib>
using namespace std;
class nodoCliente {
/*
Clase creadora de nodos de clientes para ser
usados en listas. Clase amiga de listaDCpas,
listaSimple y nodoCliente
*/

   public:
    nodoCliente(int ced, string nom, string cor, string tel)
    {
        cedula=ced;
        nombre=nom;
        telefono=tel;
        correo=cor;
        cantFacturas=0;
        mont=0;
        fact="";
    }
   private:
    int cedula;
    string nombre;
    string telefono;
    string correo;
    string fact="f";
    int mont=0;
    int cantFacturas;
   friend class ArbolB;
};
class Pagina;
typedef Pagina *pPagina;
typedef nodoCliente *tipoClave;
class Pagina
{
protected:
    tipoClave *claves;
    pPagina *ramas;
    int cuenta;
private:
    int max;
public:
    Pagina(int orden)
    {
        this->max = orden;
        this->claves = new tipoClave[orden];
        this->ramas = new pPagina[orden];
        for(int i = 0; i <= orden; i++)
        {
            this->ramas[i] = NULL;
        }
    }
    bool nodoLleno() { return (this->cuenta == this->max - 1); }
    bool nodoSemiVacio() { return (this->cuenta < this->max / 2); }
    tipoClave obtenerClave(int i) { return this->claves[i]; }
    void cambiarClave(int i, tipoClave clave) { this->claves[i] = clave; }
    Pagina *obtenerRama(int i) { return this->ramas[i]; }
    void cambiarRamas(int i, Pagina *p) { this->ramas[i] = p; }
    int obtenerCuenta(){ return this->cuenta; }
    void cambiarCuenta(int valor) { this->cuenta = valor; }

    friend class ArbolB;
};
#endif //ARBOLB_ARBOLB_H
//class nodoAdministrador {
///*
//Clase creadora de nodos de pasillo para ser
//usados en listas. Clase amiga de listaDCpas,
//listaSimple y nodoCarrito
//*/
//   public:
//    nodoPasillo(string codPas, string nom)
//    {
//        codPasillo=codPas;
//        nombre=nom;
//        pasvis=0;
//        siguiente = NULL;
//        anterior=NULL;
//        subsiguiente=NULL;
//    }
//    nodoPasillo(string codPas, string nom, nodoPasillo * signodo)
//    {
//        codPasillo=codPas;
//        nombre=nom;
//        pasvis=0;
//        siguiente = signodo;
//    }
//   private:
//    string ID;
//    string nombre;
//    nodoPasillo *siguiente;
//    nodoPasillo *anterior;
//   friend class nodoAdministrador;
//};
typedef nodoCliente *tipoClave;
class ArbolB
{
protected:
    int orden;
    Pagina *raiz;

private:
    Pagina *insertar(Pagina *raiz, tipoClave cl);
    bool empujar(Pagina *actual, tipoClave cl, tipoClave &mediana, Pagina *&nuevo);
    void meterPagina(Pagina *actual, tipoClave cl, Pagina *ramaDr, int k);

public:
    ArbolB()
    {
        this->orden = 0;
        this->raiz = NULL;
    }
    explicit ArbolB(int m)
    {
        this->orden = m;
        this->raiz = NULL;
    }
    bool arbolVacio() { return this->raiz == NULL; }
    Pagina *obtenerRaiz() { return raiz; }
    void cambiarRaiz(Pagina *r) { raiz = r; }
    int obtenerOrden() { return orden; }
    void cambiarOrden(int ord) { orden = ord; }

    Pagina *buscar(tipoClave cl, int &n);
    Pagina *buscar(Pagina *actual, tipoClave cl, int &n);

    bool buscarNodo(Pagina *actual, tipoClave cl, int &k);
    void dividirNodo(Pagina *actual, tipoClave &mediana, Pagina *&nuevo, int pos);

    void escribir();
    void escribir(Pagina *r, int h);

    void listaCreciente();
    void inOrden(Pagina *r);

    void insertar(tipoClave cl);

    ArbolB agregarClientes();
};

