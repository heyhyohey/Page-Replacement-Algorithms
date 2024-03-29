// Clock.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"


int main()
{
	PAGE page_table[SIZE];	//페이지 테이블 구조체 배열
	FILE *fp;	//파일 접근 변수
	errno_t err;	//오류 저장 변수; err=0 -> 성공, err=1 -> 실패
	bool hit;	//hit여부 임시저장
	//포인터 변수, 주소저장 변수, 요구횟수, hit횟수 저장, 반복제어 변수
	int pointer = 0, address, cnt = 0, hit_cnt = 0, i;
	double hit_rate = 0;	//hit

	err = fopen_s(&fp, "input.txt", "r");	//fp에 파일 접근 주소를 저장하고 에러여부를 err에 저장
	for (i = 0; i < sizeof(page_table) / sizeof(PAGE); i++) {	//페이지 테이블 초기화
		page_table[i].address = EMPTY;
		page_table[i].used = false;
	}
	
	if (!err) {	//파일 읽어오기가 성공했을 때에만 실행됨
		do {
			fscanf_s(fp, "%d", &address);	//파일에서 데이터를 하나씩 읽어옴
			hit = false;	//hit 초기화

			if (address == END) continue;	//읽어온 데이터가 END일 경우 실행하지 않고 종료

			cnt++;	//요구횟수 증가

			for (i = 0; i < sizeof(page_table) / sizeof(PAGE); i++) {	//페이지가 존재하는지 검사
				if(page_table[i].address != EMPTY)	//데이터가 있을때만 검사
					if (page_table[i].address == address) {
						page_table[i].used = true;	//hit시 true로 변경
						hit = true;	//hit를 true로 변경
						hit_cnt++;	//hit횟수 증가
						continue;
					}
			}

			if (!hit) {	//hit가 false일때 clock교체알고리즘 시작
				if (is_empty(page_table, sizeof(page_table) / sizeof(PAGE))) {	//테이블이 비어있을경우
					for (i = 0; i < sizeof(page_table) / sizeof(PAGE); i++) {
						if (page_table[i].address == EMPTY) {	//비어있는 테이블을 찾음
							page_table[i].address = address;	//주소삽입
							page_table[i].used = false;		//사용비트 false초기화
							break;	//삽입 후 반복문 탈출
						}
					}
				}
				else {	//테이블이 가득 차있을 경우
					while (page_table[pointer].used) {	//포인터가 가리키는 사용비트가 true일동안 반복
						if (page_table[pointer].used) {	//포인터가 가리키는 페이지의 사용비트가 1일때
							page_table[pointer++].used = false;	//사용비트를 false로 변경 하고 포인터 증가
							print_page_table(page_table, sizeof(page_table) / sizeof(PAGE), pointer, address, hit, cnt);
							//페이지 테이블의 크기와 pointer의 값이 같다면 0으로 초기화
							if (pointer == sizeof(page_table) / sizeof(PAGE))
								pointer = 0;
						}
					}
					page_table[pointer].address = address;	//요구페이지로 교체
					page_table[pointer++].used = false;	//사용비트 초기화 후 포인터 증가
					//페이지 테이블의 크기와 pointer의 값이 같다면 0으로 초기화
					if (pointer == sizeof(page_table) / sizeof(PAGE))
						pointer = 0;
					}
				print_page_table(page_table, sizeof(page_table) / sizeof(PAGE), pointer, address, hit, cnt);
				}
			if(hit)
				print_page_table(page_table, sizeof(page_table) / sizeof(PAGE), pointer, address, hit, cnt);
		} while (address != END);
	}
	else {
		printf("I/O Errer\n");
		system("pause");
		return -1;
	}
	hit_rate = (double)hit_cnt / (double)cnt;	//적중률 계산
	printf("Hit rate = %lf\n", hit_rate);	//적중률 출력
	fflush(stdout);
	fclose(fp);		//파일 닫기
	
	system("pause");

    return 0;
}

