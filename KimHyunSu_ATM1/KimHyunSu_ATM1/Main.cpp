#include<iostream>
#include<string>
#include"ATMachine.h"
using namespace std;

int ATMachine::baseNum = 0;
int ATMachine::nCurrentAccountNum = 0;

int main() {
	int select;
	// ����(100��), ATM �ܱ� �ʱ�ȭ, ������ ��ȣ
	ATMachine atm(100, 50000, "admin");

	while (1) {
		atm.displayMenu();
		cout << "�޴��� �����ϼ��� : ";
		cin >> select;
		if (cin.fail()) {
			cout << "���ڸ� �Է��ϼ���.\n" << endl;
			cin.clear();
			cin.ignore(256, '\n');
			continue;
		}
		cout << endl;
		switch (select) {

		case 1:
			atm.createAccount();
			break;
		case 2:
			atm.checkMoney();
			break;
		case 3:
			atm.depositMoney();
			break;
		case 4:
			atm.withdrawMoney();
			break;
		case 5:
			atm.transfer();
			break;
		case 6:
			atm.closeAccount();
			break;
		case 7:
			atm.managerModel();
			break;
		case 9:
			cout << "�ȳ��� ������" << endl;
			return 0;

		default:
			cout << "��ȣ Ȯ�� �� �ٽ� �Է��ϼ���." << endl;
		}
	}
	return 0;
}