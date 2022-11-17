#include <cstddef>
#include <iostream>
#include <time.h>
#include <algorithm>
#include <sstream>
#include <fstream>
#define NOMBRE_ARCHIVO "bitacora.csv"
using namespace std;
#include "bst.h"

int main(int argc, char * argv[]) { 
  BST<string> ciudades;

  // Abre el archivo
  ifstream archivo(NOMBRE_ARCHIVO);
  string linea;
  char delimitador = ',';

  // Leemos el encabezado
  getline(archivo, linea);

  // Procesa los datos
  while (getline(archivo, linea)) // Big O (n)
  {
    stringstream stream(linea); 
    string id, first_name, last_name, ZIP, city;
    getline(stream, id, delimitador);
    getline(stream, first_name, delimitador);
    getline(stream, last_name, delimitador);
    getline(stream, ZIP, delimitador);
    getline(stream, city, delimitador);

    ciudades.insert(city);
  }
  archivo.close();

  ciudades.inOrden();

  cout << endl << "Root: " << ciudades.getroot() << endl;
  
  //Ejemplo de funcionamiento de método Remove
  ciudades.remove(ciudades.getroot());
  cout << endl << "Root: " << ciudades.getroot() << endl;
}