#include <bits/stdc++.h>
using namespace std;
enum Color {
    ROJO,
    NEGRO
};
class nodo {
public:
    nodo(int v)
    {
        valor = v;
        hIzq = NULL;
        hDer = NULL;
        padre=NULL;
        color=ROJO;
    }
private:
    int valor;
    nodo *hIzq;
    nodo *hDer;
    nodo *padre;s
    Color color;

friend class RN;
};
typedef nodo*pnodo;
class RN{
public:
    nodo *raiz;
	RN() { raiz = NULL; }
	void rotarIzquierda(nodo *&, nodo *&);
	void rotarDerecha(nodo *&, nodo *&);
	void balancearArbol(nodo *&, nodo *&);
	void insert(const int &n);
	void inorder();
	void levelOrder();
	pnodo insertarNodo(pnodo raiz, pnodo pt);
	void InordenR(pnodo ra);

};

void RN::InordenR(pnodo R){
    if(R==NULL){
        return;
    }else{
        InordenR(R->hIzq);
        cout<<R->valor<<"||";
        InordenR(R->hDer);
    }
}

pnodo RN::insertarNodo(pnodo raiz, pnodo pt){
	if (raiz == NULL)
	return pt;

	if (pt->valor<raiz->valor)
	{
		raiz->hIzq = insertarNodo(raiz->hIzq, pt);
		raiz->hIzq->padre = raiz;
	}
	else if (pt->valor > raiz->valor)
	{
		raiz->hDer = insertarNodo(raiz->hDer, pt);
		raiz->hDer->padre = raiz;
	}
	else {
        return pt;
    }
	return raiz;
}
void RN::rotarIzquierda(nodo *&raiz, nodo *&pt)
{
	pnodo pt_hDer = pt->hDer;

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

void RN::rotarDerecha(nodo *&raiz, nodo *&pt)
{
	pnodo pt_hIzq = pt->hIzq;

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

void RN::balancearArbol(nodo *&raiz, nodo *&pt)
{
	pnodo padre_pt = NULL;
	pnodo abuelo_pt = NULL;

	while ((pt != raiz) && (pt->color != NEGRO) &&
		(pt->padre->color == ROJO))
	{

		padre_pt = pt->padre;
		abuelo_pt = pt->padre->padre;
		if (padre_pt == abuelo_pt->hIzq)
		{
			pnodo tio_pt = abuelo_pt->hDer;
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
			pnodo tio_pt = abuelo_pt->hIzq;
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
void RN::insert(const int &num)
{
	pnodo pt = new nodo(num);
	raiz = insertarNodo(raiz, pt);
	balancearArbol(raiz, pt);
}

int main()
{
	RN RojiNegro;

	RojiNegro.insert(74);
	RojiNegro.insert(6);
	RojiNegro.insert(5);
	RojiNegro.insert(14);
	RojiNegro.insert(32);
	RojiNegro.insert(74);
	RojiNegro.insert(10);
	cout<<"Inorden: ";
	RojiNegro.InordenR(RojiNegro.raiz);

	return 0;
}
