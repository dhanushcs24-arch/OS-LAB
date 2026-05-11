#include <stdio.h>
#include <semaphore.h>

#define N 5

sem_t chopstick[5];
sem_t room;

void wait_sem(sem_t *s) {
    sem_wait(s);
}

void signal_sem(sem_t *s) {
    sem_post(s);
}

void Philosopher(int i) {

    printf("P %d is waiting\n", i);

    wait_sem(&room);

    wait_sem(&chopstick[i-1]);
    wait_sem(&chopstick[i%5]);

    printf("P %d is granted to eat\n", i);
    printf("P %d has finished eating\n", i);

    signal_sem(&chopstick[i-1]);
    signal_sem(&chopstick[i%5]);

    signal_sem(&room);
}

int main() {
    int i, choice;

    for(i = 0; i < 5; i++)
        sem_init(&chopstick[i], 0, 1);

    sem_init(&room, 0, 4);

    while(1) {
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice == 3)
            break;

        if(choice == 1) {
            printf("\nAllow one philosopher to eat at any time\n");

            for(i = 1; i <= 5; i++) {
                Philosopher(i);
            }
        }

        else if(choice == 2) {
            printf("\nAllow two philosophers to eat at same time\n");

            for(i = 1; i <= 5; i += 2) {

                printf("P %d is waiting\n", i);
                if(i + 1 <= 5)
                    printf("P %d is waiting\n", i + 1);

                printf("P %d is granted to eat\n", i);
                if(i + 1 <= 5)
                    printf("P %d is granted to eat\n", i + 1);

                printf("P %d has finished eating\n", i);
                if(i + 1 <= 5)
                    printf("P %d has finished eating\n", i + 1);
            }
        }

        else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}