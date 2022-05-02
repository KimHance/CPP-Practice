#ifndef STATISTICS_H
#define STATISTICS_H

#include "Account.h"

class Statistics {
public:
	static int sum(Account* pArray, int size);  // °èÁÂ ÀÜ°í ÃÑÇÕ
	static int average(Account* pArray, int size); // °èÁÂ ÀÜ°í Æò±Õ
	static int max(Account* pArray, int size); // °èÁÂ ÀÜ°í ÃÖ°í
	static void accountSort(Account* pArray, int size); // ³»¸² Â÷¼ø Á¤·Ä											// (ÀÜ¾× ±âÁØ)
};

#endif