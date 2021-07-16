#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void){
    int start;
    int nokori;
    int ichi;
    int ni;
    int ans;
    int pla;
    int good;
    int wariichi;
    int warini;
    int shou;
    int owari;

    while(1){
    	printf("計算ゲームです。1→足し算  2→掛け算  3→割り算 \n");
    	scanf("%d",&start);
    	if(start==1)
    	{
    		printf("足し算コーススタート！\n");
    		for(nokori=10;nokori>0;nokori--)
    		{
    			int seed=(unsigned int)time(NULL);
                srand(seed);

                   ichi = rand()%50+1;
    			ni   = rand()%50+1;
    
    			ans = ichi+ni;
    			good = 0;
    
    			while(1)
    			{
    				printf("%d + %d = ?\n",ichi,ni);
    				scanf("%d",&pla);
    				if(pla == ans)
    				{
    					printf("正解！\n");
    					good=1;
    					break;
    				}
    				else
    				{
    					printf("残念！もう一度！\n");
    				}
    			}
    		}
    	}
    		if(start==2)
    	{
    		printf("掛け算コーススタート！\n");
    		for(nokori=10;nokori>0;nokori--)
    		{
    			int seed=(unsigned int)time(NULL);
                srand(seed);

                   ichi = rand()%20+1;
    			ni   = rand()%9+1;
    
    			ans = ichi*ni;
    			good = 0;
    
    			while(1)
    			{
    				printf("%d × %d = ?\n",ichi,ni);
    				scanf("%d",&pla);
    				if(pla == ans)
    				{
    					printf("正解！\n");
    					good=1;
    					break;
    				}
    				else
    				{
    					printf("残念！もう一度！\n");
    				}
    			}
    		}
    
    	}
    	if(start==3)
    	{
    		printf("割り算コーススタート！\n");
    		for(nokori=10;nokori>0;nokori--)
    		{
    			int seed=(unsigned int)time(NULL);
                srand(seed);

                   warini = rand()%7+2;
    			shou = rand()%20+1;
    
    			wariichi=warini*shou;
    			shou = wariichi/warini;
    
    			good = 0;
    
    			while(1)
    			{
    				printf("%d ÷ %d = ?\n",wariichi,warini);
    				scanf("%d",&pla);
    				if(pla == shou)
    				{
    					printf("正解！\n");
    					good=1;
    					break;
    				}
    				else
    				{
    					printf("残念！もう一度！\n");
    				}
    			}
    		}	
    	}
        int seed=(unsigned int)time(NULL);
                srand(seed);
    	owari=rand()%5+1;
    	switch(owari)
    	{
    		case 1:{
    			printf("\n\nあなたの計算能力はかなり高いです！\n\n");
    			break;
    			}
    		case 2:{
    			printf("\n\nあなたの計算能力は高い方です！\n\n");
    			break;
    			}
    		case 3:{
    			printf("\n\nあなたの計算能力は普通レベルです\n\n");
    			break;
    			}
    		case 4:{
    			printf("\n\n次はもう少し頑張ってみましょう\n\n");
    			break;
    			}
    		case 5:{
    			printf("\n\nあなたは計算をするのが得意なようですね！\n素晴らしい！\n\n");
    			break;
    			}/*結果が出ると楽しいと思うのでやってみた
    		      ランダムなので適当に
    		      */	
    	}
    }
    return 1;
}
