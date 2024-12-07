#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict: public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;

    public:
        
        BSTreeDict(){
            tree = new BSTree<TableEntry<V>>();
        }
        
        ~BSTreeDict(){
            delete tree;
        }
        
        // En lugar de acceder directamente a root o print_inorder, se reutiliza el operador << ya implementado en BSTree
        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
            out << *(bs.tree);
            return out;
        }

        V search(std::string key) override{
            TableEntry<V> entry(key); 
            TableEntry<V> found = tree->search(entry); 
            return found.value;
        }

        V operator[](std::string key){
            return search(key);
        }

        // Metodos heredados de Dict.h

        void insert(std::string key, V value) override{
            TableEntry<V> TableEntry(key, value);   //objeto TableEntry
            tree->insert(TableEntry);
        }

        V remove(std::string key) override {
            //TableEntry<V> entry(key); 
            TableEntry<V> found = tree->search(key); 
            tree->remove(found); 
            return found.value; 
        }

        
        int entries() override{
            return tree->size();
        }

        

       
        
};

#endif