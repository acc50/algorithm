// -------------------------------- 모든 쌍 최소거리 찾기 -------------------


//#include <iostream>
//
//#define V 5
//#define INF 100
//
//int min(int a, int b)
//{
//	if (a > b)
//		return b;
//	else
//		return a;
//}
//
//void AllPairsShortest(int graph[][V])
//{
//	for (int k = 0; k < V; ++k) {
//		for (int i = 0; i < V ; ++i) {
//
//			if (i != k) {
//				for (int j = 0; j < V; ++j) {
//
//					if (j != k && j != i) {
//						graph[i][j] = min(graph[i][k] + graph[k][j], graph[i][j]);
//					}
//
//				}
//			}
//
//		}
//	}
//
//	for (int i = 0; i < V; ++i) {
//		for (int j = 0; j < V; ++j) {
//			std::cout.width(2);
//			std::cout << graph[i][j] << "  ";
//		}
//		std::cout << std::endl;
//	}
//
//}
//
//int main()
//{
//	int graph[V][V] = { {0  ,4  ,2  ,5  ,INF},
//					  {INF,0  ,1  ,INF,4  },
//					  {1  ,3  ,0  ,1  ,2  },
//					  {-2 ,INF,INF,0  ,2  },
//					  {INF,-3 ,3  ,1  ,0  } };
//
//
//	AllPairsShortest(graph);
//
//}


// -------------------------------- 모든 쌍 최소거리 찾기 -------------------





//------------------------------------------ 배낭문제 --------------------------------------------

#include <iostream>

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

void KnapSack(int val[], int wt[], int w, int n)
{
	int **arr = new int*[n + 1];		// 배열을 가리키는 포인터를 선언
										// n + 1개 배열 동적할당
	for (int i = 0; i < n + 1; ++i)
		arr[i] = new int[w + 1];		// 각 배열은 w + 1개의 인자

	for (int i = 0; i < n + 1; ++i)
		for (int j = 0; j < w + 1; ++j)
			arr[i][j] = 0;

	for (int i = 1; i < n + 1 ; ++i) {
		for (int j = 1; j < w + 1; ++j) {

			if (wt[i - 1] > j) {
				arr[i][j] = arr[i - 1][j];
			}
			else {
				arr[i][j] = max(arr[i - 1][j], arr[i - 1][j - wt[i - 1]] + val[i - 1]);
			}

		}
	}

	for (int i = 0; i < n + 1; ++i) {
		for (int j = 0; j < w + 1; ++j) {
			std::cout.width(3);
			std::cout << arr[i][j] << "   ";
		}
		std::cout << std::endl;
	}
		
	std::cout << std::endl << std::endl << "최종 해 : " << arr[n][w];

}

int main()
{
	int val[] = { 10, 40, 30, 50 };
	int wt[] = { 5,4,6,3 };

	int w = 10;
	int n = sizeof(val) / sizeof(val[0]);

	KnapSack(val, wt, w, n);


}

//------------------------------------------ 배낭문제 --------------------------------------------