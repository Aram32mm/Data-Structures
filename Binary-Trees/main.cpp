 #include <cstddef>
#include <iostream>
#include <time.h>
#include <algorithm>
using namespace std;
#include "lista.h"
#include "hashtablevd.h"
#include "bst.h"


int main(int argc, char * argv[]) {
  LinkedList<BST<int>> bosque; // O(1)
  for(int i = 0; i < 10; i++){ // O(1)
    BST<int> arbol; // O(1)
    int cont = 0; // O(1)
    while(cont != 15){ // O(1)
      int n = rand()%99; // O(1)
      bool insertadoCorrecto = arbol.insert(n); // O(1)
      if(insertadoCorrecto){ // O(1)
        cont++; // O(1)
      }
    }
    bosque.addLast(arbol); //Añadimos a la LinkedList // O(1)
    cout<<i+1<<". "<<endl;
    arbol.InOrden();       //Imprimimos // O(1)
    cout<<endl; 
    arbol.balance();      //Si está balanceado o no // O(1)
    cout<<endl<<endl;
  }
  /*
  Profe, al final no pude sobrecargar el operador:(
  La sobrecarga para el BTS si está correctamente
  implementada, pero truena en la sobrecarga de lista.
  Si sabe cual es el error, estaría perfecto que me lo
  compartiera, de lo demás, muchas gracias por la ayuda.
*/
 // cout << bosque;

  
  



  

  


  



  


  
  

  
  
}
