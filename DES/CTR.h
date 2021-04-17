#pragma once
#include "DES.h"
#include <time.h>
#include <thread>
#include <mutex>


class CTR
{
public:
	CTR(std::string input)
	{
		input_string = input;
		for (int i = 0; i < 8; i++)
		{
			nonce += arr[rand() % 16];
		}

	}

	void parseString()
	{
		int length = input_string.length();
		int block_num = length / 16;
		last_block_length = length % 16;
		/*if (length % 16 == 0)block_num = length / 16;
		else block_num = (length / 16) + 1;*/

		for (int i = 0; i < block_num; i++)
		{
			str_vec.push_back(input_string.substr(i * 16, 16));
		}
		if (length % 16 != 0)
		{
			str_vec.push_back(input_string.substr(16 * block_num, length % 16));
			for (int j = 0; j < 16 - last_block_length; j++)
			{
				str_vec.back() += arr[rand() % 16];
			}
		}

	}

	std::string XORBlock(std::string prev_enc_, std::string block_)
	{
		std::vector<int> prev_enc = string2hex(prev_enc_);
		std::vector<int> block = string2hex(block_);
		std::vector<int> xor_str(prev_enc.size());
		for (int i = 0; i < prev_enc.size(); i++)
		{
			xor_str[i] = prev_enc[i] ^ block[i];
		}
		return hex2string(xor_str);

	}

	std::string counterStream(int index)
	{
		std::string counter = nonce;
		std::string hex = dec2hex(index);
		for (int i = 0; i < 8 - hex.length(); i++)
		{
			counter += "0";
		}
		counter += hex;
		return counter;
	}

	void encrypt(int n)
	{
		parseString();
		enc_vec.resize(str_vec.size());
		for (int i = n*(str_vec.size()/4); i < (n+1) * (str_vec.size() / 4); i++)
		{
				DES des1(counterStream(i), "85E813540F0AB405", MODE::ENCRYPTION);
				enc_vec[i] = XORBlock(des1.encryption(), str_vec[i]);
		}
	}

	
	void decrypt(int n)
	{

		std::string temp;

		for (int i = (n) * (enc_vec.size() / 4); i < (n+1)*(enc_vec.size()/4); i++)
		{
				DES des1(counterStream(i), "85E813540F0AB405", MODE::ENCRYPTION);
				dec_vec.push_back(XORBlock(des1.encryption(),enc_vec[i]));
		}
		if (last_block_length != 0)
		{
			dec_vec.back() = dec_vec.back().substr(0, last_block_length);
		}
	}

	std::string exec_enc()
	{
		//std::thread t1, t2, t3, t4;
		std::cout << "thread";
		std::thread t1(&CTR::encrypt,this,0);
		std::thread t2(&CTR::encrypt, this, 1);
		std::thread t3(&CTR::encrypt, this, 2);
		std::thread t4(&CTR::encrypt, this, 3);

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		std::string enc_str = "";
		for (int i = 0; i < enc_vec.size(); i++)
		{
			enc_str += enc_vec[i];
		}
		return enc_str;
	}


	std::string exec_dec()
	{
		//std::thread t1, t2, t3, t4;
		std::thread t1(&CTR::decrypt, this, 0);
		std::thread t2(&CTR::decrypt, this, 1);
		std::thread t3(&CTR::decrypt, this, 2);
		std::thread t4(&CTR::decrypt, this, 3);

		t1.join();
		t2.join();
		t3.join();
		t4.join();

		std::string dec_str = "";
		for (int i = 0; i < enc_vec.size(); i++)
		{
			dec_str += enc_vec[i];
		}
		return dec_str;
	}

	std::string dec2hex(int d)
	{
		int i = 0;
		std::string hex="";

		do {
			hex += arr[d % 16];
		} while ((d /= 16) > 0);


		std::reverse(hex.begin(),hex.end());

		return hex;

	}
private:
	std::string input_string;
	std::vector<std::string> str_vec;
	std::vector<std::string> enc_vec;
	std::vector<std::string> dec_vec;
	std::string nonce = "";
	std::string arr = "0123456789ABCDEF";
	int last_block_length;
};

