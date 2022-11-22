//19CS30014
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>
using namespace std;

typedef struct node
{
	char *symbol;
	int freq;
	struct node *left;
	struct node *right; 
	struct node *next;
} node;

const int INF=1e8;


node* push(node *curr,char c,int cnt)
{
	curr->next=new node;
	curr=curr->next;
	curr->left=NULL;
	curr->right=NULL;
	curr->symbol=(char *)malloc(5*sizeof(char));	
	curr->symbol[0]=c;
	curr->freq=cnt;
	return curr;
}

void traverse(node *curr)
{
	if(curr==NULL)
	{
		cout<<endl;
		return;
	}
	else
	{
		cout<<curr->symbol<<" "<<curr->freq<<" ,";
		traverse(curr->next);
	}

}

void conv(char arr[5],int i)
{
	arr[0]='N';
	int j=1;
	char temp[4];
	int k=0;
	while(i)
	{
		int rem=i%10;
		temp[k++]=char('0'+rem);
		i/=10;
	}

	for(int l=k-1;l>=0;l--)
	{
		arr[j++]=temp[l];
	}
	arr[j]='\0';
}

node *search(node *curr,int f)
{
	if(curr==NULL)
		return curr;
	if(curr->next==NULL)
		return curr;

	if(curr->next->freq>f)
		return curr;
	else 
		search(curr->next,f);

}	

ofstream fout;

void preorder(node *curr)
{
	if(curr==NULL)
		return;
	fout<<curr->symbol<<"("<<curr->freq<<"),  ";

	// if(curr->left==NULL &&  curr->right==NULL)
	// 	cout<<endl;
	// else
	// 	cout<<", ";

	preorder(curr->left);
	preorder(curr->right);

}

void treetraverse(node *curr,char arr[1000],int len,char huffman[][1000])
{
	if(curr==NULL)
		return;
	if(curr->left==NULL && curr->right==NULL)
	{
		char c=curr->symbol[0];
		if(c>='0' && c<='9')
			strcpy(huffman[26+int(c-'0')],arr);
		else if(c>='a' && c<='z')  
			strcpy(huffman[c-'a'],arr);
	}
	else
	{
		arr[len++]='0';
		arr[len]='\0';
		treetraverse(curr->left,arr,len,huffman);
		len--;
		arr[len]='\0';

		arr[len++]='1';
		arr[len]='\0';
		treetraverse(curr->right,arr,len,huffman);
		len--;
		arr[len]='\0';
	}

}

int main()
{
	ifstream fin;
	fin.open("log.txt");
	fout.open("output.txt");
	int n;
	fin>>n;

	int freq[26],num[10];

	for(int i=0;i<26;i++)
		freq[i]=0;

	for(int i=0;i<10;i++)
		num[i]=0;


	for(int i=0;i<n;i++)
	{
		char s[100];
		fin>>s;

		for(int j=0;j<strlen(s);j++)
		{
			if(s[j]>='a' && s[j]<='z')
				freq[int(s[j]-'a')]+=1;
			else if(s[j]>='A' && s[j]<='Z')
			{
				freq[s[j]-'A']++;
				s[j]='a'+(s[j]-'A');
			}

			else if(s[j]>='0' && s[j]<='9')
				num[int(s[j]-'0')]+=1;
		}
	}

	for(int i=0;i<26;i++)
		fout<<char('a'+i)<<" = "<<freq[i]<<",";

	for(int i=0;i<10;i++)
	{
		fout<<i<<" = "<<num[i];

		if(i<9)
			fout<<",";
		else
			fout<<endl;
	}

	node *head=NULL,*curr=NULL;
	int i=0;
	while(i<36)
	{
		char c;
		int cnt=1e6;

		for(int i=9;i>=0;i--)
		{
			if(cnt>num[i])
			{
				cnt=num[i];
				c=char('0'+i);
			}
			else if(cnt==num[i])
			{
				c=(char)('0'+i);
			}
		}

		for(int i=25;i>=0;i--)
		{
			if(cnt>freq[i])
			{
				cnt=freq[i];
				c=char('a'+i);
			}
			else if(cnt==freq[i])
				c=char('a'+i);
		}
		

		if(c>='0' && c<='9')
			num[c-'0']=INF;
		else
			freq[c-'a']=INF;

		if(curr==NULL)
		{
			curr=new node;
			curr->left=NULL;
			curr->right=NULL;
			curr->symbol=(char *)malloc(5*sizeof(char));	
			curr->symbol[0]=c;
			curr->freq=cnt;
			head=curr;
		}
		else
		{
			curr=push(curr,c,cnt);
		}

		i++;
	}
	

	// traverse(head);//checking if linked list is okay

	i=1;

	while(head->next!=NULL)
	{
		node *temp=new node;
		node *cur1=head,*cur2=head->next;
		temp->freq=(cur1->freq)+(cur2->freq);
		head=cur2->next;
		temp->left=cur1;
		temp->right=cur2;

		temp->symbol=(char *)malloc(5*sizeof(char));
		conv(temp->symbol,i);
		head=cur2->next;


		node *prev=search(head,temp->freq);
		if(prev==NULL)
		{
			head=temp;
			head->next=NULL;
		}
		else
		{
		   node *nxt=prev->next;
		   prev->next=temp;
		   temp->next=nxt;
		}
		i++;
	}

	preorder(head);
	fout<<endl;

	char arr[1000],huffman[36][1000];
	treetraverse(head,arr,0,huffman);

	for(int i=0;i<36;i++)
	{
		if(i<26)
		{
			fout<<char('a'+i)<<" "<<huffman[i]<<endl;
		}
		else
		{
			fout<<i-26<<" "<<huffman[i]<<endl;
		}
	}

	fin.close();
	fout.close();

		
	return 0;
}
