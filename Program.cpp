#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<time.h>
#include<stack>
#include <queue>
#include<Windows.h>
using namespace std;

queue<int> Q;

/*
1 - взыешенный ориентированный
2 - взыешенный неориентированный
3 - невзыешенный ориентированный
4 - невзыешенный неориентированный
*/
int rad = -1, diam = 0;

void BFSD(int** G, int v, int* DIST, int size) {
	Q.push(v);
	DIST[v] = 0;
	while (!Q.empty()) {
		v = Q.front();
		Q.pop();
		for (int i = 0; i < size; i++) {
			if (G[v][i] > 0 && DIST[i] == -1) {
				Q.push(i);
				DIST[i] = DIST[v] + G[v][i];
			}
		}
	}
}

int size_v = 0, size_cen = 0;

void POSH(int* DIST, int size, int** G, int v, int vibor) {
	int maxi = 0;

	for (int i = 0; i < size; i++) {
		DIST[i] = -1;
	}

	BFSD(G, v, DIST, size);

	switch (vibor) {
	case(1):
		cout << "\n";
		cout << "Соединения " << v << " вершины ";
		for (int i = 0; i < size; i++) {
			cout << DIST[i] << " ";
			maxi = max(maxi, DIST[i]);
		}
		if (diam < maxi) {
			diam = maxi;
		}
		if (rad > maxi || rad == -1) {
			rad = maxi;
		}
		break;
	case(2):
		size_v = 0;
		for (int i = 0; i < size; i++) {
			maxi = max(maxi, DIST[i]);
			if (DIST[i] != -1) {
				size_v += DIST[i];
			}
		}
		if (diam == maxi) {
			cout << v << " - переферийная \n";
		}
		if (rad == maxi) {
			cout << v << " - центральная \n";
		}
		if (size_cen == 0 || size_cen > size_v) {
			size_cen = size_v;
		}
		break;
	case(3):
		size_v = 0;
		for (int i = 0; i < size; i++) {
			if (DIST[i] != -1) {
				size_v += DIST[i];
			}
		}
		if (size_v == size_cen) {
			cout << v << " вершина - центр тяжести \n";
		}
		break;
	default:
		cout << " ОШИБКА";
	}




}



int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int** G, size = 0, vershina, * DIST, v, vibor;

	if (argv[1] == NULL) {
		cout << " \n Введите количество вершин графа: ";
		cin >> size;
	}
	else {
		size = int(*argv[2]) - 48;
	}



	G = new int* [size]; // создаём двумерный массив 
	DIST = new int[size];
	for (int i = 0; i < size; i++) {

		G[i] = new int[size];
	}

	if (argv[1] == NULL) {
		cout << "Выберите какой граф вы хотите: ";
		cin >> vibor;
	}
	else {
		vibor = int(*argv[1]) - 48;
	}
	switch (vibor) {
	case(1):
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (i == j) { G[i][j] = 0; }
				else {
					G[i][j] = rand() % 2;
					if (G[i][j] == 1) {
						G[i][j] = rand() % 9;
					}
				}
			}
		}
		break;
	case(2):
		for (int i = 0; i < size; i++) {
			for (int j = i; j < size; j++) {
				if (i == j) { G[i][j] = 0; }
				else {
					G[i][j] = rand() % 2;
					if (G[i][j] == 1) {
						G[i][j] = rand() % 9;
					}
					G[j][i] = G[i][j];
				}
			}
		}
		break;
	case(3):
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (i == j) { G[i][j] = 0; }
				else {
					G[i][j] = rand() % 2;
				}
			}
		}
		break;
	case(4):
		for (int i = 0; i < size; i++) {
			for (int j = i; j < size; j++) {
				if (i == j) { G[i][j] = 0; }
				else {
					G[i][j] = rand() % 2;
					G[j][i] = G[i][j];
				}
			}
		}
		break;
	default:
		cout << "!ОШИБКА!\n";
		cout << "Выберите какой граф вы хотите: ";
		cin >> vibor;
	}



	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << G[i][j] << " ";
		}
		cout << "\n";
	}


	for (int i = 0; i < size; i++) {
		POSH(DIST, size, G, i, 1);
	}

	cout << "\n Радиус = " << rad << " Диаметр = " << diam << "\n\n";
	for (int i = 0; i < size; i++) {
		POSH(DIST, size, G, i, 2);
	}

	for (int i = 0; i < size; i++) {
		POSH(DIST, size, G, i, 3);
	}

	cout << "\n";
	system("pause");
	return 0;
}
