#include "cstdlib"
template<typename T>
class Nodo{
    private:
        T data;
        Nodo<T>* left;
        Nodo<T>* right;
        template<typename U>
        friend class BST;
    public:
        Nodo(T data){
            this->data = data;
            this->left = NULL;
            this->right = NULL;
        }
};


template<typename T>
class BST;

template <typename T> 
ostream &operator<< (ostream &,  BST<T> &);

template<typename T>
class BST{
  private:
    Nodo<T> * root;

    // Complejidad: O(N) 
    // Mejor Caso: O(1) 
    // Caso Promedio: O(N) 
    // Peor Caso: O(N)
    // Para insertar depende del arbol y sus valores 
    bool insert(Nodo<T> * & nodo, T dato){
      if (nodo == NULL){ 
        nodo = new Nodo<T>(dato);
        return true;
      }else{
        if(dato < nodo->data){
          return insert( nodo->left, dato );
        }else if(dato > nodo->data){
          return insert( nodo->right, dato );
        }else{
          //cout << dato << " repetido." << endl; 
          return false;
        }
      } 
    }

    //TODAS LAS IMPRESIONES SON
    // Complejidad: O(N) 
    // Mejor Caso: O(1) 
    // Caso Promedio: O(N) 
    // Peor Caso: O(N)
    void InOrden(Nodo<T> * & nodo){
      if(nodo != NULL){
        InOrden(nodo->left);
        cout <<" | "<< nodo->data <<" | ";
        InOrden(nodo->right);
      }
    } 

    void PreOrden(Nodo<T> * & nodo){
      if(nodo != NULL){
        cout << nodo->data <<" | ";
        PreOrden(nodo->left);
        PreOrden(nodo->right);
      }
    }

    void PostOrden(Nodo<T> * & nodo){
      if(nodo != NULL){
        PostOrden(nodo->left);
        PostOrden(nodo->right);
        cout << nodo->data <<" | ";
      }
    }

    // Complejidad: O(N) 
    // Mejor Caso: O(1) 
    // Caso Promedio: O(N) 
    // Peor Caso: O(N)
    // Para verificar tendría que checar todos los nodos
    bool contains(Nodo<T> * & nodo, T dato){
      if (nodo == NULL){
        return false;
      }else if(dato < nodo->data){
        return contains(nodo->left,dato);
      }else if(dato > nodo->data){
        return contains(nodo->right,dato);  
      }else{
          return true;
        }
    }

    // Complejidad: O(N) 
    // Mejor Caso: O(1) 
    // Caso Promedio: O(N) 
    // Peor Caso: O(N)
    //Para el tamaño total se tiene que recorrer todo el arbol
    int size(Nodo<T> * & nodo){
      if(nodo == NULL){
         return 0;
      }else{
	      return 1 + size(nodo->left) + size(nodo->right);
      }
    }

    // Complejidad: O(Height) 
    // Mejor Caso: O(1) 
    // Caso Promedio: O(Height) 
    // Peor Caso: O(Height)
    // El peor caso pasaría con arboles desbalanceados hacia la derecha
    T max(Nodo<T> * & nodo){
      if (nodo -> right == NULL){
        return nodo->data;
      }else{
        return max(nodo->right);
      }
    }

    // Complejidad: O(Height) 
    // Mejor Caso: O(1) 
    // Caso Promedio: O(Height) 
    // Peor Caso: O(Height)
    // El peor caso pasaría con arboles desbalanceados hacia la izquierda
    T min(Nodo<T> * & nodo){
      if (nodo -> left == NULL){
        return nodo->data;
      }else{
        return min(nodo->left);
      }
    }

    // Complejidad: O(N) 
    // Mejor Caso: O(1) 
    // Caso Promedio: O(N) 
    // Peor Caso: O(N)
    //Para el height total se tiene que recorrer todo el arbol
    bool remove(Nodo<T >* & nodo, T dato) { 
      if(nodo == NULL){
        return false;
      }else if (dato < nodo->data) { 
        return remove(nodo->left, dato);    
      }else if (dato > nodo->data) { 
        return remove(nodo->right, dato);   
      }else {    
        if(nodo->left == NULL && nodo->right == NULL){ 
          // Borra nodo y regresa true
          delete nodo;
          nodo = nullptr;
          return true;
          
        }else if(nodo->left && nodo->right == NULL){
          /*Obtén el left de nodo. Asigna a temp el nodo. 
          Asigna a nodo el left. Borra temp y regresa true*/
          Nodo<T>* temp = nodo;
          nodo = nodo->left;
          delete temp;
          return true;
         
        }else if(nodo->right && nodo->left == NULL){
          /*Obtén el right de nodo. Asigna a temp el nodo.
          Asigna a nodo el right. Borra temp y regresa true*/
          Nodo<T>* temp = nodo;
          nodo = nodo->right;
          delete temp;
          return true;
          
        }else { //if (nodo->left &&  nodo->right)
          /*Obtén el dato min con getMin del lado right.
          Asigna al nodo data el min.
          Llama a remove de lado right y buscando a min
          Regresa true*/
          nodo->data = min(nodo->right);
          remove(nodo->right,nodo->data);
          return true;
        }
      }
    }

    // Complejidad: O(N) 
    // Mejor Caso: O(1) 
    // Caso Promedio: O(N) 
    // Peor Caso: O(N)
    // Para el height tenemos que recorrer todo para verificar al 100
    int height(Nodo<T> * & nodo){
      if(nodo == NULL){
        return -1;
      }else if(nodo->right == NULL && nodo ->left == NULL){
        return 0;
      }else{
        int rightmax = height(nodo->right);
        int leftmax = height(nodo->left);

        if(rightmax > leftmax){
          return rightmax + 1;
        }else{
          return leftmax + 1;
        }
      }
    }

    // Después de crear el bosque debes de imprimir de cada árbol si se 
    // desbalancean del lado izquierdo o del lado derecho.

    // Complejidad: O(N) 
    // Mejor Caso: O(1) 
    // Caso Promedio: O(N) 
    // Peor Caso: O(N)
    // Para el balance gtenemos que comprobar si todos los nodos estan balanceados, por lo tanto O(N)
    bool balance(Nodo<T> * & nodo){
      if(nodo==NULL){
        return true; 
      }
      //Alturas
      int Lheight = height(nodo->left); 
      int Rheight = height(nodo->right); 
      //Booleanos de nodos hijos usando recursiom
      bool lbal = balance(nodo->left); 
      if(!lbal){ 
        return false;
      }
      bool rbal = balance(nodo->right);
      if(!rbal){
        return false;
      }
      // Si la diferencia entre las alturas no es mas de 1 y cada nodo usando recursion esta balanceado, el arbol está balanceado 
      if (abs(Rheight - Lheight) <= 1 && lbal && rbal) 
        return true;
  
      // si llegamos hasta aca no esta balanceado
      if(Rheight > Lheight){
        cout << "Desbalanceado del lado derecho." << endl;
      }else{
        cout << "Desbalanceado del lado izquierdo." << endl;
      }
      return false;
      
    }
      
  public:
    BST(){
      root = NULL;
    }

    friend ostream & operator<< <T>(ostream &,  BST<T> &);

    void InOrden(){
      InOrden(root);
    }

    void PreOrden(){
      PreOrden(root);
    }

    void PostOrden(){
      PostOrden(root);
    }

    bool insert(T dato){
      if( is_empty() ){
        root = new Nodo<T>(dato);
        return true;
      }else{
        return insert(root, dato);
      }
    }

    bool is_empty(){
      return (root == NULL)? 1:0;
    }

    bool contains(T dato){
      return contains(root, dato);
    }

    int size(){
      return size(root);
    }

    T max(){
        return max(root);
    }

    T min(){
       return min(root);
    }

    T getroot(){
      return root->data;
    }

    bool remove(T dato){
      if (contains(dato)){
       return remove(root, dato);
      }else{
        cout << "Dato no encontrado"<<endl;
        return false;
      }
    }

    int height(){
      return height(root);
    }

    bool balance(){
     return balance(root);
    }

    
  ostream & imprime(ostream &salida, 
  Nodo<T> * &nodo)  {
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
};

template <typename T>
ostream &operator<<(ostream &salida, const BST<T> &lista) {
  return lista.imprime(salida, lista.root);
}
