#include <stdio.h>
#include "LIS.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void fillRand(int arr[],int n)
{
    for(int i=0; i<n; i++) {
        arr[i] =rand() %(n*10);
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    int n=8;
    int arr[n];//= { 10, 22, 9, 33, 21, 50, 41, 60 };
    for(int i=0; i<10; i<i++) {
        cout<<i+1<<"-iteration"<<endl;
        fillRand(arr,n);
//   printArray(arr,n);

        cout<<lisDP1(arr,n)<<endl;
        cout<<lisRec1(arr,n)<<endl;
        //cout<<lisRec2(arr,n)<<endl;
        cout<<lisDP2(arr,n)<<endl;
        cout<<lisLogN2(arr,n)<<endl;
        cout<<"==================================="<<endl;

    }
    return 0;
}
