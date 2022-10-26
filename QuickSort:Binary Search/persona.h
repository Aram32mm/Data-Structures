#include <iostream>
using namespace std;
class Persona{
  private:
    string first_name,last_name,city;
    int id, zip;
  public:
      Persona(int id = 0, int zip = 0, string fname = "", string lname = "", string city = ""){
        this->id = id;
        this->zip = zip;
        this->first_name = fname;
        this->last_name = lname;
        this->city = city;
      }

      string getFirstname(){
        return first_name;
      }
      //Declaramos la funcion de sobrecarga de operador
      friend ostream & operator<<( ostream &, const Persona &);

      //para quicksort
      bool operator>( const Persona & persona){
      return (this->last_name > persona.last_name);
      } 

      bool operator<( const Persona & persona){
      return (this->last_name < persona.last_name);
      } 

      //para busqueda binaria 
      bool operator==( const Persona & persona){
      return (this->last_name == persona.last_name);
      } 

      bool operator==(const string & last_name){
      return (this->last_name == last_name);
      } 

      bool operator>( const string & name){
      return (this->last_name > name);
      } 

      bool operator<( const string & name){
      return (this->last_name < name);
      } 
    
};

//Sobrecarga de operador <<
ostream & operator<<( ostream & salida, const Persona & persona){
  salida <<"ID: "<<persona.id<<"  FN: "<< persona.first_name <<"  LN: "<< persona.last_name <<"  ZIP: "<< persona.zip <<"   City: "<< persona.city ; 
  return salida;
 }