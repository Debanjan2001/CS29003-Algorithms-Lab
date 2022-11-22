//19CS30014
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int data;
	struct node *add;
} list;

list *head,*tail;

int a[10000];
int n;
void newlist(list *head,int i,list *prev)
{
	head->data=a[i];
	head->add=(list *)malloc(sizeof(list));
	head->add=(list *)((unsigned long long)prev^(unsigned long long)(head->add));
	if(i==n-1)
	{
		tail=head;
		tail->add=(list *)((unsigned long long)prev^(unsigned long long)(NULL));
		return;
	}

	list *next=(list *)((unsigned long long)prev^(unsigned long long)(head->add));
	newlist(next,i+1,head);
}

void traverse_from_front_to_end(list *now)
{
	int cnt=0;
	list *prev=NULL;
	while(now!=NULL)
	{
		list *temp=now;
		cnt++;
		if(cnt<n)
			printf("%d, ",now->data );
		else
			printf("%d\n\n",now->data );
		now=(list *)((unsigned long long)(now->add)^(unsigned long long)(prev));
		prev=temp;
	}

}

void traverse_from_end_to_front(list *now)
{
	int cnt=0;
	list *prev=NULL;
	while(now!=NULL)
	{
		list *temp=now;
		cnt++;
		if(cnt<n)
			printf("%d, ",now->data );
		else
			printf("%d\n\n",now->data );

		now=(list *)((unsigned long long)(prev)^(unsigned long long)(now->add));
		prev=temp;
	}
}

void reverse(struct node **head, struct node **tail)
{
	list *temp=*head;
	*head=*tail;
	*tail=temp;
}

void alternate(struct node **head, struct node **tail)
{
	list *pre1=NULL,*pre2=NULL,*right=*tail,*left=*head;
	int x=n;
	list *next1,*next2;
	x-=1;
	while(x>0)
	{
		next1=(list *)((unsigned long long)(left->add)^(unsigned long long)(pre1));
		next2=(list *)((unsigned long long)(right->add)^(unsigned long long)(pre2));

		left->add=right;
		pre1=left;
		left=next1;
		x--;
		if(x==0)
		{
			*tail=right;
			break;
		}
		
		right->add=left;
		pre2=right;
		right=next2;
		x--;

		if(x==0)
		{
			*tail=left;
			break;

		}
	}


}


int main()
{
  printf("Enter number of integers (n):");
  scanf("%d",&n);
  printf("Enter %d integers(with only one space): ",n);
  for(int i=0;i<n;i++)
  	scanf("%d",&a[i]);

  head=(list *)malloc(sizeof(list));

  newlist(head,0,NULL);
  printf("Doubly linked list traversed from front to end:\n");
  traverse_from_front_to_end(head);
  printf("Doubly linked list traversed from end to front:\n");
  traverse_from_end_to_front(tail);

  reverse(&head,&tail);

  printf("Reversed Doubly linked list traversed from front to end:\n");
  traverse_from_front_to_end(head);

  printf("Alternated Doubly linked list traversed from front to end:\n");
  alternate(&head,&tail);
  printf("I could not debug segmentation fault which is causing due to alternate function.\n");
  traverse_from_front_to_end(head);



  return 0;
}


