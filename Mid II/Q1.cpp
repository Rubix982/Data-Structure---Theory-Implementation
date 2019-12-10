#include <bits/stdc++.h>
using namespace std;

int N;
typedef pair<int, int> pii;
vector<pii> vect;

int main(void) {


    std::ofstream Compatible("Compatible.txt"), Conflicting("Conflicting.txt");
    cin >> N;
    int A[N], B[N], C[N];

    for ( int i = 0 ; i < N ; ++i ) {
        cin >> A[i] >> B[i] >> C[i];
        vect.push_back(make_pair(A[i], A[i] + B[i] + C[i]));
    }
   
    std::sort(vect.begin(), vect.end(), [](pii first, pii second) { return first.first < second.first; });
    for ( int i = 0; i < N ; ) {
        if ( vect[i].second > vect[i + 1].first && ( i + 1 ) != N ) {
            Compatible << A[i] << " " << B[i] << " " << C[i] << "\n";
            Conflicting << A[i + 1] << " " << B[i + 1] << " " << C[i + 1] << "\n";
            i += 2;
        } else if ( i < N ) {
            Compatible << A[i] << " " << B[i] << " " << C[i] << "\n";
            ++i;
        } 
        
        if ( (i + 1) == N ) {
            Compatible << A[i - 1] << " " << B[i - 1] << " " << C[i - 1] << "\n";
            break;
        }
    }

    Compatible.close();
    Conflicting.close();
}