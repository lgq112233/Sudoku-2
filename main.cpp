#include <cstdio>
#include <cstring>
#include <ctime>
#include <iostream>
#include <cstdlib>
using namespace std;

extern int Solve_Sudoku(int x,int y);
extern int Creat_Sudoku(int Sodoku_Num);
int Board[9][9];

int read(char str[]){    //读取数字

	int Num = 0,len=strlen(str);
	for (int i = 0; i < len; i++){
		if (str[i]>'9' || str[i] < '0')    //非数字
			return 0;
		Num *= 10;
		Num += str[i] - '0';
		if (Num > 1000000)    //数字过大
			return 0;
	}
	return Num;
}

int main(int argc,char *argv[]){

	if (strcmp(argv[1], "-c") == 0){    //生成终局命令
		if (int Sudoku_Num = read(argv[2]))
			Creat_Sudoku(Sudoku_Num);    //生成终局
		else
			printf("Please enter the number 1-1000000\n");    //异常处理
	}
	else if (strcmp(argv[1], "-s") == 0){
		freopen(argv[2], "r", stdin);
		freopen("sudoku.txt", "w", stdout);
		int temp,i=0,j=0;
		while (~scanf("%d", &temp)){
			Board[i][j] = temp;
			i += (j + 1) / 9;
			j = (j + 1) % 9;
			if (i == 9){    //求解数独
				Solve_Sudoku(0, 0);
				i = j = 0;
				for (int i = 0; i < 9; i++)   //打印
					for (int j = 0; j < 9; j++)
						printf("%d%c", Board[i][j], j == 8 ? '\n' : ' ');
				putchar('\n');
			}
		}
		fclose(stdin);
		fclose(stdout);
	}

	return 0;
}