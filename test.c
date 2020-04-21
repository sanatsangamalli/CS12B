#include<stdio.h>
int main(void){
	/*int *p[10][20];
	printf("%lu bytes\n", sizeof(p));
	printf("%lu bytes\n", sizeof(*p));
	printf("%lu bytes\n", sizeof(*(*p)));
	printf("%lu bytes\n", sizeof(*(*(*p))));
	//printf("%lu bytes\n", sizeof(*(*(*(*p)))));
	int x = 4;
	int *p = &x;
	int *k = p++;
	int r = p-k;
	printf("p: %d\nk: %d\nr: %d\n", *p, *k ,r);*/
	int x = 1, y = 2, z[10];
	int *ip; /* ip is a pointer to int */
	ip = &x; /* ip now points to x */
	y = *ip; /* y is now 1 */
	*ip = 0; /* x is now 0 */
	z[0] = 17;
	ip = &z[0]; /* ip now points to z[0] */
	printf("%d %d\n", *ip, y);
	z[0] = 0;
	printf("%d %d", *ip, y);
}