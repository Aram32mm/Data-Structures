#pragma once
#ifndef HERO_H
#define HERO_H

#include <string>
class Hero{
  private:
    string name;
    double friendships;

  public:
      //Complejidad: O(1)
      Hero(string name = "", double friendships = 0){
        this->name = name;
        this->friendships = friendships;
      }
      //Complejidad: O(1)
      string getName(){
        return name;
      }
      //Complejidad: O(1)
      double getFriendships(){
          return friendships;
      }
      
      //Declaramos la funcion de sobrecarga de operador
      friend ostream & operator<<( ostream &, const Hero &);

      //Complejidad: O(1)
      bool operator>( const Hero & hero){
      return (this->friendships > hero.friendships);
      } 
      //Complejidad: O(1)
      bool operator<( const Hero & hero){
      return (this->friendships < hero.friendships);
      } 
      //Complejidad: O(1)
      bool operator==( const Hero & hero){
      return (this->friendships == hero.friendships);
      } 
      //Complejidad: O(1)
      bool operator==(const string & name){
      return (this->name == name);
      } 
      //Complejidad: O(1)
      bool operator>( const string & name){
      return (this->name > name);
      } 
      //Complejidad: O(1)
      bool operator<( const string & name){
      return (this->name < name);
      }     
};

//Sobrecarga de operador <<
    //Complejidad: O(N)
ostream & operator<<( ostream & salida, const Hero & hero){
  if (hero.friendships == 0){
     salida <<"Hero: "<< hero.name << " has no friends :( "<< endl; 
  }else if(hero.friendships == 1){
     salida <<"Hero: "<< hero.name << " has " << hero.friendships <<" friendship. "<< endl; 
  }else{
     salida <<"Hero: "<< hero.name << " has " << hero.friendships <<" friendships. "<< endl; 
  }
  return salida;
 }

#endif