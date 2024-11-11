#include "../include/ges_lock.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>




void ges_lock_init(ges_lock_t *lock) {

  lock->tail = NULL;
}

void ges_lock(ges_lock_t *lock, ges_node_t *node) {

  node->next = NULL;
  node->waiting = true;

  // Atomically set the tail to the current node and get the previous tail
  ges_node_t * prev = (ges_node_t *)__sync_lock_test_and_set(&lock->tail, node);
  if (NULL == prev)
    return;

  prev->next = node;
  while (node->waiting) {
    __builtin_ia32_pause();
  }
}

void ges_unlock(ges_lock_t *lock, ges_node_t *node) {
  if (node->next == NULL) {
    if (__sync_bool_compare_and_swap((uint64_t *)&lock->tail, (uint64_t)node,
                                     NULL)) {
      return; // Successfully released the lock
    }
    // Wait for the next node to be set
    while (node->next == NULL) {
      __builtin_ia32_pause(); // Hint to the CPU
    }
  }
  // Wake up the next thread
  node->next->waiting =
      false; // Set the waiting flag of the next node to false
}

