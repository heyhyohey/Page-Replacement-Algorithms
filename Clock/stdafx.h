// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once


#include <stdio.h>
#include <tchar.h>
#include <stdbool.h>
#include <Windows.h>


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.
//테이블 사이즈 정의
#define SIZE 5
#define EMPTY -1
#define END 99
//페이지 구조체 선언
typedef struct node PAGE;
struct node {
	int address;	//물리주소
	bool used;		//사용비트
};

bool is_empty(PAGE[], int);	//페이지테이블의 빈자리가 있는지 검사하는 함수
void print_page_table(PAGE[], int, int, int, int, int);	//페이지테이블 출력
