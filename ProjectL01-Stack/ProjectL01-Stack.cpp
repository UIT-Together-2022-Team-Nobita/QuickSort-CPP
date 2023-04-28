#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

struct segment
{
	int Left;
	int Right;
};
typedef struct segment SEGMENT;
struct stack
{
	int n;
	SEGMENT arr[10000];
};
typedef struct stack STACK;

void Init(STACK&);
int IsEmpty(STACK);
int IsFull(STACK);
void Push(STACK&, SEGMENT);
SEGMENT Pop(STACK&);

bool Input(int[], int&, string);
void QuickSort(int[], int);
void QuickSort(int[], int, int);
int Partition(int[], int, int);
bool Output(int[], int, string);

int main()
{
	clock_t start, end;
	double time_use;
	start = clock();
	static int arr[1000000];
	int n;
	cout << "Project L01 - Stack" << endl;
	for (int i = 1; i <= 13; i++)
	{
		string filename = "intdata";
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
			cout << "\nImport	" << filenameinp << "	successfully!";
			cout << "\nExport	" << filenameout << "	successfully!" << endl;
		}
		else
			cout << "\nCan't open the file" << filename << endl;
	}
	end = clock();
	time_use = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "\nStack de-recursion quick sort runtime:	" << time_use;
	cout << endl;
	return 1;
}

bool Input(int arr[], int& n, string filename)
{
	ifstream fi(filename);
	if (fi.fail() == true)
		return false;
	fi >> n;
	for (int i = 0; i < n; i++)
		fi >> arr[i];
	return true;
}

void Init(STACK& stk)
{
	stk.n = 0;
}

int IsEmpty(STACK stk)
{
	if (stk.n == 0)
		return 1;
	return 0;
}

int IsFull(STACK stk)
{
	if (stk.n == 1000)
		return 1;
	return 0;
}

void Push(STACK& stk, SEGMENT x)
{
	stk.arr[stk.n] = x;
	stk.n++;
}

SEGMENT Pop(STACK& stk)
{
	SEGMENT x = stk.arr[stk.n - 1];
	stk.n--;
	return x;
}

int Partition(int arr[], int Left, int Right)
{
	int pivot = arr[Right];
	int pos = Left - 1;
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

void QuickSort(int arr[], int n)
{
	if (n <= 1)
		return;
	STACK stk;
	Init(stk);
	SEGMENT dd = { 0, n - 1 };
	Push(stk, dd);
	while (IsEmpty(stk) == 0)
	{
		dd = Pop(stk);
		int pos = Partition(arr, dd.Left, dd.Right);
		if (dd.Left < pos - 1)
			Push(stk, { dd.Left, pos - 1 });
		if (pos + 1 < dd.Right)
			Push(stk, { pos + 1, dd.Right });
	}
}

bool Output(int arr[], int n, string filename)
{
	ofstream fo(filename);
	if (fo.fail() == true)
		return false;
	fo << setw(5) << n << endl;
	for (int i = 0; i < n; i++)
		fo << setw(8) << arr[i];
	return true;
}