/*BISMILLAH
THE WHITE WOLF
NO DREAM IS TOO BIG AND NO DREAMER IS TOO SMALL*/

#include <bits/stdc++.h>
using namespace std;

typedef struct
{
    int u, v;
    double w;
} edge;

/* reversing the cmpEdges will generate max spanning tree */
bool cmpEdges(edge a, edge b)
{
    return a.w < b.w;
}

vector<edge> minSpanningEdges;
double minSpanningCost;
vector<int> treeId;

vector<edge> edges;

int root(int x)
{
    while (treeId[x] != x)
    {
        treeId[x] = treeId[treeId[x]];
        x = treeId[x];
    }
    return x;
}

void connectComponents(int x, int y)
{
    int r1 = root(x);
    int r2 = root(y);
    treeId[r1] = treeId[r2];
}

void kruskals()
{
    minSpanningCost = 0;
    minSpanningEdges.clear();
    sort(edges.begin(), edges.end(), cmpEdges);
    for (auto e : edges)
    {
        int u = e.u;
        int v = e.v;
        double w = e.w;
        if (root(u) != root(v))
        {
            minSpanningCost += w;
            minSpanningEdges.push_back(e);
            connectComponents(u, v);
        }
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    /*insert edges in the edges vector as edge struct(u, v, w). N is the max number of nodes. */

    int n, m;
    in >> n >> m;
    treeId.assign(n, -1);
    for (int i = 0; i < n; i++)
    {
        treeId[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        edge e;
        in >> e.u >> e.v >> e.w;
        edges.push_back(e);
    }

    kruskals();
    /* minSpanningCost and minSpanningEdges */

    assert((int)minSpanningEdges.size() == n - 1);
    out << "Cost of the minimum spanning tree: " << minSpanningCost << "\n";
    out << "List of edges selected by kruskal's algorithm: {";
    for (int i = 0; i < n - 1; i++)
    {
        out << "(" << minSpanningEdges[i].u << "," << minSpanningEdges[i].v << ")";
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