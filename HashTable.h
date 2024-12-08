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
        HashTable(int size){
            
            table = new ListLinked<TableEntry<V>> [size];
            n = 0;      //numero de elementos de la tabla
            max = size ;
        }

        ~HashTable(){
            delete [] table;
        }

        void insert(string key, V value) override{
            TableEntry<V> entrada = TableEntry<V>(key, value);
            int pos = h(key);
            for(int i = 0; i < table[pos].size(); i++){  
                if(table[pos].get(i).key == key){ 
                    throw std::runtime_error("");
                }
            }

            table[pos].prepend(entrada);  //añadimos el elemento al principio porque el orden no importa 
            n++;           
        }
    

        V search(string key) override{
            return operator[](key);
        }


        V remove(string key) override{
            int pos = h(key);
            for(int i = 0; i < table[pos].size(); i++){  
                if(table[pos].get(i).key == key){    
                V valor = table[pos].get(i).value;
                    table[pos].remove(i);
                    n--;
                    return valor;
                }
            }

            throw std::runtime_error("");

        }
        
        int entries() override{                 //Devuelve el número de elementos que tiene el Diccionario
            return n;
        }

        int capacity(){
            return max;
        }

        friend ostream& operator<<(ostream &out, 
        const HashTable<V> &th){
            for(int i = 0; i < th.max; i++){
                out <<  "Posición " << i <<" : "  << th.table[i] << endl;
                
            }
            return out;
        }

        V operator[] (std::string key){
            int pos = h(key);
            for (int i = 0; i < table[pos].size(); i++){
                if(table[pos].get(i).key == key){
                    return table[pos].get(i).value;
                }
            }
            throw std::runtime_error("");
        }
    
};

#endif