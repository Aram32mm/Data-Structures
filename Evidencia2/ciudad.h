#include <iostream>
using namespace std;
class Ciudad{
  private:
    string nombre;
    int habitantes;
  public:
    Ciudad(string nombre = ""){
      this->nombre = nombre;
      this->habitantes = 1;
    }
  
    int getHabitantes() {
      return this->habitantes;
    }
    
    //para busqueda binaria 
    bool operator==( const Ciudad & ciudad){
    return (this->nombre == ciudad.nombre);
    } 

    bool operator==(const string & ciudad){
      return (this->nombre == ciudad);
    } 
    
    bool operator>( const string & ciudad){
    return (this->nombre > ciudad);
    } 

    bool operator<( const string & ciudad){
    return (this->nombre < ciudad);
    }

    //para aumentar el contador 
    void operator++(int){
      habitantes++;
    } 

    bool operator>(const Ciudad & ciudad){
    return (this->nombre > ciudad.nombre);
    } 

    bool operator<( const Ciudad & ciudad){
    return (this->nombre < ciudad.nombre);
    }
    
    //Declaramos la funcion de sobrecarga de operador
    friend ostream & operator<<( ostream &, const Ciudad &);
};

//Sobrecarga de operador <<
ostream & operator<<( ostream & salida, const Ciudad & ciudad){
  salida <<"Ciudad: "<<ciudad.nombre<<endl<<"Habitantes: "<<ciudad.habitantes<<endl;
  return salida;
 }