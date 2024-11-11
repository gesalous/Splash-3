#include "../include/lock.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct ges_lock {
  volatile uint64_t next_ticket;
  volatile uint64_t current_ticket;
};

ges_lock_t ges_lock_init(void) {
  ges_lock_t lock = calloc(1UL, sizeof(struct ges_lock));
  lock->next_ticket = 0;
  lock->current_ticket = 0;
  return lock;
}

void ges_lock(ges_lock_t lock, ges_node_t node) {
  (void)node;
  uint64_t ticket = __sync_fetch_and_add(&lock->next_ticket, 1);
  while (__sync_fetch_and_add(&lock->current_ticket, 0) != ticket) {
    __builtin_ia32_pause(); // Hint to the CPU that we're spinning
  }
}

void ges_unlock(ges_lock_t lock, ges_node_t node) {
  (void)node;
  __sync_fetch_and_add(&lock->current_ticket, 1);
}
