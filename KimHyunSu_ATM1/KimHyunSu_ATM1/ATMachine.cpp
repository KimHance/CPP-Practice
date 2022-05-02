#include<iostream>
#include<time.h>
#include<stdlib.h>

#include"ATMachine.h"

using namespace std;

void ATMachine::displayMenu() {
	cout << "------------------------" << endl;
	cout << "-     TUKOREA BANK     -" << endl;
	cout << "------------------------" << endl;
	cout << " 1. 계좌 개설" << endl;
	cout << " 2. 계좌 조회" << endl;
	cout << " 3. 계좌 입금" << endl;
	cout << " 4. 계좌 출금" << endl;
	cout << " 5. 계좌 이체" << endl;
	cout << " 6. 계좌 해지" << endl;
	cout << " 7. 고객 관리" << endl;
	cout << " 9. 업무 종료" << endl;
}
ATMachine::ATMachine(int size, int balance, string password) {
	this->nMaxAccountNum = size;
	this->nMachineBalance = balance;
	this->strManagerPassword = password;
	this->pAcctArray = new Account[size];
}
void ATMachine::createAccount() {
	string name;
	string passwd;

	// 회원수 비교하며 추가
	if (ATMachine::nCurrentAccountNum < this->nMaxAccountNum) {
		cout << " ------ 개설 ------" << endl;
		cout << " 이름 입력 : ";
		cin >> name;
		cout << " 암호 입력 : ";
		cin >> passwd;

		
		// 앞에서 부터 비어있는 공간에 계좌 생성
		for (int i = 0; i < nMaxAccountNum; i++) { //중간에 비어있는 공간 고려하여
			if (this->pAcctArray[i].getAcctID() == AUTHENTIFICATION_FAIL) { //초기값이면
				this->pAcctArray[ATMachine::nCurrentAccountNum].create(makeRandNum(i), 0, name, passwd);
				cout << "\n" << name << "님 " << this->pAcctArray[ATMachine::nCurrentAccountNum].getAcctID() << "번 계좌번호가 정상적으로 생성되었습니다. 감사합니다\n" << endl;
				ATMachine::nCurrentAccountNum++;
				ATMachine::baseNum++;
				break;
			}
		}
	}
	else {
		cout << "(회원수 초과) 등록 불가" << endl;
	}
}
void ATMachine::checkMoney() {
	int acNum;
	string passwd;
	int check = 0;

	cout << " ------ 조회 ------" << endl;
	cout << " 계좌번호 입력 : ";
	cin >> acNum;
	if (cin.fail()) {
		cout << "숫자를 입력하세요.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	cout << " 비밀번호 입력 : ";
	cin >> passwd;

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (this->pAcctArray[i].check(acNum, passwd) != -1) { //-1 이면 존재하는 계정x
			cout << " 현재 잔액 : " << this->pAcctArray[i].check(acNum, passwd) << "\n" << endl;
			check = 1; //체크 걸림 
			break;
		}
	}

	// 체크 여부 확인
	if (check != 1)cout << "\n 입력하신 정보가 존재하지 않습니다.\n" << endl;
}
ATMachine::~ATMachine() {
	delete[] this->pAcctArray;
}
void ATMachine::closeAccount() {
	int acNum;
	string passwd;
	int check = 0;
	cout << " ------ 조회 ------" << endl;
	cout << " 계좌번호 입력 : ";
	cin >> acNum;
	if (cin.fail()) {
		cout << "숫자를 입력하세요.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	cout << " 비밀번호 입력 : ";
	cin >> passwd;

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (this->pAcctArray[i].check(acNum, passwd) != -1) { //-1 이면 존재하는 계정x
			
			int nb = this->pAcctArray[i].check(acNum, passwd);
			//잔고가 0이면 해지 가능
			if (nb != 0) {
				cout << "\n" << acNum << " 계좌를 해지할 수 없습니다. 잔액 : " << this->pAcctArray[i].check(acNum, passwd) << "\n" << endl;
			}
			else {
				cout << "\n" << acNum << " 계좌가 해지되었습니다 감사합니다.\n" << endl;
				this->pAcctArray[i].close();
				ATMachine::nCurrentAccountNum--;
			}
			check = 1;
			break;

		}
	}
	// 체크 여부 확인
	if (check != 1)cout << "\n 입력하신 정보가 존재하지 않습니다.\n" << endl;
}
void ATMachine::withdrawMoney() {
	int acNum;
	string passwd;
	int check = 0;

	cout << " ------ 출금 ------" << endl;
	cout << " 계좌번호 입력 : ";
	cin >> acNum;
	if (cin.fail()) {
		cout << "숫자를 입력하세요.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	cout << " 비밀번호 입력 : ";
	cin >> passwd;

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (this->pAcctArray[i].check(acNum, passwd) != -1) { //-1 이면 존재하는 계정x
			int nb = this->pAcctArray[i].check(acNum, passwd);
			if (nb == 0) {
				cout << "\n 출금 가능한 금액이 없습니다.\n" << endl;
				check = 1;
				break;
			}
			int money;
			cout << " 출금액  입력: ";
			cin >> money;
			if (cin.fail()) {
				cout << "숫자를 입력하세요.\n" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}

			// 0이햐면 돌아감
			if (money <= 0) { cout << "\n 잘못 입력하였습니다.\n" << endl; }
			else {
				if (money > this->nMachineBalance) {
					cout << "\n ATM 잔고가 부족합니다. 다른기계를 이용하세요\n" << endl;
					check = 1;
					break;
				}
				if (this->pAcctArray[i].check(acNum, passwd) >= money) {
					int curMoney = this->pAcctArray[i].withdraw(acNum, passwd, money);
					this->nMachineBalance -= money; //ATM 잔고 감소
					cout << "\n 현재잔액 : " << curMoney << "\n 출금완료\n" << endl;
					check = 1;
					break;
				}
				else {
					cout << "\n 통장 잔고가 부족합니다.\n" << endl;
					check = 1;
					break;
				}

			}
		}
	}

	// 체크 여부 확인
	if (check != 1)cout << "\n 입력하신 정보가 존재하지 않습니다.\n" << endl;

}
void ATMachine::depositMoney() {
	int acNum;
	string passwd;
	int check = 0;

	cout << " ------ 입금 ------" << endl;
	cout << " 계좌번호 입력 : ";
	cin >> acNum;
	if (cin.fail()) {
		cout << "숫자를 입력하세요.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	cout << " 비밀번호 입력 : ";
	cin >> passwd;
	

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (int nb = this->pAcctArray[i].check(acNum, passwd) != -1) { //-1 이면 존재하는 계정x
			int depo;
			cout << " 입금액  입력: ";
			cin >> depo;
			if (cin.fail()) {
				cout << "숫자를 입력하세요.\n" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}

			// 0이햐면 돌아감
			if (depo <= 0) {cout << "\n 잘못 입력하였습니다.\n" << endl;}
			else {
				int curMoney = this->pAcctArray[i].deposit(acNum, passwd, depo);
				this->nMachineBalance += depo; //ATM 잔고 증가
				cout << "\n 현재잔액 : " << curMoney <<"\n 입금완료\n" << endl;
			}
			check = 1;
			break;

		}
	}

	// 체크 여부 확인
	if (check != 1)cout << "\n 입력하신 정보가 존재하지 않습니다.\n" << endl;
}
int ATMachine::makeRandNum(int index) {
	srand(time(NULL));
	int rn;
	for (int i = 0; i < 901; i++)
	{
	again:;
		rn = rand() % 901 + 100;
		for (int j = 0; j < i; j++) {
			if (rn == this->aclist[j])
				goto again;
		}
		this->aclist[i] = rn;
	}

	return this->aclist[index];
}

// 프로젝트 2차 추가
void ATMachine::transferMoney(int id, int money) {

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (this->pAcctArray[i].getAcctID() == id) { //	보내려는 계정 존재하면
			this->pAcctArray[i].deposit(id, money);
		}
	}
}
void ATMachine::transfer() {
	int acNum;
	string passwd;
	int check = 0;

	cout << " ------ 이체 ------" << endl;
	cout << " 계좌번호 입력 : ";
	cin >> acNum;
	if (cin.fail()) {
		cout << "숫자를 입력하세요.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	cout << " 비밀번호 입력 : ";
	cin >> passwd;

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (this->pAcctArray[i].check(acNum, passwd) != -1) { //-1 이면 존재하는 계정x
			int transfer_ac;
			int transfer_depo;
			cout << " 이체계좌 입력 : ";
			cin >> transfer_ac;
			if (cin.fail()) {
				cout << "숫자를 입력하세요.\n" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
			cout << " 이체금액 입력 : ";
			cin >> transfer_depo;
			if (cin.fail()) {
				cout << "숫자를 입력하세요.\n" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}

			if (isExist(transfer_ac)) {
				if (this->pAcctArray[i].check(acNum, passwd) < transfer_depo) {
					cout << " 통장 잔액이 부족합니다.\n" << endl;
					check = 1;
					break;
				}
				transferMoney(transfer_ac, transfer_depo);
				this->pAcctArray[i].withdraw(transfer_depo);
			}
			else {
				break;
			}
			cout << " 현재 잔액 : " << this->pAcctArray[i].check(acNum, passwd) << endl;
			cout << " 이체 완료\n" << endl;
			
			check = 1;
			break;

		}
	}
	// 체크 여부 확인
	if (check != 1)cout << "\n 입력하신 정보가 존재하지 않습니다.\n" << endl;
}
inline bool ATMachine::isExist(int id) {

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (this->pAcctArray[i].getAcctID() == id) {
			return true;
		}
	}
	return false;
}
bool ATMachine::isManager(string password) {
	if (password == this->strManagerPassword)
		return true;
	else return false;
}
void ATMachine::displayReport() {
	cout<< " --------------------" << endl;
	cout << " ATM 현재 잔고:		" << this->nMachineBalance << "원" << endl;
	cout << " 고객 잔고 총액:	" << Statistics::sum(this->pAcctArray, ATMachine::baseNum) << "원(총" << ATMachine::nCurrentAccountNum<<"명)" << endl; //구현 필요
	cout << " 고객 잔고 평균:	" << Statistics::average(this->pAcctArray, ATMachine::baseNum) << "원" << endl; //구현 필요
	cout << " 고객 잔고 최고:	" << Statistics::max(this->pAcctArray, ATMachine::baseNum) << "원" << endl;  //구현 필요
	cout << " --------------------" << endl;
	cout << " -  고객 계좌 목록  -" << endl;
	cout << " --------------------" << endl;
	Statistics::accountSort(this->pAcctArray, ATMachine::baseNum);
}
void ATMachine::managerModel() {
	string passwd;
	cout << " ------ 관리 ------" << endl;
	cout << " 관리자 비밀번호 입력 : ";
	cin >> passwd;
	if (cin.fail()) {
		cout << "숫자를 입력하세요.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	if (isManager(passwd)) {
		cout << "\n관리자입니다.\n" << endl;
		displayReport();
	}
	else cout << "\n비밀번호 오류 입니다.\n" << endl;
}