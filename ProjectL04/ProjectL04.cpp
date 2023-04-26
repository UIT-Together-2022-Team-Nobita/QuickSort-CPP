#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

bool Input(int[][1000], int&, int&, string);
void QuickSort(int[][1000], int, int);
void QuickSort(int[][1000], int, int, int, int);
int Partition(int[][1000], int, int, int, int);
bool Output(int[][1000], int, int, string);

int main()
{
	clock_t start, end;
	double time_use;
	start = clock();
	static int mat[1000][1000];
	int m, n;
	cout << "Project L04" << endl;
	for (int i = 1; i <= 13; i++)
	{
		string filename = "intmatrixdata";
		if (i < 10)
			filename += '0';
		filename += to_string(i);
		string filenameinp = filename;
		filenameinp += ".inp";
		if (Input(mat, m, n, filenameinp) == true)
		{
			QuickSort(mat, m, n);
			string filenameout = filename;
			filenameout += ".outp";
			Output(mat, m, n, filenameout);
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

bool Input(int mat[][1000], int& m, int& n, string filename)
{
	ifstream fi(filename);
	if (fi.fail() == true)
		return false;
	fi >> m >> n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			fi >> mat[i][j];
	return true;
}

int Partition(int mat[][1000], int m, int n, int Left, int Right)
{
	int Pivot = mat[Right / n][Right % n];
	int pos = Left - 1;
	for (int i = Left; i <= Right - 1; i++)
		if (mat[i / n][i % n] < Pivot)
		{
			pos++;
			swap(mat[i / n][i % n], mat[pos / n][pos % n]);
		}
	pos = pos + 1;
	swap(mat[pos / n][pos % n], mat[Right / n][Right % n]);
	return pos;
}

void QuickSort(int mat[][1000], int m, int n, int Left, int Right)
{
	if (Left < Right)
	{
		int iPivot = Partition(mat, m, n, Left, Right);
		QuickSort(mat, m, n, Left, iPivot - 1);
		QuickSort(mat, m, n, iPivot + 1, Right);
	}
}

void QuickSort(int mat[][1000], int m, int n)
{
	QuickSort(mat, m, n, 0, m * n - 1);
}

bool Output(int mat[][1000], int m, int n, string filename)
{
	ofstream fo(filename);
	if (fo.fail() == true)
		return false;
	fo << setw(5) << m << setw(5) << n << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			fo << setw(5) << mat[i][j];
		fo << endl;
	}
	return true;
}