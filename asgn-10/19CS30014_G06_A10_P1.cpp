/*
NAME-DEBANJAN SAHA
ROLL-19CS30014
*/
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

typedef struct node
{
	int val;
	struct node *next;
} node;

typedef struct _hashing 
{	
	int key;
	struct _hashing *next;
	struct node *head;

} hashmap;

int hash_val(int k,int size)
{
	return (k+size)%size;
}


void insert_(hashmap **h,int i,int key,int val)
{

	hashmap *temp=h[i]->next;
	while(temp!=NULL)
	{
		if(temp->key==key)
			break;
		temp=temp->next;
	}

	if(temp!=NULL)
	{
		node *curr=temp->head;
		while(curr!=NULL)
		{
			if(curr->val==val)
				return;
			curr=curr->next;
		}

		node *now=new node;
		now->val=val;
		now->next=temp->head->next;
		temp->head=now;

	}
	else
	{
		hashmap *temp=h[i];
		hashmap *curr=(hashmap *)malloc(sizeof(hashmap));
		curr->next=temp->next;
		temp->next=curr;
		curr->key=key;
		curr->head=(node *)malloc(sizeof(node));
		curr->head->val=val;
		curr->head->next=NULL;
	}


}

void delete_by_num(hashmap **h,int pnum,int size,int y)
{
	int index=hash_val(pnum,size);
	hashmap *temp=h[index];
	while(temp!=NULL && temp->next!=NULL)
	{
		if(temp->next->key==pnum)
		{
			hashmap *curr=temp->next;
			temp->next=curr->next;
			free(curr);
			break;
		}
		temp=temp->next;
	}
}

void delete_all(hashmap **p,hashmap **c,int key,int size)
{
	int index=hash_val(key,size);

	hashmap *temp=c[index]->next;
	hashmap *prev=c[index];

	while(temp!=NULL)
	{
		if(temp->key==key)
		{
			node *head=temp->head;
			while(head!=NULL)
			{
				int val=head->val;
				delete_by_num(p,val,size,key);
				head=head->next;
			}
			prev->next=temp->next;
			free(temp);
			break;
		}
		prev=temp;
		temp=temp->next;
	}

	
}


void printtable(hashmap **h,int size,char ch,ofstream &fout)
{
	for(int i=0;i<size;i++)
	{	
		hashmap *curr=h[i]->next;
		if(curr==NULL)
			fout<<ch<<" "<<i<<" "<<-1<<" "<<-1<<endl;
		else
		{
			while(curr!=NULL)
			{
				fout<<ch<<" "<<i<<" ";
				node *head=curr->head;
				fout<<curr->key<<" ";
				while(head!=NULL)
				{
					fout<<head->val<<" ";
					head=head->next;
				}
				fout<<endl;

				curr=curr->next;
			}
		}
	}


}


int main()
{
	ofstream fout;
	ifstream fin;
	fin.open("input.txt");
	fout.open("output.txt");

	int size,t;
	fin>>size>>t;

	hashmap **p,**c;
	p=(hashmap **)malloc(size*sizeof(hashmap *));
	c=(hashmap **)malloc(size*sizeof(hashmap *));

	for(int i=0;i<size;i++)
	{
		p[i]=(hashmap *)malloc(sizeof(hashmap));
		p[i]->next=NULL;
		p[i]->head=NULL;

		c[i]=(hashmap *)malloc(sizeof(hashmap));
		c[i]->next=NULL;
		c[i]->head=NULL;

	}


	while(t--)
	{
		char sym;
		fin>>sym;
		if(sym=='+')
		{
			int y,pnum;
			fin>>y>>pnum;

			int index1=hash_val(pnum,size);
			insert_(p,index1,pnum,y);

			int index2=hash_val(y,size);
			insert_(c,index2,y,pnum);
		}
		else
		{
			int y;
			fin>>y;
			delete_all(p,c,y,size);
		}

	}

	printtable(p,size,'p',fout);
	printtable(c,size,'c',fout);


	fin.close();
	fout.close();


	return 0;
}