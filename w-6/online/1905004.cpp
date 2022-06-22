#include <bits/stdc++.h>
using namespace std;

const long long int inf = INT_MAX;

int n, mn, wn;
vector<int> parent;
vector<vector<int>> adj;
vector<vector<long long int>> residual_capacity;

vector<int> height, age, is_divorced;

long long int bfs(int s, int t, vector<int> &parent)
{
    parent.assign(n, -1);
    queue<pair<int, long long int>> q;
    q.push({s, inf});
    parent[s] = -2;
    while (!q.empty())
    {
        int u = q.front().first;
        long long int cur_flow = q.front().second;
        q.pop();
        for (int v : adj[u])
        {
            if (parent[v] == -1 && residual_capacity[u][v] > 0)
            {
                parent[v] = u;
                cur_flow = min(cur_flow, residual_capacity[u][v]);
                if (v == t)
                {
                    return cur_flow;
                }
                q.push({v, cur_flow});
            }
        }
    }
    return 0;
}

long long int max_flow(int s, int t)
{
    long long int flow = 0, new_flow = bfs(s, t, parent);
    while (new_flow)
    {
        flow += new_flow;
        int cur = t;
        while (cur != s)
        {
            int prev = parent[cur];
            residual_capacity[prev][cur] -= new_flow;
            residual_capacity[cur][prev] += new_flow;
            cur = prev;
        }
        new_flow = bfs(s, t, parent);
    }
    return flow;
}

int solve(int testcase)
{
    int ret;
    adj.assign(n, vector<int>());
    residual_capacity.assign(n, vector<long long int>(n));
    // adding men vertices with source
    for (int i = 0; i < mn; i++)
    {
        adj[i].push_back(n - 2);
        adj[n - 2].push_back(i);
        residual_capacity[n - 2][i] = 1;
    }
    // adding women vertices with sink
    for (int i = mn; i < wn + mn; i++)
    {
        adj[i].push_back(n - 1);
        adj[n - 1].push_back(i);
        residual_capacity[i][n - 1] = 1;
    }
    // adding men vertices with women vertices
    for (int i = 0; i < mn; i++)
    {
        for (int j = mn; j < wn + mn; j++)
        {
            if (abs(height[i] - height[j]) <= 12 && abs(age[i] - age[j]) <= 5 && is_divorced[i] == is_divorced[j])
            {
                adj[i].push_back(j);
                adj[j].push_back(i);
                residual_capacity[i][j] = 1;
            }
        }
    }
    ret = max_flow(n - 2, n - 1);
    return ret;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int testcases;
    in >> testcases;
    for (int testcase = 1; testcase <= testcases; testcase++)
    {
        in >> mn >> wn;
        n = mn + wn + 2;
        height.assign(n - 2, -1);
        age.assign(n - 2, -1);
        is_divorced.assign(n - 2, -1);
        for (int i = 0; i < mn + wn; i++)
        {
            in >> height[i] >> age[i] >> is_divorced[i];
        }
        out << "Case " << testcase << ": " << solve(testcase) << "\n";
    }
    return 0;
}