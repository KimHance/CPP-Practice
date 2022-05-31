#include <iostream>
#include <string>
#include "Screen.h"
#include "TicketBox.h"
#include "Statistics.h"
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
	cout << " 1. ����     ��ȭ 1��" << endl;
	cout << " 2. �ƽþ�   ��ȭ 2��" << endl;
	cout << " 3. �����̾� ��ȭ 3��" << endl;
	cout << " 7. ��� ����" << endl;
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
			return NULL;
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
	
	Statistics statistics;

	string passwd;
	cout << "------------------------------" << endl;
	cout << "         ������ �޴�" << endl;
	cout << "------------------------------" << endl;
	
	while (true) {
		cout << " ������ ��й�ȣ �Է� : ";
		cin >> passwd; cout << endl;
		if (passwd != TICKETBOX_MANAGER_PWD) {
			cout << "��й�ȣ ����" << endl;
			continue;
		}
		int euroRev, asiaRev, premRev, totalSales=0;
		euroRev = statistics.totalRevenue(this->pEuropeScreen);
		asiaRev = statistics.totalRevenue(this->pAsiaScreen);
		premRev = statistics.totalRevenue(this->pPremiumScreen);
		cout << "1. ������ȭ �󿵰� �����ݾ� : " << euroRev << endl;
		cout << "2. �ƽþƿ�ȭ �󿵰� �����ݾ� : " << asiaRev << endl;
		cout << "3. �����̾���ȭ �󿵰� �����ݾ� : " << premRev << endl;

		totalSales += statistics.totalSalesCount(this->pEuropeScreen);
		totalSales += statistics.totalSalesCount(this->pAsiaScreen);
		totalSales += statistics.totalSalesCount(this->pPremiumScreen);
		cout << "4. ��ü Ƽ�� �Ǹŷ� : " << totalSales << endl;
		break;
	}
	
}

int Ticket::totalReserved = 0;