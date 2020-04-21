#include<stdio.h>
# define min(x,y) (x < y ? x : y)
int main(void){
	/*int *p[10][20];
	printf("%lu bytes\n", sizeof(p));
	printf("%lu bytes\n", sizeof(*p));
	printf("%lu bytes\n", sizeof(*(*p)));
	printf("%lu bytes\n", sizeof(*(*(*p))));
	//printf("%lu bytes\n", sizeof(*(*(*(*p)))));*/
	int x = 1;
	int y = min(x++,x++);
	printf("%d\n", y);
}
