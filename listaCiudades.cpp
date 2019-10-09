#include <iostream>
#include <cctype>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
using namespace std;
class nodoCiudad {
   public:
    nodoCiudad(int cod, string nom)
    {
       codigo= cod;
       siguiente = NULL;
       nombre=nom;
    }

    nodoCiudad(int cod, string nom, nodoCiudad * signodo)
    {
       codigo =cod;
       nombre=nom;
       siguiente = signodo;
    }

   private:
    int codigo;
    string nombre;
    nodoCiudad *siguiente;
   friend class Ciudad;
};

typedef nodoCiudad *pnodoCiudad;

class Ciudad {
   public:
    Ciudad() { primero = actual = NULL; }

    void InsertarFinal(int cod, string nom);
    bool listaVacia() { return primero == NULL; }
    void Mostrar();
    int largoCiudad();
    Ciudad agregarCiudades();
    bool agregarCiudad(Ciudad lista, int cod);

   private:
    pnodoCiudad primero;
    pnodoCiudad actual;
};
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
		    cout << aux->codigo<<"~"<<aux->nombre<< "->";
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
            //cout<<"Codigo: "<<codI<<endl;
            aux=strtok(NULL, ";");
            string nom=aux;
            //cout<<"Nombre: "<<nom<<endl;
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
int main(){
    Ciudad ciudad;
    ciudad.agregarCiudades();
    cin.get();
    return 0;
}
