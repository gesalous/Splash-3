#include "../include/ges_lock.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


void ges_lock_init(ges_lock_t *lock) {
  lock->ticket.next_ticket = 0;
  lock->ticket.current_ticket = 0;
}

void ges_lock(ges_lock_t *lock, ges_node_t *node) {
  (void)node;
  uint64_t ticket = __sync_fetch_and_add(&lock->ticket.next_ticket, 1);
  while (__sync_fetch_and_add(&lock->ticket.current_ticket, 0) != ticket) {
    __builtin_ia32_pause(); // Hint to the CPU that we're spinning
  }
}

void ges_unlock(ges_lock_t *lock, ges_node_t *node) {
  (void)node;
  __sync_fetch_and_add(&lock->ticket.current_ticket, 1);
}
