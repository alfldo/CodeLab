#include<bits/stdc++.h>
using namespace std;
using pp = pair<int,int>;
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
bool in_range(int x,int y,int n,int m)
{
    if (x>=0 && x<=n && y>=0 && y<=m) return 1;
    return 0;
}
int bfs(vector<vector<int> > &v, vector<vector<int> > &ck)
{
    int x,y;
    x=y=0;
    queue<pp> q;
    q.push({0,0});
    ck[0][0]=1;
    while(!q.empty())
    {
        x=q.front().first;
        y=q.front().second;
        q.pop();

    }
    return 0; 
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n,m;
    cin >> n >> m;
    vector< vector<int> > v(n,vector<int>(m,0));
    vector< vector<int> > ck(n,vector<int>(m,0));
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            cin>> v[i][j];
        }
    }
    cout<< bfs(v,ck);
}