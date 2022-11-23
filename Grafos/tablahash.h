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

template <typename K, typename T> /* K key, T value*/
class Hashtable {
private:
	int size;
	HashPair<K, T> **tabla;

	int fh(K key) {
		hash<K> khash;
		return khash(key) % size;
	}

public:
	Hashtable(int size = 20) {
		this->size = size;
		tabla = new HashPair<K, T> *[size];
		for (int i = 0; i < size; i++)
			tabla[i] = NULL;
	}

	bool put(K key, T value) {
		int posicion = fh(key);
		HashPair<K, T> *nuevo = new HashPair<K, T>(key, value);
		tabla[posicion] = nuevo;
		return 1;
	}

	T get(K key) {
		return tabla[fh(key)]->value;
	}

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