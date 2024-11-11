#include "../include/ges_barrier.h"
#include <stdlib.h>

void ges_barrier_init(ges_barrier_t *barrier, int num_threads) {
  barrier->counter = num_threads;
  barrier->flag = 0;
  barrier->num_threads = num_threads;
}

void ges_barrier_wait(ges_barrier_t *barrier) {
    uint64_t current_flag = barrier->flag;
    
    // Decrement counter and get previous value
    if (1 == __sync_fetch_and_sub(&barrier->counter, 1)) {
        barrier->counter = barrier->num_threads; 
        barrier->flag = !current_flag; 
    } else {
        // Wait for flag to change
        while (barrier->flag == current_flag) {
            // CPU-friendly busy wait
            __asm__ volatile("pause" ::: "memory");
        }
    }
}

void atomic_barrier_destroy(ges_barrier_t *barrier) {
    (void)barrier;
}

