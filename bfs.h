#ifndef BFS_H_
#define BFS_H_

#include "graph.h"
#include "list.h"

/* vertex access status 
 *		white => unaccessed
 *		gray => will be accessed(in queue)
 *		black => had accessed
 */
typedef enum VertexColor_ {white, gray, black}VertexColor;

typedef struct BFSVertex_{
	void *data;
	/* access status */
	VertexColor color;
	/* how many hops to find target */
	int hops;
}BFSVertex;

/* Public Interfaces */
extern int bfs(Graph *gp, BFSVertex *start, List *hops);

#endif