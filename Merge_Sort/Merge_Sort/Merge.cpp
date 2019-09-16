#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

void Test(int A[], int *arr, int p, int q)
{
	int i = p;
	int j = (p + q) / 2 + 1;

}

void MergeSort(int A[], int *arr, int p, int q)
{
	int k = 0;

	if (p < q) {			// ������ �����ϸ�

		k = (p + q) / 2;
		MergeSort(A, arr, p, k);
		MergeSort(A, arr, k + 1, q);

		int i = p;
		int j = k + 1;

		for (int t = p; t < q + 1; t++) {

			if (i > k) {			// ������ �迭���� �� �������
				arr[t] = A[j];
				j++;
			}

			else if (j > q) {		// �������� �迭���� �� �������
				arr[t] = A[i];
				i++;
			}

			else {						// ���� ������ �迭 ��� ���� ���
				if (A[i] <= A[j]) {
					arr[t] = A[i];
					i++;
				}

				else if (A[i] > A[j]) {
					arr[t] = A[j];
					j++;
				}
			}

		}

		for (int t = p; t < q + 1; t++) {
			A[t] = arr[t];								// arr�� �����Ѱ��� A �迭�� ����
		}

	}


}

void Printarr(int A[])
{
	for (int i = 0; i < 20; i++) {
		cout << A[i] << " ";
	}
	cout << endl;
}

int main()
{
	srand((unsigned int)time(NULL));

	int A[20] = { 0, };

	int *arr = new int[20];


	int n = sizeof(A) / sizeof(A[0]);
	for (int i = 0; i < 20; i++) {
		A[i] = rand() % 1000 + 1;
	}

	Printarr(A);

	MergeSort(A, arr, 0, n - 1);

	Printarr(A);

	delete [] arr;
}