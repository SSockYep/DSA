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

//�г��� �� �翬�� ���� �Ǵ�
//�׸�����Ʈ�� 1, �ƴϸ� 0 return
int is_greenlight(panel p, story s)
{
	int i, j, check[3] = { 0, 0, 0 };
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 3; j++)
		{
			//�翬�� �г��� �����ϴ� keyword�� �ִ��� üũ
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

//����ü story�� �ִ� ������ ����ϴ� �Լ�
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
	char filename[11] = "story0.txt"; //���� �̸�, '0'�κ��� �ڿ��� ����
	char inputword[255]; //���Ͽ��� ���� ������ �ӽ÷� ����
	int random_keyword, i, j; //random_keyword: keywords�߿��� �����ϰ� �̱� ����. i,j: for for loop
	int panel_num = 0, story_num = 0;
	int check_repeat[2] = { -1, -1 }; //keyword���� �ߺ� Ȯ�ο�
	panel* panels;
	story* stories;

	srand(time(NULL));
	printf("number of panels: ");
	scanf("%d", &panel_num);
	printf("number of stories: ");
	scanf("%d", &story_num);

	panels = (panel*)malloc(panel_num*sizeof panel);
	stories = (story*)malloc(panel_num*sizeof story);

	//panel�� ������ �ܾ �����ϰ� ����
	for (i = 0; i < panel_num; i++)
	{
		panels[i].id = i;
		for (j = 0; j < 3; j++)
		{
			//�ߺ��� �ƴ� ������ ��� �ݺ��Ͽ�
			//�����ϰ� �ܾ� ����
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

	//story���� stories�� ����
	for (i = 0; i < story_num; i++)
	{
		filename[5] = '1' + i; //filename[5]�� '0'�κ�
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

	//�׸�����Ʈ ���� Ȯ�� �� �׿� ���缭 ���
	for (i = 0; i < story_num; i++)
	{
		printf("Story %d\n", i + 1);
		print_sentences(stories[i]);
		for (j = 0; j < panel_num; j++)
		{
			printf("panel %d: ", j + 1);
			if (is_greenlight(panels[j], stories[i]) == 1)
				printf("ON\n");
			else
				printf("OFF\n");
		}
	}
	return 0;
}