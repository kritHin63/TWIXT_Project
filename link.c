#include "link.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

extern int grid[ROWS][COLS];
int links[24][24];
int visited[24][24];


int active_links[ROWS][COLS][8];


int dr[8] = {-2, -2, -1, -1,  1,  1,  2,  2};
int dc[8] = {-1,  1, -2,  2, -2,  2, -1,  1};


int is_blocked(int r, int c, int nr, int nc) {
   
    int cross_r1 = r, cross_c1 = nc;
    int cross_r2 = nr, cross_c2 = c;

    if (cross_r1 >= 0 && cross_r1 < 24 && cross_c1 >= 0 && cross_c1 < 24) {
        for (int k = 0; k < 8; k++) {
            if (cross_r1 + dr[k] == cross_r2 && cross_c1 + dc[k] == cross_c2) {
                if (active_links[cross_r1][cross_c1][k]) return 1;
            }
        }
    }
    return 0;
}


void lock_links(int r, int c, int player) {
    for (int k = 0; k < 8; k++) {
        int nr = r + dr[k];
        int nc = c + dc[k];
        
        
        if (nr >= 0 && nr < 24 && nc >= 0 && nc < 24 && grid[nr][nc] == player) {
            
            if (!is_blocked(r, c, nr, nc)) {
                active_links[r][c][k] = 1;
                
                
                for(int rev=0; rev<8; rev++) {
                    if (nr + dr[rev] == r && nc + dc[rev] == c) {
                        active_links[nr][nc][rev] = 1;
                        break;
                    }
                }
            }
        }
    }
}


int get_val_checked(int r, int c, int nr, int nc) {
    if (nr < 0 || nr >= 24 || nc < 0 || nc >= 24) return 0;
    if (is_blocked(r, c, nr, nc)) return 0; 
    return links[nr][nc];
}


int join_recursive(int i, int j, int c)
{
    if (i < 0 || i >= 24 || j < 0 || j >= 24) return 0;
    if (visited[i][j]) return 0;
    
    visited[i][j] = 1;

    links[0][0] = -1, links[0][23] = -1, links[23][0] = -1, links[23][23] = -1;

    //blue
    if (c == 1)
    {
        if (i == 0 || i == 1)
        {
            links[i][j] += 10;
            if(i==0)
            {
                if(j==1)
                {
                    
                    if(get_val_checked(i,j, i + 2, j + 1) == 1 || get_val_checked(i,j, i + 1, j + 2) == 1)
                        links[i][j] += 1;
                    if(links[i][j]>0)
                    {
                        
                        if(grid[i+2][j+1]==1 && !is_blocked(i,j, i+2,j+1)) join_recursive(i+2,j+1,1);
                        if(grid[i+1][j+2]==1 && !is_blocked(i,j, i+1,j+2)) join_recursive(i+1,j+2,1);
                    }
                }
                else{
                    if(get_val_checked(i,j, i + 2, j - 1) == 1 || get_val_checked(i,j, i + 2, j + 1) == 1 || get_val_checked(i,j, i + 1, j - 2) == 1 || get_val_checked(i,j, i + 1, j + 2) == 1)
                        links[i][j] += 1;
                    if(links[i][j]>0)
                    {
                        if(grid[i+2][j-1]==1 && !is_blocked(i,j, i+2,j-1)) join_recursive(i+2,j-1,1);
                        if(grid[i+2][j+1]==1 && !is_blocked(i,j, i+2,j+1)) join_recursive(i+2,j+1,1);
                        if(grid[i+1][j-2]==1 && !is_blocked(i,j, i+1,j-2)) join_recursive(i+1,j-2,1);
                        if(grid[i+1][j+2]==1 && !is_blocked(i,j, i+1,j+2)) join_recursive(i+1,j+2,1);
                    }
                }
            }
            else
            {
                if(j==1){
                    if(get_val_checked(i,j, i + 2, j + 1) == 1 || get_val_checked(i,j, i - 1, j + 2) == 1 ||  get_val_checked(i,j, i + 1, j + 2) == 1)
                        links[i][j]+=1;
                    if(links[i][j]>0)
                    {
                        if(grid[i+2][j+1]==1 && !is_blocked(i,j, i+2,j+1)) join_recursive(i+2,j+1,1);
                        if(grid[i-1][j+2]==1 && !is_blocked(i,j, i-1,j+2)) join_recursive(i-1,j+2,1);
                        if(grid[i+1][j+2]==1 && !is_blocked(i,j, i+1,j+2)) join_recursive(i+1,j+2,1);
                    }  
                }else{
                    if(get_val_checked(i,j, i + 2, j - 1) == 1 || get_val_checked(i,j, i + 2, j + 1) == 1 || get_val_checked(i,j, i - 1, j - 2) == 1 || get_val_checked(i,j, i - 1, j + 2) == 1 || get_val_checked(i,j, i + 1, j - 2) == 1 || get_val_checked(i,j, i + 1, j + 2) == 1)
                        links[i][j]+=1;
                    if(links[i][j]>0)
                    {
                        if(grid[i+2][j-1]==1 && !is_blocked(i,j, i+2,j-1)) join_recursive(i+2,j-1,1);
                        if(grid[i+2][j+1]==1 && !is_blocked(i,j, i+2,j+1)) join_recursive(i+2,j+1,1);
                        if(grid[i-1][j-2]==1 && !is_blocked(i,j, i-1,j-2)) join_recursive(i-1,j-2,1);
                        if(grid[i-1][j+2]==1 && !is_blocked(i,j, i-1,j+2)) join_recursive(i-1,j+2,1);
                        if(grid[i+1][j-2]==1 && !is_blocked(i,j, i+1,j-2)) join_recursive(i+1,j-2,1);
                        if(grid[i+1][j+2]==1 && !is_blocked(i,j, i+1,j+2)) join_recursive(i+1,j+2,1);
                    }
                }
            }
        }
        else if (i == 23 || i == 22)
        {
            links[i][j] += 1;
            if(i==23)
            {
                if(j==1){
                    if(get_val_checked(i,j, i - 2, j + 1) == 10 ||  get_val_checked(i,j, i - 1, j + 2) == 10)
                        links[i][j] += 10;   

                    if(links[i][j]>0)
                    {
                        if(grid[i-2][j+1]==1 && !is_blocked(i,j, i-2,j+1)) join_recursive(i-2,j+1,1);
                        if(grid[i-1][j+2]==1 && !is_blocked(i,j, i-1,j+2)) join_recursive(i-1,j+2,1);
                    }
                }else{
                    if(get_val_checked(i,j, i - 2, j - 1) == 10 || get_val_checked(i,j, i - 2, j + 1) == 10 || get_val_checked(i,j, i - 1, j - 2) == 10 || get_val_checked(i,j, i - 1, j + 2) == 10)
                        links[i][j] += 10;   

                    if(links[i][j]>0)
                    {
                        if(grid[i-2][j-1]==1 && !is_blocked(i,j, i-2,j-1)) join_recursive(i-2,j-1,1);
                        if(grid[i-2][j+1]==1 && !is_blocked(i,j, i-2,j+1)) join_recursive(i-2,j+1,1);
                        if(grid[i-1][j-2]==1 && !is_blocked(i,j, i-1,j-2)) join_recursive(i-1,j-2,1);
                        if(grid[i-1][j+2]==1 && !is_blocked(i,j, i-1,j+2)) join_recursive(i-1,j+2,1);
                    }
                }
            }
            else
            {
                if(j==1)
                {
                    if(get_val_checked(i,j, i - 2, j + 1) == 10 ||  get_val_checked(i,j, i - 1, j + 2) == 10 || get_val_checked(i,j, i + 1, j + 2) == 10)
                        links[i][j] += 10;
                    if(links[i][j]>0)
                    {
                        if(grid[i-2][j+1]==1 && !is_blocked(i,j, i-2,j+1)) join_recursive(i-2,j+1,1);
                        if(grid[i-1][j+2]==1 && !is_blocked(i,j, i-1,j+2)) join_recursive(i-1,j+2,1);
                        if(grid[i+1][j+2]==1 && !is_blocked(i,j, i+1,j+2)) join_recursive(i+1,j+2,1);
                    }  
                }else{
                    if(get_val_checked(i,j, i - 2, j - 1) == 10 || get_val_checked(i,j, i - 2, j + 1) == 10 || get_val_checked(i,j, i - 1, j - 2) == 10 || get_val_checked(i,j, i - 1, j + 2) == 10 || get_val_checked(i,j, i + 1, j - 2) == 10 || get_val_checked(i,j, i + 1, j + 2) == 10)
                        links[i][j] += 10;
                    if(links[i][j]>0)
                    {
                        if(grid[i-2][j-1]==1 && !is_blocked(i,j, i-2,j-1)) join_recursive(i-2,j-1,1);
                        if(grid[i-2][j+1]==1 && !is_blocked(i,j, i-2,j+1)) join_recursive(i-2,j+1,1);
                        if(grid[i-1][j-2]==1 && !is_blocked(i,j, i-1,j-2)) join_recursive(i-1,j-2,1);
                        if(grid[i-1][j+2]==1 && !is_blocked(i,j, i-1,j+2)) join_recursive(i-1,j+2,1);
                        if(grid[i+1][j-2]==1 && !is_blocked(i,j, i+1,j-2)) join_recursive(i+1,j-2,1);
                        if(grid[i+1][j+2]==1 && !is_blocked(i,j, i+1,j+2)) join_recursive(i+1,j+2,1);
                    }
                }
            }
        }
        else
        {
            if (get_val_checked(i,j, i - 2, j - 1) == 10 || get_val_checked(i,j, i - 2, j + 1) == 10 || get_val_checked(i,j, i + 2, j - 1) == 10 || get_val_checked(i,j, i + 2, j + 1) == 10 || get_val_checked(i,j, i - 1, j - 2) == 10 || get_val_checked(i,j, i - 1, j + 2) == 10 || get_val_checked(i,j, i + 1, j - 2) == 10 || get_val_checked(i,j, i + 1, j + 2) == 10)
            {
                links[i][j] += 10;
            }
            if (get_val_checked(i,j, i - 2, j - 1) == 1 || get_val_checked(i,j, i - 2, j + 1) == 1 || get_val_checked(i,j, i + 2, j - 1) == 1 || get_val_checked(i,j, i + 2, j + 1) == 1 || get_val_checked(i,j, i - 1, j - 2) == 1 || get_val_checked(i,j, i - 1, j + 2) == 1 || get_val_checked(i,j, i + 1, j - 2) == 1 || get_val_checked(i,j, i + 1, j + 2) == 1)
            {
                links[i][j] += 1;
            }
            if(links[i][j]>0)
            {
                if(grid[i-2][j-1]==1 && !is_blocked(i,j, i-2,j-1)) join_recursive(i-2,j-1,1);
                if(grid[i-2][j+1]==1 && !is_blocked(i,j, i-2,j+1)) join_recursive(i-2,j+1,1);
                if(grid[i-1][j-2]==1 && !is_blocked(i,j, i-1,j-2)) join_recursive(i-1,j-2,1);
                if(grid[i-1][j+2]==1 && !is_blocked(i,j, i-1,j+2)) join_recursive(i-1,j+2,1);
                if(grid[i+1][j-2]==1 && !is_blocked(i,j, i+1,j-2)) join_recursive(i+1,j-2,1);
                if(grid[i+1][j+2]==1 && !is_blocked(i,j, i+1,j+2)) join_recursive(i+1,j+2,1);
                if(grid[i+2][j-1]==1 && !is_blocked(i,j, i+2,j-1)) join_recursive(i+2,j-1,1);
                if(grid[i+2][j+1]==1 && !is_blocked(i,j, i+2,j+1)) join_recursive(i+2,j+1,1);
            }
        }

        if (links[i][j] == 11)
        {
            printf("BLUE WINS");
            return 1;
        }
        else return 0;
    }

    //RED
    if (c == 2)
    {
        if (j == 0 || j == 1)
        {
            links[i][j] += 20;
            if(j==0)
            {
                if(i==1){
                    if(get_val_checked(i,j, i + 2, j + 1) == 2 || get_val_checked(i,j, i + 1, j + 2) == 2)
                        links[i][j] += 2;
                    if(links[i][j]>0)
                    {
                        if(grid[i+2][j+1]==2 && !is_blocked(i,j, i+2,j+1)) join_recursive(i+2,j+1,2);
                        if(grid[i+1][j+2]==2 && !is_blocked(i,j, i+1,j+2)) join_recursive(i+1,j+2,2);
                    }
                }
                else{
                    if(get_val_checked(i,j, i - 2, j + 1) == 2 || get_val_checked(i,j, i + 2, j + 1) == 2 || get_val_checked(i,j, i + 1, j + 2) == 2 || get_val_checked(i,j, i - 1, j + 2) == 2)
                        links[i][j] += 2;
                    if(links[i][j]>0)
                    {
                        if(grid[i-2][j+1]==2 && !is_blocked(i,j, i-2,j+1)) join_recursive(i-2,j+1,2);
                        if(grid[i+2][j+1]==2 && !is_blocked(i,j, i+2,j+1)) join_recursive(i+2,j+1,2);
                        if(grid[i+1][j+2]==2 && !is_blocked(i,j, i+1,j+2)) join_recursive(i+1,j+2,2);
                        if(grid[i-1][j+2]==2 && !is_blocked(i,j, i-1,j+2)) join_recursive(i-1,j+2,2);
                    }
                }
            }
            if(j==1)
            {
                if(i==1)
                {
                    if(get_val_checked(i,j, i + 2, j + 1) == 2 || get_val_checked(i,j, i + 1, j + 2) == 2|| get_val_checked(i,j, i+2, j-1)==2)
                        links[i][j] += 2;
                    if(links[i][j]>0)
                    {
                        if(grid[i+2][j+1]==2 && !is_blocked(i,j, i+2,j+1)) join_recursive(i+2,j+1,2);
                        if(grid[i+1][j+2]==2 && !is_blocked(i,j, i+1,j+2)) join_recursive(i+1,j+2,2);
                        if(grid[i+2][j-1]==2 && !is_blocked(i,j, i+2,j-1)) join_recursive(i+2,j-1,2);
                    }
                }
                else{
                    if(get_val_checked(i,j, i - 2, j + 1) == 2 || get_val_checked(i,j, i + 2, j + 1) == 2 || get_val_checked(i,j, i + 1, j + 2) == 2|| get_val_checked(i,j, i - 1, j + 2) == 2 || get_val_checked(i,j, i-2, j-1)==2 ||get_val_checked(i,j, i+2, j-1)==2)
                        links[i][j] += 2;
                    if(links[i][j]>0)
                    {
                        if(grid[i-2][j+1]==2 && !is_blocked(i,j, i-2,j+1)) join_recursive(i-2,j+1,2);
                        if(grid[i+2][j+1]==2 && !is_blocked(i,j, i+2,j+1)) join_recursive(i+2,j+1,2);
                        if(grid[i+1][j+2]==2 && !is_blocked(i,j, i+1,j+2)) join_recursive(i+1,j+2,2);
                        if(grid[i-1][j+2]==2 && !is_blocked(i,j, i-1,j+2)) join_recursive(i-1,j+2,2);
                        if(grid[i+2][j-1]==2 && !is_blocked(i,j, i+2,j-1)) join_recursive(i+2,j-1,2);
                        if(grid[i-2][j-1]==2 && !is_blocked(i,j, i-2,j-1)) join_recursive(i-2,j-1,2);
                    }
                }
            }
        }
        else if (j == 23 || j == 22)
        {
            links[i][j] += 2;
            if(j==23)
            {
                if(i==1)
                {
                    if(get_val_checked(i,j, i - 2, j + 1) == 20 || get_val_checked(i,j, i - 1, j + 2) == 20)
                        links[i][j] += 20;
                    if(links[i][j]>0)
                    {
                        if(grid[i-2][j-1]==2 && !is_blocked(i,j, i-2,j-1)) join_recursive(i-2,j-1,2);
                        if(grid[i-1][j-2]==2 && !is_blocked(i,j, i-1,j-2)) join_recursive(i-1,j-2,2);
                    }
                }
                else{
                    if(get_val_checked(i,j, i - 2, j + 1) == 20 || get_val_checked(i,j, i + 2, j + 1) == 20 || get_val_checked(i,j, i + 1, j + 2) == 20 || get_val_checked(i,j, i - 1, j + 2) == 20)
                        links[i][j] += 20;
                    if(links[i][j]>0)
                    {
                        if(grid[i-2][j-1]==2 && !is_blocked(i,j, i-2,j-1)) join_recursive(i-2,j-1,2);
                        if(grid[i+2][j-1]==2 && !is_blocked(i,j, i+2,j-1)) join_recursive(i+2,j-1,2);
                        if(grid[i+1][j-2]==2 && !is_blocked(i,j, i+1,j-2)) join_recursive(i+1,j-2,2);
                        if(grid[i-1][j-2]==2 && !is_blocked(i,j, i-1,j-2)) join_recursive(i-1,j-2,2);
                    }
                }
            }
            if(j==22)
            {
                if(i==1){
                    if(get_val_checked(i,j, i - 2, j + 1) == 2 || get_val_checked(i,j, i - 1, j + 2) == 2 || get_val_checked(i,j, i-2, j-1)==2 )
                        links[i][j] += 2;
                    if(links[i][j]>0)
                    {
                        if(grid[i-2][j+1]==2 && !is_blocked(i,j, i-2,j+1)) join_recursive(i-2,j+1,2);
                        if(grid[i-1][j-2]==2 && !is_blocked(i,j, i-1,j-2)) join_recursive(i-1,j-2,2); // note: fixed your type i-2 to i-1
                        if(grid[i-2][j-1]==2 && !is_blocked(i,j, i-2,j-1)) join_recursive(i-2,j-1,2);
                    } 
                }
                else{
                    if(get_val_checked(i,j, i - 2, j + 1) == 2 || get_val_checked(i,j, i + 2, j + 1) == 2 || get_val_checked(i,j, i + 1, j + 2) == 2|| get_val_checked(i,j, i - 1, j + 2) == 2 || get_val_checked(i,j, i-2, j-1)==2 ||get_val_checked(i,j, i+2, j-1)==2)
                        links[i][j] += 2;
                    if(links[i][j]>0)
                    {
                        if(grid[i-2][j+1]==2 && !is_blocked(i,j, i-2,j+1)) join_recursive(i-2,j+1,2);
                        if(grid[i+2][j+1]==2 && !is_blocked(i,j, i+2,j+1)) join_recursive(i+2,j+1,2);
                        if(grid[i+1][j-2]==2 && !is_blocked(i,j, i+1,j-2)) join_recursive(i+1,j-2,2); // note: fixed typo here too
                        if(grid[i-1][j-2]==2 && !is_blocked(i,j, i-1,j-2)) join_recursive(i-1,j-2,2);
                        if(grid[i+2][j-1]==2 && !is_blocked(i,j, i+2,j-1)) join_recursive(i+2,j-1,2);
                        if(grid[i-2][j-1]==2 && !is_blocked(i,j, i-2,j-1)) join_recursive(i-2,j-1,2);
                    }
                }
            }
        }
        else
        {
            if (get_val_checked(i,j, i - 2, j - 1) == 20 || get_val_checked(i,j, i - 2, j + 1) == 20 || get_val_checked(i,j, i + 2, j - 1) == 20 || get_val_checked(i,j, i + 2, j + 1) == 20 || get_val_checked(i,j, i - 1, j - 2) == 20 || get_val_checked(i,j, i - 1, j + 2) == 20 || get_val_checked(i,j, i + 1, j - 2) == 20 || get_val_checked(i,j, i + 1, j + 2) == 20)
            {
                links[i][j] += 20;
            }
            if (get_val_checked(i,j, i - 2, j - 1) == 2 || get_val_checked(i,j, i - 2, j + 1) == 2 || get_val_checked(i,j, i + 2, j - 1) == 2 || get_val_checked(i,j, i + 2, j + 1) == 2 || get_val_checked(i,j, i - 1, j - 2) == 2 || get_val_checked(i,j, i - 1, j + 2) == 2 || get_val_checked(i,j, i + 1, j - 2) == 2 || get_val_checked(i,j, i + 1, j + 2) == 2)
            {
                links[i][j] += 2;
            }
            if(links[i][j]>0)
            {
                if(grid[i-2][j-1]==2 && !is_blocked(i,j, i-2,j-1)) join_recursive(i-2,j-1,2);
                if(grid[i-2][j+1]==2 && !is_blocked(i,j, i-2,j+1)) join_recursive(i-2,j+1,2);
                if(grid[i-1][j-2]==2 && !is_blocked(i,j, i-1,j-2)) join_recursive(i-1,j-2,2);
                if(grid[i-1][j+2]==2 && !is_blocked(i,j, i-1,j+2)) join_recursive(i-1,j+2,2);
                if(grid[i+1][j-2]==2 && !is_blocked(i,j, i+1,j-2)) join_recursive(i+1,j-2,2);
                if(grid[i+1][j+2]==2 && !is_blocked(i,j, i+1,j+2)) join_recursive(i+1,j+2,2);
                if(grid[i+2][j-1]==2 && !is_blocked(i,j, i+2,j-1)) join_recursive(i+2,j-1,2);
                if(grid[i+2][j+1]==2 && !is_blocked(i,j, i+2,j+1)) join_recursive(i+2,j+1,2);
            }
        }
        
        if (links[i][j] == 22)
        {
            printf("RED WINS");
            return 1;
        }
        else return 0;
    }
}

int join(int i, int j, int c)
{
    memset(visited, 0, sizeof(visited));
    return join_recursive(i, j, c);
}