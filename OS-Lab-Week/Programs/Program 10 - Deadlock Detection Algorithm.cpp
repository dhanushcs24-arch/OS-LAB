#include <iostream>
using namespace std;

int main() {
    int n, m;

    cout << "Enter number of processes: ";
    cin >> n;

    cout << "Enter number of resource types: ";
    cin >> m;

    int allocation[n][m], request[n][m];
    int available[m];

    cout << "\nEnter Allocation Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "\nEnter Request Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> request[i][j];
        }
    }

    cout << "\nEnter Available Resources:\n";
    for (int j = 0; j < m; j++) {
        cin >> available[j];
    }

    bool finish[n];
    int work[m];

    for (int j = 0; j < m; j++) {
        work[j] = available[j];
    }

    for (int i = 0; i < n; i++) {
        bool allZero = true;

        for (int j = 0; j < m; j++) {
            if (allocation[i][j] != 0) {
                allZero = false;
                break;
            }
        }

        finish[i] = allZero;
    }

    int safeSequence[n];
    int count = 0;

    while (true) {
        bool found = false;

        for (int i = 0; i < n; i++) {

            if (!finish[i]) {

                bool possible = true;

                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {

                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }

                    finish[i] = true;
                    safeSequence[count++] = i;

                    found = true;
                }
            }
        }

        if (!found)
            break;
    }

    bool deadlock = false;

    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlock = true;
            break;
        }
    }

    if (deadlock) {
        cout << "\nSystem is in DEADLOCK.\n";
        cout << "Deadlocked processes are: ";

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                cout << "P" << i << " ";
            }
        }

        cout << endl;
    } else {
        cout << "\nSystem is NOT in deadlock.\n";

        cout << "Execution sequence:\n";
        for (int i = 0; i < count; i++) {
            cout << "P" << safeSequence[i];

            if (i != count - 1)
                cout << " -> ";
        }

        cout << endl;
    }

    return 0;
}