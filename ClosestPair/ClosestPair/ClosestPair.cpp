#include <iostream>
#include <cmath>

using namespace std;


typedef struct Point {
	int x;
	int y;
}Point;

Point p1, p2;
double min_dist = 100000;
int compare_count = 0;

void Merge_xSort(Point *arr, int *arr2, int *arr3, int p, int q)
{
	int k = 0;

	if (p < q) {			// ������ �����ϸ�

		k = (p + q) / 2;
		Merge_xSort(arr, arr2, arr3, p, k);
		Merge_xSort(arr, arr2, arr3, k + 1, q);

		int i = p;
		int j = k + 1;

		for (int t = p; t < q + 1; t++) {

			if (i > k) {			// ������ �迭���� �� �������
				arr2[t] = arr[j].x;
				arr3[t] = arr[j].y;
				j++;
			}

			else if (j > q) {		// �������� �迭���� �� �������
				arr2[t] = arr[i].x;
				arr3[t] = arr[i].y;
				i++;
			}

			else {						// ���� ������ �迭 ��� ���� ���
				if (arr[i].x <= arr[j].x) {
					arr2[t] = arr[i].x;
					arr3[t] = arr[i].y;
					i++;
				}

				else if (arr[i].x > arr[j].x) {
					arr2[t] = arr[j].x;
					arr3[t] = arr[j].y;
					j++;
				}
			}

		}

		for (int t = p; t < q + 1; t++) {
			arr[t].x = arr2[t];								// arr�� �����Ѱ��� A �迭�� ����
			arr[t].y = arr3[t];
		}

	}

}

void Merge_ySort(Point *arr, int *arr2, int *arr3, int p, int q)		// y ���� ����
{
	int k = 0;

	if (p < q) {			// ������ �����ϸ�

		k = (p + q) / 2;
		Merge_ySort(arr, arr2, arr3, p, k);
		Merge_ySort(arr, arr2, arr3, k + 1, q);

		int i = p;
		int j = k + 1;

		for (int t = p; t < q + 1; t++) {

			if (i > k) {			// ������ �迭���� �� �������
				arr2[t] = arr[j].x;
				arr3[t] = arr[j].y;
				j++;
			}

			else if (j > q) {		// �������� �迭���� �� �������
				arr2[t] = arr[i].x;
				arr3[t] = arr[i].y;
				i++;
			}

			else {						// ���� ������ �迭 ��� ���� ���
				if (arr[i].y <= arr[j].y) {
					arr2[t] = arr[i].x;
					arr3[t] = arr[i].y;
					i++;
				}

				else if (arr[i].y > arr[j].y) {
					arr2[t] = arr[j].x;
					arr3[t] = arr[j].y;
					j++;
				}
			}

		}

		for (int t = p; t < q + 1; t++) {
			arr[t].x = arr2[t];								// arr�� �����Ѱ��� A �迭�� ����
			arr[t].y = arr3[t];
		}

	}

}

void Printarr(Point *arr, int n)
{
	for (int i = 0; i < n; i++) {
		cout << "{" << arr[i].x << ", " << arr[i].y << "} ";
	}
	cout << endl;
}

double Min_dist(Point *arr, int start, int end)
{
	double x, y;

	for (int i = start; i < end; i++) {
		for (int j = i + 1; j <= end; j++) {
			if ((arr[j].x - arr[i].x <= min_dist) && (fabs(arr[j].y - arr[i].y) <= min_dist)) {		// �ּڰ����� x�Ÿ��� �������� �˻�
				x = arr[j].x - arr[i].x;
				y = arr[j].y - arr[i].y;
				double Pair = sqrt((x * x) + (y * y));


				cout << "{" << arr[i].x << ", " << arr[i].y << "}, ";
				cout << "{" << arr[j].x << ", " << arr[j].y << "}  =>";
				cout << Pair << " " << endl;
				++compare_count;

				if (Pair <= min_dist) {
					p1.x = arr[i].x;
					p1.y = arr[i].y;
					p2.x = arr[j].x;
					p2.y = arr[j].y;
					min_dist = Pair;
				}

			}
			
			else  if(arr[j].x - arr[i].x > min_dist){			// x���� �������� ���� �Ǿ������Ƿ� x�Ÿ��� �ּڰ����� ũ��
				j = end + 1;									// �׺��� �������� ���鿡 ���ؼ� �˻����� �ʴ´�.
			}
		}
	}

	return min_dist;
}

double Min_dist_mid(Point *arr, int start, int end)
{
	double x, y;

	int arr_count = end - start + 1;

	Point *Arr = new Point[arr_count];		// �߰��� ������ŭ �ӽù迭 ����

	for (int i = 0, k = start; i < arr_count; i++, k++) {
		Arr[i].x = arr[k].x;
		Arr[i].y = arr[k].y;
	}

	int *arr4 = new int[arr_count];
	int *arr5 = new int[arr_count];

	Merge_ySort(Arr, arr4, arr5, 0, arr_count - 1);		// �߰������� y �������� �迭

	for (int i = 0; i < arr_count; i++) {
		for (int j = i + 1; j <= arr_count; j++) {
			if ((Arr[j].y - Arr[i].y <= min_dist) && (fabs(Arr[j].x - Arr[i].x) <= min_dist)) {
				x = Arr[j].x - Arr[i].x;
				y = Arr[j].y - Arr[i].y;
				double Pair = sqrt((x * x) + (y * y));


				cout << "{" << Arr[i].x << ", " << Arr[i].y << "}, ";
				cout << "{" << Arr[j].x << ", " << Arr[j].y << "}  =>";
				cout << Pair << "(�߰�����)" << " " << endl;
				++compare_count;

				if (Pair <= min_dist) {
					p1.x = Arr[i].x;
					p1.y = Arr[i].y;
					p2.x = Arr[j].x;
					p2.y = Arr[j].y;
					min_dist = Pair;
				}

			}
			else if (Arr[j].y - Arr[i].y > min_dist) {		// y���� ������������ ���������Ƿ� y���� ���̰� �ּڰ����� ũ��
				j = end + 1;								// �׺��� ������ ���鿡 ���ؼ� ������ ����
			}
		}
	}

	delete[] Arr;
	delete[] arr4;
	delete[] arr5;

	return min_dist;
}

double ClosestPair(Point *arr, int start, int end, int n)
{
	if (n <= 3) {
		return Min_dist(arr, start, end);
	}

	else {
		int mid = (start + (end + 1)) / 2;		// �߰�


		int mid_start = 0;
		int mid_end = 0;
		double CPleft = 100000;
		double CPright = 100000;

		if (n % 2 == 0) {						// ¦����
			CPleft = ClosestPair(arr, start, mid - 1, n / 2);
			CPright = ClosestPair(arr, mid, end, n / 2);
		}

		else if (n % 2 == 1) {				// Ȧ����
			CPleft = ClosestPair(arr, start, mid, (n / 2) + 1);
			CPright = ClosestPair(arr, mid + 1, end, n / 2);
		}


		double d = min_dist;	// �Ÿ��� �ּڰ��� ���� �����ʿ� ������� ����Ǿ�����

		if (n % 2 == 0) {		// ¦��
			int Mid_left = mid - 1;		// �߰������� ���� ����� ����
			int Mid_right = mid;		// �߰������� ���� ����� ������
			double Mid_boundary = (arr[Mid_left].x + arr[Mid_right].x) / 2;	// �߰� ��輱

			for (int i = Mid_left; (Mid_boundary - min_dist) <= arr[i].x && i >= start; i--)	// �߰� �������� ���� ���� �������� ã��
				mid_start = i;

			for (int i = Mid_right; (Mid_boundary + min_dist) >= arr[i].x && i <= end; i++)	// �߰� �������� ���� ���� ū���� ã��
				mid_end = i;
		}

		else if (n % 2 == 1) {
			int Mid_left = mid;				// �߰������� ���� ����� ����
			int Mid_right = mid + 1;		// �߰������� ���� ����� ������
			double Mid_boundary = (arr[Mid_left].x + arr[Mid_right].x) / 2;	// �߰� ��輱

			for (int i = Mid_left; (Mid_boundary - min_dist) <= arr[i].x && i >= start; i--)
				mid_start = i;

			for (int i = Mid_right; (Mid_boundary + min_dist) >= arr[i].x && i <= end; i++)
				mid_end = i;
		}


		double CPmid = Min_dist_mid(arr, mid_start, mid_end);


		if (d <= CPmid) {
			return d;
		}

		else {
			return CPmid;
		}
	}
}

int main()
{
	Point arr[] = { { 316, 353 },{ 253, 857 },{ 743, 851 },{ 183, 998 },{ 262, 439 },{ 330, 732 },{ 418, 232 },{ 856, 448 },{ 596, 658 },{ 266, 100 },{ 890, 793 },{ 665, 864 },{ 238, 657 },{ 636, 731 },{ 735, 606 },{ 562, 203 },{ 492, 701 },{ 306, 393 },{ 798, 939 },{ 921, 176 },{ 637, 780 },{ 620, 975 },{ 718, 94 },{ 887, 749 },{ 756, 560 },{ 525, 805 },{ 229, 29 },{ 352, 570 },{ 670, 589 },{ 644, 821 } };

	p1.x = 0; p1.y = 0; p2.x = 0; p2.y = 0;

	int n = sizeof(arr) / sizeof(arr[0]);

	int *arr2 = new int[n];
	int *arr3 = new int[n];

	Merge_xSort(arr, arr2, arr3, 0, n - 1);

	Printarr(arr, n);

	delete[] arr2;
	delete[] arr3;

	cout << endl << endl;

	cout.setf(ios::fixed);
	cout.precision(6);
	cout << double(ClosestPair(arr, 0, n - 1, n));		// arr, ����, ��, ����
	cout << "  �ֱ����� " << "(" << p1.x << ", " << p1.y << ") (" << p2.x << ", " << p2.y << ")" << endl;
	cout << compare_count << "ȸ ��" << endl;
}