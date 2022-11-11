// Arturo Carballo Arias A01662245
// José Aram Méndez Gómez - A01657142
// Juan Francisco García Rodríguez - A01660981

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

template <typename T> class Heap;
template <typename T> class Node;
template <typename T> class Tree;

template <typename T> class Heap {
private:
  vector<T> hT;

  void maxHeapify(vector<int> &hT, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < hT.size() && hT[left] > hT[largest]) {
      largest = left;
    }

    if (right < hT.size() && hT[right] > hT[largest]) {
      largest = right;
    }

    if (largest != i) {
      swap(hT[i], hT[largest]);
      maxHeapify(hT, i);
    }
  }

  void minHeapify(vector<int> &hT, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < hT.size() && hT[left] < hT[smallest]) {
      smallest = left;
    }

    if (right < hT.size() && hT[right] < hT[smallest]) {
      smallest = right;
    }

    if (smallest != i) {
      swap(hT[i], hT[smallest]);
      minHeapify(hT, i);
    }
  }

  void MaxHeap(vector<int> &hT) {
    int ultimo_no_hoja = (hT.size() / 2) - 1;
    for (int root = ultimo_no_hoja; root >= 0; root--) {
      maxHeapify(hT, root);
    }
  }

  void MinHeap(vector<int> &hT) {
    int ultimo_no_hoja = (hT.size() / 2) - 1;
    for (int root = ultimo_no_hoja; root >= 0; root--) {
      minHeapify(hT, root);
    }
  }

public:
  Heap() {}

  void insert(int newNum) {
    hT.push_back(newNum);
    MaxHeap(hT);
    //MinHeap(hT);
  }

  int size() { return hT.size(); }

  int getDato(int i) { return hT[i]; }

  void printVector() {
    for (int i = 0; i < hT.size(); ++i)
      cout << hT[i] << " ";
    cout << "\n";
  }
};

template <typename T> class Nodo {
private:
  T data;
  Nodo<T> *left;
  Nodo<T> *right;
  template <typename U> friend class Tree;

public:
  Nodo(T data) {
    this->data = data;
    this->left = NULL;
    this->right = NULL;
  }
};

template <typename T> class Tree {
private:
  Nodo<T> *root;

  bool is_empty(Nodo<T> *&nodo) { return (nodo == NULL) ? 1 : 0; }

  int height(Nodo<T> *temp) {
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

  void insert(Nodo<T> *&nodo, T dato) {
    if (nodo == NULL) {
      nodo = new Nodo<T>(dato);
    } else{
      if( !is_empty(nodo->left) && !is_empty(nodo->right)){
        if( !is_empty(nodo->left->left) && !is_empty(nodo->left->right) ){
          insert(nodo->right, dato);
        }
        else{
          insert(nodo->left, dato);
        }
      }
      else if( !is_empty(nodo->left) && is_empty(nodo->right)){
        insert(nodo->right, dato);
      } 
      else if(is_empty(nodo->left) && is_empty(nodo->right)){
        insert(nodo->left, dato);
      }
    }
  }

  void inOrden(Nodo<T> *&nodo) {
    if (nodo != NULL) {
      inOrden(nodo->left);
      cout << nodo->data << " : ";
      inOrden(nodo->right);
    }
  }

  public:
  Tree() { root = NULL; }

  bool is_empty() { return is_empty(root); }

  void insert(T dato) { 
    if (is_empty()) {
      root = new Nodo<T>(dato);
    } else {
      insert(root, dato);
    }
  }

  void inOrden() { 
    inOrden(root);
    }

  T getroot() const { return root->data; }

};

int main() {
  Heap<int> heap;
  // Change if you want a min-heap or a max-heap on the insert function of the class Heap :)
  heap.insert(3);
  heap.insert(9);
  heap.insert(2);
  heap.insert(1);
  heap.insert(4);
  heap.insert(5);
  heap.insert(100);
  
  heap.printVector();

  Tree<int> arbol;
  int n = heap.size();
  for (int i = 0; i < n; i++) {
    arbol.insert(heap.getDato(i));
    arbol.inOrden();
    cout << endl;
  }
  cout << "root: " << arbol.getroot() << endl;
}
