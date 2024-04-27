#include <iostream>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <bitset>

using namespace std;

struct HuffmanNode {
    char data;
    int frequency;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct CompareNodes {
    bool operator()(HuffmanNode* const& a, HuffmanNode* const& b) {
        return a->frequency > b->frequency;
    }
};

HuffmanNode* buildHuffmanTree(unordered_map<char, int>& freqMap) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;

    for (auto& pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        HuffmanNode* newNode = new HuffmanNode('$', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    return pq.top();
}

void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (root == nullptr) return;

    if (root->data != '$') {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

void writeCompressedData(const string& inputFile, const string& outputFile, unordered_map<char, string>& huffmanCodes) {
    ifstream inFile(inputFile);
    ofstream outFile(outputFile, ios::binary);

    char ch;
    string encodedData = "";

    while (inFile.get(ch)) {
        encodedData += huffmanCodes[ch];
    }

    while (encodedData.length() % 8 != 0) {
        encodedData += '0';
    }

    int len = encodedData.length();
    outFile.write(reinterpret_cast<const char*>(&len), sizeof(int));

    for (size_t i = 0; i < encodedData.length(); i += 8) {
        string byte = encodedData.substr(i, 8);
        char c = static_cast<char>(stoi(byte, nullptr, 2));
        outFile.write(&c, sizeof(char));
    }

    inFile.close();
    outFile.close();
}

string readCompressedData(const string& compressedFile) {
    ifstream inFile(compressedFile, ios::binary);
    if (!inFile) {
        cerr << "Error: Unable to open compressed file!" << endl;
        exit(1);
    }

    int len;
    inFile.read(reinterpret_cast<char*>(&len), sizeof(int));

    char ch;
    string encodedData = "";
    while (inFile.get(ch)) {
        encodedData += bitset
        <8>(static_cast<unsigned char>(ch)).to_string();
    }

    encodedData = encodedData.substr(0, len);

    inFile.close();
    return encodedData;
}

string decodeHuffmanData(const string& encodedData, HuffmanNode* root) {
    string decodedData = "";
    HuffmanNode* curr = root;

    for (char bit : encodedData) {
        if (bit == '0') {
            curr = curr->left;
        } else {
            curr = curr->right;
        }

        if (curr->left == nullptr && curr->right == nullptr) {
            decodedData += curr->data;
            curr = root;
        }
    }

    return decodedData;
}

void writeDecompressedData(const string& decompressedData, const string& outputFile) {
    ofstream outFile(outputFile);
    if (!outFile) {
        cerr << "Error: Unable to open output file!" << endl;
        exit(1);
    }

    outFile << decompressedData;

    outFile.close();
}

int main() {
    string inputFile = "input.txt";
    string compressedFile = "compressed.txt";
    string decompressedFile = "decompressed.txt";

    unordered_map<char, int> freqMap;

    ifstream inFile(inputFile);
    if (!inFile) {
        cerr << "Error: Unable to open input file!" << endl;
        return 1;
    }

    char ch;
    while (inFile.get(ch)) {
        freqMap[ch]++;
    }
    inFile.close();

    HuffmanNode* root = buildHuffmanTree(freqMap);

    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    writeCompressedData(inputFile, compressedFile, huffmanCodes);
    cout << "Compression successful!" << endl;

    string encodedData = readCompressedData(compressedFile);

    string decodedData = decodeHuffmanData(encodedData, root);

    writeDecompressedData(decodedData, decompressedFile);
    cout << "Decompression successful!" << endl;

    return 0;
}
