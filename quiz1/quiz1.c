#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct __node {
    int value;
    struct __node *next;
} node_t;

void add_entry(node_t **head, int new_value)
{
    node_t **indirect = head;

    node_t *new_node = malloc(sizeof(node_t));
    new_node->value = new_value;
    new_node->next = NULL;

    //assert(new_node);
    while (*indirect)
        indirect = &(*indirect)->next;
    *indirect = new_node;
}

node_t *find_entry(node_t *head, int value)
{
    node_t *current = head;
    for (; current && current->value != value; current = current->next)
        /* interate */;
    return current;
}

void remove_entry(node_t **head, node_t *entry)
{
    node_t **indirect = head;

    while ((*indirect) != entry)
        indirect = &(*indirect)->next;

    *indirect = entry->next;
    free(entry);
}

node_t *swap_pair(node_t *head)
{
    for (node_t **node = &head; *node && (*node)->next; node = &(*node)->next->next) {
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
    return head;
}

node_t *reverse(node_t *head)
{
    node_t *cursor = NULL;
    while (head) {
        node_t *next = head->next;
        head->next = cursor; cursor = head;
        head = next;
    }
    return cursor;
}

void print_list(node_t *head)
{
    for (node_t *current = head; current; current = current->next)
        printf("%d ", current->value);
    printf("\n");
}

void indirect_swap(node_t **node){
    for (;*node && (*node)->next; node = &(*node)->next->next){
        node_t *tmp = *node;
        *node = (*node)->next;
        tmp->next = (*node)->next;
        (*node)->next = tmp;
    }
}

void indirect_reverse(node_t **node){
    node_t *pre = NULL;
    while((*node)->next){
        node_t *next = (*node)->next;
        (*node)->next = pre;
        pre = *node;
        *node = next;
    }
    (*node)->next = pre;
}

void rev_reverse(node_t *pre, node_t **node){
    if (!(*node)->next){
        (*node)->next = pre;
        return;
    }
    node_t *now = *node;
    printf("Node %d, addr=%p, pre=%p\n", (*node)->value, *node, now->next);
    *node = (*node)->next;
    rev_reverse(now, node);
    now->next = pre;
    printf("Node %d, addr=%p, pre=%p\n", now->value, now, now->next);
}

void rev_reverse_caller(node_t **head){
    rev_reverse(NULL, head);
}

int length(node_t *head){
    int l=0;
    while(head){
        l++;
        head = head->next;
    }
    return l;
}

void swap_value(node_t *node1, node_t *node2){
    int tmp = node2->value;
    node2->value = node1->value;
    node1->value = tmp;
}

void shuffle(node_t *head){
    srand(time(NULL));
    int len = length(head);
    for(int i=0; i<len; i++){
        int random = rand() % (len - i);
        node_t *target = head;
        for (int j=0; j<random; j++)
            target = target->next;
        swap_value(head, target);
        head = head->next;
    }
}

int main(int argc, char const *argv[])
{
    node_t *head = NULL;

    print_list(head);

    add_entry(&head, 72);
    add_entry(&head, 101);
    add_entry(&head, 108);
    add_entry(&head, 109);
    add_entry(&head, 110);
    add_entry(&head, 111);

    print_list(head);

    node_t *entry = find_entry(head, 101);
    remove_entry(&head, entry);

    entry = find_entry(head, 111);
    remove_entry(&head, entry);

    print_list(head);

    /* swap pair.
     * See https://leetcode.com/problems/swap-nodes-in-pairs/
     */

    shuffle(head);
    print_list(head);

    return 0;
}


