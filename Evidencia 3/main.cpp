#include <cstddef>
#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <string>
#include <algorithm>
using namespace std;
#include "lista.h"
#include "hashtable.h"
#include "persona.h"

#define NOMBRE_ARCHIVO "prueba.csv" //Prueba con csv prueba
// Error zsh killed con la base de datos bitacora, son demasiados datos
// Se necesita una compu más potente y métodos más eficientes

// 1)  Crea un censo poblacional de cada ciudad. Carga los datos en una hash table y desplegar todos los habitantes qué hay por ciudad.  
// Nota: sólo usar la tabla hash, para cargar la información.

// Complejidad: O(n) + O(Size*Tabla_size) + O(Size*Tabla_size) = O(Size*Tabla_size)
// Mejor Caso: O(1)
// Caso Promedio: O(Size*Tabla_size)
// Peor Caso: O(Size*Tabla_size)
// La complejidad total de esta función radica en el tamaño de la tabala con sus respectivos indices
void censoPoblacional(){
  Hashtable<string,int> censo; // O(1)

  // Abre el archivo
  ifstream archivo(NOMBRE_ARCHIVO); // O(1)
  string linea; // O(1)
  char delimitador = ','; // O(1)

  // Leemos el encabezado
  getline(archivo, linea); // O(1)

  // Procesa los datos
  while (getline(archivo, linea)) // O(N)
  {
    stringstream stream(linea); // Convertir la cadena a un stream // O(1)
    string id, first_name, last_name, gender, dob, phone, email, ZIP, city, state; // O(1)
    getline(stream, id, delimitador); // O(1)
    getline(stream, first_name, delimitador); // O(1)
    getline(stream, last_name, delimitador); // O(1)
    getline(stream, gender, delimitador); // O(1)
    getline(stream, dob, delimitador); // O(1)
    getline(stream, phone, delimitador); // O(1)
    getline(stream, email, delimitador); // O(1)  
    getline(stream, ZIP, delimitador); // O(1)
    getline(stream, city, delimitador); // O(1)
    getline(stream, state, delimitador); // O(1)
    if(censo.contains(city)){ // O(1)
      int cont = censo.get_or_default(city,0); // O(1)
      cont ++; // O(1)
      censo.put(city,cont); // O(1)

    }else{
      censo.put(city,1); // O(1)
    }
    
  
  }
  archivo.close(); // O(1)

  int opcion; // O(1)
  
  do { 
      cout << endl; // O(1)
      cout << "1. Ver todas las ciudades." << endl; // O(1)
      cout << "2. Ver las ciudades y el número de habitantes" << endl; // O(1)
      cout << "0. Regresar al Menú Principal." << endl << endl; // O(1)
      cout << "Opción: "; // O(1)
      cin >> opcion; // O(1)
      switch (opcion) {
      case 1:
        {
          cout << endl; // O(1)
          cout<<censo.keys(); // O(Size*Tabla_size)
          break;
        }
      case 2:
        {
          cout << endl; // O(1)
          censo.print(); // O(Size*Tabla_size)
          break;
        }
      case 0:
        {
          break; // O(1)
        }
      default:
          cout << "Opción no valida, intente de nuevo" << endl; // O(1)
      }
  } while (opcion != 0); // O(usuario) // O(1)
  cout << endl << "Regresando..." << endl; // O(1)
}

// 2)  Utilizando dos pilas para ordenar a todos los habitantes de acuerdo a su apellido o last_name.
//  Nota: sólo usar dos pilas, una para cargar la información y la segunda como auxiliar para ordenar. El resultado final queda en una de las pilas. NO usar algoritmos de ordenamiento.

// Complejidad: O(condicion*condicion) = O(N^2)
// Mejor Caso: O(1)
// Caso Promedio: O(condicion)
// Peor Caso: O(condicion)
Stack<Persona> sortStack(Stack<Persona> & input){
    Stack<Persona> tmpStack; //O(1)
    while (!input.SisEmpty()){ //O(condicion)
      Persona p = input.peek(); //O(1)
      string tmp = p.getName(); //O(1)
      input.pop(); //O(1)
      //mientras tmp no este vacio y el top element sea menor al temp
      while (!tmpStack.SisEmpty() && tmpStack.peek().getName() > tmp) { //O(condicion)
          input.push(tmpStack.peek()); //O(1)
          tmpStack.pop(); //O(1)
      }
      tmpStack.push(p); //O(1)
    }
    return tmpStack; //O(1)
}

// 3) Con una fila priorizada, debes imprimir a todos los habitantes utilizando el valor de ZIP y la prioridad menor. 
// Nota: sólo usar una fila priorizada. El resultado final queda en la fila priorizadas y se imprime en consola.

// Complejidad: O(N) * (O(N)+O(N)) = O(N^2)
// Mejor Caso: O(1)
// Caso Promedio: O(N^2)
// Peor Caso: O(N^2)
template<typename T>
Queue<T> sortQueue(Queue<T> & input){
  int n = input.sizeQ(); //O(1)
  for(int i = 1; i <= n;i++){ // O(N)
    int min_index = input.minByIndex(n-i); // O(N)
    input.insertMinAtras(min_index); // O(N)
  }
  return input; //O(1)
}




int main(int argc, char**argv) {
  Stack<Persona> StackHabitantes; 
  Queue<Persona> QueueHabitantes;

  // Abre el archivo
  ifstream archivo(NOMBRE_ARCHIVO);
  string linea;
  char delimitador = ',';

  // Leemos el encabezado
  getline(archivo, linea);
  int numeroHabitantes;

  // Procesa los datos
  while (getline(archivo, linea))
  {
    stringstream stream(linea); // Convertir la cadena a un stream
    string id, first_name, last_name, gender, dob, phone, email, ZIP, city, state;
    getline(stream, id, delimitador);
    getline(stream, first_name, delimitador);
    getline(stream, last_name, delimitador);
    getline(stream, gender, delimitador);
    getline(stream, dob, delimitador);
    getline(stream, phone, delimitador);
    getline(stream, email, delimitador);        
    getline(stream, ZIP, delimitador);
    getline(stream, city, delimitador);
    getline(stream, state, delimitador);

    Persona p(stoi(id), first_name, last_name, gender, dob, phone, email,
              stoi(ZIP), city, state);

    StackHabitantes.push(p);
    QueueHabitantes.enqueue(p);
  
  }
  archivo.close();

  
  

  int opcion;
  cout << "\nBIENVENIDO A LA BASE DE DATOS POBLACIONAL\n" << endl ;
  do {
      cout << "MENÚ" << endl<<endl;
      cout << "1. Censo poblacional de cada ciudad" << endl;
      cout << "2. Habitantes de acuerdo a su apellido o last_name." << endl;
      cout << "3. habitantes utilizando el valor de ZIP y la prioridad menor." << endl;
      cout << "0. Salir del sistema." << endl << endl;
      cout << "Opción: ";
      cin >> opcion;
      switch (opcion) {
      case 1:
        {
          //1. Crea un censo poblacional de cada ciudad. 
          censoPoblacional();
          
          break;
        }
      case 2:
        {
          cout << endl;
          //2. Ordena a todos los habitantes de acuerdo a su apellido o last_name.
          cout << sortStack(StackHabitantes);
          
          break;
        }
      case 3:
        {
          cout << endl;
          //3. Con una fila priorizada, imprime a todos los habitantes utilizando el valor de ZIP y la prioridad menor. 
          cout<< sortQueue(QueueHabitantes);
          break;
        }
      case 0:
        {
          break;
        }
      default:
          cout << endl;
          cout << "Opción no valida, intente de nuevo" << endl;
      }
      if (opcion != 0 && opcion != 1) {
          cout << endl;
          cout << "Presione ENTER para continuar";
          cin.ignore(); cin.ignore();
          cout << endl<<endl;
      }  
  } while (opcion != 0);
  cout << endl << "Cerrando el sistema..." << endl;
  cout << "GRACIAS." << endl << endl;


}
