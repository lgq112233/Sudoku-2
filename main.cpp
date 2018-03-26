#include <stdio.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>

extern int Solve_Sudoku(char File[]);
extern int Creat_Sudoku(int Sodoku_Num);

int read(char str[]){    //读取数字

	int Num = 0,len=strlen(str);
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

int main(int argc,char *argv[]){

	if (argc < 2){    //参数异常处理
		printf("Please use the parameters\n");
		return 0;
	}
	if (strcmp(argv[1], "-c") == 0){    //生成终局命令
		if (int Sudoku_Num = read(argv[2]))
			Creat_Sudoku(Sudoku_Num);    //生成终局
		else
			printf("Please enter the number 1~1000000\n");    //异常处理
	}
	else if (strcmp(argv[1], "-s") == 0){    //求解残局命令
		Solve_Sudoku(argv[2]);
	}

	return 0;
}