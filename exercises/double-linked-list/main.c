#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "double-linked-list.h"

int main(void) {
  dll_node *double_linked_list = dll_new(34);
  double_linked_list = dll_append(double_linked_list, 9);
  double_linked_list = dll_prepend(double_linked_list, 6);
  double_linked_list = dll_prepend(double_linked_list, 3);
  double_linked_list = dll_prepend(double_linked_list, 3);
  double_linked_list = dll_append(double_linked_list, 3);

  dll_print(double_linked_list);

  bool exists = dll_exists(double_linked_list, 10);
  printf("Exists %i in the list? %s\n", 10, exists ? "Yes" : "No");
  double_linked_list = dll_append(double_linked_list, 10);
  exists = dll_exists(double_linked_list, 10);
  printf("What about now? %s\n", exists ? "Yes" : "No");

  dll_print(double_linked_list);

  printf("\nTrying to delete 3 TRUE:\n");
  double_linked_list = dll_delete(double_linked_list, 3, true);
  dll_print(double_linked_list);

  printf("\nTrying to delete 9 TRUE:\n");
  double_linked_list = dll_delete(double_linked_list, 9, true);
  dll_print(double_linked_list);

  printf("\nTrying to delete 3 FALSE:\n");
  double_linked_list = dll_delete(double_linked_list, 3, false);
  dll_print(double_linked_list);

  printf("\nTrying to delete 10 FALSE:\n");
  double_linked_list = dll_delete(double_linked_list, 10, false);
  dll_print(double_linked_list);

  printf("\nTrying to delete 14 FALSE:\n");
  double_linked_list = dll_delete(double_linked_list, 14, false);
  dll_print(double_linked_list);

  printf("\n-------------------------------------------------------------------"
         "-----------\n");

  dll_destroy(double_linked_list);
  // dll_destroy_recursive(double_linked_list);

  double_linked_list = dll_new(3);
  dll_print(double_linked_list);

  printf("\nTrying to delete 3 TRUE:\n");
  double_linked_list = dll_delete(double_linked_list, 3, true);
  dll_print(double_linked_list);

  dll_destroy(double_linked_list);

  return EXIT_SUCCESS;
}
