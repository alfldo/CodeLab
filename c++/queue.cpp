#include<iostream>
#include<queue>
int main()
{
    std::queue<int> q1,q2;
    for(int i=0; i<10; i++)
    {
        q1.push(i);
    }
    std::cout<<q1.front()<<"\n";
    std::cout<<q1.back()<<"\n";
    std::swap(q1,q2);
    while(!q2.empty())
    {
        q2.pop();
    }
    std::cout<<q2.size()<<"\n";
    return 0;
}