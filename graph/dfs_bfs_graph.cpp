#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

// ! NOTE: This code is for UNDIRECTED 

// * INPUT FORMAT
/*
    First two numbers are the nodes 'n' and the edges 'k'
    Next k lines take two numbers, the indexes of the nodes to join
*/

void addEdge(vector<int> vect[], int x, int y) {
    vect[x].push_back(y);
    vect[y].push_back(x);
}

void dfs(vector<int> vect[], bool discovered[], int vertex) {
    discovered[vertex] = true;
    std::cout << vertex << " ";

    for ( const auto & neighbors : vect[vertex]) 
        if ( discovered[neighbors] != true )
            dfs(vect, discovered, neighbors);
}

void bfs(vector<int> vect[], int nodes, int vertex) {

    vector<bool> discovered(nodes, false);

    discovered[vertex] = true;

    queue<int> q;

    q.push(vertex);

    while ( !q.empty() ) {
        vertex = q.front();
        q.pop();
        std::cout << vertex << " ";

        for ( const auto & value : vect[vertex] )
            if ( !discovered[value] ) {
                q.push(value);
                discovered[value] = true;
            }
    }
    std::cout << "\n";
} 

int main(void) {

    ull nodes, edges;
    cin >> nodes >> edges;

    vector<int> vect[nodes];

    for ( int i = 0; i < edges ; ++i ) {
        ull x, y;
        cin >> x >> y;
        addEdge(vect, x, y);
    }

    for ( int i = 0; i < nodes ; ++i ) {
        std::cout << i << ": ";
        for ( const auto & dst : vect[i] )
            cout << dst << " ";
        cout << "\n";
    }

    bool discovered[nodes];

    dfs(vect, discovered, 0);
    std::cout << "\n";

    bfs(vect, nodes, 0);
}