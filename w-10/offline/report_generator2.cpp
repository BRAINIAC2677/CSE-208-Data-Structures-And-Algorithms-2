#include "hash.h"
#include "random_word_generator.h"

#include <bits/stdc++.h>
using namespace std;
#include <experimental/random>
using namespace experimental;

int main()
{
    int hash_size = 102233;
    cout << "Give the hash size:\n";
    cin >> hash_size;

    int p;
    cout << "Enter 0 for linear probing, 1 for quadratic probing, 2 for double hashing:\n";
    cin >> p;
    p = max(p, 0);
    p = min(p, 2);
    OpenHash open_hash(hash_size, LINEAR);
    if (p == 0)
    {
        cout << "Linear probing\n";
        open_hash.setProbingType(LINEAR);
    }
    else if (p == 1)
    {
        cout << "Quadratic probing\n";
        open_hash.setProbingType(QUADRATIC);
    }
    else
    {
        cout << "Double hashing\n";
        open_hash.setProbingType(DOUBLE);
    }

    int batch_size = int(hash_size * 0.1);
    int mini_batch_size = int(batch_size * 0.1);

    RandomWordGenerator random_word_generator(7, 7);
    vector<string> words = random_word_generator.generateUniqueWords(9 * batch_size);

    // making load factor 0.4
    for (int i = 0; i < 3 * batch_size; i++)
    {
        open_hash.insert(words[i], i);
    }

    for (int k = 4; k <= 9; k++)
    {
        vector<string> batch;
        // increasing load factor by 0.1
        for (int i = (k - 1) * batch_size; i < k * batch_size; i++)
        {
            batch.push_back(words[i]);
            open_hash.insert(words[i], i);
        }

        vector<string> mini_batch = random_word_generator.selectUniqueWords(batch, mini_batch_size);

        double open_total_search_time1 = 0;
        int total_probe_count1 = 0;
        for (int i = 0; i < mini_batch_size; i++)
        {
            auto start = chrono::high_resolution_clock::now();
            open_hash.search(mini_batch[i]);
            auto end = chrono::high_resolution_clock::now();
            total_probe_count1 += open_hash.getNoOfLastProbes();
            open_total_search_time1 += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        }
        double open_average_search_time1 = open_total_search_time1 / mini_batch_size;
        double average_probe_count1 = 1.0 * total_probe_count1 / mini_batch_size;

        // new random mini batch
        mini_batch = random_word_generator.selectUniqueWords(batch, mini_batch_size);
        set<string> temp_mini_batch;
        for (int i = 0; i < mini_batch_size; i++)
        {
            temp_mini_batch.insert(mini_batch[i]);
        }

        // removing the mini batch from the hash table
        for (int i = 0; i < mini_batch_size; i++)
        {
            open_hash.remove(mini_batch[i]);
        }

        // mini_batch_complement is the vector of words that are not in the mini batch but are in the batch
        vector<string> mini_batch_complement;
        for (int i = 0; i < batch_size; i++)
        {
            if (temp_mini_batch.find(batch[i]) == temp_mini_batch.end())
            {
                mini_batch_complement.push_back(batch[i]);
            }
        }

        // mini_batch2 is formed taking half of the removed words from the batch and half of the words from the mini batch complement
        vector<string> mini_batch2 = random_word_generator.selectUniqueWords(mini_batch_complement, mini_batch_size / 2);
        for (int i = 0; mini_batch2.size() < mini_batch_size; i++)
        {
            mini_batch2.push_back(mini_batch[i]);
        }

        // finding average search time & average probe count again
        double open_total_search_time2 = 0;
        int total_probe_count2 = 0;
        for (int i = 0; i < mini_batch_size; i++)
        {
            auto start = chrono::high_resolution_clock::now();
            open_hash.search(mini_batch2[i]);
            auto end = chrono::high_resolution_clock::now();
            total_probe_count2 += open_hash.getNoOfLastProbes();
            open_total_search_time2 += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
        }
        double open_average_search_time2 = open_total_search_time2 / mini_batch_size;
        double average_probe_count2 = 1.0 * total_probe_count2 / mini_batch_size;

        // inserting the mini batch back into the hash table
        for (int i = 0; i < mini_batch_size; i++)
        {
            open_hash.insert(mini_batch[i], i);
        }
        cout << fixed << setprecision(2);
        cout << "load factor: " << open_hash.getLoadFactor() << "\n----------------------------\nBefore deletion:\n";
        cout << "Avg search time: " << open_average_search_time1 << " ns\n";
        cout << "Avg probe count: " << average_probe_count1 << "\n";
        cout << "After deletion:\n";
        cout << "Avg search time: " << open_average_search_time2 << " ns\n";
        cout << "Avg probe count: " << average_probe_count2 << "\n\n";
    }

    return 0;
}