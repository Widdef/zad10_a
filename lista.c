#include "lista.h"


void list_add_end(list **p, int value)
{
	list ** marker = p;
	list *new_el = (list*)malloc(sizeof(list));

	while (*marker)
	{
		marker = &(*marker)->next;
	}
	new_el->data = value;
	new_el->next = *p;
	*marker = new_el;
}

void list_add_start(list **p, int value)
{
	if (*p == NULL)
	{
		list *new_el = (list*)malloc(sizeof(list));
		new_el->data = value;
		new_el->next = new_el;
		*p = new_el;
	}
	else
	{
		list *head = *p;
		list *marker = *p;
		list *new_el = (list*)malloc(sizeof(list));
		new_el->data = value;
		new_el->next = *p;
		*p = new_el;
		while (marker->next != head)
		{
			marker = marker->next;
		}
		(*p)->next->next = new_el;
	}
}

void list_show(list *p)
{
	printf("\n\n");
	if (p != NULL)
	{
		list *head = p;
		do
		{
			printf("%d\n", p->data);
			p = p->next;
		} while (p->next != head);
	}
}
void list_show_from_back(list **p) // 1 do pokazania
{
	list **tmp, *first, *rest;
	tmp = p;
	if (tmp == NULL)
		return;
	first = *tmp;
	rest = (*tmp)->next;
	if (rest == NULL)
		return;
	list_reverse_rek(&rest);
	first->next->next = first;
	first->next = NULL;
	*tmp = rest;
	list_show(*tmp);
}

void list_delete_first(list **p)
{
	if (*p != NULL)
	{
		list *tmp = *p;
		*p = (*p)->next;
		free(tmp);
	}
}

void list_delete_last(list **p)
{
	if (*p != NULL)
	{
		list **marker = p;
		while ((*marker)->next->next)
		{
			marker = &(*marker)->next;
		}
		list *tmp = (*marker)->next;
		(*marker)->next = NULL;
		free(tmp);
	}
}

int list_find(list **p, int value)
{
	int flag = 0;
	int index = 0;
	list **marker = p;
	while (*marker != NULL)
	{
		index++;
		if ((*marker)->data == value)
		{
			flag = 1;
			break;
		}
		marker = &(*marker)->next;
	}
	if (flag)
	{
		printf("Element exist. Index: %d\n", index);
		return 1;
	}
	printf("Element not exist\n");
	return 0;
}

void list_find_add_after(list **p, int value, int find)
{
	int flag = 0;
	list **marker = p;
	while (*marker != NULL)
	{
		if ((*marker)->data == find)
		{
			flag = 1;
			break;
		}
		marker = &(*marker)->next;
	}
	if (flag == 1)
	{
		list *new_el = (list*)malloc(sizeof(list));
		new_el->data = value;
		new_el->next = (*marker)->next;
		(*marker)->next = new_el;
	}
	else
	{
		char dec;
		printf("Element not exist\n");
		do
		{
			printf("Do you want to create element as last element of the list? (Y/N)");
			scanf("%c", &dec);
		} while (dec != 'y' && dec != 'Y' && dec != 'n' && dec != 'N');
		if (dec == 'Y' || dec == 'y')
			list_add_end(p, value);
	}
}

void list_find_add_before(list **p, int value, int find)
{
	int flag = 0;
	list **marker = p;
	while (*marker != NULL)
	{
		if ((*marker)->next->data == find)
		{
			flag = 1;
			break;
		}
		marker = &(*marker)->next;
	}
	if (flag == 1)
	{
		list *new_el = (list*)malloc(sizeof(list));
		new_el->data = value;
		new_el->next = (*marker)->next;
		(*marker)->next = new_el;
	}
	else
	{
		char dec;
		printf("Element not exist\n");
		do
		{
			printf("Do you want to create element as first element of the list? (Y/N)\n");
			scanf("%c", &dec);
		} while (dec != 'y' && dec != 'Y' && dec != 'n' && dec != 'N');
		if (dec == 'Y' || dec == 'y')
			list_add_start(p, value);
	}
}

void list_find_delete(list **p, int find)
{
	int index = 0;
	list **marker = p;
	if ((*marker)->data == find)
	{
		list_delete_first(p);
		return;
	}
	while ((*marker)->next != NULL)
	{
		index++;
		if ((*marker)->next->data == find)
			break;
		marker = &(*marker)->next;
	}
	if ((*marker)->next != NULL)
	{
		list *tmp = (*marker)->next;
		(*marker)->next = (*marker)->next->next;
		free(tmp);
	}
	else
		list_delete_last(p);
}

int check_sting(char *str)
{
	int len = (int)strlen(str);
	if ((str[len - 3] == 't') && (str[len - 4] == '.') && (str[len - 2] == 'x') && (str[len - 1] == 't'))
		return 1;
	return 0;
}

void list_from_file(list **head)
{
	int value = 0;
	char file[256];
	FILE *fptr;
	do {
		printf_s("Podaj nazwe pliku: ");
		scanf("%s", &file);
		value = check_sting(file); //Sprawdza czy plik zostal podany z rozszerzeniem txt TAK - 1 NIE - 0 
		if (value)
		{
			fptr = fopen(file, "r");
			if (fptr == NULL) // Czy uda³o siê otworzyæ plik
			{
				printf("Blad otwarcia pliku.\n");
				system("PAUSE");
				fclose(fptr);
				break;
			}
			while (fscanf(fptr, "%d", &value) != EOF)
			{
				list_add_end(head, value);
			}
			printf("Udalo sie odczytac dane z pliku.\n");
			fclose(fptr);
			system("PAUSE");
			break;
		}
		printf("Podales zly format pliku.\n");
		system("PAUSE");
	} while (!value); // Pêtla nie zakonczy sie do momentu podania pliku z rozszerzeniem txt
}

void list_to_file(list *head)
{
	int value;
	char file[256];
	FILE *fptr;
	do {
		printf_s("Podaj nazwe pliku: ");
		scanf("%s", &file);
		value = check_sting(file); //Sprawdza czy plik zostal podany z rozszerzeniem txt TAK - 1 NIE - 0 
		if (value)
		{
			fptr = fopen(file, "w");
			if (fptr == NULL) // Czy uda³o siê otworzyæ plik
			{
				printf("Blad otwarcia pliku.\n");
				system("PAUSE");
				fclose(fptr);
				break;
			}
			while (head != NULL)
			{
				fprintf(fptr, "%d ", head->data);
				head = head->next;
			}
			printf("Udalo sie zapisac dane do pliku.\n");
			fclose(fptr);
			system("PAUSE");
			break;
		}
		printf("Podales zly format pliku.\n");
		system("PAUSE");
	} while (!value); // Pêtla nie zakonczy sie do momentu podania pliku z rozszerzeniem txt
}

void list_delete_all_found_not_rek(list **p, int value) // 2 zadanie
{
	while (list_find(p, value))
	{
		list_find_delete(p, value);
	}
}

void list_delete_all_found_rek(list **p, int value)  // 2 zadanie
{
	if (*p != NULL)
	{
		int deleted = 0;
		if ((*p)->data == value)
		{
			list *tmp = *p;
			*p = (*p)->next;
			free(tmp);
			deleted = 1;
		}
		if (deleted)
			list_delete_all_found_rek(p, value);
		else
			list_delete_all_found_rek(&(*p)->next, value);
	}
}

int list_count(list **p, int value)
{
	int count = 0;
	while (*p != NULL)
	{
		if ((*p)->data == value)
			count++;
		p = &(*p)->next;
	}
	return count;
}

int list_value_most_common(list **p) // 3 zadanie
{
	list **tmp = p;
	if (*tmp == NULL)
		return;
	int most_common;
	int count = 0;
	int count_pom;
	while (*tmp != NULL)
	{
		count_pom = list_count(&(*tmp)->next, (*tmp)->data);
		if (count < count_pom)
		{
			most_common = (*tmp)->data;
			count = count_pom;
		}
		(*tmp) = (*tmp)->next;
	}
	return most_common;
}

void list_delete_indivisible(list **p, int value) // 4 zadanie
{
	list **marker = p;
	while (*marker != NULL)
	{
		if ((*marker)->data % value != 0)
			list_delete_all_found_rek(marker, (*marker)->data);
		else
			marker = &(*marker)->next;
	}
}


void list_reverse(list **p) // 5 zadanie 
{
	list *prev = NULL;
	list *cur = *p;
	list *next;
	if (*p == NULL || (*p)->next == NULL)
		return;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*p = prev;
}

void list_reverse_rek(list **p) // 5 zadanie
{
	list *first, *rest;
	if (*p == NULL)
		return;
	first = *p;
	rest = (*p)->next;
	if (rest == NULL)
		return;
	list_reverse_rek(&rest);
	first->next->next = first;
	first->next = NULL;
	*p = rest;
}