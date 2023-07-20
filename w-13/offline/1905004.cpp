/*BISMILLAH
THE WHITE WOLF
NO DREAM IS TOO BIG AND NO DREAMER IS TOO SMALL*/

#include <bits/stdc++.h>
using namespace std;

#define ZERO '0'
#define NONZERO 'X'
#define NONE '.'

class BandMatrix
{
    int n, fixed_col_n, fixed_row_n, branch_depth, branch_pos;
    vector<vector<char>> mat;

public:
    BandMatrix(int n, int fixed_col_n, int fixed_row_n, int branch_depth, int branch_pos);
    void inmat();
    void set_mat(vector<vector<char>> mat);
    void printmat();
    int get_lower_bound();
    int get_n();
    int get_fixed_col_n();
    int get_fixed_row_n();
    int get_branch_depth();
    int get_branch_pos();
    vector<vector<char>> get_mat();
};

class Compare
{
public:
    bool operator()(BandMatrix a, BandMatrix b)
    {
        if (a.get_lower_bound() > b.get_lower_bound())
        {
            return true;
        }
        else if (a.get_lower_bound() < b.get_lower_bound())
        {
            return false;
        }
        else if (a.get_branch_depth() < b.get_branch_depth())
        {
            return true;
        }
        else if (a.get_branch_depth() > b.get_branch_depth())
        {
            return false;
        }
        return a.get_branch_pos() < b.get_branch_pos();
    }
};

BandMatrix::BandMatrix(int n, int fixed_col_n, int fixed_row_n, int branch_depth, int branch_pos)
{
    this->n = n;
    this->fixed_col_n = fixed_col_n;
    this->fixed_row_n = fixed_row_n;
    this->branch_depth = branch_depth;
    this->branch_pos = branch_pos;
    mat.assign(n, vector<char>(n, NONE));
}

void BandMatrix::inmat()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> mat[i][j];
        }
    }
}

void BandMatrix::set_mat(vector<vector<char>> mat)
{
    this->mat = mat;
    this->n = mat.size();
}

void BandMatrix::printmat()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << mat[i][j];
        }
        cout << "\n";
    }
}

int BandMatrix::get_lower_bound()
{
    int lower_bound = 1;
    // unfixed rows
    for (int i = fixed_row_n; i < n; i++)
    {
        int non_zero_count = 0;
        for (int j = fixed_col_n; j < n; j++)
        {
            non_zero_count += (mat[i][j] == NONZERO);
        }
        lower_bound = max(lower_bound, (non_zero_count + 1) / 2);
    }
    // cout << "after unfixed rows: " << lower_bound << "\n";
    // unfixed cols
    for (int j = fixed_col_n; j < n; j++)
    {
        int non_zero_count = 0;
        for (int i = fixed_row_n; i < n; i++)
        {
            non_zero_count += (mat[i][j] == NONZERO);
        }
        lower_bound = max(lower_bound, (non_zero_count + 1) / 2);
    }
    // cout << "after unfixed cols: " << lower_bound << "\n";
    // fixed cols
    for (int j = 0; j < fixed_col_n; j++)
    {
        int non_zero_count = 0, first_non_zero = -1;
        for (int i = 0; i < n; i++)
        {
            if (i < j)
            {
                if (first_non_zero == -1 && mat[i][j] == NONZERO)
                {
                    first_non_zero = i;
                }
            }
            else if (i == j)
            {
                if (first_non_zero != -1)
                {
                    lower_bound = max(lower_bound, j - first_non_zero + 1);
                }
            }
            else if (i >= fixed_row_n)
            {
                non_zero_count += (mat[i][j] == NONZERO);
            }
        }
        if (non_zero_count)
        {
            if (j < fixed_row_n)
            {
                lower_bound = max(lower_bound, fixed_row_n - j + non_zero_count);
            }
            else
            {
                if (mat[j][j] == NONZERO)
                {
                    lower_bound = max(lower_bound, non_zero_count + 1);
                }
                else
                {
                    lower_bound = max(lower_bound, non_zero_count);
                }
            }
        }
    }
    // cout << "after fixed cols: " << lower_bound << "\n";
    // fixed rows
    for (int i = 0; i < fixed_row_n; i++)
    {
        int non_zero_count = 0, first_non_zero = -1;
        for (int j = 0; j < n; j++)
        {
            if (j < i)
            {
                if (first_non_zero == -1 && mat[i][j] == NONZERO)
                {
                    first_non_zero = j;
                }
            }
            else if (j == i)
            {
                if (first_non_zero != -1)
                {
                    lower_bound = max(lower_bound, i - first_non_zero + 1);
                }
            }
            else if (j >= fixed_col_n)
            {
                non_zero_count += (mat[i][j] == NONZERO);
            }
        }
        if (non_zero_count)
        {
            lower_bound = max(lower_bound, fixed_col_n - i + non_zero_count);
        }
    }
    // cout << "after fixed rows: " << lower_bound << "\n";
    return lower_bound;
}

int BandMatrix::get_n()
{
    return n;
}

int BandMatrix::get_fixed_col_n()
{
    return fixed_col_n;
}

int BandMatrix::get_fixed_row_n()
{
    return fixed_row_n;
}

int BandMatrix::get_branch_depth()
{
    return branch_depth;
}

int BandMatrix::get_branch_pos()
{
    return branch_pos;
}

vector<vector<char>> BandMatrix::get_mat()
{
    return mat;
}

vector<vector<char>> move_col(vector<vector<char>> gmat, int from, int to)
{
    int n = gmat.size();
    vector<vector<char>> rmat(gmat);
    for (int i = 0; i < n; i++)
    {
        rmat[i][to] = gmat[i][from];
    }
    for (int j = to; j < from; j++)
    {
        for (int i = 0; i < n; i++)
        {
            rmat[i][j + 1] = gmat[i][j];
        }
    }
    return rmat;
}

vector<vector<char>> move_row(vector<vector<char>> gmat, int from, int to)
{
    int n = gmat.size();
    vector<vector<char>> rmat(gmat);
    for (int j = 0; j < n; j++)
    {
        rmat[to][j] = gmat[from][j];
    }
    for (int i = to; i < from; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rmat[i + 1][j] = gmat[i][j];
        }
    }
    return rmat;
}

void solve(int t)
{
    int n;
    cin >> n;
    BandMatrix bm(n, 0, 0, 0, 0);
    bm.inmat();
    int bandwidth = n;
    vector<vector<char>> reduced_mat = bm.get_mat();
    priority_queue<BandMatrix, vector<BandMatrix>, Compare> pq;
    pq.push(bm);
    while (!pq.empty())
    {
        BandMatrix cm = pq.top();
        pq.pop();
        int lower_bound = cm.get_lower_bound();
        if (bandwidth <= lower_bound)
        {
            break;
        }
        int fixed_col_n = cm.get_fixed_col_n();
        int fixed_row_n = cm.get_fixed_row_n();
        int branch_depth = cm.get_branch_depth();
        // n-1 cols and rows are fixed
        if (fixed_col_n == fixed_col_n && fixed_col_n >= n - 1)
        {
            if (bandwidth > lower_bound)
            {
                bandwidth = lower_bound;
                reduced_mat = cm.get_mat();
            }
        }
        // fixing another col
        else if (fixed_col_n == fixed_row_n)
        {
            for (int j = fixed_col_n; j < n; j++)
            {
                BandMatrix nm = BandMatrix(n, fixed_col_n + 1, fixed_row_n, branch_depth + 1, j - fixed_col_n);
                nm.set_mat(move_col(cm.get_mat(), j, fixed_col_n));
                pq.push(nm);
            }
        }
        // fixing another row
        else
        {
            for (int i = fixed_row_n; i < n; i++)
            {
                BandMatrix nm = BandMatrix(n, fixed_col_n, fixed_row_n + 1, branch_depth + 1, i - fixed_row_n);
                nm.set_mat(move_row(cm.get_mat(), i, fixed_row_n));
                pq.push(nm);
            }
        }
    }
    cout << "\nbandwidth: " << bandwidth << "\n";
    cout << "reduced matrix:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << reduced_mat[i][j];
        }
        cout << "\n";
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int t = 1;
    // cin >> t;
    for (int i = 1; i <= t; i++)
    {
        solve(i);
    }
    return 0;
}