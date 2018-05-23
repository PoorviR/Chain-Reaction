#include <stdio.h>
const int u=11;
const int v=8;
void display_board( int arr[u][v]);
void clear_padding( int arr[u][v]);
void burst( int arr[u][v], int player_num);// check critical mass burst then clear padding then recurse
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
		scanf("%d",&x);
		scanf("%d",&y); /* x and y given in standard array indices   so add 1 to it.. padding */
		ctr++;
		arr[x][y]+= player_num;//adding a mass
		burst(arr,player_num);
		display_board(arr);
		int p=check_winner(arr);
		if(p!=0 && ctr>2)
		{
			win=1;  // win becomes 1 when the current player wins and its not the first turn.
		}
	}while(win!=0)
	printf("%d", player_num);  //winning player
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
	
	return(0);
}

void burst(int arr[u][v], int player_num)
{
}
	
	
	
	
	
		 
		
