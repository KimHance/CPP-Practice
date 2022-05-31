#include <iostream>
#include "Statistics.h"
using namespace std;

int Statistics::totalRevenue(Screen* pScreen) {
	Ticket** searArray = pScreen->getTicketArray();
	int rev = 0;
	for (int c = 1; c <= pScreen->getColMax(); c++) {
		for (int r = 1; r <= pScreen->getRowMax(); r++) {
			if (searArray[r - 1][c - 1].getPayAmount() != 0) {
				rev += searArray[r - 1][c - 1].getPayAmount();
			}	
		}
	}
	return rev;
}
int Statistics::totalSalesCount(Screen* pScreen) {
	Ticket** searArray = pScreen->getTicketArray();
	int sales = 0;
	for (int c = 1; c <= pScreen->getColMax(); c++) {
		for (int r = 1; r <= pScreen->getRowMax(); r++) {
			if (searArray[r - 1][c - 1].getCheck() == SEAT_COMPLETION_MARK)
				sales++;
		}
	}
	return sales;
}