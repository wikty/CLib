#include <stdlib.h>
#include "htable.h"

int htable_init(HTable *htb,
				unsigned int buckets,
				int (*hash)(const void *key),
				void (*destroy)(void *data)
				int (*match)(const void *key1, const void *key2)){
	if(match==NULL || hash==NULL || buckets == 0){
		return -1;
	}

	if((htb->table = (List *)malloc(buckets * sizeof(List))) == NULL){
		return -1;
	}
	for(int i=0; i<buckets; i++){
		list_init((List *)(htb->table+i), destroy, match);
	}

	htb->buckets = buckets;
	htb->hash = hash;
	htb->match = match;
	htb->destroy = destroy;
	htb->size = 0;
	return 0;
}

void htable_destroy(HTable *htb){
	for(int i=0; i<htb->buckets; i++){
		list_destroy((List *)(htb->table+i));
	}
	free(htb->table);

	memset(htb, 0, sizeof(*htb));
}

int htable_insert(HTable *htb, const void *data){
	/* existed */
	if(htable_has_data(htb, data)){
		return 1;
	}

	/* insert */
	/* Don't trust User function htb->hash() can return suitable value */
	int pos = htb->hash(data) % htb->buckets;
	if(list_push((List *)(htb->table+pos), data) != 0){
		return -1;
	}
	htb->size++;
	return 0;
}

int htable_remove(HTable *htb, const void *data){
	/* Don't trust User function htb->hash() can return suitable value */
	int pos = htb->hash(data) % htb->buckets;
	List *pList = (List *)(htb->table+pos);
	Node *pNode = list_search(pList, data);
	/* data not in htb */
	if(pNode==NULL){
		return -1;
	}

	void *temp;
	if(list_remove(pList, pNode, (void**)&temp)!=0){
		return -1;
	}
	htb->size--;
	return 0;
}

int htable_has_data(HTable *htb, const void *data){
	/* Don't trust User function htb->hash() can return suitable value */
	int pos = htb->hash(data) % htb->bucket;
	List *pList = (List *)(htb->table+pos);
	if(list_search(pList, data)!=NULL){
		return 1;
	}
	return 0;
}