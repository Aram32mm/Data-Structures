#include <map>

template<typename T>
class Vertex{

  public:
    T dato;
    double cost;
    
    Vertex(T dato, double cost ){
      this->dato = dato;
      this->cost = cost;
    }

    

    bool operator==( const Vertex<T> & v){
      return (this->dato == v.dato);
    } 
};
template<typename T>
ostream & operator<<(ostream &, const Vertex<T> &);

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
      GrafoLA(int n){
        lista_adyacencias = new Hashtable<K, vector<T> * >(n);
      }

      void addVertex(K source){
        if (!containsVertex(source)){
          vector<T> * adyacentes = new vector<T>();
          lista_adyacencias->put(source, adyacentes);
        } else{
          cout << "Repeated Vertex." << endl;
        }
      }

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

          cout << "Repeated Vertex" << endl;
          /*
          addVertex(source);
          addEdge(source,destiny);
          */
          
        }
      }

      vector<T>* getAdyacency(K source) const{
        return lista_adyacencias->get(source);
      }

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

      bool containsEdge(K source, T destiny){
        vector<T> * edges = getAdyacency(source);
        for(auto iterador = edges->begin(); iterador < edges->end() ; iterador++ ){
          if( *iterador == destiny)
            return true;
        }
        return false;
      }

      void print(){
        vector<K> vertices = lista_adyacencias->keys();
        for(int i = 0 ; i < vertices.size(); i++){
          K vertex = vertices[i];
          vector<T> * aristas = lista_adyacencias->get(vertex);
          cout << vertex << " -> ";
          for(auto iterador = aristas->begin(); iterador != aristas->end() ; iterador++ ){
            cout << *iterador << " | " ;
          }
          cout << endl;
        }
        
      }

      vector<K> dfs(K init) const{
        vector<K> search; // para guardar los datos finales
        Stack<K> stack; // para dar con el orden correcto 
        map<K,bool> check; // para checar si estan visitados o no 

        //Llenamos nuestro mapa con todos los vertices, inicializamos todos con un valor false
        vector<K> vertices = lista_adyacencias->keys(); 
        for(int i = 0 ; i < vertices.size(); i++){
          K vertex = vertices[i];
          check[vertex] = false;
        }

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
        if (vertices.size() != search.size()){
          for (auto itr = check.begin(); itr != check.end(); ++itr){
            if (itr->second == false)
              search.push_back(itr->first);
          
          }
        }
        
        return search;
      }

      vector<K> bfs(K init) const{ //Mismo algoritmo que el de DFS, pero aqui se usan queues en lugar de stacks
        vector<K> search; // para guardar los datos finales
        Queue<K> queue; // para llevar la cuenta 
        map<K,bool> check; // para checar si estan visitados o no 

        //Llenamos nuestro mapa con todos los vertices, inician todos con un valor false
        vector<K> vertices = lista_adyacencias->keys(); 
        for(int i = 0 ; i < vertices.size(); i++){
          K vertex = vertices[i];
          check[vertex] = false;
        }

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
        if (vertices.size() != search.size()){
          for (auto itr = check.begin(); itr != check.end(); ++itr){
            if (itr->second == false)
              search.push_back(itr->first);
          }
        }
    
        return search;
      }


};