#include "hash.h"
#include "random_word_generator.h"

#include <bits/stdc++.h>
using namespace std;
#include <experimental/random>
using namespace experimental;

int main()
{
    int hash_size = 102233;
    OpenHash open_hash(hash_size, DOUBLE);

    int batch_size = hash_size / 10;
    RandomWordGenerator random_word_generator(7, 7);

    vector<string> words = random_word_generator.generateUniqueWords(10 * batch_size);

    vector<string> search_words = random_word_generator.selectUniqueWords(words, batch_size);

    for (int k = 1; k < 10; k++)
    {
        for (int i = (k - 1) * batch_size; i < k * batch_size; i++)
        {
            open_hash.insert(words[i], i);
        }
        int before_probe_count = 0, after_probe_count = 0;
        int before_total_time = 0, after_total_time = 0;
        for (int i = 0; i < batch_size; i++)
        {
            auto start = chrono::high_resolution_clock::now();

            open_hash.search(search_words[i]);
            auto end = chrono::high_resolution_clock::now();
            before_total_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
            before_probe_count += open_hash.getNoOfLastProbes();
        }

        double before_avg_time = 1 * before_total_time / batch_size;
        double before_avg_probe_count = 1.0 * before_probe_count / batch_size;

        if (before_avg_probe_count > 2)
        {
            open_hash.rehashDouble(1);
            for (int i = 0; i < batch_size; i++)
            {
                auto start = chrono::high_resolution_clock::now();

                open_hash.search(search_words[i]);
                auto end = chrono::high_resolution_clock::now();
                after_total_time += chrono::duration_cast<chrono::nanoseconds>(end - start).count();
                before_probe_count += open_hash.getNoOfLastProbes();
            }
        }

        double after_avg_time = 1 * after_total_time / batch_size;
        double after_average_probe_count = 1.0 * after_probe_count / batch_size;

        cout << before_avg_probe_count << " " << before_avg_time << " " << after_average_probe_count << " " << after_avg_time << "\n";
    }

    return 0;
}