#include <iostream>
#include <string>
#include "Screen.h"
#include "TicketBox.h"
#include "Statistics.h"
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
	cout << " 1. 유럽     영화 1관" << endl;
	cout << " 2. 아시아   영화 2관" << endl;
	cout << " 3. 프리미엄 영화 3관" << endl;
	cout << " 7. 통계 관리" << endl;
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
			return NULL;
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
	
	Statistics statistics;

	string passwd;
	cout << "------------------------------" << endl;
	cout << "         관리자 메뉴" << endl;
	cout << "------------------------------" << endl;
	
	while (true) {
		cout << " 관리자 비밀번호 입력 : ";
		cin >> passwd; cout << endl;
		if (passwd != TICKETBOX_MANAGER_PWD) {
			cout << "비밀번호 오류" << endl;
			continue;
		}
		int euroRev, asiaRev, premRev, totalSales=0;
		euroRev = statistics.totalRevenue(this->pEuropeScreen);
		asiaRev = statistics.totalRevenue(this->pAsiaScreen);
		premRev = statistics.totalRevenue(this->pPremiumScreen);
		cout << "1. 유럽영화 상영관 결제금액 : " << euroRev << endl;
		cout << "2. 아시아영화 상영관 결제금액 : " << asiaRev << endl;
		cout << "3. 프리미엄영화 상영관 결제금액 : " << premRev << endl;

		totalSales += statistics.totalSalesCount(this->pEuropeScreen);
		totalSales += statistics.totalSalesCount(this->pAsiaScreen);
		totalSales += statistics.totalSalesCount(this->pPremiumScreen);
		cout << "4. 전체 티켓 판매량 : " << totalSales << endl;
		break;
	}
	
}

int Ticket::totalReserved = 0;