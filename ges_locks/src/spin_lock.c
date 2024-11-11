#include "../include/ges_lock.h"
#include <stdio.h>
#include <stdlib.h>


void ges_lock_init(ges_lock_t * lock) {
  lock->locked = 0;
}

void ges_lock(ges_lock_t *lock, ges_node_t *node) {
  (void)node;
  while (__sync_lock_test_and_set(&lock->locked, 1)) {
    // Optional: CPU hint that we're in a spin-wait loop
    __builtin_ia32_pause();
  }
}

void ges_unlock(ges_lock_t *lock, ges_node_t *node) {
  (void)node;
  __sync_lock_release(&lock->locked);
}
