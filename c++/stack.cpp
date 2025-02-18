#include<iostream>
#include<stack>
int main()
{
    std::stack<int> s1,s2;
    for(int i=0; i<10; i++)
    {
        s1.push(i);
    }
    std::cout<<s1.top()<<"\n";
    std::swap(s1,s2);
    while(!s2.empty())
    {
        s2.pop();
    }
    std::cout<<s2.size()<<"\n";
}