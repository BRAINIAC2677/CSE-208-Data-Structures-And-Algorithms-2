/*BISMILLAH
THE WHITE WOLF
NO DREAM IS TOO BIG AND NO DREAMER IS TOO SMALL*/

#include <bits/stdc++.h>
using namespace std;

//=========================================== debugger ================================================
void __print(int x) { cerr << x; }
void __print(long x) { cerr << x; }
void __print(long long x) { cerr << x; }
void __print(unsigned x) { cerr << x; }
void __print(unsigned long x) { cerr << x; }
void __print(unsigned long long x) { cerr << x; }
void __print(float x) { cerr << x; }
void __print(double x) { cerr << x; }
void __print(long double x) { cerr << x; }
void __print(char x) { cerr << '\'' << x << '\''; }
void __print(const char *x) { cerr << '\"' << x << '\"'; }
void __print(const string &x) { cerr << '\"' << x << '\"'; }
void __print(bool x) { cerr << (x ? "true" : "false"); }

template <typename T, typename V>
void __print(const pair<T, V> &x)
{
    cerr << '{';
    __print(x.first);
    cerr << ',';
    __print(x.second);
    cerr << '}';
}
template <typename T>
void __print(const T &x)
{
    int f = 0;
    cerr << '{';
    for (auto &i : x)
        cerr << (f++ ? "," : ""), __print(i);
    cerr << "}";
}
void _print() { cerr << "]\n"; }
template <typename T, typename... V>
void _print(T t, V... v)
{
    __print(t);
    if (sizeof...(v))
        cerr << ", ";
    _print(v...);
}
#ifndef ONLINE_JUDGE
#define debug(x...)               \
    cerr << "[" << #x << "] = ["; \
    _print(x)
#else
#define debug(x...)
#endif
//=========================================== end of debugger ================================================

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<long long> vll;
typedef vector<int> vi;

#define io ios_base::sync_with_stdio(false)
#define pb push_back
#define is_set(n, i) bool(n & (1LL << i))
#define bit_set(n, i) (n | (1LL << i))
#define bit_unset(n, i) (n & !(1LL << i))
#define PI 2 * acos(0.0)
#define all(r) (r).begin(), (r).end()
#define rev(r) (r).rbegin(), (r).rend()
#define dbg(a) cout << #a << " ->->->-> " << a << "\n"

int dirx[] = {1, -1, 0, 0, 1, 1, -1, -1}, diry[] = {0, 0, 1, -1, 1, -1, 1, -1};
const int maxn = 100009;
const int maxv = 1000000009;
const int mod = 1000000007;
const long long int inf = 1000000000000000000;
//=============================================ASIFAZAD==============================================//

#define ZERO 'o'
#define NONZERO 'x'
#define NONE '.'

class BandMatrix
{
    int n, fixed_col_n, fixed_row_n, branch_depth, branch_pos;
    char **mat;

public:
    BandMatrix(int n, int fixed_col_n, int fixed_row_n, int branch_depth, int branch_pos);
    void inmat();
    void printmat();
    int get_lower_bound();
    int get_n();
    int get_fixed_col_n();
    int get_fixed_row_n();
    int get_branch_depth();
    int get_branch_pos();
    ~BandMatrix();
};

BandMatrix::BandMatrix(int n, int fixed_col_n, int fixed_row_n, int branch_depth, int branch_pos)
{
    this->n = n;
    this->fixed_col_n = fixed_col_n;
    this->fixed_row_n = fixed_row_n;
    this->branch_depth = branch_depth;
    this->branch_pos = branch_pos;
    mat = new char *[n];
    for (int i = 0; i < n; i++)
    {
        mat[i] = new char[n];
        for (int j = 0; j < n; j++)
            mat[i][j] = NONE;
    }
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

BandMatrix::~BandMatrix()
{
    for (int i = 0; i < n; i++)
    {
        delete[] mat[i];
    }
    delete[] mat;
}

void solve(int t)
{
    int n, fixed_col_n, fixed_row_n;
    cin >> n >> fixed_col_n >> fixed_row_n;
    BandMatrix bm(n, fixed_col_n, fixed_row_n, 0, 0);
    bm.inmat();
    cout << "\n";
    bm.printmat();
    cout << bm.get_lower_bound() << "\n";
}

int main()
{
    io;
    ifstream in("input.txt");
    ofstream out("output.txt");
    int t;
    cin >> t;
    for (int i = 1; i <= t; i++)
    {
        solve(i);
    }
    return 0;
}