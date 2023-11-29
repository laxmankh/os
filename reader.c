#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3
#define NUM_WRITERS 2

sem_t mutex, write_block;
int data = 0;
int readers_count = 0;

void *reader(void *arg) {
    int reader_id = *((int *)arg);

    while (1) {
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&write_block);
        }
        sem_post(&mutex);

        // Reading data
        printf("Reader %d reads data: %d\n", reader_id, data);

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&write_block);
        }
        sem_post(&mutex);

        // Simulating some processing time for reading
        sleep(rand() % 3);
    }

    pthread_exit(NULL);
}

void *writer(void *arg) {
    int writer_id = *((int *)arg);

    while (1) {
        sem_wait(&write_block);

        // Writing data
        data++;
        printf("Writer %d writes data: %d\n", writer_id, data);

        sem_post(&write_block);

        // Simulating some processing time for writing
        sleep(rand() % 3);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&write_block, 0, 1);

    srand(time(NULL));

    // Create reader threads
    for (int i = 0; i < NUM_READERS; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, (void *)&reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, (void *)&writer_ids[i]);
    }

    // Let the program run for a while
    sleep(20);

    // Clean up
    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_cancel(readers[i]);
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_cancel(writers[i]);
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&write_block);

    return 0;
}
