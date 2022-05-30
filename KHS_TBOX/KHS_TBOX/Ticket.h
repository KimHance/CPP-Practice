#ifndef TICKET_H
#define TICKET_H
#define SEAT_EMPTY_MARK '-'
#define SEAT_RESERVED_MARK 'R'
#define SEAT_COMPLETION_MARK '$'
class Ticket {
	int nRow; // �¼� ��
	int nCol; // �¼� ��
	char charCheck; // ���� ����
	int nReservedID; // ���� ��ȣ
	int nPayAmount; // ���� �ݾ�
	int nPayMethod; // ���� ����
	static int totalReserved;
public:
	Ticket() {
		nRow = 0;
		nCol = 0;
		charCheck = SEAT_EMPTY_MARK;
		nReservedID = 0;
		nPayAmount = 0;
		nPayMethod = 0;
	}
	void setCheck(char check) { charCheck = check; }
	char getCheck() { return charCheck; }
	void setSeat(int row, int col) { nRow = row; nCol = col; }
	void setReservedID(int reserved) { nReservedID = reserved; }
	int getReservedID() { return nReservedID; };
	static int getTotal() { return totalReserved; }
	static void plusTotal() { totalReserved++; }

	void setPayAmount(int amount) { nPayAmount = amount; }
	int getPayAmount() { return nPayAmount; }
	void setPayMethod(int method) { nPayMethod = method; }

};
#endif