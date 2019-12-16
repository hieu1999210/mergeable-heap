#include <iostream>
#include <vector>
using namespace std;




void
display_input(int *n, int *m, vector<vector<short>*> *edges) {
    cout << "n: " << *n << "  m: " << *m << endl;
    vector<short> * vertex;
    for (int i=1; i<edges->size(); ++i) {
        cout << "vertex " << i << ": ";
        vertex = (*edges)[i];
        for (int j=1; j<vertex->size(); j++) {
            cout << (*vertex)[j] << "  ";
        }
        cout << endl;
    } 
}

void
read_input(int* n, int* m, vector<vector<short>*>* &edges) {
    cin >> *n >> *m;
    // cout << *n << *m;
    short lower_town, upper_town;
    edges = new vector<vector<short>*>(*n+1);
    for (int i=1; i<edges->size(); ++i) {
        (*edges)[i] = new vector<short>(1);
    }
    // cout << "edge size " << edges->size() << endl;
    for (int i=0; i<*m; ++i) {
        cin >> lower_town >> upper_town;
        (*edges)[upper_town]->push_back(lower_town);
        (*edges)[lower_town]->push_back(-upper_town);
    }
    // display_input(n, m, edges);
}


int
main() {
    vector<vector<short>*>* edges;
    int *n = new int;
    int *m = new int;

    read_input(n, m, edges);
    // cout << "edge size " << edges->size() << endl;
    display_input(n, m, edges);
}