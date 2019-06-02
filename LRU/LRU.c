#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5
struct table
{
	int page;
	
	int count;
};
void print(struct table* page, int input, int hit);

int main(void)
{
	bool checking[MAX_SIZE];
	struct table pagetable[MAX_SIZE];
	FILE* stream;
	int i, hit = 0;
	int input;
	int count = 0;
	int change;
	bool check;
	stream = fopen("input.txt", "r+");
	for (i = 0; i < MAX_SIZE; i++)
	{
		pagetable[i].page = -1;
		
		pagetable[i].count = 0;
	}
	while (true)
	{
		check = false;
		//들어온 시간 증가
		for (i = 0; i < MAX_SIZE; i++)
		{
			if (pagetable[i].page != -1)
			{
				pagetable[i].count++;
			}
		}
		fscanf(stream, "%d", &input);
		
		//99가 들어오면 종료
		if (input == 99)
			break;
		//hit확인
		for (i = 0; i < MAX_SIZE; i++)
		{
			if (pagetable[i].page == input) {
				check = true;
				hit++;
				pagetable[i].count = 0;
				break;
			}
		}

		if (check == true) {
			count++;
			print(pagetable, input, hit);
			continue;
		}
		for (i = 0; i < MAX_SIZE; i++)
		{
			if (pagetable[i].page == -1)
			{
				check = true;
				pagetable[i].page = input;
				break;
			}
		}
		if (check == true) {
			count++;
			print(pagetable, input, hit);
			continue;
		}
		
		change = 0;
		//가장 오래된 페이지를 교체
		for (i = 0; i < MAX_SIZE; i++)
		{
			if (pagetable[change].count < pagetable[i].count) {
				change = i;
			}
		}
		pagetable[change].page = input;
		pagetable[change].count = 0;
		print(pagetable, input, hit);
		count++;
	}
	
	
	printf("적중률 %lf \n", (double)(hit) / (double)(count));
	getchar();
	fclose(stream);
	return 0;
}

void print(struct table* page, int input, int hit) {
	int i;

	printf("Input Page = %d\n", input);	//요구된 페이지 출력
	printf("\nhit\t\t%d\n", hit);
	printf("Page\t\t");
	
	for (i = 0; i < MAX_SIZE; i++) {	//페이지 출력
		if (page[i].page == -1)
			printf("-\t");
		else
			printf("%02d\t", page[i].page);
	}
	
	printf("\ncount\t\t");
	for (i = 0; i < MAX_SIZE; i++)	//페이지 주소 출력
		if (page[i].page == -1)
			printf("-\t");
		else
			printf("%d\t", page[i].count);
	printf("\n\n");
	
}