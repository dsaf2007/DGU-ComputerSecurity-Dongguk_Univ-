#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "CTR.h"
#include <fstream>
#include <time.h>


std::string key()
{
    char input[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '!', 
'@', '#', '$', ' % ', ' ^ ', ' & ', ' * ', '(', ')', ' - ', '_', ' = ', ' + ', '[', ']', '{', '}', ';',':',',','<','.','>','/','?' };
    std::string output = "";
    for (int i = 0; i < 10; i++)
    {
        output += input[rand() % 62];
    }

    return output;
}

std::string timespan()
{
    time_t start, end,timer;
    struct tm user_stime;
    struct tm* curr_stime;
    int tm_day, tm_hour, tm_min, tm_sec;
    double diff;

    timer = time(NULL);
    curr_stime = localtime(&timer);
    int my_year=curr_stime->tm_year, my_month=curr_stime->tm_mon, my_day=curr_stime->tm_mday;

    user_stime.tm_year = my_year - 1900; // 년도가 1900년부터 시작하기 때문
    user_stime.tm_mon = my_month - 1; //월이 0부터 시작하기 때문
    user_stime.tm_mday = my_day;
    user_stime.tm_hour = 0;
    user_stime.tm_min = 0;
    user_stime.tm_sec = 0;
    user_stime.tm_isdst = 0; //썸머타임 사용안함

    start = mktime(&user_stime);
    time(&end);

    diff = difftime(end, start);

    return std::to_string(diff);
}

std::string DMAC(std::string plain_text)
{
    std::string usr_str = key();
    std::string time_span = timespan();
    std::string input = plain_text;
    input += usr_str;
    input += time_span;
    CTR ctr(input);
    ctr.encrypt();
    std::string output = ctr.output();
    return output;
}

int main()
{
    srand(time(NULL));
    double result;
    //std::ifstream readFile("test2.txt");
    std::string plain_text,key_,timespan_;
    //std::getline(readFile, plain_text);

    int cmd;

    while (1)
    {
        std::cout << "1.송신자\n";
        std::cout << "2. 수신자\n";
        std::cout << "3. 비교\n";
        std::cout << "enter command : ";
        std::cin >> cmd;

        switch (cmd)
        {
        case 1:
            std::cout << "enter plain text : ";
            std::cin >> plain_text;
            std::cout << "MAC :" << DMAC(plain_text) << std::endl;
            break;

        case 2:
            std::cout << ""
        }
    }
    



}