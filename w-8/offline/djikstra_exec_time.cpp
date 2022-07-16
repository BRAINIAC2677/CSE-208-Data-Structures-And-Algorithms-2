#include "binary_heap.h"
#include "fibonacci_heap.h"

#include <bits/stdc++.h>
using namespace std;

int n, m;
const long long int inf = 1000000000000000000;
vector<vector<pair<long long int, int>>> adj;
vector<long long int> path_cost, path_len;
vector<int> par;

void fibDjikstra(int root)
{
    path_cost.assign(n + 1, inf);
    path_len.assign(n + 1, inf);
    par.assign(n + 1, -1);
    path_cost[root] = 0;
    path_len[root] = 0;
    fibonacci_heap::PriorityQueue<pair<long long int, int>> pq;
    pq.push({path_cost[root], root});
    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        int u = cur.second;
        for (auto next : adj[u])
        {
            int v = next.second;
            long long int w = next.first;
            if (path_cost[u] + w < path_cost[v])
            {
                path_cost[v] = path_cost[u] + w;
                path_len[v] = path_len[u] + 1;
                par[v] = u;
                pq.push({path_cost[v], v});
            }
        }
    }
}

void binDjikstra(int root)
{
    path_cost.assign(n + 1, inf);
    path_len.assign(n + 1, inf);
    par.assign(n + 1, -1);
    path_cost[root] = 0;
    path_len[root] = 0;
    binary_heap::PriorityQueue<pair<long long int, int>> pq;
    pq.push({path_cost[root], root});
    while (!pq.empty())
    {
        auto cur = pq.top();
        pq.pop();
        int u = cur.second;
        for (auto next : adj[u])
        {
            int v = next.second;
            long long int w = next.first;
            if (path_cost[u] + w < path_cost[v])
            {
                path_cost[v] = path_cost[u] + w;
                path_len[v] = path_len[u] + 1;
                par[v] = u;
                pq.push({path_cost[v], v});
            }
        }
    }
}

int main()
{
    ifstream in1("directed_weighted_graph.txt");
    ofstream out("exec_time.csv");
    in1 >> n >> m;
    adj.assign(n + 1, vector<pair<long long int, int>>());
    for (int i = 0; i < m; i++)
    {
        int u, v;
        long long int w;
        in1 >> u >> v >> w;
        u--;
        v--;
        // directed graph
        adj[u].push_back({w, v});
    }
    ifstream in2("source_destination.txt");
    out << "Path Length, Path Cost,Binary Heap Execution Time(ms), Fibonacci Heap Execution Time(ms)\n";
    int k;
    in2 >> k;
    while (k--)
    {
        int s, d;
        in2 >> s >> d;
        s--;
        d--;

        clock_t before = clock();
        fibDjikstra(s);
        clock_t after = clock();
        double fib_time = (double)(after - before) / CLOCKS_PER_SEC * 1000;

        long long int len = path_len[d], cost = path_cost[d];

        before = clock();
        binDjikstra(s);
        after = clock();
        double bin_time = (double)(after - before) / CLOCKS_PER_SEC * 1000;

        assert(len == path_len[d]);
        assert(cost == path_cost[d]);

        out << len << "," << cost << "," << bin_time << "," << fib_time << "\n";
    }

    return 0;
}