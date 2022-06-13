/*BISMILLAH
THE WHITE WOLF
NO DREAM IS TOO BIG AND NO DREAMER IS TOO SMALL*/

#include <bits/stdc++.h>
using namespace std;

const int inf = INT_MAX;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n, m;
    in >> n >> m;
    vector<vector<int>> dist(n, vector<int>(n, inf));
    for (int i = 0; i < n; i++)
    {
        dist[i][i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        in >> u >> v >> w;
        u--;
        v--;
        dist[u][v] = w;
    }
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] < inf && dist[k][j] < inf)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] == inf)
            {
                out << "INF"
                    << " \n"[j == n - 1];
            }
            else
            {
                out << dist[i][j] << " \n"[j == n - 1];
            }
        }
    }
    return 0;
}