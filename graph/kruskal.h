#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <map>
#include <cstring>
#include <iostream>
using namespace std;

const int MAX = 1e5;
typedef pair<long long, pair<int, int>> ppii;
ppii p[MAX];
int edges, nodes, id[MAX];

void initialize(void) {
    for ( int i = 0; i < MAX ; ++i ) id[i] = i;
}

// Using Disjunctive Set Approach
int root(int x) {
    while ( x != id[x] ) x = id[x] = id[id[x]];
    return x;
}

void union1(int x, int y) {
    int p = root(x), q = root(y);
    id[p] = id[q];
}

long long kruskal(ppii p[]) {

    initialize();
    long long cost, minimumCost = 0 ;
    int x, y;

    for ( int i = 0 ; i < edges ; ++i ) {
        x = p[i].second.first;
        y = p[i].second.second;

        cost = p[i].first;

        if ( root(x) != root(y) ) {
            minimumCost += cost;
            union1(x, y);
        }
    }

    return minimumCost;
}

// Use this function
void start(void) {
    int x, y;
    long long weight; 

    cin >> nodes >> edges;

    for ( int i = 0; i < edges ; ++i ) {
        cin >> x >> y >> weight;
        p[i] = make_pair(weight, make_pair(x, y));
    }

    cout << "Minimum cost: " << kruskal(p) << "\n"; 
}

#endif