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
        
        friend std::ostream& operator<<(std::ostream &out, const BSTreeDict<V> &bs){
            bs.tree->print_inorder(out, bs.tree -> root);
            return out;
        }

        V operator[](std::string key){
            return search(key);
        }
        
        // Metodos heredados de Dict.h

        void insert(std::string key, V value) override{
            insert(key);
        }

        V search(std::string key) override{
            search(key);
        }

        V remove(std::string key) override{
            remove(key);
        }
        
        int entries() override{
            return tree->size();
        }

        

       
        
};

#endif