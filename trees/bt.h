#ifndef BTREE_H
#define BTREE_H

#include <queue>
#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>

typedef unsigned long long ull;
typedef long long int lli;

using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T> *left, *right;

    Node(const T &data = T(), Node<T> *left = nullptr, Node<T> *right = nullptr)
        : data(data), left(left), right(right) {}
};

template <typename T>
class bt
{

private:
    // Pointer to the root
    Node<T> *root;

    // Helper private functions, in an attempt to encapsulate the pointer to the 'root'

    void insert(const T &key, Node<T> *&node);
    Node<T> *search(T key, Node<T> *node);

    void bfs(Node<T> *node);
    void dfs(Node<T> *node);

    void preorderTraversal(Node<T> *node);
    void inorderTraversal(Node<T> *node);
    void postorderTraversal(Node<T> *node);

    ull height(Node<T> *node);
    bool isBST(Node<T> *node);
    void isBST(Node<T> *node, std::vector<T> &vect);

    // P2 Start
    
    void breadthTraverse(Node<T> * node, vector<T> & vect, lli value, lli aggregate = 0);
    void TraverseEntireTreeWithBFS(Node<T> *node, vector<T> & vect, lli value);

    // P2 End

    void deleteTree(Node<T> *node);
    void deleteNode(const T &x, Node<T> *node);

public:
    // Functions for public access, the API

    bt();

    Node<T> *search(T key);
    void insert(const T & key);
    T findmin();
    T findmax();
    Node<T> *copying(Node<T> *root);
    void bfs();
    void dfs();

    void preorderTraversal();
    void inorderTraversal();
    void postorderTraversal();

    ull height();
    bool isBST();
    bool isEmpty();
    std::vector<T> breadthTraverse(lli value);

    void TraverseEntireTreeWithBFS(lli value, vector<T> & vect);

    void deleteTree();
    void deleteNode(const T &x);

    ~bt();
};

// * The PRIVATE functions, STARTING from BELOW

template <typename T>
void bt<T>::insert(const T &key, Node<T> *&node)
{

    // if (node == nullptr) node = new Node<T>(key, nullptr, nullptr);
    // if (node->left == nullptr) node->left = new Node<T>(key, nullptr, nullptr);
    // else if (node->right == nullptr) node->right = new Node<T>(key, nullptr, nullptr);
    //
    // else {
    //     insert(key, node->left);
    //     insert(key, node->right);
    // }

    // ! READ PLEASE, THANK YOU

    // Level order insertion
    // To be extremely honest, I could not figure out what was wrong
    // with my logic in the code that is commented out above. I looked
    // up implementations for the Binary Tree, but only found
    // implementations for BSTs. The below is a level order based
    // insertion I found from GeeksForGeeks. 
    // Link is: https://www.geeksforgeeks.org/insertion-in-a-binary-tree-in-level-order/
    // Give credit where credit is due

    std::queue<Node<T> *> q;
    if ( node ) q.push(node);
    else node = new Node<T>(key, nullptr, nullptr);
    
    while ( !q.empty() ) {
        Node<T> *const ptr = q.front();
        q.pop();

        if ( ptr->left ) q.push(ptr->left);
        else { ptr->left = new Node<T>(key, nullptr, nullptr); break; }

        if ( ptr->right ) q.push(ptr->right);
        else { ptr->right = new Node<T>(key, nullptr, nullptr); break; } 
    }
}

template <typename T>
Node<T> *bt<T>::search(T key, Node<T> *node)
{
    if (node != NULL)
    {
        if (key == node->value)
            return node;
        else
        {
            return search(key, node->left);
            return search(key, node->right);
        }
    }
    else
        return NULL;
}

template <typename T>
void bfs(Node<T> *node)
{
    std::queue<Node<T> *> q;

    if (node)
    {
        q.push(node);
        std::cout << node->data << " ";
    }

    while (!q.empty())
    {
        const Node<T> *const temp = q.front();
        q.pop();

        if (temp->left)
        {
            q.push(temp->left);
            std::cout << temp->left->data << " ";
        }

        if (temp->right)
        {
            q.push(temp->right);
            std::cout << temp->right->data << " ";
        }
    }
}

template <typename T>
void bt<T>::dfs(Node<T> *node)
{
    this->inorderTraversal(this->root);
}

template <typename T>
void bt<T>::preorderTraversal(Node<T> *node)
{
    if (node != nullptr)
    {
        std::cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

template <typename T>
void bt<T>::inorderTraversal(Node<T> *node)
{
    if (node != nullptr)
    {
        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }
}

template <typename T>
void bt<T>::postorderTraversal(Node<T> *node)
{
    if (node != nullptr)
    {
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        std::cout << node->data << " ";
    }
}

template <typename T>
ull bt<T>::height(Node<T> *node)
{
    if (node == nullptr)
        return 0;

    ull left = height(node->left);
    ull right = height(node->right);

    return std::max(left, right) + 1;
}

template <typename T>
bool bt<T>::isBST(Node<T> *node) {
    std::vector<int> vect;
    isBST(node, vect);

    for (int i = 0; i < vect.size() - 1; ++i)
        if (vect[i] > vect[i + 1])
            return false;

    return true;
}

template <typename T>
void bt<T>::isBST(Node<T> *node, std::vector<T> &vect)
{
    if (node != nullptr)
    {
        isBST(node->left, vect);
        vect.push_back(node->data);
        isBST(node->right, vect);
    }
}

template <typename T>
void bt<T>::breadthTraverse(Node<T> * node, vector<T> & vect, lli value, lli aggregate) {

    std::queue<Node<T> *> q;
    vector<T> temp_vect;

    if ( node != nullptr || !( this->isBST(node) ) ) { q.push(node); }
    else return ;
    
    if ( node->data == value ) {
        temp_vect.push_back(node->data);
        return ;
    }

    lli sum = 0;
    while ( !q.empty() ) {
        int size = q.size();

        while ( size-- ) {
            Node<T> * temp_ptr = q.front();
            q.pop();

            sum += temp_ptr->data;
            temp_vect.push_back(temp_ptr->data);

            if ( temp_ptr->left != nullptr ) { q.push(temp_ptr->left); };
            if ( temp_ptr->right != nullptr ) { q.push(temp_ptr->right); };
        }

        if ( accumulate(temp_vect.begin(), temp_vect.end(), 0) == value && vect.size() == 0 ) vect = temp_vect;
    }
}

template <typename T>
void bt<T>::deleteTree(Node<T> *node)
{
    if (node != nullptr)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
        node = nullptr;
    }
}

template <typename T>
void bt<T>::deleteNode(const T &x, Node<T> *node)
{
    if (node == nullptr)
        return;
    else if (x < node->data)
        deleteNode(x, node->left);
    else if (x > node->data)
        deleteNode(x, node->right);

    if (node->left == nullptr and node->right == nullptr)
    {
        delete node;
        node = nullptr;
        return;
    }
    else if (root->left != nullptr && root->right != nullptr)
    {
        node->data = this->findmax(node->left);
    }
}

template <typename T>
void bt<T>::TraverseEntireTreeWithBFS(Node<T> *node, vector<T> & vect, lli value) {
    if ( node != nullptr ) {
        TraverseEntireTreeWithBFS(node->left, vect, value);
        breadthTraverse(node, vect, value);
        TraverseEntireTreeWithBFS(node->right, vect, value);
    }
}

// * The PRIVATE functions, ENDING from ABOVE

// * The PUBLIC functions, STARTING from BELOW

template <typename T>
bt<T>::bt() : root(nullptr) {}

template <typename T>
Node<T> *bt<T>::search(T key)
{
    this->search(key, this->root);
}

template <typename T>
void bt<T>::insert(const T & key)
{
    this->insert(key, this->root);
}

template <typename T>
Node<T> *bt<T>::copying(Node<T> *root)
{
    if (root == nullptr) return new T();
    else new Node<T>(root->data, copying(root->left), copying(root->right));
}

template <typename T>
void bt<T>::bfs()
{
    this->bfs(this->root);
}

template <typename T>
void bt<T>::dfs()
{
    this->dfs(this->root);
}

template <typename T>
void bt<T>::preorderTraversal()
{
    this->preorderTraversal(this->root);
    std::cout << "\n";
}

template <typename T>
void bt<T>::inorderTraversal()
{
    this->inorderTraversal(this->root);
    std::cout << "\n";
}

template <typename T>
void bt<T>::postorderTraversal()
{
    this->postorderTraversal(this->root);
    std::cout << "\n";
}

template <typename T>
ull bt<T>::height()
{
    return this->height(this->root);
}

template <typename T>
bool bt<T>::isBST()
{
    std::vector<int> vect;
    isBST(this->root, vect);

    for (int i = 0; i < vect.size() - 1; ++i)
        if (vect[i] > vect[i + 1])
            return false;

    return true;
}

template <typename T>
bool bt<T>::isEmpty()
{
    return this->root == nullptr;
}

template<typename T>
std::vector<T> bt<T>::breadthTraverse(lli value) {
    vector<T> vect;
    this->TraverseEntireTreeWithBFS(value, vect);
    return vect;
}

template <typename T>
void bt<T>::TraverseEntireTreeWithBFS(lli value, vector<T> & vect) {
    this->TraverseEntireTreeWithBFS(this->root, vect, value);
}

template <typename T>
void bt<T>::deleteTree()
{
    this->deleteTree(this->root);
}

template <typename T>
bt<T>::~bt()
{
    this->deleteTree(this->root);
}

// * The PUBLIC functions, ENDING from ABOVE

#endif