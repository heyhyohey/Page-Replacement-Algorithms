// stdafx.cpp : 표준 포함 파일만 들어 있는 소스 파일입니다.
// Clock.pch는 미리 컴파일된 헤더가 됩니다.
// stdafx.obj에는 미리 컴파일된 형식 정보가 포함됩니다.

#include "stdafx.h"

// TODO: 필요한 추가 헤더는
// 이 파일이 아닌 STDAFX.H에서 참조합니다.

//페이지테이블의 빈자리가 있는지 검사하는 함수
bool is_empty(PAGE arr[], int size) {
	int i;	//반복제어 변수
	for (i = 0; i < size; i++)	//하나라도 빈자리가 있다면 true 리턴
		if (arr[i].address == EMPTY) return true;
	return false;	//모두 검사하고 반복문을 빠져나왔다면 테이블이 차있다고 간주
}

//출력 함수
void print_page_table(PAGE arr[], int size, int pointer, int address, int hit, int cnt) {
	int i;
	printf("========================== %02d ==========================\n", cnt);	//순번출력
	printf("Input Page = %d\n", address);	//요구된 페이지 출력
	if (hit)				//히트 여부 출력
		printf("hit = true\n");
	else printf("hit = false\n");
	printf("Page\t\t");
	for (i = 0; i < size; i++) {	//페이지 출력
		if (arr[i].address == EMPTY)
			printf("-\t");
		else
			printf("%02d\t", arr[i].address);
	}
	printf("\nUsed bit\t");
	for (i = 0; i < size; i++)	//페이지 주소 출력
		if (arr[i].address == EMPTY)
			printf("-\t");
		else
			printf("%d\t", arr[i].used);
	printf("\nPointer\t\t");	//포인터의 위치 출력
	for (i = 0; i < pointer; i++) {
		printf("\t");
	}
	printf("pointer");
	printf("\n\n");
}