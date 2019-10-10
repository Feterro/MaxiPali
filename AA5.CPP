#include <iostream>
#include <cctype>
using namespace std;
class nodo {
   public:
    nodo(int v)
    {
        valor = v;
        hIzq = NULL;
        hDer = NULL;
        nivel=1;
    }
    int valor;
    nodo *hIzq;
    int nivel;
    nodo *hDer;
   private:
    int cant;

   friend class AA;
};
typedef nodo *pnodo;

class AA{
public:
    nodo *raiz;
	AA() { raiz = NULL; }
    InordenR(pnodo ra);
    pnodo insertar(int val, pnodo t);
    pnodo giro(pnodo aux);
    pnodo reparto(pnodo aux);
    pnodo rotarDerecha(pnodo aux);
    pnodo rotarIzquierda(pnodo aux);
    void Inorden(pnodo ra);

};
void AA::Inorden(pnodo R){
 if(R==NULL){
        return;
    }else{
        Inorden(R->hIzq);
        cout<<R->valor<<"->";
        Inorden(R->hDer);
    }
}
pnodo AA::insertar(int val, pnodo aux)
{
    if (aux==NULL){
        aux=new nodo(val);
    }
    else if (val<aux->valor){
        aux->hIzq=insertar(val, aux->hIzq);
    }
    else if (val>aux->valor){
        aux->hDer=insertar(val, aux->hDer);
    }
    else {
        cout<<"Repetido"<<endl;
    }
    aux=giro(aux);
    cout<<"Valor: "<<val<<endl;
    cout<<"Vuelve del giro: "<<aux->valor<<endl;
    aux=reparto(aux);
    cout<<"Vuelve del reparto: "<<aux->valor<<endl;
    cout<<"***********************";
    return aux;
}
pnodo AA::giro( pnodo aux )
{
    if (aux->hIzq==NULL){
        return aux;
    }
    if(aux->hIzq->nivel == aux->nivel ){
        aux= rotarIzquierda( aux );
    }
    return aux;
}
pnodo AA::reparto(pnodo aux)
{
    if (aux->hDer==NULL){
        return aux;
    }
    if( aux->hDer->nivel == aux->nivel && aux->hDer->hDer!=NULL && aux->hDer->hDer->nivel==aux->nivel)
    {
//        cout<<aux->hDer->valor<<endl;
//        cout<<aux->valor<<endl;
//        cout<<aux->hIzq<<endl;
//        cout<<"Nivel: "<<aux->hDer->nivel<<endl;
//        cout<<aux->nivel<<endl;
        cout<<"Rotar derecha"<<endl;
        cout<<aux->valor<<endl;
        aux= rotarDerecha(aux);
        aux->nivel++;
    }
    return aux;
}
pnodo AA::rotarIzquierda(pnodo aux)
{
    pnodo otro=aux->hIzq; //otro: k1 y aux=k2
    aux->hIzq = otro->hDer;
    otro->hDer= aux;
    return otro;
}
/**
* Rotate binary tree node with right child.
* For AVL trees, this is a single rotation for case 4.
*/
pnodo AA::rotarDerecha(pnodo aux)
{
    pnodo otro = aux->hDer;
    aux->hDer= otro->hIzq;
    otro->hIzq=aux;
    return otro;
}
int main() {
    AA aa;
    aa.raiz=aa.insertar(10, aa.raiz);
    aa.raiz=aa.insertar(4, aa.raiz);
    aa.raiz=aa.insertar(2, aa.raiz);
    aa.raiz=aa.insertar(11, aa.raiz);
    aa.raiz=aa.insertar(7, aa.raiz);
    aa.raiz=aa.insertar(1, aa.raiz);
    aa.raiz=aa.insertar(3, aa.raiz);
    cout<<"||||||||||||||||||||||||||||||||"<<endl;
    cout<<"Raiz: "<<aa.raiz->valor<<" "<<aa.raiz->nivel<<endl;
    cout<<"hizq "<<aa.raiz->hIzq->valor<<" "<<aa.raiz->hIzq->nivel<<endl;
    cout<<"hizq hizq "<<aa.raiz->hIzq->hIzq->valor<<" "<<aa.raiz->hIzq->hIzq->nivel<<endl;
    cout<<"hizq der "<<aa.raiz->hIzq->hDer->valor<<" "<<aa.raiz->hIzq->hDer->nivel<<endl;
    cout<<"hder "<<aa.raiz->hDer->valor<<" "<<aa.raiz->hDer->nivel<<endl;
    cout<<"hder hizq "<<aa.raiz->hDer->hIzq->valor<<" "<<aa.raiz->hDer->hIzq->nivel<<endl;
    cout<<"hder hder "<<aa.raiz->hDer->hDer->valor<<" "<<aa.raiz->hDer->hDer->nivel<<endl;
    return 0;
}
