#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct panel
{
	int id;
	char keyword[3][5];
	int decision;
} panel;

typedef struct story
{
	int id;
	char sentence[10][255];
	unsigned char lines;
}story;

//패널이 한 사연에 대해 판단
//그린라이트면 1, 아니면 0 return
int is_greenlight(panel p, story s)
{
	int i, j, check[3] = { 0, 0, 0 };
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 3; j++)
		{
			//사연에 패널이 반응하는 keyword가 있는지 체크
			if (strstr(s.sentence[i], p.keyword[j]) != NULL)
			{
				check[j] = 1;
			}
		}
	}
	if (check[0] == 1 && check[1] == 1 && check[2] == 1)
		return 1;
	else
		return 0;
}

//구조체 story에 있는 문장을 출력하는 함수
void print_sentences(story s)
{
	int i = 0;
	for (i = 0; i < s.lines; i++)
	{
		printf("\t%s", s.sentence[i]);
	}
	printf("\n");
}

int main()
{
	FILE *fp;
	char keywords[7][5] = { "like", "talk", "meet", "call", "gift", "text", "kind" };
	char filename[11] = "story0.txt"; //파일 이름, '0'부분은 뒤에서 수정
	char inputword[255]; //파일에서 읽은 문장을 임시로 저장
	int random_keyword, i, j; //random_keyword: keywords중에서 랜덤하게 뽑기 위함. i,j: for for loop
	int panel_num = 0, story_num = 0;
	int check_repeat[2] = { -1, -1 }; //keyword들의 중복 확인용
	panel* panels;
	story* stories;

	srand(time(NULL));
	printf("number of panels: ");
	scanf("%d", &panel_num);
	printf("number of stories: ");
	scanf("%d", &story_num);

	//입력값이 잘못돼있으면 -1을 리턴하고 종료
	if (panel_num < 0 || story_num < 0)
	{
		printf("wrong input\n");
		return -1;
	}

	panels = (panel*)malloc(panel_num*sizeof panel);
	stories = (story*)malloc(panel_num*sizeof story);

	//panel이 반응할 단어를 랜덤하게 선택
	for (i = 0; i < panel_num; i++)
	{
		panels[i].id = i;
		for (j = 0; j < 3; j++)
		{
			//중복이 아닐 때까지 계속 반복하여
			//랜덤하게 단어 선택
			while (true)
			{
				random_keyword = rand() % 7;
				if (j != 2)
				{
					check_repeat[j] = random_keyword;
				}

				if (check_repeat[j - 1] != random_keyword)
				{
					break;
				}
			}
			strcpy(panels[i].keyword[j], keywords[random_keyword]);
		}
	}

	//story들을 stories에 저장
	for (i = 0; i < story_num; i++)
	{
		filename[5] = '1' + i; //filename[5]가 '0'부분
		fp = fopen(filename, "r");

		stories[i].id = i;
		j = 0;
		while (!feof(fp))
		{
			fgets(inputword, 255, fp);
			strcpy(stories[i].sentence[j], inputword);
			j++;
		}
		stories[i].lines = j;
		fclose(fp);
	}

	//그린라이트 여부 확인 후 그에 맞춰서 출력
	for (i = 0; i < story_num; i++)
	{
		printf("\n   Story %d\n", i + 1);
		print_sentences(stories[i]);
		for (j = 0; j < panel_num; j++)
		{
			printf(" panel %d: ", j + 1);
			if (is_greenlight(panels[j], stories[i]) == 1)
				printf("ON\n");
			else
				printf("OFF\n");
		}
		printf("\n");
	}
	return 0;
}