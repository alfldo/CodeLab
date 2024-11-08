#include<iostream>
#include<vector>
#include<algorithm>
#define MAX 999999
int main()
{
    int n;
    std::cin >> n;
    std::vector<int> v(n+1,MAX);
    v[1]=0;
    for(int i=2; i<=n; i++)
    {
        if(i%3==0) v[i]= std::min(v[i/3]+1,v[i]);
        if(i%2==0) v[i] = std::min(v[i/2]+1,v[i]);
        v[i]= std::min(v[i],v[i-1]+1); 
    }
    std::cout<<v[n]<<'\n';
    return 0;
}