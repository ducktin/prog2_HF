#ifndef BST_HPP_INCLUDED
#define BST_HPP_INCLUDED

#include <iostream>
#include <fstream>

using namespace std;

template <class T> struct BSTNode{
    T data;
    BSTNode<T>* parent;
    BSTNode<T>* left;
    BSTNode<T>* right;

    BSTNode(T data, BSTNode<T>* parent = NULL):data(data), parent(parent),
                    left(NULL), right(NULL){}
    bool operator==(BSTNode<T>& rhs){
        return this->data == rhs->data;
    }
    bool operator>(BSTNode<T>& rhs){
        return this->data > rhs->data;
    }
    bool operator<(BSTNode<T>& rhs){
        return this->data < rhs->data;
    }
};

template <class T> class BST{
    BSTNode<T>* root;

    bool searchHelper(BSTNode<T> *root, T val){
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
    BSTNode<T>* insertHelper(BSTNode<T> *root, T val){
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
    BSTNode<T>* removeHelper(BSTNode<T>* root, T val){
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
    void printInorderHelper(BSTNode<T>* root){
        if(!root) return;
        printInorderHelper(root->left);
        cout<<" "<<root->data<<" ";
        printInorderHelper(root->right);
    }
    void printPreorderHelper(BSTNode<T>* root, ofstream& f){
        if(!root) return;
        f << root->data << endl;
        printPreorderHelper(root->left, f);
        printPreorderHelper(root->right, f);
    }
    void destPostorderHelper(BSTNode<T>* root){
        if(!root) return;
        destPostorderHelper(root->left);
        destPostorderHelper(root->right);

        delete root;
    }
    BSTNode<T>* findMin(BSTNode<T>* root){
        BSTNode<T>* tmp = root;
        while(tmp->left){
            tmp = tmp->left;
        }
        return tmp;
    }
    BST(const BST<T>& t);
    BST& operator=(const BST<T>& t);
public:
    BST():root(NULL) {}
    BST(ifstream& file):root(NULL){
        T data;
        while(file >> data){
            insert(data);
            file.ignore(10,'\n');
        }
    }
    bool search(T val){
        return searchHelper(root, val);
    }
    void insert(T val){
        root = insertHelper(root, val);
    }
    void remove(T val){
        root = removeHelper(root, val);
    }

    class iterator;
    void print(iterator first, iterator last){
        while(first!=last){
            cout<<" "<<*first<<" ";
            ++first;
        }
        cout<<endl;
    }
    void print(ofstream& file){
        printPreorderHelper(root, file);
    }
    ~BST(){
        destPostorderHelper(root);
    }

    iterator begin(){
        if(!root) return iterator();
        BSTNode<T>* tmp = root;
        while(tmp->left)
            tmp = tmp->left;
        return iterator(tmp);
    }
    iterator end(){
        return iterator();
    }

    class iterator{
        BSTNode<T>* curr;
    public:
        iterator():curr(NULL){}
        iterator(BSTNode<T>* n):curr(n){}

        iterator& operator++(){
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
        iterator operator++(int){
            iterator tmp = *this;
            operator++();
            return tmp;
        }

        bool operator!=(iterator i){return curr != i.curr;}
        T& operator*(){return curr->data;}
    };
};

#endif // BST_HPP_INCLUDED
