#include <stdio.h>
#include <stdlib.h>

#include "double-linked-list.h"

dll_node *dll_new(int value) {
  dll_node *head = malloc(sizeof(dll_node));
  if (head == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  head->value = value;
  head->prev = NULL;
  head->next = NULL;

  return head;
}

bool dll_exists(dll_node *head, int value) {
  for (dll_node *current = head; current != NULL; current = current->next) {
    if (current->value == value) {
      return true;
    }
  }

  return false;
}

dll_node *dll_prepend(dll_node *head, int value) {
  dll_node *new = dll_new(value);
  if (head == NULL) {
    return new;
  }

  head->prev = new;
  new->next = head;

  return new;
}

dll_node *dll_append(dll_node *head, int value) {
  dll_node *new = dll_new(value);
  if (head == NULL) {
    return new;
  }

  for (dll_node *current = head; current != NULL; current = current->next) {
    if (current->next == NULL) {
      new->prev = current;
      current->next = new;
      break;
    }
  }

  return head;
}

void dll_destroy(dll_node *head) {
  while (head != NULL) {
    dll_node *current = head->next;
    free(head);
    head = current;
  }
}

void dll_destroy_recursive(dll_node *head) {
  if (head != NULL) {
    dll_destroy_recursive(head->next);
    free(head);
  }
}

void dll_print(dll_node *head) {
  if (head == NULL) {
    printf("[ ]\n");
    return;
  }

  printf("[\n");
  for (dll_node *current = head; current != NULL; current = current->next) {
    if (current->prev != NULL) {
      printf("\t%03i <- ", current->prev->value);
    } else {
      printf("\t--- <- ");
    }
    printf("%02i", current->value);
    if (current->next != NULL) {
      printf(" -> %03i\n", current->next->value);
    } else {
      printf(" -> ---\n");
    }
  }
  printf("]\n");
}

dll_node *dll_delete(dll_node *head, int target, bool once) {
  if (head == NULL) {
    return head;
  }

  dll_node *current = head;
  while (current != NULL) {
    dll_node *next = current->next;
    if (current->value == target) {
      // It's the only element
      if (current->prev == NULL && current->next == NULL) {
        free(current);
        return NULL;
      }
      // It's the first
      else if (current->prev == NULL) {
        current->next->prev = NULL;
        head = next;
      }
      // It's the last
      else if (current->next == NULL) {
        current->prev->next = NULL;
      }
      // It's in the middle
      else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
      }

      free(current);
      if (once) {
        break;
      }
    }

    current = next;
  }

  return head;
}
