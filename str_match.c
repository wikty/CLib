#include <stdlib.h>

#include "str_match.h"

#define ASCII_MAX_SIZE 255

static void partial_match_table(const char *str, int table[]);
static void bm_char_table(const char *str, int table[]);
static void bm_suffix_table(const char *str, int table[]);
static void sd_char_table(const char *str, int table[]);
static void hp_char_table(const char *str, int table[]);

int prefix_str_match(const char *str, const char *pattern){
	int str_len = 0;
	int pattern_len = 0;
	const char *p = str;
	while(*p != '\0'){
		p++;
	}
	/* If str's length is larger than pow(2, 31)-1, will error */
	str_len = p - str;
	p = pattern;
	while(*p != '\0'){
		p++;
	}
	pattern_len = p - pattern;

	int i=0, j=0;
	while(i<str_len){
		if(str[i] == pattern[j]){
			i++;
			j++;
			if(j == pattern_len){
				return i - pattern_len;
			}
		}
		else{
			i -= j - 1;
			j = 0;
		}
	}
	return -1;
}

int suffix_str_match(const char *str, const char *pattern){
	int str_len = 0;
	int pattern_len = 0;
	const char *p = str;
	while(*p != '\0'){
		p++;
	}
	/* If str's length is larger than pow(2, 31)-1, will error */
	str_len = p - str;
	p = pattern;
	while(*p != '\0'){
		p++;
	}
	pattern_len = p - pattern;

	int i, j;
	i = j = pattern_len - 1;
	while(i<str_len){
		if(str[i] == pattern[j]){
			i--;
			j--;
			if(j == -1){
				return i + 1;
			}
		}
		else{
			i += pattern_len - j;
			j = pattern_len - 1;
		}
	}
	return -1;
}

int kmp_str_match(const char *str, const char *pattern){
	int str_len = 0;
	int pattern_len = 0;
	const char *p = str;
	while(*p != '\0'){
		p++;
	}
	/* If str's length is larger than pow(2, 31)-1, will error */
	str_len = p - str;
	p = pattern;
	while(*p != '\0'){
		p++;
	}
	pattern_len = p - pattern;

	int *table;
	if((table = (int *)malloc(sizeof(int) * pattern_len)) == NULL){
		return -1;
	}
	partial_match_table(pattern, table);

	int i=0, cursor=0;
	while(i < str_len){
		if(*(str+i) == *(pattern+cursor)){
			i++;
			cursor++;
			if(cursor == pattern_len){
				free(table);
				return i - pattern_len;
			}
		}
		else{
			if(cursor == 0){
				i++;
			}
			else{
				cursor = table[cursor-1];
			}
		}
	}

	free(table);
	return -1;
}

int bm_str_match(const char *str, const char *pattern){
	int str_len = 0;
	int pattern_len = 0;
	const char *p = str;
	while(*p != '\0'){
		p++;
	}
	/* If str's length is larger than pow(2, 31)-1, will error */
	str_len = p - str;
	p = pattern;
	while(*p != '\0'){
		p++;
	}
	pattern_len = p - pattern;

	int *bad_table = NULL;
	if((bad_table = (int *)malloc(sizeof(int) * ASCII_MAX_SIZE)) == NULL){
		return -1;
	}
	int *good_table = NULL;
	if((good_table = (int *)malloc(sizeof(int) * pattern_len)) == NULL){
		free(bad_table);
		return -1;
	}
	bm_char_table(pattern, bad_table);
	bm_suffix_table(pattern, good_table);

	int i, j;
	i = j = pattern_len - 1;
	while(i<str_len){
		if(str[i] == pattern[j]){
			i--;
			j--;
			if(j == -1){
				free(bad_table);
				free(good_table);
				return i + 1;
			}
		}
		else{
			int step1 = bad_table[str[i]];
			int step2;
			if(j == pattern_len-1){
				step2 = -1;
			}
			else{
				step2 = good_table[j+1];
			}
			i += (step1 > step2 ? step1 : step2);
			j = pattern_len - 1;
		}
	}

	free(bad_table);
	free(good_table);
	return -1;
}

int sd_str_match(const char *str, const char *pattern){
	int str_len = 0;
	int pattern_len = 0;
	const char *p = str;
	while(*p != '\0'){
		p++;
	}
	/* If str's length is larger than pow(2, 31)-1, will error */
	str_len = p - str;
	p = pattern;
	while(*p != '\0'){
		p++;
	}
	pattern_len = p - pattern;

	int *table = NULL;
	if((table = (int *)malloc(sizeof(int) * ASCII_MAX_SIZE)) == NULL){
		return -1;
	}
	sd_char_table(pattern, table);

	int i=0, j=0;
	while(i < str_len){
		if(str[i] == pattern[j]){
			i++;
			j++;
			if(j==pattern_len){
				free(table);
				return i - pattern_len;
			}
		}
		else{
			if(i+1 > str_len -1){
				break;
			}
			i = (pattern_len - 1) - j + i + 1 + table[str[i+1]];
			j = 0;
		}
	}

	free(table);
	return -1;
}

int hp_str_match(const char *str, const char *pattern){
	int str_len = 0;
	int pattern_len = 0;
	const char *p = str;
	while(*p != '\0'){
		p++;
	}
	/* If str's length is larger than pow(2, 31)-1, will error */
	str_len = p - str;
	p = pattern;
	while(*p != '\0'){
		p++;
	}
	pattern_len = p - pattern;

	int *table = NULL;
	if((table = (int *)malloc(sizeof(int) * ASCII_MAX_SIZE)) == NULL){
		return -1;
	}
	hp_char_table(pattern, table);

	int i,j;
	i=j=pattern_len - 1;
	while(i<str_len){
		if(str[i] == pattern[j]){
			i--;
			j--;
			if(j==-1){
				free(table);
				return i + 1;
			}
		}
		else{
			int pos = i + ((pattern_len-1) - j);
			i = pos + pattern_len - table[str[pos]];
			j = pattern_len - 1;
		}
	}

	free(table);
	return -1;
}

/*
 *	Internal Functions
 */

void partial_match_table(const char *str, int table[]){
	int str_len = 0;
	const char *p = str;
	while(*p != '\0'){
		p++;
	}
	/* If str's length is larger than pow(2, 31)-1, will error */
	str_len = p - str;

	for(int i=0; i<str_len; i++){

		/* longest common prefix and suffix in [0, i] */
		int longest = 0;
		for(int j=i-1; j>=1; j--){  /* current length is j */
			int matched = 1;
			for(int m=0; m<j; m++){
				if(*(str+m) != *(str+i-j+1+m)){
					matched = 0;
					break;
				}
			}
			if(matched){
				longest = j;
				break;
			}
		}
		table[i] = longest;
	}
}

void bm_char_table(const char *str, int table[]){
	int str_len = 0;
	const char *p = str;
	while(*p != '\0'){
		p++;
	}
	/* If str's length is larger than pow(2, 31)-1, will error */
	str_len = p - str;

	int i=0;
	for(; i<ASCII_MAX_SIZE; i++){
		table[i] = str_len;
	}
	/* the later will override */
	for(i=str_len-1; i>=0; i--){
		table[str[i]] = str_len - (i+1);
	}

}

void bm_suffix_table(const char *str, int table[]){
	int str_len = 0;
	const char *p = str;
	while(*p != '\0'){
		p++;
	}
	/* If str's length is larger than pow(2, 31)-1, will error */
	str_len = p - str;

	for(int i=str_len-1; i>0; i--){
		/* [i,,,str_len-1] is good suffix */
		
		int suffix_len = (str_len - 1) - i + 1;
		int count = suffix_len;
		int cursor = suffix_len - 1;
		int suffix = str_len - 1;
		while(cursor >= 0){
			if(str[suffix] == str[cursor]){
				cursor--;
				suffix--;
			}
			else{
				cursor += ((str_len-1) - suffix) - 1;
				suffix = str_len - 1;
				count--;
			}
		}

		table[i] = str_len + suffix_len - count;
	}
}

void sd_char_table(const char *str, int table[]){
	int str_len = 0;
	const char *p = str;
	while(*p != '\0'){
		p++;
	}
	/* If str's length is larger than pow(2, 31)-1, will error */
	str_len = p - str;

	int i=0;
	for(; i<ASCII_MAX_SIZE; i++){
		table[i] = 1;
	}
	/* later element will override */
	for(i=0; i<str_len; i++){
		table[str[i]] = -1 * i;
	}
}

void hp_char_table(const char *str, int table[]){
	int str_len = 0;
	const char *p = str;
	while(*p != '\0'){
		p++;
	}
	/* If str's length is larger than pow(2, 31)-1, will error */
	str_len = p - str;

	int i=0;
	for(; i<ASCII_MAX_SIZE; i++){
		table[i] = 0;
	}
	/* later element will override */
	for(i=0; i<str_len-1; i++){
		/* NOTICE: dont calculate str[str_len-1] */
		table[str[i]] = i + 1;
	}

}