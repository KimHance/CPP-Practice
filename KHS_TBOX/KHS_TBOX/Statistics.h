#ifndef STATISTCIS_H
#define STATISTCIS_H
#include "Screen.h"

class Statistics {
	static int sales;
public: // Static �Լ� ����
	static int totalRevenue(Screen* pScreen);
	static int totalSalesCount(Screen* pScreen);
};

#endif
