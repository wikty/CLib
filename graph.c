#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "set.h"
#include "graph.h"

/* 
 *	@param: adjacent
 *			after return, adjacent will be pointed directly to vertex's adjlist::adjacent
 */
static int get_adjacent(Graph *gp, const void *vertex, Set **adjacent);
static int get_adjlist(Graph *gp, const void *vertex, AdjList **adjlist);
static int adjlist_match(const void *data1, const void *data2);

void graph_init(Graph *gp, void (*destroy)(void *data), int (*match)(const void *data1, const void *data2)){
	gp->ecount = 0;
	gp->vcount = 0;
	gp->destroy = destroy;
	gp->match = match;

	list_init(&(gp->adjtable), NULL, adjlist_match);
}

void graph_destroy(Graph *gp){
	AdjList *adjlist = NULL;
	
	while(list_len(&(gp->adjtable)) > 0){
		if(list_pop(&(gp->adjtable), (void **)&adjlist) == 0){
			/* Destroy Set's item, actually just memset Set, and
				Set is a auto variable
			 */
			set_destroy(&(adjlist->adjacent));

			if(gp->destroy != NULL){
				gp->destroy(adjlist->vertex);
			}
			
			/* The responsibility of Manage adjlist by Library Author */
			free(adjlist);
		}
	}
	/* actually just memset ajatable(is a auto variable) */
	list_destroy(&(gp->adjtable));

	memset(gp, 0, sizeof(*gp));
}

int graph_get_adjacent(Graph *gp, const void *vertex, Set *adjacent){
	int retval;
	Set *temp = NULL;
	if((retval = get_adjacent(gp, vertex, &temp)) != 0){
		return retval;
	}
	if((retval = set_copy_to(temp, adjacent)) != 0){
		return retval;
	}
	return 0;
}

int graph_is_adjacent(Graph *gp, const void *vertex1, const void *vertex2){
	/* if vertex1 or vertex2 is not existed */
	Set *adjacent1, *adjacent2;
	get_adjacent(gp, vertex1, &adjacent1);
	if(adjacent1 == NULL){
		return 0;
	}
	get_adjacent(gp, vertex2, &adjacent2);
	if(adjacent2 == NULL){
		return 0;
	}

	int v1has2 = set_is_member(adjacent1, vertex2);
	int v2has1 = set_is_member(adjacent2, vertex1);
	if(v1has2 && v2has1){
		return 2;
	}
	else if(v1has2){
		return 1;
	}
	else if(v2has1){
		return -1;
	}
	else{
		return 0;
	}
}

int graph_add_vertex(Graph *gp, const void *vertex){
	AdjList *adjlist = NULL;
	get_adjlist(gp, vertex, &adjlist);
	if(adjlist != NULL){
		/* vertex existed, don't allow insertion duplicate vertices */
		return 1;
	}

	if((adjlist = (AdjList *)malloc(sizeof(AdjList))) == NULL){
		return -1;
	}
	adjlist->vertex = (void *)vertex;
	set_init(&(adjlist->adjacent), NULL, gp->match);

	if(list_push(&(gp->adjtable), adjlist) != 0){
		free(adjlist);
		return -1;
	}

	gp->vcount++;
	return 0;
}

int graph_add_edge(Graph *gp, const void *from, const void *to){
	Set *adjacent = NULL;
	/* if vertices not in graph, dont allow insertion */
	get_adjacent(gp, to, &adjacent);
	if(adjacent == NULL){
		return -1;
	}
	adjacent = NULL;
	get_adjacent(gp, from, &adjacent);
	/* NOW: adjacent is owned by [from] */
	if(adjacent == NULL){
		return -1;
	}
	
	int retval;
	if((retval = set_insert(adjacent, to)) != 0){
		/* existed, will return 1 */
		return retval;
	}

	gp->ecount++;
	return 0;
}

int graph_drop_vertex(Graph *gp, const void *vertex){
	AdjList *adjlist = NULL;
	get_adjlist(gp, vertex, &adjlist);
	if(adjlist == NULL){
		/* vertext is not existed */
		return 1;
	}

	/* remove all adjacent */
	AdjList *temp = NULL;
	Node *pNode = list_head(&(gp->adjtable));
	while(pNode != NULL){
		temp = (AdjList *)list_node_data(pNode);
		pNode = list_node_next(pNode);
		if(temp == adjlist){
			continue;
		}
		set_remove(&(temp->adjacent), vertex);
	}
	/* remove adjlist */
	if(gp->destroy != NULL){
		gp->destroy(adjlist->vertex);
	}
	set_destroy(&(adjlist->adjacent));
	list_remove_by_data(&(gp->adjtable), adjlist);
	free(adjlist);

	gp->vcount--;
	return 0;
}

int graph_remove_vertex(Graph *gp, const void *vertex){
	AdjList *adjlist = NULL;
	get_adjlist(gp, vertex, &adjlist);
	if(adjlist == NULL){
		/* vertext is not existed */
		return 1;
	}

	AdjList *temp = NULL;
	Node *pNode = list_head(&(gp->adjtable));
	while(pNode != NULL){
		temp = (AdjList *)list_node_data(pNode);
		pNode = list_node_next(pNode);
		if(temp == adjlist){
			continue;
		}
		if(set_is_member(&(temp->adjacent), vertex)){
			/* other verteics adjacent the vertex, so cannot remove it */
			return -1;
		}
	}
	/* remove adjlist */
	if(gp->destroy != NULL){
		gp->destroy(adjlist->vertex);
	}
	set_destroy(&(adjlist->adjacent));
	list_remove_by_data(&(gp->adjtable), adjlist);
	free(adjlist);

	gp->vcount--;
	return 0;
}

int graph_remove_edge(Graph *gp, const void *from, const void *to){
	Set *adjacent = NULL;

	/* if vertices not in graph, dont allow insertion */
	get_adjacent(gp, to, &adjacent);
	if(adjacent == NULL){
		return -1;
	}
	/* NOTICE: from test must be after to test, 
	   so adjlist store from list pointer 
	*/
	get_adjacent(gp, from, &adjacent);  /* adjacent is from's adjacent */
	if(adjacent == NULL){
		return -1;
	}

	int retval;
	if((retval = set_remove(adjacent, to)) != 0){
		/* if not in, return 1 */
		return retval;
	}

	gp->ecount--;
	return 0;
}

void graph_dump(Graph *gp, void (*print)(const void *data)){
	AdjList *adjlist = NULL;
	Set *adjacent = NULL;
	Node *pNode = list_head(&(gp->adjtable));
	while(pNode != NULL){
		adjlist = (AdjList *)list_node_data(pNode);
		print(adjlist->vertex);
		printf(": ");
		get_adjacent(gp, adjlist->vertex, &adjacent);
		set_dump(adjacent, print);
		printf("\n");
		pNode = list_node_next(pNode);
	}
}

/* 
 *	Internel Functions
 */

int get_adjlist(Graph *gp, const void *vertex, AdjList **adjlist){
	if(graph_is_empty(gp)){
		*adjlist = NULL;
		return -1;
	}
	AdjList *temp = NULL;
	
	Node *pNode = list_head(&(gp->adjtable));
	while(pNode != NULL){
		temp = (AdjList *)list_node_data(pNode);
		if(gp->match(temp->vertex, vertex)){
			*adjlist = temp;
			return 0;
		}
		pNode = list_node_next(pNode);
	}
	
	*adjlist = NULL;
	return -1;
}

int get_adjacent(Graph *gp, const void *vertex, Set **adjacent){
	AdjList *adjlist = NULL;
	int retval;
	if((retval = get_adjlist(gp, vertex, &adjlist)) == 0){
		*adjacent = &(adjlist->adjacent);
	}
	else{
		return retval;
	}
}

int adjlist_match(const void *data1, const void *data2){
	if(((AdjList *)data1)->vertex == ((AdjList *)data2)->vertex){
		return 1;
	}
	return 0;
}