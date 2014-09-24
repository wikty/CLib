#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "bfs.h"

typedef struct UserInfo_{
	int seq;
	char username[20];
}UserInfo;

int match(const BFSVertex *data1, const BFSVertex *data2){
	return (strcmp(((UserInfo *)(data1->data))->username, ((UserInfo *)(data2->data))->username) == 0 ? 1 : 0);
}

// void destroy(void* data){
// 	free(data);
// }

void print(const BFSVertex *data){
	printf("%s ", ((UserInfo *)(data->data))->username);
}

void print_list(const BFSVertex *data){
	printf("[%s, %d]\n", ((UserInfo *)(data->data))->username, data->hops);	
}

UserInfo *u[10];
Graph *gp;
BFSVertex *v[10];

int setup(){
	if((gp = (Graph *)malloc(sizeof(Graph))) == NULL){
		return -1;
	}
	graph_init(gp, NULL, match);

	for(int i=0; i<10; i++){
		if((v[i] = (BFSVertex *)malloc(sizeof(BFSVertex))) == NULL){
			free(gp);
			int j=i-1;
			for(; j>=0; j--){
				free(u[j]);
			}
			j=i-1;
			for(; j>=0; j--){
				free(v[j]);
			}
		}
		if((u[i] = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
			free(gp);
			int j=i-1;
			for(; j>=0; j--){
				free(u[j]);
			}
			j=i-1;
			for(; j>=0; j--){
				free(v[j]);
			}
		}
		u[i]->seq = i;
		sprintf(u[i]->username, "%d-item", i);
		v[i]->data = (void *)u[i];
		v[i]->hops = -1;
	}
	return 0;
}

void enddown(){
	graph_destroy(gp);
	free(gp);
	gp = NULL;

	for(int i=0; i<10; i++){
		free(u[i]);
		u[i] = NULL;
		free(v[i]);
		v[i] = NULL;
	}
}

int main(){
	setup();

	for(int i=0; i<10; i++){
		graph_add_vertex(gp, v[i]);
	}

	graph_add_edge(gp, v[0], v[1]);
	graph_add_edge(gp, v[0], v[2]);
	graph_add_edge(gp, v[0], v[3]);
	graph_add_edge(gp, v[0], v[4]);

	graph_add_edge(gp, v[1], v[5]);
	graph_add_edge(gp, v[1], v[8]);
	graph_add_edge(gp, v[1], v[2]);

	graph_add_edge(gp, v[2], v[5]);
	graph_add_edge(gp, v[2], v[7]);

	graph_add_edge(gp, v[3], v[1]);
	graph_add_edge(gp, v[3], v[6]);
	graph_add_edge(gp, v[3], v[7]);

	graph_add_edge(gp, v[4], v[5]);

	graph_add_edge(gp, v[5], v[6]);

	graph_add_edge(gp, v[6], v[7]);

	graph_add_edge(gp, v[7], v[8]);

	graph_add_edge(gp, v[8], v[9]);

	graph_add_edge(gp, v[9], v[0]);

	graph_dump(gp, print);

	List lst;
	list_init(&lst, NULL, NULL);
	bfs(gp, v[0], &lst);
	list_dump(&lst, print_list);

	enddown();
	return 0;
}