#include "CTR.h"

CTR::CTR(std::string input, std::string key_, std::string nonce_)
{
	input_string = input;
	/*for (int i = 0; i < 8; i++)
	{
		nonce += arr[rand() % 16];
	}*/
	nonce = nonce_;
	key = key_;
}


void CTR::setKey(std::string key_)
{
	key = key_;
}

void CTR::parseString()
{
	int length = input_string.length();
	int block_num = length / 16;
	last_block_length = length % 16;

	for (int i = 0; i < block_num; i++)
	{
		str_vec.push_back(input_string.substr(i * 16, 16));
	}
	if (length % 16 != 0)
	{
		str_vec.push_back(input_string.substr(16 * block_num, length % 16));
		for (int j = 0; j < 16 - last_block_length; j++)
		{
			str_vec.back() += '0';
		}
	}
}

std::string CTR::XORBlock(std::string prev_enc_, std::string block_)
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

std::string CTR::counterStream(int index)
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

void CTR::encdec(int x, int n)
{
	for (int i = x * (str_vec.size() / n); i < (x + 1) * (str_vec.size() / n); i++)
	{
		DES des1(counterStream(i), key, MODE::ENCRYPTION);
		result_vec[i] = XORBlock(des1.encryption(), str_vec[i]);
	}
	if (last_block_length != 0)
	{
		result_vec.back() = result_vec.back().substr(0, last_block_length);
	}
}

int CTR::getThreadNum()
{
	//1-8사이 가능한 큰 thread숫자를 반환
	int size = str_vec.size();
	int thread_num = 0;
	if (size % 1 == 0)
		thread_num == 1;
	if (size % 2 == 0)
		thread_num == 2;
	if (size % 3 == 0)
		thread_num == 3;
	if (size % 4 == 0)
		thread_num == 4;
	if (size % 5 == 0)
		thread_num == 5;
	if (size % 6 == 0)
		thread_num = 6;
	if (size % 7 == 0)
		thread_num = 7;
	if (size % 8 == 0)
		thread_num = 8;

	return thread_num;
}

void CTR::nonMulti()
{
	for (int i = 0; i < str_vec.size(); i++)
	{
		DES des1(counterStream(i), key, MODE::ENCRYPTION);
		result_vec[i] = XORBlock(des1.encryption(), str_vec[i]);
	}
	if (last_block_length != 0)
	{
		result_vec.back() = result_vec.back().substr(0, last_block_length);
	}
}

void CTR::execute()
{
	parseString();
	result_vec.resize(str_vec.size());
	int n = getThreadNum();
	for (int i = 0; i < n; i++)
	{
		threads.emplace_back(std::thread(&CTR::encdec, this, i, n));
	}
	for (auto& thread : threads)
		thread.join();
}

std::string CTR::getResult()
{
	std::string enc_str = "";
	for (int i = 0; i < result_vec.size(); i++)
	{
		enc_str += result_vec[i];
	}
	return enc_str;
}

std::string CTR::dec2hex(int d)
{
	int i = 0;
	std::string hex = "";

	do {
		hex += arr[d % 16];
	} while ((d /= 16) > 0);
	std::reverse(hex.begin(), hex.end());

	return hex;

}