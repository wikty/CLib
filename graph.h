#ifndef GRAPH_H_
#define GRAPH_H_

#include "list.h"
#include "set.h"

typedef struct AdjList_{
	void *vertex;
	Set adjacent;
}AdjList;

typedef struct Graph_{
	/* vertex count */
	unsigned int vcount;
	/* edge count */
	unsigned int ecount;

	int (*match)(const void *data1, const void *data2);
	void (*destroy)(void *data);

	List adjtable;
}Graph;


/* Public Interfaces
 */
extern void graph_init(Graph *gp, void (*destroy)(void *data), int (*match)(const void *data1, const void *data2));

extern void graph_destroy(Graph *gp);

extern int graph_add_vertex(Graph *gp, const void *vertex);

/*
 *  @function: this graph is a direction graph,
 *			   so just add edge from *from to *to,
 *			   not from *to to *from
 */
extern int graph_add_edge(Graph *gp, const void *from, const void *to);

/*
 *  @function: remove vertex and all of adjacent record in other vertex
 */
extern int graph_drop_vertex(Graph *gp, const void *vertex);

/*
 *  @function: remove vertex, if other adjacent with this vertex
 *			   calling failure
 */
extern int graph_remove_vertex(Graph *gp, const void *vertex);

extern int graph_remove_edge(Graph *gp, const void *from, const void *to);

/*
 *  @function: get vertex's adjlist::adjacent
 *  @param: adjacent => User should initialize(memory allocate) it
 *			after return, will hold the copy of vertex's adjlist::adjacent
 */
extern int graph_get_adjacent(Graph *gp, const void *vertex, Set *adjacent);

/*
 *  @function: is there a edge between vertex1 and vertex2
 *	@return: 0 => no adjacent or vertex1, vertex2 not in adjtable
 *			 1 => just vertex1 to vertex2
 *			 -1 => just vertex2 to vertex1
 *			 2 => vertex1 <=> vertex2
 */
extern int graph_is_adjacent(Graph *gp, const void *vertex1, const void *vertex2);

extern void graph_dump(Graph *gp, void (*print)(const void *data));

#define graph_vcount(gp)	((gp)->vcount)
#define graph_ecount(gp)	((gp)->ecount)
#define graph_is_empty(gp)	((gp)->vcount == 0 ? 1 : 0)

#endif