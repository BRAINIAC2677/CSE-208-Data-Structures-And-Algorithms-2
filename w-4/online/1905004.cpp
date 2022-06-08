/*BISMILLAH
THE WHITE WOLF
NO DREAM IS TOO BIG AND NO DREAMER IS TOO SMALL*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
const long long int inf = 1000000000000000000;
vector<vector<pair<long long int, int>>> adj;
vector<long long int> dist;
vector<int> ans;

void djikstra(int root)
{
    dist.assign(n + 1, inf);
    ans.assign(n + 1, n);
    dist[root] = 0;
    ans[root] = 0;
    multiset<pair<long long int, int>> pq;
    pq.insert({dist[root], root});
    while (!pq.empty())
    {
        auto cur = *(pq.begin());
        pq.erase(pq.begin());
        int u = cur.second;
        for (auto next : adj[u])
        {
            int v = next.second;
            long long int w = next.first;
            if ((dist[u] + w < dist[v]) || ((dist[u] + w == dist[v]) && (ans[u] + 1 < ans[v])))
            {
                if (pq.count({dist[v], v}))
                {
                    pq.erase(pq.find({dist[v], v}));
                }
                dist[v] = dist[u] + w;
                ans[v] = ans[u] + 1;
                pq.insert({dist[v], v});
            }
        }
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in >> n >> m;
    adj.assign(n + 1, vector<pair<long long int, int>>());
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long int w;
        in >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }
    int s;
    in >> s;
    djikstra(s);
    for (int i = 0; i < n; i++)
    {
        out << ans[i] << "\n";
    }
    return 0;
}