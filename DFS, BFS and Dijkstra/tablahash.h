#pragma once
#ifndef TABLAHASH_H
#define TABLAHASH_H
template <typename K, typename T> /* K key, T value*/
class HashPair {
public:
	K key;
	T value;
	HashPair(K key, T value) {
		this->key = key;
		this->value = value;
	}
	HashPair() {
	}
};

const int PRIME_CONST = 31;

template <typename K, typename T> /* K key, T value*/
class Hashtable {
private:
	int size;
	HashPair<K, T> **tabla;
  //Complejidad O(1)
	int fh(K key) {
		//hash<K> khash;
    	int hashCode = 0;
    	for (int i = 0; i < 3; i++) {
       		hashCode += key[i] * pow(PRIME_CONST, i);
    	}
    	return hashCode % size;
		//return khash(key) % size;		
	}

public:
  //Complejidad O(N)
	Hashtable(int size = 20) {
		this->size = size;
		tabla = new HashPair<K, T> *[size];
		for (int i = 0; i < size; i++)
			tabla[i] = NULL;
	}
  //Complejidad O(1)
	bool put(K key, T value) {
		int posicion = fh(key);
		HashPair<K, T> *nuevo = new HashPair<K, T>(key, value);
		tabla[posicion] = nuevo;
		return 1;
	}
  //Complejidad O(1)
	T get(K key) {
		return tabla[fh(key)]->value;
	}
  //Complejidad O(N)
	vector<K> keys() const {
		vector<K> keys;
		for (int i = 0; i < size; i++) {
			if (tabla[i] != NULL) {
				keys.push_back(tabla[i]->key);
			} else {
				continue;
			}
		}
		sort(keys.begin(), keys.end());

		return keys;
	}
  //Complejidad O(N)
	void print() {
		for (int i = 0; i < size; i++) {
			if (tabla[i] != NULL) {
				cout << "i: " << i << " k: " << tabla[i]->key
					 << "  "; //<< tabla[i]->value;
				cout << endl;
			} else {
				cout << "i: " << i << " k: " << tabla[i];
				cout << endl;
			}
		}
	}
};

#endif