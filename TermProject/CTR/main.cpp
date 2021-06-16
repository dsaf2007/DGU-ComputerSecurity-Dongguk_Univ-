#pragma once
#include "CTR.h"
#include <fstream>
#include <time.h>

int main()
{
    clock_t start, end;
    double result;
    std::ifstream readFile("test1.txt");//평문
    std::string plain_text;
    std::getline(readFile, plain_text);

    std::ifstream readKEK("../KEK.txt");//KEK
    std::string KEK;
    std::getline(readKEK, KEK);

    std::ifstream readCEK("../CEK.txt");//CEK
    std::string CEK;
    std::getline(readCEK, CEK);

    std::ifstream readNonce("../nonce.txt");//비표
    std::string nonce;
    std::getline(readNonce, nonce);

    std::string CEK_encrypted;//CEK 암호화 하여 저장
    DES EncCEK(CEK, KEK, MODE::ENCRYPTION);
    CEK_encrypted = EncCEK.encryption();
    std::ofstream writeCEK("CEK_encrypted.txt");
    writeCEK << CEK_encrypted;

    start = clock();
    CTR enc(plain_text, CEK,nonce);//암호화
    enc.execute();
    end = clock();
    std::string enc_str = enc.getResult();
    result = double(end - start);
    std::cout << "암호화 소요 시간 : " << result << "\n";

    std::ofstream writeEnc("enc_str.txt");
    writeEnc << enc_str;

    start = clock();
    CTR dec(enc_str, CEK, nonce);//복호화
    dec.execute();
    end = clock();
    std::string dec_str = dec.getResult();
    result = double(end - start);
    std::cout << "복호화 소요 시간 : " << result << "\n";
    std::ofstream writeDec("dec_str.txt");
    writeDec << dec_str;

    if (plain_text.compare(dec_str) == 0)
    {
        std::cout << "평문과 복호화한 결과가 일치\n";
    }
    else
        std::cout << "복호화가 제대로 이루어지지 않음\n";

}