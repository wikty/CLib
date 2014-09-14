#include <stdio.h>

#include "str_match.h"




int main(){
	char *str1 = "here is a simple example";
	char *str2 = "example";

	int pos;

	printf("%s\n", "Ordinary Prefix String Match");
	pos = prefix_str_match(str1, str2);
	if(pos != -1){
		printf("%s\n", str1);
		for(int i=0; i<pos; i++){
			printf("%c", ' ');
		}
		printf("%s\n", str2);
		printf("Matched On %d\n", pos);
	}
	else{
		printf("%s\n", "Not Matched");
	}
	printf("\n");

	printf("%s\n", "Ordinary Suffix String Match ");
	pos = suffix_str_match(str1, str2);
	if(pos != -1){
		printf("%s\n", str1);
		for(int i=0; i<pos; i++){
			printf("%c", ' ');
		}
		printf("%s\n", str2);
		printf("Matched On %d\n", pos);
	}
	else{
		printf("%s\n", "Not Matched");
	}
	printf("\n");


	printf("%s\n", "KMP String Match");
	pos = kmp_str_match(str1, str2);
	if(pos != -1){
		printf("%s\n", str1);
		for(int i=0; i<pos; i++){
			printf("%c", ' ');
		}
		printf("%s\n", str2);
		printf("Matched On %d\n", pos);
	}
	else{
		printf("%s\n", "Not Matched");
	}
	printf("\n");

	printf("%s\n", "BM String Match");
	pos = bm_str_match(str1, str2);
	if(pos != -1){
		printf("%s\n", str1);
		for(int i=0; i<pos; i++){
			printf("%c", ' ');
		}
		printf("%s\n", str2);
		printf("Matched On %d\n", pos);
	}
	else{
		printf("%s\n", "Not Matched");
	}
	printf("\n");


	// Test partial match table function
	// int table[4];
	// partial_match_table(str2, table);
	// printf("%s\n", str2);
	// for(int j=0; j<4; j++){
	// 	printf("%d ", table[j]);
	// }
	// printf("\n");

	return 0;
}