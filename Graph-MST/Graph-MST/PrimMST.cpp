#include <iostream>

using namespace std;
constexpr auto N = 6;

typedef struct List {
	int p1, p2;
	int weight;
}list;

list D[N];
list T[N];
int cnt = 0;

void reset(int G[][N])
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			G[i][j] = 0;
}

void PrimMST(int G[][N])
{
	int start = 3;		// ������ vertex 3

	for (int i = 0; i < N; ++i) {
		if (G[start][i] != 0 && i != start) {	// 3���� ����� ��
			D[i].weight = G[start][i];		// ����ġ�� D �� �ְ�
			D[i].p1 = start;				// p1, p2 �� 3��, ����� �� ���� ��
			D[i].p2 = i;
		}
		else {
			D[i].weight = 10000;		// ����x �� ���� ����ġ�� �ִ�
		}
	}
	T[cnt].p1 = start;	// �ʱ� Ʈ��T�� �������� ����
	D[start].weight = 0;

	int min = 10000;		// �ּ� ����ġ
	int min_number = 0;

	while (cnt < N - 1) {		// MST�� ��� ������ (Vertex�� �� - 1) ��

		for (int i = 0; i < N; ++i) {		// ����ġ Ž��
			if (D[i].weight != 0 && D[i].weight < min) {	// ����ġ�� 0�� �ƴϰ�, �ּҰ���ġ���� ������
				min = D[i].weight;							// D ����Ʈ�� �ִ� ����ġ�� �ּڰ��� min �� ����
				min_number = i;								// �ּڰ��� �ش��ϴ� vertex�� ������
			}
		}
		T[cnt].p1 = D[min_number].p1;	// D[].p1 �� ���� �� ���� ����ġ�� ���� �������� ��ȣ�� ����
		T[cnt].p2 = min_number;			// ����� ���� p2 �� ����
		T[cnt].weight = min;			// �ּ� ����ġ�� ����
		D[min_number].weight = 0;		// T�� �ִ� ���� ����ġ�� 0���� ����		 ����ġ�� 0�ϰ�� T�� �����ִ°����� �Ǵ��� Ž������ ����
		min = 10000;					// ����ġ �ּڰ� �ʱ�ȭ


		for (int i = 0; i < N; ++i) {		// ����ġ ����
			
			if (G[min_number][i] != 0 && D[i].weight != 0 && G[min_number][i] < D[i].weight) {	// ���ο� ���� ������� && T�� ������ ������ && D�� ����ġ���� �������
				D[i].weight = G[min_number][i];		// ����ġ�� ����
				D[i].p1 = min_number;				// ���ο�� ����� ���� Ž���ϴ� ���̹Ƿ� ���ο� ���� p1�� ����
				D[i].p2 = i;						// ����� ���� ����ġ�� ���� �͵� p2�� ����
			}
		}
		++cnt;

	}

	reset(G);

	for (int i = 0; i < cnt; ++i) {
		G[T[i].p1][T[i].p2] = T[i].weight;
		G[T[i].p2][T[i].p1] = T[i].weight;
		cout << "����" << i + 1 << ": (" << T[i].p1 << ", " << T[i].p2 << ") �� ����ġ   " << T[i].weight << endl;
	}
}


int main()
{
	int G[N][N] = {
		{0,3,2,0,4,0},
		{3,0,4,1,0,2},
		{2,4,0,0,5,7},
		{0,1,0,0,0,1},
		{4,0,5,0,0,9},
		{0,2,7,1,9,0} };
	
	PrimMST(G);

	cout << endl << "PrimMST ��� " << endl;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cout << G[i][j] << " ";
		}
		cout << endl;
	}
			
}