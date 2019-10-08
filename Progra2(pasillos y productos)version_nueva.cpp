#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;
enum Color {
    ROJO,
    NEGRO
};

class nodoMarca {
/*
Clase que construye los objetos de tipo nodo donde se
gurdan los datos de las marcas de los productos.
Clase amiga de lista marcas y la clase principal.
*/

   public:
    nodoMarca(string codPas, string nom, string codPro, string codMar, int cantGon, float val)
    {
        codPasillo=codPas;
        nombre=nom;
        codProducto=codPro;
        codMarca=codMar;
        cantGondola=cantGon;
        precio=val;
        cantcomp=0;
        hIzq = NULL;
        hDer = NULL;
        padre=NULL;
        siguiente=NULL;
        color=ROJO;
    }
   private:
    string codPasillo;
    string nombre;
    string codProducto;
    string codMarca;
    int cantGondola;
    float precio;
    int cantcomp;
    nodoMarca *hIzq;
    nodoMarca *hDer;
    nodoMarca *padre;
    nodoMarca *siguiente;
    Color color;

   friend class AVLProducto;
   friend class arbolPas;
   friend class RN;
   friend class lista;
};
typedef nodoMarca*pnodoMarca;
class nodoProducto {
/*
Clase creadora de nodos de productos para ser
enlazado a los nodos de pasillo . Clase amiga
 de listaDCpas,listaSimple.
*/
public:
    nodoProducto(string codPas,string codPro, string nom)
    {
        codPasillo=codPas;
        nombre=nom;
        codProducto=codPro;
        hIzq=NULL;
        hDer=NULL;
        siguiente=NULL;
        subsiguiente=NULL;
    }


private:
    string nombre;
    nodoProducto *hIzq;
    nodoProducto *hDer;
    int FB;
    string codPasillo;
    string codProducto;
    nodoProducto *siguiente;
    nodoMarca *subsiguiente;


   friend class arbolPas;
   friend class RN;
   friend class lista;
   friend class AVLProducto;
};
typedef nodoProducto *pnodoProd;
class nodoPasillo {
/*
Clase creadora de nodos de pasillo para ser
usados en listas. Clase amiga de listaDCpas,
listaSimple y nodoCarrito
*/
   public:
    nodoPasillo(string codPas, string nom)
    {
        codPasillo=codPas;
        nombre=nom;
        pasvis=0;
        hIzq=NULL;
        hDer=NULL;
        subsiguiente=NULL;
    }

   private:
    string codPasillo;
    string nombre;
    int pasvis;
    nodoPasillo *hIzq;
    nodoPasillo *hDer;
    nodoProducto *subsiguiente;
   friend class arbolPas;
   friend class AVLProducto;
   friend class RN;
};
typedef nodoPasillo *pnodoPas;
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
};
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

    friend class lista;
};
class lista {
   public:
    lista() { primero = actual = NULL; primeroMar = actualMar= NULL; }

    void InsertarFinal(string codPas, string codPro, string nom);
    void InsertarFinalMar(string codPas, string nom, string codPro, string codMar,int cantGon,float precio);
    bool ListaVacia() { return primero == NULL; }
    bool ListaVaciaMar() { return primeroMar == NULL; }
    int largoLista();
    int largoListaMar();
    void Mostrar();
    void MostrarMar();
    lista enlistarCodigos();
    lista enlistarCodigosMar();


   private:
    pnodoProd primero;
    pnodoMarca primeroMar;
    pnodoProd actual;
    pnodoMarca actualMar;

    friend class arbolPas;
    friend class RN;
    friend class AVLProducto;
};

class RN{
public:
    nodoMarca *raiz;
	RN() { raiz = NULL; }
	void rotarIzquierda(nodoMarca *&, nodoMarca *&);
	void rotarDerecha(nodoMarca *&, nodoMarca *&);
	void balancearArbol(nodoMarca *&, nodoMarca *&);
	void insert(const string &codPasilo,const string &nombre,const string &codProducto,const string &codMar,const int &gon, const float &val);
	void levelOrder();
	pnodoMarca insertarNodo(pnodoMarca raiz, pnodoMarca pt);
	void InordenMar(pnodoMarca R);
	RN arbolMarcas();

};

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
    //pasillos.InordenI(pasillos.raiz);
    archivo.close();
    return pasillos;
}
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
void RN:: InordenMar(pnodoMarca R){
 if(R==NULL){
        return;
    }else{
        InordenMar(R->hIzq);
        cout<<R->codPasillo<<"~"<<R->codProducto<<"~"<<R->codMarca<<"~"<<R->nombre<<"~"<<R->cantGondola<<"~"<<R->precio<<"/";
        InordenMar(R->hDer);
    }
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
    //    cout<<"nulo"<<endl;
    }else{
        busquedaPro(nodoPas->hIzq, nodoMar);
        if(nodoPas->codPasillo==nodoMar->codPasillo)
        {
        	if(nodoPas->subsiguiente==NULL){
            //    cout<<"nulo"<<endl;
        	}
        	else{
                //cout<<nodoPas->codPasillo<<nodoMar->codPasillo<<endl;
                AVLProducto arbol;
                arbol.raiz=nodoPas->subsiguiente;
        	    arbol.EnlaceRN(nodoPas->subsiguiente,nodoMar);
        	}
		}
        busquedaPro(nodoPas->hDer, nodoMar);
    }
}


RN RN::arbolMarcas(){
//    AVLProducto arbolProd;
	lista listaCod;
	listaCod=listaCod.enlistarCodigosMar();
	arbolPas arbolPasillo;
	arbolPasillo=arbolPasillo.arbolProductos();
	pnodoMarca aux=listaCod.primeroMar;
	for(int i=0; i<listaCod.largoListaMar();i++)
    {
//        cout<<aux->nombre<<endl;
       pnodoProd encont=arbolPasillo.busquedaPro(arbolPasillo.raiz, aux);
 //       cout<<"sale"<<endl;
//        cout<<"encont "<<encont->nombre<<endl;
//        EnlaceRN(encont->subsiguiente,aux);
       aux=aux->siguiente;
    }
    arbolPasillo.InordenTriple(arbolPasillo.raiz);
}

int main()
{
//    lista lis;
//    arbolPas pasillos;
//    pasillos.ListaBase();
//    lis.enlistarCodigos();
    RN arbol;
    arbol.arbolMarcas();
    cout<<endl;
    cout<<"fin del main";
    cin.get();
    return 0;
}
