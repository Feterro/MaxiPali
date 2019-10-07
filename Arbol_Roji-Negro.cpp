#include <bits/stdc++.h>
using namespace std;
enum Color {
    ROJO,
    NEGRO
};

class nodoMarca {
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
    Color color;

   friend class RN;
};

//class nodo {
//public:
//    nodo(int v)
//    {
//        valor = v;
//        hIzq = NULL;
//        hDer = NULL;
//        padre=NULL;
//        color=ROJO;
//    }
//private:
//    int valor;
//    nodo *hIzq;
//    nodo *hDer;
//    nodo *padre;
//    Color color;
//
//friend class RN;
//};

typedef nodoMarca*pnodoMarca;

class RN{
public:
    nodoMarca *raiz;
	RN() { raiz = NULL; }
	void rotarIzquierda(nodoMarca *&, nodoMarca *&);
	void rotarDerecha(nodoMarca *&, nodoMarca *&);
	void balancearArbol(nodoMarca *&, nodoMarca *&);
	void insert(const string &codPasilo,const string &nombre,const string &codProducto,const string &codMar,const int &gon, const float &val);
	void inorder();
	void levelOrder();
	pnodoMarca insertarNodo(pnodoMarca raiz, pnodoMarca pt);
	void InordenR(pnodoMarca ra);
};

void RN::InordenR(pnodoMarca R){
    if(R==NULL){
        return;
    }else{
        InordenR(R->hIzq);
        cout<<R->codPasillo<<"~"<<R->codProducto<<"~"<<R->codMarca<<"~"<<R->nombre<<"~"<<R->cantGondola<<"~"<<R->precio<<"||";
        InordenR(R->hDer);
    }
}

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

int main()
{
	RN RojiNegro;

	RojiNegro.insert("20","luisiana","45","75",4,3.5);
	RojiNegro.insert("21","del monte","46","21",5,3.6);
	RojiNegro.insert("22","luisiana","47","1",6,3.7);
//	cout<<RojiNegro.raiz->valor<<endl;
	RojiNegro.insert("23","luisiana","48","34",7,3.8);
	RojiNegro.insert("24","luisiana","49","18",8,3.9);
//	RojiNegro.insert(57);
//	RojiNegro.insert(8);
//	RojiNegro.insert(95);
//	RojiNegro.insert(1);
//	RojiNegro.insert(23);
//	RojiNegro.insert(47);
//	RojiNegro.insert(18);
//	RojiNegro.insert(1024);
//	RojiNegro.insert(37);
//	RojiNegro.insert(41);
	cout<<"Inorden: ";
	RojiNegro.InordenR(RojiNegro.raiz);

    cin.get();
	return 0;
}
