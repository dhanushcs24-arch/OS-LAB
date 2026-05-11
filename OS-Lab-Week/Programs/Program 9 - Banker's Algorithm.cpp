#include <iostream>
using namespace std;

int main() {
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resources: ";
    cin >> m;

    int alloc[n][m], max[n][m], need[n][m];
    int avail[m];

    cout << "\nEnter Allocation Matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> alloc[i][j];
        }
    }

    cout << "\nEnter Max Matrix:\n";
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    cout << "\nEnter Available Resources:\n";
    for(int i = 0; i < m; i++) {
        cin >> avail[i];
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    bool finish[n] = {false};
    int safeSeq[n];
    int work[m];

    for(int i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    int count = 0;

    while(count < n) {
        bool found = false;

        for(int p = 0; p < n; p++) {

            if(finish[p] == false) {

                bool possible = true;

                for(int j = 0; j < m; j++) {
                    if(need[p][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if(possible) {

                    for(int j = 0; j < m; j++) {
                        work[j] += alloc[p][j];
                    }

                    safeSeq[count] = p;
                    count++;

                    finish[p] = true;
                    found = true;
                }
            }
        }

        if(found == false) {
            cout << "\nSystem is NOT in safe state.\n";
            return 0;
        }
    }

    cout << "\nSystem is in SAFE state.\n";
    cout << "Safe Sequence: ";

    for(int i = 0; i < n; i++) {
        cout << "P" << safeSeq[i];

        if(i != n - 1)
            cout << " -> ";
    }

    cout << endl;

    return 0;
}