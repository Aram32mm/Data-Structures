#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include <cctype>
#define NOMBRE_ARCHIVO "marvel-wikia-data.csv"

using namespace std;

//Ordene afabeticamente la información por nombre para realizar las búsquedas: Usa bubble sort
template <typename T>
void bubbleSort(T arreglo[], int size)
{
    int i, j;
    T aux;

    for(i = 0; i<size; i++){
        for(j = i+1; j<size; j++){
    
            if(arreglo[i] > arreglo[j]){
                aux = arreglo[i];
                arreglo[i] = arreglo[j];
                arreglo[j] = aux;
            }
        }
    }

    for(int i = 0; i<size; i++){
        cout << arreglo[i] << endl;
    }
}

//Solicite al usuario letra de inicio de búsqueda de información: Usa búsqueda secuencial
void busquedaSecuencial(string arreglo[], int size, string inicial)
{
    string s = "Superhéroe[";
    string final = "]_CSV.csv";
    string nombre = s+inicial+final;
    //Almacenar en un archivo el resultado del ordenamiento.
    ofstream file(nombre);
    for(int i = 0; i<size; i++){
        if(arreglo[i].substr(0, 1)==inicial){
        file << arreglo[i] << endl;
        cout << arreglo[i]<<endl;
        }

    }  
    file.close();  
}

//Función que abre el archivo y cuenta cuantos datos hay(cuantas filas hay)
int tamaño(){
    ifstream archivo(NOMBRE_ARCHIVO);
    string linea;

    int tamaño = 0;

    while(getline(archivo,linea)){
        tamaño++; 
    }
    archivo.close();

    return tamaño-1;

}



int main(){
    //Abra el archivo de entrada llamado "bitacora.txt (Enlaces a un sitio externo.)" 
    ifstream archivo(NOMBRE_ARCHIVO);
    string linea;
    char delimitador = ',';

    getline(archivo,linea);

    int nPersonajes = tamaño();
    
    //creación de un arreglo dinámico 
    string *personaje;
    personaje = new string[nPersonajes];

    int i =0;

    //revisa los datos sólo utilizarás la columna de "name"
    while(getline(archivo,linea)){ 

        stringstream stream(linea);
        string pelicula, año,todo;

        getline(getline(stream,año,delimitador),pelicula,delimitador);

        *(personaje+i) = pelicula;
        i++;

    }
    
    cout<<"\nOrdenamiento\n"<<endl;
    bubbleSort<string>(personaje, nPersonajes);

    cout<<"\nBúsqueda de Superheroes\n"<<endl;
    string n ;
    cout<<"Ingrese una letra[mayúscula]: "; cin >> n;
    cout << endl;
    
    busquedaSecuencial(personaje,nPersonajes,n);
    
    delete[] personaje;

    archivo.close();
    

    return 0;
}