#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <thread>
#include <Windows.h>
void run();
void ComparePasswd(int key_length, int case_num);
float time_arr[100];
std::vector<std::pair<std::string, float>> vec;
int main()
{
	run();
}



std::string CreatePasswd(int key_length, int passwd_type)
{
	//char* passwd = new char[key_length];
	std::string passwd;
	char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
	char number[] = "0123456789";
	char alpha_num[] = "abcdefghijklmnopqrstuvwxyz0123456789";
	char whole[] = "abcdefghijklmnopqrstuvwxyz0123456789~!@#$%^&*()_+`,./<>?;':[]{}\"|";


	if (passwd_type == 1)
	{
		for (int i = 0; i < key_length; i++)
		{
			passwd += number[rand() % 10];
		}
	}
	else if (passwd_type == 2)
	{	for (int i = 0; i < key_length; i++)
		{
			passwd += alphabet[rand() % 26];
		}
	}
	else if (passwd_type == 3)
	{
		for (int i = 0; i < key_length; i++)
			passwd += alpha_num[rand()* strlen(alpha_num)/(RAND_MAX+1)];
	}
	else if (passwd_type == 4)
	{
		for (int i = 0; i < key_length; i++)
			passwd += whole[rand()*strlen(whole) / (RAND_MAX + 1)];
	}
	return passwd;
}


void ComparePasswd(int key_length,int case_num)
{

	srand(GetTickCount64());
	std::string case_passwd;
	std::string compare_passwd;
	clock_t start, end;

	for (int i = 0; i < 25; i++)
	{
		case_passwd = CreatePasswd(key_length, case_num);
		for (int i = 0; i < key_length; i++)
		{
			std::cout << case_passwd[i];
		}std::cout << " : ";
		start = clock();
		while (case_passwd.compare(compare_passwd) != 0)
		{
			compare_passwd = CreatePasswd(key_length, 4);

		}
		end = clock();
		double elapse_time = (end - start) / (double)1000;
		vec.push_back(std::make_pair(case_passwd, elapse_time));
		std::cout.precision(8);
		std::cout << (end - start) / (double)1000 << "\n";
	}
}



void run()
{
	
	int case_num;
	int key_length;
	std::cout << "input key length : ";
	std::cin >> key_length;
	/*char* case_passwd = new char[key_length];
	char* compare_passwd = new char[key_length];*/
	std::string case_passwd;
	std::string compare_passwd;
	std::cout << "choose case number(case 1 : number , case 2 : alphabet , case 3 : alphabet+number)\n  :";
	std::cin >> case_num;
	clock_t start, end;
	
	std::thread t1(ComparePasswd,key_length,case_num);
	Sleep(1000);
	std::thread t2(ComparePasswd, key_length, case_num);
	Sleep(1000);
	std::thread t3(ComparePasswd, key_length, case_num);
	Sleep(1000);
	std::thread t4(ComparePasswd, key_length, case_num);

	t1.join();
	t2.join();
	t3.join();
	t4.join();


	float sum = 0;
	for (int i = 0; i < 100; i++)
	{
		sum += vec[i].second;
	}
	sum = sum / (float)100;
	std::string out_filename = "result_";
	out_filename += std::to_string(key_length);
	out_filename += "_";
	out_filename += std::to_string(case_num) +".txt";
	std::ofstream fout(out_filename);
	fout.precision(8);
	for (int i= 0 ; i <vec.size() ; i++)
	{
		fout <<vec[i].first<<" / case<"<<i+1<<"> : "<< vec[i].second<<"\n";
	}
	fout << "\n Æò±Õ ½Ã°£Àº : " << sum;
}
