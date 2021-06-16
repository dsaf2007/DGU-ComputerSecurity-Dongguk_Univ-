#pragma once
#include "DES.h"
#include <time.h>
#include <thread>
#include <mutex>


class CTR
{
public:
	CTR(std::string input, std::string key_, std::string nonce_);
	void setKey(std::string key_);
	void parseString();
	std::string XORBlock(std::string prev_enc_, std::string block_);
	std::string counterStream(int index);
	void encdec(int x, int n);
	int getThreadNum();
	void execute();
	void nonMulti();
	std::string getResult();
	std::string dec2hex(int d);
private:
	std::string input_string;
	std::vector<std::string> str_vec;
	std::vector<std::string> result_vec;
	std::vector<std::string> dec_vec;
	std::string nonce = "";
	std::string arr = "0123456789ABCDEF";
	int last_block_length;
	std::string key;
	std::vector<std::thread> threads;
	std::vector<std::thread> threads_dec;
	std::mutex g_lock;
};

