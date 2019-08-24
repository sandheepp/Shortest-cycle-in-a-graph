#include <stdio.h>
int main( ) {

   int n,m;
   scanf("%d %d", &n, &m);

   int u[m] , v[m] ;
   long int h[m], t[m] ;

    int i;
    for( i = 0; i < m; i +=1 ){
        printf("line%d : ",i);
        scanf("%d%d%ld%ld",&u[i],&v[i], &t[i], &h[i]);
    }

    printf("%d \n", i);
    printf("%ld \n", t[0]-h[0]);

    graph d(n);
    // making above uhown graph 
	for (int j=0; j<m;j++)
	{
        printf("%ld", t[j]-h[j]);
	    g.addEdge(u[j]-1, v[j]-1, t[j]-h[j]); 
	}




    return 0;
}