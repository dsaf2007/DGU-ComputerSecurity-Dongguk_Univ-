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

std::string dec2bi(int dec)
{
	std::string s="";
	int n = dec;
	while (dec > 1)
	{
		if (dec % 2 == 1)
		{
			s += "1";
		}
		else
		{
			s += "0";
		}
		dec /= 2;
	}
	s += "1";
	
	int length = 8 - s.length();
	for (int i = 0; i < length; i++)
	{
		s += "0";
	}
	reverse(s.begin(), s.end());
	return s;
}
std::string toBinary(int n)
{
	std::string r;
	while (n != 0) {
		r += (n % 2 == 0 ? "0" : "1");
		n /= 2;
	}
	return r;
}
unsigned long long preProcessing(std::vector<int>& input)
{
	std::string output = "";
	input.push_back(0b10000000);
	unsigned long long binary=0;
	int L = input.size();

	int k = 64 - (((L % 64) + 9) % 64);
	if (k == 64) k = 0;

	for (int i = 0; i < k; i++)
	{
		input.push_back(0);
	}

	uint64_t bitLengthInBigEndian = changeEndian(L * 8);
	auto ptr = reinterpret_cast<uint8_t*>(&bitLengthInBigEndian);

	input.insert(std::end(input), ptr, ptr + 8);
	//std::cout << dec2bi(input[0]);
	for (int i = 0; i < input.size(); i++)
	{
		output += toBinary(input[i]);
	}

	for (int i = 0; i < output.length(); i++)
	{
		binary = (binary << 1) + output[i] - '0';
	}

	return binary;
}


double hashing(double A,int m,unsigned long long x)
{
	double hash = m * ((x*A)-(long long)(x*A));

	return hash;
}

int main()
{
	std::string x; double A;
	std::cout << "x : ";
	std::cin >> x;
	std::cout << "A : ";
	std::cin >> A;
	
	std::vector<int> initial;
	
	for (int i = 0; i < x.length(); i++)
	{
		initial.push_back(((int)x[i]));
	}
	//std::cout << dec2bi(initial[1]);
	unsigned long long x_pre=0;
	x_pre=preProcessing(initial);

	double result;

	result = hashing(A, 2048, x_pre);

	std::cout << "hash result : " << result << std::endl;



	return 0;
}