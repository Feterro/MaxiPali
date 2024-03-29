#ifndef ARBOLPAS_H
#define ARBOLPAS_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "nodos.h"
using namespace std;
class arbolPas {
/*
Clase creadora de listas donde se insertaran
los pasillos. Base de la estructura creada con archivos
*/

   public:
    pnodoPas raiz;
    arbolPas():raiz(NULL){}
   // void PreordenI();
    void InordenI(pnodoPas raiz);
    void InordenTriple(pnodoPas R);
   // void PostordenI();
    bool arbolVacio() { return raiz == NULL; }
    arbolPas ListaBase();
    void InsertaBinario(pnodoPas raiz, string cod, string nombre);
    nodoProducto* busquedaPro(nodoPasillo *nodoPas,nodoMarca* nodMar);
    arbolPas arbolProductos();
    void MostrarPasillos(pnodoPas ra);
    bool encontrarPasillo(bool encontrado,pnodoPas ra, string codPas);
    void MostrarProductos(pnodoPas r, string codPas);
    bool ValidarProducto1(pnodoPas ra, string codPas, string codProd, bool valido);
    void MostrarMarcas(pnodoPas R, string codPas, string codProd);
    bool validarMarca(pnodoPas ra, string codPas, string codProd, string codMar, bool valido);
    pnodoMarca encontrarNodo1(pnodoPas ra, string codPas, string codProd, string codMar, pnodoMarca marca);
};
#endif // ARBOLPAS_H
