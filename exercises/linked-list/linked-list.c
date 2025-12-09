#include <stdio.h>
#include <stdlib.h>

#include "linked-list.h"

node *ll_new(int value) {
  node *head = malloc(sizeof(node));
  if (head == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  head->value = value;
  head->next = NULL;

  return head;
}

bool ll_exists(node *head, int value) {
  for (node *current = head; current != NULL; current = current->next) {
    if (current->value == value) {
      return true;
    }
  }

  return false;
}

node *ll_prepend(node *head, int value) {
  node *new = ll_new(value);
  new->next = head;

  return new;
}

node *ll_append(node *head, int value) {
  node *new = ll_new(value);

  for (node *current = head; current != NULL; current = current->next) {
    if (current->next == NULL) {
      current->next = new;
      return head;
    }
  }

  return new;
}

void ll_destroy(node *head) {
  while (head != NULL) {
    node *next = head->next;
    free(head);
    head = next;
  }
}

void ll_destroy_recursive(node *head) {
  if (head != NULL) {
    ll_destroy_recursive(head->next);
    free(head);
  }
}

void ll_print(node *head) {
  printf("[ ");
  for (node *current = head; current != NULL; current = current->next) {
    printf("%i ", current->value);
  }
  printf("]\n");
}

node *ll_delete(node *head, int target, bool once) {
  node *current = head, *last = NULL, *next = NULL;

  while (current != NULL) {
    next = current->next;
    if (current->value == target) {
      // If it's the first element
      if (!last) {
        head = next;
      } else {
        last->next = next;
      }

      free(current);
      if (once) {
        break;
      }
    } else {
      // Advance `last` only if the node was not removed.
      last = current;
    }

    current = next;
  }

  return head;
}
