#include "../include/lock.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct ges_lock {
  volatile int locked;
};

ges_lock_t ges_lock_init(void) {
  return calloc(1UL, sizeof(struct ges_lock));
}

void ges_lock(ges_lock_t lock, ges_node_t node) {
  (void)node;
  while (__sync_lock_test_and_set(&lock->locked, 1)) {
    // Optional: CPU hint that we're in a spin-wait loop
    __builtin_ia32_pause();
  }
}

void ges_unlock(ges_lock_t lock, ges_node_t node) {
  (void)node;
  __sync_lock_release(&lock->locked);
}
