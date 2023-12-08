#include "lists.h"

void free_dlistint(dlistint_t *head)
{
    if (head == NULL)
        return;

    dlistint_t *temp = head;

    while (temp->next)
    {
        temp = temp->next;
        free(temp->prev);
    }

    free(temp);
}
