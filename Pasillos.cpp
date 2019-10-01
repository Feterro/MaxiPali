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
class arbolPas {
/*
Clase creadora de listas donde se insertaran
los pasillos. Base de la estructura creada con archivos
*/

   public:
    pnodoPas raiz;
    arbolPas():raiz(NULL){}

    void PreordenI();
    void InordenR(pnodoPas raiz);
    void PostordenI();

    bool arbolVacio() { return raiz == NULL; }
    arbolPas ListaBase();
    void InsertaBinario(pnodoPas raiz,string cod, string nombre);

   friend class listaDCPro;
   friend class listaSimple;
   friend class nodoCarrito;
};
void arbolPas::InordenR(pnodoPas R){
    if(R==NULL){
        return;
    }else{
        InordenR(R->hIzq);
        cout<<R->codPasillo<<"~"<<R->nombre<<"||";
        InordenR(R->hDer);
    }
}
void arbolPas::InsertaBinario(pnodoPas raiz,string cod, string nombre)
{
    cout<<cod<<endl;
    cout<<nombre<<endl;
    stringstream codi(cod);
    int valor;
    codi>>valor;
    if (arbolVacio()){
            cout<<"estabaVacio"<<endl;
        raiz=new nodoPasillo(cod, nombre);
        //cout<<"Primero: "<<arbol.raiz->codPasillo<<endl;
    }
    else{
        cout<<"no estaba vacio"<<endl;
        stringstream codRa(raiz->codPasillo);
        int valRa;
        codRa>>valRa;
        if(valor<valRa){//no acepta valores repetidos
            cout<<"va pa la izq"<<endl;
            if(raiz->hIzq==NULL){
                raiz-> hIzq = new nodoPasillo(cod, nombre);
                //cout<<": "<<arbol.raiz->codPasillo<<endl;
            }else{
                InsertaBinario(raiz->hIzq,cod, nombre);
            }
        }else if(valor>valRa){
            cout<<"va pa la der"<<endl;
            if(raiz->hDer==NULL){
                cout<<"se inserta"<<endl;
                raiz->hDer = new nodoPasillo(cod, nombre);
            }else{
                InsertaBinario(raiz->hDer,cod, nombre);
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
        bool rep=false;
        cout<<nom<<" "<<cod<<endl;
        pasillos.InsertaBinario(pasillos.raiz,cod, nom);

    }
    cout<<"Hola2"<<endl;
    pnodoPas aux=pasillos.raiz;
    //cout<<pasillos.raiz->nombre<<" "<<pasillos.raiz->hIzq->nombre<<endl;
    pasillos.InordenR(pasillos.raiz);
    archivo.close();
    return pasillos;
}
int main()
{
    arbolPas pasillos;
    pasillos.ListaBase();
    cout<<"fin del main"<<endl;
    cin.get();
    return 0;
}
