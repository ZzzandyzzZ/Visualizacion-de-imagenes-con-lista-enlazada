#include "doublelinkedlist.h"
using namespace std;

DoubleLinkedList::DoubleLinkedList(int maxsize)
{
    first=nullptr;
    last=nullptr;
    size=0;
    maxSize=maxsize;
}

DoubleLinkedList::Node *DoubleLinkedList::begin() const
{
    return first;
}

DoubleLinkedList::Node *DoubleLinkedList::end() const
{
    return last;
}

int DoubleLinkedList::getMaxSize() const
{
    return maxSize;
}

int DoubleLinkedList::getSize() const
{
    return size;
}

void DoubleLinkedList::push_back(Imagen_ a){
    Node*nuevo=new  Node(a);
    size++;
    if(first==nullptr){
        first=nuevo;
        last=nuevo;
        return;
    }
    else{
        last->next=nuevo;
        nuevo ->previous=last;
        last=nuevo;
        first->previous=last;
        last->next=first;

    }


}
int DoubleLinkedList::fsize(){
    return size;
}

void DoubleLinkedList::show(){
    Node *actual;
    if(first==nullptr)
    {
       qDebug()<<"LISTA VACIA"<<endl;
       return;
    }
    actual=first;
    qDebug()<<"Los elementos son"<<endl;
    qDebug() <<actual->dato.getTitle()<<endl;
    actual=actual->next;
    while(actual!=first){
        qDebug() <<actual->dato.getTitle()<<endl;
        actual=actual->next;
    }
    qDebug()<<endl;


}
int DoubleLinkedList::deleteN(DoubleLinkedList::iterator Element){
    Node*element =Element.getPNode();
    if(element==nullptr)return 0;
    size--;
    Node *actual,*temp;
    actual=first;
    if(element==first){
         if(size==0)
         {
            delete element;
             return 0;
         }
         first=first->next;
         first->previous=last;
         last->next=first;
         delete actual;
         return 1;
    }
     if(element==last){
         temp=last;
         actual=last->previous;
         actual->next=first;
         first->previous=actual;
         last=actual;
         delete temp;
         return 2;
    }
    element->previous->next=element->next;
    element->next->previous=element->previous;
    delete element;
    return 3;
}

void DoubleLinkedList::showAll(){
    Node*actual;
    actual=first;
    for(int i=0;i<this->fsize();i++){
       // cout<<"previousrior: "<<actual->previous->dato.titulo<<" Actual: "<<actual->dato.titulo<<" nextuiente: "<<actual->next->dato.titulo<<endl;

        actual= actual->next;


    }

}

