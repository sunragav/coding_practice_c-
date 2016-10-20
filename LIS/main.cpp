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
    for(int n=5; n<=10; n++) {
        //int n=10;
        int arr[n];//= { 10, 22, 9, 33, 21, 50, 41, 60 };
        //int arr[n]= {1, 53, 1, 6, 40, 34, 25, 37};
        for(int i=0; i<100; i<i++) {
            cout<<i+1<<"-iteration"<<endl;
            fillRand(arr,n);
            printArray(arr,n);

            cout<<lisDP1(arr,n)<<endl;
            cout<<lisRec1(arr,n)<<endl;
            //cout<<lisRec2(arr,n)<<endl;
            cout<<lisDP2(arr,n)<<endl;
            cout<<lisLogN2(arr,n)<<endl;
            cout<<"==================================="<<endl;

        }

    }
    return 0;
}
