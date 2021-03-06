/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phi_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 08:32:42 by alidy             #+#    #+#             */
/*   Updated: 2021/05/24 14:52:06 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	philo_end(t_ph *ph, pid_t *pid)
{
	int	i;
	int	check;
	int	status;

	i = 0;
	status = 0;
	check = 0;
	while (i < ph->nb)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			check = 1;
			break ;
		}
		i++;
	}
	i = 0;
	while (i < ph->nb && check)
	{
		kill(pid[i], SIGTERM);
		i++;
	}
	free(pid);
}

int	test_args(int argc, char **argv)
{
	int	i;
	int	y;

	i = 1;
	y = 0;
	if (argc != 5 && argc != 6)
	{
		printf("Bad args\n");
		return (0);
	}
	while (i < argc)
	{
		while (argv[i][y])
		{
			if (!(argv[i][y] >= '0' && argv[i][y] <= '9'))
			{
				printf("Bad args\n");
				return (0);
			}
			++y;
		}
		y = 0;
		++i;
	}
	return (1);
}

int	init_sem(t_ph *ph)
{
	sem_unlink("/is_dead");
	sem_unlink("/speak");
	sem_unlink("/id");
	sem_unlink("/fork");
	ph->is_dead = sem_open("/is_dead", O_CREAT | O_EXCL, S_IRWXU, 1);
	ph->speak = sem_open("/speak", O_CREAT | O_EXCL, S_IRWXU, 1);
	ph->id = sem_open("/id", O_CREAT | O_EXCL, S_IRWXU, 1);
	ph->fork = sem_open("/fork", O_CREAT | O_EXCL, S_IRWXU, ph->nb);
	return (1);
}

int	init_ph(t_ph *ph, int argc, char **argv)
{
	if (!test_args(argc, argv))
		return (0);
	if (argc == 6)
	{
		ph->must_eat = ft_atoi(argv[5]);
		if (ph->must_eat < 1)
			return (0);
	}
	else
		ph->must_eat = -1;
	ph->nb = ft_atoi(argv[1]);
	ph->t_die = ft_atoi(argv[2]);
	ph->t_eat = ft_atoi(argv[3]);
	ph->t_sleep = ft_atoi(argv[4]);
	ph->nb_fork = ph->nb;
	if (!init_sem(ph))
		return (0);
	return (1);
}
