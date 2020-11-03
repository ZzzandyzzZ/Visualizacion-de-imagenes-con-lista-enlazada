#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H
#include "Imagen_.h"
#include<iostream>
#include <QDebug>
#include<QMessageBox>
using namespace std;
class DoubleLinkedList
{
private:
    class Node {
    public:
        Imagen_ dato;
        Node *next;
        Node *previous;
        Node(Imagen_ x){
            dato=x;
            next=nullptr;
            previous=nullptr;
        }
        void setDato(Imagen_ image){
            dato=image;
        }
    };
    DoubleLinkedList::Node *first;
    DoubleLinkedList::Node *last;
    int size;
    int maxSize;
public:
    class iterator{
    private:
        Node *pNode;
    public:
        void operator =(Node* x)
        {
            pNode=x;

        }
        void operator ++()
        {
            pNode=pNode->next;
        }
        void operator --()
        {
            pNode=pNode->previous;
        }
        Imagen_ operator *()
        {
            return pNode->dato;
        }
        bool operator ==(Node *x)
        {
            return pNode==x;
        }
        bool operator !=(Node *x)
        {
            return pNode!=x;
        }
        Node *getPNode() const{
            return pNode;
        }
    };
    void push_back(Imagen_ a);
    int fsize();
    void show();
    int deleteN(DoubleLinkedList::iterator element);
    void showAll();
    DoubleLinkedList(int);
    Node *begin() const;
    Node *end() const;

    int getMaxSize() const;
    int getSize() const;
};

#endif // DOUBLELINKEDLIST_H
