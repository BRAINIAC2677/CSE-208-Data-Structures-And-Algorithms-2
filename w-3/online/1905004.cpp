#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    int u, v;
    double w;
} edge;

bool cmpEdges(edge a, edge b)
{
    return a.w > b.w;
}

int n, m;
vector<set<pair<double, int>>> adj;
vector<edge> edges;
vector<bool> vis;

void dfs(int node)
{
    vis[node] = true;
    for (auto a : adj[node])
    {
        if (!vis[a.second])
        {
            dfs(a.second);
        }
    }
}

bool is_connected()
{
    vis.assign(n, false);
    int comp = 0;
    for (int i = 0; i < n; i++)
    {
        if (!vis[i])
        {
            comp++;
            dfs(i);
        }
    }
    return comp == 1;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in >> n >> m;
    adj.assign(n, set<pair<double, int>>());
    for (int i = 0; i < m; i++)
    {
        int u, v;
        double w;
        in >> u >> v >> w;
        adj[u].insert({w, v});
        adj[v].insert({w, u});
        edges.push_back({u, v, w});
    }
    double minSpanningCost = 0;
    vector<edge> minSpanningEdges;
    sort(edges.begin(), edges.end(), cmpEdges);
    for (int i = 0; i < m; i++)
    {
        int u = edges[i].u, v = edges[i].v;
        double w = edges[i].w;
        adj[u].erase({w, v});
        adj[v].erase({w, u});
        if (!is_connected())
        {
            minSpanningCost += w;
            minSpanningEdges.push_back(edges[i]);
            adj[u].insert({w, v});
            adj[v].insert({w, u});
        }
    }

    // output
    out << "Edges in MST\n";
    for (int i = 0; i < minSpanningEdges.size(); i++)
    {
        out << "(" << minSpanningEdges[i].u << "," << minSpanningEdges[i].v << ")\n";
    }
    out << "Total weight of MST is " << minSpanningCost << "\n";
    return 0;
}