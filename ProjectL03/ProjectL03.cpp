//Stack overflow fractiondata13.inp
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

struct fraction
{
	int numerator;
	int denominator;
};
typedef struct fraction FRACTION;

bool Input(FRACTION[], int&, string);
int FCompare(FRACTION, FRACTION);
void QuickSort(FRACTION[], int);
void QuickSort(FRACTION[], int, int);
int Partition(FRACTION[], int, int);
bool Output(FRACTION[], int, string);

int main()
{
	clock_t start, end;
	double time_use;
	start = clock();
	static FRACTION FA[1000000];
	int n;
	cout << "Project L03" << endl;
	for (int i = 1; i <= 13; i++)
	{
		string filename = "fractiondata";
		if (i < 10)
			filename += '0';
		filename += to_string(i);
		string filenameinp = filename;
		filenameinp += ".inp";
		if (Input(FA, n, filenameinp) == true)
		{
			QuickSort(FA, n);
			string filenameout = filename;
			filenameout += ".outp";
			Output(FA, n, filenameout);
			cout << "\nImport	" << filenameinp << "	successfully!";
			cout << "\nExport	" << filenameout << "	successfully!" << endl;
		}
		else
			cout << "\nCan't open the file" << filename << endl;
	}
	end = clock();
	time_use = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\nRuntime:	" << time_use;
	cout << endl;
	return 1;
}

bool Input(FRACTION FA[], int& n, string filename)
{
	ifstream fi(filename);
	if (fi.fail() == true)
		return false;
	fi >> n;
	for (int i = 0; i < n; i++)
		fi >> FA[i].numerator >> FA[i].denominator;
	return true;
}
int FCompare(FRACTION ft1, FRACTION ft2)
{
	double q1 = (double)ft1.numerator / ft1.denominator;
	double q2 = (double)ft2.numerator / ft2.denominator;
	if (q1 > q2)
		return 1;
	if (q1 < q2)
		return -1;
	return 0;
}

int Partition(FRACTION FA[], int Left, int Right)
{
	FRACTION pivot = FA[Right];
	int pos = (Left - 1);
	for (int i = Left; i <= Right - 1; i++)
		if (FCompare(FA[i], pivot) == -1)
		{
			pos++;
			swap(FA[pos], FA[i]);
		}
	pos = pos + 1;
	swap(FA[pos], FA[Right]);
	return pos;
}

void QuickSort(FRACTION FA[], int Left, int Right)
{
	if (Left < Right)
	{
		int iPivot = Partition(FA, Left, Right);
		QuickSort(FA, Left, iPivot - 1);
		QuickSort(FA, iPivot + 1, Right);
	}
}

void QuickSort(FRACTION FA[], int n)
{
	QuickSort(FA, 0, n - 1);
}

bool Output(FRACTION FA[], int n, string filename)
{
	ofstream fo(filename);
	if (fo.fail() == true)
		return false;
	fo << setw(5) << n << endl;
	for (int i = 0; i < n; i++)
		fo << setw(5) << FA[i].numerator << setw(5) << FA[i].denominator << endl;
	return true;
}