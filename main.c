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
	return ((struct data*)(char*)(pos) - (unsigned long)(&((struct data*)0)->list));
}

struct data	*new_elem(void)
{
	struct data	*rslt;

	rslt = (struct data*)malloc(sizeof(struct data));
	if (!rslt)
	{
		write(2, "malloc erro\n", 12);
		exit(1);
	}
	rslt->list.next = NULL;
	rslt->a = rand();
	write(1, "new item\n", 9);
	return (rslt);
}

void	add_tail(struct data *head)
{
	struct data	*last;
	struct list	*temp;

	temp = head->list.next;
	if (!temp)
	{
		head->list.next = &(new_elem()->list);
		return ;
	}
	while (temp->next)
		temp = temp->next;
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
		printf("%d : %d\n", i, tmp->a);
		tmp = give_data(tmp->list.next);
		printf("next data ok\n");
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
	while (i < 100)
	{
		add_tail(head);
		i++;
	}
	list_read(head);
	return (0);
}
