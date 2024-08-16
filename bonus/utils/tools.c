/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechcha <abechcha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 11:19:10 by abechcha          #+#    #+#             */
/*   Updated: 2024/07/21 11:59:31 by abechcha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../cub.h"

// t_ray *lst_new(void)
// {
//     t_ray *p;
//     p = malloc(sizeof(t_ray));
//     if (!p)
//         error_message(NULL , 5);
//     p->wall_x = 0;
//     p->wall_y = 0;
//     p->next = NULL;
//     return p;
// }

// void lst_add_back(t_ray **head)
// {
//     t_ray *tmp;
//     tmp = *head;
//     if (!head || !(*head)){
//         *head = lst_new();
//         return ;
//     }
//     while(tmp->next)
//         tmp = tmp->next;
//     tmp->next = lst_new();
// }

// t_ray *lst_last(t_ray *head)
// {
//     t_ray *tmp;
//     tmp = head ;
//     while(tmp && tmp->next)
//         tmp = tmp->next;
//     return tmp;
// }
