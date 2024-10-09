#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Function to calculate the Dice Coefficient
double diceCoefficient(const unordered_set<string>& setA, const unordered_set<string>& setB) {
    if (setA.empty() || setB.empty()) return 0.0;

    int intersectionCount = 0;

    // Count common words
    for (const string& word : setA) {
        if (setB.find(word) != setB.end()) {
            intersectionCount++;
        }
    }

    return (2.0 * intersectionCount) / (setA.size() + setB.size());
}

// Function to read a document and return a set of unique words
unordered_set<string> readDocument(const string& filename) {
    ifstream file(filename);
    unordered_set<string> words;
    string word;

    if (file.is_open()) {
        while (file >> word) {
            // Convert to lowercase and remove punctuation
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());
            if (!word.empty()) {
                words.insert(word);
            }
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file " << filename << endl;
    }

    return words;
}

// Function to perform single-pass clustering
void singlePassClustering(const vector<string>& documents, double threshold) {
    vector<unordered_set<string>> clusters;

    for (const string& doc : documents) {
        unordered_set<string> words = readDocument(doc);
        bool foundCluster = false;

        for (auto& cluster : clusters) {
            // Calculate similarity
            if (diceCoefficient(words, cluster) >= threshold) {
                // Add words to the existing cluster
                cluster.insert(words.begin(), words.end());
                foundCluster = true;
                break;
            }
        }

        // Create a new cluster if no similar cluster is found
        if (!foundCluster) {
            clusters.push_back(words);
        }
    }

    // Print the clusters
    cout << "Clusters formed based on the documents:" << endl;
    for (size_t i = 0; i < clusters.size(); i++) {
        cout << "Cluster " << i + 1 << ": ";
        for (const string& word : clusters[i]) {
            cout << word << " ";
        }
        cout << endl;
    }
}

int main() {
    // List of document filenames
    vector<string> documents = {
        "2a.txt",  
        "2b.txt",
        "2c.txt",
        "2d.txt",
        "2e.txt"
    };

    double threshold = 0.5; // Similarity threshold for clustering
    singlePassClustering(documents, threshold);
    
    return 0;
}
