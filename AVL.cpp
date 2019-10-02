#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
using namespace std;
class nodo {
public:
    nodo(int v)
    {
       valor = v;
       hIzq = NULL;
       hDer = NULL;
    }
    int valor;

    nodo *hIzq;
    nodo *hDer;
    int FB;
//   private:
//
//    nodo *hIzq;
//    nodo *hDer;
//    int FB;

   friend class AVL;
};
typedef nodo *pnodo;
class AVL{
public:
    pnodo raiz;
    AVL():raiz(NULL){}
    bool Hh;
    void InordenR(pnodo raiz);
    void InsertarBalanceado(nodo *r, nodo *r2, bool Hh, int x);
    void RotacionDobleIzquierda(nodo *n1, nodo *n2);
    void RotacionDobleDerecha(nodo *n1, nodo *n2);
    void RotacionSimpleIzquierda(nodo *n1, nodo *n2);
    void RotacionSimpleDerecha(nodo *n1, nodo *n2);
};
void AVL::InordenR(pnodo R){
    //cout<<"trytgui"<<endl;
    if(R==NULL){
        //cout<<"GDSHDGHJAS"<<endl;
        return;
    }else{
        //cout<<"kljjfgf"<<endl;
        InordenR(R->hIzq);
        cout<<R->valor<<"||";
        InordenR(R->hDer);
    }
}
void AVL::InsertarBalanceado(nodo *aux,nodo *ra, bool Hh, int x){
    pnodo n1;
    if(raiz==NULL){
        raiz=new nodo(x);
        cout<<"Raiz: "<<raiz->valor<<endl;
        Hh = true;
        return;
    }
    else if(aux==NULL&&raiz!=NULL){
        if(x<ra->valor)
            ra->hIzq=new nodo(x);
        else if(x>ra->valor)
            ra->hDer=new nodo(x);
        //cout<<raiz->hDer->hDer<<endl;
        //cout<<"Otros: "<<->valor<<endl;
        Hh = true;
    }else{
        //cout<<"q as2"<<endl;
        if(x<aux->valor){
            InsertarBalanceado(aux->hIzq,aux, Hh, x);

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
            if(x>aux->valor){
                InsertarBalanceado(aux->hDer,aux, Hh, x);

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
void AVL::RotacionDobleIzquierda(nodo* n, nodo* n1){
    nodo *n2;
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

void AVL::RotacionDobleDerecha(nodo* n, nodo* n1){
    nodo *n2;
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

void AVL::RotacionSimpleDerecha(nodo* n, nodo* n1){
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

void AVL::RotacionSimpleIzquierda(nodo* n, nodo* n1){
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
int main(){
    AVL arbol;
    arbol.InsertarBalanceado(arbol.raiz,arbol.raiz, false, 10);
    //cout<<"raiz del arbol "<<arbol.raiz->valor<<endl;
    //cout<<"Vuelve"<<endl;
    arbol.InsertarBalanceado(arbol.raiz,arbol.raiz, false, 4);
    arbol.InsertarBalanceado(arbol.raiz,arbol.raiz, false, 5);
    arbol.InsertarBalanceado(arbol.raiz,arbol.raiz, false, 7);
    arbol.InsertarBalanceado(arbol.raiz,arbol.raiz, false, 47);
   arbol.InsertarBalanceado(arbol.raiz,arbol.raiz, false, 9);
    cout<<"raiz del arbol: "<<arbol.raiz->valor<<endl;
    cout<<"hijo der: "<<arbol.raiz->hDer->valor<<endl;
    arbol.InordenR(arbol.raiz);
    cout<<"Termina main"<<endl;
    cin.get();
    return 0;
}
