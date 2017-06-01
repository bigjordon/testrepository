int main(int __argc, char* __argv[]) 
{ 
	int* __p = (int*)__argc;
	
	(*__p) = 9999;

	__asm__("":::"memory"); // comment or not

	if((*__p) == 9999) 
		return 5;

	return (*__p); 
}
/*gcc -O -S example1.c*/
