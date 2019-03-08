/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = (queue_t *) malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL) {
        perror("Fail to malloc for queue_t\n");
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    list_ele_t *curr = NULL;

    if (!q)
        return;

    for (curr = q->head; curr != NULL; curr = q->head) {
        q->head = q->head->next;
        free(curr->value);
        free(curr);
    }

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    if (!q) {
        perror("q is NULL\n");
        return false;
    }
    newh = malloc(sizeof(list_ele_t));
    if (!newh) {
        perror("Failed to allocate memory for new element.\n");
        return false;
    }

    newh->value = (char *) malloc(strlen(s) + 1);
    if (!newh->value) {
        perror("Failed to allocate memory for value of new element.\n");
        free(newh);
        return false;
    }

    strncpy(newh->value, s, strlen(s));
    newh->value[strlen(s)] = '\0';
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    if (!q->tail)
        q->tail = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newt;
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q) {
        perror("q is NULL\n");
        return false;
    }

    newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        perror("Failed to allocate memory for new element.\n");
        return false;
    }

    newt->value = (char *) malloc(strlen(s) + 1);
    if (!newt->value) {
        perror("Failed to allocate memory for value of new element.\n");
        free(newt);
        return false;
    }

    strncpy(newt->value, s, strlen(s));
    newt->value[strlen(s)] = '\0';
    newt->next = NULL;
    if (q->tail) {
        q->tail->next = newt;
        q->tail = newt;
    } else {
        q->tail = newt;
        q->head = newt;
    }

    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *curr;

    /* You need to fix up this code. */
    if (!q) {
        perror("q is NULL\n");
        return false;
    }

    if (!q->head) {
        perror("q is empty\n");
        return false;
    }
    curr = q->head;
    if (q->head->next)
        q->head = q->head->next;
    else
        q->head = q->tail = NULL;

    if (sp) {
        size_t len = strlen(curr->value);
        if (len >= bufsize)
            len = bufsize - 1;

        strncpy(sp, curr->value, len);
        sp[len] = '\0';
    }

    free(curr->value);
    free(curr);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q)
        return 0;
    else
        return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *pnext, *pprev = NULL;
    /* You need to write the code for this function */
    if (!q) {
        perror("q is NULL\n");
        return;
    }

    if (!q->head) {
        perror("q is empty\n");
        return;
    }

    pnext = q->head;
    q->tail = q->head;
    while (q->head) {
        pnext = q->head->next;
        q->head->next = pprev;
        pprev = q->head;
        q->head = pnext;
    }
    q->head = pprev;
}
