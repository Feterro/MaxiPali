#include "arbolb.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
using namespace std;
void ArbolB::insertar(tipoClave cl)
{
    raiz = insertar(raiz, cl);
}
Pagina* ArbolB::insertar(Pagina *r, tipoClave cl)
{
    bool subeArriba;
    tipoClave mediana;
    Pagina *nd;
    subeArriba = empujar(r, cl,  mediana, nd);
    // El arbol crece de nivel y se inserta la clave mediana
    if(subeArriba)
    {
        Pagina *p;
        p = new Pagina(orden);
        p->cambiarCuenta(1);
        p->cambiarClave(1, mediana);
        // Claves menores
        p->cambiarRamas(0, r);
        // Claves mayores
        p->cambiarRamas(1, nd);
        r = p;
    }
    return r;
}

bool ArbolB::empujar(Pagina *actual, tipoClave cl, tipoClave &mediana, Pagina *&nuevo)
{
    int k;
    bool subeArriba = false;
    // Llego a una pagina nula
    if(actual == NULL)
    {
        cout<<"if"<<endl;
        // Se devuelve hacia la pagina padre
        subeArriba = true;
        mediana = cl; //medoana = nodo
        nuevo = NULL;
    }
    else
    {
        cout<<"else"<<endl;
        bool esta;
        esta = buscarNodo(actual, cl, k);
        if (esta) {
            throw "\nClave duplicada";
        }
        subeArriba = empujar(actual->obtenerRama(k), cl, mediana, nuevo);
        cout<<"sube arriba "<<subeArriba<<endl;
        if (subeArriba) {
            if (!actual->nodoLleno()){
                cout<<"no lleno"<<endl;
                subeArriba = false;
                meterPagina(actual, mediana, nuevo, k);
            } else {
                cout<<"lleno"<<endl;
                subeArriba = true;
                dividirNodo(actual, mediana, nuevo, k);
            }
        }
    }
    cout<<"llega"<<endl;
    return subeArriba;
}
/**
 * Revisa si la clave se encuentra en el arbol
 * @param actual La pagina actual
 * @param cl La clave que se busca
 * @param k La posicion de la pagina
 * @return verdadero si se encuentra la clave
 */
bool ArbolB::buscarNodo(Pagina *actual, tipoClave cl, int &k)
{
    int index;
    bool encontrado;
    // Revisar si la clave esta en la pagina
    if(cl->cedula<actual->obtenerClave(1)->cedula)
    {
        encontrado = false;
        index = 0;
    }
    else
    {
        // Llegar a la posicion que debe tener la clave
        index = actual->obtenerCuenta();
        while(cl->cedula < actual->obtenerClave(index)->cedula && index > 1)
        {
            index--;
        }
        // Revisar si la clave existe
        encontrado = cl->cedula == actual->obtenerClave(index)->cedula;
    }
    k = index;
    return encontrado;
}

/**
 * Baja por las ramas del arbol hasta encontrar la clave
 * @param cl La clave que se desea buscar
 * @param n
 * @return La referencia al nodo donde se encuentra la clave
 */
Pagina* ArbolB::buscar(tipoClave cl, int &n)
{
    return buscar(this->raiz, cl, n);
}

/**
 * Recorre todos los nodos en busca de las claves
 * @param actual
 * @param cl
 * @param n
 * @return
 */
Pagina* ArbolB::buscar(Pagina *actual, tipoClave cl, int &n)
{
    // Parada de la funcion recursiva
    if(actual == NULL)
    {
        return NULL;
    }
    else
    {
        // Verificar si existe dentro del nodo
        bool esta = buscarNodo(actual, cl, n);
        if (esta)
            return actual;
        else
            return buscar(actual->obtenerRama(n), cl, n);
    }
}

void ArbolB::meterPagina(Pagina *actual, tipoClave cl, Pagina *ramaDr, int k)
{
    // Desplazar elementos a la derecha
    for(int i = actual->obtenerCuenta(); i >= k + 1; i--)
    {
        actual->cambiarClave(i + 1, actual->obtenerClave(i));
        actual->cambiarRamas(i + 1, actual->obtenerRama(i));
    }
    // Pone la clave y la rama derecha en la posicion k + 1
    actual->cambiarClave(k + 1, cl);
    actual->cambiarRamas(k + 1, ramaDr);
    // Incrementa el numero de claves
    actual->cambiarCuenta(actual->obtenerCuenta() + 1);
}

void ArbolB::dividirNodo(Pagina *actual, tipoClave &mediana, Pagina *&nuevo, int pos)
{
    int i, posMdna, k;
    Pagina *nuevaPag;
    k = pos;
    // Posicion de la clave mediana
    posMdna = (k <= orden / 2) ? orden / 2 : orden / 2 + 1;
    nuevaPag = new Pagina(orden);
    for(i = posMdna + 1; i < orden; i++)
    {
        nuevaPag->cambiarClave(i - posMdna, actual->obtenerClave(i));
        nuevaPag->cambiarRamas(i - posMdna, actual->obtenerRama(i));
    }
    nuevaPag->cambiarCuenta((orden - 1) - posMdna);
    actual->cambiarCuenta(posMdna);
    if (k <= orden / 2)
        meterPagina(actual, mediana, nuevo, pos);
    else
    {
        pos = k - posMdna;
        meterPagina(nuevaPag, mediana, nuevo, pos);
    }
    mediana = actual->obtenerClave(actual->obtenerCuenta());
    nuevaPag->cambiarRamas(0, actual->obtenerRama(actual->obtenerCuenta()));
    actual->cambiarCuenta(actual->obtenerCuenta() - 1);
    nuevo = nuevaPag;
}
void ArbolB::escribir()
{
    escribir(raiz, 1);
}
void ArbolB::escribir(Pagina *r, int h)
{
    int i;
    if (r != NULL)
    {
        escribir(r->obtenerRama(0), h + 5);
        for(int i = 1; i <= r->obtenerCuenta() / 2; i++){
            escribir(r->obtenerRama(i), h + 5);
            cout << endl;
        }
        for(i = 1; i <= r->obtenerCuenta(); i++)
        {
            for(int j = 0; j <= h; j++)
            {
                cout << " ";
            }
            cout << r->obtenerClave(i)->cedula <<"~"<< r->obtenerClave(i)->nombre<< endl;
        }
        for(i = r->obtenerCuenta() / 2 + 1; i <= r->obtenerCuenta(); i++)
        {
            this->escribir(r->obtenerRama(i), h + 5);
        }
        cout << endl;
    }
}
void ArbolB::listaCreciente()
{
    inOrden(raiz);
}
void ArbolB::inOrden(Pagina *r)
{
    if(r)
    {
        inOrden(r->obtenerRama(0));
        for (int k = 1; k <= r->obtenerCuenta(); k++)
        {
            cout << r->obtenerClave(k) << " ";
            inOrden(r->obtenerRama(k));
        }
    }
}
ArbolB ArbolB::agregarClientes(){
    ArbolB clientes;
    ifstream archivo;
    string texto;
    archivo.open("Clientes.txt",ios::in);
    if (archivo.fail()){
        cout<<"Error al leer el archivo"<<endl;
    }
    else{
        while(!archivo.eof())
        {
            getline(archivo, texto);
            char cstr[texto.size() + 1];
            strcpy(cstr, texto.c_str());
            char var[]=";";
            char *token = strtok(cstr,var);
            string cedula=token;
            stringstream stringInt(cedula);
            int ced;
            stringInt>>ced;
            token = strtok(NULL,var);
            string nom=token;
            token = strtok(NULL,var);
            string cor=token;
            token = strtok(NULL,var);
            string tel=token;
            nodoCliente *cliente=new nodoCliente(ced, nom, cor, tel);
            clientes.insertar(cliente);
        }
    }
    clientes.escribir();
}
int main() {
    ArbolB arbolb;
    arbolb.agregarClientes();
    return 0;
}




