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
std::string dec2bi(uint8_t dec)
{
	std::string s;
	while (dec > 1)
	{
		if (dec % 2 == 1)
			s += '1';
		else
			s += '0';
		dec / 2;
	}
	s += '1';
	reverse(s.begin(), s.end());

	return s;
}

int preProcessing(std::vector<int>& input)
{
	std::string output = "";
	input.push_back(0b10000000);
	int binary=0;
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
	 std::cout << input[63];
	for (int i = 0; i < input.size(); i++)
	{
		output += dec2bi(input[i]);
	}

	for (int i = 0; i < output.length(); i++)
	{
		binary = (binary << 1) + output[i] - '0';
	}

	return binary;
}


double hashing(double A,int m,int x)
{
	double hash = m * ((x*A)-(int)(x*A));

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
	std::cout << initial[0];
	int x_pre=0;
	x_pre=preProcessing(initial);

	double result;

	result = hashing(A, 512, x_pre);

	std::cout << "hash result : " << result << std::endl;



	return 0;
}