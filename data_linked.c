#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

struct data
{
	int a;
};

struct list
{
	void	*data;
	struct list	*next;
};

struct list 	*new_elem()
{
	struct list	*rslt;
	struct data	*data;

	rslt = malloc(sizeof(struct list));
	if (!rslt)
	{
		printf("malloc error");
		exit(1);
	}
	rslt->data = malloc(sizeof(struct data));
	if (!rslt->data)
	{
		printf("malloc error");
		exit(1);
	}
	data = (void*)rslt->data;
	data->a = rand();
	return (rslt);
}

void	add_tail(struct list *head)
{
	struct list *temp;

	temp = head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_elem();
}

void	list_read(struct list *head)
{
	struct data *data;
	int i;

	i = 0;
	while(head)
	{
		data = (struct data*)head->data;
		printf("%d : %d\n", i, data->a);
		head = head->next;
		i++;
	}
}

int	main(void)
{
	struct list *head;
	int	i;

	i = 0;
	srand(time(NULL));
	head = new_elem();
	while (i < 50001)
	{
		add_tail(head);
		i++;
	}
	list_read(head);
	return (0);
} 
