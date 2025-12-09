#include <stdbool.h>
#include <stdbool.h>

typedef struct node {
  int value;
  struct node *next;
} node;

// `ll_new` returns the head of a new Linked List
node *ll_new(int value);

// `ll_exists` finds if a value exists in the Linked List
bool ll_exists(node *head, int value);

// `ll_prepend` inserts a new element at the front and returns the new head.
node *ll_prepend(node *head, int value);

// `ll_append` walks to the tail, links a new element, and returns the head.
node *ll_append(node *head, int value);

// `ll_destroy` deletes an entire Linked List
void ll_destroy(node *head);

// `ll_destroy_recursive` deletes an entire Linked List using recursion
void ll_destroy_recursive(node *head);

// `ll_print` prints every element in the Linked List
void ll_print(node *head);

// `ll_delete` removes nodes matching `target` and returns the revised head.
// Set `once` true to stop after the first removal, false to purge all matches.
node *ll_delete(node *head, int target, bool once);
