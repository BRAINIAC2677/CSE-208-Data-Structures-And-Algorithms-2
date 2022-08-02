#ifndef RANDOM_WORD_GENERATOR
#define RANDOM_WORD_GENERATOR

#include <bits/stdc++.h>
using namespace std;
#include <experimental/random>
using namespace experimental;

class RandomWordGenerator
{
    int min_length, max_length;

public:
    RandomWordGenerator(int min_length, int max_length)
    {
        this->min_length = min_length;
        this->max_length = max_length;
    }
    string generateWord()
    {
        string word;
        int len = randint(min_length, max_length);
        for (int i = 0; i < len; i++)
        {
            word += (char)randint((int)'a', (int)'z');
        }
        return word;
    }
    vector<string> generateWords(int num_of_words)
    {
        vector<string> words;
        for (int i = 0; i < num_of_words; i++)
        {
            words.push_back(generateWord());
        }
        return words;
    }
    vector<string> generateUniqueWords(int num_of_words)
    {
        vector<string> words;
        set<string> unique_words;
        while (unique_words.size() < num_of_words)
        {
            string word = generateWord();
            if (unique_words.find(word) == unique_words.end())
            {
                unique_words.insert(word);
                words.push_back(word);
            }
        }
        return words;
    }

    vector<string> selectUniqueWords(vector<string> from, int n)
    {
        n = min(n, (int)from.size());
        vector<string> words;
        set<string> unique_words;
        while (unique_words.size() < n)
        {
            int index = randint(0, (int)from.size() - 1);
            string word = from[index];
            if (unique_words.find(word) == unique_words.end())
            {
                unique_words.insert(word);
                words.push_back(word);
            }
        }
        return words;
    }
};

#endif