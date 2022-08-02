#include "red_black_tree.h"
using namespace rbt;

#include <bits/stdc++.h>
using namespace std;

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n;
    in >> n;
    out << n << "\n";
    RedBlackTree<int> LalKalaGach(INT_MAX);
    for (int i = 0; i < n; i++)
    {
        int e, x;
        in >> e >> x;
        out << e << " " << x << " ";
        if (e == 0)
        {
            if (LalKalaGach.remove(x) == nullptr)
            {
                out << "0\n";
            }
            else
            {
                out << "1\n";
            }
        }
        else if (e == 1)
        {
            if (LalKalaGach.search(x) == nullptr)
            {
                LalKalaGach.insert(x);
                out << "1\n";
            }
            else
            {
                out << "0\n";
            }
        }
        else if (e == 2)
        {
            if (LalKalaGach.search(x) == nullptr)
            {
                out << "0\n";
            }
            else
            {
                out << "1\n";
            }
        }
        else if (e == 3)
        {
            out << LalKalaGach.noOfKeysLessThan(x) << "\n";
        }
    }
    return 0;
}