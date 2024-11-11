#include <stdbool.h>

struct ges_node {
  struct ges_node *next;
  volatile bool waiting;
};

typedef struct  ges_lock * ges_lock_t;
typedef struct ges_node * ges_node_t;

ges_lock_t ges_lock_init(void);

void ges_lock(ges_lock_t lock, ges_node_t node);

void ges_unlock(ges_lock_t loc, ges_node_t node);
