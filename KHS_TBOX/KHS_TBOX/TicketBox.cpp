#include <iostream>
#include "Screen.h"
#include "TicketBox.h"
using namespace std;

TUKoreaTBox::TUKoreaTBox() {
	cout << "=========================" << endl;
	cout << "  �ѱ� ���д��б� ����" << endl;
	cout << "=========================" << endl;
	cout << endl;
}
TUKoreaTBox::~TUKoreaTBox() {
	delete pEuropeScreen;
	delete pAsiaScreen;
	delete pPremiumScreen;
}
Screen* TUKoreaTBox::selectMenu() {
	int num;
	cout << "--------------------" << endl;
	cout << "  �󿵰� ���� �޴�" << endl;
	cout << "--------------------" << endl;
	cout << " 1.\t����\t��ȭ\t1��" << endl;
	cout << " 2.\t�ƽþ�\t��ȭ\t2��" << endl;
	cout << " 3.\t�����̾�\t��ȭ\t3��" << endl;
	cout << " 7.\t���\t����" << endl;
	cout << "\n ����(1~3,9) �׿� ���� : ";
	cin >> num;

	if (cin.fail()) {
		return NULL;
	}
	switch (num) {
		case 1:{
			Screen* pScreen = this->pEuropeScreen;
			return pScreen;
		}	
		case 2: {
			Screen* pScreen = this->pAsiaScreen;
			return pScreen;
		}	
		case 3: {
			Screen* pScreen = this->pPremiumScreen;
			return pScreen;
		}
		case 9:{
			Manage();
		}
		default: {
			return NULL;
		} 
	}
}
void TUKoreaTBox::Initialize() {
	// Screen(��ȭ����, Ƽ�ϰ���, �¼�(nRowMax), �¼�(nColMax))
	pEuropeScreen = new EuropeScreen("���� ��������", 10000, 10, 10);
	pAsiaScreen = new AsiaScreen("�� ����", 12000, 10, 10);
	pPremiumScreen = new PremiumScreen("���� ��Ʈ������2", 30000, 6, 6);
}
void TUKoreaTBox::Manage() {
}

int Ticket::totalReserved = 0;