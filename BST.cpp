#include "memtrace.h"
#include "BST.hpp"
template<class T>
BSTNode<T>::BSTNode(T data, BSTNode<T>* parent):data(data), parent(parent),
                    left(NULL), right(NULL){}
template<class T>
bool BSTNode<T>::operator==(BSTNode<T>& rhs){
        return this->data == rhs->data;
    }
template<class T>
bool BSTNode<T>::operator>(BSTNode<T>& rhs){
        return this->data > rhs->data;
    }
template<class T>
bool BSTNode<T>::operator<(BSTNode<T>& rhs){
        return this->data < rhs->data;
    }
template<class T>
bool BST<T>::searchHelper(BSTNode<T> *root, T val){
    if(!root)
        return false;
    else {
        if(root->data == val)
            return true;
        else {
            if(root->data < val)
                return searchHelper(root->right, val);
            else
                return searchHelper(root->left, val);
        }
    }
}
template<class T>
BSTNode<T>* BST<T>::insertHelper(BSTNode<T> *root, T val){
    if(!root){
        root = new BSTNode<T>(val);
    } else {
        if(root->data == val);
        else if (root->data > val) {
            if (!root->left) {
                root->left = new BSTNode<T>(val, root);
            } else {
                root->left = insertHelper(root->left, val);
            }
        } else {
            if (!root->right) {
                root->right = new BSTNode<T>(val, root);
            } else {
                root->right = insertHelper(root->right, val);
            }
        }
    }
    return root;
}
template<class T>
BSTNode<T>* BST<T>::removeHelper(BSTNode<T>* root, T val){
    if(!root) return root;
    else if(val < root->data) root->left = removeHelper(root->left, val);
    else if(val > root->data) root->right= removeHelper(root->right, val);
    else { // found then delete
        // Case 1: No child
        if(!root->left && !root->right){
            delete root;
            root = NULL;
        }
        // Case 2: One child
        else if(!root->left){
            BSTNode<T>* tmp = root;
            root = root->right;
            root->parent = tmp->parent;
            delete tmp;
        }
        else if(!root->right){
            BSTNode<T>* tmp = root;
            root = root->left;
            root->parent = tmp->parent;
            delete tmp;
        }
        // Case 3: Two children
        else {
            BSTNode<T>* tmp = findMin(root->right);
            root->data = tmp->data;
            root->right = removeHelper(root->right, root->data);
        }
    }
    return root;
}
template<class T>
void BST<T>::printInorderHelper(BSTNode<T>* root){
    if(!root) return;
    printInorderHelper(root->left);
    cout<<" "<<root->data<<" ";
    printInorderHelper(root->right);
}
template<class T>
void BST<T>::printPreorderHelper(BSTNode<T>* root, ofstream& f){
    if(!root) return;
    f << root->data << endl;
    printPreorderHelper(root->left, f);
    printPreorderHelper(root->right, f);
}
template<class T>
void BST<T>::destPostorderHelper(BSTNode<T>* root){
    if(!root) return;
    destPostorderHelper(root->left);
    destPostorderHelper(root->right);

    delete root;
}
template<class T>
BSTNode<T>* BST<T>::findMin(BSTNode<T>* root){
    BSTNode<T>* tmp = root;
    while(tmp->left){
        tmp = tmp->left;
    }
    return tmp;
}
template<class T>
BST<T>::BST():root(NULL) {}
template<class T>
BST<T>::BST(ifstream& file):root(NULL){
    T data;
    while(file >> data){
        insert(data);
        file.ignore(10,'\n');
    }
}
template<class T>
bool BST<T>::search(T val){
    return searchHelper(root, val);
}
template<class T>
void BST<T>::insert(T val){
    root = insertHelper(root, val);
}
template<class T>
void BST<T>::remove(T val){
    root = removeHelper(root, val);
}
template<class T>
void BST<T>::print(iterator first, iterator last){
    while(first!=last){
        cout<<" "<<*first<<" ";
        ++first;
    }
    cout<<endl;
}
template<class T>
void BST<T>::print(ofstream& file){
    printPreorderHelper(root, file);
}
template<class T>
BST<T>::~BST(){
    destPostorderHelper(root);
}
template<class T>
typename BST<T>::iterator BST<T>::begin(){
    if(!root) return iterator();
    BSTNode<T>* tmp = root;
    while(tmp->left)
        tmp = tmp->left;
    return iterator(tmp);
}
template<class T>
typename BST<T>::iterator BST<T>::end(){
    return iterator();
}
template<class T>
BST<T>::iterator::iterator():curr(NULL){}
template<class T>
BST<T>::iterator::iterator(BSTNode<T>* n):curr(n){}
template<class T>
typename BST<T>::iterator& BST<T>::iterator::operator++(){
    if(curr){
        if(curr->right){
            curr = curr->right;
            while(curr->left)
                curr = curr->left;
        } else {
            while(true){
                if(!curr->parent){
                    curr = NULL;
                    break;
                } else if(curr->parent->left == curr){
                    curr = curr->parent;
                    break;
                } else
                    curr = curr->parent;
            }
        }
    }
    return *this;
}
template<class T>
typename BST<T>::iterator BST<T>::iterator::operator++(int){
    iterator tmp = *this;
    operator++();
    return tmp;
}
template<class T>
bool BST<T>::iterator::operator!=(typename BST<T>::iterator i){return curr != i.curr;}
template<class T>
T& BST<T>::iterator::operator*(){return curr->data;}
template<class T>
T* BST<T>::iterator::operator->(){return &curr->data;}
