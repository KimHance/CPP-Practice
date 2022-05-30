#include <iostream>
#include "Screen.h"
#include "TicketBox.h"
using namespace std;

TUKoreaTBox::TUKoreaTBox() {
	cout << "=========================" << endl;
	cout << "  한국 공학대학교 극장" << endl;
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
	cout << "  상영관 메인 메뉴" << endl;
	cout << "--------------------" << endl;
	cout << " 1.\t유럽\t영화\t1관" << endl;
	cout << " 2.\t아시아\t영화\t2관" << endl;
	cout << " 3.\t프리미엄\t영화\t3관" << endl;
	cout << " 7.\t통계\t관리" << endl;
	cout << "\n 선택(1~3,9) 그외 종료 : ";
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
	// Screen(영화제목, 티켓가격, 좌석(nRowMax), 좌석(nColMax))
	pEuropeScreen = new EuropeScreen("비포 선라이즈", 10000, 10, 10);
	pAsiaScreen = new AsiaScreen("세 얼간이", 12000, 10, 10);
	pPremiumScreen = new PremiumScreen("닥터 스트레인지2", 30000, 6, 6);
}
void TUKoreaTBox::Manage() {
}

int Ticket::totalReserved = 0;