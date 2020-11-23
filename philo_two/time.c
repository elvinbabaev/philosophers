/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avallie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 20:11:40 by avallie           #+#    #+#             */
/*   Updated: 2020/11/23 20:11:43 by avallie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

long long int	get_time(struct timeval time_old, struct timeval time_new)
{
	return (((time_new.tv_sec * 1000) - (time_old.tv_sec * 1000)
	+ (time_new.tv_usec / 1000) - (time_old.tv_usec / 1000)));
}
