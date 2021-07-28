#include <iostream>
#include <vector>

using namespace std;

template<class V> class HashTable {
private:
	struct Slot { int key; V value; };
    vector<Slot> *d;
    const int m;

    int hashFunc(int k) { return k % m; }

    bool isEmpty(int k) { return this->d[this->hashFunc(k)].size() == 0; }

public:
    HashTable (int l): m(l) {
        this->d = new vector<Slot> [this->m];
        for (int i=0; i<this->m; i++) this->d[i] = {};
    }

    V get(int k, int at = 0) {
        const int h = this->hashFunc(k);
        for (int i=0; i<this->d[h].size(); i++) {
        	if (this->d[h][i].key == k) {
                if (at == 0) return this->d[h][i].value;
                at--;
            }
        }
        return NULL;
    }

    void insert(int k, V v) {
        const int h = this->hashFunc(k);
        this->d[h].push_back({ k, v });
    }

    void insert(int k, V v, int at) {
        if (this->isEmpty(k)) {
            this->insert(k, v);
            return;
        }

        const int h = this->hashFunc(k);
        for (int i=0; i<this->d[h].size(); i++) {
            if (this->d[h][i].key == k) {
                if (at == 0) {
                    this->d[h].insert(this->d[h].begin() + i, { k, v });
                    return;
                }
                at--;
            }
        }
    }

    void remove(int k, int at = 0) {
        if (this->isEmpty(k)) return;

        const int h = this->hashFunc(k);
        if (this->d[h].size() == 1) {
            this->d[0] = {};
            return;
        }
        
        for (int i=0; i<this->d[h].size(); i++) {
        	if (this->d[h][i].key == k) {
                if (at == 0) {
                    this->d[h].erase(this->d[h].begin() + i);
                    return;
                }
                at--;
            }
        }
    }

    void display() {
        for (int i=0; i<this->m; i++) {
            cout << '[' << i << "] = ";
            for (int x=0; x<this->d[i].size(); x++) {
                cout << '(' << this->d[i][x].key << ", " << this->d[i][x].value << ')';
                if (x != (this->d[i].size() - 1)) cout << " -> ";
            }
            cout << endl;
        }
    }
};

int main (int argc, char *argv[]) {
	HashTable<string> ht = HashTable<string>(7);
	
    ht.insert(1, "15");
    ht.insert(1, "8");
    ht.insert(4, "11");
    ht.insert(4, "15");
    ht.insert(6, "27");

    ht.remove(1);

    ht.display();

    return 0;
}