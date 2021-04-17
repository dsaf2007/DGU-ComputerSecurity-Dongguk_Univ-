#include <iostream>
#include <cstdlib>
#include <fstream>
#include <time.h>
#include <chrono>
int gdb(int a, int b)
{
	int temp, x = a, y = b;
	while (y != 0)
	{
		temp = y;
		y = x % y;
		x = temp;
	}
	return x;
}

int randPrime(int n)
{

	int a = rand();
	while (gdb(a, n) != 1)
	{
		a = rand();
	}
	return a;
}
int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	srand(time(NULL));
	int N;
	int rangeMax = 99999;
	int rangeMin = 10000;
	std::ofstream output("./test_6.txt");
	clock_t start, end;

	for (int i = 0; i < 100; i++)
	{
		N = (int)(((double)((rand() << 15) | rand())) / (((RAND_MAX << 15) | RAND_MAX) + 1) * (rangeMax - rangeMin) + rangeMin);

		int k = randPrime(N);

		int x = 1;
		std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
		for (int result = k % N; result != 1; ++x)
		{
			result = (result * k) % N;
		}
		std::chrono::duration<double> sec = std::chrono::system_clock::now() - start;
		std::cout << "<" << i << ">" << k << "^" << x << " mod " << N << " = 1 | time : " << sec.count() << "ÃÊ\n";
		output << "<" << i << ">" << k << "^" << x << " mod " << N << " = 1 | time : " << sec.count() << "ÃÊ\n";
	}

	return 0;
}