#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <cstdlib>
using namespace std;

int Board[9][9];
int Try_List[9];

int Random_Init(int Num[]){    //�������1-9ȫ����

	for (int i = 0; i < 9; i++)    //˳������1~9
		Num[i] = i + 1;
	for (int i = 0; i < 9; i++){
		int j = rand() % 9;    //�������0~8����
		swap(Num[j], Num[8]);    //�����һ�����ֽ���
	}

	return 0;
}

bool Judge(int x,int y,int num){

	for (int i = 0; i < 9; i++){    //��ǰ�С��кϷ��ж�
		if (Board[x][i] == num)
			return 0;
		if (Board[i][y] == num)
			return 0;
	}
	int area_x = x - x % 3, area_y = y - y % 3;    //���������������Ͻ�����
	for (int i = area_x; i < area_x+3; i++)    //��ǰ����Ϸ��ж�
		for (int j = area_y; j < area_y+3;j++)
			if (Board[i][j] == num)
				return 0;

	return 1;
}

int Fill_Sudoku(int x,int y){
	int ori = Board[x][y];    //��¼��ֵ
	int next_x = x + (y + 1) / 9, next_y = (y + 1) % 9;    //��һ��������

	if (x >= 9)    //ȫ�����
		return 1;
	if (Board[x][y]){    //��ǰ�������
		if (Fill_Sudoku(next_x, next_y))
			return 1;
	}
	else{    //��ǰΪ�ո�
		for (int i = 0; i < 9; i++){
			int Try_Num = Try_List[i];    //��ǰ��������
			if (Judge(x, y, Try_Num)){    //�ж��Ƿ�Ϸ�
				Board[x][y] = Try_Num;
				if (Fill_Sudoku(next_x, next_y))
					return 1;
			}
		}
	}
	Board[x][y] = ori;    //���ݻ�ԭ

	return 0;
}

int Creat_Sudoku(int Sodoku_Num){

	freopen("sudoku.txt", "w", stdout);
	srand((unsigned)time(NULL));    //ʱ������
	while (Sodoku_Num--){
		for (int i = 0; i < 9;i++)    //��չ���
			memset(Board[i], 0, sizeof(Board[i]));
		Random_Init(Board[0]);    //�����ʼ����һ������
		for (int i = 0; i < 9; i++)
			if (Board[0][i] == 5){    //ѧ�ź���λ22 (2+2)%9+1=5
				swap(Board[0][0], Board[0][i]);
				break;
			}
		Random_Init(Try_List);    //�����ʼ�����ֳ���˳��
		Fill_Sudoku(1,0);    //���о�
		for (int i = 0; i < 9; i++)   //��ӡ
			for (int j = 0; j < 9; j++)
				printf("%d%c", Board[i][j], j == 8 ? '\n' : ' ');
		putchar('\n');
	}
	fclose(stdout);

	return 0;
}

int Solve_Sudoku(char file[]){

	freopen(file, "r", stdin);
	freopen("sudoku.txt", "w", stdout);
	int temp, i = 0, j = 0;
	Random_Init(Try_List);
	while (~scanf("%d", &temp)){
		Board[i][j] = temp;
		i += (j + 1) / 9;
		j = (j + 1) % 9;
		if (i == 9){    //�������
			Fill_Sudoku(0, 0);
			i = j = 0;
			for (int i = 0; i < 9; i++)   //��ӡ
				for (int j = 0; j < 9; j++)
					printf("%d%c", Board[i][j], j == 8 ? '\n' : ' ');
			putchar('\n');
		}
	}
	fclose(stdin);
	fclose(stdout);

	return 0;
}