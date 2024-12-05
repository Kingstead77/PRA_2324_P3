#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T> 
class BSTree {
    private:
        //atributos
        int nelem;
        BSNode<T>* root;
        //miembros privados

        BSNode<T>* search (BSNode<T>* n, T e) const{
            if (n == nullptr){
                throw std::runtime_error("Nodo no encontrado");
            }
            else if (e > n->elem){
                return search(n.right, e);
            }
            else if (e < n->elem){
                return search(n->left, e);
            }
            else
                return n;   //devuelve  la posicion donde se encuentra el elemento
        }

        BSNode<T>* insert (BSNode<T>* n, T e){
            if (n == nullptr){
                Node(e);
            }
            else if(e == n->elem){
                throw std::runtime_error("Nodo ya existente");
            }
            else if (e > n->elem){
                n->right = insert(n->right, e); //insertar arbol en el derecho
            }else
                n->left = insert(n->left, e); //si no en el izquierdo
            return n;
        }

        void print_inorder(std::ostream& out, BSNode<T>* n) const {
            if (n == nullptr){
                return;
            }
            print_inorder(out, n->left); 
            out << n->elem << " ";
            print_inorder(out, n->right);
        }

        BSNode<T>* remove(BSNode<T>* n, T e){
            if (n == nullptr){
                throw std::runtime_error("Element not found");
            }
            else if (e > n->elem){
                n->right = remove(n->right, e);
            }
            else if (e < n->elem){
                n->left = remove(n->left, e);
            }else{  //ya estamos en el nodo
                if (n->left != nullptr && n->right != nullptr){ //tiene 2 hijos
                    n->elem = max(n->left); //buscamos el elemento máximo del sub-arbol izquierdo y lo remplazamos por el que vamos a borrar
                    n->left = remove_max(n->left);  //eliminamos el máximo de antes por que ya lo hemos cambiado de posición
                }else   //tiene 1 o 0 descendiantes
                    if (n->left != nullptr){    //vemos si está en la derecha o izquierda y lo cambiamos
                        n = n->left;    
                    }else
                        n = n->right;
            }
            return n;
        }

        T max(BSNode<T>* n) const {
            if (n->right == nullptr)
                return n->elem;
            return max(n->right);
        }

        BSNode<T>* remove_max(BSNode<T>* n){
            if (n->right = nullptr){    //si no tiene hijo derecho (es el más grande), devuelve el hijo izquierdo. Si tampoco tiene devuelve null eliminándose
                return n->left;
            }else{
                n->right = remove_max(n->right); //si ha retornado null (es el más grande), se elimina el nodo ya que apunta a nullptr
                return n;   //devuelve
            }
        }

        void delete_cascade(BSNode<T>* n){
            if (n == nullptr){
                return;
            }
            delete_cascade(n->left);    //Elimina los arboles izquierda y derecha (postorden)
            delete_cascade(n->right);
            delete n;
        }

    public:
        // creacion y tamaño
        BSTree(){
            nelem = 0;
            root = nullptr;
        }

        int size() const{
            return nelem;
        }

        //busqueda de elementos

        T search(T e) const{
            return search(root, e).elem;
        }

        T operator[] (T e) const{
            return search(e);
        }

        void insert (T e){
            return insert(root, e);
        }

        friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst){
            bst.print_inorder(out, bst.root);
            return out;
        }

        void remove(T e){
            root = remove(root, e);
        }

        ~BSTree(){
            delete_cascade(root);
        }
};

#endif