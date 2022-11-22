/*
NAME-DEBANJAN SAHA
ROLL-19CS30014
*/
#include<iostream>
#include<fstream>
#include <iomanip> 
using namespace std;

int max(int a,int b)
{
	if(a>=b)
		return a;
	return b;
}

typedef struct interval
{
	int id;
	int start;
	int end;
	int length;
} interval;

void schedule_visit(int *ans,interval a[], int len, int n,int order[])
{
    if (len==1)  //when size is 1 ,I dont need to swap so I just binary search 
    {
        int lo=1,hi=1440*60;

		while(lo<hi) //Binary Search
		{
			bool flag=1;
			int time=a[0].start*60;
			int mid=(lo+hi)/2;

			for(int i=1;i<n;i++)
			{
				if(a[i].end*60-time<mid)
				{
					flag=0;
					break;
				}
				else
				{
					time=max(a[i].start*60,time+mid);
				}
			}

			if(flag)
				lo=mid+1;
			else
				hi=mid;

		}

		if(*ans<=lo-1) //Updating maximum possible ans
		{
			*ans=lo-1;
			for(int i=0;i<n;i++)
			{
				order[i]=a[i].id;
			}
		}

       return; 
    }
 	
 	//recursion for checking all possible combinations of the array.
    for (int i=0;i<len;i++) 
    {
        schedule_visit(ans,a,len-1,n,order);

        // if length is odd, I swap 0th or first and (len-1)th or (last) element
        if(len%2==1)
        {
        	interval temp=a[0];
        	a[0]=a[len-1];
        	a[len-1]=temp;
        }
 
        // If length is even, swap ith and (len-1)th or (last) element
        else
        {
            interval temp=a[i];
        	a[i]=a[len-1];
        	a[len-1]=temp;
        }
    }

}


int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input1.txt");
	fout.open("output1.txt");
	int n;
	fin>>n;
	interval arr[n];
	for(int i=0;i<n;i++)
	{
		fin>>arr[i].start>>arr[i].end;
		arr[i].length=arr[i].end-arr[i].start;
		arr[i].id=i; //Numbering as per I got them.
	}

	int order[n];
	int time=0;

	schedule_visit(&time,arr,n,n,order);
	int min=time/60;
	int second=time%60;
	fout<<min<<" : ";
	fout<<setfill('0')<<setw(2)<<second<<endl;

	for(int i=0;i<n;i++)
	{
		fout<<order[i]<<" ";
	}
	fout<<endl;

	fin.close();
	fout.close();

	return 0;
}

