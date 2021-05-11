#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstdint>
#include <cmath>
#include <algorithm>

uint64_t changeEndian(uint64_t x)
{
	x = ((x << 8) & 0xFF00FF00FF00FF00ULL) | ((x >> 8) & 0x00FF00FF00FF00FFULL);
	x = ((x << 16) & 0xFFFF0000FFFF0000ULL) | ((x >> 16) & 0x0000FFFF0000FFFFULL);
	return (x << 32) | (x >> 32);
}

std::string toBinary(int n)//decimal to binary
{
	std::string r;
	while (n != 0) {
		r += (n % 2 == 0 ? "0" : "1");
		n /= 2;
	}
	return r;//string���·� ���
}
unsigned long long preProcessing(std::vector<int>& input)//�Է� �� ��ó��
{
	std::string output = "";
	input.push_back(0b10000000);//�Է� �� �ڿ� 1 1�� �߰�
	unsigned long long binary=0;
	int L = input.size();

	int k = 64 - (((L % 64) + 9) % 64);//ũ�⸦ ���߱� ����
	if (k == 64) k = 0;

	for (int i = 0; i < k; i++)//������ ��ŭ �ڿ� 0�߰�
	{
		input.push_back(0);
	}

	uint64_t bitLengthInBigEndian = changeEndian(L * 8);
	auto ptr = reinterpret_cast<uint8_t*>(&bitLengthInBigEndian);

	input.insert(std::end(input), ptr, ptr + 8);//������ 8��Ʈ�� ���ڿ� ũ�� �Է�

	for (int i = 0; i < input.size(); i++)//������ ������ ���ڿ��� ��ȯ�Ͽ� ��ģ��.
	{
		output += toBinary(input[i]);
	}

	for (int i = 0; i < output.length(); i++)
	{
		binary = (binary << 1) + output[i] - '0';//������ ������ ������ ��ȯ
	}

	return binary;
}


double hashing(double A,int m,unsigned long long x)//multiplication Method
{
	double hash = m * ((x*A)-(long long)(x*A));//m 2�� ������, A 0��1������ �Ҽ� , x �Է°�.

	return hash;
}

int main()
{
	while(1)
	{std::string x; double A=0.0000001;
	std::cout << "x : ";
	std::cin >> x;
	std::cout << "A : "<<A<<std::endl;
	
	std::vector<int> initial;
	
	for (int i = 0; i < x.length(); i++)
	{
		initial.push_back(((int)x[i]));//���� ascii�ڵ��� �ڵ�� ���ڷ� ��ȯ
	}

	unsigned long long x_pre=0;
	x_pre=preProcessing(initial);

	double result;

	result = hashing(A, 2048, x_pre);//�ؽ�

	std::cout << "hash result : " << result << std::endl;
	}


	return 0;
}