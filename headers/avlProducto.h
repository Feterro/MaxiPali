#ifndef AVLPRODUCTOS_H
#define AVLPRODUCTOS_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "nodos.h"
using namespace std;
class AVLProducto{
public:
    pnodoProd raiz;
    AVLProducto():raiz(NULL){}
    bool Hh;
    void InordenR(pnodoProd raiz);
    void InsertarBalanceado(nodoProducto *r, nodoProducto *r2, bool Hh, string codPas, string codProd, string nomProd);
    void RotacionDobleIzquierda(nodoProducto *n1, nodoProducto *n2);
    void RotacionDobleDerecha(nodoProducto *n1, nodoProducto *n2);
    void RotacionSimpleIzquierda(nodoProducto *n1, nodoProducto *n2);
    void RotacionSimpleDerecha(nodoProducto *n1, nodoProducto *n2);
    void EnlaceAvl(nodoPasillo *nodoPas,nodoProducto *nodoPro);
    void InordenPro(pnodoProd R);
    void EnlaceRN(nodoProducto *nodoPro, nodoMarca *nodoMar);
    void MostrarProductos(pnodoProd ra);
    bool validarProducto2(pnodoProd ra,string codPas, string codProd, bool valido);
    void MostrarMarcas2(pnodoProd ra, string codProd);
    bool validarMarcas2(pnodoProd ra,string codProd, string codMar, bool valido);
    pnodoMarca encontrarNodo2(pnodoProd ra, string codProd, string codMar, pnodoMarca marca);

    friend class lista;
};
#endif // AVLPRODUCTOS_H
