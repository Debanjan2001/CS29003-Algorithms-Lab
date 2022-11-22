#include<iostream>
using namespace std;

typedef struct 
{
	int x,y;
} point ;

int INT_MAX=1e9;

void printgrid(char arr[][200],int a,int b)
{
	for(int i=0;i<a;i++)
	{
		for(int j=0;j<b;j++)
		{
			cout<<arr[i][j];
		}
		cout<<endl;
	}
}

typedef struct 
{
	point *Arr ;
	int queue_size;
	int front,rear;
} QUEUE ;

void init(QUEUE *q, int size)
{
	//allocates space for queue
	q->Arr=(point *)malloc(size*sizeof(point));
	q->queue_size=0;
	q->front=0;
	q->rear=-1;
}

int isempty(QUEUE q)//returns 1 if the queue is empty, else 0
{
	if(q.queue_size==0)
		return 1;

	return 0;
}

void enqueue(QUEUE *q, point p)
{
	q->rear++;
	q->Arr[q->rear]=p;
	q->queue_size++;
}

point dequeue(QUEUE *q)
{
	point curr=q->Arr[q->front];
	(q->front)=(q->front)+1;
	q->queue_size--;
	return curr;
}

int safe(char arr[][200],int x,int y,int a,int b)
{
	if(x<a && y<b && x>=0 && y>=0 && arr[x][y]=='*')
		return 1;
	return 0;
}

int row[4]={-1,+1,0,0};
int col[4]={0,0,+1,-1};

int strategy1(char arr[][200],point start,point dest,int a,int b)
{
	QUEUE q;
	init(&q,a*b+10);
	bool vis[a][b];
	bool flag=0;

	for(int i=0;i<a;i++)
	{
		for(int j=0;j<b;j++)
		{
			vis[i][j]=false;
		}
	}

	vis[start.x][start.y]=true;
	enqueue(&q,start);
	while(isempty(q)!=1)
	{
		point curr=dequeue(&q);

		vis[curr.x][curr.y]=true;
		if(curr.x==dest.x && curr.y==dest.y)
		{
			flag=1;
			break;
		}


		for(int k=0;k<4;k++)
		{
			int x=curr.x+row[k],y=curr.y+col[k];
			if(safe(arr,x,y,a,b) && !vis[x][y])
			{
				vis[x][y]=1;
				point temp;
				temp.x=x;
				temp.y=y;
				enqueue(&q,temp);
			}
		}


	}

	if(flag)
	{
		cout<<"Path Exists."<<endl;
		return 1;
	}
	else
	{
		cout<<"No path exists."<<endl;
		return 0;
	}

}

typedef struct STACK
{
	point head;
	struct STACK *next;
} STACK;

void init_stack(STACK **s) 
{
	*s=(STACK *)malloc(sizeof(STACK));
	//initializes the head and next pointer
	point inv;
	inv.x=INT_MAX;
	inv.y=INT_MAX;
	(*s)->head=inv;
	(*s)->next=NULL;
}


int isempty_stack(STACK *s)
{
	if(s->next==NULL)
		return 1;
	return 0;
	//returns 1 if the stack is empty, 0 otherwise

}
void push(STACK **s, point p)
{
	STACK *temp=new STACK;
	temp->head=p;
	temp->next=*s;
	*s=temp;
}

point pop(STACK **s)
{
	point curr=(*s)->head;
	STACK *temp=*s;
	*s=(*s)->next;
	free(temp);
	return curr;
}

void strategy2(char arr[][200],point start,point dest,int a,int b)
{
	STACK *s,*PRINTER;
	init_stack(&s);
	init_stack(&PRINTER);

	bool vis[a][b],is_found=0;

	for(int i=0;i<a;i++)
	{
		for(int j=0;j<b;j++)
		{
			vis[i][j]=false;
		}
	}

	push(&s,start);
	while(isempty_stack(s)!=1)
	{
		point curr=s->head;
		vis[curr.x][curr.y]=1;
		bool flag=0;
		for(int k=0;k<4;k++)
		{
			int x=curr.x+row[k],y=curr.y+col[k];
			if(safe(arr,x,y,a,b) && !vis[x][y])
			{
				vis[x][y]=1;
				point temp;
				temp.x=x,temp.y=y;
				push(&s,temp);
				flag=1;
				if(x==dest.x && y==dest.y)
					is_found=1;
				break;
			}
		}

		if(is_found)
		{
			while(!isempty_stack(s))
			{
				point p=pop(&s);
				push(&PRINTER,p);
			}
		}

		if(!flag)
		{
			if(!isempty_stack(s))
				pop(&s);
		}
	}
	
	while(!isempty_stack(PRINTER))
	{
		point p=pop(&PRINTER);
		cout<<"("<<p.x<<","<<p.y<<")";
		if(PRINTER->next==NULL)
			cout<<endl;
		else
			cout<<",";

	}


}


int main()
{
	int a,b,n;
	cin>>a>>b>>n;
	char arr[200][200];
	for(int i=0;i<a;i++)
	{
		for(int j=0;j<b;j++)
		{
			arr[i][j]='*';
		}
	}

	point unstable[n],start,dest;
	for(int i=0;i<n;i++)
	{
		cin>>unstable[i].x;
	}

	for(int i=0;i<n;i++)
	{
		cin>>unstable[i].y;
		arr[unstable[i].x][unstable[i].y]='-';
	}

	cin>>start.x>>start.y>>dest.x>>dest.y;

	cout<<"Grid of Stones is:"<<endl;

	printgrid(arr,a,b);

	int path_exists=strategy1(arr,start,dest,a,b);

	if(path_exists)
	{
		strategy2(arr,start,dest,a,b);
	}

	return 0;
}