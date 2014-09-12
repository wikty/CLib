#include <stdio.h>

#include "graph.h"

typedef struct UserInfo_{
	int seq;
	char username[20];
}UserInfo;

int match(const void *data1, const void *data2){
	return (strcmp(((UserInfo *)data1)->username, ((UserInfo *)data2)->username) == 0 ? 1 : 0);
}

// void destroy(void* data){
// 	free(data);
// }

void print(const void *data){
	printf("%s ", ((UserInfo *)data)->username);
}

UserInfo *u[10];
Graph *gp;

int setup(){
	if((gp = (Graph *)malloc(sizeof(Graph))) == NULL){
		return -1;
	}
	graph_init(gp, NULL, match);

	for(int i=0; i<10; i++){
		if((u[i] = (UserInfo *)malloc(sizeof(UserInfo))) == NULL){
			free(gp);
			for(int j=i-1; j>=0; j--){
				free(u[j]);
				return -1;
			}
		}
		u[i]->seq = i;
		sprintf(u[i]->username, "%d-item", i);
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
	}
}

int main(){
	setup();

	for(int i=0; i<10; i++){
		graph_add_vertex(gp, u[i]);
	}

	graph_add_edge(gp, u[0], u[1]);
	graph_add_edge(gp, u[0], u[2]);
	graph_add_edge(gp, u[0], u[3]);
	graph_add_edge(gp, u[0], u[4]);

	graph_add_edge(gp, u[1], u[5]);
	graph_add_edge(gp, u[1], u[8]);
	graph_add_edge(gp, u[1], u[2]);

	graph_add_edge(gp, u[2], u[5]);
	graph_add_edge(gp, u[2], u[7]);

	graph_add_edge(gp, u[3], u[1]);
	graph_add_edge(gp, u[3], u[6]);
	graph_add_edge(gp, u[3], u[7]);

	graph_add_edge(gp, u[4], u[5]);

	graph_add_edge(gp, u[5], u[6]);

	graph_add_edge(gp, u[6], u[7]);

	graph_add_edge(gp, u[7], u[8]);

	graph_add_edge(gp, u[8], u[9]);

	graph_add_edge(gp, u[9], u[0]);

	graph_dump(gp, print);

	puts("Drop 0-item");
	graph_drop_vertex(gp, u[0]);
	graph_dump(gp, print);
	puts("");

	puts("Remove 9-item(will failure, because 8-item adjacent to 9-item)");
	graph_remove_vertex(gp, u[9]);
	graph_dump(gp, print);
	puts("");

	puts("Remove edge from 8-item to 9-item");
	graph_remove_edge(gp, u[8], u[9]);
	graph_dump(gp, print);
	puts("");

	puts("Remove 9-item(will success)");
	graph_remove_vertex(gp, u[9]);
	graph_dump(gp, print);
	puts("");	

	puts("Remove edge from 1-item to 5-item");
	graph_remove_edge(gp, u[1], u[5]);
	graph_dump(gp, print);
	puts("");

	puts("Add edge from 1-item to 5-item");
	graph_add_edge(gp, u[1], u[5]);
	graph_dump(gp, print);
	puts("");

	graph_dump(gp, print);


	enddown();
	return 0;
}