int reversestring(const char* str, int len);

int main(){
	const char* str1 = "Hello World!";
	int len1 = strlen(str1);

	int result1 = reversestring(str1, len1);

	_exit(0);
}
