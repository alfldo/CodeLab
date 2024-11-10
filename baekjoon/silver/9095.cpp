#include<iostream>
#include<vector>
#include<algorithm>

int main()
{
    int T,n,max;
    std::vector<int> v,dp;
    std::cin >> T;
    for(int i=0; i<T; i++)
    {
        std::cin >> n;
        v.push_back(n);
    }
    max= *std::max_element(v.begin(),v.end());
    dp.assign(max,0);
    for(int i=0; i<max; i++)
    {

    }
    return 0;
}