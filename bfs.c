#include <stdlib.h>
#include "list.h"
#include "queue.h"
#include "graph.h"
#include "bfs.h"

static void __bfs_get_adjlist(Graph *gp, BFSVertex *vertex, AdjList **adjlist){
	*adjlist = NULL;
	Node *pNode = list_head(&(gp->adjtable));
	AdjList *temp = NULL;
	while(pNode != NULL){
		temp = (AdjList *)list_node_data(pNode);
		if(gp->match(temp->vertex, vertex)){
			*adjlist = temp;
			break;
		}
		pNode = list_node_next(pNode);
	}
}

int bfs(Graph *gp, BFSVertex *start, List *hops){
	if(gp == NULL || start == NULL || hops == NULL){
		return -1;
	}
	AdjList *temp = NULL, *adjlist = NULL;
	Node *pNode = list_head(&(gp->adjtable));
	while(pNode != NULL){
		temp = (AdjList *)list_node_data(pNode);
		pNode = list_node_next(pNode);
		if(gp->match(start, temp->vertex)){
			adjlist = temp;
			((BFSVertex *)temp->vertex)->color = gray;
			((BFSVertex *)temp->vertex)->hops = 0;
		}
		else{
			((BFSVertex *)temp->vertex)->color = white;
			((BFSVertex *)temp->vertex)->hops = -1;
		}
	}
	if(adjlist == NULL){
		return -1;
	}

	
	Queue que;
	queue_init(&que, NULL, NULL);
	queue_enqueue(&que, adjlist);

	while(queue_len(&que) > 0){
		adjlist = (AdjList *)list_node_data(queue_head(&que));

		Node *pNode = list_head(&(adjlist->adjacent));
		while(pNode){
			if(((BFSVertex *)(pNode->data))->color == white){
				AdjList *next_adjlist = NULL;
				__bfs_get_adjlist(gp, (BFSVertex *)(pNode->data), &next_adjlist);
				if(next_adjlist != NULL){
					((BFSVertex *)(next_adjlist->vertex))->color = gray;
					((BFSVertex *)(next_adjlist->vertex))->hops = ((BFSVertex *)(adjlist->vertex))->hops+1;
					queue_enqueue(&que, next_adjlist);
				}
			}
			pNode = list_node_next(pNode);
		}
		queue_dequeue(&que, &adjlist);
		((BFSVertex *)(adjlist->vertex))->color = black;
	}

	pNode = NULL;
	pNode = list_head(&(gp->adjtable));
	while(pNode){
		temp = (AdjList *)list_node_data(pNode);
		if(((BFSVertex *)(temp->vertex))->hops != -1){
			list_push(hops, temp->vertex);
		}
		pNode = list_node_next(pNode);
	}
	return 0;
}