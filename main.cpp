#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string compressRLE(const string& data) {
    string compressedData = "";
    int count = 1;
    for (int i = 0; i < data.length(); ++i) {
        if (i + 1 < data.length() && data[i] == data[i + 1]) {
            count++;
        } else {
            compressedData += to_string(count) + data[i];
            count = 1;
        }
    }
    return compressedData;
}

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

void writeCompressedData(const string& inputFile, const string& outputFile) {
    ifstream inFile(inputFile);
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

    string compressedData = compressRLE(data);

    outFile << compressedData;

    inFile.close();
    outFile.close();

    cout << "Compression successful!" << endl;
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
    string inputFile = "input.txt";
    string compressedFile = "compressed.txt";
    string decompressedFile = "decompressed.txt";

    writeCompressedData(inputFile, compressedFile);
    writeDecompressedData(compressedFile, decompressedFile);

    return 0;
}
