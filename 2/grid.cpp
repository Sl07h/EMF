#include "grid.h"



void GRID::inputGrid()
{
	string filepath;
	if (isGridUniform)
		filepath = "input/uniform_grid.txt";
	else
		filepath = "input/nonuniform_grid.txt";

	std::ifstream fin(filepath);

	fin >> xLeft >> xRight;

	fin >> width;

	if (!isGridUniform) {
		fin >> kx;
		nx = width - 1;
	}

	fin.close();
}



void GRID::inputTime()
{
	string filepath;
	if (isGridUniform)
		filepath = "input/uniform_time.txt";
	else
		filepath = "input/nonuniform_time.txt";

	std::ifstream fin(filepath);

	fin >> tFirst >> tLast;

	fin >> tCount;

	if (!isGridUniform) {
		fin >> kt;
		nt = tCount - 1;
	}

	fin.close();
}




void GRID::buildGrid()
{
	//  xLeft         xRight
	//	  *-------------*
	//    0    width    10

	if (isGridUniform) {
		hx = ((xRight - xLeft) / double(width - 1)) / pow(2, coefGrid);
		cout << hx << endl;
		if (coefGrid != 0)
			width = (width - 1) * pow(2, coefGrid) + 1;
	}
	else {
		if (coefGrid != 0) {
			width = (width - 1) * pow(2, coefGrid) + 1;
			nx *= pow(2, coefGrid);
			kx *= pow(kx, 1.0 / coefGrid);
		}

		hx = (xRight - xLeft) * (1 - kx) / (1 - pow(kx, nx));
	}




	elemCount = width;
	cout << "Grid is uniform" << endl
		<< "Coef: " << coefGrid << endl
		<< "Width: " << width << endl
		<< "Count of elements: " << elemCount << endl
		<< "hx: " << hx << endl;
	nodes.resize(elemCount);


	if (isGridUniform) {

		size_t i, elem;
		double x;

		// ������ �������
		nodes[0].setNodesData(xLeft, 0, 1, coefGrid);

		i = 1;
		x = xLeft + hx * i;
		for (elem = 1; elem < width; elem += width, i++)
		{
			nodes[elem].setNodesData(x, i, 0, coefGrid);
			nodes[elem].border = 0;
		}

		// ��������� �������
		nodes[elemCount - 1].setNodesData(xRight, width, 1, coefGrid);
	}

	else {

		double x;
		size_t i, elem;

		i = 1;
		dx = hx * kx;
		x = xLeft + hx;

		// ������ �������
		nodes[0].setNodesData(xLeft, 0, 1, coefGrid);

		for (elem = 1; elem < width; elem++, i++, dx *= kx)
		{
			nodes[elem].setNodesData(x, i, 0, coefGrid);
			nodes[elem].border = 0;
			x += dx;
		}

		// ��������� �������
		nodes[elemCount - 1].setNodesData(xRight, width, 1, coefGrid);
	}
}



// ���������� ����� �� �����
void GRID::showGrid() {

	for (size_t i = 0; i < width; i++)
		cout << nodes[i].x << " ";
}



// ���������� ���������� � ������� ����� � 2 ������
void GRID::saveGridAndBorder(const string &filepathGrid, const string &filepathGridBorder) {

	ofstream grid(filepathGrid);
	ofstream border(filepathGridBorder);
	for (size_t i = 0; i < elemCount; i++)
	{
		if (nodes[i].type > 0)
			border << nodes[i].x << endl;
		else
			grid << nodes[i].x << endl;
	}

	border.close();
	grid.close();
}