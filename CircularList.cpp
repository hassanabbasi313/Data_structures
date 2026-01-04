#include <iostream>
#include <stdexcept>
using namespace std;

template<typename N>
class Node {
private:
    N element;
    Node<N>* next_node;
public:
    Node(N e = 0, Node<N>* n = nullptr) : element(e), next_node(n) {}
    N retrieve() const { return element; }
    Node<N>* next() const { return next_node; }
    void setnext(Node<N>* n) { next_node = n; }
    void setelement(N e) { element = e; }
};
template<typename C>
class CircularList {
private:
    Node<C>* tail;  // points to the last node
public:
    CircularList() : tail(nullptr) {}

    bool emptyList() const { return tail == nullptr; }

    int listSize() const {
        if (tail == nullptr) return 0;
        int s = 0;
        Node<C>* ptr = tail->next();
        do {
            s++;
            ptr = ptr->next();
        } while (ptr != tail->next());
        return s;
    }

    C frontElement() const {
        if (tail == nullptr) throw "underflow";
        return tail->next()->retrieve();
    }

    C lastElement() const {
        if (tail == nullptr) throw "underflow";
        return tail->retrieve();
    }

    void pushAtFront(C e) {
        Node<C>* newNode = new Node<C>(e);
        if (tail == nullptr) {
            newNode->setnext(newNode);
            tail = newNode;
        } else {
            newNode->setnext(tail->next());
            tail->setnext(newNode);
        }
    }

    void pushAtEnd(C e) {
        pushAtFront(e);
        tail = tail->next();
    }

    C popAtFront() {
        if (tail == nullptr) throw "underflow";
        Node<C>* head = tail->next();
        C e = head->retrieve();
        if (head == tail) {
            delete head;
            tail = nullptr;
        } else {
            tail->setnext(head->next());
            delete head;
        }
        return e;
    }

    C popAtEnd() {
        if (tail == nullptr) throw "underflow";
        Node<C>* head = tail->next();
        C e;
        if (head == tail) {
            e = tail->retrieve();
            delete tail;
            tail = nullptr;
            return e;
        }
        Node<C>* ptr = head;
        while (ptr->next() != tail) {
            ptr = ptr->next();
        }
        e = tail->retrieve();
        ptr->setnext(head);
        delete tail;
        tail = ptr;
        return e;
    }

    void display() const {
        if (tail==nullptr) {
            cout<<"List is empty\n";
            return;
        }
        Node<C>* ptr = tail->next();
        do {
            cout<<ptr->retrieve()<<" ";
            ptr=ptr->next();
        } while(ptr != tail->next());
        cout << endl;
    }

    void eraseElement(C e) {
        if (tail == nullptr) {
            cout << "List is empty\n";
            return;
        }
        Node<C>* ptr = tail->next();
        Node<C>* previous = tail;
        bool found = false;
        do {
            if (ptr->retrieve() == e) {
                found = true;
                Node<C>* erasePtr = ptr;
                if (erasePtr == tail->next()) {
                    popAtFront();
                    ptr = tail ? tail->next() : nullptr;
                    previous = tail;
                } else if (erasePtr == tail) {
                    popAtEnd();
                    ptr = tail ? tail->next() : nullptr;
                } else {
                    previous->setnext(erasePtr->next());
                    ptr = erasePtr->next();
                    delete erasePtr;
                }
            } else {
                previous = ptr;
                ptr = ptr->next();
            }
        } while (ptr && ptr!=tail->next());

        if (!found) cout << "Element not found\n";
    }
    ~CircularList() {
        while (!emptyList()) {
            popAtFront();
        }
    }

};

int main() {

    return 0;
}
