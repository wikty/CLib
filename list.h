#ifndef LIST_H_
#define LIST_H_

typedef struct Node_{
    void *data;
    struct Node_ *next;
}Node;

typedef struct List_{
    Node *head;
    Node *tail;
    unsigned int length;
    /* Free node's data, if is NULL, means User manage node.data by himself */
    void (*destroy)(void *data);
    /* If data1 match data2 return 1, else return 0 */
    int (*match)(const void *data1, const void *data2);
}List;

/*
 *  @param: destroy
 *			User pass this function pointer to free Node.data, 
 *			If don't want free space, just pass NULL
 *			In other words, if User pass destroy function, User
 *			should manage the removed node's data, if don't pass
 *			destroy function, User should manage all of node's data
 *  @param: match
 *			Using this function pointer to search node, return 1 if
 *			data1 match data2, or return 0. if don't want to enable 
 *			search function just pass NULL
 */
extern void list_init(List *lst, void (*destroy)(void *data), int (*match)(const void *data, const void *item));

extern void list_destroy(List *lst);

/*
 *  @return: 1 => has node
 *			 0 => doesn't have node
 */
extern int list_has_node(List *lst, Node *pNode);

/*
 *  @return: NULL => pNode is list_head(lst), or pNode not in lst
 *			 Node* => pNode's previous node
 */
extern Node* list_node_prev(List *lst, Node *pNode);

/*
 *  @param: pNode
 *			Insert new node before pNode
 *  @param: data
 *			Node.data space allocation is the responsibility of the User
 *  @return: 0 => insert successfully
 */
extern int list_insert(List *lst, Node *pNode, const void *data);

/*
 *	@function: Add new node before list_head(lst) node, equal to list_insert(lst, NULL, data)
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
 *  @function: Add new node after list_tail(lst) node, equal to list_append(lst, NULL, data)
 *  @return: 0 => successfully
 */
 extern int list_push(List *lst, const void *data);

/*
 *  @param: pNode
 *			Remove pNode from lst
 *  @param: data
 *			The removed pNode's data, the space allocation is 
 *			the responsibility of the user
 *  @return: 0 => successfully
 */
extern int list_remove(List *lst, Node *pNode, void **data);

/*
 *  @param: pNode
 *			Remove pNode's next node from lst
 *  @param: data
 *			The removed pNode's next node's data, the space allocation is 
 *			the responsibility of the user
 *  @return: 0 => successfully
 */
extern int list_remove_next(List *lst, Node *pNode, void **data);

/*
 *	@return: 0 => successfully
 *			 -1 => fail, lst's match function is NULL or data is NULL
 *			 1 => lst don't have data
 */
extern int list_remove_by_data(List *lst, const void *data);

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
 *			The removed list_tail(lst)'s data, the space allocation is 
 *			the responsibility of the user
 *  @return: 0 => successfully
 */
extern int list_pop(List *lst, void **data);

/*
 *  @param: data
 *			find the node that match(node.data, data) return the node pointer
 *  @return: NULL => not found, or undefined match function
 *			 Node* => the matched node
 */
extern Node* list_search(List *lst, const void *data);

/*
 *  @param: pos 
 *			from 0 to list_len(list)-1
 *  @return: NULL => if pos not in range [0, list_len(lst)-1]
 *			 Node* => get node and *not* remove from list
 */
extern Node* list_get(List *lst, unsigned int pos);

/*
 *  @param: print
 *			the function to print the node's data
 */
extern void list_dump(List *lst, void (*print)(const void *data));

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
