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
                return search(n->right, e);
            }
            else if (e < n->elem){
                return search(n->left, e);
            }
            else
                return n;   //devuelve  la posicion donde se encuentra el elemento
        }

        BSNode<T>* insert (BSNode<T>* n, T e){
            if (n == nullptr){
                nelem++;
                return new BSNode<T>(e);
                //n = new BSNode<T>(e);
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
            if (n != nullptr){
                print_inorder(out, n->left); 
                out << n->elem << " ";
                print_inorder(out, n->right);
            }
        }

        T max(BSNode<T>* n) const {
            if(n == nullptr){
                throw std::runtime_error("El árbol está vacío");
            }
            else if(n->right != nullptr){
                return max(n->right);
            }
            else{
                return n->elem;
            }
        }

        BSNode<T>* remove_max(BSNode<T>* n){
            if (n->right = nullptr){    //si no tiene hijo derecho (es el más grande), devuelve el hijo izquierdo. Si tampoco tiene devuelve null eliminándose
                return n->left;
            }else{
                n->right = remove_max(n->right); //si ha retornado null (es el más grande), se elimina el nodo ya que apunta a nullptr
                return n;   //devuelve
            }
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
                if (n->left != nullptr && n->right != nullptr){  // 1. Tiene dos hijos
                    n->elem = max(n->left);                  //ponemos el máximo de la izquierda en n->elem 
                    n->left = remove_max(n->left);                  //borramos el máximo de la izquierda
                    return n;
                }
                else if(n->left != nullptr){                // 2. Tiene hijo a la izquierda
                    BSNode<T>* sustituto = n->left;         //guardamos el hijo izquierdo
                    delete n;                               //borramos el actual
                    return sustituto;                       //devolvemos el izquierdo
                }
                else if(n->right != nullptr){               //3. Tiene hijo a la derecha
                    BSNode<T>* sustituto = n->right;        //aplicamos lo mismo
                    delete n;
                    return sustituto;
                }
                else{
                    delete n;                               //4. No tiene hijos :( 
                    return nullptr;                         //lo borramos y ya jaja :)
                }
                nelem--;
            }
            return n;

            
            return n;
        }

        void delete_cascade(BSNode<T>* n){
            if (n != nullptr){
                delete_cascade(n->left);    //Elimina los arboles izquierda y derecha (postorden)
                delete_cascade(n->right);
                delete n;
            }
            
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
            BSNode<T>* encontrado = search(root, e);
            return encontrado->elem;
        }

        T operator[] (T e) const{
            return search(e);
        }

        void insert (T e){
            root = insert(root, e);
        }

        friend std::ostream& operator<<(std::ostream &out, const BSTree<T> &bst){
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