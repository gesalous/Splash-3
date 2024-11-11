#ifndef GES_BARRIER_H
#define GES_BARRIER_H
#include <stdint.h>
typedef struct {
    volatile uint64_t counter;     // Tracks number of arrived threads
    volatile uint64_t flag;       // Sense flag for barrier synchronization
    volatile int num_threads;        // Total number of threads to wait for
} ges_barrier_t;

void ges_barrier_init(ges_barrier_t *barrier, int num_threads);

void ges_barrier_wait(ges_barrier_t *barrier);

// Destroy the barrier
void ges_barrier_destroy(ges_barrier_t *barrier);
#endif
