#include<stdio.h>
#define MAX_SIZE 30
#define TRUE 1

void print_fifo(int input, int* FRAME, int count, int hit)
{
	printf("input page = %d \n", input);
	printf("  %d   %d   %d   %d   %d \n", FRAME[0], FRAME[1], FRAME[2], FRAME[3], FRAME[4]);
	printf(" < count=%d > < hit=%d > \n\n", count, hit);
}

int main() {

	int hit = 0, hit2 = 0, count = 0, input; // hit Ƚ��, �� �䱸Ƚ��, �о�� �� ����

	FILE * fp; 
	fp = fopen("input.txt", "r"); // ���� �ҷ�����

	if (fp == NULL) { // ������ ����ִ��� Ȯ��
		printf("������ ���� �� �����ϴ�.");
	}

	int FRAME[5] = {-1, -1, -1, -1, -1}; // ������ �ʱ�ȭ
	int num = 0;

	while (TRUE) {

		fscanf(fp, "%d", &input); // �ϳ� �о����

		if (input == 99) { // 99 ������ �ߴ�

			print_fifo(input, FRAME, count, hit); // ������ ���
			break;
		}
		count++;

		for (int i = 0; i < 5; i++) { // hit ���� Ȯ��
			if ( FRAME[i] == input) {
				hit++;
				break;
			}
		}

		if ( hit2 == hit ) {
			FRAME[num++] = input; // ������ ������ ��ġ ����
			if (num == 5)
				num = 0;
		}
		else {
			hit2++;
		}

		print_fifo(input, FRAME, count, hit); // ������ ���
	}
	
	printf("Hit rate = %lf\n", (double)hit/(double)count );	//���߷� ���, ���
	fclose(fp);	//���� �ݱ�

	return 0;
}