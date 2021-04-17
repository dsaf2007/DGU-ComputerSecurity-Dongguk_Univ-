#pragma once
#include "DES.h"


DES::DES() {}
DES::DES(std::string text, std::string key, MODE mode)
{
    if (mode == MODE::ENCRYPTION)
        plaintext = text;
    else if (mode == MODE::DECRYPTION)
        ciphertext = text;
    keystring = key;

    keyPermutationTable = 
    { 0,
       57,49,41,33,25,17, 9,
       1,58,50,42,34,26,18,
       10, 2,59,51,43,35,27,
       19,11, 3,60,52,44,36,
       63,55,47,39,31,23,15,
       7,62,54,46,38,30,22,
       14, 6,61,53,45,37,29,
       21,13, 5,28,20,12, 4
    };
    rounds = 
    { 0,
       1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1
    };
    compressionPermutationTable = 
    { 0,
       14,17,11,24, 1, 5, 3,28,
       15, 6,21,10,23,19,12, 4,
       26, 8,16, 7,27,20,13, 2,
       41,52,31,37,47,55,30,40,
       51,45,33,48,44,49,39,56,
       34,53,46,42,50,36,29,32
    };
    IP = 
    { 0,
       58,50,42,34,26,18,10, 2,
       60,52,44,36,28,20,12, 4,
       62,54,46,38,30,22,14, 6,
       64,56,48,40,32,24,16, 8,
       57,49,41,33,25,17, 9, 1,
       59,51,43,35,27,19,11, 3,
       61,53,45,37,29,21,13, 5,
       63,55,47,39,31,23,15, 7
    };
    IPinverse = 
    { 0,
       40, 8,48,16,56,24,64,32,
       39, 7,47,15,55,23,63,31,
       38, 6,46,14,54,22,62,30,
       37, 5,45,13,53,21,61,29,
       36, 4,44,12,52,20,60,28,
       35, 3,43,11,51,19,59,27,
       34, 2,42,10,50,18,58,26,
       33, 1,41, 9,49,17,57,25
    };
    EP = 
    { 0,
       32, 1, 2, 3, 4, 5,
       4, 5, 6, 7, 8, 9,
       8, 9,10,11,12,13,
       12,13,14,15,16,17,
       16,17,18,19,20,21,
       20,21,22,23,24,25,
       24,25,26,27,28,29,
       28,29,30,31,32, 1
    };
    s[1] = 
    { 0,
       14, 4,13, 1, 2,15,11, 8, 3,10, 6,12, 5, 9, 0, 7,
       0,15, 7, 4,14, 2,13, 1,10, 6,12,11, 9, 5, 3, 8,
       4, 1,14, 8,13, 6, 2,11,15,12, 9, 7, 3,10, 5, 0,
       15,12, 8, 2, 4, 9, 1, 7, 5,11, 3,14,10, 0, 6,13
    };
    s[2] = 
    { 0,
       15, 1, 8,14, 6,11, 3, 4, 9, 7, 2,13,12, 0, 5,10,
       3,13, 4, 7,15, 2, 8,14,12, 0, 1,10, 6, 9,11, 5,
       0,14, 7,11,10, 4,13, 1, 5, 8,12, 6, 9, 3, 2,15,
       13, 8,10, 1, 3,15, 4, 2,11, 6, 7,12, 0, 5,14, 9
    };
    s[3] = 
    { 0,
       10, 0, 9,14, 6, 3,15, 5, 1,13,12, 7,11, 4, 2, 8,
       13, 7, 0, 9, 3, 4, 6,10, 2, 8, 5,14,12,11,15, 1,
       13, 6, 4, 9, 8,15, 3, 0,11, 1, 2,12, 5,10,14, 7,
       1,10,13, 0, 6, 9, 8, 7, 4,15,14, 3,11, 5, 2,12
    };
    s[4] = 
    { 0,
       7,13,14, 3, 0, 6, 9,10, 1, 2, 8, 5,11,12, 4,15,
       13, 8,11, 5, 6,15, 0, 3, 4, 7, 2,12, 1,10,14, 9,
       10, 6, 9, 0,12,11, 7,13,15, 1, 3,14, 5, 2, 8, 4,
       3,15, 0, 6,10, 1,13, 8, 9, 4, 5,11,12, 7, 2,14
    };
    s[5] = 
    { 0,
       2,12, 4, 1, 7,10,11, 6, 8, 5, 3,15,13, 0,14, 9,
       14,11, 2,12, 4, 7,13, 1, 5, 0,15,10, 3, 9, 8, 6,
       4, 2, 1,11,10,13, 7, 8,15, 9,12, 5, 6, 3, 0,14,
       11, 8,12, 7, 1,14, 2,13, 6,15, 0, 9,10, 4, 5, 3
    };
    s[6] = 
    { 0,
       12, 1,10,15, 9, 2, 6, 8, 0,13, 3, 4,14, 7, 5,11,
       10,15, 4, 2, 7,12, 9, 5, 6, 1,13,14, 0,11, 3, 8,
       9,14,15, 5, 2, 8,12, 3, 7, 0, 4,10, 1,13,11, 6,
       4, 3, 2,12, 9, 5,15,10,11,14, 1, 7, 6, 0, 8,13
    };
    s[7] = 
    { 0,
       4,11, 2,14,15, 0, 8,13, 3,12, 9, 7, 5,10, 6, 1,
       13, 0,11, 7, 4, 9, 1,10,14, 3, 5,12, 2,15, 8, 6,
       1, 4,11,13,12, 3, 7,14,10,15, 6, 8, 0, 5, 9, 2,
       6,11,13, 8, 1, 4,10, 7, 9, 5, 0,15,14, 2, 3,12
    };
    s[8] = 
    { 0,
       13, 2, 8, 4, 6,15,11, 1,10, 9, 3,14, 5, 0,12, 7,
       1,15,13, 8,10, 3, 7, 4,12, 5, 6,11, 0,14, 9, 2,
       7,11, 4, 1, 9,12,14, 2, 0, 6,10,13,15, 3, 5, 8,
       2, 1,14, 7, 4,10, 8,13,15,12, 9, 0, 3, 5, 6,11
    };
    Pbox = 
    { 0,
       16, 7,20,21,29,12,28,17, 1,15,23,26, 5,18,31,10,
       2, 8,24,14,32,27, 3, 9,19,13,30, 6,22,11, 4,25
    };
}

std::string DES::encryption()
{
       // std::cout << "Plain Text : [" << plaintext << "]\n";
      //  std::cout << "   Key     : [" << keystring << "]\n";
        binaryText = string2hex(plaintext);
        key = string2hex(keystring);
        key = initialKeySelection(key);
        keyGeneration();
        binaryText = initialPermutation(binaryText);
        splitLeftRight(binaryText);
       // std::cout << "round     left         right         key\n";
        for (int round = 1; round <= 16; round++) 
        {
            right = expansionPermutation(right);//F function
            right = XOR_Key(right, round);//F function
            right = S_box_substitution(right);//F function
            right = PboxPermutation(right);//F function
            right = XOR_left(left, right);
            nextLeft();
            if (round == 16) 
            {
                std::vector<int> tmp;
                tmp = left;
                left = right;
                right = tmp;
            }
           // std::cout << std::setw(5) << round << "  [" << hex2string(left) << "]  [" << hex2string(right) << "]  [" << hex2string(keys[round]) << "]\n";
        }
        binaryText = lastPermutation(binaryText);//IP inverse
        ciphertext = hex2string(binaryText);
      //  std::cout << "Cipher Text : [" << ciphertext << "]\n";

        return ciphertext;
}
std::string DES::decryption()
{
   // std::cout << "Cipher Text : [" << ciphertext << "]\n";
   // std::cout << "    Key     : [" << keystring << "]\n";
    binaryText = string2hex(ciphertext);
    key = string2hex(keystring);
    key = initialKeySelection(key);
    keyGeneration();
    binaryText = initialPermutation(binaryText);
    splitLeftRight(binaryText);
   // std::cout << "round     left         right         key\n";
    for (int round = 16; round >= 1; round--) 
    {
        right = expansionPermutation(right);
        right = XOR_Key(right, round);
        right = S_box_substitution(right);
        right = PboxPermutation(right);
        right = XOR_left(left, right);
        nextLeft();
        if (round == 1) 
        {
            std::vector<int> tmp;
            tmp = left;
            left = right;
            right = tmp;
        }
       // std::cout << std::setw(5) << 17 - round << "  [" << hex2string(left) << "]  [" << hex2string(right) << "]  [" << hex2string(keys[round]) << "]\n";
    }
    binaryText = lastPermutation(binaryText);
    plaintext = hex2string(binaryText);
   // std::cout << "Plain Text : [" << plaintext << "]\n";

    return plaintext;
}

std::vector<int> DES::initialKeySelection(const std::vector<int>& key) 
{
    std::vector<int> selectedKey(57);
    for (int i = 1; i <= 56; i++)
        selectedKey[i] = key[keyPermutationTable[i]];
    return selectedKey;
}
void DES::leftShift(std::vector<int>& key, int s) 
{
    std::vector<int> temp1, temp2;
    for (int i = 1; i <= 56; i++) 
    {
        if (i <= 28) 
        {
            if (i <= s)
                temp1.push_back(key[i]);
            key[i] = i + s <= 28 ? key[i + s] : temp1[i + s - 29];
        }
        else 
        {
            if (i - 28 <= s)
                temp2.push_back(key[i]);
            key[i] = i + s <= 56 ? key[i + s] : temp2[i + s - 57];
        }
    }
}
std::vector<int> DES::keyPermutationAndCompression() 
{
    std::vector<int> compressedKey(49);
    for (int i = 1; i <= 48; i++)
        compressedKey[i] = key[compressionPermutationTable[i]];
    return compressedKey;
}
std::vector<int> DES::initialPermutation(const std::vector<int>& text) 
{
    std::vector<int> IPtext(65);
    for (int i = 1; i <= 64; i++)
        IPtext[i] = text[IP[i]];
    return IPtext;
}
void DES::splitLeftRight(const std::vector<int>& text) 
{
    left.resize(33); right.resize(33);
    for (int i = 1; i <= 32; i++)
        left[i] = text[i];
    for (int i = 33; i <= 64; i++)
        right[i - 32] = text[i];
    rightOrigin = right;
}
std::vector<int> DES::expansionPermutation(const std::vector<int>& right) 
{
    std::vector<int> expansedRight(49);
    for (int i = 1; i <= 48; i++)
        expansedRight[i] = right[EP[i]];
    return expansedRight;
}
std::vector<int> DES::XOR_Key(const std::vector<int>& right, int round) 
{
    std::vector<int> newRight(49);
    for (int i = 1; i <= 48; i++)
        newRight[i] = right[i] ^ keys[round][i];
    return newRight;
}
std::vector<int> DES::S_box_substitution(const std::vector<int>& right) 
{
    std::vector<int> newRight(1);
    for (int i = 1; i <= 8; i++) 
    {
        int from = (i - 1) * 6 + 1, to = i * 6;
        int row = 2 * right[from] + right[to], column = 8 * right[from + 1] + 4 * right[from + 2] + 2 * right[from + 3] + right[from + 4];

        int idx = 16 * row + column + 1;
        int num = s[i][idx];
        int a1 = num / 8; num -= a1 * 8;
        int a2 = num / 4; num -= a2 * 4;
        int a3 = num / 2; num -= a3 * 2;
        int a4 = num;
        newRight.push_back(a1);
        newRight.push_back(a2);
        newRight.push_back(a3);
        newRight.push_back(a4);
    }
    return newRight;
}
std::vector<int> DES::PboxPermutation(const std::vector<int>& right) 
{
    std::vector<int> newRight(33);
    for (int i = 1; i <= 32; i++)
        newRight[i] = right[Pbox[i]];
    return newRight;
}
std::vector<int> DES::XOR_left(const std::vector<int>& left, const std::vector<int>& right) 
{
    std::vector<int> newRight(33);
    for (int i = 1; i <= 32; i++) 
    {
        newRight[i] = left[i] ^ right[i];
    }
    return newRight;
}
void DES::nextLeft() 
{
    left = rightOrigin;
    rightOrigin = right;
}
std::vector<int> DES::lastPermutation(const std::vector<int>& text) 
{
    std::vector<int> compound(1);
    std::vector<int> newText(1);
    for (int i = 1; i <= 32; i++)
        compound.push_back(left[i]);
    for (int i = 1; i <= 32; i++)
        compound.push_back(right[i]);
    for (int i = 1; i <= 64; i++)
        newText.push_back(compound[IPinverse[i]]);
    return newText;
}
void DES::keyGeneration()
{
    for (int i = 1; i <= 16; i++)
    {
        leftShift(key, rounds[i]);
        keys[i] = keyPermutationAndCompression();
    }
}

std::vector<int> string2hex(const std::string& str)
{
    std::vector<int> hexcode;
    hexcode.resize(1 + str.size() * 4);
    for (int i = 0; i < str.size(); i++)
    {
        switch (str[i])
        {
        case '0':
            hexcode[4 * i + 1] = 0; hexcode[4 * i + 2] = 0; hexcode[4 * i + 3] = 0; hexcode[4 * i + 4] = 0;
            break;
        case '1':
            hexcode[4 * i + 1] = 0; hexcode[4 * i + 2] = 0; hexcode[4 * i + 3] = 0; hexcode[4 * i + 4] = 1;
            break;
        case '2':
            hexcode[4 * i + 1] = 0; hexcode[4 * i + 2] = 0; hexcode[4 * i + 3] = 1; hexcode[4 * i + 4] = 0;
            break;
        case '3':
            hexcode[4 * i + 1] = 0; hexcode[4 * i + 2] = 0; hexcode[4 * i + 3] = 1; hexcode[4 * i + 4] = 1;
            break;
        case '4':
            hexcode[4 * i + 1] = 0; hexcode[4 * i + 2] = 1; hexcode[4 * i + 3] = 0; hexcode[4 * i + 4] = 0;
            break;
        case '5':
            hexcode[4 * i + 1] = 0; hexcode[4 * i + 2] = 1; hexcode[4 * i + 3] = 0; hexcode[4 * i + 4] = 1;
            break;
        case '6':
            hexcode[4 * i + 1] = 0; hexcode[4 * i + 2] = 1; hexcode[4 * i + 3] = 1; hexcode[4 * i + 4] = 0;
            break;
        case '7':
            hexcode[4 * i + 1] = 0; hexcode[4 * i + 2] = 1; hexcode[4 * i + 3] = 1; hexcode[4 * i + 4] = 1;
            break;
        case '8':
            hexcode[4 * i + 1] = 1; hexcode[4 * i + 2] = 0; hexcode[4 * i + 3] = 0; hexcode[4 * i + 4] = 0;
            break;
        case '9':
            hexcode[4 * i + 1] = 1; hexcode[4 * i + 2] = 0; hexcode[4 * i + 3] = 0; hexcode[4 * i + 4] = 1;
            break;
        case 'A':
            hexcode[4 * i + 1] = 1; hexcode[4 * i + 2] = 0; hexcode[4 * i + 3] = 1; hexcode[4 * i + 4] = 0;
            break;
        case 'B':
            hexcode[4 * i + 1] = 1; hexcode[4 * i + 2] = 0; hexcode[4 * i + 3] = 1; hexcode[4 * i + 4] = 1;
            break;
        case 'C':
            hexcode[4 * i + 1] = 1; hexcode[4 * i + 2] = 1; hexcode[4 * i + 3] = 0; hexcode[4 * i + 4] = 0;
            break;
        case 'D':
            hexcode[4 * i + 1] = 1; hexcode[4 * i + 2] = 1; hexcode[4 * i + 3] = 0; hexcode[4 * i + 4] = 1;
            break;
        case 'E':
            hexcode[4 * i + 1] = 1; hexcode[4 * i + 2] = 1; hexcode[4 * i + 3] = 1; hexcode[4 * i + 4] = 0;
            break;
        case 'F':
            hexcode[4 * i + 1] = 1; hexcode[4 * i + 2] = 1; hexcode[4 * i + 3] = 1; hexcode[4 * i + 4] = 1;
            break;
        }
    }
    return hexcode;
}
std::string hex2string(const std::vector<int>& hex)
{
    std::string str;
    for (int i = 0; i < (hex.size() - 1) / 4; i++)
    {
        int s = 8 * hex[4 * i + 1] + 4 * hex[4 * i + 2] + 2 * hex[4 * i + 3] + hex[4 * i + 4];
        switch (s)
        {
        case 0:
            str += '0';
            break;
        case 1:
            str += '1';
            break;
        case 2:
            str += '2';
            break;
        case 3:
            str += '3';
            break;
        case 4:
            str += '4';
            break;
        case 5:
            str += '5';
            break;
        case 6:
            str += '6';
            break;
        case 7:
            str += '7';
            break;
        case 8:
            str += '8';
            break;
        case 9:
            str += '9';
            break;
        case 10:
            str += 'A';
            break;
        case 11:
            str += 'B';
            break;
        case 12:
            str += 'C';
            break;
        case 13:
            str += 'D';
            break;
        case 14:
            str += 'E';
            break;
        case 15:
            str += 'F';
            break;
        }
    }
    return str;
}