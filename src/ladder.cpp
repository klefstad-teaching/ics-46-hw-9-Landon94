#include "ladder.h"
#include <cmath>

using namespace std;

void error(string word1, string word2, string msg) {
    cout << word1 << ", " << word2 << " " << msg << endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d) {
    int s1 = str1.size();
    int s2 = str2.size();
    int offset = abs(s1 - s2);
    if (offset > d) {
        return false;
    }
    int difference = 0;

    if (s1 == s2) {
        for (int i = 0; i<s2; ++i) {
            if (str1[i] != str2[i]) {
                ++difference;
                if (difference > 1) {
                    return false;
                }
            }
        }
        return true;
    } else {
        string high;
        string low;
        if (s1 < s2) {
            low = str1;
            high = str2;
        } else {
            high = str1;
            low = str2;
        }
        int h = 0;
        int l = 0;
        while (h < high.size() && l < low.size()){
            if (high[h] == low[l]) {
                ++h;
                ++l;
            } else {
                ++difference;
                if (difference > 1) {
                    return false;
                }
                ++h;
            }
        }

        difference += (l - h);
        return difference <= d;
    }
}


bool is_adjacent(const string& word1, const string& word2) {
    return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list) {
    if (word_list.find(end_word) == word_list.end()) {
        return {};
    }
    queue<vector<string>> ladder_queue;
    ladder_queue.push({begin_word});
    
    set<string> visited;
    visited.insert(begin_word);
    
    while (!ladder_queue.empty()) {
        vector<string> ladder = ladder_queue.front();
        ladder_queue.pop();
        string last_word = ladder.back();
        
        for(string word : word_list) {
            if (is_adjacent(last_word, word)) {
                if (visited.find(word) == visited.end()) {
                    visited.insert(word);
                    vector<string> new_ladder = ladder;
                    new_ladder.push_back(word);
                    if (word == end_word) {
                        return new_ladder;
                    }
                    ladder_queue.push(new_ladder);
                }
            }

        }
    }
    return {};
}

void load_words(set<string> & word_list, const string& file_name) {
    ifstream file(file_name);
    string word;
    while(file >> word) {
        word_list.insert(word);
    }
    file.close();
}

void print_word_ladder(const vector<string>& ladder) {
    if (ladder.size() == 0) {
        cout << "No word ladder found" << endl;
        return;
    }
    for (string x: ladder) {
        cout << x << ' ';
    }
    cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder() {
    set<string> word_list;

    load_words(word_list, "words.txt");
    my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
    my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}