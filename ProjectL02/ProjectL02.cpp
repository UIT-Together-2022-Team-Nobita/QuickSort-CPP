#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

bool Input(float[], int&, string);
void QuickSort(float[], int);
void QuickSort(float[], int, int);
int Partition(float[], int, int); 
bool Output(float[], int, string);

int main()
{
	clock_t start, end;
	double time_use;
	start = clock();
	static float arr[1000000];
	int n;
	cout << "Project L02" << endl;
	for (int i = 1; i <= 13; i++)
	{
		string filename = "floatdata";
		if (i < 10)
			filename += '0';
		filename += to_string(i);
		string filenameinp = filename;
		filenameinp += ".inp";
		if (Input(arr, n, filenameinp) == true)
		{
			QuickSort(arr, n);
			string filenameout = filename;
			filenameout += ".outp";
			Output(arr, n, filenameout);
			cout << "\nImport	" << filenameinp << "		successfully!";
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

bool Input(float arr[], int& n, string filename)
{
	ifstream fi(filename);
	if (fi.fail() == true)
		return false;
	fi >> n;
	for (int i = 0; i < n; i++)
		fi >> arr[i];
	return true;
}

int Partition(float arr[], int Left, int Right)
{
	int pivot = arr[Right];
	int pos = (Left - 1);
	for (int i = Left; i <= Right - 1; i++)
		if (arr[i] < pivot)
		{
			pos++;
			swap(arr[pos], arr[i]);
		}
	pos++;
	swap(arr[pos], arr[Right]);
	return pos;
}

void QuickSort(float arr[], int Left, int Right)
{
	if (Left < Right)
	{
		int iPivot = Partition(arr, Left, Right);
		QuickSort(arr, Left, iPivot - 1);
		QuickSort(arr, iPivot + 1, Right);
	}
}

void QuickSort(float arr[], int n)
{
	QuickSort(arr, 0, n - 1);
}

bool Output(float arr[], int n, string filename)
{
	ofstream fo(filename);
	if (fo.fail() == true)
		return false;
	fo << setw(5) << n << endl;
	for (int i = 0; i < n; i++)
		fo << setw(8) << arr[i];
	return true;
}