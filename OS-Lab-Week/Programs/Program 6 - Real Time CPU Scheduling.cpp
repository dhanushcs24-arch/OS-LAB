#include <bits/stdc++.h>
using namespace std;

#define SIM_TIME 50

struct Task {
    int id;
    int execution;
    int period;
    int deadline;
    int remaining;
    int next_release;
    int weight;
};

void resetTasks(vector<Task> &tasks) {
    for (auto &t : tasks) {
        t.remaining = 0;
        t.next_release = 0;
        t.deadline = t.period;
    }
}

void rateMonotonic(vector<Task> tasks) {
    cout << "\nRate Monotonic Scheduling\n";

    for (int time = 0; time < SIM_TIME; time++) {

        for (auto &t : tasks) {
            if (time == t.next_release) {
                t.remaining = t.execution;
                t.next_release += t.period;
            }
        }

        int selected = -1;
        int min_period = INT_MAX;

        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].remaining > 0 && tasks[i].period < min_period) {
                min_period = tasks[i].period;
                selected = i;
            }
        }

        if (selected != -1) {
            cout << "Time " << time << ": Task " << tasks[selected].id << "\n";
            tasks[selected].remaining--;
        } else {
            cout << "Time " << time << ": Idle\n";
        }
    }
}

void earliestDeadlineFirst(vector<Task> tasks) {
    cout << "\nEarliest Deadline First\n";

    for (int time = 0; time < SIM_TIME; time++) {

        for (auto &t : tasks) {
            if (time == t.next_release) {
                t.remaining = t.execution;
                t.deadline = time + t.period;
                t.next_release += t.period;
            }
        }

        int selected = -1;
        int earliest_deadline = INT_MAX;

        for (int i = 0; i < tasks.size(); i++) {
            if (tasks[i].remaining > 0 && tasks[i].deadline < earliest_deadline) {
                earliest_deadline = tasks[i].deadline;
                selected = i;
            }
        }

        if (selected != -1) {
            cout << "Time " << time << ": Task " << tasks[selected].id << "\n";
            tasks[selected].remaining--;
        } else {
            cout << "Time " << time << ": Idle\n";
        }
    }
}

void proportionalScheduling(vector<Task> tasks) {
    cout << "\ncProportional Scheduling\n";

    int n = tasks.size();
    int current = 0;
    int slice = tasks[0].weight;

    for (int time = 0; time < SIM_TIME; time++) {

        if (slice == 0) {
            current = (current + 1) % n;
            slice = tasks[current].weight;
        }

        cout << "Time " << time << ": Task " << tasks[current].id << "\n";
        slice--;
    }
}

int main() {

    int n;
    cout << "Enter number of tasks: ";
    cin >> n;

    vector<Task> tasks(n);

    for (int i = 0; i < n; i++) {
        cout << "\nTask " << i + 1 << "\n";

        tasks[i].id = i + 1;

        cout << "Execution Time: ";
        cin >> tasks[i].execution;

        cout << "Period: ";
        cin >> tasks[i].period;

        cout << "Weight: ";
        cin >> tasks[i].weight;

        tasks[i].remaining = 0;
        tasks[i].next_release = 0;
        tasks[i].deadline = tasks[i].period;
    }

    rateMonotonic(tasks);

    resetTasks(tasks);
    earliestDeadlineFirst(tasks);

    resetTasks(tasks);
    proportionalScheduling(tasks);

    return 0;
}

