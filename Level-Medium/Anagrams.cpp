#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

using namespace std;

int main() {
    // Optimization for faster I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    // A map to store the frequency of each "sorted word" signature
    // Key: the sorted string (e.g., "acellr")
    // Value: count of words that match this signature
    unordered_map<string, int> anagram_counts;
    
    int max_subset_size = 0;

    for (int i = 0; i < N; ++i) {
        string word;
        cin >> word;

        // Create the canonical form by sorting the letters
        // "caller" -> "acellr"
        // "cellar" -> "acellr"
        string sorted_word = word;
        sort(sorted_word.begin(), sorted_word.end());

        // Increment the count for this anagram group
        anagram_counts[sorted_word]++;
        
        // Update the maximum size found so far
        if (anagram_counts[sorted_word] > max_subset_size) {
            max_subset_size = anagram_counts[sorted_word];
        }
    }

    cout << max_subset_size << endl;

    return 0;
}