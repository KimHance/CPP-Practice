#include <iostream>
#include <string>
#include "Screen.h"
#include "Pay.h"
using namespace std;

Screen::Screen(string name, int price, int row, int col) {
	this->strMovieName = name;
	this->nTicketPrice = price;
	this->nRowMax = row;
	this->nColMax = col;

	pSeatArray = new Ticket* [row];
	for (int r = 0; r < row; ++r)
		pSeatArray[r] = new Ticket[col];
	for (int r = 0; r < row; ++r) {
		for (int c = 0; c < col; ++c) {
			pSeatArray[r][c].setSeat(r + 1, c + 1);
		}
	}

}
void Screen::Menu() {
	cout << " 1. 상영 영화 정보" << endl;
	cout << " 2. 좌석 예약 현황" << endl;
	cout << " 3. 좌석 예약" << endl;
	cout << " 4. 예약 취소" << endl;
	cout << " 5. 결제 하기" << endl;
	cout << " 7. 메인 메뉴 이동" << endl;
	cout << endl;
}	

void EuropeScreen::showMovieInfo() {
	cout << "----------------------------------------" << endl;
	cout << "   [" << this->strMovieName << "]"<< endl;
	cout << "----------------------------------------" << endl;
	cout << " 영화관 : 유럽영화 1관" << endl;
	cout << " 주인공 : 에단 호크, 줄리 델피 외" << endl;
	cout << " 줄거리 : 프랑스 파리의 소르본느 대학생인 셀린느(줄리 델피)는 헝가리 부다페스트에 사는 할머니를 만나고 ..." << endl;
	cout << " 가격 : " << this->nTicketPrice << endl;
}
void AsiaScreen::showMovieInfo() {
	cout << "----------------------------------------" << endl;
	cout << "   [" << this->strMovieName << "]" << endl;
	cout << "----------------------------------------" << endl;
	cout << " 영화관 : 아시아영화 2관" << endl;
	cout << " 주인공 : 아미르 칸, R.마드 하반, 샤르만 조시 외" << endl;
	cout << " 줄거리 : 비행기에 탄 이 영화의 화자 파르한은 이륙 직전, 어딘가에서 걸려온 한 통의 전화를 받는다. ..." << endl;
	cout << " 가격 : " << this->nTicketPrice << endl;
}
void PremiumScreen::showMovieInfo() {
	cout << "----------------------------------------" << endl;
	cout << "   [" << this->strMovieName << "]" << endl;
	cout << "----------------------------------------" << endl;
	cout << " 영화관 : 프리미엄영화 3관" << endl;
	cout << " 주인공 : 베네딕트 컴버배치, 엘리자베스 올슨 외" << endl;
	cout << " 줄거리 : 검붉은 에너지 형태의 괴물에게서 달아나고 있는 어딘가 다른 모습의 닥터 스트레인지와 데님 셔츠를 걸친 소녀 ..." << endl;
	cout << " 가격 : " << this->nTicketPrice << endl;
}

void EuropeScreen::showMovieMenu() {
	cout << endl;
	cout << "----------------------------------------" << endl;
	cout << "   영화 메뉴 - " << this->strMovieName << endl;
	cout << "----------------------------------------" << endl;
	Menu();
}
void AsiaScreen::showMovieMenu() {
	cout << "----------------------------------------" << endl;
	cout << "   영화 메뉴 - " << this->strMovieName << endl;
	cout << "----------------------------------------" << endl;
	Menu();
}
void PremiumScreen::showMovieMenu() {
	cout << "----------------------------------------" << endl;
	cout << "   영화 메뉴 - " << this->strMovieName << endl;
	cout << "----------------------------------------" << endl;
	Menu();
}

void Screen::showSeatMap() {
	cout << "\t[ 좌석 예약 현황 ]" << endl;
	cout << "\t";
	for (int r = 1; r <= nRowMax; r++) cout << "["<< r <<"] ";
	cout << endl;
	for (int c = 1; c <= nColMax; c++) {
		cout << "[" << c << "]\t";
		for (int r = 1; r <= nRowMax; r++) {
			cout << "[" << pSeatArray[r-1][c-1].getCheck() << "] ";
		}
		cout << endl;
	}
}
void Screen::reserveTicket() {
	int row, col;
	cout << "  [ 좌석 예약]" << endl;
	cout << "좌석 행 번호 입력(1 - " << this->nRowMax << ") :";
	cin >> row;
	cout << "좌석 열 번호 입력(1 - " << this->nColMax << ") :";
	cin >> col;

	if (pSeatArray[row-1][col-1].getCheck() != SEAT_EMPTY_MARK)
		cout << " 이미 예약된 좌석입니다." << endl;
	else {
		Ticket::plusTotal();
		pSeatArray[row-1][col-1].setCheck(SEAT_RESERVED_MARK);
		pSeatArray[row-1][col-1].setReservedID(Ticket::getTotal());
		cout << "행[" << row << "] 열[" << col << "] " << pSeatArray[row-1][col-1].getReservedID() << " 예약 번호로 접수 되었습니다." << endl;
	}
	
	cout << endl;
}
void Screen::cancelReservation() {
	int bookNum;
	cout << "\n [ 좌석 예약 취소 ]" << endl;
	cout << "예약 번호 입력 : ";
	cin >> bookNum;
	Ticket* ticket = checkReservedID(bookNum);

	if (ticket == NULL)
		cout << "해당하는 예약번호가 없습니다.";
	else {
		int tmp = ticket->getReservedID();
		if (tmp == bookNum && ticket->getCheck() == SEAT_RESERVED_MARK) {
			ticket->setCheck(SEAT_EMPTY_MARK);
			ticket->setReservedID(0);
			cout << bookNum << " 예약 번호가 취소 처리되었습니다." << endl;;
		}
		else {
			cout << "예약을 취소할 수 없습니다. 결제가 완료된 예약입니다." << endl;
		}
	}
}
Ticket* Screen::checkReservedID(int id) {
	for (int r = 0; r < nRowMax; ++r) {
		for (int c = 0; c < nColMax; ++c) {
			if (pSeatArray[r][c].getReservedID() == id)
				return &pSeatArray[r][c];
		}
	}
	return NULL;
}

void Screen::payment() {
	int bookNum;
	cout << "\n [ 좌석 예약 결제 ]" << endl;
	cout << "예약 번호 입력 : ";
	cin >> bookNum;
	Ticket* ticket = checkReservedID(bookNum);

	if (ticket == NULL)
		cout << "해당하는 예약번호가 없습니다." << endl;
	else if (ticket->getCheck() != SEAT_RESERVED_MARK)
		cout << "결제를 진행할 수 없습니다.";
	else {
		cout << "---------------------------" << endl;
		cout << "     결제 방식 선택" << endl;
		cout << "---------------------------" << endl;
		cout << " 1. 모바일 결제" << endl;
		cout << " 2. 은행 이체 결제" << endl;
		cout << " 3. 카드 결제" << endl;
		cout << "\n 결제 방식(1~3) : ";
		int num;
		cin >> num;
		switch (num) {
		case 1: {
			MobilePay mobilePay(MOBILE_PHONE_INTEREST_RATE);
			ticket->setPayMethod(MOBILE_PHONE_PAYMENT);
			int pay = mobilePay.charge(nTicketPrice);
			if (pay != 0) {
				ticket->setCheck(SEAT_COMPLETION_MARK);
				ticket->setPayAmount(pay);
			}
			break;
		}
		case 2: {
			BankTransfer bankTransfer(BANK_TRANSFER_INTEREST_RATE);
			ticket->setPayMethod(BANK_TRANSFER_PAYMENT);
			int pay = bankTransfer.charge(nTicketPrice);
			if (pay != 0) {
				ticket->setCheck(SEAT_COMPLETION_MARK);
				ticket->setPayAmount(pay);
			}
			break;
		}
		case 3: {
			CardPay cardPay(CREDIT_CARD_PAYMENT);
			ticket->setPayMethod(CREDIT_CARD_PAYMENT);
			int pay = cardPay.charge(nTicketPrice);
			if (pay != 0) {
				ticket->setCheck(SEAT_COMPLETION_MARK);
				ticket->setPayAmount(pay);
			}
			break;
		}
		default:
			cout << " 숫자를 잘못 입력하였습니다.\n" << endl;
			break;
		}
	}
}


Screen::~Screen() {
	for (int r = 0; r < nRowMax; ++r)
		delete[] pSeatArray[r];
	delete[] pSeatArray;
}

