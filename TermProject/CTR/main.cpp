#pragma once
#include "CTR.h"
#include <fstream>
#include <time.h>

int main()
{
    clock_t start, end;
    double result;
    std::ifstream readFile("test1.txt");//��
    std::string plain_text;
    std::getline(readFile, plain_text);

    std::ifstream readKEK("../KEK.txt");
    std::string KEK;
    std::getline(readKEK, KEK);
    //std::cout << KEK << std::endl;

    std::ifstream readCEK("../CEK.txt");
    std::string CEK;
    std::getline(readCEK, CEK);

    std::ifstream readNonce("../nonce.txt");
    std::string nonce;
    std::getline(readNonce, nonce);

    std::string CEK_encrypted;
    DES EncCEK(CEK, KEK, MODE::ENCRYPTION);
    CEK_encrypted = EncCEK.encryption();

    std::ofstream writeCEK("CEK_encrypted.txt");
    writeCEK << CEK_encrypted;

    CTR enc(plain_text, CEK,nonce);
    enc.execute();
    std::string enc_str = enc.getResult();
    std::ofstream writeEnc("enc_str.txt");
    writeEnc << enc_str;

    CTR dec(enc_str, CEK, nonce);
    dec.execute();
    std::string dec_str = dec.getResult();
    std::ofstream writeDec("dec_str.txt");
    writeDec << dec_str;

    if (plain_text.compare(dec_str) == 0)
    {
        std::cout << "�򹮰� ��ȣȭ�� ����� ��ġ\n";
    }
    else
        std::cout << "��ȣȭ�� ����� �̷������ ����\n";

}