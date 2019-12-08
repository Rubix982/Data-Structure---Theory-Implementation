#ifndef DSA_H
#define DSA_H

#include <fstream>
#include <iostream>
#include <cstring>

template<typename T>
class DSA {
protected:
    T * Buffer;
    int Size;

public:

    // Constructor
    DSA(int size) {
        this->Size = size;
        Buffer = ( Size == 0 ? 0 : new T[this->Size] );
        memset(Buffer, 0, sizeof(T)*this->Size);
    }

    // Copy Constructor
    DSA(const DSA &obj)
        :   Size(obj.Size), Buffer(new T[obj.Size]) {
            memcpy(this->Buffer, obj.Buffer, sizeof(T)*obj.Size);
    }

    // Assignment Operator
    DSA<T> &operator=(const DSA<T> & rhs) {
        if ( this != &rhs ) {
            
            // Delete old buffer
            delete[] Buffer;

            // If new fails afterwards, setting it to 0
            // if a safe check that there is no dangling
            // pointer left
            Buffer = 0;    
            
            // Send to copy constructor, otherwise there
            // is code duplication here
            Size = rhs.Size;
            Buffer = new T[rhs.Size];
            memcpy(this->Buffer, rhs.Buffer, sizeof(T) * rhs.Size);
        }
        return *this;
    }

    // Index Operator
    int operator[](int index) {
        if ( index < 0 || index > Size - 1 ) {
            std::cout << "Out of bounds exception.\n";
            return -1;
        }
        else 
            return Buffer[index];
    }

    // Resize Operator
    void resize(int newSize) {
        if ( newSize != this->Size ) {
            int * temp = new T[this->Size];
            memcpy(temp, Buffer, sizeof(T)*this->Size);

            delete[] Buffer;
            Buffer = 0;

            int oldSize = this->Size;
            this->Size = newSize;
            Buffer = new T[this->Size];

            // Set all to 0 first
            memset(Buffer, 0, sizeof(T)*Size);
            
            // Copy back the previous data
            memcpy(Buffer, temp, sizeof(T)*oldSize);

            delete[] temp;
            temp = 0;
        
            std::cout << "New array successfully created.\n";
        }
    }

    // Extraction
    template<typename M>
    friend std::ostream &operator<<(std::ostream &outFile, const DSA<M> &obj);

    // Insertion
    template<typename M>
    friend std::istream &operator>>(std::istream &inFile, DSA<M> &obj);

    // getSize
    int getSize(void) {
        return this->Size;
    }

    // Insertion
    void insert(T element, int index) {
        if ( index < 0 || index > Size - 1)
            std::cout << "Out of bounds exception.\n";
        else
            Buffer[index] = element;
    }

    // Searching
    int search(T element) {
        for ( int i = 0 ; i < Size ; ++i )
            if ( this->Buffer[i] == element )
                return i;
        
        std::cout << element << " not found in Buffer.\n";
        return -1;
    }

    // Destructor
    ~DSA() {
        delete[] Buffer;
        Buffer = 0;
    }
};

// Extraction
template<typename T>
std::ostream &operator<<(std::ostream &outFile, const DSA<T> &obj) {
    
    for ( int i = 0 ; i < obj.Size ; ++i )
        outFile << obj.Buffer[i] << " ";
    outFile << std::endl;

    return outFile;
}

// Insertion
template<typename T>
std::istream &operator>>(std::istream &inFile, DSA<T> &obj) {
    for (int i = 0; i < obj.Size; ++i)
        inFile >> obj.Buffer[i];

    std::cout << std::endl;

    return inFile;
}

#endif