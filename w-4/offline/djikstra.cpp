#include <bits/stdc++.h>
using namespace std;

int n, m;
const long long int inf = 1000000000000000000;
vector<vector<pair<long long int, int>>> adj;
vector<long long int> dist;
vector<int> par;

/*
1| v must be 0-indexed
2| if no path exist from root to v, the returned vector is empty
*/
vector<int> getPath(int v, int root = 0)
{
    vector<int> path;
    for (int cur = v; cur != -1; cur = par[cur])
    {
        path.push_back(cur);
    }
    reverse(path.begin(), path.end());
    if (path[0] != root)
    {
        path.clear();
    }
    return path;
}

void djikstra(int root)
{
    dist.assign(n + 1, inf);
    par.assign(n + 1, -1);
    dist[root] = 0;
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
            if (dist[u] + w < dist[v])
            {
                if (pq.count({dist[v], v}))
                {
                    pq.erase(pq.find({dist[v], v}));
                }
                dist[v] = dist[u] + w;
                par[v] = u;
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
        // directed graph
        adj[u].push_back({w, v});
    }
    int s, d;
    in >> s >> d;
    djikstra(s);
    // output
    out << "Shortest Path Cost: " << dist[d] << "\n";
    vector<int> path = getPath(d, s);
    int pn = path.size();
    for (int i = 0; i < pn; i++)
    {
        out << path[i];
        if (i < pn - 1)
        {
            out << "->";
        }
    }
    return 0;
}