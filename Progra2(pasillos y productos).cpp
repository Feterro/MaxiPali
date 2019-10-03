#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
using namespace std;
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
    }

   private:
    string codPasillo;
    string nombre;
    int pasvis;
    nodoPasillo *hIzq;
    nodoPasillo *hDer;
   friend class arbolPas;
};
typedef nodoPasillo *pnodoPas;
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
    }
private:
    int FB;
    string codPasillo;
    string nombre;
    string codProducto;
    nodoProducto *hIzq;
    nodoProducto *hDer;
    nodoProducto *siguiente;

   friend class lista;
   friend class AVLProducto;
};
typedef nodoProducto *pnodoProd;
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
};
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
   // void PostordenI();
    bool arbolVacio() { return raiz == NULL; }
    arbolPas ListaBase();
    void InsertaBinario(pnodoPas raiz, string cod, string nombre);
};

class lista {
   public:
    lista() { primero = actual = NULL; }

    void InsertarFinal(string codPas, string codPro, string nom);
    bool ListaVacia() { return primero == NULL; }
    int largoLista();
    void Mostrar();
    lista enlistarCodigos();

   private:
    pnodoProd primero;
    pnodoProd actual;
};
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
    pasillos.InordenI(pasillos.raiz);
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
                if(n1->FB =-1){
                    RotacionSimpleIzquierda(aux, n1);
                }else{
                    RotacionDobleIzquierda(aux,n1);
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
                        if(n1->FB=1){
                            RotacionSimpleDerecha(aux, n1);
                        }else{
                            RotacionDobleDerecha(aux, n1);
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

lista lista::enlistarCodigos(){
    lista listaAlm;
    ifstream archivo;
    string texto;
    archivo.open("ProductosPasillos.txt",ios::in);
    while(!archivo.eof())
    {
        cout<<"ciclo"<<endl;
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
            cout<<"siay nada"<<endl;
            pnodoProd aux=listaAlm.primero;
            for(int i=0; i<listaAlm.largoLista(); i++)
            {
                cout<<"vuelto loko prro"<<codPro<<" "<<aux->codProducto<<endl;
                if(aux->codProducto==codPro){
                    rep=true;
                    cout<<"cmamo"<<endl;
                }
                aux=aux->siguiente;
            }
            if(rep==false)
                listaAlm.InsertarFinal(codPas,codPro,nom);
        }
        else{
          cout<<"nuai nada"<<endl;
          listaAlm.InsertarFinal(codPas,codPro,nom);
        }
    }
    listaAlm.Mostrar();
}
//listaDCpas listaDCpas::SublistaPro()
//{
///*
//Metodo que agrega productos a los pasillos
//*/
//
//    arbolPas lista;
//    listaDCpas listabas=lista.ListaBase();
//    ifstream archivo;
//    string texto;
//    archivo.open("ProductosPasillos.txt",ios::in);
//    while(!archivo.eof())
//    {
//        getline(archivo, texto);
//        char cstr[texto.size() + 1];
//        strcpy(cstr, texto.c_str());
//        char var[]=";";
//        char *token = strtok(cstr,var);
//        string codPas=token;
//        token = strtok(NULL,var);
//        string codPro=token;
//        token = strtok(NULL,var);
//        string nom=token;
//        pnodo aux=listabas.primeroPas;
//        int cont=1;
//        while(aux->siguiente!=listabas.primeroPas||cont==listabas.largoLista())
//        {
//            if(aux->codPasillo==codPas)
//            {
//                if(aux->subsiguiente!=NULL)
//                {
//                    bool rep=false;
//                    pnodo2 aux2=aux->subsiguiente;
//                    while(aux2->siguiente!=aux->subsiguiente)
//                    {
//                        if(aux2->siguiente->codProducto==codPro){
//                            rep=true;
//                            break;}
//					 	if(aux2->codProducto==codPro){
//                            rep=true;
//                            break;
//                        }
//                    aux2=aux2->siguiente;
//                    }
//                    if(aux->subsiguiente->siguiente==aux->subsiguiente)
//                    {
//                        if(aux2->codProducto==codPro)
//                            rep=true;
//                	}
//                    if(rep==true)
//                    {
//                        cout<< "Ya existe un producto con el codigo "<< codPro<<endl;
//                        aux=listabas.primeroPas;
//                        break;
//                	}
//                    if (rep==false)
//                    {
//                        pnodo2 nuevo = new nodoProducto(codPas, nom, codPro);
//                        nuevo->anterior = aux->subsiguiente->anterior;
//                        nuevo->siguiente=aux->subsiguiente;
//                        aux->subsiguiente->anterior->siguiente=nuevo;
//                        aux->subsiguiente->anterior=nuevo;
//                        break;
//                    }
//                }
//                else
//                {
//                   aux->subsiguiente= new nodoProducto(codPas, nom, codPro);
//                   aux->subsiguiente->anterior=aux->subsiguiente;
//                   aux->subsiguiente->siguiente=aux->subsiguiente;
//                   break;
//            	}
//            }
//            cont++;
//            aux=aux->siguiente;
//        }
//    }
//archivo.close();
////listabas.MostrarTerc();
//return listabas;
//}
int main()
{
    lista lis;
    arbolPas pasillos;
    pasillos.ListaBase();
    lis.enlistarCodigos();
    cout<<endl;
    cout<<"fin del main";
    cin.get();
    return 0;
}
