#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;
#include "tablahash.h"
#include "linkedlist.h"
#include "grafo.h"

int main() {
  GrafoLA<int,  Vertex<int>> grafo(20);
  //Agregamos Vertices
  grafo.addVertex(1);
  grafo.addVertex(2);
  grafo.addVertex(3);
  grafo.addVertex(4);
  grafo.addVertex(5);
  grafo.addVertex(6);
  grafo.addVertex(7);
  grafo.addVertex(8);
  grafo.addVertex(9);
  grafo.addVertex(10);

  //Agregamos los Edges
  grafo.addEdge(1, Vertex<int>(2,10));
  grafo.addEdge(1, Vertex<int>(4,20));
  grafo.addEdge(1, Vertex<int>(5,20));
  grafo.addEdge(1, Vertex<int>(6,5));
  grafo.addEdge(1, Vertex<int>(7,15));
  
  grafo.addEdge(2, Vertex<int>(3,5));
  grafo.addEdge(2, Vertex<int>(4,10));
  
  grafo.addEdge(3, Vertex<int>(4,5));
  grafo.addEdge(3, Vertex<int>(2,15));
  
  grafo.addEdge(4, Vertex<int>(5,10));
  
  grafo.addEdge(5, Vertex<int>(6,5));

  grafo.addEdge(7, Vertex<int>(6,10));
  
  grafo.addEdge(8, Vertex<int>(7,5));
  grafo.addEdge(8, Vertex<int>(1,5));
  grafo.addEdge(8, Vertex<int>(2,20));
  
  grafo.addEdge(9, Vertex<int>(8,20));
  grafo.addEdge(9, Vertex<int>(2,15));
  grafo.addEdge(9, Vertex<int>(10,10));

  grafo.addEdge(10, Vertex<int>(2,5));
  grafo.addEdge(10, Vertex<int>(3,15));

  
  grafo.print();
  
  cout << endl;
  
  vector<int> dfs = grafo.dfs(1);
  vector<int> bfs = grafo.bfs(1);

  cout << "Depth First Search:"<<endl;
  for (auto i = dfs.begin(); i != dfs.end(); ++i)
        cout << *i << " ";

  cout << endl << endl;
  
  cout << "Breadth First Search:"<<endl;
  for (auto j = bfs.begin(); j != bfs.end(); ++j)
        cout << *j << " ";
  
  cout << endl;
} 
