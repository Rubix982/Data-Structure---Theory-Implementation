#ifndef CIRCULARLINKEDLIST_H
#define CIRCULARLINKEDLIST_H

#include <iostream>

template<typename T>
struct CLL_Node
{
    CLL_Node *next;
    CLL_Node *prev;
    T data;

    CLL_Node(T data, CLL_Node<T> *next = nullptr, CLL_Node<T> *prev = nullptr)
        : data(data), next(next), prev(prev) {}
};

// Helper function
template<typename T>
CLL_Node<T> *newLink(T data, CLL_Node<T> *next = nullptr, CLL_Node<T> *prev = nullptr) {
    return new CLL_Node<T>(data, next, prev);
}

template<typename T>
class CircularLinkedList {

public:
    CircularLinkedList();
    void push_front(T newData);
    void push_back(T newData);
    T pop_front(void);
    T pop_back(void);
    void insert_after(CLL_Node<T> *prev_ptr, T newData);
    void insert_before(CLL_Node<T> *prev_ptr, T newData);
    bool isEmpty(void) const;
    void display(void);
    ~CircularLinkedList();

private:
    CLL_Node<T> *head, *tail;
};

template<typename T>
CircularLinkedList<T>::CircularLinkedList() {
    head = tail = NULL;
}

template<typename T>
bool CircularLinkedList<T>::isEmpty(void) const {
    return head == nullptr;
}

template<typename T>
void CircularLinkedList<T>::push_front(T newData)
{
    if (head == nullptr) {
        head = tail = newLink<T>(newData, nullptr, nullptr);
        tail->next = tail; tail->prev = tail;
        head->next = head; head->prev = head;
    }
    else {
        CLL_Node<T> * ptr = newLink<T>(newData);
        ptr->next = head;
        ptr->prev = tail;
        head->prev = ptr;
        tail->next = ptr;
        head = ptr;
    }
}

template<typename T>
void CircularLinkedList<T>::push_back(T newData)
{
    if (head == nullptr) {
        tail = head = newLink<T>(newData);
        head->next = head; head->prev = head;
        tail->next = tail; tail->prev = tail;
    } else {
        CLL_Node<T> * ptr = newLink<T>(newData);
        ptr->next = head;
        ptr->prev = tail;
        head->prev = ptr;
        tail->next = ptr;
        tail = ptr;
    }
}

template<typename T>
T CircularLinkedList<T>::pop_front(void)
{
    T el;
    if (head == nullptr)
        std::cout << "List is already empty.\n";
    else if ( head == tail ) {
        delete head;
        head = nullptr;
    } else {
        CLL_Node<T> *temp = head;
        el = temp->data;

        tail->next = head->next;
        head->next->prev = tail;
        head = head->next;

        delete temp;
        temp = nullptr;
    }
    return el;
}

template<typename T>
T CircularLinkedList<T>::pop_back(void) {
    T el;
    if (tail == nullptr)
        std::cout << "List is already empty.\n";
    else if ( head == tail ) {
        el = head->data;
        delete head;
        head = nullptr;
    }
    else {
        CLL_Node<T> *temp = tail;
        el = temp->data;

        head->prev = tail->prev;
        tail->prev->next = head;
        tail = tail->prev;

        delete temp;
        temp = nullptr;
    }
    return el;
}

template<typename T>
void CircularLinkedList<T>::insert_after(CLL_Node<T> *prev_ptr, T newData)
{
    if (head == nullptr)
        std::cout << "List is already empty. Can't insert after nullptr.\n";
    else
    {
        CLL_Node<T> *node = newLink<T>(newData, prev_ptr->next, prev_ptr);

        prev_ptr->next = node;
        prev_ptr->next->prev = node;
    }
}

template<typename T>
void CircularLinkedList<T>::insert_before(CLL_Node<T> *prev_ptr, T newData)
{
    if (head == nullptr) {
        std::cout << "List is already empty. Can't insert before nullptr.\n";
    } else if ( prev_ptr == head ) {
        push_front(newData);
    } else if ( prev_ptr == tail ) {
        push_back(newData);
    } else {
        CLL_Node<T> *node = newLink<T>(newData);
        node->next = prev_ptr;
        node->prev = prev_ptr->prev;

        prev_ptr->prev->next = node;
        prev_ptr->prev = node;
    }
}

template<typename T>
void CircularLinkedList<T>::display(void)
{
    if ( head == NULL ) {
        std::cout << "List is empty.\n";
        return ;
    }


    CLL_Node<T> *ptr = head;

    std::cout << ptr->data;
    while (ptr != tail && ptr->next != head)
    {
        ptr = ptr->next;
        std::cout << " <-> " << ptr->data;
    }
    std::cout << "\n";
}

template<typename T>
CircularLinkedList<T>::~CircularLinkedList() {}    

#endif