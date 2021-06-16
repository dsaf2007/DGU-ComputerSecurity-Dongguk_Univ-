#pragma once
#include "DES.h"
#include <time.h>
#include <thread>
#include <mutex>


class CTR
{
public:
	CTR(std::string input, std::string key_, std::string nonce_);//생성자
	void setKey(std::string key_);//key setter
	void parseString();//문자열 64비트 단위로 잘라 저장
	std::string XORBlock(std::string prev_enc_, std::string block_);//xor 연산
	std::string counterStream(int index);//nonce와 블록 번호를 결합하여 카운터 생성
	void encdec(int x, int n);//암호화 복호화
	int getThreadNum();//적절한 멀티스레드 개수 반환
	void execute();//실행
	void nonMulti();//단일 스레드 실행
	std::string getResult();// 암호화 복호화 결과 리턴
	std::string dec2hex(int d);//10진수 16진수 변환
private:
	std::string input_string; //입력 문자열
	std::vector<std::string> str_vec;//파싱한 문자열
	std::vector<std::string> result_vec;//암호화 복호화 한 결과
	std::string nonce;//비표
	std::string arr = "0123456789ABCDEF";
	int last_block_length;//마지막 블록 문자열 길이
	std::string key;//키
	std::vector<std::thread> threads;//멀티스레드 벡터
};

