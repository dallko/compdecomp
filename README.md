I used the vscode compiler in my work, when you press 'run' the code automatically adds files 'compressed.txt' and 'decompressed.txt' where you can find outputs.

1.Compression and Decompression Algorithms
Compression Algorithm (Run-Length Encoding - RLE):
-Explanation: Run-Length Encoding (RLE) is a simple form of data compression that replaces sequences of the same data value with a single value and count.
-Implementation Details:
The 'compressRLE' function iterates over each character in the input string.
It counts consecutive occurrences of the same character.
When a different character is encountered or the end of the string is reached, it appends the count and the character to the compressed string.
-Example: "AAABBBCCC" would be compressed to "3A3B3C"

-Decompression Algorithm (Reverse Run-Length Encoding):
-Explanation: Reverse Run-Length Encoding decompresses the compressed string by repeating each character according to the count.
Implementation Details:
The 'decompressRLE' function iterates over each character in the compressed string.
It constructs the decompressed string by repeating each character according to the count.
-Example: "3A3B3C" would be decompressed to "AAABBBCCC".


2. Major Functions and Code Blocks
'compressRLE' Function: Compresses input string using RLE.
'decompressRLE' Function: Decompresses a compressed string.
'writeCompressedData' Function: Reads data from an input file, compresses it, and writes the compressed data to an output file.
'writeDecompressedData' Function: Reads compressed data from a file, decompresses it, and writes the decompressed data to an output file.
'main' Function: Entry point of the program. Calls compression and decompression functions.
3. Compression Technique Explanation
Run-Length Encoding (RLE):
A simple compression technique that reduces redundancy by representing repeated data with a count and a single value. It works well for data with long runs of repeated characters or symbols.

