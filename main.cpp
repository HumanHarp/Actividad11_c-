#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

struct Document {
    int id;
    string path;
};

void createDocumentFile(const vector<string>& documentPaths, const string& outputFile) {
    ofstream outFile(outputFile);
    if (!outFile) {
        cerr << "Error: No se pudo crear el archivo " << outputFile << endl;
        return;
    }
    int id = 1;
    for (const auto& path : documentPaths) {
        outFile << id << "\t" << path << endl;
        id++;
    }
    outFile.close();
}

void updatePostingFile(const string& postingFile, const string& updatedFile, const unordered_map<int, float>& tokenWeights) {
    ifstream inFile(postingFile);
    ofstream outFile(updatedFile);
    if (!inFile || !outFile) {
        cerr << "Error: No se pudo abrir uno de los archivos." << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        int docID = rand() % 100 + 1;
        float weight = 1.0;
        auto it = tokenWeights.find(docID);
        if (it != tokenWeights.end()) {
            weight = it->second;
        }
        outFile << line << "\t" << docID << "\t" << weight << endl;
    }
    inFile.close();
    outFile.close();
}

void logProcessingTime(const vector<string>& documentPaths, const string& logFile) {
    ofstream logOut(logFile);
    if (!logOut) {
        cerr << "Error: No se pudo crear el archivo de log " << logFile << endl;
        return;
    }

    auto start = chrono::high_resolution_clock::now();

    for (const auto& path : documentPaths) {
        auto fileStart = chrono::high_resolution_clock::now();
        cout << "Procesando archivo: " << path << endl;
        this_thread::sleep_for(chrono::milliseconds(50));
        auto fileEnd = chrono::high_resolution_clock::now();
        chrono::duration<double> fileDuration = fileEnd - fileStart;
        logOut << "Archivo: " << path << " - Tiempo: " << fileDuration.count() << " segundos" << endl;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> totalDuration = end - start;
    logOut << "Tiempo total: " << totalDuration.count() << " segundos" << endl;

    logOut.close();
}

int main() {
    vector<string> documentPaths = {"doc1.txt", "doc2.txt", "doc3.txt"};
    unordered_map<int, float> tokenWeights = {{1, 0.5}, {2, 1.2}, {3, 0.8}};

    string documentFile = "documents.txt";
    string postingFile = "posting.txt";
    string updatedPostingFile = "updated_posting.txt";
    string logFile = "a11_123456.txt";

    createDocumentFile(documentPaths, documentFile);
    updatePostingFile(postingFile, updatedPostingFile, tokenWeights);
    logProcessingTime(documentPaths, logFile);

    return 0;
}
