#include <stdio.h>
#include <stdlib.h>

#include "linked-list.h"

int main(void) {
  node *linked_list = ll_new(34);
  linked_list = ll_append(linked_list, 9);
  linked_list = ll_prepend(linked_list, 6);
  linked_list = ll_prepend(linked_list, 3);
  linked_list = ll_prepend(linked_list, 3);
  linked_list = ll_append(linked_list, 3);

  ll_print(linked_list);

  printf("\nTrying to delete 3 TRUE:\n");
  linked_list = ll_delete(linked_list, 3, true);
  ll_print(linked_list);

  printf("\nTrying to delete 9 TRUE:\n");
  linked_list = ll_delete(linked_list, 9, true);
  ll_print(linked_list);

  printf("\nTrying to delete 3 FALSE:\n");
  linked_list = ll_delete(linked_list, 3, false);
  ll_print(linked_list);

  ll_destroy(linked_list);

  return EXIT_SUCCESS;
}
