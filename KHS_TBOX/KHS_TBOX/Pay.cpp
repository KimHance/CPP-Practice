#include <iostream>
#include <string>
#include "Pay.h"
using namespace std;

int CardPay::charge(int amount) {
	string cardNum;
	string name;

	cout << "	[ �ſ�ī�� ���� ]" << endl;
	cout << "ī�� ��ȣ �Է�(12�ڸ���) : ";
	cin >> cardNum;
	if (cardNum.length() != 12)
		cout << "ī�� ��ȣ �Է� ����" << endl;
	else {
		cout << "�̸� : ";
		cin >> name;
		int totalAmount = amount + amount * interest;
		cout << " �ſ�ī�� ������ �Ϸ�Ǿ����ϴ�. : " << totalAmount << endl;
		return totalAmount;
	}
		
	return 0;
}

int BankTransfer::charge(int amount) {
	string bankNum;
	string name;

	cout << "	[ KPU ���� ���� ]" << endl;
	cout << "���� ��ȣ �Է�(12�ڸ���) : ";
	cin >> bankNum;
	if (bankNum.length() != 12)
		cout << "���� ��ȣ �Է� ����" << endl;
	else {
		cout << "�̸� : ";
		cin >> name;
		int totalAmount = amount + amount * interest;
		cout << " KPU ���� ������ �Ϸ�Ǿ����ϴ�. : " << totalAmount << endl;
		return totalAmount;
	}

	return 0;
}

int MobilePay::charge(int amount) {
	string phoneNum;
	string name;

	cout << "	[ ����� ���� ]" << endl;
	cout << "��ȭ��ȣ �Է�(11�ڸ���) : ";
	cin >> phoneNum;
	if (phoneNum.length() != 11)
		cout << "��ȭ��ȣ �Է� ����" << endl;
	else {
		cout << "�̸� : ";
		cin >> name;
		int totalAmount = amount + amount * interest;
		cout << "�ſ�ī�� ������ �Ϸ�Ǿ����ϴ�. : " << totalAmount << endl;
		return totalAmount;
	}

	return 0;
}