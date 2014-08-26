#include <stdio.h>

int my_is_numeric(char c){
	return (c >= '0' && c <= '9');
}

int my_atoi(const char *str){
	int value = 0;

	int pos = 0;
	int sign = 1;
	if(str[pos] == '-'){
		sign *= -1;
		pos++;
	}
	else if(str[pos] == '+'){
		pos++;
	}

	while(str[pos] != '\0'){
		if(!my_is_numeric(str[pos])){
			return 0;
		}
		value = (value<<3) + (value<<1) + (str[pos] - '0');
		pos++;
	}
	return value*sign;
}

int main(){
	char str[] = "-000999999000";

	printf("%d\n", my_atoi(str));
	return 0;
}

