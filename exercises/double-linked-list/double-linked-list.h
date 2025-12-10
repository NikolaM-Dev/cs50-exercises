#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <stdbool.h>

typedef struct dll_node {
  int value;
  struct dll_node *prev;
  struct dll_node *next;
} dll_node;

// `dll_new` returns the head of a new Double Linked List
dll_node *dll_new(int value);

// `dll_exists` finds if a value exists in the Double Linked List
bool dll_exists(dll_node *head, int value);

// `dll_prepend` inserts a new element at the front and returns the new head.
dll_node *dll_prepend(dll_node *head, int value);

// `dll_append` walks to the tail, links a new element, and returns the head.
dll_node *dll_append(dll_node *head, int value);

// `dll_destroy` deletes an entire Double Linked List
void dll_destroy(dll_node *head);

// `dll_destroy_recursive` deletes an entire Double Linked List using recursion
void dll_destroy_recursive(dll_node *head);

// `dll_print` prints every element in the Double Linked List
void dll_print(dll_node *head);

// `dll_delete` removes dll_nodes matching `target` and returns the revised head.
// Set `once` true to stop after the first removal, false to purge all matches.
dll_node *dll_delete(dll_node *head, int target, bool once);

#endif // DOUBLE_LINKED_LIST_H
