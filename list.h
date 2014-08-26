#ifndef LIST_H_
#define LIST_H_

/* Used: 
 * 	memset()
 */
#include<stdlib.h>

typedef struct Node_{
    void *data;
    struct Node_ *next;
}Node;

typedef struct List_{
    Node *head;
    Node *tail;
    unsigned int length;
    /* free node.data, if is NULL, means userself manage node.data */
    void (*destroy)(void *data);
    /* if data match item return 1, or return 0 */
    int (*match)(const void *data, const void *item);
}List;

/*
 *  @param: destroy
 *			User pass this function pointer to free Node.data space, 
 *			If don't want free space, just pass NULL
 *  @param: match
 *			Using this function pointer to search node, return 1 if
 *			*data(node.data) match *item, or return 0, if don't want
 *			to search node just pass NULL
 */
extern void list_init(List *lst, void (*destroy)(void *data), int (*match)(const void *data, const void *item));

extern void list_destroy(List *lst);

/*
 *  @return: 1 => has node
 *			 0 => doesn't have node
 */
extern int list_has_node(List *lst, Node *pNode);

/*
 *  @return: NULL => pNode is lst->head, or pNode not in lst
 *			 Node* => pNode's previous node
 */
extern Node* list_node_prev(List *lst, Node *pNode);

/*
 *  @param: pNode
 *			Insert new node before pNode
 *  @param: data
 *			Node.data space allocation is the responsibility of the user
 *  @return: 0 => insert successfully
 */
extern int list_insert(List *lst, Node *pNode, const void *data);

/*
 *	@function: Add new node before head node, equal to list_insert(lst, NULL, data)
 *  @return: 0 => insert successfully
 */
extern int list_unshift(List *lst, const void *data);

/*
 *  @param: pNode
 *			Add new node after pNode
 *  @param: data
 *			Node.data space allocation is the responsibility of the user
 *  @return: 0 => append successfully
 */
extern int list_append(List *lst, Node *pNode, const void *data);

/*
 *  @function: Add new node after tail node, equal to list_append(lst, NULL, data)
 *  @return: 0 => successfully
 */
 extern int list_push(List *lst, const void *data);

/*
 *  @param: pNode
 *			Remove pNode from lst
 *  @param: data
 *			The removed node(pNode)'s data, the space allocation is 
 *			the responsibility of the user
 *  @return: 0 => successfully
 */
extern int list_remove(List *lst, Node *pNode, void **data);

/*
 *  @param: pNode
 *			Remove pNode's next node from lst
 *  @param: data
 *			The removed pNode->next->data, the space allocation is 
 *			the responsibility of the user
 *  @return: 0 => successfully
 */
extern int list_remove_next(List *lst, Node *pNode, void **data);

/*
 *  @function: equal to list_remove(lst, list_head(lst), data)
 *
 *  @param: data
 *			The removed node(lst->head)'s data, the space allocation is 
 *			the responsibility of the user
 *  @return: 0 => successfully
 */
extern int list_shift(List *lst, void **data);


/*
 *  @function: equal to list_remove(lst, list_tail(lst), data)
 *
 *  @param: data
 *			The removed node(lst->tail)'s data, the space allocation is 
 *			the responsibility of the user
 *  @return: 0 => successfully
 */
extern int list_pop(List *lst, void **data);

/*
 *  @param: item
 *			find the node that List::match(node.data, item) return the node pointer
 *  @return: NULL => no match, or undefined match function
 *			 Node* => the matched node
 */
extern Node* list_search(List *lst, const void *item);

/*
 *  @param: pos from 0 to lst->length-1
 *  @return: NULL => pos >= lst->length
 *			 Node* => get node and *not* remove from list
 */
extern Node* list_get(List *lst, unsigned int pos);

#define list_head(lst) ((lst)->head)
#define list_tail(lst) ((lst)->tail)
#define list_len(lst) ((lst)->length)
#define list_is_head(lst, pNode) ((pNode) == (lst)->head ? 1 : 0)
#define list_is_tail(lst, pNode) ((pNode) == (lst)->tail ? 1 : 0)
#define list_is_empty(lst) ((lst)->length == 0 ? 1 : 0)
/* compare two node, not list */
#define list_is_equal(pNode1, pNode2) ((pNode1) == (pNode2) ? 1 : 0)
#define list_node_data(pNode) ((pNode)->data)
#define list_node_next(pNode) ((pNode)->next)

#endif
