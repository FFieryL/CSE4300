#include <types.h>
#include <kern/errno.h>
#include <kern/limits.h>
#include <kern/unistd.h>
#include <vfs.h>
#include <vnode.h>
#include <lib.h>
#include <thread.h>

int _exit(int code){
	kprintf("%d\n", code);
	thread_exit();
}

int printint(int c){
	kprintf("%d\n", c);
	return (c % 5 == 0) ? 0 : 1;
}

int reversestring(const char* str, int len){
	int i;
	char reversed[len + 1];
	for (i = 0; i < len; i++){
		reversed[i] = str[len - i - 1];
	}
	reversed[len] = '\0';
	kprintf("%s\n", reversed);
	return (len % 2 == 0) ? 1 : 0;
}
