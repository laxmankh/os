#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopstick[NUM_PHILOSOPHERS];
pthread_t philosopher[NUM_PHILOSOPHERS];

void *philosopher_action(void *arg) {
    int philosopher_id = *(int *)arg;
    int left_chopstick = philosopher_id;
    int right_chopstick = (philosopher_id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking\n", philosopher_id);
        sleep(rand() % 3); // Simulate thinking

        // Pick up chopsticks
        pthread_mutex_lock(&chopstick[left_chopstick]);
        printf("Philosopher %d picked up left chopstick %d\n", philosopher_id, left_chopstick);
        pthread_mutex_lock(&chopstick[right_chopstick]);
        printf("Philosopher %d picked up right chopstick %d\n", philosopher_id, right_chopstick);

        // Eating
        printf("Philosopher %d is eating\n", philosopher_id);
        sleep(rand() % 3); // Simulate eating

        // Put down chopsticks
        pthread_mutex_unlock(&chopstick[left_chopstick]);
        printf("Philosopher %d put down left chopstick %d\n", philosopher_id, left_chopstick);
        pthread_mutex_unlock(&chopstick[right_chopstick]);
        printf("Philosopher %d put down right chopstick %d\n", philosopher_id, right_chopstick);
    }
}

int main() {
    int i;
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutex locks for each chopstick
    for (i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_init(&chopstick[i], NULL);
    }

    // Create threads for each philosopher
    for (i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosopher_ids[i] = i;
        pthread_create(&philosopher[i], NULL, philosopher_action, &philosopher_ids[i]);
    }

    // Wait for threads to finish (this will never happen due to the infinite loop in philosopher_action)
    for (i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_join(philosopher[i], NULL);
    }

    // Cleanup
    for (i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_destroy(&chopstick[i]);
    }

    return 0;
}
