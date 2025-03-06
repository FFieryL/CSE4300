#include <unistd.h>
#include <stdio.h>
int printint(int code);

int main(){
	int i;
	int result[5];
	int test[] = {1, 2, 3, 4, 5};
	for (i = 0; i < 5; i++){
		result[i] = printint(test[i]);
	}
	_exit(0);
}
