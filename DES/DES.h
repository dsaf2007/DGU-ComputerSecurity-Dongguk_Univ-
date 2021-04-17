#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

enum MODE {
    ENCRYPTION, DECRYPTION
};

class DES {
private:
    std::string plaintext;
    std::string ciphertext;
    std::string keystring;
    std::vector<int> key;
    std::vector<int> keys[17];
    std::vector<int> keyPermutationTable;
    std::vector<int> rounds;
    std::vector<int> compressionPermutationTable;
    std::vector<int> binaryText;
    std::vector<int> IP;//Initial Permutaion
    std::vector<int> IPinverse;
    std::vector<int> left, right, rightOrigin;
    std::vector<int> EP;//ExpansionPermutaion
    std::vector<int> s[9];//s-box
    std::vector<int> Pbox;//Permutaion

    

    std::vector<int> initialKeySelection(const std::vector<int>& key);//64->56
    void leftShift(std::vector<int>& key, int s);//split to 28bit - shift left
    std::vector<int> keyPermutationAndCompression();//create 48bit round key
    std::vector<int> initialPermutation(const std::vector<int>& text);
    void splitLeftRight(const std::vector<int>& text);
    std::vector<int> expansionPermutation(const std::vector<int>& right);
    std::vector<int> XOR_Key(const std::vector<int>& right, int round);
    std::vector<int> S_box_substitution(const std::vector<int>& right);
    std::vector<int> PboxPermutation(const std::vector<int>& right);
    std::vector<int> XOR_left(const std::vector<int>& left, const std::vector<int>& right);
    void nextLeft();
    std::vector<int> lastPermutation(const std::vector<int>& text);

    void keyGeneration();
public:
    DES();
    DES(std::string text, std::string key, MODE mode);

    std::string encryption(); 
    std::string decryption();
};

std::vector<int> string2hex(const std::string& str);
std::string hex2string(const std::vector<int>& hex);