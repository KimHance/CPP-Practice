#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

#include "Statistics.h"
#include "ATMachine.h"

using namespace std;

bool compare(pair<string, pair<int, int> >a,pair<string, pair<int, int> >b) {
	if (a.second.second == b.second.second) {
		return a.second.first > b.second.first;
	}
	else {
		return a.second.second > b.second.second;
	}
}
int Statistics::sum(Account* pArray, int size) {
	int sum=0;
	for (int i = 0; i < size; i++) {
		if (pArray[i].getAcctID() != AUTHENTIFICATION_FAIL) { //-1 이면 존재하는 계정x
			sum += pArray[i].getBalance();
		}
	}
	return sum;
}
int Statistics::average(Account* pArray, int size) {
	if (ATMachine::getCurAcNum() == 0) return 0;
	int sum=0;
	int average;
	for (int i = 0; i < size; i++) {
		if (pArray[i].getAcctID() != AUTHENTIFICATION_FAIL) { //-1 이면 존재하는 계정x
			sum += pArray[i].getBalance();
		}
	}
	average = sum / ATMachine::getCurAcNum();
	return average;
}
int Statistics::max(Account* pArray, int size) {
	int max = 0;
	for (int i = 0; i < size; i++) {
		if (pArray[i].getAcctID() != AUTHENTIFICATION_FAIL) { //-1 이면 존재하는 계정x
			if (max < pArray[i].getBalance()) max = pArray[i].getBalance();
		}
	}
	return max;
}
void Statistics::accountSort(Account* pArray, int size) {

	if (ATMachine::getCurAcNum() == 0) return;

	vector<pair<string, pair<int, int> > > v;

	for (int i = 0; i < size; i++) {
		if (pArray[i].getAcctID() != AUTHENTIFICATION_FAIL) { //-1 이면 존재하는 계정x
			string name = pArray[i].getAccountName();
			int id = pArray[i].getAcctID();
			int money = pArray[i].getBalance();
			v.push_back(pair<string, pair<int, int>>(name, pair<int,int>(id, money)));
		}
	}
	
	sort(v.begin(), v.end(), compare);
	for (int i = 0; i < v.size(); i++) {
		cout << " " << i + 1 << "	" << v[i].first << "	" << v[i].second.first << "	" << v[i].second.second << "원" << endl;
	}
	cout << endl;
}