#pragma once
#include "CTR.h"
#include <fstream>
#include <time.h>

int main()
{

    srand(time(NULL));
    clock_t start, end;
    double result;
    std::ifstream readFile("test1.txt");//평문
    std::string plain_text;
    std::getline(readFile, plain_text);

    std::ifstream readKEK("../KEK.txt");
    std::string KEK;
    std::getline(readKEK, KEK);

    std::ifstream readCEK("../CEK.txt");
    std::string CEK;
    std::getline(readCEK, CEK);

    std::string CEK_encrypted;
    DES EncCEK(CEK, KEK, MODE::ENCRYPTION);
    CEK_encrypted = EncCEK.encryption();

    std::ofstream writeCEK("CEK_encrypted.txt");
    writeCEK << CEK_encrypted;

    CTR ctr(plain_text, CEK);
    ctr.encrypt();
    std::string enc_str = ctr.getEnc();
    std::ofstream writeEnc("enc_str.txt");
    writeEnc << enc_str;
    ctr.decrypt();
    std::string dec_str = ctr.getDec();
    std::ofstream writeDec("dec_str.txt");
    writeDec << dec_str;

    if (plain_text.compare(dec_str) == 0)
    {
        std::cout << "평문과 복호화한 결과가 일치\n";
    }
    else
        std::cout << "복호화가 제대로 이루어지지 않음\n";

    //CBC cbc(plain_text);
    ////std::cout << "CBC encryption" << std::endl;
    //start = clock();
    //cbc.encrypt();
    //end = clock();
    //result = (double)(end - start);
    //std::cout << "CBC encryption elapse time : " << result/CLOCKS_PER_SEC << "\n";
    ////std::cout << "CBC decryption" << std::endl;
    //start = clock();
    //cbc.decrypt();
    //end = clock();
    //result = (double)(end - start);
    //std::cout << "CBC decryption elapse time : " << result/ CLOCKS_PER_SEC << "\n";
    

   /* CTR ctr(plain_text);
    std::cout << "CTR encryption" << std::endl;*/
   /* start = clock();
    std::thread t1(&CTR::encrypt,CTR(plain_text),0);
    std::thread t2(&CTR::encrypt, CTR(plain_text), 1);
    std::thread t3(&CTR::encrypt, CTR(plain_text), 2);
    std::thread t4(&CTR::encrypt, CTR(plain_text), 3);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    end = clock();
    result = (double)(end - start);
    std::cout << "CTR encryption elapse time : " << result/ CLOCKS_PER_SEC << "\n";*/
    //std::cout << "CTR decryption" << std::endl;
   /* start = clock();
    ctr.decrypt();
    end = clock();
    result = (double)(end - start);
    std::cout << "CTR decryption elapse time : " << result/CLOCKS_PER_SEC << "\n";*/


   /* std::ofstream writeFile("test1.txt");
    std::string arr = "0123456789ABCDEF";
    for (int i = 0; i < 10500000; i++)
    {
        writeFile << arr[rand() % 16];
    }*/
}