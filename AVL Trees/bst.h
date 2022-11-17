#include <iostream>
using namespace std;

template <typename T> class Nodo {
private:
  T data;
  Nodo<T> *left;
  Nodo<T> *right;
  template <typename U> friend class BST;

public:
  Nodo(T data) {
    this->data = data;
    this->left = NULL;
    this->right = NULL;
  }
};

template <typename T> class BST;

template <typename T> 
ostream &operator<< (ostream &,  BST<T> &);

template <typename T> class BST {
private:
   Nodo<T> *root;

   /* Insertar un nuevo dato en el árbol
      Complejidad Total: Big O (log n)
      Cada vez que queremos insertar un elemento en el árbol, estamos diviendo a la mitad los datos 
      para encontrar la posición, esto por la naturaleza del comportamiento de un árbol bnario,por lo 
      que la complejidad queda como logaritmo 2 de N.
    */
  void insert(Nodo<T> *&nodo, T dato) {
    if (nodo == NULL) {
      nodo = new Nodo<T>(dato);
    } else {
      if (dato < nodo->data) {
        insert(nodo->left, dato);
        balanceo(nodo);
      } else if (dato > nodo->data) {
        insert(nodo->right, dato);
        balanceo(nodo);
      } else {
        
      }
    }
  }

  /* Recorrido del árbol In-Order
     Complejidad Total: Big O (n)
     Aunque hay recursión con complejidad O(log N), en realidad pues para imprimir todos los elementos del árbol 
     tenemos que recorrerlo por completo 
  */
  void inOrden(Nodo<T> *&nodo) {
    if (nodo != NULL) {
      inOrden(nodo->left);
      cout << "~ " << nodo->data << endl;
      inOrden(nodo->right);
    }
  }

  /* Recorrido del árbol Pre-Order
     Complejidad Total: Big O (n)
     Aunque hay recursión con complejidad O(log N), en realidad pues para imprimir todos los elementos del árbol 
     tenemos que recorrerlo por completo 
  */
  void preOrden(Nodo<T> * & nodo){
    if(nodo!= NULL){
      cout << "~ " << nodo->data << endl;
      preOrden(nodo->left);
      preOrden(nodo->right);
    
    }
  }
  
  /* Recorrido del árbol Post-Order
     Complejidad Total: Big O (n)
     Aunque hay recursión con complejidad O(log N), en realidad pues para imprimir todos los elementos del árbol 
     tenemos que recorrerlo por completo 
  */
  void postOrden(Nodo<T> * & nodo){
    if(nodo != NULL){
      postOrden(nodo->left);
      postOrden(nodo->right);
      cout << "~ " << nodo->data << endl;
    }
  }

  /* Verifica si el árbol contiene algún dato que queramos localizar
     Complejidad Total: Big O (log n)
     Al igual que la inserción, la localicación depende de log(n) búsquedas.
  */
  bool contains(Nodo<T> *&nodo, T dato) {
    if (nodo == NULL) {
      return false;
    } else if (dato < nodo->data) {
      return contains(nodo->left, dato);
    } else if (dato > nodo->data) {
      return contains(nodo->right, dato);
      } else {
      return true;
    }
  }

  /* Remueve algún dato del árbol 
     Complejidad Total: Big O (log n) 
     Al igual que la inserción y la localicación, depende de log(n) búsquedas.
  */
  bool remove(Nodo<T> *&nodo, T dato) {
    if (nodo == NULL) {
      return false;
    } else if (dato < nodo->data) {
      return remove(nodo->left, dato);
    } else if (dato > nodo->data) {
      return remove(nodo->right, dato);
    } else {
      if (nodo->left == NULL && nodo->right == NULL) {

        /*Borra nodo y regresa true*/
        delete nodo;
        nodo = NULL;
        return true;

      } else if (nodo->left && nodo->right == NULL) {

        Nodo<T> *left = nodo->left;
        Nodo<T> *temp = nodo;
        nodo = left;
        balanceo(nodo);
        delete temp;
        return true;
        /*
        Asigna a left el apuntador izquierdo del nodo.
        Asigna a temp el nodo.
        Asigna a nodo el left
        Borra temp y regresa true*/

      } else if (nodo->right && nodo->left == NULL) {
        Nodo<T> *right = nodo->right;
        Nodo<T> *temp = nodo;
        nodo = right;
        balanceo(nodo);
        delete temp;
        return true;
        /*
        Asigna a right el apuntador derecho del nodo.
        Asigna a temp el nodo.
        Asigna a nodo el right
        Borra temp y regresa true*/
      } else { // if (nodo->left &&  nodo->right) {
        /*
        Obtén el dato min con getMin del lado right.
        Asigna al nodo data el min.
        Llama a remove de lado right y buscando a min
        Regresa true*/
        T min = getMin(nodo->right);
        nodo->data = min;
        remove(nodo->right, min);
        balanceo(nodo);
        return true;
      }
    }
  }

  /* Localiza el dato más pequeño del árbol
     Complejidad: Big O(log n)
     Es logaritmo de N, por que tiene que recorrer solo la altura del árbol, esto por
     que se tiene que ir hasta el último nodo de la izquierda, ya que ahí se encuentra el árbol
  */
  T getMin(Nodo<T> *nodo) {
    if (nodo->left == NULL) {
      return nodo->data;
    } else {
      return getMin(nodo->left);
    }
  }

  /* Calcula la altura del árbol
     Complejidad: Big O (n)
     Al querer saber la altura del árbol, tenemos que visitar todas las ramas para asegurarnos
     de que encpntrar el último nodo y en base a esto calcular la altura.
  */
  int height(Nodo<T> *temp)
  {
    int h = 0;
    if (temp != NULL)
    {
      int l_height = height(temp->left);
      int r_height = height(temp->right);
      int max_height = max(l_height, r_height);
      h = max_height + 1;
    }
    return h;
  }

  /* Calcula el factor de balanceo del árbol
     Complejidad: Big O (n)
     Depende de la root y de la altura de sus nodos hijos, así que lo dejamos como 
     Big O(altura de nodos hijos)

  */
  int calcula_fe(Nodo<T> *temp)
  {
    int left_height = height(temp->left);
    int right_height = height(temp->right);
    int b_factor =  right_height - left_height;
    return b_factor;
  }

  /* Balancea el árbol en caso de ser necesario
     Complejidad: Big O (1)
     El balanceo actua de forma local con los nodos y sus operaciones son Big O(1)
  */
  void balanceo(Nodo<T> *&temp) {
    int bf = calcula_fe(temp);
  
    if (bf > 1) {
      int bf_hijo = calcula_fe(temp->right);
      
      if (bf_hijo < 0) {
        right_rotation(temp->right);
        left_rotation(temp);
      } else {
        left_rotation(temp);
      }
    }else if (bf < -1) {
       int bf_hijo = calcula_fe(temp->left);
      if (bf_hijo > 0) {
        left_rotation(temp->left);
        right_rotation(temp);
      } else {
        right_rotation(temp);
      }
    }
  }
  
  /* Rotación izquierda
     Complejidad: O (1)
  */
  void left_rotation(Nodo<T> * & nodo) {
    Nodo<T> *right = nodo->right;
    Nodo<T> * left = right->left;
    right->left = nodo;
    nodo->right = left;
    nodo = right; 
  }
  
  /* Rotación derecha
     Complejidad: O (1)
  */
  void right_rotation(Nodo<T> * & nodo) {
    Nodo<T> *left = nodo->left;
    Nodo<T> * right = left->right;
    left->right = nodo;
    nodo->left = right;
    nodo = left; 
  }

  /* Imprime
     Complejidad: Big O (n)
  */
  ostream & imprime(ostream &salida, Nodo<T> * &nodo)  {
    if (nodo != NULL) {
      imprime(salida, nodo->left);
      salida << nodo->data << " : ";
      cout << nodo->data << " : ";
      imprime(salida, nodo->right);
    }else{
      salida <<  " : ";
      return salida;
    }
    return salida;
  }

public:
  BST() { root = NULL; }

  friend ostream & operator<< <T>(ostream &,  BST<T> &);

  void inOrden() { inOrden(root); }

  void preOrden() { preOrden(root); }

  void postOrden() { postOrden(root); }

  void insert(T dato) {
    if (is_empty()) {
      root = new Nodo<T>(dato);
    } else {
      insert(root, dato);
    }
  }
  bool is_empty() { return (root == NULL) ? 1 : 0; }

  bool contains(T dato) { return contains(root, dato); }

  T getMin() { return getMin(root); }

  bool remove(T dato) { return remove(root, dato); }

  T getroot() const { return root->data; }

  int max(int a, int b) { return (a > b) ? a : b; }
};

template <typename T>
ostream &operator<<(ostream &salida,  BST<T> &lista) {
  return lista.imprime(salida, lista.root);
}