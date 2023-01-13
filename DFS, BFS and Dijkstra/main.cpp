#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <cmath>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <vector>
using namespace std;
#include "tablahash.h"
#include "linkedlist.h"
#include "grafo.h"


#define NOMBRE_ARCHIVO "marvel_clean.csv"

// Complejidad: O(N)  
UnorderedMap< string, Vertex<string> > graph_from_file(){
  ifstream archivo(NOMBRE_ARCHIVO);
  string linea;
  char delimitador = ';';

  getline(archivo, linea);
  
  UnorderedMap< string,  Vertex<string> > grafo;

  while (getline(archivo, linea))
  {
    stringstream stream(linea); // Convertir la cadena a un stream
    string hero1, hero2, friendship;
    getline(stream, hero1, delimitador);
    getline(stream, hero2, delimitador);
    getline(stream, friendship, delimitador);

    double cost = stod(friendship);
    grafo.addEdge(hero1, Vertex<string>(hero2,cost));
  }
  archivo.close();

  return grafo;
}

// QuickSort
// Complejidad: O(N^2) en teoría, pero en práctica sería de O(N log N) 
template <typename T>
void quickSort(LinkedList<T> &lista, int primero, int ultimo){
  // inicializamos nuestras variables
  int i, j, central; // O(1)
  T pivote; // O(1)

  i = primero; // O(1)
  j = ultimo; // O(1)

  central = (primero + ultimo) / 2; //O(log N)  // calculamos la posicion central
  pivote = lista.get(central);     // O(1)  // encontramos nuestro valor pivote
  do
  {
    while (lista.get(i) < pivote) // O(CONDICION)
      i++; // O(1) // mientras sea menor que el pivote lo saltamos
    while (lista.get(j) > pivote) // O(CONDICION)
      j--; // O(1) // mientras sea menor que el pivote lo saltamos

    if (i <= j) // O(1)
    { // si i es mayor j quiere decur que nos pasamos, mientras tanto ...
      T dato = lista.get(i); // O(1)
      lista.set(i, lista.get(j)); // O(1)
      lista.set(j, dato); // O(1)
      i++; // O(1) // aumentamos el contador
      j--; // O(1) // aumentamos el contador
    }

  } while (i <= j); //O(N)  // cuando el i y el j se crucen se termina el bucle

  if (primero < j) // O(1)
  {                               
    quickSort(lista, primero, j); //O(N log N)  // recursión
  }
  if (i < ultimo) // O(1)
  {
    quickSort(lista, i, ultimo);//O(N log N)  // recursión
  }
}

  
int main() {
  
  UnorderedMap <string,  Vertex<string> > grafo = graph_from_file();

  //sort con quicksort y linkedlists
  LinkedList<Hero> ll_heroes = grafo.heroes_ll();
  quickSort(ll_heroes,0,ll_heroes.size()-1);
  
  int opcion;

  cout << "BIENVENIDO A LA BASE DE DATOS DE SUPERHEROES" << endl << endl;
  do {
      cout << "Menu del sistema" << endl;
      cout << "1. Personajes del universo Marvel con mas y menos conexiones." << endl;
      cout << "2. Recorridos de anchura y profundidad de un personaje a otro." << endl;
      cout << "3. Prunning del grafo (personajes con menos de n conexiones)." << endl;
      cout << "4. Recorrido de Dijsktra de un personaje a otro." << endl;
      cout << "5. Top 10 influencers del universo Marvel (con más conexiones)." << endl;
      cout << "0. Salir del sistema." << endl << endl;
      cout << "Opcion: ";
      cin >> opcion;
      switch (opcion) {
      case 1:
        {
      
          cout << "\nPERSONAJES DEL UNIVERSO MARVEL CON MAS Y MENOS CONEXIONES.\n"<<endl;
          cout << "Personaje con menos conexiones: " << ll_heroes.getFirst() << endl;
          cout << "Personaje con mas conexiones: " << ll_heroes.getLast();
          break;
        }
        
      case 2:
        {

          cout << "\nRECORRIDOS DE ANCHURA Y PROFUNDIDAD DE UN PERSONAJE A OTRO\n"<<endl;
          string inicio, final;
          cout << "Introduza el personaje donde desea iniciar: "; getline(cin >> ws, inicio);
          cout << "Introduza el personaje donde desea terminar: "; getline(cin >> ws, final);

          cout << "\n   Recorrido de profundidad  \n"<<endl;
          grafo.df_search(inicio, final);
          cout << "\n   Recorrido de anchura  \n"<<endl;
          grafo.bf_search(inicio, final);
          break;
        }
      case 3:
        {
          
          int conexiones;
          cout << "\nPRUNNING DEL GRAFO\n"<<endl;
          cout << "Introduce el numero de conexiones: "; cin >> conexiones;
          grafo.prunning(conexiones);
          cout << endl << "Prunning realizado exitosamente!" <<endl;
          break;
        }
      case 4:
        {

          cout << "\n RECORRIDO DE DIJSKTRA DE UN PERSONAJE A OTRO \n"<<endl;
          string inicio, final;
          cout << "Introduza el personaje donde desea iniciar: "; getline(cin >> ws, inicio);
          Vertex<string> source(inicio,0);
          cout << "Introduza el personaje donde desea terminar: "; getline(cin >> ws, final);

          double pathValue = grafo.dijkstra(source,final);
          
          if (  pathValue > 0){
            cout << "El camino más corto entre " << inicio << " y " << final << " tiene un valor de " << pathValue << ". "<<endl;
          } else if( inicio == final){
            cout << "No hay recorrido, son el mismo"<<endl;
          } else {
            cout << "No hay camino disponible entre ambos personajes"<<endl;
          }
          
          break;
        }
      case 5:
        {
          
          cout << "\n TOP 10 INFLUENCERS DEL UNIVERSO MARVEL \n"<< endl;
          int size = ll_heroes.size();
          for (int i = size - 1; i > size - 11; i--){
            cout << ll_heroes.get(i) << endl;
          }
          break;
        }
      case 0:
        {
          break;
        }
      default:
          cout << "Opcion no valida, intente de nuevo" << endl;
      }
      if (opcion != 0) {
          cout << endl << endl << "Presione ENTER para continuar";
          cin.ignore(); cin.ignore();
          cout << endl << endl;
      }  
  } while (opcion != 0);
  cout << endl << "Cerrando la base de datos..." << endl;
  cout << "GRACIAS." << endl << endl;

}