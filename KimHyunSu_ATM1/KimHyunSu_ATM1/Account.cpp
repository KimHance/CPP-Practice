#include<iostream>
#include<string>
#include"Account.h"

using namespace std;

Account::Account() {
	this->nID = -1;
	this->nBalance = 0;
}
void Account::create(int id, int money, string name, string passwd) {
	this->nID = id;
	this->nBalance = money;
	this->strAccountName = name;
	this->strPassword = passwd;
}
inline bool Account::authenticate(int id, string passwd) {
	// �Է� ID, passwd ������ true;
	if (id == this->nID && passwd == this->strPassword) {
		return true;
	}
	// �ƴϸ� false
	return false;
}
void Account::close() {
	this->nID = AUTHENTIFICATION_FAIL;
	this->nBalance = 0;
	this->strAccountName = "";
	this->strPassword = "";
}
int Account::check(int id, string  passwd) {
	// �����ϸ� �ܰ� return
	if (this->authenticate(id, passwd)) {
		return this->nBalance;
	}
	// ������ -1 return
	else {
		return AUTHENTIFICATION_FAIL;
	}
}
int Account::deposit(int id, string password, int money) {
	if (this->authenticate(id, password)) {
		this->nBalance += money;
		return this->nBalance;
	}
	else {
		return AUTHENTIFICATION_FAIL;
	}
	
}

// ������Ʈ 2�� �߰�
int Account::deposit(int id,int money) {
	this->nBalance += money;
	return this->nBalance;
}
int Account::withdraw(int id, string password, int money) {
	if (this->authenticate(id, password)) {
		if (money <= this->nBalance) {
			this->nBalance -= money;
			return this->nBalance;
		}else if(money > this->nBalance) {
			return AUTHENTIFICATION_FAIL;
		}
	}
	else {
		printf("authenticate ����");
		return AUTHENTIFICATION_FAIL;
	}
	
}
void Account::withdraw( int money) {
	this->nBalance -= money;
}

