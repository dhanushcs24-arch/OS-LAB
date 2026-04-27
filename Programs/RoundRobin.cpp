#include <iostream>
#include <queue>
using namespace std;

int main() {
    int n, tq;

    cout << "Enter number of processes: ";
    cin >> n;

    int at[n], bt[n], rem_bt[n], ct[n], tat[n], wt[n];

    for(int i = 0; i < n; i++) {
        cout << "Enter Arrival Time for P" << i+1 << ": ";
        cin >> at[i];
        cout << "Enter Burst Time for P" << i+1 << ": ";
        cin >> bt[i];
        rem_bt[i] = bt[i];
    }

    cout << "Enter Time Quantum: ";
    cin >> tq;

    int time = 0, completed = 0;

    while(completed < n) {
        bool executed = false;

        for(int i = 0; i < n; i++) {

            if(at[i] <= time && rem_bt[i] > 0) {
                executed = true;

                if(rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                }
                else {
                    time += rem_bt[i];
                    ct[i] = time;
                    rem_bt[i] = 0;
                    completed++;
                }
            }
        }

        if(!executed)
            time++; 
    }

    for(int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";

    for(int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t" << at[i] << "\t" << bt[i] << "\t" 
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << endl;
    }

    return 0;
}
