#include "set.h"

int set_is_member(const Set *st, const void *data){
	Node *pNode = list_search_node(st, data);
	return (pNode == NULL ? 0 : 1);
}

int set_insert(Set *st, const void *data){
	if(set_is_member(st, data)){
		return 1;
	}
	return list_push(st, data);
}

int set_remove(Set *st, const void *data){
	Node *pNode = list_search(st, data);
	if(pNode==NULL){
		return -1;
	}
	Node *p;
	return list_remove(st, pNode, &p);
}

int set_union(Set *st, const Set *st1, const Set *st2){
	set_init(st, st1->destroy, st1->match);

	Node *pCurrentNode = list_head(st1);
	while(pCurrentNode){
		if(set_insert(st, list_node_data(pCurrentNode))!=0){
			set_destroy(st);
			return -1;	
		}
		pCurrentNode = list_node_next(pCurrentNode);
	}

	pCurrentNode = list_head(st2);
	while(pCurrentNode){
		if(!set_is_member(st, list_node_data(pCurrentNode))){
			if(set_insert(st, list_node_data(pCurrentNode))!=0){
				set_destroy(st);
				return -1;
			}
		}
		pCurrentNode = list_node_next(pCurrentNode);
	}
	return 0;
}

int set_intersection(Set *st, const Set *st1, const Set *st2){
	set_init(st, st1->destroy, st1->match);

	Node *pCurrentNode = list_head(st1);
	while(pCurrentNode){
		if(set_is_member(st2, list_node_data(pCurrentNode))){
			if(set_insert(st, list_node_data(pCurrentNode))!=0){
				set_destroy(st);
				return -1;
			}
		}
		pCurrentNode = list_node_next(pCurrentNode);
	}
	return 0;
}

int set_difference(Set *st, const Set *st1, const Set *st2){
	set_init(st, st1->destroy, st1->match);

	Node *pCurrentNode = list_head(st1);
	while(pCurrentNode){
		if(!set_is_member(st2, list_node_data(pCurrentNode))){
			if(set_insert(st, list_node_data(pCurrentNode))!=0){
				set_destroy(st);
				return -1;
			}
		}
		pCurrentNode = list_node_next(pCurrentNode);
	}
	return 0;
}

int set_is_equal(const Set *st1, const Set *st2){
	if(set_len(st1) != set_len(st2)){
		return 0;
	}

	return set_is_subset(st1, st2);
}

int set_is_subset(const Set *st, const Set *st1){
	if(set_len(st) < set_len(st1)){
		return 0;
	}
	Node *pCurrentNode = list_head(st1);
	while(pCurrentNode){
		if(!set_is_member(st, list_node_data(pCurrentNode))){
			return 0;
		}
		pCurrentNode = list_node_next(pCurrentNode);
	}
	return 1;
}