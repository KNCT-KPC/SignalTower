#include <stdio.h>
#include <stdbool.h>

int map[11][11];
bool turn;

int  A(int x,int y,int a,int i,int j,int t)
{
	while(1)
	{
		if(map[x+a*i][y+a*j]==t)
		{
			break;
		}
		else if(map[x+a*i][y+a*j]==turn+1)
		{
			//printf("98");
			a++;
		}
		else if(map[x+a*i][y+a*j]==0)
		{
			return 0;
		}
	}
	for(a;a>=0;a=a-1)
	{
		//printf("97");
		map[x+a*i][y+a*j]=t;
	}
	return 1;
}
int hantei(int x,int y,int t)
{
	int a=1;
	int ct=0;
	for(int i=-1;i<2;i++)
	{
		for(int j=-1;j<2;j++)
		{
			if(map[x+a*i][y+a*j]==turn+1==1)
			{
				if(A(x,y,a,i,j,t)==1)
				{
					ct++;
				}
			}	
		}
	}
	if(ct==0)
	{
		return 0;
	}
	return 1;
}

void  board()
{
	int i=1;
	printf(" ");
	for(i;i<=8;i++)
	{
		printf(" %d ",i);
	}
	puts("←x軸");
	for(int a=1;a<=8;a++)
	{
		printf(" ");
		for(int b=0;b<8;b++)
		{
			printf(" ー");
		}
		puts("");
		printf("%d",a);
		for(int c=1;c<=8;c++)
		{
			printf("|");
			if(map[c][a]==1)
			{
				printf("○");
			}
			else if(map[c][a]==2)
			{
				printf("●");
			}
			else
			{
				printf("　");
			}	
		}
		printf("|");
		puts("");
	}
	printf(" ");
	for(i=0;i<8;i++)
	{
		printf(" ー");
	}	
	puts("");	
	puts("↑");	
	puts("y軸");	
	puts("");	
}

int main(void)
{
	int x;
	int y;

	int ct=1;	
	char s;
	char ss='p';
	int t;
	int a=0;
	
	
	map[4][4]=2;
	map[4][5]=1;
	map[5][4]=1;
	map[5][5]=2;
	
	board();
	while(ct<65)
	{
		if(turn==0)
		{
			t=2;
			printf("黒のターンです\n\n");
		}
		else if(turn==1)
		{
			t=1;
			printf("白のターンです\n\n");
		}
		while(1)
		{
			printf("パスする場合は「p」を入力してください\nパスをしない場合は「Enter」キーを押してください\n");
			scanf("%c",&s);
			//printf("%c",s);
			if(s==ss)
			{
				break;
			}
			while(1)
			{
				printf("x軸の数値を入力してください\n");
				scanf("%d",&x);
			/*	if(x>0&&x<9)
				{
					break;
				}
				else
				{	
					printf("その数値は入力出来ません\nもう一度入力してください\n");
				}
			}
			while(1)
			{*/
				printf("y軸の数値を入力してください\n※x軸の数値を間違えた場合は数値を入力せずに、「Enter」キーを押してください\n");
				scanf("%d",&y);
				if(y>0||y<9||x>0||x<9)
				{
					ct++;
					break;
				}
				else
				{	
					printf("その数値は入力出来ません\nもう一度入力してください\n");
				}
			}
			//printf("99");
			if(hantei(x,y,t)==1)
			{
				//printf("%d",map[4][4]);
				break;
			}
			
			else
			{
				printf("ここには置けません。もう一度入力してください。\n");
				board();
			}
				
		}
		board();
		turn=!turn;
	}
}	
