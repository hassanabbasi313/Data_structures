#include<iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

template<typename T>
class Node{
private:
    T element;
    Node<T> *next_node;
public:
    Node(T e=T(),Node<T> *n=nullptr):element(e),next_node(n){}
    //Getters
    T retrieve() const{
        return element;
    }
    Node<T>* next() const {
        return next_node;
    }
    //Setters
    void setnext(Node<T>* n){
        next_node=n;
    }
    void setelement(T e){
        element= e;
    }
};
template<typename T>
class SinglyList{
private:
    Node<T>* list_head;
public:
    SinglyList() {
        list_head = nullptr;
    }
    bool emptyList(){
        return list_head==nullptr;
    }
    int listSize()const {
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
    Node<T> *head() const {
        return list_head;
    }
    Node<T> *tail() const {
        Node<T>* tail=nullptr;
        for(Node<T>* ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
                tail=ptr;
        }
        return tail;
    }
    void pushAtFront(T e){
        Node<T>*p=new Node<T>(e,list_head);
        list_head=p;
    }
    void pushAtEnd(T e){
        //For an Empty List
        if (list_head == nullptr) {
            list_head = new Node<T>(e, nullptr);
            return;
        }
        Node<T>* last=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
            last=ptr;
        }
        last->setnext(new Node<T>(e,nullptr));
    }
    T popAtEnd(){
        T e;
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
        Node<T>* last=nullptr;
        Node<T>* secondLast=nullptr;
        for(Node<T> *ptr=list_head;ptr!=nullptr;ptr=ptr->next()){
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
        delete temp;
        return e;
    }
    void display() const {
        for (Node<T>* ptr = list_head; ptr != nullptr; ptr = ptr->next()) {
            cout<<ptr->retrieve()<<" ";
        }
        cout<<endl;
    }

    void eraseElement(T e) {
        if (list_head == nullptr) {
            throw "underflow";
        }

        Node<T>* current = list_head;
        Node<T>* previous = nullptr;
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
                Node<T>* temp = current;
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
        Node<T>* current = list_head;
        while (current != nullptr) {
            Node<T>* next = current->next();
            delete current;
            current = next;
        }
        list_head = nullptr;
    }


};
template<typename Type>
class SimpleTree{
private:
    Type node_value;
    SimpleTree<Type> *parent_node;
    SinglyList<SimpleTree*> children;
public:
    SimpleTree(Type const& obj,SimpleTree *p){
        node_value=obj;
        parent_node=p;
    }
    Type retrieve(){
        return node_value;
    }
    SimpleTree<Type>* parent() const {
        return parent_node;
    }
    bool isRoot() const {
        return parent()==nullptr;
    }
    int degree() const {
        return children.listSize();
    }
    bool isLeaf() const {
        return degree()==0;
    }
    SimpleTree<Type>* child(int n) const {
        if (n < 0 || n >= degree()) return nullptr;
        Node<SimpleTree<Type>*>* node = children.head();
        for (int i = 0; i < n; ++i) {
            node = node->next();
        }

        return node->retrieve();
    }



    void insertNode(Type const &obj){
        children.pushAtEnd(new SimpleTree<Type>(obj,this));
    }
    void detach(){
        if(isRoot()){
            return;
        }
        parent()->children.eraseElement(this);
        parent_node=nullptr;
    }
    void attach(SimpleTree<Type>* tree){
        if(!tree->isRoot()){
            tree->detach();
        }
        tree->parent_node=this;
        children.pushAtEnd(tree);
    }
    int sizee() const {
        int treeSize = 1;
        for(Node<SimpleTree<Type>*>* node = children.head(); node != nullptr; node = node->next()){
            treeSize += node->retrieve()->sizee();
        }
        return treeSize;
    }
    int height() const {
        int treeHeight = 0;
        for(Node<SimpleTree<Type>*>* node = children.head(); node != nullptr; node = node->next()){
            treeHeight = std::max(treeHeight, 1 + node->retrieve()->height());
        }
        return treeHeight;
    }
    void depth_first_traversal() const {
        cout<<retrieve()<<"\t";
        for(Node<SimpleTree*>* ptr=children.head();ptr!=nullptr;ptr=ptr->next()){
            ptr->retrieve()->depth_first_traversal();
        }
    }


};

int main() {
    cout << "Testing SimpleTree...\n";

    // Create root node
    SimpleTree<string> root("Fayyaz", nullptr);

    // Create child nodes
    SimpleTree<string>* child1 = new SimpleTree<string>("Owais", nullptr);
    SimpleTree<string>* child2 = new SimpleTree<string>("Mahnoor", nullptr);

    // Attach children to root
    root.attach(child1);
    root.attach(child2);

    // Add grandchildren to child1
    SimpleTree<string>* grand1 = new SimpleTree<string>("Ali", nullptr);
    SimpleTree<string>* grand2 = new SimpleTree<string>("Ahmed", nullptr);
    child1->attach(grand1);
    child1->attach(grand2);

    // Root and leaf checks
    cout << "Root is root? " << (root.isRoot() ? "Yes" : "No") << endl;
    cout << "Child1 is leaf? " << (child1->isLeaf() ? "Yes" : "No") << endl;
    cout << "Grand1 is leaf? " << (grand1->isLeaf() ? "Yes" : "No") << endl;

    // Degree checks
    cout << "Degree of root: " << root.degree() << endl;
    cout << "Degree of child1: " << child1->degree() << endl;

    // Tree size and height
    cout << "Size of tree: " << root.sizee() << endl;
    cout << "Height of tree: " << root.height() << endl;

    // Detach a grandchild
    grand1->detach();
    cout << "After detaching grand1, size: " << root.sizee() << endl;

    // Attach a new subtree to child2
    SimpleTree<string>* newSub = new SimpleTree<string>("Raad", nullptr);
    child2->attach(newSub);
    cout << "After attaching newSub to child2, height: " << root.height() << endl;

    // Access children of root
    for(int i=0;i<root.degree();i++){
        cout << "Child " << i << " value: " << root.child(i)->retrieve() << endl;
    }

    // Clean up dynamically allocated nodes
    delete grand1;
    delete grand2;
    delete newSub;
    delete child1;
    delete child2;

    return 0;
}
