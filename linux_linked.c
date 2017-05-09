#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

struct list
{
	struct list *next;
	struct list *prev;
};

struct data
{
	int a;
	struct list list;
};

struct data	*give_data(struct list *pos)
{
	if (!pos)
	{
		//printf("error for giving data cause pos is NULL\n");
		return (NULL);
	}
	return ((struct data*)((char*)(pos) - (unsigned long)(&((struct data*)0)->list)));
}

struct data	*new_elem(void)
{
	struct data	*rslt;

	rslt = malloc(sizeof(struct data));
	if (!rslt)
	{
		write(2, "malloc erro\n", 12);
		exit(1);
	}
	rslt->list.next = NULL;
	rslt->a = rand();
	//printf("new item with adress : %p and  a = %d\n", &rslt,  rslt->a);
	return (rslt);
}

void	add_tail(struct data *head)
{
	struct data	*last;
	struct list	*temp;

	temp = head->list.next;
	if (!temp)
	{
	//	printf("first tail\n");
		head->list.next = &(new_elem()->list);
		return ;
	}
	while (temp->next)
	{
	//	printf("next\n");
		temp = temp->next;
	}
	last = new_elem();
	temp->next = &(last->list);
}

void	list_read(struct data *head)
{
	struct data *tmp;
	int					i;

	i = 0;
	tmp = head;
	while (tmp)
	{
//		printf("%d : %d\n", i, tmp->a);
		tmp = give_data(tmp->list.next);
	//	printf("next data adress : %p\n", tmp);
		i++;
	}
}

int		main(void)
{
	int i;
	struct data *head;

	srand(time(NULL));
	head = new_elem();
	i = 0;
	while (i < 50000)
	{
		add_tail(head);
		i++;
	}
	list_read(head);
	printf("linux linked finish");
	return (0);
}
