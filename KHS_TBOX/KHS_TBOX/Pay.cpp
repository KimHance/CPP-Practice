#include <iostream>
#include <string>
#include "Pay.h"
using namespace std;

int CardPay::charge(int amount) {
	string cardNum;
	string name;

	cout << "	[ 신용카드 결제 ]" << endl;
	cout << "카드 번호 입력(12자리수) : ";
	cin >> cardNum;
	if (cardNum.length() != 12)
		cout << "카드 번호 입력 오류" << endl;
	else {
		cout << "이름 : ";
		cin >> name;
		int totalAmount = amount + amount * interest;
		cout << " 신용카드 결제가 완료되었습니다. : " << totalAmount << endl;
		return totalAmount;
	}
		
	return 0;
}

int BankTransfer::charge(int amount) {
	string bankNum;
	string name;

	cout << "	[ KPU 은행 결제 ]" << endl;
	cout << "은행 번호 입력(12자리수) : ";
	cin >> bankNum;
	if (bankNum.length() != 12)
		cout << "은행 번호 입력 오류" << endl;
	else {
		cout << "이름 : ";
		cin >> name;
		int totalAmount = amount + amount * interest;
		cout << " KPU 은행 결제가 완료되었습니다. : " << totalAmount << endl;
		return totalAmount;
	}

	return 0;
}

int MobilePay::charge(int amount) {
	string phoneNum;
	string name;

	cout << "	[ 모바일 결제 ]" << endl;
	cout << "전화번호 입력(11자리수) : ";
	cin >> phoneNum;
	if (phoneNum.length() != 11)
		cout << "전화번호 입력 오류" << endl;
	else {
		cout << "이름 : ";
		cin >> name;
		int totalAmount = amount + amount * interest;
		cout << "신용카드 결제가 완료되었습니다. : " << totalAmount << endl;
		return totalAmount;
	}

	return 0;
}