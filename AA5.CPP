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
   private:
    nodo *hIzq;
    int nivel;
    nodo *hDer;
    int valor;

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
        return aux;
    }
    aux=giro(aux);
    aux=reparto(aux);
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
        aux= rotarDerecha(aux);
        aux->nivel++;
    }
    return aux;
}
pnodo AA::rotarIzquierda(pnodo aux)
{
    pnodo otro=aux->hIzq;
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
int main(){
    AA aa;
    aa.raiz=aa.insertar(10, aa.raiz);
    aa.raiz=aa.insertar(4, aa.raiz);
    aa.raiz=aa.insertar(2, aa.raiz);
    aa.raiz=aa.insertar(11, aa.raiz);
    aa.raiz=aa.insertar(7, aa.raiz);
    aa.raiz=aa.insertar(1, aa.raiz);
    aa.raiz=aa.insertar(3, aa.raiz);
    aa.Inorden(aa.raiz);
    return 0;
}
