#include<stdio.h>
#include<stdlib.h>
#include "link.h"
#include "config.h"

int grid[24][24]={0};

void pg(void)
{
    grid[0][0]=-1,grid[0][23]=-1,grid[23][0]=-1,grid[23][23]=-1;
    printf("     0   1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22  23\n");
    for(int i=0;i<24;i++)
    {
        if(i==1 || i==23)
        printf("\033[1;34m       ---------------------------------------------------------------------   \033[0m\n");
        printf("%02d  ",i);
        for(int j=0;j<24;j++)
        {
            if((j==1 || j==23) && (i!=0) && i!=23) printf("\033[1;31m| \033[0m");
            if((j==1 || j==23) && (i==0 || i==23) )printf("  ");

            if(grid[i][j]==0) printf("⬛ ");
            else if(grid[i][j]==1) printf("🟦 ");
            else if(grid[i][j]==2) printf("🟥 ");
            else if(grid[i][j]==-1) printf("   ");
        }
        printf("\n");
    }
}

int main()
{
    int x,y;
    printf("To quit the game, please enter 0 0 as input\n");
    pg();
    while(1>0)
    {
        printf("Blues chance\n");
        scanf("%d%d",&x,&y);
        if(x==0 && y==0) return 0;
        while(grid[x][y]!=0 || y==0 || y>=23 || x>23)
        {
            printf("Cant choose that block, enter coord again\n");
            scanf("%d%d",&x,&y);
            if(x==0 && y==0)
            {
                printf("RED WINSSS!!");
                 return 0;
            }
        }
        grid[x][y]=1;
        
        lock_links(x, y, 1);
        
        pg();
        if(join(x,y,1)==1) return 0;
        printf("blue %d\n",links[x][y]);

        printf("Reds chance\n");
        scanf("%d%d",&x,&y);
        if(x==0 && y==0) return 0;
        while(grid[x][y]!=0 || x==0 || x>=23 || y>23)
        {
            printf("Cant choose that block, enter coord again\n");
            scanf("%d%d",&x,&y);
            if(x==0 && y==0)
            {
                printf("BLUE WINSSS!!");
                 return 0;
            }
        }
        grid[x][y]=2;
        
        
        lock_links(x, y, 2);
        
        pg();
        if(join(x,y,2)==1) return 0;
        printf("red %d\n",links[x][y]);
    }
}