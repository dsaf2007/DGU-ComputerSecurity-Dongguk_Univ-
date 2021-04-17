#include <iostream>
#include <string>

class Caeser//시저 암호
{
public:
	void encrypt(int key)//암호화
	{
		key = key % 26;//26 이상의 숫자를 입력 받을 경우 대비
		for (int i = 0; i < plain_text.length(); i++)//입력받은 평문 길이만큼
		{
			if (plain_text[i] == ' ')//공백은 그대로 암호문에 입력
			{
				encrypt_str += plain_text[i];
			}
			else
			{
				if((int)plain_text[i]+key >122)
					encrypt_str += (char)((int)plain_text[i] + key-26);//z인 122를 넘어갈 경우 -26을 하여 앞으로 돌린다.
				else
					encrypt_str += (char)((int)plain_text[i] + key);//ascii code이용. int로 명시적 형변환 후 숫자를 더해서 시저 암호화 후 char로 다시 형변환
			}			
		}
	}
	void decrypt(int key)//복호화
	{
		key = key % 26;
		for (int i = 0; i < encrypt_str.length(); i++)
		{
			if (plain_text[i] == ' ')//공백일시 그대로 입력
			{
				decrypt_str += encrypt_str[i];
			}
			else
			{
				if ((int)encrypt_str[i] - key < 97)
					decrypt_str += (char)((int)plain_text[i] - key + 26);//a인 97보다 작을 경우 +26을 하여 z로 넘어가게 한다.
				else
					decrypt_str += (char)((int)plain_text[i] -key);//ascii code이용. int로 명시적 형변환 후 숫자를 더해서 시저 암호화 후 char로 다시 형변환
			}
		}
	}
	void getPlainText(std::string input_string)//평문을 입력받는다.
	{
		plain_text = input_string;
	}
	std::string plain_text;//입력받을 평문
	std::string encrypt_str;//암호문
	std::string decrypt_str;//복호문
};

class SimpleSubstitution//단일 치환 암호
{
public:
	void encrypt()//암호화
	{
		for (int i = 0; i < plain_text.length(); i++)
		{
			if (plain_text[i] == ' ')//공백일 경우 바로 문자열에 추가
			{
				encrypt_str += plain_text[i];
			}
			else
			{
				for (int j = 0; j < 27; j++)//평문 테이블과 비교하여 일치 할 때 해당 index를 가지는 암호 테이블 문자를 문자열에 입력
				{
					if (plain_text[i] == plain_table[j])
						encrypt_str += encrypt_table[j];
				}
			}
		}
	}
	void decrypt()//복호화
	{
		for (int i = 0; i < encrypt_str.length(); i++)
		{
			if (encrypt_str[i] == ' ')
			{
				decrypt_str += encrypt_str[i];
			}
			else
			{
				for (int j = 0; j < 27; j++)//암호 테이블과 비교하여 일치 할 때 해당 index를 가지는 암호 테이블 문자를 문자열에 입력
				{
					if (encrypt_str[i] == encrypt_table[j])
						decrypt_str += plain_table[j];
				}
			}
		}
	}
	void getPlainText(std::string input_string)
	{
		plain_text = input_string;
	}
	std::string plain_text;//평문
	std::string encrypt_str;//암호문
	std::string decrypt_str;//복호문
private:
	char plain_table[27] = "abcdefghijklmnopqrstuvwxyz"; // 평문 테이블
	char encrypt_table[27] = "WYHFXUMTJVSGENBRDZLQAPCOKI";// 암호 테이블
};

int main()
{
	int cmd;
	std::string input;
	int key;
	Caeser a;
	SimpleSubstitution b;
	while (1)
	{	
		std::cout << "1. caeser encryption\n";
		std::cout << "2. caeser decryption\n";
		std::cout << "3. simple substitution cipher encryption\n";
		std::cout << "4. simple substitution cipher decryption\n";
		std::cout << "5. exit\n";
		std::cout << "Select menu : ";
		std::cin >> cmd;
		std::cin.ignore();
		switch (cmd)
		{
		case 1:
			std::cout << "Enter text to encrypt : ";
			std::getline(std::cin, input);
			std::cout << "enter key : ";
			std::cin >> key;
			a.getPlainText(input);
			a.encrypt(key);
			std::cout << "Text encrypted : " << a.encrypt_str << "\n";
			break;
		case 2:
			std::cout << "Enter text to decrypt : ";
			std::getline(std::cin, input);
			std::cout << "enter key : ";
			std::cin >> key;
			a.getPlainText(input);
			a.decrypt(key);
			std::cout << "Text decrypted : " << a.decrypt_str << "\n";
			break;
		case 3:
			std::cout << "Enter text to encrypt : ";
			std::getline(std::cin, input);
			b.getPlainText(input);
			b.encrypt();
			std::cout << "Text encrypted : " << b.encrypt_str << "\n";
			break;
		case 4:
			std::cout << "Enter text to decrypt : ";
			std::getline(std::cin, input);
			b.getPlainText(input);
			b.decrypt();
			std::cout << "Text decrypted : " << b.decrypt_str << "\n";
			break;
		case 5:
			std::cout << "exit program\n";
			exit(0);
			break;
		}
		std::cout << "-------------------------------------\n";
	}
}