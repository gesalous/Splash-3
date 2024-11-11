#include "lock.h"
#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
// Shared resources
static volatile uint64_t counter;

// Thread argument structure
struct worker{
    uint64_t operations_per_thread;
    int thread_id;
    ges_lock_t lock;
};

// Thread function
void *thread_work(void *arg) {
    struct worker *worker = (struct worker *)arg;
    struct ges_node node = {0};
    for (uint64_t i = 0; i < worker->operations_per_thread; i++) {
      ges_lock(worker->lock, &node);
      counter++;
      ges_unlock(worker->lock, &node);
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <num_threads> <total_operations>\n", argv[0]);
        return 1;
    }

    // Parse command line arguments
    int num_threads = atoi(argv[1]);
    uint64_t total_operations = atoll(argv[2]);

    if (num_threads <= 0 || total_operations <= 0) {
        fprintf(stderr, "Error: Both arguments must be positive numbers\n");
        return 1;
    }

    if (total_operations % num_threads != 0) {
        fprintf(stderr, "Error: Total operations must be evenly divisible by number of threads\n");
        return 1;
    }
  
    ges_lock_t lock = ges_lock_init();

    // Calculate operations per thread
    long long operations_per_thread = total_operations / num_threads;

    // Create thread arguments and thread array
    pthread_t *threads = calloc(num_threads, sizeof(pthread_t));
    struct worker *workers = calloc(num_threads, sizeof(struct worker));

    if (!threads || !workers) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }

    // Record start time
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Create threads
    for (int i = 0; i < num_threads; i++) {
        workers[i].operations_per_thread = operations_per_thread;
        workers[i].thread_id = i;
        workers[i].lock = lock;
        
        int ret = pthread_create(&threads[i], NULL, thread_work, &workers[i]);
        if (ret != 0) {
            fprintf(stderr, "Error: Failed to create thread %d: %s\n", i, strerror(ret));
            return 1;
        }
    }

    // Wait for all threads to complete
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    // Record end time
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    // Calculate elapsed time in seconds
    double elapsed = (end_time.tv_sec - start_time.tv_sec) +
                    (end_time.tv_nsec - start_time.tv_nsec) / 1e9;

    // Verify results
    if (counter == total_operations) {
        printf("Test successful!\n");
        printf("Final counter value: %lu\n", counter);
        printf("Expected value: %lu\n", total_operations);
        printf("Number of threads: %d\n", num_threads);
        printf("Operations per thread: %lld\n", operations_per_thread);
        printf("Total time: %.3f seconds\n", elapsed);
        printf("Operations per second: %.2f\n", total_operations / elapsed);
    } else {
        printf("Test failed!\n");
        printf("Final counter value: %lu\n", counter);
        printf("Expected value: %lu\n", total_operations);
    }

    // Cleanup
    free(threads);
    free(workers);

    return (counter == total_operations) ? 0 : 1;
}

