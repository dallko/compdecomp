#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string decompressRLE(const string& data) {
    string decompressedData = "";
    int count = 0;
    string num = "";
    for (char ch : data) {
        if (isdigit(ch)) {
            num += ch;
        } else {
            if (!num.empty()) {
                count = stoi(num);
                num = "";
            }
            for (int i = 0; i < count; ++i) {
                decompressedData += ch;
            }
        }
    }
    return decompressedData;
}

void writeDecompressedData(const string& compressedFile, const string& outputFile) {
    ifstream inFile(compressedFile);
    ofstream outFile(outputFile);

    if (!inFile) {
        cerr << "Error: Unable to open input file!" << endl;
        return;
    }

    if (!outFile) {
        cerr << "Error: Unable to open output file!" << endl;
        inFile.close();
        return;
    }

    string data;
    getline(inFile, data);

    string decompressedData = decompressRLE(data);

    outFile << decompressedData;

    inFile.close();
    outFile.close();

    cout << "Decompression successful!" << endl;
}

int main() {
    string compressedFile = "compressed.txt";
    string decompressedFile = "decompressed.txt";

    writeDecompressedData(compressedFile, decompressedFile);

    return 0;
}
