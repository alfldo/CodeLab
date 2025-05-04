#include<iostream>
#include<vector>
int main()
{
    std::vector<int> v(10,0);
    v.assign(5,1);
    std:: cout<< v[0] << " " << v.front() << " " << v.back()<<"\n";
    v.clear();
    
    return 0;
}