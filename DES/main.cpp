#pragma once
#include "CBC.h"
#include "CTR.h"
#include <fstream>
#include <time.h>

int main()
{
    std::cout << "==================ENCRYPTION==================\n";
    DES des1("0123456789ABC", "85E813540F0AB405", MODE::ENCRYPTION);
    des1.encryption();
    std::cout << "==================DECRYPTION==================\n";
    DES des2("E5A951F59B3160C0", "85E813540F0AB405", MODE::DECRYPTION);
    des2.decryption();
    /*std::string plain_text = "0123456789ABCDEFFEDCBA98765432100A1B2C3D4E5F6";
    std::cout <<"plain text: " <<plain_text << std::endl;*/
    srand(time(NULL));
    clock_t start, end;
    double result;
    std::ifstream readFile("test2.txt");
    std::string plain_text;
    std::getline(readFile, plain_text);

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