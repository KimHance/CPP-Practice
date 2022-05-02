#ifndef ATMACHINE_H
#define ATMACHINE_H

#include<string>
#include"Account.h"
#include"Statistics.h"

using std::string;

#define NEGATIVE_ATM_BALANCE -10 // ATM 잔액 부족

class ATMachine {
private:
	int aclist[901]; //100~1000사이 901개
	Account* pAcctArray; // 동적 생성된 고객계좌 배열 포인터
	int nMachineBalance; // ATM 잔고
	int makeRandNum(int index); //중복 제거
	int nMaxAccountNum; // 동적 생성된 고객계좌 배열 크기
	string strManagerPassword; // 관리자 비밀번호
	inline bool isExist(int id); // 계좌 존재 확인 
	
	// 프로젝트 2차 추가
	bool isManager(string password);  // 매니저 암호 확인
	void displayReport();  // 통계 화면 처리
	static int nCurrentAccountNum ; // 개설된 고객 계좌 수
	static int baseNum; // 마지막 계좌 생성 위치
public:
	ATMachine(int size, int balance, string password); // 계좌 배열크기, ATM 잔고, 관리자 암호 초기화
	~ATMachine();
	void displayMenu(); // ATM 기능 선택 화면
	void createAccount(); // 계좌 개설
	void closeAccount(); // 계좌 해지
	void checkMoney(); // 계좌 조회
	void depositMoney(); // 계좌 입금
	void withdrawMoney(); // 계좌 출금

	// 프로젝트 2차 추가
	void transferMoney(int id, int money); // 계좌 이체
	void transfer(); // 계좌 이체
	void managerModel(); // 고객 관리
	static int getCurAcNum() { return nCurrentAccountNum; }
	static int getBaseNum() { return baseNum; }
};
#endif