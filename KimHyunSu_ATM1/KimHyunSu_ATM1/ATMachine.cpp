#include<iostream>
#include<string>
#include<time.h>
#include<stdlib.h>


#include "ATMachine.h"
#include "Account.h"

using namespace std;

int aclist[901]; //100~1000���� 901��

int makeRandNum(int index) { //�ߺ� ���� 
	srand(time(NULL));
	int rn;
	for (int i = 0; i < 901; i++)
	{
	again:;
		rn = rand() % 901 + 100;
		for (int j = 0; j < i; j++) {
			if (rn == aclist[j])
				goto again;
		}
		aclist[i] = rn;
	}

	return aclist[index];
}

void ATMachine::displayMenu() {
	cout << "------------------------" << endl;
	cout << "-     TUKOREA BANK     -" << endl;
	cout << "------------------------" << endl;
	cout << " 1. ���� ����" << endl;
	cout << " 2. ���� ��ȸ" << endl;
	cout << " 3. ���� �Ա�" << endl;
	cout << " 4. ���� ���" << endl;
	cout << " 6. ���� ����" << endl;
	cout << " 9. ���� ����" << endl;
}

ATMachine::ATMachine(int size, int balance, string password) {
	this->nMaxAccountNum = size;
	this->nMachineBalance = balance;
	this->strManagerPassword = password;
	this->nCurrentAccountNum = 0; //���� ���¼� 0���� �ʱ�ȭ
	this->pAcctArray = new Account[size];
}

void ATMachine::createAccount() {
	string name;
	string passwd;

	// ȸ���� ���ϸ� �߰�
	if (this->nCurrentAccountNum < this->nMaxAccountNum) {
		cout << " ------ ���� ------" << endl;
		cout << " �̸� �Է� : ";
		cin >> name;
		cout << " ��ȣ �Է� : ";
		cin >> passwd;

		
		// �տ��� ���� ����ִ� ������ ���� ����
		for (int i = 0; i < nMaxAccountNum; i++) { //�߰��� ����ִ� ���� ����Ͽ�
			if (this->pAcctArray[i].getAcctID() == -1) { //�ʱⰪ�̸�
				this->pAcctArray[this->nCurrentAccountNum].create(makeRandNum(i), 0, name, passwd);
				cout << "\n" << name << "�� " << this->pAcctArray[this->nCurrentAccountNum].getAcctID() << "�� ���¹�ȣ�� ���������� �����Ǿ����ϴ�. �����մϴ�\n" << endl;
				this->nCurrentAccountNum++;
				break;
			}
		}
	}
	else {
		cout << "(ȸ���� �ʰ�) ��� �Ұ�" << endl;
	}
}

void ATMachine::checkMoney() {
	int acNum;
	string passwd;
	int check = 0;

	cout << " ------ ��ȸ ------" << endl;
	cout << " ���¹�ȣ �Է� : ";
	cin >> acNum;
	cout << " ��й�ȣ �Է� : ";
	cin >> passwd;

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if ( this->pAcctArray[i].check(acNum, passwd) != -1) { //-1 �̸� �����ϴ� ����x
			cout << " ���� �ܾ� : " << this->pAcctArray[i].check(acNum, passwd) << "\n" << endl;
			check = 1; //üũ �ɸ� 
			break;
		}
	}

	// üũ ���� Ȯ��
	if (check != 1)cout << "\n �Է��Ͻ� ������ �������� �ʽ��ϴ�.\n" << endl;
}

ATMachine::~ATMachine() {
}

void ATMachine::closeAccount() {
	int acNum;
	string passwd;
	int check = 0;
	cout << " ------ ��ȸ ------" << endl;
	cout << " ���¹�ȣ �Է� : ";
	cin >> acNum;
	cout << " ��й�ȣ �Է� : ";
	cin >> passwd;

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (this->pAcctArray[i].check(acNum, passwd) != -1) { //-1 �̸� �����ϴ� ����x
			
			int nb = this->pAcctArray[i].check(acNum, passwd);
			//�ܰ� 0�̸� ���� ����
			if (nb != 0) {
				cout << "\n" << acNum << " ���¸� ������ �� �����ϴ�. �ܾ� : " << this->pAcctArray[i].check(acNum, passwd) << "\n" << endl;
			}
			else {
				cout << "\n" << acNum << " ���°� �����Ǿ����ϴ� �����մϴ�.\n" << endl;
				this->pAcctArray[i].close();
				this->nCurrentAccountNum--;
			}
			check = 1;
			break;

		}
	}
	// üũ ���� Ȯ��
	if (check != 1)cout << "\n �Է��Ͻ� ������ �������� �ʽ��ϴ�.\n" << endl;
}

void ATMachine::depositMoney() {
	int acNum;
	string passwd;
	int check = 0;

	cout << " ------ �Ա� ------" << endl;
	cout << " ���¹�ȣ �Է� : ";
	cin >> acNum;
	cout << " ��й�ȣ �Է� : ";
	cin >> passwd;

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (int nb = this->pAcctArray[i].check(acNum, passwd) != -1) { //-1 �̸� �����ϴ� ����x
			int depo;
			cout << " �Աݾ�  �Է�: ";
			cin >> depo;

			// 0����� ���ư�
			if (depo <= 0) {cout << "\n �߸� �Է��Ͽ����ϴ�.\n" << endl;}
			else {
				int curMoney = this->pAcctArray[i].deposit(acNum, passwd, depo);
				this->nMachineBalance += depo; //ATM �ܰ� ����
				cout << "\n �����ܾ� : " << curMoney <<"\n �ԱݿϷ�\n" << endl;
			}
			check = 1;
			break;

		}
	}

	// üũ ���� Ȯ��
	if (check != 1)cout << "\n �Է��Ͻ� ������ �������� �ʽ��ϴ�.\n" << endl;
}

void ATMachine::withdrawMoney(){
	int acNum;
	string passwd;
	int check = 0;

	cout << " ------ ��� ------" << endl;
	cout << " ���¹�ȣ �Է� : ";
	cin >> acNum;
	cout << " ��й�ȣ �Է� : ";
	cin >> passwd;

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (this->pAcctArray[i].check(acNum, passwd) != -1) { //-1 �̸� �����ϴ� ����x
			int nb = this->pAcctArray[i].check(acNum, passwd);
			if (nb == 0) {
				cout << "\n ��� ������ �ݾ��� �����ϴ�.\n" << endl;
				check = 1;
				break;
			}
			int money;
			cout << " ��ݾ�  �Է�: ";
			cin >> money;

			// 0����� ���ư�
			if (money <= 0) { cout << "\n �߸� �Է��Ͽ����ϴ�.\n" << endl; }
			else {
				if (money > this->nMachineBalance) {
					cout << "\n ATM �ܰ� �����մϴ�. �ٸ���踦 �̿��ϼ���\n" << endl;
					check = 1;
					break;
				}
				if (this->pAcctArray[i].check(acNum,passwd) >= money) {
					int curMoney = this->pAcctArray[i].withdraw(acNum, passwd, money);
					this->nMachineBalance -= money; //ATM �ܰ� ����
					cout << "\n �����ܾ� : " << curMoney << "\n ��ݿϷ�\n" << endl;
					check = 1;
					break;
				}
				else {
					cout << "\n ���� �ܰ� �����մϴ�.\n" << endl;
					check = 1;
					break;
				}
					
			}		
		}
	}

	// üũ ���� Ȯ��
	if (check != 1)cout << "\n �Է��Ͻ� ������ �������� �ʽ��ϴ�.\n" << endl;

}