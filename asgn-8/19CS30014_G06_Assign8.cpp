/*
NAME-DEBANJAN SAHA
ROLL-19CS30014
*/
#include<iostream>
using namespace std;

typedef struct coordinate
{
	int x,y;
}point;

int minimum(int a,int b)
{
	if(a<b)
		return a ;
	return b;
}

bool isSafe(int i,int j,int n)
{
	return (i>=0 && j>=0 && i<n && j<n);
}

int max(int a,int b)
{
	if(a>b)
		return a;
	return b;
}

int dx[]={0,0,1,-1};
int dy[]={1,-1,0,0};

void dfs(int max_allowed_weight,int **grid,point **parent,int **vis,int x,int y,int n)
{
	if(vis[x][y]==1)
		return;
	if(grid[x][y]>max_allowed_weight)
		return;

	vis[x][y]=1;

	for(int i=0;i<4;i++)
	{
		int nx=x+dx[i];
		int ny=y+dy[i];

		if(isSafe(nx,ny,n))
		{
			if(vis[nx][ny]==1)
				continue;

			if(grid[nx][ny]>max_allowed_weight)
				continue;

			point par;
			par.x=x,par.y=y;
			parent[nx][ny]=par;
			dfs(max_allowed_weight,grid,parent,vis,nx,ny,n);
		}
	}
}

int printpath(int x,int y,point **parent,int *count)
{
	if(x==-1 && y==-1)
	{
		return *count;
	}

	point par=parent[x][y];
	*count=printpath(par.x,par.y,parent,count);
	cout<<"("<<x<<","<<y<<"),";
	
	return *count+1;
}

int leastTimeDijkstra(int **grid,int n,point src,point dest)
{
	bool vis[n][n];
	int INF= 1e7;
	int time[n][n];
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			vis[i][j]=0;
			time[i][j]=INF;	
		}
	}

	vis[src.x][src.y]=1;
	time[src.x][src.y]=0;
	for(int i=0;i<4;i++)
	{
		int nx=src.x+dx[i];
		int ny=src.y+dy[i];
		if(isSafe(nx,ny,n))
		{
			time[nx][ny]=max(grid[nx][ny],grid[src.x][src.y]);
		}
	}

	for(int i=0;i<n*(n-1);i++)
	{
		int mn=INF;
		point v;
		for(int j=0;j<n;j++)
		{
			for(int k=0;k<n;k++)
			{
				if(vis[j][k]==false && time[j][k]<mn)
				{
					mn=time[j][k];
					v.x=j;
					v.y=k;
				}
			}
		}

		vis[v.x][v.y]=true;

		for(int i=0;i<4;i++)
		{
			int nx=v.x+dx[i];
			int ny=v.y+dy[i];
			if(isSafe(nx,ny,n))
			{
				int t= max(time[v.x][v.y],grid[nx][ny]);
				t=minimum(t,time[nx][ny]);
				time[nx][ny]=t;
			}
		}
	}

	return time[dest.x][dest.y];
}

int main()
{
	int n;
	cin>>n;
	int **grid,**vis,mx=0;
	point **parent;

	grid=(int **)malloc(n*sizeof(int *));
	parent=(point **)malloc(n*sizeof(point *));
	vis=(int **)malloc(n*sizeof(int *));

	for(int i=0;i<n;i++)
	{
		parent[i]=(point *)malloc(n*sizeof(point));
		grid[i]=(int *)malloc(n*sizeof(int*));
		vis[i]=(int *)malloc(n*sizeof(int));

		for(int j=0;j<n;j++)
		{
			cin>>grid[i][j];
			mx=max(mx,grid[i][j]); //finding highest value of grid[i][j] to do binary search 
			parent[i][j]={-1,-1};
		}
	}

	point src,dest; 
	cin>>src.x>>src.y>>dest.x>>dest.y; //Input Source+ Destination

	int lo=0,hi=mx+1;

	while(lo<hi)
	{
		int mid=(lo+hi)/2;

		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				vis[i][j]=0;
			}
		}

		dfs(mid,grid,parent,vis,src.x,src.y,n);

		if(vis[dest.x][dest.y]==1) // if I can reach destination ,try lesser weights
		{
			hi=mid;
		}
		else
			lo=mid+1;
	}

	if(src.x==dest.x && src.y==dest.y)
		lo=0;

	cout<<"The Minimum Time Taken is : "<<lo<<endl<<endl;

	point parent_dest=parent[dest.x][dest.y];

	printf("The Path to reach from (%d,%d) to (%d,%d) is: \n",src.x,src.y,dest.x,dest.y);
	int cell_count = 0;

	cell_count=1+ printpath(parent_dest.x,parent_dest.y,parent,&cell_count); //added one because started from parent of destination

	cout<<"("<<dest.x<<","<<dest.y<<")"<<endl<<endl;

	cout<<"The Number of Blocks traversed are : "<<cell_count<<endl;


	cout<<"-----------------------"<<endl;
	cout<<"BONUS PART"<<endl;
	int t0=	leastTimeDijkstra(grid,n,src,dest);
	cout<<"The least time found using Dijkstra is: "<<t0<<endl;

	return 0;
}