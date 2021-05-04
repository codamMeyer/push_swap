#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;

	while (*lst != NULL)
	{
		temp = *lst;
		*lst = temp->next;
		ft_lstdelone(temp, del);
	}
	*lst = NULL;
}
