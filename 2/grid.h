#pragma once
#include "head.h"


struct NODE {

	bool isFirstNode = false;
	int i;
	double x;
	int type = -9000;		// -9000	������� ��� �������������
							// -1		��������� ����
							// 0		���������� ����
							// n		����� �������
	int border;				// ����� �������
	double time;

	void setNodesData(double _x, int _i, int _type, double _coef) {
		x = _x;
		i = _i;
		type = _type;
		if (i % int(pow(2, _coef)) == 0)
			isFirstNode = true;
	}
};



class GRID
{
public:
	void inputGrid();
	void inputTime();
	void buildGrid();
	void showGrid();
	void saveGridAndBorder(const string &filepathGrid, const string &filepathGridBorder);

protected:

	int coefGrid, // ������� ��� ������� ����� �� ������������
		coefTime; // ������� ��� ������� ����� �� �������

	// ������������
	bool isGridUniform;
	int width;
	double xLeft, xRight;
	double hx, nx, kx, hxPrev;
	double dx;
	int elemCount;

	// �����
	bool isTimeUniform;
	int tCount;
	double tFirst, tLast;
	double ht, nt, kt, htPrev;
	double dt;

	// ����
	vector <NODE> nodes;
};