#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>


std::string encryption(std::vector<std::string> plain, std::vector<char> pad)//암호화
{
	std::string result;
	int x = 0;
	for (int i = 0; i < plain.size(); i++)
	{
		for (int j = 0; j < plain[i].size(); j++)
		{
				std::string temp;
				temp = plain[i][j] ^ pad[x++];
				result += temp;
		}
	}
	return result;
}
std::string decryption(std::string encrypted_, std::vector<char> pad)//복호화
{
	std::string result;
	int x = 0;
	for (int i = 0; i < encrypted_.size(); i++)
	{
			std::string temp;
			temp = encrypted_[i] ^ pad[x++];
			result += temp;
	}
	
return result;
}
void createOtp(std::vector<std::string> plain, std::string out, std::vector<char>& otp_)//평문 길이만큼 pad 생성
{
	std::ofstream otp(out);//복호문 저장
	int x = 0;
	for (int i = 0; i < plain.size(); i++)
	{
		for (int j = 0; j < plain[i].size(); j++)
		{
				otp_.push_back((char)rand());
		}
	}
	for (auto it : otp_)
	{
		otp << otp_[it];
	}


}
int main(void)
{
	std::string input_file; //평문 txt
	std::string OTP_file; // 생성된 패드
	std::string enc_file; //암호문 txt
	std::string dec_file;
	std::vector<std::string> plain_text;//평문
	std::vector<char> otp;//otp
	std::string encrypted;//암호문
	std::string decrypted;//복호문
	srand(time(NULL));

	std::cout << "input file name : ";
	std::cin >> input_file;
	std::cout << "encrypted file name : ";
	std::cin >> enc_file;
	std::cout << "decrypted file name : ";
	std::cin >> dec_file;
	OTP_file = "otp.txt";

	std::ifstream read_file(input_file);//평문
	std::ofstream enc_file_out(enc_file);//암호문 저장
	std::ofstream dec_file_out(dec_file);//복호문 저장

	if (read_file.is_open())//평문 읽어오기
	{
		while (!read_file.eof())
		{
			std::string s;
			std::getline(read_file, s);
			s += '\n';//개행문자 추가
			plain_text.push_back(s);
		}
	}

	createOtp(plain_text, OTP_file, otp);
	encrypted = encryption(plain_text, otp);
	enc_file_out << encrypted;
	decrypted = decryption(encrypted, otp);
	dec_file_out << decrypted;
	
	return 0;
}