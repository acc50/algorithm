#include <iostream>

using namespace std;
constexpr auto N = 6;
int cnt = 0;
int w = 0;

typedef struct List{
	int p1, p2;
	int weigh;
	struct List *next;
}list;

void Reset_Graph(int G[][N])
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			G[i][j] = 0;
		}
	}
}

void Make_Set(int p[])
{
	for (int i = 0; i < N; ++i)
		p[i] = i;
}

int Find_Set(int x, int p[])
{
	if (x == p[x])			// x�� x�� �θ��̸� ����
		return x;
	else
		return Find_Set(p[x], p);		// �ƴϸ� ���
}

void Union(int x, int y, int p[], list *k)
{
	if (p[Find_Set(x, p)] != p[Find_Set(y, p)]) {		// x�Ǻθ�!= y�Ǻθ�
		p[Find_Set(y, p)] = Find_Set(x, p);		// y�� �θ� = x�� �θ�

		cout << "���� " << ++cnt << "(" << x << ", " << y << ")" <<		// ���� �� �� ���� ���
			"����ġ " << k->weigh << endl;
		w = w + k->weigh;
	}
}

void KruskalMST(int G[][N], int p[], list *head)
{
	Reset_Graph(G);		// Ʈ���� �ʱ�ȭ
	
	Make_Set(p);		// �� �����


	for (list *k = head; k->next != nullptr;) {		// ����Ʈ�� Ž��
		
		Union(k->p1, k->p2, p, k);		// ���� �Լ�

		list *temp = k;		// ������ �ӽ� list ������
		k = k->next;		// k�� �������� �ű�
		delete temp;		// temp ����
	}

	cout << "����ġ�� �� " << w << endl;
}

int main()
{
	int G[N][N] = {
		{0,8,2,0,4,0},
		{8,0,4,1,0,2},
		{2,4,0,0,3,7},
		{0,1,0,0,0,1},
		{4,0,3,0,0,9},
		{0,2,7,1,9,0} };

	list *head = nullptr;
	bool check = false;

	for (int i = 0; i < 6; ++i) {			// ����Ʈ�� ����
		for (int j = 0; j < 6; ++j) {

			if (G[i][j] != 0) {

				if (head != nullptr) {
					for (list *p = head; p->next != nullptr; p = p->next) {
						if ((i == p->p1 && j == p->p2) ||
							(j == p->p1 && i == p->p2))
						{
							check = true;
						}
					}
				}

				if (check == false || head == nullptr) {		// �ߺ��� �ƴҰ��
					list *L = new list;
					L->next = nullptr;
					L->p1 = i;
					L->p2 = j;
					L->weigh = G[i][j];

					if (head == nullptr)		// ��尡 ��������� ����
						head = L;

					else {							// �������������
						list *temp = head;		// temp = head
						while (temp->next != nullptr)		// ����Ʈ�� ������ ��
							temp = temp->next;
						temp->next = L;		// ����Ʈ ���� next �� L
					}
				}

			}
			check = false;
		}
	}

	for (list *p = head; p->next != nullptr; p = p->next) {				// ����Ʈ�� �������� ����
		for (list *k = p->next; k->next != nullptr; k = k->next) {

			if (p->weigh > k->weigh) {
				int temp = p->weigh;
				p->weigh = k->weigh;
				k->weigh = temp;

				temp = p->p1;
				p->p1 = k->p1;
				k->p1 = temp;

				temp = p->p2;
				p->p2 = k->p2;
				k->p2 = temp;

			}

		}
	}

	for (list *p = head; p->next != nullptr; p = p->next)								// ����Ʈ Ȯ�ο�
		cout << p->p1 + 1 << " " << p->p2 + 1 << " " << p->weigh << " " << endl;

	int parent[N] = { 0, };
	KruskalMST(G, parent, head);

}