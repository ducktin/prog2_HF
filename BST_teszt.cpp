#include <iostream>
#include <fstream>
#include "memtrace.h"
#include "BST.hpp"

using namespace std;

class SajatOsztaly{
    int* data;
public:
    SajatOsztaly(int i):data(new int){*data = i;}
    SajatOsztaly(const SajatOsztaly& s):data(new int){*data = *s.data;}
    SajatOsztaly& operator=(const SajatOsztaly& s){
        if(this != &s){
            delete data;
            data = new int;
            *data = *s.data;
        }
        return *this;
    }
    ~SajatOsztaly(){delete data;}
    void setData(int i){*data = i;}
    int getData(){return *data;}
    bool operator==(SajatOsztaly& rhs){
        return *this->data == *rhs.data;
    }
    bool operator>(SajatOsztaly& rhs){
        return *this->data > *rhs.data;
    }
    bool operator<(SajatOsztaly& rhs){
        return *this->data < *rhs.data;
    }
};

ostream& operator<<(ostream& os, SajatOsztaly& s){
    return (os << s.getData());
}
istream& operator>>(istream& is, SajatOsztaly& s){
    int i;
    is >> i;
    s.setData(i);
    return is;
}


void test1(){
    BST<int> A;
    A.insert(6);
    A.insert(3);
    A.insert(20);
    A.insert(7);
    A.insert(2);
    A.insert(4);
    A.insert(1);
    A.insert(9);
    A.insert(12);
    A.insert(10);
    A.print(A.begin(),A.end());

    cout<<A.search(20)<<endl;
    cout<<A.search(5)<<endl;
    cout<<A.search(1)<<endl;
}
void test2(){
    BST<int> B;
    B.insert(20);
    B.insert(25);
    B.insert(7);
    B.insert(2);
    B.insert(4);
    B.insert(1);
    B.insert(9);
    B.insert(12);
    B.print(B.begin(),B.end());
    B.remove(4);
    B.remove(7);
    B.remove(20);
    B.print(B.begin(),B.end());
}

void test3(){
    BST<SajatOsztaly> C;
    C.insert(SajatOsztaly(2));
    C.insert(SajatOsztaly(1));
    C.insert(SajatOsztaly(3));
    C.print(C.begin(),C.end());

    cout << C.search(SajatOsztaly(2))<<endl;

    C.remove(SajatOsztaly(2));
    C.print(C.begin(),C.end());
}
void test4(){
    BST<int> D;
    D.insert(5);
    D.insert(3);
    D.insert(7);
    D.insert(2);
    D.insert(4);
    D.insert(6);
    D.insert(8);
    D.print(D.begin(),D.end());

    ofstream file("data.dat");
    D.print(file);
    file.close();
}
void test5(){
    ifstream file("data.dat");
    BST<int> E(file);
    file.close();

    E.print(E.begin(),E.end());
}

int main(){
    cout<<boolalpha;
    int test;
    while(cin>>test)
        switch(test){
            case 1:{
                test1(); break;
            }
            case 2:{
                test2(); break;
            }
            case 3:{
                test3(); break;
            }
            case 4:{
                test4(); break;
            }
            case 5:{
                test5(); break;
            }
        }
    return 0;
}
