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
	return r;//string형태로 출력
}
unsigned long long preProcessing(std::vector<int>& input)//입력 값 전처리
{
	std::string output = "";
	input.push_back(0b10000000);//입력 값 뒤에 1 1개 추가
	unsigned long long binary=0;
	int L = input.size();

	int k = 64 - (((L % 64) + 9) % 64);//크기를 맞추기 위해
	if (k == 64) k = 0;

	for (int i = 0; i < k; i++)//부족한 만큼 뒤에 0추가
	{
		input.push_back(0);
	}

	uint64_t bitLengthInBigEndian = changeEndian(L * 8);
	auto ptr = reinterpret_cast<uint8_t*>(&bitLengthInBigEndian);

	input.insert(std::end(input), ptr, ptr + 8);//마지막 8비트에 문자열 크기 입력

	for (int i = 0; i < input.size(); i++)//이진수 형태의 문자열로 변환하여 합친다.
	{
		output += toBinary(input[i]);
	}

	for (int i = 0; i < output.length(); i++)
	{
		binary = (binary << 1) + output[i] - '0';//합쳐진 이진수 정수로 변환
	}

	return binary;
}


double hashing(double A,int m,unsigned long long x)//multiplication Method
{
	double hash = m * ((x*A)-(long long)(x*A));//m 2의 제곱수, A 0과1사이의 소수 , x 입력값.

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
		initial.push_back(((int)x[i]));//문자 ascii코드의 코드로 숫자로 변환
	}

	unsigned long long x_pre=0;
	x_pre=preProcessing(initial);

	double result;

	result = hashing(A, 2048, x_pre);//해싱

	std::cout << "hash result : " << result << std::endl;
	}


	return 0;
}