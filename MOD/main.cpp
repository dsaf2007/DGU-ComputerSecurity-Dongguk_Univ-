#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <chrono>
#include <random>
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

	int a =  rand();
	while (gdb(a, n) != 1)
	{
		a = rand();
	}
	return a;
}

long long pow(long long k, int x, int N) {
	if (x == 0) return 1;
	if (x == 1) return k;
	if (x % 2 == 1) return (k * pow(k * k % N, x / 2, N)) % N;
	if (x % 2 == 0) return pow(k * k % N, x / 2, N) % N;
}
int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	srand(time(NULL));
	int N;
	int rangeMax = 9999;
	int rangeMin = 1000;
	std::ofstream output("./test_4.txt");
	clock_t start, end;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(rangeMin, rangeMax);
	int R[100]; 
	for (int i = 0; i < 100; i++)
	{
		R[i] = dis(gen);
		std::cout << i<<" "<<R[i] << std::endl;
	}

	for (int i = 0; i < 100; i++)
	{

		std::chrono::system_clock::time_point StartTime = std::chrono::system_clock::now();
		int k = randPrime(R[i]);
		int x = 1;
		for (int result = k % R[i]; result != 1; ++x)
		{
			result = pow(result, x, R[i]);

		}
		
		std::chrono::system_clock::time_point EndTime = std::chrono::system_clock::now();
		std::chrono::nanoseconds mill = std::chrono::duration_cast<std::chrono::nanoseconds>(EndTime - StartTime);
		std::cout << "<" << i << ">" << k << "^" << x << " mod " << R[i] << " = 1 | time : " << mill.count() << "nanosec\n";
		output << "<" << i << ">" << k << "^" << x << " mod " << R[i] << " = 1 | time : " << mill.count() << "nanosec\n";
	}

	return 0;
}