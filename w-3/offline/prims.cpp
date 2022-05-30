/*BISMILLAH
THE WHITE WOLF
NO DREAM IS TOO BIG AND NO DREAMER IS TOO SMALL*/

#include <bits/stdc++.h>
using namespace std;

const int maxn = 10009;

vector<pair<double, int>> adj[maxn];
double minSpanningCost;
vector<pair<int, int>> minSpanningEdges;

void prims(int root)
{
    minSpanningCost = 0;
    vector<int> marked(maxn);
    priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>>> pq;
    pq.push({0, {root, -1}});
    while (!pq.empty())
    {
        auto e = pq.top();
        pq.pop();
        int u = e.second.first;
        double weight = e.first;
        if (marked[u])
            continue;
        marked[u] = 1;
        minSpanningCost += weight;
        if (e.second.second != -1)
        {
            minSpanningEdges.push_back(e.second);
        }
        for (pair<int, int> a : adj[u])
        {
            int v = a.second;
            if (!marked[v])
            {
                pq.push({a.first, {v, u}});
            }
        }
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    /* make adj list here. adj[i]:{weight, vertext}. maxn is the maximum no of nodes.*/
    int n, m;
    in >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v;
        double w;
        in >> u >> v >> w;
        adj[u].push_back({w, v});
        adj[v].push_back({w, u});
    }

    /* prims(1) for mst rooted at 1.*/
    prims(1);

    assert((int)minSpanningEdges.size() == n - 1);
    out << "Cost of the minimum spanning tree: " << minSpanningCost << "\n";
    out << "List of edges selected by kruskal's algorithm: {";
    for (int i = 0; i < n - 1; i++)
    {
        out << "(" << minSpanningEdges[i].first << "," << minSpanningEdges[i].second << ")";
        if (i == n - 2)
        {
            out << "}\n";
        }
        else
        {
            out << ",";
        }
    }

    return 0;
}