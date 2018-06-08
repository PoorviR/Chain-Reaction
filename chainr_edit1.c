#include <stdio.h>
#include <math.h>
const int u=11;
const int v=8;
void display_board( int arr[u][v]);
void clear_padding( int arr[u][v]);
void burst( int arr[u][v],int x,int y, int player_num);// check critical mass burst then clear padding then recurse
int check_winner( int arr[u][v]);  // winning condition all cells are either 0 or of one player
int main()
{
	int arr[u][v];
	for(int i=0;i<u;i++)
	{
		for(int j=0;j<v;j++)
		{
			arr[i][j]=0;
		}
	}
	int player_num=1;
	int ctr=0;int win=0;
	do
	{
		int x,y;
		printf ("Enter the coordinates to play:\n");
		scanf("%d",&x);
		scanf("%d",&y);  /* x and y given in standard array indices   so add 1 to it.. padding */
		if ( (player_num*arr[x+1][y+1] <0) || (x <0 || y <0) )/* checks for illegal moves */
		{
			printf ("Illegal move.Play again.\n");
			continue;
		}
		ctr++;
		arr[x+1][y+1]+= player_num;   //adding a mass
		x=x+1;
		y=y+1;
		burst(arr,x,y,player_num);		
		display_board(arr);
		//printf ("ctr = %d, player num = %d\n", ctr, player_num);
		int p=check_winner(arr);
		player_num = player_num * -1; // changing player
		if(p!=0 && ctr>2)
		{
			win=1;  // win becomes 1 when the current player wins and its not the first turn.
		}
	}
	while (win==0);
	printf("Player %d is the winner.\n", (player_num* -1));  //winning player
}

void display_board( int arr[u][v])
{
	for(int i=1;i<u-1;i++)
	{
		for(int j=1;j<v-1;j++)
		{
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}

void clear_padding( int arr[u][v])
{
	for(int i=0;i<u;i++)
	{
		arr[i][0]=0;
		arr[i][v-1]=0;
	}
	for(int i=0;i<v;i++)
	{
		arr[0][i]=0;
		arr[u-1][i]=0;
	}
}

int check_winner( int arr[u][v])
{
	int i,j,count1=0,count2=0,count3=0;
	for (i=0 ; i<u ; i++)
	{
		for (j=0 ; j<v ; j++)
		{
			if (arr[i][j] > 0 )
			{
				count1++;
			}
			else if (arr[i][j] < 0 )
			{
				count2++;
			}
			else
			{
				count3++;
			}
		}
	}
	if ( count1 + count3 == u*v || count2 + count3 == u*v)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void burst(int arr[u][v],int x,int y, int player_num)
{
	int i,j;
	if ((x==1 && y==1) || (x==1 && y==6) || (x==9 && y==1) || (x==9 && y==6))
	{
		if (abs(arr[x][y])>=2)
		{
			arr[x+1][y] = player_num*(abs(arr[x+1][y]) + 1);
			arr[x-1][y] = player_num*(abs(arr[x-1][y]) + 1);
			arr[x][y+1] = player_num*(abs(arr[x][y+1]) + 1);
			arr[x][y-1] = player_num*(abs(arr[x][y-1]) + 1);
			arr[x][y] = player_num*(abs(arr[x][y])-2);
			clear_padding(arr);
			burst(arr,(x+1),y, player_num);
			burst(arr,(x-1),y, player_num);
			burst(arr,x,y+1, player_num);
			burst(arr,x,y-1, player_num);
			
		}
	}
	else if (((x == 9 || x == 1) && ( y>1 && y<6)) || ((y == 1 || y==6) && ( x > 1 && x<9)))
	{
		if (abs(arr[x][y]) >=3)
		{
			arr[x+1][y] = player_num*(abs(arr[x+1][y]) + 1);
			arr[x-1][y] = player_num*(abs(arr[x-1][y]) + 1);
			arr[x][y+1] = player_num*(abs(arr[x][y+1]) + 1);
			arr[x][y-1] = player_num*(abs(arr[x][y-1]) + 1);
			arr[x][y] = player_num*(abs(arr[x][y])-3);
			clear_padding(arr);
			burst(arr,(x+1),y, player_num);
			burst(arr,(x-1),y, player_num);
			burst(arr,x,y+1, player_num);
			burst(arr,x,y-1, player_num);
			
		}
	}
	else
	{
		if (abs(arr[x][y]) >=4)
		{
			arr[x+1][y] = player_num*(abs(arr[x+1][y]) + 1);
			arr[x-1][y] = player_num*(abs(arr[x-1][y]) + 1);
			arr[x][y+1] = player_num*(abs(arr[x][y+1]) + 1);
			arr[x][y-1] = player_num*(abs(arr[x][y-1]) + 1);
			arr[x][y] = player_num*(abs(arr[x][y])-4);
			clear_padding(arr);
			burst(arr,(x+1),y, player_num);
			burst(arr,(x-1),y, player_num);
			burst(arr,x,y+1, player_num);
			burst(arr,x,y-1, player_num);
			
		}
	}
}	
	
	

