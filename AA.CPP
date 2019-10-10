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
   private:
    int cant;
    nodo *hDer;
    nodo *siguiente;
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
    if( raiz == NULL){
        raiz = new nodo(val);
        return raiz;
    }
    else if (aux==NULL && raiz!=NULL){
        aux=new nodo(val);
    }
    else if( val<aux->valor){
        aux->hIzq= insertar(val, aux->hIzq );
       // cout<<"aux: "<<aux->hIzq<<endl;
    }
    else if( val>aux->valor ){
        //cout<<"fdsgsg"<<endl;
        aux->hDer=insertar( val, aux->hDer );
    }
    else{
        cout<<"Repetido"<<endl;
    }
    //cout<<aux->hIzq->nivel<<endl;
    if (aux->hIzq!=NULL){
        cout<<"aux: "<<aux->valor<<" ";
        cout<<aux->nivel<<endl;
        //cout<<"der "<<aux->hDer->valor<<endl;
        cout<<"izq "<<aux->hIzq->valor<<endl;
        //Inorden(raiz);
        aux = giro( aux );
        cout<<aux->valor<<endl;
       // cout<<aux->hDer->valor<<endl;
       // cout<<aux->hDer->hDer->valor<<endl;
       // cout<<"Nraiz: "<<raiz->valor<<endl;
        aux = reparto( aux );
    }
    return aux;
}
pnodo AA::giro( pnodo aux )
{
    if (aux->hIzq==NULL){
        return aux;
    }
    if(aux->hIzq->nivel == aux->nivel ){
        cout<<"Rotar "<<endl;
        aux= rotarIzquierda( aux );
        cout<<aux->valor<<endl;
    }
    return aux;
}
pnodo AA::reparto(pnodo aux)
{
    if( aux->hDer->nivel == aux->nivel )
    {
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
    pnodo otro = aux->hDer; //aux=k1 otro=k2
    aux->hDer= otro->hIzq;
    otro->hIzq=aux;
    return otro;
}
int main() {
    AA aa;
    //cout<<aa.raiz;
   // cout<<aa.insertar(4, aa.raiz)->valor;
    //cout<<aa.raiz;
    aa.insertar(12, aa.raiz);
    cout<<"llega"<<endl;
    aa.insertar(9, aa.raiz);
    if(aa.raiz->hIzq!=NULL)
        if(aa.raiz->hIzq->nivel==aa.raiz->nivel)
            aa.raiz=aa.raiz->hIzq;
    aa.Inorden(aa.raiz);

    cout<<"llega2"<<endl;
    aa.insertar(7, aa.raiz);
    if((aa.raiz->hIzq!=NULL))
        if(aa.raiz->hIzq->nivel==aa.raiz->nivel)
            aa.raiz=aa.raiz->hIzq;
    aa.Inorden(aa.raiz);

    cout<<"llega3"<<endl;
    aa.insertar(4, aa.raiz);
    if((aa.raiz->hIzq!=NULL))
        if(aa.raiz->hIzq->nivel==aa.raiz->nivel)
            aa.raiz=aa.raiz->hIzq;
    aa.Inorden(aa.raiz);

    cout<<"llega4"<<endl;
    aa.insertar(5, aa.raiz);
    if((aa.raiz->hIzq!=NULL))
        if(aa.raiz->hIzq->nivel==aa.raiz->nivel)
            aa.raiz=aa.raiz->hIzq;
    aa.Inorden(aa.raiz);

    cout<<"llega5"<<endl;
    aa.insertar(6, aa.raiz);
    if((aa.raiz->hIzq!=NULL))
        if(aa.raiz->hIzq->nivel==aa.raiz->nivel)
            aa.raiz=aa.raiz->hIzq;
    aa.Inorden(aa.raiz);
    //aa.insertar(2, aa.raiz);
    return 0;
}
