#include<iostream>
#include<time.h>
#include<stdlib.h>

#include"ATMachine.h"

using namespace std;

void ATMachine::displayMenu() {
	cout << "------------------------" << endl;
	cout << "-     TUKOREA BANK     -" << endl;
	cout << "------------------------" << endl;
	cout << " 1. ���� ����" << endl;
	cout << " 2. ���� ��ȸ" << endl;
	cout << " 3. ���� �Ա�" << endl;
	cout << " 4. ���� ���" << endl;
	cout << " 5. ���� ��ü" << endl;
	cout << " 6. ���� ����" << endl;
	cout << " 7. �� ����" << endl;
	cout << " 9. ���� ����" << endl;
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

	// ȸ���� ���ϸ� �߰�
	if (ATMachine::nCurrentAccountNum < this->nMaxAccountNum) {
		cout << " ------ ���� ------" << endl;
		cout << " �̸� �Է� : ";
		cin >> name;
		cout << " ��ȣ �Է� : ";
		cin >> passwd;

		
		// �տ��� ���� ����ִ� ������ ���� ����
		for (int i = 0; i < nMaxAccountNum; i++) { //�߰��� ����ִ� ���� ����Ͽ�
			if (this->pAcctArray[i].getAcctID() == AUTHENTIFICATION_FAIL) { //�ʱⰪ�̸�
				this->pAcctArray[ATMachine::nCurrentAccountNum].create(makeRandNum(i), 0, name, passwd);
				cout << "\n" << name << "�� " << this->pAcctArray[ATMachine::nCurrentAccountNum].getAcctID() << "�� ���¹�ȣ�� ���������� �����Ǿ����ϴ�. �����մϴ�\n" << endl;
				ATMachine::nCurrentAccountNum++;
				ATMachine::baseNum++;
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
	if (cin.fail()) {
		cout << "���ڸ� �Է��ϼ���.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	cout << " ��й�ȣ �Է� : ";
	cin >> passwd;

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (this->pAcctArray[i].check(acNum, passwd) != -1) { //-1 �̸� �����ϴ� ����x
			cout << " ���� �ܾ� : " << this->pAcctArray[i].check(acNum, passwd) << "\n" << endl;
			check = 1; //üũ �ɸ� 
			break;
		}
	}

	// üũ ���� Ȯ��
	if (check != 1)cout << "\n �Է��Ͻ� ������ �������� �ʽ��ϴ�.\n" << endl;
}
ATMachine::~ATMachine() {
	delete[] this->pAcctArray;
}
void ATMachine::closeAccount() {
	int acNum;
	string passwd;
	int check = 0;
	cout << " ------ ��ȸ ------" << endl;
	cout << " ���¹�ȣ �Է� : ";
	cin >> acNum;
	if (cin.fail()) {
		cout << "���ڸ� �Է��ϼ���.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
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
				ATMachine::nCurrentAccountNum--;
			}
			check = 1;
			break;

		}
	}
	// üũ ���� Ȯ��
	if (check != 1)cout << "\n �Է��Ͻ� ������ �������� �ʽ��ϴ�.\n" << endl;
}
void ATMachine::withdrawMoney() {
	int acNum;
	string passwd;
	int check = 0;

	cout << " ------ ��� ------" << endl;
	cout << " ���¹�ȣ �Է� : ";
	cin >> acNum;
	if (cin.fail()) {
		cout << "���ڸ� �Է��ϼ���.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
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
			if (cin.fail()) {
				cout << "���ڸ� �Է��ϼ���.\n" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}

			// 0����� ���ư�
			if (money <= 0) { cout << "\n �߸� �Է��Ͽ����ϴ�.\n" << endl; }
			else {
				if (money > this->nMachineBalance) {
					cout << "\n ATM �ܰ� �����մϴ�. �ٸ���踦 �̿��ϼ���\n" << endl;
					check = 1;
					break;
				}
				if (this->pAcctArray[i].check(acNum, passwd) >= money) {
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
void ATMachine::depositMoney() {
	int acNum;
	string passwd;
	int check = 0;

	cout << " ------ �Ա� ------" << endl;
	cout << " ���¹�ȣ �Է� : ";
	cin >> acNum;
	if (cin.fail()) {
		cout << "���ڸ� �Է��ϼ���.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	cout << " ��й�ȣ �Է� : ";
	cin >> passwd;
	

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (int nb = this->pAcctArray[i].check(acNum, passwd) != -1) { //-1 �̸� �����ϴ� ����x
			int depo;
			cout << " �Աݾ�  �Է�: ";
			cin >> depo;
			if (cin.fail()) {
				cout << "���ڸ� �Է��ϼ���.\n" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				return;
			}

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

// ������Ʈ 2�� �߰�
void ATMachine::transferMoney(int id, int money) {

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (this->pAcctArray[i].getAcctID() == id) { //	�������� ���� �����ϸ�
			this->pAcctArray[i].deposit(id, money);
		}
	}
}
void ATMachine::transfer() {
	int acNum;
	string passwd;
	int check = 0;

	cout << " ------ ��ü ------" << endl;
	cout << " ���¹�ȣ �Է� : ";
	cin >> acNum;
	if (cin.fail()) {
		cout << "���ڸ� �Է��ϼ���.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	cout << " ��й�ȣ �Է� : ";
	cin >> passwd;

	for (int i = 0; i < this->nMaxAccountNum; i++) {
		if (this->pAcctArray[i].check(acNum, passwd) != -1) { //-1 �̸� �����ϴ� ����x
			int transfer_ac;
			int transfer_depo;
			cout << " ��ü���� �Է� : ";
			cin >> transfer_ac;
			if (cin.fail()) {
				cout << "���ڸ� �Է��ϼ���.\n" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}
			cout << " ��ü�ݾ� �Է� : ";
			cin >> transfer_depo;
			if (cin.fail()) {
				cout << "���ڸ� �Է��ϼ���.\n" << endl;
				cin.clear();
				cin.ignore(256, '\n');
				break;
			}

			if (isExist(transfer_ac)) {
				if (this->pAcctArray[i].check(acNum, passwd) < transfer_depo) {
					cout << " ���� �ܾ��� �����մϴ�.\n" << endl;
					check = 1;
					break;
				}
				transferMoney(transfer_ac, transfer_depo);
				this->pAcctArray[i].withdraw(transfer_depo);
			}
			else {
				break;
			}
			cout << " ���� �ܾ� : " << this->pAcctArray[i].check(acNum, passwd) << endl;
			cout << " ��ü �Ϸ�\n" << endl;
			
			check = 1;
			break;

		}
	}
	// üũ ���� Ȯ��
	if (check != 1)cout << "\n �Է��Ͻ� ������ �������� �ʽ��ϴ�.\n" << endl;
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
	cout << " ATM ���� �ܰ�:		" << this->nMachineBalance << "��" << endl;
	cout << " �� �ܰ� �Ѿ�:	" << Statistics::sum(this->pAcctArray, ATMachine::baseNum) << "��(��" << ATMachine::nCurrentAccountNum<<"��)" << endl; //���� �ʿ�
	cout << " �� �ܰ� ���:	" << Statistics::average(this->pAcctArray, ATMachine::baseNum) << "��" << endl; //���� �ʿ�
	cout << " �� �ܰ� �ְ�:	" << Statistics::max(this->pAcctArray, ATMachine::baseNum) << "��" << endl;  //���� �ʿ�
	cout << " --------------------" << endl;
	cout << " -  �� ���� ���  -" << endl;
	cout << " --------------------" << endl;
	Statistics::accountSort(this->pAcctArray, ATMachine::baseNum);
}
void ATMachine::managerModel() {
	string passwd;
	cout << " ------ ���� ------" << endl;
	cout << " ������ ��й�ȣ �Է� : ";
	cin >> passwd;
	if (cin.fail()) {
		cout << "���ڸ� �Է��ϼ���.\n" << endl;
		cin.clear();
		cin.ignore(256, '\n');
		return;
	}
	if (isManager(passwd)) {
		cout << "\n�������Դϴ�.\n" << endl;
		displayReport();
	}
	else cout << "\n��й�ȣ ���� �Դϴ�.\n" << endl;
}