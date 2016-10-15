#include <bits/stdc++.h>
using namespace std;

bool isOperator(char c)
{
    char o[] ={'+','-','*','/'};
    for(int i=0;i<4;i++)
    {
        if(c==o[i])return true;
    }
    return false;
}
int perform(char o,int o1,int o2){
    int res =0;
    switch(o){
        case '+': res= o1+o2; break;
        case '-': res= o1-o2; break;
        case '*': res= o1*o2; break;
        case '/': res= o1/o2; break;
    }
    return res;
}  

int getInt(char* dig)
{
    int res=0;
    int len = strlen(dig);
    for(int i=len-1;i>=0;i--)
    {
        res+=pow(10,len-1-i)*(dig[i]-'0');
    }    
    return res;
}

int evaluatePostFix(char s[])
{
    int res =0 ;
    stack<int> stk;
    char dig[100]={0};
    int i=0;
    while(*s)
    {
        if(isOperator(*s)){
            int o2 = stk.top();stk.pop();
            int o1 = stk.top();stk.pop();
            res = perform(*s,o1,o2);  
            stk.push(res);              
        }
        else if (isdigit(*s)){
            dig[i++]=*s;            
        }
        else if(*s==' ' && *dig){
            int d = getInt(dig);            
            stk.push(d);
            i=0;
            memset(dig,0,100);
        }
        s++;
    }
    return res; 
}

int main(int argc, char **argv)
{
	cout<<evaluatePostFix("10 6 * 30 / 2 2 * *");
	return 0;
}
