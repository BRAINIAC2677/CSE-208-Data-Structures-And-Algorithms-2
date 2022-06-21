#include <bits/stdc++.h>
using namespace std;

const long long int inf = LONG_MAX;

int t, n;
vector<int> parent;
vector<int> in_source_segment;
vector<vector<int>> adj;
vector<vector<long long int>> residual_capacity;

vector<string> team_name;
vector<int> win, loss, remaining;
vector<vector<int>> game;

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

void mincut_dfs(int cur)
{
    in_source_segment[cur] = 1;
    for (int next : adj[cur])
    {
        if ((!in_source_segment[next]) && residual_capacity[cur][next] > 0)
        {
            mincut_dfs(next);
        }
    }
}

/*
1| assumes that the max_flow function has been called before it
*/
void calc_mincut(int s)
{
    in_source_segment.assign(n, 0);
    mincut_dfs(s);
}

bool is_eliminated(int cur_t)
{
    adj.assign(n, vector<int>());
    residual_capacity.assign(n, vector<long long int>(n));

    // connecting team vertices to sink
    for (int i = 0; i < t; i++)
    {
        if (i != cur_t)
        {
            adj[n - 1].push_back(i);
            adj[i].push_back(n - 1);
            residual_capacity[i][n - 1] = win[cur_t] + remaining[cur_t] - win[i];
        }
    }
    int total_games = 0;

    // connecting match vertices with source and team vertices
    for (int i = 0, k = t; i < t; i++)
    {
        for (int j = i + 1; j < t; j++)
        {
            if (i != cur_t && j != cur_t)
            {
                // connecting with source
                adj[n - 2].push_back(k);
                adj[k].push_back(n - 2);
                residual_capacity[n - 2][k] = game[i][j];

                // connecting with team vertices
                adj[k].push_back(i);
                adj[i].push_back(k);
                residual_capacity[k][i] = game[i][j];

                adj[k].push_back(j);
                adj[j].push_back(k);
                residual_capacity[k][j] = game[i][j];

                total_games += game[i][j];
                k++;
            }
        }
    }
    return total_games != max_flow(n - 2, n - 1);
}

void mout(vector<pair<int, vector<int>>> eliminated_team)
{
    ofstream out("output.txt");
    for (int i = 0; i < eliminated_team.size(); i++)
    {
        int ei = eliminated_team[i].first;
        vector<int> teams = eliminated_team[i].second;
        out << team_name[ei] << " is eliminated.\n";
        out << "They can win at most " << win[ei] << " + " << remaining[ei] << " = " << win[ei] + remaining[ei] << " games.\n";
        int won = 0;
        int tn = teams.size();
        for (int i = 0; i < tn; i++)
        {
            won += win[teams[i]];
            if (i)
            {
                if (i == tn - 1)
                {
                    out << " and ";
                }
                else
                {
                    out << ", ";
                }
            }
            out << team_name[teams[i]];
        }
        out << " have already won a total of " << won << " games.\n";
        int lft = 0;
        for (int i = 0; i < tn; i++)
        {
            for (int j = i + 1; j < tn; j++)
            {
                lft += game[teams[i]][teams[j]];
            }
        }
        out << "They play each other " << lft << " times.\n";
        out << "So on average, each of the team wins " << won + lft << "/" << tn << " = " << 1.0 * (won + lft) / tn << " games.\n\n";
    }
}

void min()
{
    ifstream in("input.txt");
    in >> t;
    // number of vertices in the flow network
    n = t + 2 + (t - 1) * (t - 2) / 2;

    team_name.assign(t, "");
    win.assign(t, -1);
    loss.assign(t, -1);
    remaining.assign(t, -1);
    game.assign(t, vector<int>(t));

    for (int i = 0; i < t; i++)
    {
        in >> team_name[i] >> win[i] >> loss[i] >> remaining[i];
        for (int j = 0; j < t; j++)
        {
            in >> game[i][j];
        }
    }
}

int main()
{
    min();
    vector<pair<int, vector<int>>> eliminated_team;
    for (int i = 0; i < t; i++)
    {
        if (is_eliminated(i))
        {
            eliminated_team.push_back({i, vector<int>()});
            calc_mincut(n - 2);
            for (int j = 0; j < t; j++)
            {
                if (in_source_segment[j])
                {
                    eliminated_team.back().second.push_back(j);
                }
            }
        }
    }
    mout(eliminated_team);
    return 0;
}