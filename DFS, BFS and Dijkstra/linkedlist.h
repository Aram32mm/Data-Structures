#pragma once
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

template <typename T> class Node {
private:
  T data;
  Node<T> *next;
  Node<T> *previous;
  template <typename U> friend class LinkedList;

public:
  Node(T data, Node<T> *next, Node<T> *previous) {
    this->data = data;
    this->next = next;
    this->previous = previous;
  }
};

template <typename T> class LinkedList;

template<typename T>
ostream & operator<< (ostream &, const LinkedList<T> &);

template <typename T> class LinkedList {
private:
  Node<T> *head;
  Node<T> *last;
  int _size;

public:
  LinkedList() {
    head = last = NULL;
    _size = 0;
  }

friend ostream & operator<< <T>(ostream &, const LinkedList<T> &);
  /*
  Método para agregar un nodo al inicio de la lista.
  Complejidad: O(1)
  */
  void addFirst(T dato) {
    _size++;
    // SORT the code:
    Node<T> *nuevo = new Node<T>(dato, NULL, NULL);
    if (head == NULL && last == NULL) { // si es vacía la lista
      head = last = nuevo;
    } else {
      nuevo->next = head;
      head->previous = nuevo;
      head = nuevo;
    }
  }
  /*
  Método imprime todos los nodos de la lista
  */
  void print() {
    Node<T> *aux = head;
    while (aux != NULL) {
      cout << aux->data << endl;
      aux = aux->next;
    }
  }
  /*
  Método imprime todos los nodos de la lista
  Complejidad: O(N)
  */
  void reverse() {
    Node<T> *aux = last;
    while (aux != NULL) {
      cout << aux->data << endl;
      aux = aux->previous;
    }
  }

  /*
  Método que regresa 1, si la lista no tiene elementos.
  Complejidad: O(1)
  */
  bool is_empty() { return (head == NULL) ? true : false; }
  /*
  Método para agregar un nodo al final de la lista.
  Complejidad: O(1)
  */
  void addLast(T dato) {
    _size++;
    Node<T> *nuevo = new Node<T>(dato, NULL, NULL);
    if (is_empty()) {
      head = last = nuevo; // addFirst(dato)
    } else {
      last->next = nuevo;
      nuevo->previous = last;
      last = nuevo;
    }
  }
  /*
  Método para calcular el tamaño de la lista, cuántos elementos tenemos.
  Complejidad: O(1)
  */
  int size() const { return this->_size; }

  /*
  Método para revisar si existe un elemento, regresa 1 si existe o 0 sino
  existe.
  Complejidad: O(N)
  */
  bool contains(T data) {
    Node<T> *temp = head;
    bool exists = 0;
    while (temp != NULL && exists == 0) {
      if (data == temp->data) {
        exists = 1;
      }
      temp = temp->next;
    }
    return exists;
  }

  /*
  Método para obtener un elemento que se encuentra en una posición: "index".
  Si index es menor a 0 o mayor al tamaño se lanza exception.
  Complejidad: O(Index)
  */
  T get(int index) const{
    if (index < 0 || index > size())
      throw -1;
    Node<T> *temporal = head;
    for (int i = 0; i < index; i++) {
      temporal = temporal->next;
    }
    return temporal->data;
  }
  //Complejidad: O(Index)
  void get(int index, T dato) const{
    if (index < 0 || index > size())
      throw -1;
    Node<T> *temporal = head;
    for (int i = 0; i < index; i++) {
      temporal = temporal->next;
    }
    temporal->data = dato;
  }

  /*
  Método para remover de la lista el primer elemento, si la lista NO es vacía
  se puede realizar. 
  Complejidad: O(1)
*/
  T remove_front() {
    if (is_empty()) {
      throw -1;
    } else if (head == last) {
      // 1 nodo
      T dato = head->data; // sacar dato
      delete head;         // borrar nodo
      head = last = NULL;
      _size--;
      return dato;
    } else {
      // minimo 2 nodos
      T dato = head->data;
      head = head->next;
      delete head->previous;
      head->previous = NULL;
      _size--;
      return dato;
    }
  }

  /*
  Método para remover de la lista el último elemento, si la lista NO es vacía
  se puede realizar. 
  Complejidad: O(1)
*/
  T remove_last() {
    if (is_empty()) {
      throw -1;
    } else if (head == last) {
      // 1 nodo
      T dato = head->data; // sacar dato
      delete head;         // borrar nodo
      head = last = NULL;
      _size--;
      return dato;
    } else {
      // minimo 2 nodos
      T dato = last->data;
      last = last->previous;
      //delete last->next;
      last->next = NULL;
      _size--;
      return dato;
    }
  }

  /*
  Obtiene el dato guardado en el último nodo
  Complejidad: O(1)
  */
  T getFirst() {
    if (is_empty()) {
      throw 1;
    }
    return head->data;
  }

  /*
  Obtiene el dato guardado en el último nodo
  Complejidad: O(1)
  */
  T getLast() {
    if (is_empty()) {
      throw 1;
    }
    return last->data;
  }

  /*
  Método para remover de la lista el último elemento, si la lista NO es vacía
  se puede realizar. 
  Complejidad: O(Index)*/
  T remove(int index) {
    if (is_empty()) {
      throw -1;
    } else if (index == 0) {
      return remove_front();
    } else if (index == _size-1) {
      return remove_last();
    } else {
      Node<T> *aux = head;
      for (int i = 0; i < index; i++)
        aux = aux->next;
      // minimo 2 nodos
      T dato = aux->data;
      aux->previous->next = aux->next;
      aux->next->previous = aux->previous;
      aux->next = NULL;
      aux->previous = NULL;
      delete aux;
      _size--;
      return dato;
    }
  }
  //Complejidad: O(Index)
  void insert(T dato, int index) {
    if (is_empty()) {
      throw -1;
    } else if (index < 0 && index > _size) {
      throw -1;
    } else {
      Node<T> *aux = head;
      for (int i = 0; i < index; i++)
        aux = aux->next;
      // minimo 2 nodos
      Node<T> *n = new Node<T>(dato, NULL, NULL);
      n->next = aux;
      n->previous = aux->previous;
      aux->previous = n;
      n->previous->next = n;
      _size++;
      return dato;
    }
  }
  //Complejidad: O(Index)
  void set (int index, T dato) const{
    if (index < 0 || index > size())
      throw -1;
    Node<T> *temporal = head;
    for (int i = 0; i < index; i++) {
      temporal = temporal->next;
    }
    temporal->data = dato;
  }
};

//Complejidad: O(N)
template<typename T>
ostream & operator<< (ostream & salida, const LinkedList<T> & lista){
      for( int  i = 0 ; i < lista.size(); i++){
        salida << lista.get(i) << " | ";
      }
  return salida;
} 
    
template <typename T> class Stack : public LinkedList<T> {
public:
  Stack() : LinkedList<T>() {}
  //Complejidad: O(1)
  void push(T dato){
    LinkedList<T>::addLast(dato);
  }
  //Complejidad: O(1)
  T pop(){
  return LinkedList<T>::remove_last();
}
  //Complejidad: O(1)
  T peek(){
  return LinkedList<T>::getLast();
}
};

template <typename T> class Queue : public LinkedList<T> {
public:
  Queue() : LinkedList<T>() {}
  //Complejidad: O(1)
  void enqueue(T dato){
    LinkedList<T>::addLast(dato);
  }
  //Complejidad: O(1)
  T dequeue(){
  return LinkedList<T>::remove_front();
}
  //Complejidad: O(1)
  T peek(){
  return LinkedList<T>::getFirst();
}
  //Complejidad: O(N)
  int getMax(){
  T maximoDecimusMeridious = LinkedList<T>::getFirst();
  int posicion = 0;
  for(int i = 0; i < LinkedList<T>::size(); i++ ){
    if( LinkedList<T>::get(i) > maximoDecimusMeridious ){
        maximoDecimusMeridious = LinkedList<T>::get(i);
        posicion = i;
      }
    }
  
  return posicion;
}
  //Complejidad: O(N)
  int getMin(){
  T minimunDecimusMeridious = LinkedList<T>::getFirst();
  int posicion = 0;
  for(int i = 0; i < LinkedList<T>::size(); i++ ){
    if( LinkedList<T>::get(i) < minimunDecimusMeridious ){
        minimunDecimusMeridious = LinkedList<T>::get(i);
        posicion = i;
      }
    }
  return posicion;
}
  //Complejidad: O(N)
  T dequeueMax(){
  return LinkedList<T>::remove(getMax());
}
  //Complejidad: O(N)
  T peekMax(){
  return LinkedList<T>::get(getMax());
}
  //Complejidad: O(N)
  T dequeueMin(){
  return LinkedList<T>::remove(getMin());
}
  //Complejidad: O(N)
  T peekMin(){
  return LinkedList<T>::get(getMin());
}
};

#endif
