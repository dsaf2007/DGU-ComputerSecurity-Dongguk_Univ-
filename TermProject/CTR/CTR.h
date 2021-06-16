#pragma once
#include "DES.h"
#include <time.h>
#include <thread>
#include <mutex>


class CTR
{
public:
	CTR(std::string input, std::string key_, std::string nonce_);//������
	void setKey(std::string key_);//key setter
	void parseString();//���ڿ� 64��Ʈ ������ �߶� ����
	std::string XORBlock(std::string prev_enc_, std::string block_);//xor ����
	std::string counterStream(int index);//nonce�� ��� ��ȣ�� �����Ͽ� ī���� ����
	void encdec(int x, int n);//��ȣȭ ��ȣȭ
	int getThreadNum();//������ ��Ƽ������ ���� ��ȯ
	void execute();//����
	void nonMulti();//���� ������ ����
	std::string getResult();// ��ȣȭ ��ȣȭ ��� ����
	std::string dec2hex(int d);//10���� 16���� ��ȯ
private:
	std::string input_string; //�Է� ���ڿ�
	std::vector<std::string> str_vec;//�Ľ��� ���ڿ�
	std::vector<std::string> result_vec;//��ȣȭ ��ȣȭ �� ���
	std::string nonce;//��ǥ
	std::string arr = "0123456789ABCDEF";
	int last_block_length;//������ ��� ���ڿ� ����
	std::string key;//Ű
	std::vector<std::thread> threads;//��Ƽ������ ����
};

