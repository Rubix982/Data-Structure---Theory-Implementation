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

        iterator(const T & a = T(), iterator<T> * next = nullptr) :   data(a), next(next) {}
    };

    template<typename T>
    class const_iterator {
    public:
        const T data;
        const_iterator<T> * next;

        const_iterator(const T & a = T(), const const_iterator<T> * next = nullptr) :   
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
            ~list();

            // Q1
            void insert_at_tail(T toPut);
            void insert_at_head(T toPut);
            void insert_at(int index, T elem);
            void insert_before(int index, T elem);
            void insert_after(int index, T elem);
            void delete_from_front();
            T delete_from_end();
            void delete_at(int index);
            void delete_before(int index);
            void delete_after(int index);
            bool search_data(T toSearch);
            void swap(int from, int to);
            void display(void) const;               // Sanity Check
            void bubbleSort(void);
            size_t length_Of_list(void) const;
            size_t getSize(void) const;

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

            // Q2
            size_t Count(T toSearchFor) const;

            // Q3
            T getVal(int index) const;            // Gets back value at a certain index
    };


    // Helper Function, WORKING
    template<typename T>
    iterator<T> * listNode(T toPut = 0, iterator<T> * next = nullptr) {
        return new iterator<T>(toPut, next);
    }

    // WORKING
    template<typename T>
    list<T>::list(void) :   _size(0) {
            head = tail = nullptr;
    }

    // WORKING
    template<typename T>
    list<T>::list(iterator<T> * start) :   _size(0) {
            head = tail = start;
    }

    // WORKING
    template<typename T>
    void list<T>::insert_at_tail(T toPut) {
        if ( tail == nullptr ) {
            head = tail = listNode<T>(toPut);
        } else {
            tail->next = listNode<T>(toPut, nullptr);
            tail = tail->next, ++_size;
        }
    }

    // WORKING
    template<typename T>
    void list<T>::insert_at_head(T toPut) {
        if ( head == nullptr ) {
            head = tail = listNode<T>(toPut);
        } else {
            head = listNode<T>(toPut, head), ++_size;
        }
    }

    // WORKING
    template<typename T>
    void list<T>::insert_at(int index, T elem) {
        if ( index < 0 || index >= _size ) {
            cout << "Range out of bounds\n";
        } else {
            iterator<T> * move = head;
            
            for ( int counter = 0 ; move->next != nullptr && counter < index - 1; ++counter, move = move->next ) 
                    ;

            move->next = listNode<T>(elem, move->next);
            ++_size;
        }
    }

    template<typename T>
    void list<T>::insert_before(int index, T elem) {
        if ( index < 0 || index >= _size || index - 1 < 0 ) {
            cout << "Range out of bounds\n";
        } else {
            iterator<T> * move = head;
            
            for ( int counter = 0 ; move->next != nullptr && counter < index - 2; ++counter, move = move->next ) 
                    ;

            move->next = listNode<T>(elem, move->next);
            ++_size;
        }    
    }

    template<typename T>
    void list<T>::insert_after(int index, T elem) {
        if ( index < 0 || index >= _size || index + 1 >= _size ) {
            cout << "Range out of bounds\n";
        } else {
            iterator<T> * move = head;
            
            for ( int counter = 0 ; move->next != nullptr && counter < index ; ++counter, move = move->next ) 
                    ;

            move->next = listNode<T>(elem, move->next);
            ++_size;
        }    
    }

    // WORKING
    template<typename T>
    void list<T>::delete_from_front() {
        if ( head == nullptr ) {
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
    T list<T>::delete_from_end() {
        if ( tail == nullptr ) {
            cout << "List is empty\n";
        } else if ( head == tail ) {
            delete head;
            head = tail = nullptr;
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

    // WORKING
    template<typename T>
    void list<T>::delete_at(int index) {
        if ( index < 0 || index >= _size ) {
            cout << "Out of range.\n";
        } else {
            int counter = 0;
            iterator<T> * move;

            for ( move = head; move->next != nullptr && counter < index - 1; ++counter, move=move->next )
                ;

            iterator<T> * temp = move->next;
            move->next = move->next->next;
            delete temp;
            temp = nullptr;
            --_size;
        }   
    }

    template<typename T>
    void list<T>::delete_before(int index) {
        if ( index < 0 || index >= _size || index - 1 < 0 ) {
            cout << "Out of range.\n";
        } else {
            int counter = 0;
            iterator<T> * move;

            for ( move = head; move->next != nullptr && counter < index - 2; ++counter, move=move->next )
                ;

            iterator<T> * temp = move->next;
            move->next = move->next->next;
            delete temp;
            temp = nullptr;
            --_size;
        }   
    }

    template<typename T>
    void list<T>::delete_after(int index) {
        if ( index < 0 || index >= _size || index + 1 >= _size ) {
            cout << "Out of range.\n";
        } else {
            int counter = 0;
            iterator<T> * move;

            for ( move = head; move->next != nullptr && counter < index; ++counter, move=move->next )
                ;

            iterator<T> * temp = move->next;
            move->next = move->next->next;
            delete temp;
            temp = nullptr;
            --_size;
        }   
    }

    // WORKING
    template<typename T>
    bool list<T>::search_data(T toSearch) {
        if ( head == nullptr ) {
            cout << "Linked List is empty.\n";
        } else {
            for ( iterator<T> * move = head ; move->next != nullptr ; move=move->next ) 
                if ( move->data == toSearch ) 
                    return true;
            
            return false;
        }
    }

    // WORKING
    template<typename T>
    void list<T>::display(void) const {
        if ( head == nullptr ) {
            cout << "List is empty.\n";
            return;
        } 

        iterator<T> * ptr = head;
        while ( ptr ) {
            cout << setw(3) << ptr->data << " ";
            ptr = ptr->next;
        }
        cout << endl;     
    }

    template<typename T>
    void list<T>::swap(int from, int to) {
        if ( head == NULL ) {
            cout << "List is empty.\n";
            return ;
        }
        if ( from == to ) 
            return ;
        if ( abs(to - from) == 1) {

            iterator<T> * from_prev, * from_after, * from_curr;

            int counter = 0;
            for ( from_prev = head ; from_prev != NULL && counter < from - 2 ; ++counter, from_prev = from_prev->next )
                ;  

            from_curr = from_prev->next;

            counter = 0;
            for ( from_after = head ; from_after != NULL && counter < to - 1 ; ++counter, from_after = from_after->next )
                ;

            from_prev->next = from_after;
            from_curr->next = from_after->next;
            from_after->next = from_curr;
        
            return ;
        }

        iterator<T> * from_prev, * from_after, * to_prev, * to_after;

        int counter = 0;
        for ( from_prev = head ; from_prev != NULL && counter < from - 1 ; ++counter, from_prev = from_prev->next)
            ;  
        from_after = from_prev->next;

        counter = 0;
        for ( to_prev = head ; to_prev != NULL && counter < to - 1 ; ++counter, to_prev = to_prev->next ) 
            ; 
        to_after = to_prev->next;

        iterator<T> * ptr = from_after->next;

        from_prev->next = to_after;
        from_after->next = to_after->next;
        to_after->next = ptr;
        to_prev->next = from_after;
    }

    template<typename T>
    size_t list<T>::length_Of_list(void) const {
        iterator<T> * ptr = head;
        size_t counter = 0;
        while ( ptr ) {
            ptr = ptr->next;
            counter++;
        }
        return counter;
    }

    template<typename T>
    size_t list<T>::Count(T toSearchFor) const {
        size_t counter = 0;
        for ( iterator<T> * ptr = head ; ptr->next != nullptr ; ptr = ptr->next )
            if ( ptr->data == toSearchFor )
                ++counter;

        return counter;
    }

    template<typename T>
    T list<T>::getVal(int index) const {
        if ( index < 0 || index > _size ) {
            cout << "Out of range.\n";
            return -1;
        } else {
            iterator<T> * ptr = head;
            for ( int counter = 0 ; ptr->next != nullptr && counter < index ; ptr = ptr->next, ++counter )
                ;   
            return ptr->data;
        }
    }

    // WORKING
    template<typename T>
    size_t list<T>::getSize(void) const {
        return _size + 1;
    }

    template<typename T>
    list<T>::~list() {
        if ( head == NULL ) 
            return ;
        else {
            iterator<T> * ptr;
            while ( head != NULL ) {
                ptr = head->next;
                delete head;
                head = ptr;
            }
        }    
    }

    template<typename T>
    void list<T>::bubbleSort(void) {
        if ( head == NULL ) {
            cout << "List is empty.\n";
            return ;
        } 

        int counter = 0;
        for ( iterator<T> * ptr = head ; ptr->next != NULL ; ++counter, ptr=ptr->next )
            ;
        
        if ( counter == 1 ) {
            swap(0, 1);
            return ;
        }

        for ( iterator<T> * outer = head ; outer->next->next != NULL ; outer = outer->next ) {
            for ( iterator<T> * inner = head ; inner->next->next != NULL ; inner = inner->next ) {
                if ( inner->data > inner->next->data ) {

                    iterator<T> * inner_prev;

                    for ( inner_prev = head ; inner_prev->next != inner ; inner_prev = inner_prev->next ) 
                        ;
                    
                    iterator<T> * ptr = inner->next->next;

                    inner_prev->next = inner->next;
                    inner->next = ptr;
                    inner_prev->next->next = inner;
                }
            }
        }
    }

    template<typename T>
    void list<T>::assign(iterator<T> first, iterator<T> last) {

            iterator<T> * ptr = head;

            while ( ptr->next != nullptr ) {

                iterator<T> * temp = ptr;
                ptr = ptr->next;
                temp->next = nullptr;
                delete temp;
                temp = nullptr;

            }

            delete ptr;
            ptr = nullptr;

            for ( iterator<T> * temp = first ; temp != last ; temp = temp->next )
                insert_at_tail(temp->data);
    }

    template<typename T>
    void list<T>::assign(size_t n, const T & el = T()) {

        iterator<T> * ptr = head;

        while ( ptr->next != nullptr ) {

            iterator<T> * temp = ptr;
            ptr = ptr->next;
            temp->next = nullptr;
            delete temp;
            temp = nullptr;

        }

        delete ptr;
        ptr = nullptr;

        for ( size_t i  = 0; ; i < n ; ++i )
            insert_at_tail(el);
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

        while ( ptr->next != nullptr ) {

            iterator<T> * temp = ptr;
            ptr = ptr->next;
            temp->next = nullptr;
            delete temp;
            temp = nullptr;

        }

        delete ptr;
        ptr = nullptr;
    }

    template<typename T>
    bool list<T>::empty() const {
        return head == nullptr || tail == nullptr;
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
           delete_from_front();
           return nullptr;
       } else if ( i == tail ) {
            delete_from_end();
            return head;
       } else if ( i != head && i != tail) {

           iterator<T> * ptr = head;

           for ( ; ptr != i ; ptr = ptr->next )
                ;

            ptr->next = i->next;
            i->next = nullptr;
            delete i;
            i = nullptr;
       } else std::cout << "Edge, unknown edge case.\n";
    }

    template<typename T>
    iterator<T> list<T>::erase(iterator<T> first, iterator<T> last) {

        if ( first == head && last == tail ) {

            clear();

            return nullptr;

        } else if ( first == head ) {

            for ( iterator<T> * ptr = head->next ; ptr != last ; ptr = ptr->next ) {
                head->next = nullptr;
                delete head;
                head = nullptr;

                head = ptr;
            } 

            head = last->next;
            last->next = nullptr;

            return head;

        } else if ( last == tail ) {

            iterator<T> * temp = head;

            while ( temp != first && temp != nullptr )
                temp = temp->next;

            // Since last == tail, then as tail->next = nullptr, 
            // then last->next == nullptr
            temp->next = last->next;

            for ( iterator<T> * ptr = first->next ; ptr != last ; ptr = ptr->next ) {
                first->next = nullptr;
                delete first;
                first = nullptr;

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

            ptr->next = new iterator<T>(el, nullptr);
            ptr->next->next = tail;

            return ptr->next;

       } else {

            iterator<T> * ptr = head;

            for ( ; ptr ->next != i ; ptr = ptr->next ) ;

            iterator<T> * temp = ptr->next;
            ptr->next = new iterator<T>(el, nullptr);
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

                ptr->next = new iterator<T>(el, nullptr);
                ptr = ptr->next;

            }

            ptr->next = tail;

        } else if ( i != head && i != tail ) {
            
                iterator<T> * ptr = head;

                for ( ; ptr->next != i ; ptr = ptr->next )
                    ;   

                for ( size_t counter = 0 ; counter < n ; ++counter ) {
                    ptr->next = new iterator<T>(el, nullptr);
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
                ptr->next = new iterator<T>(deferencing->data, nullptr);
                ptr = ptr->next;                
            }

            ptr->next = i;  
        } 
    }
};

#endif