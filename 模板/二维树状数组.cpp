//http://blog.csdn.net/zxy_snow/article/details/6264135
#include <queue>
#include <stack>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <limits.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int MAX = 1010;
int c[MAX][MAX];
int n;
int Lowbit(int x)
{
	return x & (-x);
}
void Updata(int x,int y)
{
	int i,k;
	for(i=x; i<=n; i+=Lowbit(i))
		for(k=y; k<=n; k+=Lowbit(k))
			c[i][k]++;
}
int Get(int x,int y)
{
	int i,k,sum = 0;
	for(i=x; i>0; i-=Lowbit(i))
		for(k=y; k>0; k-=Lowbit(k))
			sum += c[i][k];
	return sum;
}
int main()
{
	int ncases,m;
	int x1,y1,x2,y2;
	char ch[2];
	scanf("%d",&ncases);
	while( ncases-- )
	{
		memset(c,0,sizeof(c));
		scanf("%d%d",&n,&m);
		while( m-- )
		{
			scanf("%s",ch);
			if( ch[0] == 'C' )
			{
				scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
				x1++; y1++; x2++; y2++;
				Updata(x2,y2);
				Updata(x1-1,y1-1);
				Updata(x1-1,y2);
				Updata(x2,y1-1);
			}
			else
			{
				scanf("%d%d",&x1,&y1);
				printf("%d\n",Get(x1,y1)%2);
			}
		}
		printf("\n");
	}
return 0;
}
