#include <stdio.h>
int global_var;

int global_initialized_var=5;
void function()
{
	int stack_var;
	printf("function stack is %p\n",&stack_var);
}
main()
{
	int stack_var;
	static int static_initialized_var=5;
	static int static_var;
	int *heap_var_ptr;

	heap_var_ptr=(int *)malloc(4);
	printf("global_initialized_var is %p\n",&global_initialized_var);
	printf("static_initialized_var is %p\n",&static_initialized_var);

	printf("global_var is %p\n",&global_var);
	printf("static_var is %p\n",&static_var);

	printf("heap_var is %p\n",heap_var_ptr);
	
	printf("stack_var is %p\n",&stack_var);
	function();
}

