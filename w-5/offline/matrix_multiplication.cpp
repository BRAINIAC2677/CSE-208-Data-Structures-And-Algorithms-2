/*BISMILLAH
THE WHITE WOLF
NO DREAM IS TOO BIG AND NO DREAMER IS TOO SMALL*/

#include <bits/stdc++.h>
using namespace std;

const int inf = INT_MAX;

vector<vector<int>> matmult(vector<vector<int>> a, vector<vector<int>> b)
{
    int n = a.size(), m = b[0].size(), l = b.size();
    vector<vector<int>> ret(n, vector<int>(m, inf));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int k = 0; k < l; k++)
            {
                if (a[i][k] < inf && b[k][j] < inf)
                {
                    ret[i][j] = min(ret[i][j], a[i][k] + b[k][j]);
                }
            }
        }
    }
    return ret;
}

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
    int p = 1;
    while (p < n - 1)
    {
        dist = matmult(dist, dist);
        p <<= 1;
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
