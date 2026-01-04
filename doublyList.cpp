#include<iostream>
#include <stdexcept>
using namespace std;

template<typename T>
class Node{
private:
    T element;
    Node<T> *next_node,*previous_node;
public:
    Node(T e=T(),Node<T> *n=nullptr,Node<T>*p=nullptr):element(e),next_node(n),previous_node(p){}
    //Getters
    T retrieve() const{
        return element;
    }
    Node<T>* next() const {
        return next_node;
    }
    Node<T>* previous() const{
        return previous_node;
    }
    //Setters
    void setnext(Node<T>* n){
        next_node=n;
    }
    void setprevious(Node<T>* n){
        previous_node=n;
    }
    void setelement(T e){
        element= e;
    }
};

template<typename T>
class DoublyList{
private:
    Node<T> *list_head;
public:
    DoublyList() {
        list_head = nullptr;
    }
    bool emptyList(){
        return list_head==nullptr;
    }
    int listSize(){
        int size=0;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            size++;
        }
        return size;
    }
    T frontElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        return list_head->retrieve();
    }
    T lastElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        Node<T> *p1=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            p1=ptr;
        }
        return p1->retrieve();
    }
    int countElement(T n)const{
        if (list_head==nullptr){
            throw "underflow";
        }
        int countE=0;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            if(ptr->retrieve()==n){
                countE++;
            }
        }
        return countE;
    }
    Node<T> *head(){
        return list_head;
    }
    void pushAtFront(T e){
        Node<T>*p=new Node<T>(e,list_head,nullptr);
        if(list_head!=nullptr){
            list_head->setprevious(p);
        }
        list_head=p;
    }
    void pushAtEnd(T e){
        //For an Empty List
        if (list_head == nullptr) {
            pushAtFront(e);
            return;
        }
        Node<T>* last=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            last=ptr;
        }
        Node<T>*newnode= new Node<T>(e,nullptr,last);
        last->setnext(newnode);
    }
    T popAtEnd(){
        T e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node<T>* last=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            last=ptr;
        }
        e=last->retrieve();
        last->previous()->setnext(nullptr);
        delete last;
        return e;
    }
    T popAtFront(){
        T e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node<T>* temp= list_head;
        e=list_head->retrieve();
        list_head=list_head->next();
        list_head->setprevious(nullptr);
        delete temp;
        return e;
    }
    void eraseElement(T e){
        // empty list
        if (list_head == nullptr) {
            throw "underflow";
        }
        bool found=false;
        for(Node<T> *ptr=list_head;ptr!=nullptr;){
                if(ptr->retrieve()==e){
                    found = true;
                    Node<T>* erasePtr=ptr;
                    ptr=ptr->next();
                    if(erasePtr==list_head){
                        popAtFront();
                    }
                    else if (erasePtr->next()==nullptr){
                        popAtEnd();
                    }
                    else{
                        erasePtr->previous()->setnext(erasePtr->next());
                        erasePtr->next()->setprevious(erasePtr->previous());
                        delete erasePtr;
                        erasePtr = nullptr;
                        }
                }
                else {
                    ptr= ptr->next();
                }
        }
        if(found==false){
            cout<<"Element not found"<<endl;
        }
    }
    void display() {
        for (Node<T>* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
            cout<<ptr->retrieve()<<" ";
        }
        cout <<endl;
    }
    ~DoublyList() {
        for (Node<T>* current=list_head; current != nullptr; ) {
            Node<T>* nextNode=current->next();
            delete current;
            current=nextNode;
        }
        list_head=nullptr;
    }

};
int main(){

    return 0;
}
