/*
Act 2.3 - Actividad Integral estructura de datos lineales

Integrantes:
Jose Aram Méndez Gómez - A01657142
Juan Francisco García Rodríguez - A01660981
Arturo Carballo Arias - A01662245

6 de octubre de 2022
*/

#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
using namespace std;
#include "lista.h"
#include "persona.h"
#include "ciudad.h"

#define NOMBRE_ARCHIVO "bitacora.csv"

using namespace std;

// Pide first_name e imprime la frecuencia con la que se repite
// Comnplejidad: O(N)
// Mejor Caso: O(N) 
// Caso Promedio: O(N)
// Peor Caso: O(N) 
// Debido a que tiene que medir la frecuencia, es necesario recorrer todo el arreglo para no dejar de lado ningún dato por lo que todos los casos caerían en O(N)
template <typename T, typename S>
int busquedaSecuencial(LinkedList<T> &lista, S busco)
{
  int frecuencia = 0; // 0(1)
  for (int i = 0; i < lista.size(); i++) // O(N)
  { 
    if (lista.get(i).getFirstname() == busco) // O(1)
    {               
      frecuencia++; // O(1)
    }
  }
  return frecuencia; // O(1)
}

// Muestra ordenada la lista ligada, utilizando el last_name como atributo para ordenar. ¿Qué método de ordenamiento utilizarás y por qué?
// Utilizamos QuickSort, por que es el algortimo de ordenamiento más eficiente que hay hasta la fecha, casi no hace intercambios de elementos innecesarios, es un algoritmo de ordenamiento en lugar, significa que no se necesita espacio de almacenamiento adicional para realizar el ordenamiento, y usa recursividad, lo cuál nos encanta a los programadores.
// Complejidad: O(N^2) en teoría, pero en práctica sería de O(N log N) 
// Mejor Caso: O(N log N)  // entre mejor pivote se tenga, es decir, que las particiones estén más balanceadas funcionará mejor
// Caso Promedio: O(N log N) 
// Peor Caso: O(N^2), este caso es sumamente improbabale que curiosamente lo tendríamos al intentar ordenar una lista ya ordenada.
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

// Implementa la búsqueda binaria para encontrar una persona, utilizando  el last_name como atributo para buscar.
// Complejidad: O(log N)
// Mejor Caso: O(1) El elemento buscado está en el centro
// Caso Promedio: O(log N/2) En promedio el elemento caerá en las zonas intermedias de entre la mitad a la esquina, siendo log(N/2)
// Peor Caso: O(log N) El elemento buscado está en una esquina, por lo que se necesita log(n) comparaciones
template <typename T, typename S>
int busquedaBinario(LinkedList<T> &lista, S busco)
{
  int lo = 0, mid, hi = lista.size() - 1; //O(1) 
  // necesitamos checar para mid=lo-(hi-lo)/2
  while (hi - lo > 1) //O(log N)
  {
    mid = (hi + lo) / 2; //O(log N)

    if (lista.get(mid) < busco) //O(1)
    {
      lo = mid + 1; //O(log N)
    }
    else //O(1)
    {
      hi = mid; //O(log N)
    }
  }

  if (lista.get(lo) == busco) //O(1)
  {
    cout << "Encontrado!" << endl; //O(1)
    return lo; //O(1)
  }
  else if (lista.get(hi) == busco) //O(1)
  {
    cout << "Encontrado!" << endl; //O(1)
    return hi; //O(1)
  }
  else //O(1)
  {
    cout << "No se ha encontrado :(" << endl; //O(1)
    return 0; //O(1)
  }
}

// Procesa los datos y crea una lista de ciudades con habitantes en orden 
// Complejidad: O(n) + O(n log(n)) = O(n log(n))
// Complejidad: O(n log(n))
// Mejor Caso: O(n log(n))
// Caso Promedio: O(n log(n))
// Peor Caso: O(n log(n))
//Como queremos checar por repetidos tenemos que recorrer todo el tamaño de la lista, por lo que no hay mejor ni peor caso.
void ciudades_Proceso(LinkedList<Ciudad> &lista)
{
  int primero = 0; //O(1)
  int ultimo = lista.size() - 1; //O(1)
  quickSort(lista, primero, ultimo); //O(N log N)
  for (int i = 0; i < lista.size(); i++) //O(N)
  {
    if (i == lista.size() - 1) //O(1)
    {
      break; //O(1)
    }
    else if (lista.get(i) == lista.get(i + 1)) //O(1)
    {
      Ciudad c = lista.get(i); //O(1)
      c++; //O(1)
      lista.set(i + 1, c); //O(1)
      lista.remove(i); //O(1)
      i--;
    }
  }
}

//¿Cuáles son las cinco ciudades con mayor número de personas registradas
// Complejidad: O(n) + O(n log(n)) + O(n log(n)) = O(n log(n))
// Mejor Caso: O(n log(n))
// Caso Promedio: O(n log(n))
// Peor Caso: O(n log(n))
void ciudadmax(LinkedList<Ciudad> &lista)
{
  ciudades_Proceso(lista); //O(n log(n))
  Ciudad mayores[5]; //O(1)
  for (int i = 0; i < 5; i++){ //O(1)
    Ciudad c, c0; //O(1)
    c0 = lista.get(0); //O(1)
    int index = 0; //O(1)
    for (int e = 0; e < lista.size(); e++) //O(N)
    {
      c = lista.get(e); //O(1)
      if (c0.getHabitantes() < c.getHabitantes()){ //O(1)
        c0 = c; //O(1)
        index = e; //O(1)
      }
    }
    mayores[i] = c0; //O(1)
    lista.remove(index); //O(1)
  }
  for (int i = 0; i < 5; i++){ //O(1)
    cout << mayores[i] << endl; //O(1)
    lista.addLast(mayores[i]); //O(1)
  }
  ciudades_Proceso(lista); //O(n log(n))
}

//¿Cuántos habitantes existen por ciudad?
// Complejidad: O(n log(n))
// Mejor Caso: O(n log(n))
// Caso Promedio: O(n log(n))
// Peor Caso: O(n log(n))
//Solo imprimimos la lista de la función por lo que sería O(1), pero al utilizar la función para odenar y quitar repetidos la complejidad total queda como O(n log(n)
void habitantes_Ciudad(LinkedList<Ciudad> &lista)
{
  ciudades_Proceso(lista); //O(n log(n))
  cout << lista; //O(1)
}


int main()
{
  LinkedList<Persona> personas;
  LinkedList<Ciudad> ciudades;
  
  // Abre el archivo
  ifstream archivo(NOMBRE_ARCHIVO);
  string linea;
  char delimitador = ',';

  // Leemos el encabezado
  getline(archivo, linea);

  // Procesa los datos
  while (getline(archivo, linea))
  {
    stringstream stream(linea); // Convertir la cadena a un stream
    string id, first_name, last_name, ZIP, city;
    getline(stream, id, delimitador);
    getline(stream, first_name, delimitador);
    getline(stream, last_name, delimitador);
    getline(stream, ZIP, delimitador);
    getline(stream, city, delimitador);

    int int_id = stoi(id);
    int int_zip = stoi(ZIP);
    personas.addLast(Persona(int_id, int_zip, first_name, last_name, city));
    ciudades.addLast(Ciudad(city));
  }
  archivo.close();
  /*
  //Probando la sobrecarga de operadores
  cout << personas;
  */
  /*
  //Probando el destructor
  personas.~LinkedList();
  */

  int opcion;

  cout << "BIENVENIDO A LA BASE DE DATOS DE PERSONAS" << endl << endl;
  do {
      cout << "Menú del sistema" << endl;
      cout << "1. Cinco ciudades con mayor número de personas registradas" << endl;
      cout << "2. Frecuencia con la que se repite un first name." << endl;
      cout << "3. Número de habitantes por ciudad." << endl;
      cout << "4. Lista ordenada por last name." << endl;
      cout << "5. Encontrar una persona por medio del last name." << endl;
      cout << "0. Salir del sistema." << endl << endl;
      cout << "Opción: ";
      cin >> opcion;
      switch (opcion) {
      case 1:
        {
          //1. ¿Cuáles son las cinco ciudades con mayor número de personas registradas? 
          cout << "\n CINCO CIUDADES CON MÁS HABITANTES \n"<<endl;
          ciudadmax(ciudades);
          break;
        }
      case 2:
        {
          //2. Da un first_name e imprime que tantas veces se repite ese nombre
          cout << "\n VECES QUE SE REPITE UN FIRST NAME \n"<<endl;
          string first_name;
          cout<< "Search for a first name: ";cin >> first_name;
          int i = busquedaSecuencial(personas,first_name);
          cout<< "El nombre " << first_name << " se repite " << i << " veces." << endl;
          break;
        }
      case 3:
        {
          //3. ¿Cuántos habitantes existen por ciudad? 
          cout << "\n TABLA DE HABITANTES/CIUDAD \n"<<endl;
          habitantes_Ciudad(ciudades);
          cout<< ciudades;
          break;
        }
      case 4:
        {
          //4.Muestra ordenada la lista ligada, utilizando el last_name como atributo para ordenar. ¿Qué método de ordenamiento utilizarás y por qué?
          cout << "\n TABLA ORDENADA POR LAST NAME \n"<<endl;
          quickSort(personas,0,(personas.size()-1));
          cout << personas;
          break;
        }
      case 5:
        {
          //5.Implementa la búsqueda binaria para encontrar una persona, utilizando  el last_name como atributo para buscar.
          cout << "\n BUSCA UN LAST NAME \n"<< endl;
          quickSort(personas, 0, (personas.size() - 1));
          string last_name;
          cout << "Search for a last name: "; cin >> last_name;
          int index = busquedaBinario(personas, last_name);
          while(personas.get(index) == personas.get(index-1))
          {
            index--;
          };
          int cont = index;
          while(personas.get(cont) == personas.get(cont+1))
          {
            cont++;
          };

          while(index != cont+1){
            cout << personas.get(index)<<endl;
            index ++;
          }
          break;
        }
      case 0:
        {
          break;
        }
      default:
          cout << "Opción no valida, intente de nuevo" << endl;
      }
      if (opcion != 0) {
          cout << endl << endl;
          cout << "Presione ENTER para continuar";
          cin.ignore();cin.ignore();
          cout << endl << endl;
      }  
  } while (opcion != 0);
  cout << endl << "Cerrando el sistema..." << endl;
  cout << "Gracias por usar el sistema." << endl << endl;
 
}