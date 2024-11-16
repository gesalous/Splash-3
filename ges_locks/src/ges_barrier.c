#include "../include/ges_barrier.h"
#include <stdlib.h>
#include <stdio.h>
void ges_barrier_init(ges_barrier_t *barrier) {
  barrier->counter = 0;
  barrier->flag = 0;
}

void ges_barrier_wait(ges_barrier_t *barrier, uint64_t num_proc) {
    uint64_t current_flag = barrier->flag;
    fprintf(stderr, "Barrier target is %lu\n",num_proc); 
    // Decrement counter and get previous value
    if (num_proc != __sync_fetch_and_add(&barrier->counter, 1)) {
        barrier->counter = 0;
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

