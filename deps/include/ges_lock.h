#ifndef GES_LOCK_H
#define GES_LOCK_H
#include <stdint.h>

enum lock_type {SPIN_LOCK = 1, TICKET_LOCK, MCS_LOCK};

typedef struct ges_node{
  struct ges_node *next;
  volatile unsigned char waiting;
}ges_node_t;

struct ges_ticket {
  volatile uint64_t next_ticket;
  volatile uint64_t current_ticket;
};

typedef struct {
  enum lock_type lock_type;
  union {
    ges_node_t *tail;
    volatile int locked;
    struct ges_ticket ticket;
  };
}ges_lock_t;


void ges_lock_init(ges_lock_t * lock);

void ges_lock(ges_lock_t * lock, ges_node_t * node);

void ges_unlock(ges_lock_t * lock, ges_node_t * node);
#endif
