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

	int hit = 0, hit2 = 0, count = 0, input; // hit 횟수, 총 요구횟수, 읽어온 값 저장

	FILE * fp; 
	fp = fopen("input.txt", "r"); // 파일 불러오기

	if (fp == NULL) { // 파일이 비어있는지 확인
		printf("파일을 읽을 수 없습니다.");
	}

	int FRAME[5] = {-1, -1, -1, -1, -1}; // 프레임 초기화
	int num = 0;

	while (TRUE) {

		fscanf(fp, "%d", &input); // 하나 읽어오기

		if (input == 99) { // 99 만나면 중단

			print_fifo(input, FRAME, count, hit); // 프레임 출력
			break;
		}
		count++;

		for (int i = 0; i < 5; i++) { // hit 여부 확인
			if ( FRAME[i] == input) {
				hit++;
				break;
			}
		}

		if ( hit2 == hit ) {
			FRAME[num++] = input; // 저장할 프레임 위치 변경
			if (num == 5)
				num = 0;
		}
		else {
			hit2++;
		}

		print_fifo(input, FRAME, count, hit); // 프레임 출력
	}
	
	printf("Hit rate = %lf\n", (double)hit/(double)count );	//적중률 계산, 출력
	fclose(fp);	//파일 닫기

	return 0;
}