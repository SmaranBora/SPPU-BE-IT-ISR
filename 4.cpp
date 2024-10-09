#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <string>

using namespace std;

// Function to calculate precision and recall
pair<float, float> calculate_precision_recall(const set<string>& answer_set, const set<string>& relevant_docs) {
    // Intersection of retrieved documents and relevant documents
    set<string> relevant_retrieved;
    for (const auto& doc : answer_set) {
        if (relevant_docs.find(doc) != relevant_docs.end()) {
            relevant_retrieved.insert(doc);
        }
    }

    // Calculate precision and recall
    float precision = answer_set.size() > 0 ? (float)relevant_retrieved.size() / answer_set.size() : 0;
    float recall = relevant_docs.size() > 0 ? (float)relevant_retrieved.size() / relevant_docs.size() : 0;

    return {precision, recall};
}

// Function to get user input for documents
set<string> input_documents(const string& prompt) {
    cout << prompt << endl;
    string input;
    getline(cin, input);

    set<string> docs;
    stringstream ss(input);
    string doc;

    while (getline(ss, doc, ',')) {
        docs.insert(doc);  // Add document to set, automatically removing duplicates
    }

    return docs;
}

int main() {
    // Input for retrieved documents (answer set)
    set<string> answer_set_A = input_documents("Enter the retrieved documents for the query (separated by commas):");

    // Input for relevant documents
    set<string> relevant_docs_Rq1 = input_documents("Enter the relevant documents for the query (separated by commas):");

    // Calculate precision and recall
    auto [precision, recall] = calculate_precision_recall(answer_set_A, relevant_docs_Rq1);

    // Display precision and recall
    cout << "\nPrecision: " << precision << endl;
    cout << "Recall: " << recall << endl;

    return 0;
}
