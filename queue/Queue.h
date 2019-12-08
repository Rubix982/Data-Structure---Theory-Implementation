#ifndef QUEUE_H
#define QUEUE_H

class Queue {
    private:
        int front, rear, size;
        int * arr;

    public:

    Queue(int size)
        :   size(size), front(-1), rear(-1) {
            arr = new int[size];
        }

    void enqueue(int data) {
        if (!isFull()) {
            rear++;
            arr[rear] = data;
            if ( front == - 1) 
                front = 0;
        }
    }

    void dequeue(void) {
        if (!isEmpty()) {
            if ( front == rear )
                front = rear = -1;
            else 
                front++;
        }
    }

    bool isFull(void) {
        return rear == size - 1;
    }

    bool isEmpty(void) {
        return front == -1;
    }
};

#endif