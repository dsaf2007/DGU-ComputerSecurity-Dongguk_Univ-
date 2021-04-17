#pragma once
#include "DES.h"



class CBC
{
public:
	CBC(std::string input)
	{
		input_string = input;
		for (int i = 0; i < 16; i++)
		{
			iv+=arr[rand()%16];
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
			str_vec.push_back(input_string.substr(16*block_num, length % 16));
			for (int j = 0; j < 16 -last_block_length; j++)
			{
				str_vec.back() += arr[rand() % 16];
			}
			//std::cout <<"\n\n"<< str_vec.back()<<"\n\n";
		}
	}

	std::string XORBlock(std::string prev_enc_,std::string block_)
	{
		std::vector<int> prev_enc=string2hex(prev_enc_);
		std::vector<int> block=string2hex(block_);
		std::vector<int> xor_str(prev_enc.size());
		for (int i = 0; i < prev_enc.size(); i++)
		{
			xor_str[i] = prev_enc[i] ^ block[i];
		}
		return hex2string(xor_str);

	}


	void encrypt()
	{
		parseString();
		std::string temp;

		for (int i = 0; i < str_vec.size(); i++)
		{
			if (i == 0)
			{
				DES des1(XORBlock(iv,str_vec[i]), "85E813540F0AB405", MODE::ENCRYPTION);
				enc_vec.push_back(des1.encryption());
				temp = XORBlock(enc_vec.back(),str_vec[i + 1]);
			}
			else
			{
				DES des1(temp, "85E813540F0AB405", MODE::ENCRYPTION);
				enc_vec.push_back(des1.encryption());
				if(i<str_vec.size()-1)temp = XORBlock(enc_vec.back(), str_vec[i + 1]);
			}
		}
	}


	void decrypt()
	{

		std::string temp;

		for (int i = 0; i < enc_vec.size(); i++)
		{
			if (i == 0)
			{
				DES des1(enc_vec[i], "85E813540F0AB405", MODE::DECRYPTION);
				dec_vec.push_back(XORBlock(des1.decryption(),iv));
			}
			else
			{
				DES des1(enc_vec[i], "85E813540F0AB405", MODE::DECRYPTION);
				dec_vec.push_back(XORBlock(des1.decryption(),enc_vec[i-1]));
			}
		}
		if (last_block_length != 0)
		{
			dec_vec.back() = dec_vec.back().substr(0,last_block_length);
		}

	}


private:
	std::string input_string;
	std::vector<std::string> str_vec;
	std::vector<std::string> enc_vec;
	std::vector<std::string> dec_vec;
	std::string iv="";
	std::string arr = "0123456789ABCDEF";
	int last_block_length;
};

