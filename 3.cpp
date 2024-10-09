#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Function to clean up a word by removing punctuation and converting to lowercase
string cleanWord(const string &word) {
    string cleaned = word;
    cleaned.erase(remove_if(cleaned.begin(), cleaned.end(), ::ispunct), cleaned.end());
    transform(cleaned.begin(), cleaned.end(), cleaned.begin(), ::tolower);
    return cleaned;
}


string stemWord(const string &word) {
    string stemmed = word;
   
    // Remove common suffixes
    if (stemmed.size() > 4) { // Only stem words with length > 4 to avoid excessive shortening
        if (stemmed.substr(stemmed.size() - 3) == "ing")
            stemmed = stemmed.substr(0, stemmed.size() - 3);
        else if (stemmed.substr(stemmed.size() - 2) == "ed")
            stemmed = stemmed.substr(0, stemmed.size() - 2);
        else if (stemmed.substr(stemmed.size() - 1) == "s")
            stemmed = stemmed.substr(0, stemmed.size() - 1);
    }
    return stemmed;
}

class InvertedIndex {
    map<string, vector<int>> index;  // The inverted index

public:
    // Function to build the index from a file
    void buildIndex(const string &filename) {
        ifstream file(filename);
        string line;
        int lineNumber = 0;

        while (getline(file, line)) {
            lineNumber++;
            stringstream ss(line);
            string word;
            
            while (ss >> word) {
                word = cleanWord(word);     // Clean the word
                word = stemWord(word);      // Stem the word
                index[word].push_back(lineNumber); // Add line number to the word's occurrence list
            }
        }
        file.close();
    }

    // Function to search for a word in the index
    void search(const string &query) {
        string cleanedQuery = cleanWord(query);
        string stemmedQuery = stemWord(cleanedQuery);

        if (index.find(stemmedQuery) != index.end()) {
            cout << "The word '" << query << "' (stemmed to '" << stemmedQuery << "') is found at lines: ";
            for (int lineNum : index[stemmedQuery]) {
                cout << lineNum << " ";
            }
            cout << endl;
        } else {
            cout << "The word '" << query << "' was not found in the document." << endl;
        }
    }
    void printIndex() {
        cout << "Inverted Index:\n";
        for (const auto &entry : index) {
            cout << entry.first << ": ";
            for (int lineNum : entry.second) {
                cout << lineNum << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    InvertedIndex index;
    string filename = "3a.txt";  // Name of the text file

    // Build the inverted index
    index.buildIndex(filename);
    index.printIndex();
    // Perform searches
    string query;
    cout << "Enter a word to search: ";
    cin >> query;
    index.search(query);

    return 0;
}
