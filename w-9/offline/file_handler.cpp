#include <bits/stdc++.h>
using namespace std;

set<int> ignores;

int main()
{
    ifstream in("in.txt");
    ofstream out("input.txt");
    ignores.insert(2);
    ignores.insert(3);
    int n;
    vector<pair<int, int>> v;
    in >> n;
    for (int i = 0; i < n; i++)
    {
        int e, x;
        in >> e >> x;
        if (ignores.count(e) == 0)
        {
            v.push_back({e, x});
        }
    }
    out << v.size() << "\n";
    for (auto p : v)
    {
        out << p.first << " " << p.second << "\n";
    }
    return 0;
}