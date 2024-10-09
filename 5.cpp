#include <iostream>
#include <vector>
#include <set>
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

// Function to calculate harmonic mean (F-measure)
float calculate_f_measure(float precision, float recall) {
    return (precision + recall > 0) ? 2 * (precision * recall) / (precision + recall) : 0;
}

// Function to calculate E-measure (alpha = 0.5 by default)
float calculate_e_measure(float precision, float recall, float alpha = 0.5) {
    return (precision + recall > 0) ? 1.0 - (1.0 / ((alpha / recall) + ((1 - alpha) / precision))) : 0;
}

int main() {
    // Hardcoded input for retrieved documents (answer set)
    set<string> answer_set_A = {"d123", "d84", "d56", "d6", "d8", "d9", "d511", "d129", "d187", "d25", "d38", "d48", "d250", "d113", "d3"};

    // Hardcoded input for relevant documents
    set<string> relevant_docs_Rq1 = {"d123", "d56", "d9", "d25", "d3"};

    // Calculate precision and recall
    auto [precision, recall] = calculate_precision_recall(answer_set_A, relevant_docs_Rq1);

    // Calculate F-measure
    float f_measure = calculate_f_measure(precision, recall);

    // Calculate E-measure
    float e_measure = calculate_e_measure(precision, recall);

    // Display precision, recall, F-measure, and E-measure
    cout << "\nPrecision: " << precision << endl;
    cout << "Recall: " << recall << endl;
    cout << "F-measure (Harmonic Mean): " << f_measure << endl;
    cout << "E-measure: " << e_measure << endl;

    return 0;
}
