#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>

int Board[25][9][9];
int Try_List[9];

int read(char str[]){    //读取参数

	int Num = 0, len = strlen(str);
	for (int i = 0; i < len; i++){
		if (str[i]>'9' || str[i] < '0')    //非数字
			return 0;
		Num *= 10;
		Num += str[i] - '0';
		if (Num > 1000000 || Num == 0)     //数字不在范围内
			return 0;
	}
	return Num;
}

void swap(int &a, int &b){    //交换两个数
	
	int temp = a;
	a = b;
	b = temp;

}

int Random_Init(int Num[]){    //随机生成1-9全排列

	for (int i = 0; i < 9; i++)    //顺序填入1~9
		Num[i] = i + 1;
	for (int i = 0; i < 20; i++){
		int j = rand() % 9;    //随机生成0~8数字
		swap(Num[j], Num[8]);    //与最后一个数字交换
	}

	return 0;
}

int Judge(int s,int x,int y,int num){    //判断填充合法

	for (int i = 0; i < 9; i++){    //当前行、列合法判断
		if (Board[s][x][i] == num)
			return 0;
		if (Board[s][i][y] == num)
			return 0;
	}
	int area_x = x - x % 3, area_y = y - y % 3;    //计算所处宫格左上角坐标
	for (int i = area_x; i < area_x+3; i++)    //当前宫格合法判断
		for (int j = area_y; j < area_y+3;j++)
			if (Board[s][i][j] == num)
				return 0;

	return 1;
}

int Fill_Sudoku(int s,int x,int y){    //填充函数
	int init = Board[s][x][y];    //记录初值
	int next_x = x + (y + 1) / 9, next_y = (y + 1) % 9;    //下一方格坐标

	if (x >= 9)    //全部完成
		return 1;
	if (Board[s][x][y]){    //当前格已填充
		if (Fill_Sudoku(s,next_x, next_y))
			return 1;
	}
	else{    //当前为空格
		for (int i = 0; i < 9; i++){
			int Try_Num = Try_List[i];    //当前尝试数字
			if (Judge(s,x, y, Try_Num)){    //判断合法
				Board[s][x][y] = Try_Num;
				if (Fill_Sudoku(s,next_x, next_y))
					return 1;
			}
		}
	}
	Board[s][x][y] = init;    //回溯还原

	return 0;
}

void Swap_Col(int s,int beg,int end){    //列随机交换

	for (int i = 0; i < 5; i++){ 
		int j = rand() % (end-beg+1) + beg;
		for (int k = 0; k < 9;k++)
			swap(Board[s][k][j], Board[s][k][end]);   
	}

}

void Swap_Row(int s,int beg, int end){    //行随机交换

	for (int i = 0; i < 5; i++){
		int j = rand() % (end - beg + 1) + beg;
		for (int k = 0; k < 9; k++)
			swap(Board[s][j][k], Board[s][end][k]);
	}

}

int Creat_Sudoku(int Sodoku_Num){    //生成终局

	freopen("sudoku.txt", "w", stdout);
	srand((unsigned)time(NULL));    //时间种子
	while (Sodoku_Num>0){
		memset(Board, 0, sizeof(Board));    //清空宫格
		for (int i = 0; i < 20; i++){    //每轮生成20个种子矩阵
			Random_Init(Board[i][0]);    //随机初始化第一行数字
			for (int j = 0; j < 9; j++)
				if (Board[i][0][j] == 5){    //学号后两位22 (2+2)%9+1=5
					swap(Board[i][0][0], Board[i][0][j]);
					break;
				}
			Random_Init(Try_List);    //随机初始化数字尝试顺序
			Fill_Sudoku(i, 1, 0);    //开始填充
		}
		int extend = 1000;
		while (extend--){    //扩展1000个终局
			if (Sodoku_Num-- == 0)
				break;
			int sand = rand() % 20;
			Swap_Col(sand, 1, 2), Swap_Row(sand, 1, 2);
			Swap_Col(sand, 3, 5), Swap_Row(sand, 3, 5);
			Swap_Col(sand, 6, 8), Swap_Row(sand, 6, 8);
			for (int i = 0; i < 9; i++)   //打印
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

int Solve_Sudoku(char File[]){    //求解残局

	freopen(File, "r", stdin);
	freopen("sudoku.txt", "w", stdout);
	srand((unsigned)time(NULL));    //时间种子
	Random_Init(Try_List);
	int i = 0, j = 0;
	while (~scanf("%d", &Board[0][i][j])){
		i += (j + 1) / 9;    //下一数字坐标
		j = (j + 1) % 9;
		if (i == 9){    //读入完毕 求解数独
			Fill_Sudoku(0, 0, 0);
			i = j = 0;
			for (int i = 0; i < 9; i++)   //打印
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