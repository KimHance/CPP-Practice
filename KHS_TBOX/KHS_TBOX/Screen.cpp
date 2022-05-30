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
	cout << " 1. �� ��ȭ ����" << endl;
	cout << " 2. �¼� ���� ��Ȳ" << endl;
	cout << " 3. �¼� ����" << endl;
	cout << " 4. ���� ���" << endl;
	cout << " 5. ���� �ϱ�" << endl;
	cout << " 7. ���� �޴� �̵�" << endl;
	cout << endl;
}	

void EuropeScreen::showMovieInfo() {
	cout << "----------------------------------------" << endl;
	cout << "   [" << this->strMovieName << "]"<< endl;
	cout << "----------------------------------------" << endl;
	cout << " ��ȭ�� : ������ȭ 1��" << endl;
	cout << " ���ΰ� : ���� ȣũ, �ٸ� ���� ��" << endl;
	cout << " �ٰŸ� : ������ �ĸ��� �Ҹ����� ���л��� ������(�ٸ� ����)�� �밡�� �δ��佺Ʈ�� ��� �ҸӴϸ� ������ ..." << endl;
	cout << " ���� : " << this->nTicketPrice << endl;
}
void AsiaScreen::showMovieInfo() {
	cout << "----------------------------------------" << endl;
	cout << "   [" << this->strMovieName << "]" << endl;
	cout << "----------------------------------------" << endl;
	cout << " ��ȭ�� : �ƽþƿ�ȭ 2��" << endl;
	cout << " ���ΰ� : �ƹ̸� ĭ, R.���� �Ϲ�, ������ ���� ��" << endl;
	cout << " �ٰŸ� : ����⿡ ź �� ��ȭ�� ȭ�� �ĸ����� �̷� ����, ��򰡿��� �ɷ��� �� ���� ��ȭ�� �޴´�. ..." << endl;
	cout << " ���� : " << this->nTicketPrice << endl;
}
void PremiumScreen::showMovieInfo() {
	cout << "----------------------------------------" << endl;
	cout << "   [" << this->strMovieName << "]" << endl;
	cout << "----------------------------------------" << endl;
	cout << " ��ȭ�� : �����̾���ȭ 3��" << endl;
	cout << " ���ΰ� : ���׵�Ʈ �Ĺ���ġ, �����ں��� �ý� ��" << endl;
	cout << " �ٰŸ� : �˺��� ������ ������ �������Լ� �޾Ƴ��� �ִ� ��� �ٸ� ����� ���� ��Ʈ�������� ���� ������ ��ģ �ҳ� ..." << endl;
	cout << " ���� : " << this->nTicketPrice << endl;
}

void EuropeScreen::showMovieMenu() {
	cout << endl;
	cout << "----------------------------------------" << endl;
	cout << "   ��ȭ �޴� - " << this->strMovieName << endl;
	cout << "----------------------------------------" << endl;
	Menu();
}
void AsiaScreen::showMovieMenu() {
	cout << "----------------------------------------" << endl;
	cout << "   ��ȭ �޴� - " << this->strMovieName << endl;
	cout << "----------------------------------------" << endl;
	Menu();
}
void PremiumScreen::showMovieMenu() {
	cout << "----------------------------------------" << endl;
	cout << "   ��ȭ �޴� - " << this->strMovieName << endl;
	cout << "----------------------------------------" << endl;
	Menu();
}

void Screen::showSeatMap() {
	cout << "\t[ �¼� ���� ��Ȳ ]" << endl;
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
	cout << "  [ �¼� ����]" << endl;
	cout << "�¼� �� ��ȣ �Է�(1 - " << this->nRowMax << ") :";
	cin >> row;
	cout << "�¼� �� ��ȣ �Է�(1 - " << this->nColMax << ") :";
	cin >> col;

	if (pSeatArray[row-1][col-1].getCheck() != SEAT_EMPTY_MARK)
		cout << " �̹� ����� �¼��Դϴ�." << endl;
	else {
		Ticket::plusTotal();
		pSeatArray[row-1][col-1].setCheck(SEAT_RESERVED_MARK);
		pSeatArray[row-1][col-1].setReservedID(Ticket::getTotal());
		cout << "��[" << row << "] ��[" << col << "] " << pSeatArray[row-1][col-1].getReservedID() << " ���� ��ȣ�� ���� �Ǿ����ϴ�." << endl;
	}
	
	cout << endl;
}
void Screen::cancelReservation() {
	int bookNum;
	cout << "\n [ �¼� ���� ��� ]" << endl;
	cout << "���� ��ȣ �Է� : ";
	cin >> bookNum;
	Ticket* ticket = checkReservedID(bookNum);

	if (ticket == NULL)
		cout << "�ش��ϴ� �����ȣ�� �����ϴ�.";
	else {
		int tmp = ticket->getReservedID();
		if (tmp == bookNum && ticket->getCheck() == SEAT_RESERVED_MARK) {
			ticket->setCheck(SEAT_EMPTY_MARK);
			ticket->setReservedID(0);
			cout << bookNum << " ���� ��ȣ�� ��� ó���Ǿ����ϴ�." << endl;;
		}
		else {
			cout << "������ ����� �� �����ϴ�. ������ �Ϸ�� �����Դϴ�." << endl;
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
	cout << "\n [ �¼� ���� ���� ]" << endl;
	cout << "���� ��ȣ �Է� : ";
	cin >> bookNum;
	Ticket* ticket = checkReservedID(bookNum);

	if (ticket == NULL)
		cout << "�ش��ϴ� �����ȣ�� �����ϴ�." << endl;
	else if (ticket->getCheck() != SEAT_RESERVED_MARK)
		cout << "������ ������ �� �����ϴ�.";
	else {
		cout << "---------------------------" << endl;
		cout << "     ���� ��� ����" << endl;
		cout << "---------------------------" << endl;
		cout << " 1. ����� ����" << endl;
		cout << " 2. ���� ��ü ����" << endl;
		cout << " 3. ī�� ����" << endl;
		cout << "\n ���� ���(1~3) : ";
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
			cout << " ���ڸ� �߸� �Է��Ͽ����ϴ�.\n" << endl;
			break;
		}
	}
}


Screen::~Screen() {
	for (int r = 0; r < nRowMax; ++r)
		delete[] pSeatArray[r];
	delete[] pSeatArray;
}

