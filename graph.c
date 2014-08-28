#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "set.h"
#include "graph.h"

void graph_init(Graph *gp, void (*destroy)(void *data), int (*match)(const void *data1, const void *data2)){
	gp->ecount = 0;
	gp->vcount = 0;
	gp->destroy = destroy;
	gp->match = match;

	list_init(&(gp->adjtable), NULL, NULL);
}

void graph_init(Graph *gp){
	AdjList *adjlist = NULL;
	
	while(list_len(gp->adjtable) > 0){
		if(list_pop(&(gp->adjtable), (void **)&adjlist) == 0){
			/* Set destroy itself, actually just memset empty */
			set_destroy(&(adjlist->adjacent));

			if(gp->destroy != NULL){
				gp->destroy(adjlist->vertex);
			}
			
			free(adjlist);
		}
	}
	/* actually just memset empty */
	list_destroy(&(gp->adjtable));

	memset(gp, 0, sizeof(*gp));
}

int graph_get_adjlist(Grap *gp, const void *vertex, AdjList **adlist){
	if(graph_is_empty(gp)){
		*adlist = NULL;
		return -1;
	}
	
	*adlist = list_head(&(gp->adjtable));
	while(*adlist != NULL){
		if(gp->match(((AdjList *)(*adlist))->vertex, vertex)){
			return 0;
		}
		*adlist = list_node_next(*adlist);
	}
	
	*adlist = NULL;
	return -1;
}

int graph_is_adjacent(Graph *gp, const void *vertex1, const void *vertex2){
	AdjList *adjlist1, *adjlist2;
	graph_get_adjlist(gp, vertex1, &adjlist1);
	if(adjlist1 == NULL){
		return 0;
	}
	graph_get_adjlist(gp, vertex2, &adjlist2);
	if(adjlist2 == NULL){
		return 0;
	}
	int v1has2 = set_is_member(adjlist1, vertex2);
	int v2has1 = set_is_member(adjlist2, vertex1);
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
	graph_get_adjlist(gp, vertex, &adjlist);
	if(adjlist != NULL){
		/* vertex existed, dont allow insertion duplicate vertices */
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
	AdjList *adjlist = NULL;

	/* if vertices not in graph, dont allow insertion */
	graph_get_adjlist(gp, to, &adjlist);
	if(adjlist == NULL){
		return -1;
	}
	/* NOTICE: from test must be after to test, 
	   so adjlist store from list pointer 
	*/
	graph_get_adjlist(gp, from, &adjlist);
	if(adlist == NULL){
		return -1;
	}
	
	int retval;
	if((retval = set_insert(adjlist->adjacent, to)) != 0){
		return retval;
	}

	gp->ecount++;
	return 0;
}

int graph_drop_vertex(Graph *gp, const void *vertex){
	AdjList *adjlist = NULL;
	graph_get_adjlist(gp, vertex, &adjlist);

	if(adjlist == NULL){
		return -1;
	}

	/* remove all adjacent */
	AdjList *p = (AdjList *)list_head(&(gp->adjtable));
	while(p != NULL){
		set_remove(((AdjList *)p)->adjacent, vertex);
		p = list_node_next(p);
	}
	/* remove adjlist */
	if(gp->destroy != NULL){
		gp->destroy(adjlist->vertex);
	}
	set_destroy(&(adjlist->adjacent));
	free(adjlist);

	gp->vcount--;
	return 0;
}

int graph_remove_vertex(Graph *gp, const void *vertex){
	AdjList *adjlist = NULL;
	graph_get_adjlist(gp, vertex, &adjlist);

	if(adjlist == NULL){
		return -1;
	}

	AdjList *p = (AdjList *)list_head(&(gp->adjtable));
	while(p != NULL){
		/* dont allow removal of the vertex if it is in an adjacent list */
		if(set_is_member(((AdjList *)p)->adjacent, vertex)){
			return -1;
		}
		p = list_node_next(p);
	}
	/* remove adjlist */
	if(gp->destroy != NULL){
		gp->destroy(adjlist->vertex);
	}
	set_destroy(&(adjlist->adjacent));
	free(adjlist);

	gp->vcount--;
	return 0;
}

int graph_remove_edge(Graph *gp, const void *from, const void *to){
	AdjList *adjlist = NULL;

	/* if vertices not in graph, dont allow insertion */
	graph_get_adjlist(gp, to, &adjlist);
	if(adjlist == NULL){
		return -1;
	}
	/* NOTICE: from test must be after to test, 
	   so adjlist store from list pointer 
	*/
	graph_get_adjlist(gp, from, &adjlist);
	if(adlist == NULL){
		return -1;
	}

	int retval;
	if((retval = set_remove(adjlist->adjacent, to)) != 0){
		return retval;
	}

	gp->ecount--;
	return 0;
}

