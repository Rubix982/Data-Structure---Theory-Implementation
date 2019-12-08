#ifndef LINKED_LIST
#define LINKED_LIST

#include <iostream>
#include <iomanip>
using namespace std;

namespace SAIF {
    template<typename T>
    class iterator {
    public:
        T data;
        iterator<T> * next;

        iterator(const T & a = T(), iterator<T> * next = NULL) :   data(a), next(next) {}
    };

    template<typename T>
    class const_iterator {
    public:
        const T data;
        const_iterator<T> * next;

        const_iterator(const T & a = T(), const const_iterator<T> * next = NULL) :   
            data(a), next(next) {}
    };

    template<typename T>
    class list {
        private:
            iterator<T> * head, * tail;
            size_t _size;

        public:
            list();
            list(iterator<T> * start);
            list(const list<T> & obj);
            list<T> & operator=(const list<T> & rhs);

            // Q1
            void push_back(T toPut);
            T pop_back();
            void push_front(T toPut);
            void pop_front();

            void assign(iterator<T> first, iterator<T> last);
            void assign(size_t n, const T & el = T());
            T & back();
            const T & back() const;
            iterator<T> begin();
            const_iterator<T> begin() const;
            void clear();
            bool empty() const;
            iterator<T> end(void);
            const_iterator<T> end(void) const;
            iterator<T> erase(iterator<T> i);
            iterator<T> erase(iterator<T> first, iterator<T> last);
            T & front();
            const T & front() const;
            iterator<T> insert(iterator<T> i, const T & el = T());
            void insert(iterator<T> i, size_t n, const T & el);
            void insert(iterator<T> i, iterator<T> first, iterator<T> last);
            
            ~list();
    };

    template<typename T>
    iterator<T> * listNode(T toPut = 0, iterator<T> * next = NULL) {
        return new iterator<T>(toPut, next);
    }

    template<typename T>
    list<T>::list(void) :   _size(0) {
            head = tail = NULL;
    }

    template<typename T>
    list<T>::list(iterator<T> * start) :   _size(0) {
            
        head = tail = NULL;

        iterator<T> * ptr = start;

        while ( ptr != NULL ) {
            push_back(ptr->data);
            ptr = ptr->next;
        }

    }

    // WORKING
    template<typename T>
    void list<T>::push_back(T toPut) {
        if ( tail == NULL ) {
            head = tail = listNode<T>(toPut);
        } else {
            tail->next = listNode<T>(toPut, NULL);
            tail = tail->next, ++_size;
        }
    }

    // WORKING
    template<typename T>
    void list<T>::push_front(T toPut) {
        if ( head == NULL ) {
            head = tail = listNode<T>(toPut);
        } else {
            head = listNode<T>(toPut, head), ++_size;
        }
    }

    // WORKING
    template<typename T>
    void list<T>::pop_front() {
        if ( head == NULL ) {
            cout << "Already empty\n";
        } else {
            iterator<T> * temp = head;
            head = head->next;
            delete temp;
            temp = 0;
            --_size;
        }
    }

    // WORKING, but used help from the book...
    template<typename T>
    T list<T>::pop_back() {
        if ( tail == NULL ) {
            cout << "List is empty\n";
        } else if ( head == tail ) {
            delete head;
            head = tail = NULL;
        } else {
            iterator<T> * move;
            for ( move = head ; move->next != tail ; move = move->next )
                ;   
            delete tail;
            tail = move;
            tail->next = 0;
            --_size;
        }
    }


    template<typename T>
    void list<T>::assign(iterator<T> first, iterator<T> last) {

        iterator<T> * ptr = head;

        while ( ptr->next != NULL ) {

            iterator<T> * temp = ptr;
            ptr = ptr->next;
            temp->next = NULL;
            delete temp;
            temp = NULL;

        }

        delete ptr;
        ptr = NULL;

        for ( iterator<T> * temp = first ; temp != last ; temp = temp->next )
            push_back(temp->data);
    }

    template<typename T>
    void list<T>::assign(size_t n, const T & el = T()) {

        iterator<T> * ptr = head;

        while ( ptr->next != NULL ) {

            iterator<T> * temp = ptr;
            ptr = ptr->next;
            temp->next = NULL;
            delete temp;
            temp = NULL;

        }

        delete ptr;
        ptr = NULL;

        for ( size_t i  = 0; ; i < n ; ++i )
            push_back(el);
    }

    template<typename T>
    T & list<T>::back() {
        return tail->data;
    }

    template<typename T>
    const T & list<T>::back() const {
        return tail->data
    }

    template<typename T>
    iterator<T> list<T>::begin() {
        return this->head;
    }

    template<typename T>
    const_iterator<T> list<T>::begin() const {
        return const_iterator{head->data, head->next};
    }

    template<typename T>
    void list<T>::clear() {
        iterator<T> * ptr = head;

        while ( ptr->next != NULL ) {

            iterator<T> * temp = ptr;
            ptr = ptr->next;
            temp->next = NULL;
            delete temp;
            temp = NULL;

        }

        delete ptr;
        ptr = NULL;
    }

    template<typename T>
    bool list<T>::empty() const {
        return head == NULL || tail == NULL;
    }

    template<typename T>
    iterator<T> list<T>::end(void) {
        return this->tail->next;
    }

    template<typename T>
    const_iterator<T> list<T>::end(void) const {
        return const_iterator{tail->data, tail->next};
    }

    template<typename T>
    iterator<T> list<T>::erase(iterator<T> i) {

       if ( i == head ) {
           pop_front();
           return NULL;
       } else if ( i == tail ) {
            pop_back();
            return head;
       } else if ( i != head && i != tail) {

           iterator<T> * ptr = head;

           for ( ; ptr != i ; ptr = ptr->next )
                ;

            ptr->next = i->next;
            i->next = NULL;
            delete i;
            i = NULL;
       } else std::cout << "Edge, unknown edge case.\n";
    }

    template<typename T>
    iterator<T> list<T>::erase(iterator<T> first, iterator<T> last) {

        if ( first == head && last == tail ) {

            clear();

            return NULL;

        } else if ( first == head ) {

            for ( iterator<T> * ptr = head->next ; ptr != last ; ptr = ptr->next ) {
                head->next = NULL;
                delete head;
                head = NULL;

                head = ptr;
            } 

            head = last->next;
            last->next = NULL;

            return head;

        } else if ( last == tail ) {

            iterator<T> * temp = head;

            while ( temp != first && temp != NULL )
                temp = temp->next;

            // Since last == tail, then as tail->next = NULL, 
            // then last->next == NULL
            temp->next = last->next;

            for ( iterator<T> * ptr = first->next ; ptr != last ; ptr = ptr->next ) {
                first->next = NULL;
                delete first;
                first = NULL;

                first = ptr;
            } 

            return last->next;

        } else std::cout << "Error, unknown edge case.\n";
    }

    template<typename T>
    T & list<T>::front() {
        return this->head;
    }

    template<typename T>
    const T & list<T>::front() const {
        return this->head;
    }

    template<typename T>
    iterator<T> list<T>::insert(iterator<T> i, const T & el = T()) {
       if ( i == head ) {
           front_inserter(el);
           return head;
       } else if ( i == tail ) {
            for ( iterator<T> * ptr = head ; ptr->next != tail ; ptr = ptr->next ) ;

            ptr->next = new iterator<T>(el, NULL);
            ptr->next->next = tail;

            return ptr->next;
       } else {
            iterator<T> * ptr = head;

            for ( ; ptr ->next != i ; ptr = ptr->next ) ;

            iterator<T> * temp = ptr->next;
            ptr->next = new iterator<T>(el, NULL);
            ptr->next->next = temp;

            return ptr->next;   
       }
    }

    template<typename T>
    void list<T>::insert(iterator<T> i, size_t n, const T & el = T()) {

        if ( i == head ) {

            for ( size_t counter = 0 ; counter < n ; ++counter ) 
                front_inserter(el);
            

        } else if ( i == tail ) {

            iterator<T> * ptr = head;

            for ( ; ptr->next != i ; ptr = ptr->next )
                ;   
            
            for ( size_t counter = 0 ; counter < n ; ++counter ) {

                ptr->next = new iterator<T>(el, NULL);
                ptr = ptr->next;

            }

            ptr->next = tail;

        } else if ( i != head && i != tail ) {
            
                iterator<T> * ptr = head;

                for ( ; ptr->next != i ; ptr = ptr->next )
                    ;   

                for ( size_t counter = 0 ; counter < n ; ++counter ) {
                    ptr->next = new iterator<T>(el, NULL);
                    ptr = ptr->next;
                }

                ptr->next = i;

        } else std::cout << "Error, edge case not recognized.\n";
        
    }

    template<typename T>
    void list<T>::insert(iterator<T> i, iterator<T> first, iterator<T> last) {

        if ( i == head ) {

            for ( iterator<T> * ptr = first ; ptr != last ; ptr = ptr->next )
                front_inserter(ptr->data);

        } else {

            iterator<T> * ptr = head;

            for ( ; ptr->next != i ; ptr = ptr->next ) ;   
            
            for ( iterator<T> * deferencing = first ; deferencing != last ; deferencing = deferencing->next ) {
                ptr->next = new iterator<T>(deferencing->data, NULL);
                ptr = ptr->next;                
            }

            ptr->next = i;  
        } 
    }
};

#endif