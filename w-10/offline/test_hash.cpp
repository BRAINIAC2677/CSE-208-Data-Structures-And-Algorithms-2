#include "hash.h"
#include "random_word_generator.h"

#include <bits/stdc++.h>
using namespace std;

int uniqueHashValue(int no_of_key)
{
    RandomWordGenerator random_word_generator(7, 7);
    vector<string> words = random_word_generator.generateUniqueWords(no_of_key);
    ChainedHash chained_hash(10001);
    set<long long int> hash_values;
    for (int i = 0; i < no_of_key; i++)
    {
        hash_values.insert(chained_hash.polynomialHash(words[i], 41, 2 * no_of_key));
    }
    return (int)hash_values.size();
}

int main()
{
    int n;
    cout << "Enter the number of keys:\n";
    cin >> n;
    int no_of_hash_values = uniqueHashValue(n);
    cout << "Unique Hash Values: " << no_of_hash_values << "\n";
    cout << fixed << setprecision(2);
    cout << "Uniqueness: " << (double)no_of_hash_values / n << "%\n";
    return 0;
}