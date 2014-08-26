#include"list.h"

void list_init(List *lst, void (*destroy)(void *data), int (*match)(const void *data, const void *item)){
    lst->head = NULL;
    lst->tail = NULL;
    lst->length = 0;
    lst->destroy = destroy;
    lst->match = match;
}

void list_destroy(List *lst){
    void *data;
    while(list_len(lst)>0){
        if(list_pop(lst, (void **)&data)==0 && lst->destroy!=NULL){
            lst->destroy(data);
        }
    }
    memset(lst, 0, sizeof(*lst));
}

int list_has_node(List *lst, Node *pNode){
    if(pNode!=NULL){
        Node *pCurrentNode = list_head(lst);
        while(pCurrentNode){
            if(list_is_equal(pCurrentNode, pNode)){
                return 1;
            }
            pCurrentNode = list_node_next(pCurrentNode);
        }
    }
    return 0;
}

Node* list_node_prev(List *lst, Node *pNode){
    Node *pPrevNode, *pCurrentNode;
    pPrevNode = NULL;
    pCurrentNode = list_head(lst);
    while(pCurrentNode){
        if(list_is_equal(pCurrentNode, pNode)){
            return pPrevNode;
        }
        pPrevNode = pCurrentNode;
        pCurrentNode = list_node_next(pCurrentNode);
    }
    return NULL;
}

int list_insert(List *lst, Node *pNode, const void *data){
    if(list_is_empty(lst) && pNode!=NULL){
        return -1;
    }
    Node *pNewNode = NULL;
    if(pNode==NULL || list_is_head(lst, pNode)){
        /* insert before list head */
        if((pNewNode = (Node *)malloc(sizeof(Node)))==NULL){
            return -1;
        }
        pNewNode->data = (void *)data;
        pNewNode->next = list_head(lst);

        lst->head = pNewNode;
        if(list_is_empty(lst)){
            lst->tail = pNewNode;
        }
    }
    else{
        /* insert before pNode(non-head-node) */
        Node *pPrevNode = list_node_prev(lst, pNode);
        if(pPrevNode==NULL){
            /* pNode not in lst */
            return -1;
        }
        
        if((pNewNode = (Node *)malloc(sizeof(Node)))==NULL){
            return -1;
        }
        pNewNode->data = (void *)data;
        pNewNode->next = pNode;

        pPrevNode->next = pNewNode;
    }

    lst->length++;
    return 0;
}

int list_unshift(List *lst, const void *data){
    return list_insert(lst, NULL, data);
}

int list_append(List *lst, Node *pNode, const void *data){
    if(list_is_empty(lst) && pNode!=NULL){
        return -1;
    }
    Node *pNewNode = NULL;
    if(pNode==NULL || list_is_tail(lst, pNode)){
        /* append after list tail */
        if((pNewNode = (Node *)malloc(sizeof(Node)))==NULL){
            return -1;
        }
        pNewNode->data = (void *)data;
        pNewNode->next = NULL;
       
        if(list_is_empty(lst)){
            lst->head = pNewNode;
            lst->tail = pNewNode;
        }
        else{
            lst->tail->next = pNewNode;
            lst->tail = pNewNode;
        }
    }
    else{
        /* append after pNode(non-tail-node) */
        /*
        if(!list_has_node(lst, pNode)){
            return -1;
        }
        */
        if((pNewNode = (Node *)malloc(sizeof(Node)))==NULL){
            return -1;
        }        
        pNewNode->data = (void *)data;
        pNewNode->next = list_node_next(pNode);
        
        pNode->next = pNewNode;
    }

    lst->length++;
    return 0;
}

int list_push(List *lst, const void *data){
    return list_append(lst, NULL, data);
}

int list_remove(List *lst, Node *pNode, void **data){
    Node *pCurrentNode = list_head(lst);
    Node *pPrevNode = NULL;
    while(pCurrentNode){
        if(list_is_equal(pCurrentNode, pNode)){
            *data = list_node_data(pNode);
            if(list_is_head(lst, pNode)){
                /* remove head node */
                lst->head = list_node_next(lst->head);
            }
            if(list_is_tail(lst, pNode)){
                lst->tail = pPrevNode;
            }
            if(pPrevNode!=NULL){
                pPrevNode->next = list_node_next(pNode);
            }
            lst->length--;
            /* the responsibility of allocation node.data space is User,
               but Node allocation is list programer
            */
            free(pNode);
            return 0;
        }
        pPrevNode = pCurrentNode;
        pCurrentNode = list_node_next(pCurrentNode);
    }
    return -1;
}

int list_remove_next(List *lst, Node *pNode, void **data){
    if(list_len(lst)<2 || list_is_tail(lst, pNode)){
        return -1;
    }

    /*
    if(!list_has_node(lst, pNode)){
        return -1;
    }
    */

    Node *pNextNode = list_node_next(pNode);
    *data = list_node_data(pNextNode);
    pNode->next = list_node_next(pNextNode);
    lst->length--;
    free(pNextNode);

    if(list_is_tail(lst, pNode)){
        lst->tail = pNode;
        lst->tail->next = NULL;
    }
    return 0;
}

int list_shift(List *lst, void **data){
    if(list_is_empty(lst)){
        return -1;
    }
    Node *pNode = list_head(lst);
    *data = list_node_data(pNode);
    lst->head = list_node_next(pNode);
    lst->length--;

    if(list_is_empty(lst)){
        lst->tail = NULL;
    }
    free(pNode);
    return 0;
}

int list_pop(List *lst, void **data){
    if(list_is_empty(lst)){
        return -1;
    }
    Node *pNode = list_tail(lst);
    *data = list_node_data(pNode);
    Node *pPrevNode = list_node_prev(lst, pNode);
    if(pPrevNode==NULL){
        /* list has only one node */
        lst->head = lst->tail = NULL;
    }
    else{
        pPrevNode->next = NULL;        
    }
    lst->length--;
    free(pNode);
    return 0;
}

Node* list_search(List *lst, const void *item){
    if(lst->match==NULL){
        return NULL;
    }
    Node *pCurrentNode = list_head(lst);
    while(pCurrentNode){
        if(lst->match(list_node_data(pCurrentNode), item)){
            return pCurrentNode;
        }
        pCurrentNode = list_node_next(pCurrentNode);
    }
    return NULL;
}

Node* list_get(List *lst, unsigned int pos){
    if(pos >= list_len(lst)){
        return NULL;
    }
    if(pos==0){
        return list_head(lst);
    }

    Node *pNode = list_head(lst);
    for(int i=1; i<=pos; i++){
        pNode = list_node_next(pNode);
    }
    return pNode;
}