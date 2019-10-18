#include <iostream>

using namespace std;

constexpr auto N = 6;

void DFS(int G[][N], bool visited[], int n)
{
	if (visited[n] == false) {
		visited[n] = true;
		cout << n + 1 << " ";



		for (int i = 0; i < N; ++i)
			if (G[n][i] == 1)
				DFS(G, visited, i);
	}
}

void enqueue(int queue[], bool visited[], int &back, int n)		// ���� ���� �� �湮�ߴ� ó����
{
	back = back + 1;
	queue[back] = n + 1;		// n + 1 �� Vertex �� 1���� �ִٰ� ����⿡ n + 1 �� ����
	visited[n] = true;
}

void dequeue(int queue[], int &front)
{
	front = front + 1;
	cout << queue[front] << " ";
}

void BFS(int G[][N], bool visited[], int Q[], int &back, int &front, int n)
{
	enqueue(Q, visited, back, n);		// �� ó�� ������ ��带 ť�� ����

	while (front < N - 1) {		// ť�� �ִ� N�� ���Ƿ� front �� N - 1 ���� ũ�� ���� ��ȸ�Ѱ�
		dequeue(Q, front);

		for (int i = 0; i < 6; i++) {						// ó�� ��忡�� ������ Vertex ���� ã��
			if (G[n][i] == 1 && visited[i] == false)		
				enqueue(Q, visited, back, i);				// ������ Vertex ���� ť�� ����
		}
		n = Q[front + 1] - 1;								// �׷����� ���� ��ȸ�� Vertex�� ù��°ť���� ������ ���� ���� ���� �� ����
	}
	back = -1;		// ��ȸ ����� ť�� �ٽ� ����ϱ����� �ʱⰪ���� ��������
	front = -1;
}

void Set(bool visited[])		// visited ���� �Լ�
{
	for (int i = 0; i < N; ++i)
		visited[i] = false;
}

int main()
{

	int G[N][N] =
	{ {0,1,1,1,0,1},
	  {1,0,1,0,0,0},
	  {1,1,0,0,1,0},
	  {1,0,0,0,0,1},
	  {0,0,1,0,0,1},
	  {1,0,0,1,1,0} };

	bool visited[N];

	int Queue[N];
	int back = -1;		// inqueue �� ����
	int front = -1;		// dequeue �� ����


	Set(visited);
	cout << "���۳�� : 1" << endl;
	cout << "DFS: " << endl;
	DFS(G, visited, 0);
	cout << endl << endl;

	cout << "BFS: " << endl;
	Set(visited);
	BFS(G, visited, Queue, back, front, 0);
	cout << endl << endl;


	Set(visited);
	cout << "���۳�� : 2" << endl;
	cout << "DFS: " << endl;
	DFS(G, visited, 1);
	cout << endl << endl;

	cout << "BFS: " << endl;
	Set(visited);
	BFS(G, visited, Queue, back, front, 1);
	cout << endl << endl;


	return 0;

}