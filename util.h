//
// STARTER CODE: util.h
//
// Pedro Pardo
// UIN: 656286719
// University of Illinois, Chicago
// CS 251, Fall 2022
//
// This file will use HashMaps and Priority Queues to use Huffman Compression of text to create files of this compressed data.
// This file will be used to complete the menuOptions provided in main.cpp
//

#pragma once
#include <queue>
#include "hashmap.h"
// #include "mainprog.h"
// #include "bitstream.h"


typedef hashmap hashmapF;
typedef unordered_map <int, string> hashmapE;

struct HuffmanNode {
    int character;
    int count;
    HuffmanNode* zero;
    HuffmanNode* one;
};

struct compare
{
    bool operator()(const HuffmanNode *lhs,
        const HuffmanNode *rhs)
    {
        return lhs->count > rhs->count;
    }
};

//
// *This method frees the memory allocated for the Huffman tree.
//
void freeTree(HuffmanNode* node) {
    if(node == nullptr){ //base case if tree is empty
        return;
    }
    freeTree(node->zero); //go left
    freeTree(node->one); //go right
    delete node; //delete
    node = nullptr; //set "root" nack to null
}

//
// *This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
//
void buildFrequencyMap(string filename, bool isFile, hashmapF &map) {
    if(isFile == true){ //when the selection is file
        ifstream inFile(filename); //loads file
        char current;
        inFile.get(current); //gets the current key
        while(!inFile.eof()){ //while in the file
            int key = (int)current; //convers char into int
            if(map.containsKey(key) == true){ //while the map contains key
                int freq = map.get(key); //get the freq of current key
                freq++; //add one since found
                map.put(key,freq); //insert
            }
            else{ //if map doesnt have key
                int freq = 1; //give base freq
                map.put(key, freq); //insert to map
            }
            inFile.get(current); //get next
        }
        int key = PSEUDO_EOF; //when not in file
        map.put(key, 1); //make pseudo key
    }
    else{ // when its just text
        for(int i = 0; i < filename.length(); i++){ //search for the text 
            char key = (int)filename[i]; //convert to char
            if(map.containsKey(key) == true){ //checks if inside map
                int freq = map.get(key); //find freq in map
                freq++; //add one since found
                map.put(key,freq); //insert to map
            }
            else{ //not in map
                int freq = 1; //create base freq
                map.put(key, freq);
            }
        }
        int key = PSEUDO_EOF; //when key isnt found
        map.put(key, 1);
    }
    
}

//
// *This function builds an encoding tree from the frequency map.
//
HuffmanNode* buildEncodingTree(hashmapF &map) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, compare> pq; 
    for (int key : map.keys()){ //search keys in map
        HuffmanNode* node = new HuffmanNode; //create node based off data 
        node->character = key;
        node->count = map.get(key);
        node->zero = nullptr;
        node->one = nullptr;
        pq.push(node); //push into the priority queue
    }
    while(pq.size() != 1){ //while the priority_queue size isnt 1
        HuffmanNode* zero = pq.top(); //find top and store
        pq.pop(); //remove
        HuffmanNode* one = pq.top(); // find second
        pq.pop(); //remove
        HuffmanNode* top = new HuffmanNode; //create new node
        int newCount = zero->count + one->count; //create new count of both 
        top->count = newCount;
        top->character = NOT_A_CHAR;
        top->zero = zero;
        top->one = one;

        pq.push(top); //push linked into priority_queue
    }
   
    HuffmanNode* root = nullptr; //create root
    root = pq.top(); //set root to the top
    return root;  //return the root
}

//
// *Recursive helper function for building the encoding map.
//
void _buildEncodingMap(HuffmanNode* node, hashmapE &encodingMap, string str,
                       HuffmanNode* prev) {
    
    if(node == nullptr){ //check if tree is null
        return;
    }
    if(node->zero == nullptr && node->one == nullptr){ //checks if tree doesnt have leafs
        int key = node->character; //find key
        encodingMap[key] = str; //set key value to the string
        node = prev; //set prev node
        return;
    }
    str += "0"; //create string with 0 since left
    prev = node; //set prev to node working with
    node = node->zero; //go left
    _buildEncodingMap(node, encodingMap, str, prev);
    str.pop_back(); //pop the string
    str += "1"; //create string with 1 since right
    node = prev->one; //go right
    _buildEncodingMap(node, encodingMap, str, node);    
}

//
// *This function builds the encoding map from an encoding tree.
//
hashmapE buildEncodingMap(HuffmanNode* tree) {
    hashmapE encodingMap; //create map
    string str = ""; //set string
    _buildEncodingMap(tree, encodingMap, str, nullptr); //call helper
    return encodingMap;  //return map
}

//
// *This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
//
string encode(ifstream& input, hashmapE &encodingMap, ofbitstream& output,
              int &size, bool makeFile) {
    
    string encodeString = ""; char currChar;
    input.get(currChar); //get char from input
    while(!input.eof()){ //while there are still chars
        int currCharInt = (int)currChar; //convert to int
        string append = encodingMap.find(currCharInt)->second; 
        if(makeFile == true){
            for(int i = 0; i < append.size(); i++){ //get all chars in the string
                if(append[i] == '1') { //if char is 1
                    output.writeBit(1); //output 1
                } 
                else if (append[i] == '0') { //oif char is 0
                    output.writeBit(0); //output 0
                }
            }
        }
        encodeString += append; //add the created string to the main
        input.get(currChar); //continue to next
    }

    //if file runs out
    int key = PSEUDO_EOF;
    string append = encodingMap.find(key)->second; //find all psuedo keys
    encodeString += append;
    size = encodeString.size(); //update size paramrter 
    if(makeFile == true){
        for(int i = 0; i < append.size(); i++){ //get all chars in the string
            if(append[i] == '1') { //if char is 1
                output.writeBit(1); //output 1
            } 
            else if (append[i] == '0') { //oif char is 0
                output.writeBit(0); //output 0
            }
        }
    }
    return encodeString; //return string
}


//
// *This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) {
    string decodeString = ""; 
    int bit = input.readBit(); //get the bit
    HuffmanNode* temp = encodingTree; //create node 
    while(!input.eof()){ //while file isnt over
        if(temp->zero == nullptr && temp->one == nullptr) { //base case for no leaf
            int appendInt = temp->character; //get char
            if(appendInt == PSEUDO_EOF) { //when it hits pseudo break
                break;
            }
            char appendChar = (char)appendInt; //get valid char
            decodeString += appendChar; //add to main string
            output << appendChar; //outpout
            temp = encodingTree; //set temp to the tree
        }
        if(bit == 0){ //when bit is 0
            temp = temp->zero; //set tenmp to left
        }
        else if(bit == 1){ //when bit is 1
            temp = temp->one; //set temp to 1
        }
        bit = input.readBit(); //get new bit
    }
    return decodeString;
}

//
// *This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
//
string compress(string filename) {
    hashmapF freqMap; hashmapE ecodeMap; HuffmanNode* encodeTree = nullptr; int size = 0; string encodeString = "";
    buildFrequencyMap(filename, true, freqMap); //build map using file name 
    encodeTree = buildEncodingTree(freqMap); //create tree
    ecodeMap = buildEncodingMap(encodeTree); //create map

    ofbitstream output(filename + ".huf"); //create new txt with .huf
    ifstream input(filename); //get input from filename

    output << freqMap; //push everything into new file
    encodeString = encode(input, ecodeMap, output, size, true); //get encoded message
    output.close(); //close output file

    freeTree(encodeTree); //free created tree

    return encodeString;   //return the string
}

//
// *This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note: this function should reverse what the compress
// function did.
//
string decompress(string filename) {
    hashmapF freqMap; hashmapE ecodeMap; HuffmanNode* encodeTree = nullptr; string decodeString = "";
    ifbitstream input(filename); //get content from file
    int pos = filename.find(".txt"); //find where .txt is
    filename = filename.substr(0,pos); //subtract eveything after .txt
    ofstream output(filename + "_unc.txt"); //change to new name

    input >> freqMap; //get content from freqMap
    encodeTree = buildEncodingTree(freqMap); //build tree 
    decodeString = decode(input, encodeTree, output); //decode the contents

    output.close(); //close the file
    freeTree(encodeTree); //free contents

    return decodeString;   //return message
}
