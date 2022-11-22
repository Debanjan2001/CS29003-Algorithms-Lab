/*
NAME-DEBANJAN SAHA
ROLL-19CS30014
*/
#include<iostream>
using namespace std;

#define MAX_SIZE 100
typedef struct _job 
{
	int jobId;
	int startTime;
	int jobLength;
	int remLength;
	int run; //first runtime
} job;

typedef struct _newheap 
{
	job list[MAX_SIZE];
	int index[MAX_SIZE];
	int numJobs;
} newheap;

typedef struct _jobPair 
{	int jobid_from;
	int jobid_to;
} 
jobpair;

void swap(job *a,job *b)
{
	job temp=*a;
	*a=*b;
	*b=temp;
}

int compare(job a,job b) //checks if job a<job b
{
	/* returns 1 if job a has smaller remaining length than b or
	   if they have same remaining length
			return 1 if a.id<b.id
	   otherwise returns 0
	*/

	if(a.remLength==b.remLength)
	{
		if(a.jobId<b.jobId)
			return 1;

		return 0;
	}

	if(a.remLength<b.remLength)
		return 1;

	return 0;
}


void initHeap(newheap *H)
{
	H->numJobs=0;
}

void insertJob(newheap *H, job j)
{
	H->numJobs++;

	int i=H->numJobs;

	H->index[j.jobId]=i;

	H->list[i]=j;

	int parent=i/2;

	//going up to fix heap property
	while(parent!=0 && compare(H->list[i],H->list[parent])==1)
	{
		swap( &(H->list[i]), &(H->list[parent]) );
		i/=2;
		parent/=2;
	}

}

void minHeapify(newheap *H,int i) //go down
{
	int smallest=i; //assume i to be smallest.
	int leftChild=2*i;
	int rightChild=2*i+1;
	int size = H->numJobs;

	if(leftChild<size && compare(H->list[leftChild],H->list[smallest])==1) //if left is small
		smallest=leftChild ;

	if(rightChild<=size && compare(H->list[rightChild],H->list[smallest])==1) //if right is small
		smallest=rightChild ;

	if(smallest!=i)
	{
		swap( &(H->list[i]),&(H->list[smallest]) );
		minHeapify(H,smallest);
	}
}

int extractMinJob(newheap *H,job *j)
{
	if(H->numJobs==0)
		return -1;

	*j=H->list[1];

	int size=H->numJobs;

	swap( &(H->list[1]),&(H->list[size]));
	
	H->numJobs--;

	minHeapify(H,1);

	return 0;
}

void decreaseKey(newheap *H, int jid)
{
		int i=H->index[jid];
		if(H->list[i].jobId==jid )
		{
			if(H->list[i].remLength==H->list[i].jobLength)
			{
				int len=H->list[i].remLength;
				H->list[i].remLength -= len/2;
				int par=i/2;

				int j=i;

				while(par!=0 && compare(H->list[j],H->list[par]))
				{
					swap( &(H->list[i]),&(H->list[par]));
					j/=2;
					par=j/2;
				}

			}
		}
}

void newScheduler(job jobList[], int n,jobpair pairList[], int m)
{
	int curr=0,curr_job=-1;
	newheap h;
	initHeap(&h);

	job *jobList2 =(job *)malloc((n+1)*sizeof(job)); //temp list for maintaing proper order of ids
	//preferably did this for correctly inserting into heap.

	int max_time=0;
	for(int i=0;i<n;i++)
	{
		jobList2[jobList[i].jobId]=jobList[i];

		if(max_time<jobList[i].startTime)
			max_time=jobList[i].startTime;
	}

	//sorting using counting sort--------------

	int count[max_time+1]={0};

	for(int i=0;i<n;i++)
	{
		count[jobList[i].startTime]++;
	}

	for(int i=1;i<=max_time;i++)
	{
		count[i]+=count[i-1];
	}

	job temp[n];
	for(int i=0;i<n;i++)
	{
		temp[count[jobList[i].startTime]-1]=jobList[i];
		--count[jobList[i].startTime];
	}

	for(int i=0;i<n;i++)
	{
		jobList[i]=temp[i];
		// cout<<jobList[i].jobId<<" "<<jobList[i].startTime<<endl;
	}

	//Sorting Finished----------------------

	for(int t=0;;t++)
	{
		if(t>0)
			cout<<curr_job<<" ";

		if(curr_job!=-1 && jobList2[curr_job].remLength==0)
		{
			

			for(int i=0;i<m;i++)
			{
				if(pairList[i].jobid_from==curr_job)
				{
					int to=pairList[i].jobid_to;//index of a job to change time

					if(jobList2[to].run==-1)
					{
						decreaseKey(&h,to);
						int len=jobList2[to].remLength;
						jobList2[to].remLength-=(len/2);
					}
				}
			}


			curr_job=-1;
		}

		while(curr<n && t==jobList[curr].startTime)
		{
			insertJob(&h,jobList[curr]);
			curr++;
		}

		if(curr_job==-1)
		{
			job j;
			int flag=extractMinJob(&h,&j);

			if(flag==0)
			{
				curr_job=j.jobId;
				if(jobList2[curr_job].run==-1)
						jobList2[curr_job].run=t;
			}
		}
		else
		{
			job j;
			int flag=extractMinJob(&h,&j);
			if(flag==0)
			{
				if(compare(j,jobList2[curr_job])==1)
				{
					insertJob(&h,jobList2[curr_job]);
					curr_job=j.jobId;
					if(jobList2[curr_job].run==-1)
						jobList2[curr_job].run=t;

				}
				else
				{
					insertJob(&h,j);
				}
			}
		}

		if(curr_job!=-1)
			jobList2[curr_job].remLength--;

		if(curr==n && curr_job==-1)
			break;
	}

	for(int i=0;i<n;i++)
	{
		jobList[i].remLength=0;
		jobList[i].run=jobList2[jobList[i].jobId].run;
	}

	cout<<endl;
}

int main()
{
	int n;
	cout<<"Enter no. of jobs (n): ";
	cin>>n;
	cout<<"Enter the jobs:"<<endl;

	job *job_array=(job *)malloc(n*sizeof(job));

	for(int i=0;i<n;i++)
	{
		cin>>job_array[i].jobId>>job_array[i].startTime>>job_array[i].jobLength;
		job_array[i].remLength=job_array[i].jobLength;
		job_array[i].run=-1;
	}

	cout<<"Enter the number of dependency pairs"<<endl;
	int m;
	cin>>m;

	jobpair *pairList=(jobpair *)malloc(m*sizeof(jobpair));

	cout<<"Enter the dependency pairs"<<endl;
	for(int i=0;i<m;i++)
		cin>>pairList[i].jobid_from>>pairList[i].jobid_to;



	double avg=0.0;


	cout<<"Jobs scheduled at each timestep are:"<<endl;
	newScheduler(job_array,n,pairList,m);

	for(int i=0;i<n;i++)
	{
		avg+=job_array[i].run-job_array[i].startTime;
	}

	avg/=n;

	cout<<"Average Turnaround Time is "<<avg<<endl;




	return 0;
}