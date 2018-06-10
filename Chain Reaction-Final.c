//including standard libraries
#include <stdio.h>
#include <math.h>

//varaibles setting size of board declared globally
const int u=11;
const int v=8;

//function to display the current board
void display_board( int arr[u][v]);

//function to clear the padding cells (outermost cells that is not a part of the game)
void clear_padding( int arr[u][v]);

//function that checks the coordinate for its critical mass
void burstcheck( int arr[u][v],int x,int y, int player_num);

//bursts the cell given its coordinate and checks if suurounding cells are burstable
void burstin( int arr[u][v],int x,int y, int player_num, int ortho);

//checks if any player has won..condition is that all must be of one player
int check_winner( int arr[u][v]);
int check_winner2( int arr[u][v]);

//main program
int main()
{
	//initializing the array to all 0s
	int arr[u][v];
	for(int i=0;i<u;i++)
	{
		for(int j=0;j<v;j++)
		{
			arr[i][j]=0;
		}
	}

	//player num is current player... ctr is the turn number of the game.. to make sure first move doesnt count as win
	int player_num=1;
	int ctr=0;int win=0;

	//setting the gameplay loop
	do
	{
		int x,y;
		printf ("Enter the coordinates to play:\n");
		scanf("%d",&x);
		scanf("%d",&y);
		/* x and y given in standard array indices   so add 1 to it.. padding */
		if ( (player_num*arr[x+1][y+1] <0) || (x <0 || y <0) )/* checks for illegal moves */
		{
			printf ("Illegal move.Play again.\n");
			continue;
		}
		ctr++;
		//adding a mass
		arr[x+1][y+1]+= player_num;
		x=x+1;
		y=y+1;
		burstcheck(arr,x,y,player_num);
		display_board(arr);
		//printf ("ctr = %d, player num = %d\n", ctr, player_num);
		//checking if the game has been won
		int p=check_winner2(arr);

		// changing player number
		player_num = player_num * -1;
		if(p!=0 && ctr>2)
		{
			win=1;  // win becomes 1 when the current player(before changing sign in the line before if) wins and its not the first turn.
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
		return 1;
	}
	else
	{
		return 0;
	}
}

int check_winner2(int arr[u][v])
{
	int a=0;
	for(int i=0;i<u;i++)
	{
		for(int j=0;j<v;j++)
		{
			if(a*arr[i][j]<0)
			{
				return 0;
			}
			else if(a==0 && arr[i][j]!=0)
			{
				a=arr[i][j];
			}
			else if(a*arr[i][j]>=0)
			{
				continue;
			}
		}
	}
	return 1;
}

void burstcheck(int arr[u][v],int x,int y, int player_num)
{
	int i,j;
	if ((x==1 && y==1) || (x==1 && y==6) || (x==9 && y==1) || (x==9 && y==6))
	{
		if (abs(arr[x][y])>=2)
		{
			burstin(arr,x,y,player_num,2);
		}
	}
	else if (((x == 9 || x == 1) && ( y>1 && y<6)) || ((y == 1 || y==6) && ( x > 1 && x<9)))
	{
		if (abs(arr[x][y]) >=3)
		{
			burstin(arr,x,y,player_num,3);
		}
	}
	else
	{
		if (abs(arr[x][y]) >=4)
		{
			burstin(arr,x,y,player_num,4);
		}
	}
}

void burstin(int arr[u][v],int x,int y, int player_num, int ortho)
{
	arr[x+1][y] = player_num*(abs(arr[x+1][y]) + 1);
	arr[x-1][y] = player_num*(abs(arr[x-1][y]) + 1);
	arr[x][y+1] = player_num*(abs(arr[x][y+1]) + 1);
	arr[x][y-1] = player_num*(abs(arr[x][y-1]) + 1);
	arr[x][y] = player_num*(abs(arr[x][y])-ortho);
	clear_padding(arr);
	if(!check_winner2(arr))// it doesnt error in first move also because multiple bursts are not possible in the first move
	{
		burstcheck(arr, x+1, y, player_num);
		burstcheck(arr, x-1, y, player_num);
		burstcheck(arr, x, y+1, player_num);
		burstcheck(arr, x, y-1, player_num);
	}
}



