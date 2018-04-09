#include "stdafx.h"
#include "CppUnitTest.h"
#include "../generator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestRead)
		{
			Assert::IsTrue(read("0") == 0);
			Assert::IsTrue(read("abc") == 0);
			Assert::IsTrue(read("12345") == 12345);
			Assert::IsTrue(read("10000000") == 0);
			Assert::IsTrue(read("-56") == 0);
			Assert::IsTrue(read("1000000") == 1000000);
		}

		TEST_METHOD(TestRandom_Init)
		{
			int text = 10;
			while (text--){
				int num[9], vis[10] = { 0 }, flag = 1;
				srand((unsigned)time(NULL));
				Random_Init(num);
				for (int i = 0; i < 9; i++){
					if (num[i] < 1 || num[i] > 9)
						flag = 0;
					if (vis[num[i]])
						flag = 0;
					vis[num[i]] = 1;
				}
				Assert::IsTrue(flag == 1);
			}
		}

		TEST_METHOD(TestJudge)
		{
			int B[9][9] = { 5, 2, 1, 4, 9, 6, 8, 7, 3,
				3, 9, 4, 7, 1, 8, 5, 6, 2,
				6, 8, 7, 0, 3, 2, 1, 4, 9,
				1, 4, 3, 9, 5, 7, 6, 2, 8,
				2, 7, 8, 6, 4, 3, 9, 1, 5,
				9, 6, 5, 8, 2, 1, 4, 3, 7,
				7, 5, 6, 2, 8, 4, 3, 9, 1,
				4, 1, 9, 3, 7, 5, 2, 8, 6,
				8, 3, 2, 1, 6, 9, 7, 5, 4
			};
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
					Board[0][i][j] = B[i][j];
			Assert::IsTrue(Judge(0, 2, 3, 5) == 1);
			int C[9][9] = { 5, 2, 1, 4, 9, 6, 8, 7, 3,
				3, 9, 4, 7, 1, 8, 5, 6, 2,
				6, 8, 7, 0, 3, 2, 1, 4, 9,
				1, 4, 3, 9, 5, 7, 6, 2, 8,
				2, 7, 8, 6, 4, 3, 9, 1, 5,
				9, 6, 5, 8, 2, 1, 4, 3, 7,
				7, 5, 6, 2, 8, 4, 3, 9, 1,
				4, 1, 9, 3, 7, 5, 2, 8, 6,
				8, 3, 2, 1, 6, 9, 7, 5, 4
			};
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
					Board[0][i][j] = C[i][j];
			Assert::IsTrue(Judge(0, 2, 3, 4) == 0);
		}

		TEST_METHOD(TestFill)
		{
			int B[9][9] = { 0, 2, 1, 4, 9, 0, 8, 7, 0,
				3, 0, 4, 7, 1, 8, 5, 6, 2,
				6, 8, 7, 0, 3, 0, 1, 4, 9,
				1, 4, 0, 9, 5, 7, 6, 2, 0,
				0, 7, 8, 0, 4, 3, 0, 1, 5,
				9, 6, 0, 8, 2, 0, 4, 3, 7,
				7, 5, 6, 2, 8, 4, 3, 0, 1,
				4, 1, 9, 0, 7, 0, 2, 8, 6,
				0, 0, 2, 1, 6, 9, 7, 0, 4
			};
			for (int i = 0; i < 9; i++)
				for (int j = 0; j < 9; j++)
					Board[0][i][j] = B[i][j];
			Assert::IsTrue(Fill_Sudoku(0, 0, 0) == 0);
		}

		TEST_METHOD(TestCreat)
		{
			Assert::IsTrue(Creat_Sudoku(1) == 0);
			Assert::IsTrue(Creat_Sudoku(20) == 0);
			Assert::IsTrue(Creat_Sudoku(100000) == 0);
		}

	};
}