#include<iostream>
#include <stdexcept>
using namespace std;
class Node{
private:
    int element;
    Node *next_node;
public:
    Node(int e=0,Node *n=nullptr):element(e),next_node(n){}
    //Getters
    int retrieve() const{
        return element;
    }
    Node* next() const {
        return next_node;
    }
    //Setters
    void setnext(Node* n){
        next_node=n;
    }
    void setelement(int e){
        element= e;
    }
    friend class SinglyList;
};
class SinglyList{
private:
    Node* list_head;
public:
    SinglyList() {
        list_head = nullptr;
    }
    bool emptyList(){
        return list_head==nullptr;
    }
    int listSize(){
        int size=0;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            size++;
        }
        return size;
    }
    int frontElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        return list_head->retrieve();
    }
    int lastElement() const {
        if (list_head==nullptr){
            throw "underflow";
        }
        Node *p1=nullptr;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            p1=ptr;
        }
        return p1->retrieve();
    }
    int countElement(int n)const{
        if (list_head==nullptr){
            throw "underflow";
        }
        int countE=0;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            if(ptr->retrieve()==n){
                countE++;
            }
        }
        return countE;
    }
    Node *head(){
        return list_head;
    }
    Node *tail(){
        Node* tail=nullptr;
        for(Node* ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
                tail=ptr;
        }
        return tail;
    }
    void pushAtFront(int e){
        Node*p=new Node(e,list_head);
        list_head=p;
    }
    void pushAtEnd(int e){
        //For an Empty List
        if (list_head == nullptr) {
            list_head = new Node(e, nullptr);
            return;
        }
        Node* last=nullptr;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            last=ptr;
        }
        Node*newnode= new Node(e,nullptr);
        last->setnext(newnode);
    }
    int popAtEnd(){
        int e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        //If the list have only 1 element
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node* last=nullptr;
        Node* secondLast=nullptr;
        for(Node *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
                if(ptr->next()!=nullptr){
                    secondLast=ptr;
                }
                last=ptr;
        }
        e=last->retrieve();
        secondLast->setnext(nullptr);
        delete last;
        return e;
    }
    int popAtFront(){
        int e;
        if (list_head == nullptr) {
            throw "underflow";
        }
        if (list_head->next()==nullptr){
            e=list_head->retrieve();
            delete list_head;
            list_head=nullptr;
            return e;
        }
        Node* temp= list_head;
        e=list_head->retrieve();
        list_head=list_head->next();
        delete temp;
        return e;
    }
    void display() {
        for (Node* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
            cout << ptr->retrieve() << " ";
        }
        cout << endl;
    }

    void eraseElement(int e) {
        if (list_head == nullptr) {
            throw "underflow";
        }

        Node* current = list_head;
        Node* previous = nullptr;
        bool found = false;

        while (current != nullptr) {

            if (previous == nullptr && current->retrieve() == e) {
                found = true;
                popAtFront();
                current = list_head;
                continue;
            }

            if (current->retrieve() == e && current->next() == nullptr) {
                found = true;
                popAtEnd();
                break;
            }

            if (current->retrieve() == e) {
                found = true;
                Node* temp = current;
                previous->setnext(current->next());
                current = current->next();
                delete temp;
            }

            else {
                previous=current;
                current=current->next();
            }
        }

        if (!found) {
            cout<<"Element not found"<<endl;
        }
    }


    ~SinglyList() {
        Node* current = list_head;
        while (current != nullptr) {
            Node* next = current->next();
            delete current;
            current = next;
        }
        list_head = nullptr;
    }


};
int main() {

    SinglyList list;

    cout << "===== TEST 1: Pop & Erase on EMPTY LIST =====" << endl;
    try {
        list.popAtFront();
    } catch(const char* e) {
        cout << "popAtFront() on empty list -> " << e << endl;
    }

    try {
        list.popAtEnd();
    } catch(const char* e) {
        cout << "popAtEnd() on empty list -> " << e << endl;
    }

    try {
        list.eraseElement(10);
    } catch(const char* e) {
        cout << "eraseElement() on empty list -> " << e << endl;
    }

    cout << "\n===== TEST 2: Push at Front & End =====" << endl;
    list.pushAtFront(10);
    list.pushAtEnd(20);
    list.pushAtEnd(30);
    list.pushAtFront(5);
    list.display();         // Expected: 5 10 20 30

    cout << "\n===== TEST 3: Pop on Single-Element List =====" << endl;
    SinglyList single;
    single.pushAtFront(100);
    cout << "List: ";
    single.display();
    cout << "popAtFront -> " << single.popAtFront() << endl;  // 100
    cout << "List after popAtFront: ";
    single.display();

    single.pushAtFront(200);
    cout << "List: ";
    single.display();
    cout << "popAtEnd -> " << single.popAtEnd() << endl;      // 200
    cout << "List after popAtEnd: ";
    single.display();

    cout << "\n===== TEST 4: popAtFront() on multi-element =====" << endl;
    list.display();      // 5 10 20 30
    cout << "popAtFront = " << list.popAtFront() << endl;  // 5
    list.display();      // 10 20 30

    cout << "\n===== TEST 5: popAtEnd() on multi-element =====" << endl;
    list.display();      // 10 20 30
    cout << "popAtEnd = " << list.popAtEnd() << endl;  // 30
    list.display();      // 10 20

    cout << "\n===== TEST 6: eraseElement (HEAD delete) =====" << endl;
    list.pushAtFront(50);   // list = 50 10 20
    list.display();
    list.eraseElement(50);  // delete head
    list.display();         // Expected: 10 20

    cout << "\n===== TEST 7: eraseElement (TAIL delete) =====" << endl;
    list.eraseElement(20);  // delete tail
    list.display();         // Expected: 10

    cout << "\n===== TEST 8: eraseElement (MIDDLE delete) =====" << endl;
    list.pushAtEnd(40);     // 10 40
    list.pushAtEnd(50);     // 10 40 50
    list.pushAtEnd(60);     // 10 40 50 60
    list.display();
    list.eraseElement(50);  // delete middle
    list.display();         // Expected: 10 40 60

    cout << "\n===== TEST 9: eraseElement multiple consecutive matches =====" << endl;
    list.pushAtFront(60);   // 60 10 40 60
    list.pushAtFront(60);   // 60 60 10 40 60
    cout << "Before erase: ";
    list.display();

    list.eraseElement(60);

    cout << "After erase: ";
    list.display();         // Expected: 10 40

    cout << "\n===== TEST 10: eraseElement not found =====" << endl;
    list.display();
    list.eraseElement(999); // not found

    cout << "\n===== TEST 11: countElement, frontElement, lastElement =====" << endl;
    cout << "List: ";
    list.display();
    cout << "Count of 10: " << list.countElement(10) << endl;
    cout << "Front Element: " << list.frontElement() << endl;
    cout << "Last Element: " << list.lastElement() << endl;
    cout << "List size: " << list.listSize() << endl;

    cout << "\n===== ALL TESTS COMPLETED =====" << endl;

    return 0;
}
