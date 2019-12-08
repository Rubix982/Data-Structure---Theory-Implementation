#ifndef PRIMM_H
#define PRIMM_H

#include <queue>
#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int MAX = 1e5;
typedef pair<long long, int> pii;
bool marked[MAX];
vector<pii> adj[MAX];

long long primms(int x) {
    priority_queue<pii, vector<pii>, greater<pii>> Q;
    pii p;
    Q.push(make_pair(x, 0));
    int y;
    long long minimumCost = 0;

    while ( !Q.empty() ) {
        
        // Select the edge with minimum weight
        p = Q.top();
        Q.pop();

        x = p.second;

        // Checking for cycle
        if ( marked[x] == true )
            continue;
        marked[x] = true;
        minimumCost += p.first;
        for ( int i = 0 ; i < adj[x].size() ; ++i ) {
            y = adj[x][i].second;

            if ( marked[y] == false )
                Q.push(adj[x][i]);
        }
    }
}

void start(void) {
    int nodes, edges, x, y;
    long long cost, minimumCost = 0;
    cin >> nodes >> edges;

    for ( int i = 0; i < edges ; ++i ) {
        cin >> x >> y >> cost;
        adj[x].push_back(make_pair(cost, y));
        adj[x].push_back(make_pair(cost, y));
    }

    cout << primms(1) << "\n";
}

#endif