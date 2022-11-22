// 19CS30014\_G06\_Assign2.c
#include<iostream>
#include "assign2.h"
using namespace std;

int maximum(int a,int b);

Point *merged_list(Point left[],Point right[],int left_size,int right_size,int *final_size)
{
  
  Point *res=(Point *)malloc((left_size+right_size)*sizeof(Point));
  int k=0;
  int h1=0,h2=0,i=0,j=0;

  while(i<left_size && j<right_size)
  {
    //This is wrong code...
  //   if(left[i].x<right[j].x)
  //   {
  //     int x1=left[i].x;
  //     h1=left[i].y;
  //     int mx=maximum(h1,h2);
  //     res[k].x=x1;
  //     res[k].y=mx;
  //     i++;
  //     k++;
  //   }
  //   else
  //   {
  //     int x2=right[j].x;
  //     h2=right[j].y;
  //     int mx=maximum(h1,h2);
  //     res[k].x=x2;
  //     res[k].y=mx;
  //     k++;
  //     j++;
  //   }
  // }
    
    if(left[i].x==right[j].x)//no change
    {
      if(maximum(h1,h2)!=maximum(left[i].y,right[j].y))
      {
        res[k].y=maximum(left[i].y,right[j].y);
        res[k++].x=left[i].x;
      }

      h1=left[i].y;
      h2=right[j].y;
      i++;
      j++;
    }
    else if(left[i].x>right[j].x) //greater left
    {
      if(right[j].y>h1)
      {
        res[k++]=right[j];

      }
      else
      {
        if(h1<h2)
        {
          res[k].x=right[j].x;
          res[k++].y=h1;
        }
      }
      h2=right[j].y;
      j++;
    }
    else if(left[i].x<right[j].x)  //smaller left
    {
      if(left[i].y>h2)
      {
        res[k++]=left[i];
      }
      else
      {
        if(h1>h2)
        {
          res[k].x=left[i].x;
          res[k++].y=h2;
        }
      }

      h1=left[i].y;
      i++;
    }
   


  }

  while(i<left_size)
  {
    res[k]=left[i];
    k++;i++;
  }

  while(j<right_size)
  {
    res[k]=right[j];
    j++;k++;
  }

  *final_size=k;
  return res;

}

Point *sort(Box boxes[],int start,int end, int *outputlength)
{
  if(start==end)
  {
    Point *res=(Point *)malloc(2*sizeof(Point));
    res[1].x=boxes[start].right;
    res[1].y=0;
    res[0].x=boxes[start].left;
    res[0].y=boxes[start].ht;
    *outputlength=2;
    return res;
  }

  int mid=(start+end)/2;  
  int left_size,right_size;
  Point *left=sort(boxes,start,mid,&left_size);
  Point *right=sort(boxes,mid+1,end,&right_size);
  Point *overall_solution = merged_list(left,right,left_size,right_size,outputlength);

  return overall_solution;

}

Point* findOutLine(Box boxes[], int size, int* outputsize)
{
  Point *point_array=sort(boxes,0,size-1,outputsize);
  return point_array;
}

int main()
{
  process();
  return 0;
}


int maximum(int a,int b)
{
  if(a>b)
    return a;
  return b;
}