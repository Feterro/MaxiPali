#ifndef ARBOLINVENTARIO_H
#define ARBOLINVENTARIO_H
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "nodos.h"

using namespace std;

class ArbolInventario{
public:
    nodoInventario *raiz;
	ArbolInventario() { raiz = NULL; }
    InordenR(pnodoInventario ra);
    pnodoInventario insertar(int codArb,string codPas, string nom, string codPro, string codMar, int cantStk, bool canasta, pnodoInventario aux);
    pnodoInventario giro(pnodoInventario aux);
    pnodoInventario reparto(pnodoInventario aux);
    pnodoInventario rotarDerecha(pnodoInventario aux);
    pnodoInventario rotarIzquierda(pnodoInventario aux);
    void Inorden(pnodoInventario ra);
    ArbolInventario agregarInventario();
};
#endif // ARBOLINVENTARIO_H
