#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

using namespace std;

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t emptyslots;
sem_t full;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;

    for(int i = 0; i < 10; i++) {
        item = rand() % 100;

        sem_wait(&emptyslots);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        cout << "Produced: " << item << " at position " << in << endl;
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1);
    }

    pthread_exit(NULL);
}

void* consumer(void* arg) {
    int item;

    for(int i = 0; i < 10; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        item = buffer[out];
        cout << "Consumed: " << item << " from position " << out << endl;
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&emptyslots);

        sleep(2);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t prod, cons;

    sem_init(&emptyslots, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&emptyslots);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}