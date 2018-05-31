#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _SL_NODE
{
	char pos[10];
	char name[50];
	int hp;
	int mp;
	int speed;

	_SL_NODE* pNext;
}SL_NODE;

typedef struct _TR_NODE
{
	char pos[10];
	char name[50];
	int hp;
	int mp;
	int speed;

	_TR_NODE* pLeft;
	_TR_NODE* pRight;
}TR_NODE;

void SortByName_SL(SL_NODE** head)
{
	SL_NODE* tmp, *tmp2;
	SL_NODE* New;
	FILE* fp;
	fp = fopen("LOLDic_100.txt", "r");
	if (fp != NULL)
	{
		fseek(fp, 0, 0);
		for (int i = 0; i < 100; i++)
		{
			tmp = *head;

			New = NULL;
			while (New == NULL)
				New = (SL_NODE*)malloc(sizeof(SL_NODE));
			fscanf(fp, "%s %s %d %d %d", New->pos, New->name, &New->hp, &New->mp, &New->speed);
			New->pNext = NULL;

			if (tmp == NULL)
			{
				*head = New;
				tmp = *head;
			}
			else
			{
				while (tmp->pNext != NULL&&strcmp(tmp->pNext->name, New->name) < 0)
				{
					tmp = tmp->pNext;
				}
				New->pNext = tmp->pNext;
				tmp->pNext = New;
			}
		}
		tmp = *head;
		tmp2 = *head;
		*head = tmp->pNext;
		while (tmp2->pNext != NULL&&strcmp(tmp2->pNext->name, tmp->name) < 0)
		{
			tmp2 = tmp2->pNext;
		}
		tmp->pNext = tmp2->pNext;
		tmp2->pNext = tmp;
	}
	fclose(fp);
}

void prDataSL(SL_NODE* head)
{
	SL_NODE* tmp;
	
	tmp = head;
	int a = 0;
	while (tmp != NULL)
	{
		printf("%d %s %s %d %d %d\n", ++a, tmp->pos, tmp->name, tmp->hp, tmp->mp, tmp->speed);
		tmp = tmp->pNext;
	}
}

void delSL(SL_NODE* head)
{
	SL_NODE* tmp, *del;
	tmp = head;
	while (tmp != NULL)
	{
		del = tmp;
		tmp = tmp->pNext;
		free(del);
	}
}

void node(TR_NODE* root, TR_NODE* New)
{
	int a = 0;
	a = strcmp(root->name, New->name);

	if (a < 0)
	{
		if (root->pRight == NULL)
		{
			root->pRight = New;
			return;
		}
		else
		{
			node(root->pRight, New);
		}
	}
	else if (a > 0)
	{
		if (root->pLeft == NULL)
		{
			root->pLeft = New;
			return;
		}
		else
		{
			node(root->pLeft, New);
		}
	}
	else if (a == 0)
	{
		printf("error");
		getchar();
		return;
	}

	
}

void DataToTree(TR_NODE** root)
{
	TR_NODE* New;
	FILE* fp;
	fp = fopen("LOLDic_100.txt", "r");
	if (fp != NULL)
	{
		fseek(fp, 0, 0);
		for (int i = 0; i < 100; i++)
		{
			New = NULL;
			while (New == NULL)
				New = (TR_NODE*)malloc(sizeof(TR_NODE));
			fscanf(fp, "%s %s %d %d %d", New->pos, New->name, &New->hp, &New->mp, &New->speed);
			New->pLeft = NULL;
			New->pRight = NULL;
			if (*root == NULL)
			{
				*root = New;
			}
			else
			{
				node(*root, New);
			}
		}
	}
}

void SearchInTree(TR_NODE* root, char* name)
{
	int a = 0;
	a = strcmp(root->name, name);

	if (a < 0)
	{
		if (root->pRight == NULL)
		{
			printf("없음");
			return;
		}
		else
		{
			SearchInTree(root->pRight, name);
		}
	}
	else if (a > 0)
	{
		if (root->pLeft == NULL)
		{
			printf("없음");
			return;
		}
		else
		{
			SearchInTree(root->pLeft, name);
		}
	}
	else if (a == 0)
	{
		printf("%s %s %d %d %d\n",root->pos, root->name, root->hp, root->mp, root->speed);
		return;
	}
}
void PrintAll(TR_NODE* root)
{
	if (root->pLeft != NULL)
	{
		PrintAll(root->pLeft);
	}
	printf("%s %s %d %d %d\n",root->pos, root->name, root->hp, root->mp, root->speed);
	if (root->pRight != NULL)
	{
		PrintAll(root->pRight);
	}
	return;
}

int DeleteInTree(TR_NODE* root, char* name)
{
	int a = 0;
	int check = 0;
	a = strcmp(root->name, name);
	
	if (a == 0)
	{
		if (root->pLeft == NULL && root->pLeft == NULL)
		{
			return 1;
		}
		else if (root->pLeft != NULL && root->pRight != NULL)
		{
			return 4;
		}
		else
		{
			if (root->pLeft == NULL)
			{
				return 3;
			}
			else
			{
				return 2;
			}
		}
	}
	else if (a < 0)
	{
		if (root->pRight == NULL)
		{
			return 0;
		}
		else
		{
			check = DeleteInTree(root->pRight, name);
			if (check == 1)
			{
				free(root->pRight);
				root->pRight = NULL;
			}
			else if (check == 2)
			{
				TR_NODE* tmp;
				tmp = root->pRight;
				root->pRight = tmp->pLeft;
				free(tmp);
			}
			else if (check == 3)
			{
				TR_NODE* tmp;
				tmp = root->pRight;
				root->pRight = tmp->pRight;
				free(tmp);
			}
			else if (check == 4)
			{
				TR_NODE* tmp,*tmp2;
				TR_NODE* delTmp;
				delTmp = root->pRight;
				tmp = root->pRight;
				tmp = tmp->pRight;
				tmp2 = tmp;
				if (tmp->pLeft != NULL)
				{
					while (tmp->pLeft->pLeft != NULL)
					{
						tmp2 = tmp;
						tmp = tmp->pLeft;
					}
				}
				else
				{
					root->pRight = tmp;
					tmp->pLeft = delTmp->pLeft;
					free(delTmp);
					return 0;
				}
				
				tmp->pLeft = delTmp->pLeft;
				tmp->pRight = delTmp->pRight;
				root->pRight = tmp;
				tmp2->pLeft = NULL;
				free(delTmp);
			}
			return 0;
		}
	}
	else
	{
		if (root->pLeft == NULL)
		{
			return 0;
		}
		else
		{
			check = DeleteInTree(root->pLeft, name);
			if (check == 1)
			{
				free(root->pLeft);
				root->pLeft = NULL;
			}
			else if (check == 2)
			{
				TR_NODE* tmp;
				tmp = root->pLeft;
				root->pLeft = tmp->pLeft;
				free(tmp);
			}
			else if (check == 3)
			{
				TR_NODE* tmp;
				tmp = root->pLeft;
				root->pLeft = tmp->pRight;
				free(tmp);
			}
			else if (check == 4)
			{
				TR_NODE* tmp, *tmp2;
				TR_NODE* delTmp;
				delTmp = root->pLeft;
				tmp = root->pLeft;
				tmp = tmp->pLeft;
				tmp2 = tmp;
				if (tmp->pRight != NULL)
				{
					while (tmp->pRight->pRight != NULL)
					{
						tmp2 = tmp;
						tmp = tmp->pRight;
					}
				}
				else
				{
					root->pLeft = tmp;
					tmp->pRight = delTmp->pRight;
					free(delTmp);
					return 0;
				}

				tmp->pLeft = delTmp->pLeft;
				tmp->pRight = delTmp->pRight;
				root->pLeft = tmp;
				tmp2->pRight = NULL;
				free(delTmp);
			}
			return 0;
		}
	}
}

int main()
{
	clock_t beforeSL;
	SL_NODE* Shead = NULL;
	TR_NODE* Troot = NULL;
	char name[30];

	/*beforeSL = clock();
	SortByName_SL(&Shead);
	prDataSL(Shead);
	printf("\nSort single : %f sec.", ((double)clock() - (double)beforeSL) / 1000);
	delSL(Shead);
	getchar();*/

	DataToTree(&Troot);

	scanf("%s", name);
	SearchInTree(Troot, name);

	PrintAll(Troot);

	scanf("%s", name);
	DeleteInTree(Troot, name);

	PrintAll(Troot);
	printf("!");
}