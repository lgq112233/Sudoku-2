#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>

int Board[25][9][9];
int Try_List[9];

int read(char str[]){    //��ȡ����

	int Num = 0, len = strlen(str);
	for (int i = 0; i < len; i++){
		if (str[i]>'9' || str[i] < '0')    //������
			return 0;
		Num *= 10;
		Num += str[i] - '0';
		if (Num > 1000000 || Num == 0)     //���ֲ��ڷ�Χ��
			return 0;
	}
	return Num;
}

void swap(int &a, int &b){    //����������
	
	int temp = a;
	a = b;
	b = temp;

}

int Random_Init(int Num[]){    //�������1-9ȫ����

	for (int i = 0; i < 9; i++)    //˳������1~9
		Num[i] = i + 1;
	for (int i = 0; i < 20; i++){
		int j = rand() % 9;    //�������0~8����
		swap(Num[j], Num[8]);    //�����һ�����ֽ���
	}

	return 0;
}

int Judge(int s,int x,int y,int num){    //�ж����Ϸ�

	for (int i = 0; i < 9; i++){    //��ǰ�С��кϷ��ж�
		if (Board[s][x][i] == num)
			return 0;
		if (Board[s][i][y] == num)
			return 0;
	}
	int area_x = x - x % 3, area_y = y - y % 3;    //���������������Ͻ�����
	for (int i = area_x; i < area_x+3; i++)    //��ǰ����Ϸ��ж�
		for (int j = area_y; j < area_y+3;j++)
			if (Board[s][i][j] == num)
				return 0;

	return 1;
}

int Fill_Sudoku(int s,int x,int y){    //��亯��
	int init = Board[s][x][y];    //��¼��ֵ
	int next_x = x + (y + 1) / 9, next_y = (y + 1) % 9;    //��һ��������

	if (x >= 9)    //ȫ�����
		return 1;
	if (Board[s][x][y]){    //��ǰ�������
		if (Fill_Sudoku(s,next_x, next_y))
			return 1;
	}
	else{    //��ǰΪ�ո�
		for (int i = 0; i < 9; i++){
			int Try_Num = Try_List[i];    //��ǰ��������
			if (Judge(s,x, y, Try_Num)){    //�жϺϷ�
				Board[s][x][y] = Try_Num;
				if (Fill_Sudoku(s,next_x, next_y))
					return 1;
			}
		}
	}
	Board[s][x][y] = init;    //���ݻ�ԭ

	return 0;
}

void Swap_Col(int s,int beg,int end){    //���������

	for (int i = 0; i < 5; i++){ 
		int j = rand() % (end-beg+1) + beg;
		for (int k = 0; k < 9;k++)
			swap(Board[s][k][j], Board[s][k][end]);   
	}

}

void Swap_Row(int s,int beg, int end){    //���������

	for (int i = 0; i < 5; i++){
		int j = rand() % (end - beg + 1) + beg;
		for (int k = 0; k < 9; k++)
			swap(Board[s][j][k], Board[s][end][k]);
	}

}

int Creat_Sudoku(int Sodoku_Num){    //�����վ�

	freopen("sudoku.txt", "w", stdout);
	srand((unsigned)time(NULL));    //ʱ������
	while (Sodoku_Num>0){
		memset(Board, 0, sizeof(Board));    //��չ���
		for (int i = 0; i < 20; i++){    //ÿ������20�����Ӿ���
			Random_Init(Board[i][0]);    //�����ʼ����һ������
			for (int j = 0; j < 9; j++)
				if (Board[i][0][j] == 5){    //ѧ�ź���λ22 (2+2)%9+1=5
					swap(Board[i][0][0], Board[i][0][j]);
					break;
				}
			Random_Init(Try_List);    //�����ʼ�����ֳ���˳��
			Fill_Sudoku(i, 1, 0);    //��ʼ���
		}
		int extend = 1000;
		while (extend--){    //��չ1000���վ�
			if (Sodoku_Num-- == 0)
				break;
			int sand = rand() % 20;
			Swap_Col(sand, 1, 2), Swap_Row(sand, 1, 2);
			Swap_Col(sand, 3, 5), Swap_Row(sand, 3, 5);
			Swap_Col(sand, 6, 8), Swap_Row(sand, 6, 8);
			for (int i = 0; i < 9; i++)   //��ӡ
				for (int j = 0; j < 9; j++){
					if (j == 8)
						putchar('\n');
					else{
						putchar(Board[sand][i][j] + '0');
						putchar(' ');
					}
				}
			if (Sodoku_Num)
				putchar('\n');
		}
	}
	fclose(stdout);

	return 0;
}

int Solve_Sudoku(char File[]){    //���о�

	freopen(File, "r", stdin);
	freopen("sudoku.txt", "w", stdout);
	srand((unsigned)time(NULL));    //ʱ������
	Random_Init(Try_List);
	int i = 0, j = 0;
	while (~scanf("%d", &Board[0][i][j])){
		i += (j + 1) / 9;    //��һ��������
		j = (j + 1) % 9;
		if (i == 9){    //������� �������
			Fill_Sudoku(0, 0, 0);
			i = j = 0;
			for (int i = 0; i < 9; i++)   //��ӡ
				for (int j = 0; j < 9; j++){
					if (j == 8)
						putchar('\n');
					else{
						putchar(Board[0][i][j] + '0');
						putchar(' ');
					}
				}
			putchar('\n');
		}
	}
	fclose(stdin);
	fclose(stdout);

	return 0;
}