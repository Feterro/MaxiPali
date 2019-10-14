#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
#include "headers/rojinegro.h"
#include "headers/lista.h"
#include "headers/ciudades.h"
#include "headers/avlProducto.h"
#include "headers/arbolPas.h"
#include "headers/arbolInventario.h"
#include "headers/arbolb.h"
#include "headers/Principal.h"
using namespace std;
/*
Metodos simples de insertar, mostrar ect
*/
//Ciudad:
void Ciudad::Mostrar()
{
    nodoCiudad *aux;
    if (primero== NULL)
        cout << "No hay elementos";
    else
    {
        aux = primero;
		while(aux)
		{
		    cout << aux->codigo<<" || "<<aux->nombre<< "-> ";
		    aux = aux->siguiente;
		}
		cout << endl;
   }
}
int Ciudad::largoCiudad(){
    int cont=0;
    pnodoCiudad aux;
    aux = primero;
    if(listaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }

}
void Ciudad::InsertarFinal(int cod, string nom)
{
    if (listaVacia())
        primero = new nodoCiudad(cod, nom);
    else
        { pnodoCiudad aux = primero;
            while ( aux->siguiente != NULL)
                aux= aux->siguiente;
                aux->siguiente=new nodoCiudad(cod, nom);
        }
}
//Marcas
pnodoMarca RN::insertarNodo(pnodoMarca raiz, pnodoMarca pt){
	if (raiz == NULL)
        return pt;
    int codRaiz;
    stringstream codtrans(raiz->codMarca);
    codtrans>>codRaiz;
    int codIns;
    stringstream codtrans2(pt->codMarca);
    codtrans2>>codIns;
	if (codIns<codRaiz)
	{
		raiz->hIzq = insertarNodo(raiz->hIzq, pt);
		raiz->hIzq->padre = raiz;
	}
	else if (codIns > codRaiz)
	{
		raiz->hDer = insertarNodo(raiz->hDer, pt);
		raiz->hDer->padre = raiz;
	}
	else {
        return pt;
    }
	return raiz;
}
void RN::rotarIzquierda(nodoMarca *&raiz, nodoMarca *&pt)
{
	pnodoMarca pt_hDer = pt->hDer;

	pt->hDer = pt_hDer->hIzq;

	if (pt->hDer != NULL)
		pt->hDer->padre = pt;

	pt_hDer->padre = pt->padre;

	if (pt->padre == NULL)
		raiz = pt_hDer;

	else if (pt == pt->padre->hIzq)
		pt->padre->hIzq = pt_hDer;

	else
		pt->padre->hDer = pt_hDer;

	pt_hDer->hIzq = pt;
	pt->padre = pt_hDer;
}
void RN::rotarDerecha(nodoMarca *&raiz, nodoMarca *&pt)
{
	pnodoMarca pt_hIzq = pt->hIzq;

	pt->hIzq = pt_hIzq->hDer;

	if (pt->hIzq != NULL)
		pt->hIzq->padre = pt;

	pt_hIzq->padre = pt->padre;

	if (pt->padre == NULL)
		raiz = pt_hIzq;

	else if (pt == pt->padre->hIzq)
		pt->padre->hIzq = pt_hIzq;

	else
		pt->padre->hDer = pt_hIzq;

	pt_hIzq->hDer = pt;
	pt->padre = pt_hIzq;
}
void RN::balancearArbol(nodoMarca *&raiz, nodoMarca *&pt)
{
	pnodoMarca padre_pt = NULL;
	pnodoMarca abuelo_pt = NULL;

	while ((pt != raiz) && (pt->color != NEGRO) &&
		(pt->padre->color == ROJO))
	{

		padre_pt = pt->padre;
		abuelo_pt = pt->padre->padre;
		if (padre_pt == abuelo_pt->hIzq)
		{
			pnodoMarca tio_pt = abuelo_pt->hDer;
			if (tio_pt != NULL && tio_pt->color == ROJO)
			{
				abuelo_pt->color = ROJO;
				padre_pt->color = NEGRO;
				tio_pt->color = NEGRO;
				pt = abuelo_pt;
			}
			else
			{
				if (pt == padre_pt->hDer)
				{
					rotarIzquierda(raiz, padre_pt);
					pt = padre_pt;
					padre_pt = pt->padre;
				}
				rotarDerecha(raiz, abuelo_pt);
				swap(padre_pt->color, abuelo_pt->color);
				pt = padre_pt;
			}
		}
		else
		{
			pnodoMarca tio_pt = abuelo_pt->hIzq;
			if ((tio_pt != NULL) && (tio_pt->color == ROJO))
			{
				abuelo_pt->color = ROJO;
				padre_pt->color = NEGRO;
				tio_pt->color = NEGRO;
				pt = abuelo_pt;
			}
			else
			{
				if (pt == padre_pt->hIzq)
				{
					rotarDerecha(raiz, padre_pt);
					pt = padre_pt;
					padre_pt = pt->padre;
				}
				rotarIzquierda(raiz, abuelo_pt);
				swap(padre_pt->color, abuelo_pt->color);
				pt = padre_pt;
			}
		}
	}

	raiz->color = NEGRO;
}
void RN::insert(const string &codPasilo,const string &nombre,const string &codProducto,const string &codMar,const int &gon, const float &val)
{
	pnodoMarca pt = new nodoMarca(codPasilo,nombre,codProducto,codMar,gon,val);
	raiz = insertarNodo(raiz, pt);
	balancearArbol(raiz, pt);
}
void RN:: InordenMar(pnodoMarca R){
 if(R==NULL){
        return;
    }else{
        InordenMar(R->hIzq);
        cout<<R->codPasillo<<"~"<<R->codProducto<<"~"<<R->codMarca<<"~"<<R->nombre<<"~"<<R->cantGondola<<"~"<<R->precio<<"/";
        InordenMar(R->hDer);
    }
}
//Listas para codigos repetidos
int lista::largoLista(){
    int cont=0;

    pnodoProd aux;
    aux = primero;
    if(ListaVacia()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }

}
int lista::largoListaMar(){
    int cont=0;

    pnodoMarca aux;
    aux = primeroMar;
    if(ListaVaciaMar()){
        return cont;
    }else{
        while(aux!=NULL){
        aux=aux->siguiente;
        cont++;
    }
    return cont;
    }
}
void lista::InsertarFinal(string codPas, string codPro, string nom)
{
   if (ListaVacia())
     primero = new nodoProducto(codPas,codPro,nom);
   else
     { pnodoProd aux = primero;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodoProducto(codPas,codPro,nom);
      }
}
void lista::InsertarFinalMar(string codPas, string nom, string codPro, string codMar,int cantGon,float precio)
{
   if (ListaVaciaMar())
     primeroMar = new nodoMarca(codPas, nom, codPro, codMar, cantGon, precio);
   else
     { pnodoMarca aux = primeroMar;
        while ( aux->siguiente != NULL)
          aux= aux->siguiente;
        aux->siguiente=new nodoMarca(codPas, nom, codPro, codMar, cantGon, precio);
      }
}
void lista::Mostrar()
{
   nodoProducto *aux;
   if (primero== NULL)
       cout << "No hay elementos";
   else
   {


   		aux = primero;
		while(aux)
		{
		    cout <<aux->codPasillo<<"~"<<aux->codProducto<<"~"<<aux->nombre<< "-> ";
		    aux = aux->siguiente;
		}
		cout << endl;
   }
}
void lista::MostrarMar()
{
   nodoMarca *R;
   if (primeroMar== NULL)
       cout << "No hay elementos";
   else
   {
   		R = primeroMar;
		while(R)
		{
		    cout<<R->codPasillo<<"~"<<R->codProducto<<"~"<<R->codMarca<<"~"<<R->nombre<<"~"<<R->cantGondola<<"~"<<R->precio<< "-> ";
		    R = R->siguiente;
		}
		cout << endl;
   }
}
//Pasillos
void arbolPas::InordenI(pnodoPas R){
    if(R==NULL){
        return;
    }else{
        InordenI(R->hIzq);
        cout<<R->codPasillo<<"~"<<R->nombre<<"||";
        InordenI(R->hDer);
    }
}
void arbolPas::InsertaBinario(pnodoPas aux,string cod, string nombre)
{
    stringstream codi(cod);
    int valor;
    codi>>valor;
    if (arbolVacio()){
        raiz=new nodoPasillo(cod, nombre);
    }
    else{
        stringstream codRa(aux->codPasillo);
        int valRa;
        codRa>>valRa;
        if(valor<valRa){
            if(aux->hIzq==NULL){
                aux-> hIzq = new nodoPasillo(cod, nombre);
            }else{
                InsertaBinario(aux->hIzq,cod, nombre);
            }
        }else if(valor>valRa){
            if(aux->hDer==NULL){
                aux->hDer = new nodoPasillo(cod,nombre);
            }else{
                InsertaBinario(aux->hDer,cod, nombre);
            }
        }
    }
}
arbolPas arbolPas::ListaBase()
{
/*
Metodo que crea la lista de pasillos a
partir de archivos
*/

    arbolPas pasillos;
    ifstream archivo;
    string texto;
    archivo.open("Pasillos.txt",ios::in);
    while(!archivo.eof())
    {
        getline(archivo, texto);
        char cstr[texto.size() + 1];
        strcpy(cstr, texto.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        string cod=token;
        token = strtok(NULL,var);
        string nom=token;
        bool rep=false;;
        pasillos.InsertaBinario(pasillos.raiz,cod, nom);
    }
    archivo.close();
    return pasillos;
}
void arbolPas::InordenTriple(pnodoPas R){
    if(R==NULL){
        return;
    }else{
        InordenTriple(R->hIzq);
        cout<<"||"<<R->codPasillo<<"~"<<R->nombre;
        AVLProducto pro;
        pro.raiz=R->subsiguiente;
        pro.InordenPro(R->subsiguiente);
        InordenTriple(R->hDer);
    }
}
//Productos
void AVLProducto::InsertarBalanceado(nodoProducto *aux, nodoProducto *ra, bool Hh, string codPas, string codProd, string nomProd){
    pnodoProd n1;
    stringstream cp(codProd);
    int codProdu;
    cp>>codProdu;
    int codProduAux;
    if(aux!=NULL){
        stringstream cpa(aux->codProducto);
        cpa>>codProduAux;
    }
    else{
        stringstream cpa(ra->codProducto);
        cpa>>codProduAux;
    }
    if(raiz==NULL){
        raiz=new nodoProducto(codPas,codProd,nomProd);
        Hh = true;
        return;
    }
    else if(aux==NULL&&raiz!=NULL){
        if(codProdu<codProduAux)
            ra->hIzq=new nodoProducto(codPas,codProd,nomProd);
        else if(codProdu>codProduAux)
            ra->hDer=new nodoProducto(codPas,codProd,nomProd);
        //cout<<raiz->hDer->hDer<<endl;
        //cout<<"Otros: "<<->valor<<endl;
        Hh = true;
    }else{
        //cout<<"q as2"<<endl;
        if(codProdu<codProduAux){
            InsertarBalanceado(aux->hIzq,aux, Hh,codPas,codProd,nomProd);

        if(Hh){
            switch(aux->FB){
                case 1: aux->FB=0;
                Hh = false;
                break;
                case 0: aux->FB  = -1;
                break;
                case -1: n1=aux->hIzq;
                if(n1->FB==-1){
                    RotacionSimpleIzquierda(aux, n1);
                    if(aux->codProducto==raiz->codProducto)
                        raiz=n1;
                }else{
                    RotacionDobleIzquierda(aux,n1);
                    if(aux->codProducto==raiz->codProducto)
                        raiz=n1;
                }
                Hh = false;
                break;
            }
        }
        }else{
            if(codProdu>codProduAux){
            InsertarBalanceado(aux->hDer,aux, Hh,codPas,codProd,nomProd);
                if(Hh){
                    switch(aux->FB){
                        case -1: aux->FB=0;
                        Hh = false;
                        break;
                        case 0: aux->FB=1;
                        break;
                        case 1:n1=aux->hDer;
                        if(n1->FB==1){
                            RotacionSimpleDerecha(aux, n1);
                            if(aux->codProducto==raiz->codProducto)
                                raiz=n1;
                        }else{
                            RotacionDobleDerecha(aux, n1);
                            if(aux->codProducto==raiz->codProducto)
                                raiz=n1;
                        }
                        Hh=false;
                        break;
                    }
                }
            }
        }
    }
}
void AVLProducto::RotacionDobleIzquierda(nodoProducto* n, nodoProducto* n1){
    nodoProducto *n2;
    n2=n1->hDer;
    n->hIzq = n2->hDer;
    n2->hDer=n;
    n1->hDer=n2->hIzq;
    n2->hIzq=n1;

    if(n2->FB==1){
        n1->FB=-1;
    }else{
        n1->FB=0;
    }
    if(n2->FB==-1){
        n->FB=1;
    }else{
        n->FB=0;
    }
    n2->FB=0;
    n=n2;
}
void AVLProducto::RotacionDobleDerecha(nodoProducto* n, nodoProducto* n1){
    nodoProducto *n2;
    n2=n1->hIzq;
    n->hDer = n2->hIzq;
    n2->hIzq=n;
    n1->hIzq=n2->hDer;
    n2->hDer=n1;

    if(n2->FB==1){
        n->FB=-1;
    }else{
        n->FB=0;
    }
    if(n2->FB==-1){
        n1->FB=1;
    }else{
        n1->FB=0;
    }
    n2->FB=0;
    n=n2;
}
void AVLProducto::RotacionSimpleDerecha(nodoProducto* n, nodoProducto* n1){
    n->hDer=n1->hIzq;
    n1->hIzq=n;

    if(n1->FB==1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=1;
        n1->FB=-1;
    }
    n=n1;
}
void AVLProducto::RotacionSimpleIzquierda(nodoProducto* n, nodoProducto* n1){
    n->hIzq=n1->hDer;
    n1->hDer=n;

    if(n1->FB==-1){
        n->FB=0;
        n1->FB=0;
    }else{
        n->FB=-1;
        n1->FB=-1;
    }
    n=n1;
}
void AVLProducto::InordenPro(pnodoProd R){
    if(R==NULL){
        return;
    }else{
        InordenPro(R->hIzq);
        cout<<"|||"<<R->codPasillo<<"~"<<R->codProducto<<R->nombre<<"||||";
        RN mar;
        mar.raiz=R->subsiguiente;
        mar.InordenMar(R->subsiguiente);
        InordenPro(R->hDer);
    }
}
//Inventario
pnodoInventario ArbolInventario::insertar(int conca, string codPas, string nom, string codPro, string codMar, int cantStk, bool canasta, pnodoInventario aux)
{
    if (aux==NULL){
        aux=new nodoInventario(codPas, nom, codPro, codMar, cantStk, canasta);
    }
    else if (conca<aux->codArbol){
        aux->hIzq=insertar(conca,codPas, nom, codPro, codMar, cantStk, canasta, aux->hIzq);
    }
    else if (conca>aux->codArbol){
        aux->hDer=insertar(conca,codPas, nom, codPro, codMar, cantStk, canasta, aux->hDer);
    }
    else {
        cout<<"Repetido"<<endl;
        return aux;
    }
    aux=giro(aux);
    aux=reparto(aux);
    return aux;
}
pnodoInventario ArbolInventario::giro( pnodoInventario aux )
{
    if (aux->hIzq==NULL){
        return aux;
    }
    if(aux->hIzq->nivel == aux->nivel ){
        aux= rotarIzquierda( aux );
    }
    return aux;
}
pnodoInventario ArbolInventario::reparto(pnodoInventario aux)
{
    if (aux->hDer==NULL){
        return aux;
    }
    if( aux->hDer->nivel == aux->nivel && aux->hDer->hDer!=NULL && aux->hDer->hDer->nivel==aux->nivel)
    {
        aux= rotarDerecha(aux);
        aux->nivel++;
    }
    return aux;
}
pnodoInventario ArbolInventario::rotarIzquierda(pnodoInventario aux)
{
    pnodoInventario otro=aux->hIzq;
    aux->hIzq = otro->hDer;
    otro->hDer= aux;
    return otro;
}
/**
* Rotate binary tree node with right child.
* For AVL trees, this is a single rotation for case 4.
*/
pnodoInventario ArbolInventario::rotarDerecha(pnodoInventario aux)
{
    pnodoInventario otro = aux->hDer;
    aux->hDer= otro->hIzq;
    otro->hIzq=aux;
    return otro;
}
//Crear Estructuras
lista lista::enlistarCodigos(){
    lista listaAlm;
    ifstream archivo;
    string texto;
    archivo.open("ProductosPasillos.txt",ios::in);
    while(!archivo.eof())
    {
        //cout<<"ciclo"<<endl;
        getline(archivo, texto);
        char cstr[texto.size() + 1];
        strcpy(cstr, texto.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        string codPas=token;
        token = strtok(NULL,var);
        string codPro=token;
        token = strtok(NULL,var);
        string nom=token;
        bool rep=false;
        if(!listaAlm.ListaVacia())
        {
           //cout<<"siay nada"<<endl;
            pnodoProd aux=listaAlm.primero;
            for(int i=0; i<listaAlm.largoLista(); i++)
            {
                //cout<<"vuelto loko prro"<<codPro<<" "<<aux->codProducto<<endl;
                if(aux->codProducto==codPro){
                    rep=true;
                    //cout<<"cmamo"<<endl;
                }
                aux=aux->siguiente;
            }
            if(rep==false)
                listaAlm.InsertarFinal(codPas,codPro,nom);
        }
        else{
          //cout<<"nuai nada"<<endl;
          listaAlm.InsertarFinal(codPas,codPro,nom);
        }
    }
    //listaAlm.Mostrar();
    return listaAlm;
}
void AVLProducto::EnlaceAvl(nodoPasillo *nodoPas,nodoProducto *nodoPro){
    if(nodoPas==NULL){
        return;
    }else{
        EnlaceAvl(nodoPas->hIzq, nodoPro);
        if(nodoPas->codPasillo==nodoPro->codPasillo)
        {
        	if(nodoPas->subsiguiente==NULL){
        		nodoPas->subsiguiente=nodoPro;
        	}
        	else{
                AVLProducto ArbolEnla;
                ArbolEnla.raiz=nodoPas->subsiguiente;
                ArbolEnla.InsertarBalanceado(ArbolEnla.raiz, ArbolEnla.raiz, false,nodoPro->codPasillo,nodoPro->codProducto,nodoPro->nombre);
        	}
		}
        EnlaceAvl(nodoPas->hDer, nodoPro);
    }
}
arbolPas arbolPas::arbolProductos(){
    AVLProducto arbolProd;
	lista listaCod;
	listaCod=listaCod.enlistarCodigos();
	arbolPas arbolPasillo;
	arbolPasillo=arbolPasillo.ListaBase();
	pnodoProd aux=listaCod.primero;
	for(int i=0; i<listaCod.largoLista();i++)
    {
        arbolProd.EnlaceAvl(arbolPasillo.raiz, aux);
        aux=aux->siguiente;
    }
    return arbolPasillo;
}
lista lista::enlistarCodigosMar(){
    lista listaAlm;
    ifstream archivo;
    string texto;
    archivo.open("MarcasProductos.txt",ios::in);
    while(!archivo.eof())
    {
        getline(archivo, texto);
        char cstr[texto.size() + 1];
        strcpy(cstr, texto.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        string codPas=token;
        token = strtok(NULL,var);
        string codPro=token;
        token = strtok(NULL,var);
        string codMar=token;
        token = strtok(NULL,var);
        string nom=token;
        token = strtok(NULL,var);
        string cantGondIni=token;
        stringstream cantconv(cantGondIni);
        int cantGond;
        cantconv>>cantGond;
        token = strtok(NULL,var);
        string precioIni=token;
        stringstream preconv(precioIni);
        int precio;
        preconv>>precio;
        bool rep=false;
        if(!listaAlm.ListaVacia())
        {
           //cout<<"siay nada"<<endl;
            pnodoMarca aux=listaAlm.primeroMar;
            for(int i=0; i<listaAlm.largoListaMar(); i++)
            {
                //cout<<"vuelto loko prro"<<codPro<<" "<<aux->codProducto<<endl;
                if(aux->codMarca==codMar){
                    rep=true;
                    //cout<<"cmamo"<<endl;
                }
                aux=aux->siguiente;
            }
            if(rep==false)
                listaAlm.InsertarFinalMar(codPas,nom,codPro,codMar,cantGond,precio);
        }
        else{
          //cout<<"nuai nada"<<endl;
          listaAlm.InsertarFinalMar(codPas,nom,codPro,codMar,cantGond,precio);
        }
    }
    //listaAlm.MostrarMar();
    return listaAlm;
}
void AVLProducto::EnlaceRN(nodoProducto *nodoPro, nodoMarca *nodoMar){
    if(nodoPro==NULL){
        return;
    }else{
        EnlaceRN(nodoPro->hIzq, nodoMar);
        if(nodoPro->codProducto==nodoMar->codProducto)
        {
            //cout<<nodoPro->codProducto<<nodoMar->codProducto<<endl;
        	if(nodoPro->subsiguiente==NULL){
                RN ArbolEnla;
                ArbolEnla.raiz=nodoPro->subsiguiente;
                ArbolEnla.insert(nodoMar->codPasillo,nodoMar->nombre,nodoMar->codProducto,nodoMar->codMarca,nodoMar->cantGondola,nodoMar->precio);
                nodoPro->subsiguiente=ArbolEnla.raiz;

        	}
        	else{
                RN ArbolEnla;
                ArbolEnla.raiz=nodoPro->subsiguiente;
                ArbolEnla.insert(nodoMar->codPasillo,nodoMar->nombre,nodoMar->codProducto,nodoMar->codMarca,nodoMar->cantGondola,nodoMar->precio);
                nodoPro->subsiguiente=ArbolEnla.raiz;
        	}
		}
        EnlaceRN(nodoPro->hDer, nodoMar);
    }
}
nodoProducto* arbolPas::busquedaPro(nodoPasillo *nodoPas,nodoMarca* nodoMar){
    if(nodoPas==NULL){
    }else{
        busquedaPro(nodoPas->hIzq, nodoMar);
        if(nodoPas->codPasillo==nodoMar->codPasillo)
        {
        	if(nodoPas->subsiguiente==NULL){
        	}
        	else{
                AVLProducto arbol;
                arbol.raiz=nodoPas->subsiguiente;
        	    arbol.EnlaceRN(nodoPas->subsiguiente,nodoMar);
        	}
		}
        busquedaPro(nodoPas->hDer, nodoMar);
    }
}
arbolPas RN::arbolMarcas(){
	lista listaCod;
	listaCod=listaCod.enlistarCodigosMar();
	arbolPas arbolPasillo;
	arbolPasillo=arbolPasillo.arbolProductos();
	pnodoMarca aux=listaCod.primeroMar;
	for(int i=0; i<listaCod.largoListaMar();i++)
    {
       pnodoProd encont=arbolPasillo.busquedaPro(arbolPasillo.raiz, aux);
       aux=aux->siguiente;
    }
    arbolPasillo.InordenTriple(arbolPasillo.raiz);
    return arbolPasillo;
}
Ciudad Ciudad::agregarCiudades(){
    Ciudad listaCiudades;
    ifstream archivo;
    string ciudad;
    archivo.open("Ciudades.txt", ios::in);
    if (archivo.fail()){
        cout<<"Error al leer el archivo"<<endl;
    }
    else{
        while(!archivo.eof())
        {
            getline(archivo, ciudad);
            char cstr[ciudad.size()+1];
            strcpy(cstr, ciudad.c_str());
            char *frase=cstr;
            char *aux;
            aux=strtok(frase,";");
            string cod;
            stringstream codStr;
            codStr<<aux;
            codStr>>cod;
            stringstream stringInt(cod);
            int codI;
            stringInt>>codI;
            aux=strtok(NULL, ";");
            string nom=aux;
            if (listaCiudades.listaVacia()){
                listaCiudades.InsertarFinal(codI, nom);
            }
            bool agregar=agregarCiudad(listaCiudades, codI);
            if(agregar){
                listaCiudades.InsertarFinal(codI, nom);
            }
        }
    }
    listaCiudades.Mostrar();
    return listaCiudades;
}
bool Ciudad::agregarCiudad(Ciudad lista, int cod){
    pnodoCiudad aux=lista.primero;
    while (aux!=NULL){
        if(aux->codigo==cod)
            return false;
        aux=aux->siguiente;
    }
    return true;
}
void ArbolInventario::Inorden(pnodoInventario R){
 if(R==NULL){
        return;
    }else{
        Inorden(R->hIzq);
        cout<<R->codArbol<<" ** "<<R->nivel<<"->";
        Inorden(R->hDer);
    }
}
ArbolInventario ArbolInventario::agregarInventario(){
    ArbolInventario inventario;
    ifstream archivo;
    string texto;
    archivo.open("Inventario.txt",ios::in);
    while(!archivo.eof())
    {
        getline(archivo, texto);
        char cstr[texto.size() + 1];
        strcpy(cstr, texto.c_str());
        char var[]=";";
        char *token = strtok(cstr,var);
        string codPas=token;
        token = strtok(NULL,var);
        string codPro=token;
        token = strtok(NULL,var);
        string codMar=token;
        token = strtok(NULL,var);
        string nom=token;
        token = strtok(NULL,var);
        string cantStkIni=token;
        stringstream cantconv(cantStkIni);
        int cantStk;
        cantconv>>cantStk;
        token = strtok(NULL,var);
        string decbool=token;
        bool canasta;
        if(decbool=="1")
            canasta=true;
        else
            canasta=false;
        string conc=codPas+codPro+codMar;
        stringstream codTrans(conc);
        int codArbol;
        codTrans>>codArbol;
        inventario.raiz=insertar(codArbol,codPas, nom, codPro, codMar, cantStk, canasta, inventario.raiz);
    }
    archivo.close();
    cout<<"Inorden: "<<endl;
    inventario.Inorden(inventario.raiz);
    return inventario;
}
void ArbolB::insertar(tipoClave cl, string nombre, string telefono, string codigoCiudad, string correo)
{
    raiz = insertar(raiz, cl, nombre, telefono, codigoCiudad, correo);
}
Pagina* ArbolB::insertar(Pagina *r, tipoClave cl, string nombre, string telefono, string codigoCiudad, string correo)
{
    bool subeArriba;
    int mediana;
    Pagina *nd;
    subeArriba = empujar(r, cl,  mediana, nd, nombre, telefono, codigoCiudad, correo);
    // El arbol crece de nivel y se inserta la clave mediana
    if(subeArriba)
    {
        Pagina *p;
        p = new Pagina(orden);
        p->cambiarCuenta(1);
        p->cambiarClave(1, mediana);
        p->cambiarDato(1,0,nombre);
        p->cambiarDato(1,1,telefono);
        p->cambiarDato(1,2,codigoCiudad);
        p->cambiarDato(1,3,correo);
        // Claves menores
        p->cambiarRamas(0, r);
        // Claves mayores
        p->cambiarRamas(1, nd);
        r = p;
    }
    return r;
}
bool ArbolB::empujar(Pagina *actual, tipoClave cl, tipoClave &mediana, Pagina *&nuevo, string &nombre, string &telefono, string &codigoCiudad, string &correo)
{
    int k;
    bool subeArriba = false;
    // Llego a una pagina nula
    if(actual == NULL)
    {
        // Se devuelve hacia la pagina padre
        subeArriba = true;
        mediana = cl;
        nuevo = NULL;
    }
    else
    {
        bool esta;
        esta = buscarNodo(actual, cl, k);
        if (esta) {
            throw "\nClave duplicada";
        }
        subeArriba = empujar(actual->obtenerRama(k), cl, mediana, nuevo, nombre, telefono, codigoCiudad, correo);
        if (subeArriba) {
            if (!actual->nodoLleno()) {
                subeArriba = false;
                meterPagina(actual, mediana, nuevo, k, nombre, telefono, codigoCiudad, correo);
            } else {
                subeArriba = true;
                dividirNodo(actual, mediana, nuevo, k, nombre, telefono, codigoCiudad, correo);
            }
        }
    }
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
    if(cl < actual->obtenerClave(1))
    {
        encontrado = false;
        index = 0;
    }
    else
    {
        // Llegar a la posicion que debe tener la clave
        index = actual->obtenerCuenta();
        while(cl < actual->obtenerClave(index) && index > 1)
        {
            index--;
        }
        // Revisar si la clave existe
        encontrado = cl == actual->obtenerClave(index);
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
    if(actual == nullptr)
    {
        return nullptr;
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
void ArbolB::meterPagina(Pagina *actual, tipoClave cl, Pagina *ramaDr, int k, string nombre, string telefono, string codigoCiudad, string correo)
{
    // Desplazar elementos a la derecha
    for(int i = actual->obtenerCuenta(); i >= k + 1; i--)
    {
        actual->cambiarClave(i + 1, actual->obtenerClave(i));
        actual->cambiarDato(i+1 , 0 , actual->obtenerDato(i,0));
        actual->cambiarDato(i+1 , 1 , actual->obtenerDato(i,1));
        actual->cambiarDato(i+1 , 2 , actual->obtenerDato(i,2));
        actual->cambiarDato(i+1 , 3 , actual->obtenerDato(i,3));
        actual->cambiarRamas(i + 1, actual->obtenerRama(i));
    }
    // Pone la clave y la rama derecha en la posicion k + 1
    actual->cambiarClave(k + 1, cl);
    actual->cambiarDato(k+1,0,nombre);
    actual->cambiarDato(k+1,1,telefono);
    actual->cambiarDato(k+1,2,codigoCiudad);
    actual->cambiarDato(k+1,3,correo);
    actual->cambiarRamas(k + 1, ramaDr);
    // Incrementa el numero de claves
    actual->cambiarCuenta(actual->obtenerCuenta() + 1);
}
void ArbolB::dividirNodo(Pagina *actual, tipoClave &mediana, Pagina *&nuevo, int pos, string &nombre, string &telefono, string &codigoCiudad, string &correo)
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
        nuevaPag->cambiarDato(i - posMdna , 0 , actual->obtenerDato(i,0));
        nuevaPag->cambiarDato(i - posMdna , 1 , actual->obtenerDato(i,1));
        nuevaPag->cambiarDato(i - posMdna , 2 , actual->obtenerDato(i,2));
        nuevaPag->cambiarDato(i - posMdna , 3 , actual->obtenerDato(i,3));
    }
    nuevaPag->cambiarCuenta((orden - 1) - posMdna);
    actual->cambiarCuenta(posMdna);
    if (k <= orden / 2)
        meterPagina(actual, mediana, nuevo, pos, nombre, telefono, codigoCiudad, correo);
    else
    {
        pos = k - posMdna;
        meterPagina(nuevaPag, mediana, nuevo, pos, nombre, telefono, codigoCiudad, correo);
    }
    mediana = actual->obtenerClave(actual->obtenerCuenta());
    nombre = actual->obtenerDato(actual->obtenerCuenta(),0);
    telefono = actual->obtenerDato(actual->obtenerCuenta(),1);
    codigoCiudad = actual->obtenerDato(actual->obtenerCuenta(),2);
    correo = actual->obtenerDato(actual->obtenerCuenta(),3);
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
            cout << r->obtenerClave(i) <<","<< r->obtenerDato(i,0) << endl;
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
            cout << r->obtenerClave(k) <<","<< r->obtenerDato(k,0) << endl;" - ";
            inOrden(r->obtenerRama(k));
        }
    }
}
void ArbolB::cargarClientes(string pNombreArchivo){
    //ArbolB cliente;
    int n;
    bool repetido;
    int cedula;
    string codigoCiudad;
    string linea;
    string cedulaS;
    string nombre;
    string telefono;
    string correo;
    ifstream archivo (pNombreArchivo);
    while (getline(archivo, linea)){
        istringstream lineaActual (linea);
        getline(lineaActual,cedulaS,';');
        getline(lineaActual,nombre,';');
        getline(lineaActual,codigoCiudad,';');
        getline(lineaActual,telefono,';');
        getline(lineaActual,correo,';');
        cedula = stoi (cedulaS);
        Pagina* aux = buscar(cedula,n);
        if (aux == NULL){
            insertar(cedula,nombre,telefono,codigoCiudad,correo);

        }
    }
    archivo.close();
    //return cliente;
}
void ArbolB::cargarAdmins(string pNombreArchivo){
    int n;
    bool repetido;
    int cedula;
    string linea;
    string cedulaS;
    string nombre;
    ifstream archivo (pNombreArchivo);
    while (getline(archivo, linea)){
        istringstream lineaActual (linea);
        getline(lineaActual,cedulaS,';');
        getline(lineaActual,nombre,';');
        cedula = stoi (cedulaS);
        Pagina* aux = buscar(cedula,n);
        if (aux == NULL){
            insertar(cedula,nombre,"","","");
        }
    }
    archivo.close();
}
//Funcionalidad
//Comprar
void arbolPas::MostrarProductos(pnodoPas R, string codPas){
    if(R==NULL){
        return;
    }else{
        MostrarProductos(R->hIzq, codPas);
        if (R->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=R->subsiguiente;
            pro.MostrarProductos(R->subsiguiente);
        }
        MostrarProductos(R->hDer, codPas);
    }
}
void AVLProducto::MostrarProductos(pnodoProd R){
    if(R==NULL){
        return;
    }else{
        MostrarProductos(R->hIzq);

        cout<<R->nombre<<" "<<R->codProducto<<endl;
        MostrarProductos(R->hDer);
    }
}
void arbolPas::MostrarPasillos(pnodoPas ra){
    if (ra==NULL){
        return;
    }
    else{
        MostrarPasillos(ra->hIzq);
        cout<<ra->nombre<<" "<<ra->codPasillo<<endl;
        MostrarPasillos(ra->hDer);
    }
}
bool arbolPas::encontrarPasillo(bool encontrado, pnodoPas ra, string codPas){
    if (ra==NULL){
    }
    else{
        encontrado=encontrarPasillo(encontrado, ra->hIzq, codPas);
        if (codPas==ra->codPasillo){
            encontrado=true;
        }
        encontrado=encontrarPasillo(encontrado, ra->hDer, codPas);
    }
    return encontrado;

}
bool arbolPas::ValidarProducto1(pnodoPas R, string codPas,string codProd ,bool valido){
    if(R==NULL){
    }else{
        valido=ValidarProducto1(R->hIzq, codPas, codProd, valido);
        if (R->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=R->subsiguiente;
            valido=pro.validarProducto2(R->subsiguiente,codPas, codProd, valido);

        }
        valido=ValidarProducto1(R->hDer, codPas, codProd, valido);
    }
    return valido;
}
bool AVLProducto::validarProducto2(pnodoProd ra,string codPas, string codProd, bool valido){
    if(ra==NULL){
    }else{
        valido=validarProducto2(ra->hIzq, codPas, codProd, valido);
        if (codProd==ra->codProducto){
            valido=true;
        }
        valido=validarProducto2(ra->hDer, codPas, codProd, valido);

    }
    return valido;
}
void arbolPas::MostrarMarcas(pnodoPas R, string codPas, string codProd){
    if(R==NULL){
        return;
    }else{
        MostrarMarcas(R->hIzq, codPas, codProd);
        if (R->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=R->subsiguiente;
            pro.MostrarMarcas2(R->subsiguiente, codProd);
        }
        MostrarMarcas(R->hDer, codPas, codProd);
    }
}
void AVLProducto::MostrarMarcas2(pnodoProd R, string codProd){
    if(R==NULL){
    }else{
        MostrarMarcas2(R->hIzq, codProd);
        if (codProd==R->subsiguiente->codProducto){
            RN mar;
            mar.MostrarMarcas3(R->subsiguiente);
        }
        MostrarMarcas2(R->hDer, codProd);
    }
}
void RN::MostrarMarcas3(pnodoMarca R){
 if(R==NULL){
    }else{
        MostrarMarcas3(R->hIzq);
        cout<<R->nombre<<" "<<R->codMarca<<" // "<<R->cantGondola<<" "<<R->precio<<endl;
        MostrarMarcas3(R->hDer);
    }
}
bool arbolPas::validarMarca(pnodoPas ra, string codPas, string codProd, string codMar, bool valido){
    if(ra==NULL){
    }else{
        valido=validarMarca(ra->hIzq, codPas, codProd,codMar, valido);
        if (ra->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=ra->subsiguiente;
            valido=pro.validarMarcas2(ra->subsiguiente, codProd,codMar, valido);

        }
        valido=validarMarca(ra->hDer, codPas, codProd, codMar, valido);
    }
    return valido;
}
bool AVLProducto::validarMarcas2(pnodoProd ra, string codProd, string codMar, bool found){
    if(ra==NULL){
    }else{
        found=validarMarcas2(ra->hIzq, codProd, codMar, found);
        if (codProd==ra->subsiguiente->codProducto){
            RN marcas;
            found=marcas.validarMarcas3(ra->subsiguiente,codMar, found);
        }
        found=validarMarcas2(ra->hDer,codProd, codMar, found);

    }
    return found;
}
bool RN::validarMarcas3(pnodoMarca ra, string codMar,bool encontrado){
    pnodoMarca marca;
    if(ra==NULL){
    }else{
        encontrado=validarMarcas3(ra->hIzq,codMar,encontrado);
        if (codMar==ra->codMarca){
            encontrado=true;
            marca=ra;
        }
        encontrado=validarMarcas3(ra->hDer,codMar, encontrado);

    }
    return encontrado;
}
pnodoMarca arbolPas::encontrarNodo1(pnodoPas ra, string codPas, string codProd, string codMar, pnodoMarca marca){
    bool var=false;
    if(ra==NULL){
    }else{
        marca=encontrarNodo1(ra->hIzq, codPas, codProd,codMar, marca);
        if (ra->codPasillo==codPas){
            AVLProducto pro;
            pro.raiz=ra->subsiguiente;
            marca=pro.encontrarNodo2(ra->subsiguiente, codProd,codMar, marca);
        }
        marca=encontrarNodo1(ra->hDer, codPas, codProd, codMar, marca);
    }
    return marca;

}
pnodoMarca AVLProducto::encontrarNodo2(pnodoProd ra, string codProd, string codMar, pnodoMarca marca){
    if(ra==NULL){
    }else{
        marca=encontrarNodo2(ra->hIzq,codProd,codMar, marca);
        if (ra->codProducto==codProd){
            RN marcas;
            marcas.raiz=ra->subsiguiente;
            marca=marcas.encontrarNodo3(ra->subsiguiente,codMar, marca);
        }
        marca=encontrarNodo2(ra->hDer, codProd, codMar, marca);
    }
    return marca;
}
pnodoMarca RN::encontrarNodo3(pnodoMarca ra, string codMar, pnodoMarca marca){
    bool var=false;
    if(ra==NULL){
    }else{
        marca=encontrarNodo3(ra->hIzq, codMar, marca);
        if (ra->codMarca==codMar){
            marca=ra;
        }
        marca=encontrarNodo3(ra->hDer,codMar, marca);
    }
    return marca;
}
void Principal::escogerPasillo(arbolPas pasillos){
    cout<<"Estos son las opciones de pasillos: "<<endl;
    cout<<"Nombre / Codigo"<<endl;
    pasillos.MostrarPasillos(pasillos.raiz);
    cout<<"Escoja el codigo de pasillo que desea: "<<endl;
    string codigo;
    cin>>codigo;
    bool pasilloValido=false;
    pasilloValido=pasillos.encontrarPasillo(pasilloValido, pasillos.raiz, codigo);
    if (pasilloValido==true){
        cout<<"Las opciones de productos son: "<<endl;
        escogerProducto(pasillos, codigo);
    }
    else{
        cout<<"Pasillo no encontrado. Presione 1 si desea seguir comprando u otra cosa sino: "<<endl;
        string dec;
        cin>>dec;
        if(dec=="1"){
            escogerPasillo(pasillos);
        }
        else {
            cout<<"Gracias por su compra!"<<endl;
        }
    }

}
void Principal::escogerProducto(arbolPas pasillos, string codPas){
    cout<<"Nombre Producto / Codigo Producto"<<endl;
    pasillos.MostrarProductos(pasillos.raiz, codPas);
    cout<<"Seleccione el codigo de producto que desea: "<<endl;
    string codProd;
    cin>>codProd;
    bool productoValido=false;
    productoValido=pasillos.ValidarProducto1(pasillos.raiz, codPas,codProd ,productoValido);
    if (productoValido){
        cout<<"Las opciones de marcas son: "<<endl;
        escogerMarca(pasillos, codPas, codProd);
    }
    else{
        cout<<"El codigo de producto que selecciono es incorrecto, presione 1 si desea seguir comprando, cualquier otra cosa sino: "<<endl;
        string dec;
        cin>>dec;
        if(dec=="1"){
            cout<<"Si desea escoger otro producto del mismo pasillo dijite 1, si desea escoger otro pasillo digite cualquier tecla: "<<endl;
            string dec2;
            cin>>dec2;
            if (dec2=="1"){
                escogerProducto(pasillos, codPas);
            }
            else{
                escogerPasillo(pasillos);
            }
        }
        else{
            cout<<"Gracias por su compra!"<<endl;
        }
    }
}
void Principal::escogerMarca(arbolPas pasillos,string codPas, string codProd){
    cout<<"Nombre Marca / Codigo Marca // Cantidad / Precio por unidad"<<endl;
    pasillos.MostrarMarcas(pasillos.raiz, codPas, codProd);
    cout<<"Digite el codigo de la marca que desea: "<<endl;
    string codMar;
    cin>>codMar;
    bool encontrado=false;
    encontrado=pasillos.validarMarca (pasillos.raiz, codPas, codProd, codMar, encontrado);
    if (encontrado){
        cout<<"Escriba la cantidad que desea: "<<endl;
        int absoluto;
        cin>>absoluto;
        int cant1;
        cant1=abs(absoluto);
        if(!cin)
        {
            cin.clear();
            cin.ignore();
            cout<<"Entrada incorrecta, ingrese solo numeros: "<<endl;
            cin>>cant1;
        }
        pnodoMarca mar;
        mar=pasillos.encontrarNodo1(pasillos.raiz, codPas, codProd, codMar, mar);
        if (mar->cantGondola>=cant1){
            //Hacer la cola para agregar a la pila
            mar->cantGondola=((mar->cantGondola)-cant1);
            cout<<"Producto agregado con exito al carrito\nDesea seguir comprando? Presione 1 para Si o cualquier tecla para no: "<<endl;
            string resp;
            cin>>resp;
            if(resp=="1")
                escogerPasillo(pasillos);
            else
            {
                cout<<"Gracias por su compra, pronto se le cobraran sus articulos."<<endl;
                //menuCliente(); //Hacer bien, meter los paráemtros
            }
        }
        else if(mar->cantGondola<cant1&&mar->cantGondola!=0){
            cout<<"La cantidad de que existe de esta marca es menor de la que usted solicita.\nSolo hay: "<<mar->cantGondola<<endl;
            cout<<"Usted puede:"<<endl;
            cout<<"1)Llevarse la cantidad que hay\n2)Escoger otra marca del mismo producto.\n3)Escoger otro producto del mismo pasillo\n4)Escoger otro pasillo\nOtro)Dejar de comprar\nDigite la opcion que desea: "<<endl;
            string dec2;
            cin>>dec2;
            if (dec2=="2"){
                escogerMarca(pasillos,codPas, codProd);
            }
            else if (dec2=="3"){
                escogerProducto(pasillos,codPas);
            }
            else if(dec2=="4"){
                escogerPasillo(pasillos);
            }
            else if (dec2=="1")
            {
                //Hacer cola para agregar a pila
                mar->cantGondola=0;
                cout<<"Producto agregado con exio al carrito\nDesea seguir comprando? Presione 1 para Si o cualquier tecla para no: "<<endl;
                string resp;
                cin>>resp;
                if(resp=="1")
                    escogerPasillo(pasillos);
                else{
                    cout<<"Gracias por su compra, pronto se le cobrarán sus artículos."<<endl;
                    //menuCliente(); //Hacer el metodo y agregar los parametros
                }
            }
            else{
                cout<<"Gracias por su compra!"<<endl;
            }
        }
        else if (mar->cantGondola==0)
        {
            cout<<"Lamentamos el incoveniente, pero en este momento no tenemos unidades de la marca seleccionada."<<endl;
            cout<<"Usted puede:"<<endl;
            cout<<"1)Escoger otra marca del mismo producto.\n2)Escoger otro producto del mismo pasillo\n3)Escoger otro pasillo\nOtro)Dejar de comprar\nDigite la opcion que desea: "<<endl;
            string dec2;
            cin>>dec2;
            if (dec2=="1"){
                escogerMarca(pasillos,codPas, codProd);
            }
            else if (dec2=="2"){
                escogerProducto(pasillos,codPas);
            }
            else if(dec2=="3"){
                escogerPasillo(pasillos);
            }
            else{
                //menuCliente(); //Hacer
            }
        }

    }
    else{
        cout<<"El codigo de marca que ingreso es incorrecto."<<endl;
        cout<<"1)Escoger otra marca del mismo producto.\n2)Escoger otro producto del mismo pasillo\n3)Escoger otro pasillo\nOtro)Dejar de comprar\nDigite la opcion que desea: "<<endl;
        string dec2;
        cin>>dec2;
        if (dec2=="1"){
            escogerMarca(pasillos,codPas, codProd);
        }
        else if (dec2=="2"){
            escogerProducto(pasillos,codPas);
        }
        else if(dec2=="3"){
            escogerPasillo(pasillos);
        }
        else{
            cout<<"Gracias por su compra!"<<endl;
        }
    }

}
void Principal::comprar(arbolPas pasillos){
    escogerPasillo(pasillos);
}
//Ingresar
//Cola de clientes, log in
//bool Principal::agregarCliente(colaCliente, string ced)
//{
//    pnodoCola aux=colaCliente.primero;
//    while (aux!=NULL){
//        if(aux->cedula==ced)
//            return false;
//        aux=aux->siguiente;
//    }
//    return true;
//}
bool Principal::validarCliente(ArbolB cliente, string ced)
{
    int k;
    stringstream var(ced);
    int cedula;
    var>>cedula;
    Pagina *pag=new Pagina(5);
    pag=cliente.buscar(cedula, k);
    if (pag!=NULL){
        return true;
    }
    else{
        cout<<"No existe ningun cliente con ese numero de cedula";
        return false;
    }
}
bool Principal::validarAdministrador(ArbolB administrador, string cod){
    int k;
    stringstream var(cod);
    int codigo;
    var>>codigo;
    Pagina *pag=new Pagina(5);
    pag=administrador.buscar(codigo, k);
    if (pag!=NULL){
        return true;
    }
    else{
        cout<<"No existe ningun administrador con ese codigo";
        return false;
    }
}
void Principal::agregarCola(ArbolB cliente, string cedula){
    int k;
    stringstream var(cedula);
    int cedulaa;
    var>>cedula;
    Pagina *pag=new Pagina(5);
    pag=cliente.buscar(cedulaa, k);
    bool validar=validarCliente(cliente, cedula);
    if (validar){
        if (cola.ListaVacia()){
            cola.InsertarFinal(cedula, *pag->obtenerDato(k, 0), *pag->obtenerDato(k, 1),*pag->obtenerDato(k, 2), *pag->obtenerDato(k, 3), *pag->obtenerDato(k, 4));
        }
        else{
            bool rep;
            rep=agregarCliente(colaCliente, cedula);
            if (rep==false){
                cola.InsertarFinal(cedula, *pag->obtenerDato(k, 0), *pag->obtenerDato(k, 1),*pag->obtenerDato(k, 2), *pag->obtenerDato(k, 3), *pag->obtenerDato(k, 4));
            }
        }
    }
}
void Principal::login(ArbolB administradores, ArbolB clientes, string cedula){
    if(validarCliente(clientes,cedula)){
        menuCliente();
    }
    else if (validarAdministrador(administradores, cedula)){
        menuAdministrador();
    }
    else{
        cout<<"Usted no esta registrado como cliente ni como administrador, desea ingresar como invitado o enviar una solicitud para ser regsitrado?\nDigite 1 para enviar la solicitud u otra cosa para entrar como invitado: "<<endl;
        string dec;
        cin>>dec;
        if(dec=="1"){
            //Enviar solicitud, preguntar a Fabrizio
        }
        else{
            menuInvitado();
        }
    }
}
//void Principal::menuCliente(arbolPas pasillos, AVLProducto productos, RN marcas, ArbolInventario inventario)
//{
//    cout<<"1)\nComprar\n2)Consultar precio\n3)Consultar si es de canasta\n)4)Consultar Impuesto, \n5)Salir"
//    cout<<"Digite el numero de lo que desea realizar: ";
//    string opc;
//    cin>>opc;
//    if(opc=="1")
//    {
//        comprar(pasillos, productos, marcas, inventario); //Terminar
//    }
//    else if (opc=="2")
//    {
//        if (cola.ListaVacia()==true){
//            cout<<"No puede hacer cobros porque no hay ningun cliente en la cola de espera."<<endl;
//            menu(listaPas, cliente, inventario);
//        }
//        pagar(listaPas,cliente,inventario);
//        cout<<"Lista en el menu: ";
//        listaVent.Mostrar();
//    }
//    else if(opc=="3")
//    {
//        if (listaVent.ListaVacia()&&listaVentCopia.ListaVacia()){
//            cout<<"No puede recargar la gondola ya que la lista de ventas esta vacia."<<endl;
//            menu(listaPas, cliente, inventario);
//        }
//        if (lisVent==true)
//            lisVent=false;
//        else
//            lisVent=true;
//        rellenarGondolas(listaPas,cliente, inventario);
//    }
//    else if (opc=="4")
//    {
//        if(listaVent.ListaVacia()&&listaVentCopia.ListaVacia()){
//            cout<<"No se puede recargar el inventario porque la lista de ventas esta vacia."<<endl;
//            menu(listaPas, cliente, inventario);
//        }
//        rellenarInventario(listaPas,cliente, inventario);
//    }
//    else if (opc=="5")
//    {
//        escogerReporte(listaPas, cliente, inventario);
//    }
//    else if (opc=="6")
//    {
//        cout<<"Gracias por comprar en nuestro sistema.";
//        exit(1);
//    }
//    else
//    {
//        cout<<"Indicacion invalida, trate con los numeros 1, 2, 3, 4, 5 o 6"<<endl;
//        menu(listaPas, cliente, inventario);
//    }
//
//}
int main()
{
    arbolPas pasillos;
    RN arbol;
    Ciudad ciudad;
    ArbolInventario inven;
    Principal principal;
    pasillos=arbol.arbolMarcas();
    Pagina *actual;
//    ArbolB arbolAdm=ArbolB(5);
//    cout<<"\n"<<endl;
//    ciudad.agregarCiudades();
//    cout<<endl;
//    inven.agregarInventario();
//    cout<<endl;
    ArbolB cliente=ArbolB(5);
    cliente.cargarClientes("Clientes.txt");
   // cliente.escribir();
   // arbolCli.cargarClientes("Clientes.txt");
    //arbolCli.escribir();
   // cout<<endl;
   // arbolAdm.cargarAdmins("Administradores.txt");
   // arbolAdm.escribir();
   // cout<<endl;
   //cout<<"Ingrese su numero de cedula: "<<endl;
  // string cedula;
   //cin>>cedula;
//   principal.login(cliente, cedula);
    principal.comprar(pasillos);
    cout<<"fin del main";
    cin.get();
    return 0;
}
