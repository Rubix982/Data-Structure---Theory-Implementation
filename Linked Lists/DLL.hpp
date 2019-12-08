#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

#include <iostream>
using namespace std;

template<typename T>
struct DLL_Node {
    T data;
    DLL_Node * next;
    DLL_Node * prev;

    DLL_Node(T data, DLL_Node * prev = nullptr, DLL_Node * next = nullptr)
        : data(data), prev(prev), next(next) {}
};

template<typename T>
DLL_Node<T> * DLL_newNode(T data, DLL_Node<T> * prev = nullptr, DLL_Node<T> * next = nullptr) {
    return new DLL_Node<T>(data, prev, next);
}

// class DoublyLinkedList
template<typename T>
class DoublyLinkedList {

public:

    DoublyLinkedList() { 
        head = tail = nullptr;
    }

    DoublyLinkedList(size_t n, const T & el = T()) {
        for ( size_t i = 0; i < n ; ++i ) 
            push_front(el);
    }

    DoublyLinkedList(DLL_Node<T> first, DLL_Node<T> last) {

        // In case given 'last' parameter becomes NULL at some point
        // add an execption to stop the loop if 'nullptr' is encountered
        for ( DLL_Node<T> * ptr = first ; ptr != last and ptr != nullptr ; ptr = ptr->next )
            push_back(ptr->data);
    }

    void push_front(const T & data) {
        if ( head == nullptr ) head = tail = DLL_newNode<T>(data);
        else head = DLL_newNode<T>(data, nullptr, head);
    }

    void push_back(const T & data) {
        if ( tail == nullptr ) head = tail = DLL_newNode<T>(data);
        else {
            tail = DLL_newNode<T>(data, tail, nullptr);
            tail->prev->next = tail;
        }
    }

    void pop_front() {
        if ( head == tail ) {   //  Only one node
            delete tail;
            head = tail = nullptr;
        } else {
            head = head->next;
            delete head->prev;
            head->prev = nullptr;
        }
    }

    void pop_back() {
        if ( head == tail ) {
            delete head;
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }
    }

    void display(void) const {
        DLL_Node<T> * ptr = head;

        cout << ptr->data;
        while ( ptr = ptr->next, ptr != nullptr )
            cout << " <-> " << ptr->data;
        std::cout << "\n";
    }

    size_t getSize(void) const {
        return this->_size;
    }

    T & back(void) {
        return tail->data;
    }

    const T & back(void) const {
        return tail->data;
    }

    DLL_Node<T> begin(void) {
        return this->head;
    }

    void clear(void) {
        DLL_Node<T> * ptr = head;

        while ( head != nullptr ) {
            head = head->next;
            ptr->prev = ptr->next = nullptr;
            delete ptr;
        }
    }

    bool empty(void) const {
        return head == nullptr and tail == nullptr;
    }

    DLL_Node<T> end(void) {
        return this->tail;
    }

    DLL_Node<T> end(void) const {
        return this->tail;
    }

    DLL_Node<T> erase(DLL_Node<T> * i) {

        if ( i->next == nullptr ) {

            DLL_Node<T> * ptr = i->prev;
            ptr->next = nullptr;
            i->prev = nullptr;
            delete i;
            i = nullptr;
            return ptr;
        
        } else if ( i->prev == nullptr ) {
            pop_front();
            return head;
        } else {
        
            DLL_Node<T> * prev_ptr = i->prev, next_ptr = i->next;
            prev_ptr->next = next_ptr;
            next_ptr->prev = prev_ptr;
            i->prev = i->next = nullptr;
            delete i;
            i = nullptr;
            return next_ptr;
        
        }
    }

    DLL_Node<T> erase(DLL_Node<T> * first, DLL_Node<T> * last) {

        if ( first == nullptr or last = nullptr ) 
                std::cout << "Exception occurred, either one of the parameters is a null pointer.\n";
        else if ( ( first == head and last == tail ) or ( first->prev == nullptr and last->next == nullptr ) )
            clear();
        else if ( first->prev == nullptr ) {

            head = last->next;
            head->next = last->next->next;

            if ( last->next->next != nullptr ) head->next->prev = head;

            head->prev->next = nullptr;
            head->prev = nullptr;
            last->next = nullptr;

            for ( DLL_Node<T> * ptr = first->next ; ptr != last->next ; ptr = ptr->next ) {
                DLL_Node<T> * before = ptr->prev;
                before->prev = before->next = nullptr;
                ptr->prev = nullptr;
                delete before;
                before = nullptr;
            }

            return head;       

        } else if ( last->next == nullptr ) {
            
            tail = first->prev;
            tail->prev = first->prev->prev;

            if ( first->prev->prev != nullptr ) tail->prev->next = tail;

            tail->next->prev = nullptr;
            tail->next = nullptr;
            first->prev = nullptr;
            
            for ( DLL_Node<T> * ptr = first->next ; ptr != last->next ; ptr = ptr->next ) {
                DLL_Node<T> * before = ptr->prev;
                before->prev = before->next = nullptr;
                ptr->prev = nullptr;
                delete before;
                before = nullptr;
            }

            return tail;
        } else if ( ( first != head and last != tail ) or ( first->prev != nullptr and last->next != nullptr ) ) {
            
            DLL_Node<T> * before = first->prev, * after = last->next;

            before->next = after;
            after->prev = before;
            
           // Just making sure no exception occurs here 
            before->next->prev = before;
            after->prev->next = after;

            first->prev = nullptr;
            last->next = nullptr;

            for ( DLL_Node<T> * ptr = first->next ; ptr != last->next ; ptr = ptr->next ) {
                DLL_Node<T> * before = ptr->prev;
                before->prev = before->next = nullptr;
                ptr->prev = nullptr;
                delete before;
                before = nullptr;
            }            

            return after;

        } else std::cout << "Unrecognized, either unknown pointers or unhandled edge case.\n";
    }

    T & front(void) {
        return this->head->data;
    }

    const T & front(void) const {
        return this->head->data;
    }

    DLL_Node<T> insert(DLL_Node<T> i, const T & el = T()) {

       if ( i->next == nullptr ) {          // tail case

            T data = back();
            pop_back();
            push_back(el);
            push_back(data);

            return tail->prev;

       } else if ( i->prev == nullptr ) {   // head case

            push_front()

       } else {                             // middle case

            DLL_Node<T> * ptr = DLL_newNode(el);
            ptr->next = i;
            ptr->prev = i->prev;
            i->prev = ptr;
            ptr->prev->next = ptr;
            ptr->next->prev = ptr;

            return ptr;

       }
    }

    DLL_Node<T> insert(DLL_Node<T> i, DLL_Node<T> first, DLL_Node<T> last) {

        /*

        Funcationality: Insert elements from located referenced 

        */
    }

private:
    DLL_Node<T> * head, * tail;
};

#endif