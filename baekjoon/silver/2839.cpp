#include<iostream>
#include<algorithm>
#include<vector>
#define MAX 2147483647
int main()
{
    std::iostream::sync_with_stdio(false);
    std::cout.tie(0); std::cin.tie(0);
    int n;
    std::cin>>n;
    std::vector<int> v(n+1,MAX);
    v[3]=1;
    v[5]=1;
    for(int i=6; i<=n; i++)
    {
        if(v[i-3]!= MAX) v[i]=std::min(v[i],v[i-3])+1;
        if(v[i-5]!= MAX) v[i]=std::min(v[i],v[i-5])+1;
    }
    if(v[n]<MAX) std::cout<<v[n]<<'\n';
    else std::cout<<-1<<'\n';
    return 0;
}

/*
문제를 풀 때 v[i-3],v[i-5]의 값이 min을 써서 알아서
필터가 된다고 생각하였는데, 이경우 MAX가 나타나는 경우는 불가능을
의미함으로 명시적으로 조건을 확인하는 것이 필요함


변경전 
v[n]=std::min(v[i-3],v[i-5])+1;

변경후
if(v[i-3]!= MAX) v[i]=std::min(v[i],v[i-3])+1;
if(v[i-5]!= MAX) v[i]=std::min(v[i],v[i-5])+1;
*/