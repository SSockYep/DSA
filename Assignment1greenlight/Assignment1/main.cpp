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

void print_sentences(story s)
{
	int i = 0;
	for (i = 0; i < s.lines; i++)
	{
		printf("%s", s.sentence[i]);
	}
	printf("\n");
}

int main()
{
	FILE *fp;
	char keywords[7][5] = { "like", "talk", "meet", "call", "gift", "text", "kind" };
	char filename[11] = "story0.txt"; //파일 이름 '0'부분은 뒤에서 수정
	char inputword[255];
	int random_keyword, i, j;
	int panel_num = 0, story_num = 0;
	int check_repeat[2] = { -1, -1 };
	panel* panels;
	story* stories;

	srand(time(NULL));
	printf("number of panels: ");
	scanf("%d", &panel_num);
	printf("number of stories: ");
	scanf("%d", &story_num);

	panels = (panel*)malloc(panel_num*sizeof panel);
	stories = (story*)malloc(panel_num*sizeof story);
	for (i = 0; i < panel_num; i++)
	{
		panels[i].id = i;
		for (j = 0; j < 3; j++)
		{
			while (true)
			{
				random_keyword = rand() % 7;
				if (j != 2)
					check_repeat[j] = random_keyword;

				if (check_repeat[j - 1] != random_keyword)
					break;
			}
			strcpy(panels[i].keyword[j], keywords[random_keyword]);
		}
	}

	for (i = 0; i < story_num; i++)
	{
		filename[5] = '1' + i;
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

	for (i = 0; i < story_num; i++)
	{
		printf("Story %d\n", i + 1);
		print_sentences(stories[i]);
		for (j = 0; j < panel_num; j++)
		{
			printf("panel %d: ", j + 1);
			if (is_greenlight(panels[j], stories[i]))
				printf("ON\n");
			else
				printf("OFF\n");
		}
	}
	return 0;
}