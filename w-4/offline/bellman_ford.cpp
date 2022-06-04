/*BISMILLAH
THE WHITE WOLF
NO DREAM IS TOO BIG AND NO DREAMER IS TOO SMALL*/

#include <bits/stdc++.h>
using namespace std;

struct edge
{
    int u, v;
    long long int w;
};

const long long int inf = 1000000000000000000;
int n, m;
vector<edge> edges;
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

/*
1| returns false if graph contains negative cylce
*/
bool bellman_ford(int root)
{
    dist.assign(n + 1, inf);
    par.assign(n + 1, -1);
    dist[root] = 0;
    for (int i = 0; i < n - 1; i++)
    {
        bool no_change = true;
        for (int j = 0; j < m; j++)
        {
            int u = edges[j].u, v = edges[j].v;
            long long int w = edges[j].w;
            if (dist[u] != inf && dist[u] + w < dist[v])
            {
                no_change = false;
                dist[v] = dist[u] + w;
                par[v] = u;
            }
        }
        if (no_change)
        {
            break;
        }
    }
    for (int i = 0; i < m; i++)
    {
        int u = edges[i].u, v = edges[i].v;
        long long int w = edges[i].w;
        if (dist[u] + w < dist[v])
        {
            return false;
        }
    }
    return true;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    in >> n >> m;
    for (int i = 0; i < m; i++)
    {
        edge e;
        in >> e.u >> e.v >> e.w;
        edges.push_back(e);
    }
    int s, d;
    in >> s >> d;
    bool contain_neg_cycle = !bellman_ford(s);
    if (contain_neg_cycle)
    {
        out << "The graph contains negative cycle\n";
    }
    else
    {
        // output
        out << "The graph does not contain negative cycle.\nShortest Path Cost: " << dist[d] << "\n";
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
    }
    return 0;
}