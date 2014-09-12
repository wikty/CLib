#include <stdlib.h>

#include "ohtable.h"

/* If pointer this address means the position had a data before */
static char ohtable_vacated;

int ohtable_init(OHTable *ohtb,
				unsigned int positions,
				int (*hash1)(const void *data),
				int (*hash2)(const void *data),
				void (*destroy)(void *data),
				int (*match)(const void *key1, const void *key2)){
	if((ohtb->table = (void **)malloc(positions * sizeof((void *))) == NULL){
		return -1;
	}
	for(int i=0; i<positions; i++){
		ohtb->table[i] = NULL;
	}


	ohtb->positions = positions;
	ohtb->hash1 = hash1;
	ohtb->hash2 = hash2;
	ohtb->destroy = destroy;
	ohtb->match = match;
	ohtb->size = 0;
	ohtb->vacated = &ohtable_vacated;
	return 0;
}

void ohtable_destroy(OHTable *ohtb){
	if(ohtb->destroy!=NULL){
		for(int i=0; i<ohtb->positions; i++){
			if(ohtb->table[i] != NULL && ohtb->table[i] != ohtb->vacated){
				ohtb->destroy(ohtb->table[i]);
			}
		}
	}
	free(ohtb->table);

	memset(ohtb, 0, sizeof(*ohtb));
}

int ohtable_insert(OHTable *ohtb, const void *data){
	/* table is filled */
	if(ohtb->size == ohtb->positions){
		return -1;
	}

	/* data is existed*/
	if(ohtable_has_data(ohtb, data)){
		return 1;
	}

	for(int i=0; i<ohtb->positions; i++){
		int pos = (ohtb->hash1(data) + (ohtb->hash2(data))*i) % ohtb->positions;
		if(ohtb->table[pos]==NULL || ohtb->table[pos]==ohtb->vacated){
			ohtb->table[pos] = (void *)data;
			ohtb->size++;
			return 0;
		}
	}
	/* hash function is correctly */
	return -1;
}

int ohtable_remove(OHTable *ohtb, const void *data){
	for(int i=0; i<ohtb->positions; i++){
		int pos = (ohtb->hash1(data) + (ohtb->hash2(data))*i) % ohtb->positions;
		if(ohtb->table[pos]==NULL){
			return -1;
		}
		if(ohtb->table[pos]==ohtb->vacated){
			continue;
		}
		if(ohtb->match(ohtb->table[pos], data)){
			ohtb->table[pos]=ohtb->vacated;
			ohtb->size--;
			return 0;
		}
		
	}
	return -1;
}

int ohtable_has_data(OHTable *ohtb, const void *data){
	for(int i=0; i<ohtb->positions; i++){
		int pos = (ohtb->hash1(data) + (ohtb->hash2(data))*i) % ohtb->positions;
		if(ohtb->table[pos]==NULL){
			return 0;
		}
		if(ohtb->table[pos]==ohtb->vacated){
			continue;
		}
		if(ohtb->match(ohtb->table[pos], data)){
			return 1;
		}
	}
	return 0;
}

void ohtable_dump(OHTable *ohtb, void (*print)(const void *data)){
	for(int i=0; i<ohtb->positions; i++){
		print(ohtb->positions+i);
	}
}