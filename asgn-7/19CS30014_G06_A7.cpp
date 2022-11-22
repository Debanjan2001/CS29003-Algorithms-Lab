/*
NAME-DEBANJAN SAHA
ROLL-19CS30014
*/
#include<iostream>
#include<string.h> 
#include<stdlib.h>
using namespace std;

typedef struct _node
{
	int rank;
	struct _node *parent;
}node;

node ***makeset(node ***C,int m,int n)
{
	C=(node ***)malloc(m*sizeof(node **));

	for(int i=0;i<m;i++)
	{
		C[i] = (node **)malloc(n*sizeof(node *));
		for(int j=0;j<n;j++)
		{	
			node *curr= (node *)malloc(sizeof(node));
			curr->parent=curr;
			curr->rank=0;
			C[i][j]=curr;
		}
	}

	return C;	
}

node *findset(node *x)
{
	node *root=x, *temp=x;

	while(root->parent!=root)
		root=root->parent;

	while(temp->parent!=temp)
	{
		node *z=temp;
		temp=temp->parent;
		z->parent=root;
	}

	return root;
}

void mergeset(node *a,node *b)
{
	node *x=findset(a);
	node *y=findset(b);

	if(x==y)
		return;

	if(x->rank==y->rank)
	{
		y->parent=x;
		x->rank = x->rank+1;
	}
	else
	{
		if(x->rank>y->rank)
		{
			y->parent=x;
		}
		else
		{
			x->parent=y;
		}
	}
}

void findtreasure(node ***C,int **H,int **V,int m,int n)
{
	int wall_count=0;
	while(wall_count<m*n-1)
	{
		int x=rand()%(2*m-1); //odd means horizontal wall and even means vertical
		int i=x/2;
		if(x%2==0)
		{
			if(n==1) //dont wanna divide by (n-1=0)
				continue;
			int j=rand()%(n-1);
			if(V[i][j]==1 && findset(C[i][j])!=findset(C[i][j+1]))
			{
				mergeset(C[i][j],C[i][j+1]);
				V[i][j]=0;
				wall_count++;
			}
		}
		else
		{
			int j=rand()%n;
			if(i>=m-1)
				continue;
			if(H[i][j]==1 && i+1<m && findset(C[i][j])!=findset(C[i+1][j]))
			{
				mergeset(C[i][j],C[i+1][j]);
				H[i][j]=0;
				wall_count++;	

			}
		}

	}

	
	if(findset(C[0][0])==findset(C[m-1][n-1]))
		cout<<"The final chamber can be reached from the start chamber."<<endl;
	else
		cout<<"The final chamber can not be reached from the start chamber."<<endl;
}

void printgrid(int **H,int **V,int m,int n)
{
	for(int i=0;i<=n;i++)
	{
		if(i==0)
			cout<<"+   ";
		else if(i==n)
			cout<<"+"<<endl;
		else 
			cout<<"+---";
	}	

	for(int i=0;i<2*m;i++)
	{
		for(int j=0;j<=n;j++)
		{
			if(i%2==0)
			{
				int k=i/2;

				if(j==0)
					cout<<"|   ";
				else if(k==m-1 && j==n)
					cout<<endl;
				else if(j==n)
					cout<<"|"<<endl;
				else
				{
					if(V[k][j-1]==1)
						cout<<"|   ";
					else
						cout<<"    ";
				}
			}

			else 
			{
				int k =i/2;

				if(k<m-1 )
				{
					if( j<n && H[k][j]==1)
						cout<<"+---";
					else if(j<n && H[k][j]==0)
						cout<<"+   ";
					else if(j==n)
						cout<<"+"<<endl;
				}
				else
				{
					if(j!=n)
						cout<<"+---";
					else
						cout<<"+"<<endl;
				}
			}
		}
	}
}


int main(int argc,char **argv)
{
	srand((unsigned  int)time(NULL));
	int m,n;

	if(argc>=3)
	{
		m = atoi(argv[1]);  //Took first argument as m
		n = atoi(argv[2]);  //Took first argument as n
	}
	else 
	{
		m=10;
		n=10;
	}

	//---------PART1--------

	node ***C;
	C = makeset(C,m,n);

	int **H = (int **)malloc((m-1)*sizeof(int *));
	for(int i=0;i<m-1;i++)
	{
		H[i]=(int *)malloc(n*sizeof(int));
		for(int j=0;j<n;j++)
		{
			H[i][j]=1; //there is a wall denoted by 1
		}
	}

	int **V =(int **)malloc(m*sizeof(int *));
	for(int i=0;i<m;i++)
	{
		V[i]=(int *)malloc((n-1)*sizeof(int));
		for(int j=0;j<n-1;j++)
		{
			V[i][j]=1; //there is a wall denoted by 1
		}
	}
 	
 	cout<<"Initial Grid :"<<endl;
	printgrid(H,V,m,n);
	cout<<endl;


	//--------PART2-----------

	findtreasure(C,H,V,m,n);
		

	// ----PART3--------------
	cout<<endl<<"Final Grid :"<<endl;
	printgrid(H,V,m,n);
	cout<<endl;


	return 0;
}