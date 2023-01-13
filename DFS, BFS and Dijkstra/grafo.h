#pragma once
#ifndef GRAFO_H
#define GRAFO_H
#include <map>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <iterator> 
#include "hero.h"

#define INF 0x3f3f3f3f

template<typename T>
class Vertex{

  public:
    T dato;
    double cost;
    // Complejidad: O(1)  
    Vertex(){}
    // Complejidad: O(1)  
    Vertex(T dato, double cost ){
      this->dato = dato;
      this->cost = cost;
    }
    // Complejidad: O(1)  
    bool operator==( const Vertex<T> & v){
      return (this->dato == v.dato);
    } 
    // Complejidad: O(1)  
    bool operator==( const string & dato){
      return (this->dato == dato);
    } 
     // Complejidad: O(1)  
    bool operator==( const double & cost){
      return (this->cost == cost);
    } 
    // Complejidad: O(1)  
    bool operator>( const double & cost){
      return (this->cost > cost);
    } 
     // Complejidad: O(1)  
    bool operator<( const double & cost){
      return (this->cost < cost);
    } 
     // Complejidad: O(1)  
    bool operator<( const Vertex<T> & v){
      return (this->cost < cost);
    } 
     // Complejidad: O(1)  
    bool operator>( const Vertex<T> & v){
      return (this->cost > cost);
    } 
};
template<typename T>
ostream & operator<<(ostream &, const Vertex<T> &);

// Complejidad: O(N)
template<typename T>
ostream & operator<<(ostream & salida, const Vertex<T> & v){
  salida << v.dato << ":" <<v.cost;
  return salida;
}

template<typename K, typename T>
class GrafoLA{
  private:
      Hashtable<K, vector<T> * >* lista_adyacencias;

  public:
      // Complejidad: O(1)
      GrafoLA(int n){
        lista_adyacencias = new Hashtable<K, vector<T> * >(n);
      }
      // Complejidad: O(V)
      void addVertex(K source){
        if (!containsVertex(source)){
          vector<T> * adyacentes = new vector<T>();
          lista_adyacencias->put(source, adyacentes);
        } else{
          cout << "Repeated Vertex." << endl;
        }
      }
      // Complejidad: O(V + E)
      void addEdge(K source, T destiny){
        if (containsVertex(source) && containsVertex(destiny.dato)){
          if (!containsEdge(source,destiny)){
            vector<T> * adyacentes = lista_adyacencias->get(source);
            adyacentes->push_back(destiny);
          } else{
            vector<T> * edges = getAdyacency(source);
            for(auto iterador = edges->begin(); iterador < edges->end() ; iterador++ ){
              if( *iterador == destiny)
              swap(*iterador,destiny);
            }
          }
          
        }else if(containsVertex(source) && !containsVertex(destiny.dato)){
          if (!containsEdge(source,destiny)){
            vector<T> * adyacentes = lista_adyacencias->get(source);
            adyacentes->push_back(destiny);
          } else{
            vector<T> * edges = getAdyacency(source);
            for(auto iterador = edges->begin(); iterador < edges->end() ; iterador++ ){
              if( *iterador == destiny)
                swap(*iterador,destiny);
            }
          }
          addVertex(destiny.dato);
          
        }else{

          //cout << "Repeated Vertex" << endl;
          
          addVertex(source);
          addEdge(source,destiny);
          
        }
      }
      // Complejidad: O(1)
      vector<T>* getAdyacency(K source) const{
        return lista_adyacencias->get(source);
      }

      // Complejidad: O(V)
      bool containsVertex(K source){
        vector<K> vertices = lista_adyacencias->keys();
        for(int i = 0 ; i < vertices.size(); i++){
          K vertex = vertices[i];
          if (vertex == source){
            return true;
          }
        }
        return false;
      }
      // Complejidad: O(E)
      bool containsEdge(K source, T destiny){
        vector<T> * edges = getAdyacency(source);
        for(auto iterador = edges->begin(); iterador < edges->end() ; iterador++ ){
          if( *iterador == destiny)
            return true;
        }
        return false;
      }
      // Complejidad: O(E)
      int countEdges(K source){
        int number_Edges = 0;
        vector<T> * edges = getAdyacency(source);
        for(auto iterador = edges->begin(); iterador < edges->end() ; iterador++ ){
          number_Edges++;
        }
        return number_Edges;

      }

      // Complejidad: O(E + V)
      void print(){
        vector<K> vertices = lista_adyacencias->keys();
        for(int i = 0 ; i < vertices.size(); i++){
          K vertex = vertices[i];
          vector<T> * aristas = lista_adyacencias->get(vertex);
          cout << vertex << " ("<<countEdges(vertex)<<") " << "-> ";
          for(auto iterador = aristas->begin(); iterador != aristas->end() ; iterador++ ){
            cout << *iterador << " | " ;
          }
          
          cout << endl << endl;
        }
        
      }
      // Complejidad: O(V)
      int countVertexes(){
        vector<K> vertices = lista_adyacencias->keys();
        return vertices.size();
      }
      // Complejidad: O(E + V)
      vector<K> dfs(K init) const{
        vector<K> search; // para guardar los datos finales
        Stack<K> stack; // para dar con el orden correcto 
        map<K,bool> check = visited(); // para checar si estan visitados o no 

        stack.push(init); //metemos al stack nuestro vertice inicial

        while(!stack.is_empty()){ 
          K init = stack.peek(); // con este valor vamos a trabajar
          stack.pop(); // lo removemos del stack

          if (check.at(init) == false){ // si no lo hemos visitado
            search.push_back(init); //metelo al vector
            check[init] = true; // marcalo como visitado 
          }

          // Iteramos con sus edges 
          vector<T> * edges = getAdyacency(init);
          for(auto iterador = edges->begin(); iterador < edges->end() ; iterador++ ){
            if(check.at(iterador->dato) == false){ // si no lo hemos visitado
              stack.push(iterador->dato);         //  metelo al stack
            } 
          }
        }

        // Manejamos los vertices desconectados
        vector<K> vertices = lista_adyacencias->keys(); 
        if (vertices.size() != search.size()){
          for (auto itr = check.begin(); itr != check.end(); ++itr){
            if (itr->second == false)
              search.push_back(itr->first);
          
          }
        }
        
        return search;
      }
      // Complejidad: O(E + V)
      vector<K> bfs(K init) const{ //Mismo algoritmo que el de DFS, pero aqui se usan queues en lugar de stacks
        vector<K> search; // para guardar los datos finales
        Queue<K> queue; // para llevar la cuenta 
        map<K,bool> check = visited(); // para checar si estan visitados o no 

        queue.enqueue(init); 

        while(!queue.is_empty()){
          K init = queue.peek();
          queue.dequeue();

          if (check.at(init) == false){
            search.push_back(init);
            check[init] = true;
          }

          vector<T> * edges = getAdyacency(init);
          for(auto iterador = edges->begin(); iterador < edges->end() ; iterador++ ){
            if(check.at(iterador->dato) == false){
              queue.enqueue(iterador->dato);
            } 
          }
        }
        vector<K> vertices = lista_adyacencias->keys(); 
        if (vertices.size() != search.size()){
          for (auto itr = check.begin(); itr != check.end(); ++itr){
            if (itr->second == false)
              search.push_back(itr->first);
          }
        }
    
        return search;
      }

      // Complejidad: O(V)
      map<K,bool> visited() const{
        map<K,bool> visited; // para checar si estan visitados o no 

        //Llenamos nuestro mapa con todos los vertices, inician todos con un valor false
        vector<K> vertices = lista_adyacencias->keys(); 
        for(int i = 0 ; i < vertices.size(); i++){
          K vertex = vertices[i];
          visited[vertex] = false;
        }
        return visited;
      }
      // Complejidad: O(E + V)
      bool df_search(K init, K target) const{
        Stack<K> stack; // para dar con el orden correcto 
        map<K,bool> check = visited(); // para checar si estan visitados o no 

        stack.push(init); //metemos al stack nuestro vertice inicial

        while(!stack.is_empty()){ 
          K init = stack.peek(); // con este valor vamos a trabajar
          stack.pop(); // lo removemos del stack

          if (check.at(init) == false){ // si no lo hemos visitado
            if (init == target){ //si es igual al target
              cout << init;
              return true; //acaba la funcion
            }
            cout << init << " -> "; 
            check[init] = true; // marcalo como visitado 
          }

          // Iteramos con sus edges 
          vector<T> * edges = getAdyacency(init);
          for(auto iterador = edges->begin(); iterador < edges->end() ; iterador++ ){
            if(check.at(iterador->dato) == false){ // si no lo hemos visitado
              stack.push(iterador->dato);         //  metelo al stack
            } 
          }
        } 
        return false;
      }
      // Complejidad: O(E + V)
      bool bf_search(K init, K target) const{ //Mismo algoritmo que depth search, pero aqui se usan queues en lugar de stacks
        Queue<K> queue; // para llevar la cuenta 
        map<K,bool> check = visited(); // para checar si estan visitados o no 

        queue.enqueue(init); 

        while(!queue.is_empty()){
          K init = queue.peek();
          queue.dequeue();

          if (check.at(init) == false){
            if (init == target){
              cout << init;
              return true;
            }
            cout << init << " -> ";
            check[init] = true; // marcalo como visitado 
          }

          vector<T> * edges = getAdyacency(init);
          for(auto iterador = edges->begin(); iterador < edges->end() ; iterador++ ){
            if(check.at(iterador->dato) == false){
              queue.enqueue(iterador->dato);
            } 
          }
        }
    
        return false;
      }
    
};

template<typename K, typename T>
class UnorderedMap{
  private:
      unordered_map< K, vector<T> *> grafo;
  public:
      // Complejidad: O(1)  
      UnorderedMap(){
      }

      // Complejidad: O(1)
      void addVertex(K source){
           grafo[source] = new vector<T>(); //O(N)
      }

      // Complejidad: O(V)
      void addEdge(K source, T destiny){ // O(N)
        if (grafo.find(source) != grafo.end()){ // Si el source está en el mapa
          vector<T> * adyacentes = grafo[source]; // Agrega destiny a edges
          adyacentes->push_back(destiny);
        
        }else{ // Si no está 
          addVertex(source); // Agregalo a los vertices 
          vector<T> * adyacentes = grafo[source]; // agregalo a sus edges
          adyacentes->push_back(destiny);
        }

        if (!(grafo.find(destiny.dato) != grafo.end())){ // si el destino  no es vertice
          addVertex(destiny.dato); //hazlo vertice 
        }
    
      }

      // Complejidad: O(V)
      int countVertex(){ 
        int verts = 0;
        for (auto data: grafo){
          verts++;
        }
        return verts;
      }
      
      // Complejidad: O(1)
      int countEdges(K source) const{
        vector<T> * adyacentes = grafo.at(source);
        return adyacentes->size();
      }

      // Complejidad: O(1)
      vector<T>* getAdyacency(K source) const{
        vector<T> * adyacentes = grafo.at(source);
        return adyacentes;
      }
      
      // Complejidad: O(E + V)
      void print(){
        for (auto data: grafo){
          cout << data.first << " (" << countEdges(data.first) << ") -> ";
          vector<T> *aristas = data.second;
          for(auto ite = aristas->begin(); ite != aristas->end(); ++ite){
            cout << *ite << " | ";
          }
          cout << endl << endl;
        }
      }

      // Complejidad: O(V)
      unordered_map<K,bool> visited() const{
        unordered_map<K,bool> visited; // para checar si estan visitados o no 

        //Llenamos nuestro mapa con todos los vertices, inician todos con un valor false
        for (auto data: grafo){
          K vertex = data.first;
          visited[vertex] = false;
        }
        return visited;
      }

      // Complejidad: O(E)  
      unordered_map<K,double> costs() const{
        unordered_map<K,double> costs;
        
        for (auto data: grafo){
          K vertex = data.first;
          costs[vertex] = INF;
        }
        
        return costs;
      }

      // Complejidad: O(E + V)
      bool df_search(K init, K target) const{
        Stack<K> stack; // para dar con el orden correcto 
        unordered_map<K,bool> check = visited(); // para checar si estan visitados o no 
        try {
          check.at(init);
        }catch(...) {
          cout << "Vertice no encontrado "<< endl;
          cout << "Intenta con otro nombre" << endl;
          return false;
        }
        
        stack.push(init); //metemos al stack nuestro vertice inicial
        while(!stack.is_empty()){ 
          K init = stack.peek(); // con este valor vamos a trabajar
          stack.pop(); // lo removemos del stack
        
          if (check.at(init) == false){ // si no lo hemos visitado
            if (init == target){ //si es igual al target
            cout << init << endl;
            return true; //acaba la funcion
            }
            cout << init << " -> "; 
            check[init] = true; // marcalo como visitado 
          }  

          // Iteramos con sus edges 
          vector<T> * edges = getAdyacency(init);
          for(auto iterador = edges->begin(); iterador < edges->end() ; iterador++ ){
            
            if(check.at(iterador->dato) == false){ // si no lo hemos visitado
              stack.push(iterador->dato);         //  metelo al stack
            }
          }
        } 

        cout << "No Encontrado."<< endl;
        return false;
      }
      
      // Complejidad: O(E + V)
      bool bf_search(K init, K target) const{ //Mismo algoritmo que depth search, pero aqui se usan queues en lugar de stacks
        Queue<K> queue; // para llevar la cuenta 
        unordered_map<K,bool> check = visited(); // para checar si estan visitados o no 

        try {
          check.at(init);
        }catch(...) {
          cout << "Vertice no encontrado "<< endl;
          cout << "Intenta con otro nombre" << endl;
          return false;
        }
        
        queue.enqueue(init); 

        while(!queue.is_empty()){
          K init = queue.peek();
          queue.dequeue();

          if (check.at(init) == false){
            if (init == target){
              cout << init;
              return true;
            }
            cout << init << " -> ";
            check[init] = true; // marcalo como visitado 
          }

          vector<T> * edges = getAdyacency(init);
          for(auto iterador = edges->begin(); iterador < edges->end() ; iterador++ ){
            if(check.at(iterador->dato) == false){
              queue.enqueue(iterador->dato);
            } 
          }
        }
        cout << "Not found"<< endl;
        return false;
      }

      // Complejidad: O(V+E)
      void prunning(int conexiones){
        prunneVertex(conexiones);
        prunneEdges();
      }

      // Complejidad: O(V)
      void prunneVertex(int conexiones){
        typename unordered_map< K, vector<T> *>::iterator itv = grafo.begin();
        while(itv != grafo.end()) {
            K temp = itv->first;
            itv++;
          
            if(countEdges(temp) < conexiones){
              grafo.erase(temp);
            }
        }
      }

      // Complejidad: O(E)
      void prunneEdges(){
        for (auto data: grafo){
          vector<T> *aristas = data.second;
          int i = 0;
          typename vector<T>::iterator itv = aristas->begin();
          while(itv != aristas->end()) {
            if (grafo.find(itv->dato) == grafo.end()){
              aristas->erase(itv);
            } else{
              itv++;
            }
          }
        }
      }

      // Complejidad: O(N)
      vector<Hero> heroes_vector(){ 
        vector<Hero> heroes;
        for (auto hero: grafo) {
          Hero h(hero.first,countEdges(hero.first));
          heroes.push_back(h);
        }
        return heroes;
      } 

      // Complejidad: O(N)
      LinkedList<Hero> heroes_ll(){ 
        LinkedList<Hero> heroes;
        for (auto hero: grafo) {
          Hero h(hero.first,countEdges(hero.first));
          heroes.addLast(h);
        }
        return heroes;
      } 

      // Complejidad: O(E)
      void obtainFriendships(K key){
        cout << key << " -> ";
         vector<T> *aristas = getAdyacency(key);
          for(auto ite = aristas->begin(); ite != aristas->end(); ++ite){
            cout << *ite << " | " << endl;
          }
      }

      // Complejidad: O(ElogV)
      void dijkstra(T init){
        Queue<T> nodes; //para los vertices con su valor
        unordered_map <K, double> distances = costs();
        
        nodes.enqueue(init); //metemos al queue nuestro vertex incial
        
        while( !nodes.is_empty() ){
          T curr = nodes.dequeueMin();
          distances[curr.dato] = curr.cost;

          vector<T> * edges = getAdyacency(curr.dato);
          for(auto iterador = edges->begin(); iterador < edges->end(); iterador++ ){
            K dato = iterador->dato;
            double edgeCost = iterador->cost;

            if(curr.cost + edgeCost < distances.at(dato)){
              distances[dato] = curr.cost + edgeCost;
              nodes.enqueue(*iterador);
            }
          }
        }
        
        typename map<K, double>::iterator itr;
        cout << "\nShortest path from "<<init.dato<<" to all reachable nodes:"<<"\n";
        cout << "\tEDGE\tCOST\n";
        for (itr = distances.begin(); itr != distances.end(); ++itr){
          if (itr->second == 0){
            continue;
          }
          if (itr->second != INF){
            cout << '\t' << itr->first << '\t' << itr->second << '\n';
          }
        }
      }

      // Complejidad: O(ElogV)
      double dijkstra(T init, K target){ 
        Queue<T> nodes; //para los vertices con su valor
        unordered_map <K, double> distances = costs();

        try {
          distances.at(init.dato);
          distances.at(target);
        }catch(...) {
          cout << "Error."<< endl;
          cout << "Ya sea el vertice inicial o el final son incorrectos." << endl;
          return 0;
        }
        
        nodes.enqueue(init); //metemos al queue nuestro vertex incial
        
        while( !nodes.is_empty() ){
          T curr = nodes.dequeueMin();
          distances[curr.dato] = curr.cost;

          vector<T> * edges = getAdyacency(curr.dato);
          for(auto iterador = edges->begin(); iterador < edges->end(); iterador++ ){
            K dato = iterador->dato;
            double edgeCost = iterador->cost;

            if(curr.cost + edgeCost < distances.at(dato)){
              distances[dato] = curr.cost + edgeCost;
              nodes.enqueue(*iterador);
            }
          }
        }
        if (distances[target] == INF){
          return 0;
        } else if (distances[target] == 0){
          return 0;
        }
        return distances[target];
      }
    

};

#endif