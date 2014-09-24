#include <stdlib.h>
#include "graph.h"
#include "dfs.h"
#include "list.h"

static void __dfs_get_adjlist(Graph *gp, DFSVertex *vertex, AdjList **adjlist){
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

static void __dig(Graph *gp, AdjList *adjlist, List *lst){
	
	((DFSVertex *)(adjlist->vertex))->color = gray;
	list_push(lst, adjlist->vertex);

	Node *p = list_head(&(adjlist->adjacent));
	while(p){
		AdjList *next_adjlist = NULL;
		__dfs_get_adjlist(gp, list_node_data(p), &next_adjlist);
		
		if(next_adjlist && ((DFSVertex *)next_adjlist->vertex)->color == white){
			__dig(gp, next_adjlist, lst);
		}
		
		p = list_node_next(p);
	}

	((DFSVertex *)(adjlist->vertex))->color = black;
}

int dfs(Graph *gp, List *lst){
	if(gp == NULL || lst == NULL){
		return -1;
	}

	/* initialize status */
	AdjList *temp = NULL;
	Node *pNode = list_head(&(gp->adjtable));
	while(pNode != NULL){
		temp = (AdjList *)list_node_data(pNode);
		((DFSVertex *)temp->vertex)->color = white;
		pNode = list_node_next(pNode);
	}

	pNode = list_head(&(gp->adjtable));
	while(pNode != NULL){
		temp = (AdjList *)list_node_data(pNode);
		
		if(((DFSVertex *)temp->vertex)->color == white){
			__dig(gp, temp, lst);
		}
		
		pNode = list_node_next(pNode);
	}
	return 0;
}