#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

class CircularQueue {
    private:
        int front, rear, size;
        int * arr;

    public:

    CircularQueue(int size)
        :   size(size), front(-1), rear(-1) {
            arr = new int[size];
        }

    void enqueue(int x) {
        if ( !isFull() ) {
            if ( rear == size - 1 || rear == -1 ) {
                rear = 0;
                arr[rear] = x;
                if ( front == -1 )
                    front == 0;
            }
        } else {
            rear++;
            arr[rear] =x;
        }
    }

    void dequeue(int x) {
        if ( !isEmpty() ) {
            if ( front == rear )
                front = rear = -1;
            else if ( front == size - 1)
                front = 0;
        } else 
            front++;
    }

    bool isFull(void) {
        return ( (rear == size - 1 && front == 0) || (front == rear + 1) );
    }

    bool isEmpty(void) {
        return front == -1;
    }
};

#endif