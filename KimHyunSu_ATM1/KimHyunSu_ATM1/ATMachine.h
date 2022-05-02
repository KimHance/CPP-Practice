#ifndef ATMACHINE_H
#define ATMACHINE_H

#include<string>
#include"Account.h"
#include"Statistics.h"

using std::string;

#define NEGATIVE_ATM_BALANCE -10 // ATM �ܾ� ����

class ATMachine {
private:
	int aclist[901]; //100~1000���� 901��
	Account* pAcctArray; // ���� ������ ������ �迭 ������
	int nMachineBalance; // ATM �ܰ�
	int makeRandNum(int index); //�ߺ� ����
	int nMaxAccountNum; // ���� ������ ������ �迭 ũ��
	string strManagerPassword; // ������ ��й�ȣ
	inline bool isExist(int id); // ���� ���� Ȯ�� 
	
	// ������Ʈ 2�� �߰�
	bool isManager(string password);  // �Ŵ��� ��ȣ Ȯ��
	void displayReport();  // ��� ȭ�� ó��
	static int nCurrentAccountNum ; // ������ �� ���� ��
	static int baseNum; // ������ ���� ���� ��ġ
public:
	ATMachine(int size, int balance, string password); // ���� �迭ũ��, ATM �ܰ�, ������ ��ȣ �ʱ�ȭ
	~ATMachine();
	void displayMenu(); // ATM ��� ���� ȭ��
	void createAccount(); // ���� ����
	void closeAccount(); // ���� ����
	void checkMoney(); // ���� ��ȸ
	void depositMoney(); // ���� �Ա�
	void withdrawMoney(); // ���� ���

	// ������Ʈ 2�� �߰�
	void transferMoney(int id, int money); // ���� ��ü
	void transfer(); // ���� ��ü
	void managerModel(); // �� ����
	static int getCurAcNum() { return nCurrentAccountNum; }
	static int getBaseNum() { return baseNum; }
};
#endif