#include <bits/stdc++.h>
using namespace std;

string inp[3];

bool same(string s)
{
    int n = s.size();
    for(int i = 1; i < n; i++)
    {
        if(s[i] != s[i-1])
        {
            return false;
        }
    }
    return true;
}

/*
returns number of winning state for the letter c
*/
int win(char c)
{
    int ret = 0;
    for(int i = 0; i< 3; i++)
    {
        if(same(inp[i]) && inp[i][0] == c)
        {
            ret++;
        }
    }
    for(int i = 0; i < 3; i++)
    {
        string temp;
        for(int j = 0;j < 3; j++)
        {
            temp.push_back(inp[j][i]);
        }
        if(same(temp) && temp[0] == c)
        {
            ret++;
        }
    }
    string temp;
    for(int i = 0; i< 3; i++)
    {
        temp.push_back(inp[i][i]);
    }
    if(same(temp)&&temp[0] == c)
    {
        ret++;
    }
    temp.clear();
    for(int i = 0, j = 2; i < 3; i++, j--)
    {
        temp.push_back(inp[i][j]);
    }
    if(same(temp)&&temp[0] == c)
    {
        ret++;
    }
    return ret;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int cx = 0, co = 0, cd = 0;
        for(int i = 0; i< 3; i++)
        {
            inp[i].clear();
            cin>>inp[i];
            for(int j = 0;j < 3; j++)
            {
                cx += (inp[i][j] == 'X');
                co += (inp[i][j] == 'O');
                cd += (inp[i][j] == '_');
            }
        }
        
        int wx = win('X');
        int wo = win('O');
        int ans;
        /*
        ans = 3; below are 2 conditions for valid grid
        1| number of x must be equal or 1 more than number of o
        2| there can't be more than one winning state in a valid grid

        ans = 1
        3|if all the cells are marked, the game is a draw.
        4| if number of winning state is 1 then someone has won.

        else ans = 2

        */
        if(cx - co > 1 || cx - co < 0 || wx + wo > 1)
        {
            ans = 3;
        }
        else if(cd == 0 || wx + wo == 1)
        {
            ans = 1;
        }
        else 
        {
            ans = 2;
        }
        cout<<ans<<"\n";
    }
}