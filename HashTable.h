#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"
#include "../../Practica1/PRA_2324_P1/ListLinked.h" 

using namespace std;

template <typename V>
class HashTable: public Dict<V> {

    private:
        int n;      //numero de elementos de la tabla
        int max;    //numero de cubetas de la tabla
        ListLinked<TableEntry<V>>* table;    //array de punteros a listas enlazadas

        int h(std::string key){                 //devuelve la cubeta (posicion) en la tabla hash de key
            int suma = 0;
            int pos = 0;
            for(char c : key){
                suma = suma + int(c);
            }
            pos = suma % max;
            return pos;                                 
        }                                       //resto de la división entre la suma de los valores ASCII y el tamaño de la tabla hash

    public:
        
        void insert(std::string key, V value) override {
            
            int pos = h(key);

            if (table[pos] == nullptr) {
                table[pos] = new ListLinked<TableEntry<V>>();
            }

            for (const auto& entry : *(table[pos])) {
                if (entry.key == key) {
                    throw runtime_error();
                }
            }
            table[pos]->insert(TableEntry<V>(key, value));
            ++n;
        }


        V search(std::string key) override {    //Busca el valor correspondiente a key. Devuelve el valor value asociado si key está en el diccionario.
            int pos = h(key);
            if (table[pos] == nullptr) {
                throw runtime_error();
            }
            Node<V>* current = table[pos];
            //const auto& item = table[pos];  //me creo una variable referencia "&" item con "auto", para que coincida el tipo y con ello comparo las keys 
            while(current != nullptr){
                if (current.key == key){
                    return current.value;
                }else 
                    throw runtime_error();
                current = current->next;
            }
        }

        V remove(std::string key) override{     //Elimina el par key->value si se encuentra en el diccionario
            int pos = h(key);
            if (table[pos] == nullptr) {
                throw runtime_error();
            }
            table[pos] == nullptr;
        }
        
        int entries() override{                 //Devuelve el número de elementos que tiene el Diccionario
            return n;
        }

        HashTable(int size){
            
            table = new ListLinked<TableEntry<V>>;
            for (int i = 0; i < size; i++){
                table[i] = nullptr;

            }
            n = 0;      //numero de elementos de la tabla
            max = 0;
        }

        ~HashTable(){
            for (int i = 0; i < max; i++){
                delete table[i];
            }
        }

        int capacity(){
            return max;
        }

        friend std::ostream& operator<< (std::ostream &out, const HashTable<V> &th){
            for (int i = 0; i < th.max; i++){
                cout << "Indice " << i << ": ";
                if (th.table[i] != nullptr){
                    for (const auto& entry : *(th.table[i])){ //*(th.table[i]) es la lista enlazada desreferenciada, th.table[i] es un puntero, no una lista
                        out << "[" << entry.key << ": " << entry.value << "]" << endl;
                    }
                }else
                    out << "---" << endl;
            }

            return out;

        }

        V operator[] (std::string key){
            if(!(h(key)))
                throw runtime_error();
            return key;
        }
};

#endif