/*
NAME-DEBANJAN SAHA
ROLL-19CS30014
*/

/*----------PART1-----------------------------------------------------------------------------------

Define:-
	dp[i][j] denotes maximum probability of success of i reactions using total j units of catalysts.

Optimal subproblem:-
	
 	Suppose I am calculating for N reactions and C units of catalysts.Suppose for j units used in N-th
 	reaction I get maximum value of overall probability . So the probability will be = e(N,j)*dp[N-1][C-j].
 	i.e - product of probability of N-th experiment with j units and the maximum value of probability of 
 	all N-1 reactions with a total C-j units of catalysts.


Recursive formulation:-

   dp[i][j] = max { e(i,k)*dp[i-1][j-k] } for all k=1 to k<=j.


Base Cases:-

	dp[1][j]=e(1,j); 
	
	dp[i][0]=0 ; (as e(i,0)=0 --> no catalyst means no success)
	
	dp[0][j]=0; ( no reaction means no success ;actually it does not matter what value I choose as its 
				 value does	not affect my dp table.So I can choose it as success and denote 1 too. )
	
Time Complexity:
  	
  	O(N*C^2)

-------------------------------------------------------------------------------------------------------*/

#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;


//---------PART 2 ---------------------------------------------------------

int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("input.txt");
	fout.open("output.txt");

	int n,c;
	fin>>n>>c;
	double **probability,**dp;

	probability=(double **)malloc((n+1)*sizeof(double *));
	dp=(double **)malloc((n+1)*sizeof(double *));

	for(int i=0;i<=n;i++)
	{
		probability[i]=(double *)malloc((c+1)*sizeof(double));
		dp[i]=(double *)malloc((c+1)*sizeof(double));
	}


	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=c;j++)
		{
			fin>>probability[i][j];
		}
	}

	for(int i=0;i<=n;i++)
	{
		probability[i][0]=0;
		dp[i][0]=0;
	}

	for(int j=0;j<=c;j++)
	{
		probability[0][j]=0;
		dp[0][j]=0;
		dp[1][j]=probability[1][j];
	}

	int num[n+1]; //Number of catalysts per reaction.

	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=c;j++)
		{
			dp[i][j]=0; // I dont know their maximum probability yet.So make them minimum = 0.
			
			for(int k=1;k<=j;k++)
			{
				double curr=probability[i][k]*dp[i-1][j-k];
				if(dp[i][j]<curr)
					dp[i][j]=curr;
			}
		}
	}


	fout<<dp[n][c]<<endl;

	//Backtracking 
	for(int i=n;i>=1;i--)
	{
		for(int j=1;j<=c;j++)
		{
			if(dp[i][c]==(dp[i-1][c-j]*probability[i][j])) //means I have used j units in i-th reaction
			{
				num[i]=j; //so I assign j units to i-th reaction
				c-=j; // remove those j units from total available units .
				break;
			}

			if(i==1) // since I can not backtrack it from previous values as it was my base case
				num[i]=c; //so assign whatever is remaining units of catalysts.
		}
	}


	for(int i=1;i<=n;i++)
		fout<<"Reaction "<<i<<" : "<<num[i]<<endl;



	for(int i=0;i<=n;i++)
	{
		free(dp[i]);
		free(probability[i]);
	}

	fin.close();
	fout.close();

	return 0;
}

