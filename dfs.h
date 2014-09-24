#ifndef DFS_H_
#define DFS_H_

#include "graph.h"
#include "list.h"

/* vertex access status 
 *		white => initial status
 *		gray => will be accessed
 *		black => had accessed
 */
typedef enum VertexColor_ {white, gray, black}VertexColor;

typedef struct DFSVertex_{
	VertexColor color;
	void *data;
}DFSVertex;

extern int dfs(Graph *gp, List *lst);

#endif