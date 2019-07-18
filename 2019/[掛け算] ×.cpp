#include <stdio.h>
int main(void)

{
	int x, y, z;

	printf("------------------------------- [ Input ]-------------------------------\n\n");
	printf("x × y = z の計算をします[掛け算]\n\n\n");

	printf(" x に代入する自然数を入力してください\n\n");
	printf(" x = ");
	scanf_s("%d", &x);


	printf("\n\n\n y に代入する自然数を入力してください\n\n");
	printf(" y = ");
	scanf_s("%d", &y);

	z = x * y;



	printf("-------------------------------[ OutPut ]-------------------------------\n\n");
	printf(" x = %d\n", x);
	printf(" y = %d\n", y);

	printf("\n [ x × y = %d]\n", z);

	printf("\n\n-------------------------------------------------------------------------");
	printf("\nこのプログラムを動かしてくれて ありがとう!\n");
	printf("君も釧路工業高等専門学校でプログラムについて 一緒に学ぼう！");
	printf("\n\n\n\n　");

	return 0;
}