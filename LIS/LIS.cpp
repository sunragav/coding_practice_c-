#include <iostream>
#include <memory.h>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include "LIS.h"
using namespace std;

int lisRec1(int arr[], int n,int& m)
{
    if(n==1) return 1;
    int res =1;
    int max_so_far = 1;
    for(int i=1; i<n; i++) {
        res=lisRec1(arr,i,m);
        if(arr[i-1]<arr[n-1] && res+1>max_so_far) max_so_far = res+1;
    }
    m= max(m,max_so_far);
    return max_so_far;
}

int lisRec1(int arr[],int n)
{

    cout<<"recursive solution"<<endl;
    int m=0;
    lisRec1(arr,n,m);
    return m;
}

int lisDP1(int arr[],int n)
{
    cout<<"DP solution1"<<endl;
    int dp[n];
    for(int i=0; i<n; i++)
        dp[i]=1;
    for(int i=1; i<n; i++) {
        for(int j=0; j<i; j++) {
            if(arr[j]<arr[i] && dp[i]<dp[j]+1)dp[i]=dp[j]+1;
        }
    }
    int m=0;
    for(int i=0; i<n; i++)
        m= max(m,dp[i]);
    return m;
}
/*
 *      a p p l e
 *    0 0 0 0 0 0
 * a  0 1 1 1 1 1
 * p  0 1 2 2 2 2
 * e  0 1 2 2 2 3
 *
 */

int lcs(int arr1[], int arr2[], int n)
{
    int dp[n+1][n+1];
    memset(dp,0,sizeof(dp));
    for(int i=1; i<n+1; i++) {
        for(int j=1; j<n+1; j++) {
            if(arr1[i-1]==arr2[j-1])dp[i][j]=dp[i-1][j-1]+1;
            else dp[i][j] = max(dp[i][j-1],dp[i-1][j]);
        }
    }
    /*
    for(int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            cout<<dp[i][j]<<" ";

        }
        cout<<endl;
    }*/
    /*int i=n,j=n;

    while(i>0 && j>0) {
        if(arr1[i-1]==arr2[j-1]) {
            v.push_back(arr1[i-1]);
            //cout<<arr1[i-1]<<" ";
            i=i-1;
            j=j-1;
        } else if(dp[i-1][j]>dp[i][j-1]) {
            i--;
        } else {
            j--;
        }
    }
    //cout<<endl;

    for(int i=v.size()-1; i>=0; i--)
        cout<<v[i]<<" ";
    cout<<endl;*/
    return dp[n][n];
}

int lisDP2(int arr[],int n)
{
    cout<<"DP solution2 (lis via lcs method)"<<endl;
    int arr2[n];
    memcpy(arr2,arr,sizeof(int)*n);
    sort(arr2,arr2+n);
    unique(arr2,arr2+n);

    //printArray(arr2, n);
    return lcs(arr,arr2,n);
}

int ceilIndex(int temp[], int s, int e,int p)
{
    while(e-s>1) {
        int m= s+(e-s)/2;
        if(temp[m]>=p) {
            e=m;
        }  else {
            s=m;
        }
    }
    return e;
}

int lisLogN(int a[],int n)
{
    cout<<"nlogn solution"<<endl;
    int temp[n]= {0};
    int parent[n]= {0};
    int len  = 1;
    temp[0]=a[0];
    for(int i=1; i<n; i++) {
        if(a[i]<temp[0]) {
            temp[0] =a[i];
        } else if(a[i]>temp[len-1]) {
            temp[len++]=a[i];
        } else {
            temp[ceilIndex(temp,-1,len-1,a[i])] =a[i];
        }
    }
    return len;
}

int lisLogN2(int a[],int n)
{
    cout<<"nlogn solution"<<endl;
    int temp[n]= {0};
    int parent[n]= {0};
    memset(parent,-1,sizeof(parent));
    int len  = 1;
    temp[0]=0;
    for(int i=1; i<n; i++) {
        if(a[i]<a[temp[0]]) {
            temp[0] =i;
        } else if(a[i]>a[temp[len-1]]) {
            parent[i]=temp[len-1];
            temp[len++]=i;

        } else {
            int index= ceilIndex(temp,-1,len-1,a[i]);
            temp[index] =i;
            parent[i]=temp[index-1];
        }
    }

    int index=temp[len-1];
    while(index!=-1) {
        cout<<a[index]<<" ";
        index=parent[index];
    }
    cout<<endl;
    for(int i=temp[len-1]; i>=0; i=parent[i])
        cout<<a[i]<<" ";
    cout<<endl;
    return len;
}

void printArray(int a[],int n)
{
    for(int i=0; i<n; i++)
        cout<<a[i]<<" ";
    cout<<endl;
}
