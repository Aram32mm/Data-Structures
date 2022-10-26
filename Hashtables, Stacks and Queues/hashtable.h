#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "lista.h"
#include <algorithm>
#include <string>
#include <cmath>
template <typename T>
void quickSort(LinkedList<T> &lista, int primero, int ultimo)
{
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

template <typename K, typename T> /* K key, T value*/
class HashPair {
public:
  K key;
  T value;
  HashPair(K key, T value) {
    this->key = key;
    this->value = value;
  }
  HashPair() {}
};

template <typename K, typename T> 
class Hashtable {
private:
  int numElemnts;

  int size; //numero de casillas para guardar llaves

  LinkedList<HashPair<K, T> *> *tabla; //puntero a dichas casillas

  int fh(K key) const { //Función Hash perfecta para strings
    hash<K> khash;
    int preHash = 0;
    for(int i = 0; i < key.length(); i++) {
      preHash += pow(31, i) * key[i];
    } 

    return khash(key) % size; 
  }

public:
  Hashtable(int size = 50000) {
    this->size = size;
    numElemnts = 0;
    tabla = new LinkedList<HashPair<K, T> *>[size];
    for (int i = 0; i < size; i++)
      tabla[i] = LinkedList<HashPair<K, T> *>();
  }

  bool put(K key, T value) {
    int posicion = fh(key);
    LinkedList<HashPair<K, T> *> lista = tabla[posicion];
    int indice = -1;
    for (int i = 0; i < lista.size(); i++) {
      if (lista.get(i)->key == key) {
        indice = i;
      }
    }
    if(indice >= 0) {
      lista.get(indice)->value = value;
    }else{
      tabla[posicion].addLast(new HashPair<K, T>(key, value));
      numElemnts++;
    }
    return (indice >= 0) ? 0 : 1;
  }

  //Función miembro. Devuelve el valor asociado a la llave key de esta tabla hash. Si key no existe en la tabla devuelve default_value.
  // Complejidad: O(N)
  // Mejor Caso: O(1)
  // Caso Promedio: O(n)
  // Peor Caso: O(n)
  //Para obtener un valor se tiene que checar si está, por lo que tiene que recorrer todas las posiciones
  T get_or_default(K key, const T default_value) const {
    int posicion = fh(key); // O(1)
    LinkedList<HashPair<K,T>*> lista = tabla[posicion]; // O(1)
    int i=0; // O(1)
    for (int i = 0; i < lista.size(); i++) { // O(N)
      if (lista.get(i)->key == key) // O(1)
        return lista.get(i)->value; // O(1)
    }
    return default_value; // O(1)
  }

  //Función miembro. Devuelve true si esta tabla hash está vacía, o false en caso contrario.
  bool contains(K key) const {
    int posicion = fh(key);
    LinkedList<HashPair<K, T> *> lista = tabla[posicion];
    int indice = -1;
    for (int i = 0; i < lista.size(); i++) {
      if (lista.get(i)->key == key) {
        indice = i;
      }
    }
    return (indice == -1) ? 0 : 1;
  }

  // Función miembro. Devuelve un vector con todas las llaves de esta tabla hash ordenadas de manera ascendente. Se puede usar la función std:sort para ordenar el vector resultante.
  // Complejidad: O(Size*Tabla_size) + O(N logN) = O(Size*Tabla_size)
  // Mejor Caso: O(1)
  // Caso Promedio: O(Size*Tabla_size)
  // Peor Caso: O(Size*Tabla_size)
  //Para obtener las llaves tenemos que recorrer las llaves y las posiciones
  LinkedList<K> keys() const{
    LinkedList<K> vkr; // O(1)
    for (int i = 0; i < size; i++) { // O(size)
      for(int j = 0; j < tabla[i].size(); j++){ // O(tabla size)
        K k = tabla[i].get(j)->key;
        if (!vkr.contains(k)) // O(1)
          vkr.addLast(k); // O(1)
      }    
    }
    quickSort(vkr,0,vkr.size()-1); //O(N log N
    return vkr; // O(1)
  }

  //Función miembro. Devuelve el valor asociado a la llave key de esta tabla hash. Si key no existe en la tabla devuelve default_value.
  // Complejidad: O(N)
  // Mejor Caso: O(1)
  // Caso Promedio: O(n)
  // Peor Caso: O(n)
  //Para remover un valor se tiene que checar si está, por lo que tiene que recorrer todas las posiciones
  bool remove(K key){
    int posicion = fh(key); // O(1)
    LinkedList<HashPair<K, T> *> lista = tabla[posicion]; // O(1)
    int indice = -1; // O(1)
    for (int i = 0; i < lista.size(); i++) { // O(N)
      if (lista.get(i)->key == key) { // O(1)
        indice = i; // O(1)
      }
    }
    if(indice >= 0) { // O(1)
      cout << "Llave encontrada."<<endl; // O(1)
      tabla[posicion].remove(indice); // O(1)
      numElemnts--; // O(1)
    }else{ // O(1)
      cout << "Llave no encontrada."<<endl; // O(1)
    }
    return (indice >= 0) ? 1 : 0; // O(1)
  }

  //Función miembro. Devuelve el número de elementos (parejas de llave/valor) contenidos en esta tabla hash.
  //Función miembro. Devuelve el valor asociado a la llave key de esta tabla hash. Si key no existe en la tabla devuelve default_value.
  // Complejidad: O(1)
  // Mejor Caso: O(1)
  // Caso Promedio: O(1)
  // Peor Caso: O(1)
  int sizeK() {
    return numElemnts; // O(1)
  }

  // Función miembro. Devuelve un vector con todas las llaves de esta tabla hash ordenadas de manera ascendente. Se puede usar la función std:sort para ordenar el vector resultante.
  // Complejidad: O(Size*Tabla_size) + O(N logN) = O(Size*Tabla_size)
  // Mejor Caso: O(1)
  // Caso Promedio: O(Size*Tabla_size)
  // Peor Caso: O(Size*Tabla_size)
  //Para obtener las llaves tenemos que recorrer las llaves y las posiciones 
  void print(){
          for(int i =0; i < size; i++){ // O(size)
            for(int j =0; j < tabla[i].size(); j++){ // O(tabla size)
              cout <<"Idx(FH):" <<i << " | " << tabla[i].get(j)->key  << " -> " << tabla[i].get(j)->value<<" | "<<endl; // O(1)
            }
          }
      }
};
#endif
