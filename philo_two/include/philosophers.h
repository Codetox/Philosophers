/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alidy <alidy@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 17:45:44 by alidy             #+#    #+#             */
/*   Updated: 2021/05/22 14:15:07 by alidy            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# define EATING 1
# define SLEEPING 2
# define THINKING 3
# define FORK 4
# define DIED 5

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	int				state;
	struct timeval	last_eat;
}					t_philo;

typedef struct s_ph
{
	int				nb;
	int				t_sleep;
	int				t_eat;
	int				t_die;
	int				must_eat;
	int				is_dead;
	int				current;
	int				nb_fork;
	sem_t			*fork;
	sem_t			*speak;
	sem_t			*dead;
	sem_t			*id;
	sem_t			*check;
	long			time;
}					t_ph;

int					test_args(int argc, char **argv);
int					init_sem(t_ph *ph);
int					init_ph(t_ph *ph, int argc, char **argv);
void				free_ph(t_ph *ph);
int					ft_atoi(const char *str);
int					ft_strlen(char *str);
long				ft_timersub(struct timeval *s);
long				ft_time(struct timeval *s);
long				ft_timer(long time);
long				ft_have_time(struct timeval *s, int time);
int					phi_is_dead(t_ph *ph);
void				print_state(t_ph *ph, int id, int state);
t_philo				init_philo(t_ph *ph);
void				phi_my_sleep(t_ph *ph, int time);
void				phi_sleep(t_ph	*ph, t_philo *philo);

#endif
