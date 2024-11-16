#ifndef GES_BARRIER_H
#define GES_BARRIER_H
#include <stdint.h>
typedef struct {
    volatile uint64_t counter;     // Tracks number of arrived threads
    volatile uint64_t flag;       // Sense flag for barrier synchronization
} ges_barrier_t;

void ges_barrier_init(ges_barrier_t *barrier);

void ges_barrier_wait(ges_barrier_t *barrier, uint64_t num_proc);

// Destroy the barrier
void ges_barrier_destroy(ges_barrier_t *barrier);
#endif
