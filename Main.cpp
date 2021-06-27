#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#pragma comment(linker, "/STACK:16777216")
typedef struct variables
{
	char v[200][100];
	int line[200];
	int find[200][100];
	int cur2;
	int cur_f;
	int pretb;
};
typedef struct functions
{
	char f[100][100];
	int line[100];
	char links[100][100];
	int cur;
	int cur_link;
	
};

int equal_v(char names[], char data[], int l, int i)
{
	int count = 0;
	for (int j = i; j - i < l; ++j)
	{
		if (data[j] == names[j - i])
		{
			count++;
		}
	}
	if (count == l && data[count + i] == ' ')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void clean(char a[])
{
	for (int i = 0; i < strlen(a); ++i)
	{
		a[i] = '\0';
	}
}
//проверка 
int h_control(char d[], char s[])
{
	int j = 0;
	for (int i = 0; i < 10; ++i)
	{
		if (s[i] == d[i])
		{
			j++;
		}
	}
	if (j == 10)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}
int equal(char names[], char data[], int l, int i)
{
	int count = 0;
	for (int j = i; j < l; ++j)
	{
		if (data[j] == names[j - i])
		{
			count++;
		}
	}
	if (count == l)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int find_cycle(char data[][300],int count)
{
	int i = 0;
	int j;
	while (i < count)
	{
		j = 0;
		while (data[i][j] == '\t' || data[i][j] == ' ')
		{
			j++;

			if (data[i][j] == '{' && data[i-1][j]!='t')
			{
				return 1;
			}
		}
		++i;
	}
	return 0;
}
int var_in_brackets(int start, char data[][300], char n_u[][20], int n_c, char stack[][20], int stack_c, int f, variables* current2)
{
	int lin = start;
	if (f == 0)
	{
		while (data[lin][0] != '}')
		{
			lin++;
		}
	}
	else
	{
		while (data[lin][f] != '}')
		{
			lin++;
		}
	}
	int finish = lin;
	if (f == 2)
	{
		return finish;
	}
	for (int i = start; i < finish; ++i)
	{
		if (data[i][f + 1] == '{')
		{
			i = var_in_brackets(i, data, n_u, n_c, stack, stack_c, f + 1, current2);
		}
		for (int j = 0; j < current2->cur2; ++j)
		{
			if (current2->line[j] == i)
			{
				strncpy(stack[stack_c], current2->v[i], strlen(current2->v[i]));
				stack_c++;
			}
		}
		char line[1000];
		for (int i = 0; i < 1000; ++i)
		{
			line[i] = '\0';
		}
		strncpy(line, data[i], strlen(data[i]));
		for (int j = 0; j < strlen(line); ++j)
		{
			if (line[j] == '(' || line[j] == '!' || line[j] == ')' || line[j] == '*' || line[j] == '+' || line[j] == '/' || line[j] == '%' || line[j] == ',' || line[j] == ':' || line[j] == '&' || line[j] == '|' || line[j] == '\t' || line[j] == ';' || line[j] == '<' || line[j] == '>' || line[j] == '=' || line[j] == ']' || line[j] == '[')
			{
				line[i] = ' ';
			}
		}
		for (int p = 0; p < strlen(line); p++)
		{
			for (int k = 0; k < stack_c; k++)
			{
				if (equal_v(stack[k], line, strlen(stack[k]), p) && (p == 0 || line[p - 1] == ' '))
				{
					clean(stack[k]);
				}
			}
		}
	}
	return finish;
}
int var_find(char data[][300], variables* current2, functions* current, int count)
{
	int li = 0;
	char n_u[100][20];
	int n_c = 0;
	int t_end = 0;
	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			n_u[i][j] = '\0';
		}
	}
	// структуры
	while (li < count)
	{
		if (data[li][0] == 't' && data[li][1] == 'y' && data[li][2] == 'p' && data[li][3] == 'e' && data[li][4] == 'd')
		{
			int start = li + 1;
			while (data[li][0] != '}')
			{
				li++;
			}
			if (li > count)
			{
				return 0;
			}
			int finish = li;
			char stack[100][20];
			for (int i = 0; i < 100; ++i)
			{
				for (int j = 0; j < 20; ++j)
				{
					stack[i][j] = '\0';
				}
			}
			int stack_c = 0;
			for (int i = 0; i < current2->cur2; ++i)
			{
				if (current2->line[i] > start && current2->line[i] < finish)
				{
					strncpy(stack[stack_c], current2->v[i], strlen(current2->v[i]));
					stack_c++;
				}
			}
			int j = li;
			while (j < count)
			{
				char line[1000];
				for (int i = 0; i < 1000; ++i)
				{
					line[i] = '\0';
				}
				strncpy(line, data[j], strlen(data[j]));
				for (int i = 0; i < strlen(line); ++i)
				{
					if (line[i] == '(' || line[i] == '!' || line[i] == ')' || line[i] == '*' || line[i] == '+' || line[i] == '/' || line[i] == '%' || line[i] == ',' || line[i] == ':' || line[i] == '&' || line[i] == '|' || line[i] == '\t' || line[i] == ';' || line[i] == '<' || line[i] == '>' || line[i] == '=' || line[i] == ']' || line[i] == '[' || line[i] == '.')
					{
						line[i] = ' ';
					}
				}
				for (int p = 1; p < strlen(line); p++)
				{
					for (int k = 0; k < stack_c; k++)
					{
						if (equal_v(stack[k], line, strlen(stack[k]), p) && (p == 0 || line[p - 1] == ' '))
						{
							clean(stack[k]);
						}
					}
				}
				j++;
			}
			for (int i = 0; i < stack_c; ++i)
			{
				if (stack[i][0] != '\0')
				{
					strncpy(n_u[n_c], stack[i], strlen(stack[i]));
					n_c++;
				}
			}
			t_end = li;
		}
		li++;
	}
	li = t_end;
	while (li < count)
	{
		while (data[li][0] != '{')
		{
			if (li < count)
			{
				if (n_c == 0)
				{
					printf("неиспользованных переменных нет");
					printf("\n");
					return 0;
				}
				else
				{
					printf("Неиспльзованные переменные:");
					for (int k = 0; k < n_c; k++)
					{
						printf("%s", n_u[k]);
					}
					printf("\n");
					return 0;
				}
			}
			li++;
		}
		int start = li + 1;
		char stack[100][20];
		for (int i = 0; i < 100; ++i)
		{
			for (int j = 0; j < 20; ++j)
			{
				stack[i][j] = '\0';
			}
		}
		int stack_c = 0;
		int f = 0;
		li = var_in_brackets(start, data, n_u, n_c, stack, stack_c, f, current2);
	}
	if (n_c == 0)
	{
		printf("неиспользованных переменных нет");
		return 0;
	}
	else
	{
		printf("Неиспльзованные переменные:");
		for (int k = 0; k < n_c; k++)
		{
			printf("%s", n_u[k]);
		}
		printf("\n");
		return 0;
	}
}

int function_detector(char data[], char names[][100], functions* current, int li, int time)
{
	if (time)
	{
		for (int i = 0; i < current->cur; ++i)
		{
			if (li == current->line[i])
			{
				return 0;
			}
		}
	}
	//чекнуть все названия в строке
	for (int i = 0; i < strlen(data); ++i)
	{
		//сдедать искл для комментариев
		for (int j = 0; j < 30; ++j)
		{
			if (equal(names[j], data, strlen(names[j]), i) || time)
			{
				for (int p = i + 1; p < strlen(data); ++p)
				{
					if (p == strlen(data) - 1 && time)
					{
						return 0;
					}
					if (data[p] == '"')
					{
						while (data[p] != '"' && p < strlen(data))
						{
							++p;
						}
						++p;
					}
					if ((data[p] == '/' && data[p + 1] == '/') || data[p] == '/*')
					{
						return 0;
					}
					if (data[p] == '(')///доп усл на функцию --> ЭТО ФУНКЦИЯ
					{
						char function[100] = { '\0' };
						p--;
						while (data[p] != ' ' && data[p] != '(' && data[p] != '!' && data[p] != '*' && data[p] != '+' && data[p] != '/' && data[p] != '%' && data[p] != ',' && data[p] != ':' && data[p] != '&' && data[p] != '|' && data[p] != '{' && data[p] != '{' && p != -1 && data[p] != '\t')
						{
							p--;
						}
						p++;
						int k = p;
						while (data[p] != '(')
						{
							function[p - k] = data[p];
							p++;
						}
						if (time == 0)
						{
							strncpy(current->f[current->cur], function, strlen(function));
							current->line[current->cur] = li;
							current->cur++;
							return 0;
						}
						else
						{
							j = 30;
							for (int m = 0; m < current->cur; ++m)
							{
								if (strlen(function) == strlen(current->f[m]) && equal(function, current->f[m], strlen(function), 0))
								{
									for (int l = 0; l < current->cur; ++l)
									{
										if (li < current->line[l] || li>current->line[current->cur - 1])
										{
											if (li > current->line[current->cur - 1])
											{
												strncpy(current->links[current->cur_link], current->f[current->cur - 1], strlen(current->f[current->cur - 1]));
												strncpy(current->links[current->cur_link + 1], function, strlen(function));
												current->cur_link += 2;
												break;
											}
											else
											{
												strncpy(current->links[current->cur_link], current->f[l - 1], strlen(current->f[l - 1]));
												strncpy(current->links[current->cur_link + 1], function, strlen(function));
												current->cur_link += 2;
												break;
											}
										}
									}
								}
							}
						}
					}
				}

			}
		}
	}
}

int uslovie(char a[], int i, int* f) {
	if (a[i] == 'f' && a[i + 1] == 'o' && a[i + 2] == 'r' && (a[i + 3] == ' ' || a[i + 3] == '(') ||
		a[i] == 'w' && a[i + 1] == 'h' && a[i + 2] == 'i' && a[i + 3] == 'l' && a[i + 4] == 'e' ||
		a[i] == 'i' && a[i + 1] == 'f' && (a[i + 2] == ' ' || a[i + 2] == '('))
		return 1;
	if (a[i] == 's' && a[i + 1] == 't' && a[i + 2] == 'r' && a[i + 3] == 'u' && a[i + 4] == 'c' && a[i + 5] == 't' && (a[i + 6] == ' ' || a[i + 6] == '\n'))
		return 5 ;
	if (a[i] == 's' && a[i + 1] == 'w' && a[i + 2] == 'i' && a[i + 3] == 't' && a[i + 4] == 'c')
		return 6;
	if (a[i] == 'c' && a[i + 1] == 'a' && a[i + 2] == 's' && a[i + 3] == 'e')
		return 7;
	if (a[i] == 'b' && a[i + 1] == 'r' && a[i + 2] == 'e' && a[i + 3] == 'a')
		return 8;
	return *f;
}

int forma(char data[][300], char data2[][300], int count)
{
	int ministack1 = 0, ministack2 = 0,n=0, ministack3 = 0, ministack4[100],temp=0, o = 0,p=0, ftype = 0, fswitch = 0, posswitch = 0, fdef = 0, i1 = 0, j1 = 0, i = 0, j = 0, f1 = 0, f2 = 0, flag = 0, lvl = 0, f = 0, FC = 0; //flag=1 - '#' ;
	for (int z = 0; z < count; z++)
	{
		if (data[i][j] == -52 && j==0)
		{
			i++;
			z++;
		}
		if (z == 465)
			int t = 0;
			//return 1;
		for (j = 0; j < strlen(data[i]);)
		{
			if (f2 == 0)
				while (data[i][j] == '\t' || data[i][j] == ' ')
				{
					j++;
					f2 = 1;
				}
			if (f1 == 1)
				if (data[i][j] == '\n')
					j++;
				else
					if (data[i][j] != '#')
					{
						data2[i1][0] = '\n';
						data2[i1][1] = '\0';
						i1++;
						f2 = 0;
						f1 = 0;
					}
					else
						f1 = 0;
			if (data[i][j] == '/' && data[i][j + 1] == '*' && data[i][j+2] != '\'')
			{
				ministack3++;
				FC = 1;
				data[i][j + 1] = '/';
				//i = i + 2;
			}
			while (data[i][j] == '*' && data[i][j + 1] == '/' && data[i][j + 2] != '\'')
			{
				ministack3--;
				j = j + 2;
				if (ministack3 == 0)
				{
					FC = 0;
					data2[i1][j1] = '\n';
					j1++;
					data2[i1][j1] = '\0';
					j1 = 0;
					i1++;
				}
			}
			if (data[i][j] == '}' && data[i][j - 1] != '\'' && FC==0)
			{
				ministack2 = ministack4[o - 1];
				o = o - 1;
				if (fswitch == 1 && o - 1 == posswitch)
				{
					fswitch = 0;
					posswitch = 0;
				}
			}
			if (j1 == 0 && data[i][j] != '\n')
			{
				while (data[i][j] == '\t' || data[i][j] == ' ')
					j++;
				if (f == 1 && data[i][j] != '{' && data[i][j - 1] != '\'')
				{
					ministack2++;
					f = 2;
				}
				else
					f = 0;
				int w = 0;
				for (j1 = 0; w < ministack2; w++)
				{
					data2[i1][j1] = ' ';
					data2[i1][j1 + 1] = ' ';
					data2[i1][j1 + 2] = ' ';
					data2[i1][j1 + 3] = ' ';
					j1 = j1 + 4;
					f2 = 1;
				}
				if (data[i][j] == '/')
					int r = 0;
				else
					if (FC == 1)
					{
						data2[i1][j1] = '/';
						data2[i1][j1 + 1] = '/';
						j1 = j1 + 2;
						f2 = 1;
					}
			}
			if (data[i][j] == '#' && data[i][j-1]!='"' && data[i][j + 1] != '\'')
			{
				if (data[i][j + 1] == 'd' || data[i][j + 1] == 'p')
					fdef = 1;
				flag = 1;
				data2[i1][j1] = data[i][j];
				f2 = 1;
				j1++;
				j++;
			}
			else
				if (data[i][j] == 'e' && data[i][j + 1] == 'l' && data[i][j + 2] == 's' && data[i][j + 3] == 'e' && FC == 0)
				{
					f = 1;
					for (int w = 0; w < 4; w++)
					{
						data2[i1][j1] = data[i][j];
						f2 = 1;
						j++;
						j1++;
					}
					data2[i1][j1] = '\n';
					j1++;
					data2[i1][j1] = '\0';
					j1 = 0;
					i1++;
					f2 = 0;
				}
				else
					if (data[i][j] == '(' && data[i][j - 1] != '\'' )
					{
						ministack1++;
						data2[i1][j1] = data[i][j];
						f2 = 1;
						j++;
						j1++;
					}
					else
						if (FC == 0 && ((data[i][j] == '>' && flag == 1) || (data[i][j] == '"' && flag == 1) || (data[i][j] == ';' && ministack1 == 0) || (data[i][j] == '{' && data[i][j + 1] != '\'') || (data[i][j] == '}' && data[i][j + 1] != '\'')))
						{
							if (data[i][j] == '}' && o == 0)
							{
								if (o == 0)
									if (ftype == 0)
									{
										data2[i1][j1] = data[i][j];
										j++;
										j1++;
										data2[i1][j1] = '\n';
										data2[i1][j1 + 1] = '\0';
										i1++;
										j1 = 0;
										data2[i1][j1] = '\n';
										data2[i1][j1 + 1] = '\0';
										i1++;
										j1 = 0;
										f2 = 0;
									}
									else
									{
										while (data[i][j] != ';')
										{
											data2[i1][j1] = data[i][j];
											j++;
											j1++;
										}
										data2[i1][j1] = data[i][j];
										j++;
										j1++;
										ftype = 0;
										data2[i1][j1] = '\n';
										j1++;
										data2[i1][j1] = '\0';
										j1 = 0;
										i1++;
										data2[i1][j1] = '\n';
										j1++;
										data2[i1][j1] = '\0';
										j1 = 0;
										i1++;
										f2 = 0;
									}
							}
							else
							{
								if (data[i][j] == '>' || data[i][j] == '"')
								{
									f1 = 1;
									if (flag == 1)
										if (n == 0)
											n++;
										else
											n = 0;
								}
									if (data[i][j] == '{')
									{
										if (ftype == 1 && o == 0)
										{
											data2[i1][j1] = '\n';
											j1++;
											data2[i1][j1] = '\0';
											j1 = 0;
											i1++;
											f2 = 0;
											ministack4[o] = ministack2;
											o++;
											ministack2++;
										}
										else
										{
											ministack4[o] = ministack2;
											o++;
											ministack2++;
										}
									}
									if (f == 2)
										ministack2--;
									flag = 0;
									data2[i1][j1] = data[i][j];
									j++;
									j1++;
									if (n == 1 && data[i][j - 1] == '"')
										f1 = 0;
									else
									{
										data2[i1][j1] = '\n';
										j1++;
										data2[i1][j1] = '\0';
										j1 = 0;
										i1++;
										f2 = 0;
									}
							}
						}
						else
							if (data[i][j] == ')' && j + 1 <= strlen(data[i]) && data[i][j + 1] != '\'')
							{
								data2[i1][j1] = data[i][j];
								f2 = 1;
								j++;
								j1++;
								ministack1--;
								if ((data[i][j] == '{' && ministack1 == 0) || (data[i][j] == '{' && ftype == 1))
								{
									data2[i1][j1] = '\n';
									j1++;
									data2[i1][j1] = '\0';
									j1 = 0;
									i1++;
									data2[i1][j1] = data[i][j];
									j++;
									j1++;
									data2[i1][j1] = '\n';
									j1++;
									data2[i1][j1] = '\0';
									j1 = 0;
									i1++;
									ministack4[o] = ministack2;
									o++;
									ministack2++;
									f2 = 0;
								}
								else
									if (ministack1 == 0 && data[i][j] != '{' && data[i][j] != ';' && data[i][j]!=' ' && data[i][j]!=']' && data[i][j] != '"')
									{
										data2[i1][j1] = '\n';
										j1++;
										data2[i1][j1] = '\0';
										j1 = 0;
										i1++;
										f2 = 0;
									}
							}
							else
								if ((data[i][j] == '\n' || data[i][j] == '\0') && FC == 0 && fdef != 2) //&& j!=0
								{
									f2 = 0;
									j++;
								}
								else
								{
									if ((fdef == 1 || fdef == 2) && (data[i][j] == ' ' || data[i][j] == '\n'))
									{
										if (fdef == 1)
										{
											data2[i1][j1] = data[i][j];
											j1++;
										}
										j++;
										fdef++;
										if (fdef == 3)
										{
											data2[i1][j1] = '\n';
											j1++;
											data2[i1][j1] = '\0';
											j1 = 0;
											i1++;
											f2 = 0;
											fdef = 0;
										}
									}
									else
									{
										f = uslovie(data[i], j, &f);
										if (f == 8 || f == 7)
											p = 1;
										if (temp == 1 && f != 7)
											temp = 0;
										if (f == 5)
										{
											f = 0;
											ftype = 1;
										}
										if (f == 6)
										{
											f = 0;
											fswitch = 1;
											posswitch = o;
										}
										if (p == 1)
										{
											if (f == 8)
											{
												ministack2--;
												f = 0;
												p = 0;
											}
											if (f == 7)
											{
												if (temp == 1)
												{
													j1 = j1 - 4;
													ministack2--;
												}
												p = 0;
												f = 0;
											}
										}
										if (fswitch == 1 && data[i][j] == ':')
										{
											p = 1;
											temp = 1;
										}
										data2[i1][j1] = data[i][j];
										f2 = 1;
										j1++;
										if (p == 1)
										{
											data2[i1][j1] = '\n';
											j1++;
											data2[i1][j1] = '\0';
											j1 = 0;
											i1++;
											ministack2++;
											p = 0;
											f2 = 0;
										}
										if (data[i][j] == '\n')
										{
											data2[i1][j1] = '\0';
											j1 = 0;
											i1++;
											f2 = 0;
										}
										j++;
									}
								}
		}
		i++;
		j = 0;
	}
	return i1;
}

int variables_detector(char data[], char names[][100], functions* current, variables* current2, int li, int time)
{

	for (int i = 0; i < current->cur; ++i)
	{
		if (li == current->line[i])
		{
			return 0;
		}
	}
	for (int i = 0; i < current2->cur2; ++i)
	{
		if (li == current2->line[i])
		{
			return 0;
		}
	}
	for (int i = 0; i < strlen(data); ++i)
	{
		//сделать искл для комментариев
		int x = 0;
		for (int j = 0; j < 30; ++j)
		{
			if (equal_v(names[j], data, strlen(names[j]), i) || time)
			{
				for (int p = i + 1; p < strlen(data); ++p)
				{
					if (p == strlen(data) - 1 && time)
					{
						return 0;
					}
					char variable[100] = { '\0' };
					if (data[p] == '=')
					{
						p -= 2;
						while (data[p] != ' ')
						{
							p--;
						}
						p++;
						int k = p;
						while (data[p] != ' ')
						{
							variable[p - k] = data[p];
							p++;
						}
						if (time == 0)
						{
							strncpy(current2->v[current2->cur2], variable, strlen(variable));
							current2->line[current2->cur2] = li;
							current2->cur2++;
							return x;
						}

					}
					if (data[p] == ';')
					{
						p -= 1;
						while (data[p] != ' ')
						{
							p--;
						}
						p++;
						int k = p;
						while (data[p] != ';')
						{
							variable[p - k] = data[p];
							p++;
						}
						if (time == 0)
						{
							strncpy(current2->v[current2->cur2], variable, strlen(variable));
							current2->line[current2->cur2] = li;
							current2->cur2++;
							x = 1;
							return x;
						}
					}
				}
			}
		}
	}
}

void function_using(functions* current)
{
	for (int i = 0;i < current->cur;++i)
	{
		for (int j = 0; j < current->cur_link;j++)
		{
			if (strlen(current->f[i]) == strlen(current->links[j]) && equal(current->f[i], current->links[j], strlen(current->f[i]), 0))
			{
				clean(current->f[i]);
				break;
			}
		}
	}
	int k = 0;
	char not_use[100][100] = { {'\0'} };
	for (int i = 0;i < current->cur;++i)
	{
		if (strlen(current->f[i]) != 0)
		{
			strncpy(not_use[k], current->f[i], strlen(current->f[i]));
			k++;
		}
	}
	if (k)
	{
		printf("В программе есть неиспользованные функции:");
		for (int i = 0; i < k;++i)
		{
			printf("%s ",not_use[i]);
		}
		printf("\n");
	}
	else 
	{
		printf("В программе нет неиспользованных функций\n");
	}
}
/*void copy(char a[],char b[]) // из а в б
{
	int p = 0;
	while (a[p] != '\0')
	{
		char x = a[p];
		b[p] = x;
		++p;
	}
}*/

int check_if(char data[][300], int line, int tab)
{
	int j = 0, flag = 0;
	while (1)
	{
		line--;
		j = 0;
		while (data[line][j] == ' ' || data[line][j] == '\t')
			j++;
		if (data[line][j] == 'i' && data[line][j + 1] == 'f' && data[line][j + 2] == ' ' && j == tab - 4)
		{
			while (data[line][j] != ')')
			{
				if (data[line][j] == '<' || data[line][j] == '>' || data[line][j] == '=')
				{
					flag = 1;
					break;
				}
				j++;
			}
			break;
		}
	}
	return flag;
}

int looping(char data[][300], int line, int tab, int type)
{
	//func если в рекурсивной функции нет return произойдет зацикливание
	if (type == 1)
	{
		int j = tab + 4;
		char br[8] = { "return " };
		char t;
		int f_return = 0, flag = 0;
		line += 2;
		while (j > tab)
		{
			j = 0;
			while (data[line][j] == ' ' || data[line][j] == '\t')
			{
				j++;
			}
			f_return = 0;
			if (data[line][j] == '}' && j == tab)
			{
				if (flag == 0)
					return 1;
				else
					return 0;
			}
			for (int i = 0; i < 7; ++i)
			{
				if (br[i] == data[line][j + i])
					f_return++;
				else
				{
					f_return = 0;
					break;
				}
			}
			if (f_return == 7)
			{
				if (j == tab + 1 || j == tab + 4)
					flag = 1;
				else if (j == tab + 2 || j == tab + 8)
				{
					if (check_if(data, line, j)) //вызываем чек усл
						flag = 1;
					else
						flag = 0;
				}
			}
			line++;
		}
	}
	//while
	if (type == 2)
	{
		int flag = 0, j = tab, f_break = 0;
		char b[7] = { "break;" };
		while (data[line][j] != ')')
		{
			if (data[line][j] == '<' || data[line][j] == '>' || data[line][j] == '=')
				return 0;
			j++;
		}
		line += 2;
		while (j > tab)
		{
			j = 0;
			while (data[line][j] == ' ' || data[line][j] == '\t')
			{
				j++;
			}
			for (int i = 0; i < 6; ++i)
			{
				if (b[i] == data[line][j + i])
					f_break++;
				else
				{
					f_break = 0;
					break;
				}
			}
			if (f_break == 6)
			{
				if (check_if(data, line, j))
					return 0;
				else
					return 1;
			}
			line++;
		}
		return 1;
	}

}

/* int recursion(struct functions* current, char data[][100])
{
	int j = 0, k = 0;
	char recursion[100][100];
	int flag_loop = 0;
	while (strcmp(current->links[j], ""))
	{
		if (strcmp(current->links[j], current->links[j + 1]) == 0)
		{
			strcpy(recursion[k], current->links[j]);
			flag_loop += looping(data, current->line[j], 0, 1);
			k++;
		}
		j += 2;
	}
	if (k > 0)
	{
		printf("В программе есть рекурсивные функции: ");
		for (int i = 0; i < k; ++i)
		{
			printf("%s ", recursion[i]);
		}
		printf("\n");
	}
	else
	{
		printf("В программе нет рекурсивных функций.\n");
	}
	return flag_loop;
} */

void recursion(functions* current)
{
	int j = 0;
	int k = 0;
	char recursion[100][100];
	while (strcmp(current->links[j], ""))
	{
		if (strcmp(current->links[j], current->links[j + 1]) == 0)
		{
			strcpy(recursion[k], current->links[j]);
			//flag_loop += looping(data, current->line[j], 0, 1);
			k++;
		}
		j += 2;
	}
	if (k > 0)
	{
		printf("В программе есть рекурсивные функции: ");
		for (int i = 0; i < k; ++i)
		{
			printf("%s ", recursion[i]);
		}
		printf("\n");

	}
	else
	{
		printf("В программе нет рекурсивных функций.\n");
	}
}


int nested_loops(char data[][300], int count)
{
	int mx = 0, cur = 0, i = 0, j;
	int struct_brack = 0;
	int brackets[100] = { 0 };
	int count_brack = 0;
	int flag_loop = 0;
	while (i < count)
	{
		if (count_brack < 0)
			count_brack = 0;
		j = 0;
		while (data[i][j] == '\t' || data[i][j] == ' ')
			j++;
		if (data[i][j] == '{')
		{
			brackets[count_brack] = -1;
			count_brack++;
		}
		else if (data[i][j] == '}')
		{
			if (j == brackets[count_brack - 1])
			{
				if (cur > mx)
					mx = cur;
				cur -= 1;
			}
			count_brack--;
		}
		else if ((data[i][j] == 'f' && data[i][j + 1] == 'o' && data[i][j + 2] == 'r' && data[i][j + 3] == ' ') || (data[i][j] == 'w' && data[i][j + 1] == 'h' && data[i][j + 2] == 'i' && data[i][j + 3] == 'l' && data[i][j + 4] == 'e' && data[i][j + 5] == ' '))
		{
			if (data[i][j] == 'w')
				flag_loop += looping(data, i, j, 2);
			i++;
			if (data[i][j] != '{')
			{
				if (cur + 1 > mx)
					mx = cur;
			}
			else
			{
				brackets[count_brack] = j;
				count_brack++;
				cur++;
				if (cur > mx)
					mx = cur;
			}
		}
		i++;
	}
	printf("Максимальная вложенность циклов в коде равна %d\n", mx);
	return flag_loop;
}


void check_looping(int flag)
{
	if (flag > 0)
		printf("Программа зацикливается\n");
	else
		printf("Программа не зацикливается\n");
}

void standard(functions* current, variables* current2)
{
	printf("Неправильные названия функций:");
	for (int i = 0; i < current->cur; ++i)
	{
		for (int j = 0; j < strlen(current->f[i]); ++j)
		{
			if (j == 0)
			{
				if (current->f[i][j] < 'A' || current->f[i][j]>'Z')
				{
					printf("%s ", current->f[i]);
					break;
				}
			}
			if (current->f[i][j] == '_')
			{
				if (current->f[i][j + 1] < 'A' || current->f[i][j + 1]>'Z')
				{
					printf("%s ", current->f[i]);
					break;
				}
			}
		}
	}
	printf("\n");
	printf("Неправильные названия переменных: ");
	for (int i = 0; i < current2->cur2; ++i)
	{
		for (int j = 0; j < strlen(current2->v[i]); ++j)
		{
			if (j == 0)
			{
				if (current2->v[i][j] < 'a' || current2->v[i][j]>'z')
				{
					printf("%s ", current->f[i]);
					break;
				}
			}
			if (current2->v[i][j] == '_')
			{
				printf("%s ", current2->v[i]);
				break;
			}
			if (current2->v[i][j] == '-')
			{
				printf("%s ", current2->v[i]);
				break;
			}
			if (current2->v[i][j] == ' ')
			{
				printf("%s ", current2->v[i]);
				break;
			}
		}
	}
	printf("\n");
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int h_line = 0;
	int i = 0;
	char path[100] = { '\0' };
	char path_txt[100] = { '\0' };
	fgets(path, 1000, stdin);
	path[strlen(path) - 1] = '\0';
	strncpy(path_txt, path, strlen(path));
	path_txt[strlen(path_txt) - 1] = 't';
	path_txt[strlen(path_txt) - 2] = 'x';
	path_txt[strlen(path_txt) - 3] = 't';
	char s[] = "#include ";
	s[strlen(s)] = '"';
	char data[1600][300], data2[1600][300];
	if (-1 == rename(path, path_txt))
	{
		perror("Error");
	}
	FILE* inp = fopen(path_txt, "r+");

	while (!feof(inp))
	{
		fgets(data[i], 800, inp);
		//data[i][strlen(data[i]) - 1] = '\0';
		if (h_control(data[i], s))
		{
			int j;
			char path_h[100] = { '\0' };
			char path_new[100] = { '\0' };
			char path_h_txt[100] = { '\0' };
			strncpy(path_h, path, strlen(path));
			strncpy(path_h_txt, path, strlen(path));
			char h[100] = { '\0' };
			char h_txt[100] = { '\0' };
			j = 10;
			while (data[i][j] != 34)
			{
				h[j - 10] = data[i][j];
				h_txt[j - 10] = data[i][j];
				j++;
			}
			h_txt[strlen(h) + 1] = 't';
			h_txt[strlen(h)] = 'x';
			h_txt[strlen(h) - 1] = 't';
			j = strlen(path_h) - 1;
			while (path_h[j] != '\\')
			{
				path_h[j] = '\0';
				path_h_txt[j] = '\0';
				j--;
			}
			for (int i = j + 1; i < j + (strlen(h)) + 1; ++i)
			{
				path_h[i] = h[i - j - 1];
				path_h_txt[i] = h[i - j - 1];
			}
			int x = strlen(path_h_txt);
			path_h_txt[x + 1] = 't';
			path_h_txt[x] = 'x';
			path_h_txt[x - 1] = 't';
			if (-1 == rename(path_h, path_h_txt))
			{
				perror("Error");
			}
			FILE* inp_h = fopen(path_h_txt, "r+");
			while (!(feof(inp_h)))
			{
				++i;
				fgets(data[i], 10000, inp_h);
				//data[i][strlen(data[i]) - 1] = '\0';
			}
			fclose(inp_h);
			rename(path_h_txt, path_h);
			h_line = i+1;
		}
		i++;
	}
	fclose(inp);
	rename(path_txt, path);
	int count = i;
	count=forma(data, data2, count);
	int g = find_cycle(data2, h_line);
	if (g)
	{
		printf("Есть циклы во вложенных файлах");
	}
	else
	{
		printf("Нет циклов во вложенных файлах");
	}
	char names[100][100] = { {"char"}, {"signed char"}, {"unsigned char"},{"short"}, {"short int"}, {"signed short"},{"signed short int"}, {"unsigned short"}, {"unsigned short int"},{"int"}, {"signed"}, {"signed int"},{"unsigned"}, {"unsigned int"}, {"long"},{"long int"}, {"signed long"}, {"signed long int"},{"unsigned long"}, {"unsigned long int"}, {"long long"},{"long long int"}, {"signed long long"}, {"signed long long int"},{"unsigned long long"}, {"unsigned long long int"}, {"float"},{"double"}, {"long double"}, {"void"} };
	struct functions* current = (functions*)malloc(sizeof(functions));
	current->cur = 0;
	current->cur_link = 0;
	for (int i = 0; i < 100; ++i)
	{
		current->line[i] = 0;
		for (int j = 0; j < 100; ++j)
		{
			current->f[i][j] = '\0';
			current->links[i][j] = '\0';
		}
	}
	for (int i = 0; i < count; i++)
	{
		function_detector(data2[i], names, current, i, 0);
	}
	for (int i = 0; i < count; i++)
	{
		function_detector(data2[i], names, current, i, 1);
	}
	struct variables* current2 = (variables*)malloc(sizeof(variables));
	current2->cur2 = 0;
	current2->cur_f = 0;
	for (int i = 0; i < 1000; ++i)
	{
		current2->line[i] = 0;
		for (int j = 0; j < 100; ++j)
		{
			current2->v[i][j] = '\0';
		}
	}
	int p = 0;
	for (int i = 0; i < count; i++)
	{
		if (variables_detector(data2[i], names, current, current2, i, 0))
		{
			p = 1;
		}
	}
	if (p == 1)
	{
		printf("\nНе все переменные получают начальные значения\n");
	}
	else
	{
		printf("Все переменные получают начальные значения\n");
	}
	for (int i = 0; i < current2->cur2;i++)
	{
		g = 0;
		for (int j = 0;j < strlen(current2->v[i]); ++j)
		{
			if (g == 1)
			{
				current2->v[i][j] = '\0';
			}
			else
			{
				if (current2->v[i][j] == '[')
				{
					g = 1;
					current2->v[i][j] = '\0';
				}
			}
		}
	}
	int f;
	standard(current, current2);
	var_find(data2, current2, current, count);
	function_using(current);
	recursion(current);
	int flag_loop = nested_loops(data2, count);
	check_looping(flag_loop);
	//recursion(current, data2);
	//nested_loops(data2, count);
	FILE* fw = fopen("inf.txt", "w");
	char r[20] = "(recursive)";
	int iskl[100];
	int iskl_c = 0;
	for (int i = 0; i < current->cur_link; i++)
	{
		if (i % 2 == 0)
		{
			if (equal(current->links[i], current->links[i+1],strlen(current->links[i]),0) && strlen(current->links[i])==strlen(current->links[i+1]))
			{
				int y = strlen(current->links[i]);
				for (int p = 0;p < current->cur_link;++p)
				{
					if (i!=p && (equal(current->links[i], current->links[p], strlen(current->links[p]), 0) && strlen(current->links[p]) == strlen(current->links[i])))
					{
						for (int j = strlen(current->links[p]); j < strlen(current->links[i]) + strlen(r); ++j)
						{
							current->links[p][j] = r[j - y];
						}
					}
				}
				p = i;
				for (int j = strlen(current->links[p]); j < strlen(current->links[i]) + strlen(r); ++j)
				{
					current->links[p][j] = r[j - y];
				}
				iskl[iskl_c] = i;
				iskl_c++;
				iskl[iskl_c] = i+1;
				iskl_c++;
			}
		}
	}
	for (int i = 0; i < current->cur_link; i++)
	{
		int z = 1;
		for (int j = 0; j < iskl_c;++j)
		{
			if (i == iskl[j])
			{
				z = 0;
			}
		}
		if (z)
		{
			fprintf(fw, "%s\n", current->links[i]);
		}
	}
	int op = 0;
	int man = 0;
	fclose(fw);
	char pathnew[100] = { '\0' };
	FILE* fe = fopen("14.txt", "w");
	FILE* fq = fopen (path_txt, "w");
	for (int w = 0; w < count;w++)
	{
		if (data2[w][strlen(data2[w]) - 5] == '.' && data2[w][strlen(data2[w]) - 4] == 'h' && data2[w][strlen(data2[w]) - 3] == '"' && data2[w][strlen(data2[w]) - 2] == ';')
		{
			fputs(data2[w], fq);
			int er = 0;
			for (int qw = 10; qw < strlen(data2[w]) - 3; qw++)
			{
				pathnew[er] = data2[w][qw];
				er++;
			}
			pathnew[er] = '\0';
			if (op == 0)
			{
				//fclose(fe);
			//	fe = fopen(pathnew, "w");
				//fe = fopen("12.txt", "w");
				op = 1;
				man = 0;
			}
			else
			{
				fclose(fe);
				//fopen(pathnew, "w");
				fe = fopen("13.txt", "w");
				man = 0;
			}
			w++;
		}
		if (data2[w][0] == 'i' && data2[w][4] == 'm' && data2[w][5] == 'a' && data2[w][6] == 'i')
		{
			if (op == 1)
			{
					op = 0;
			}
		}
		if (op == 0)
			fputs(data2[w], fq);
		else
			fputs(data2[w], fe);
	}
}
