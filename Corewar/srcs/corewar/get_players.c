/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_players.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 17:59:06 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/27 12:56:46 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	is_player(t_vm *v, int live)
{
	int i;

	i = -1;
	while (++i < v->nplayer)
		if (live == v->p[i].nplayer)
		{
			if (DISPLAY && (v->verbose_param & FLAG_VERBOSE_LIVES))
				ft_printf("Player %d (%s) is said to be alive\n",
						i + 1, v->p[i].name);
			else if (v->display_mode == 2)
			{
				pthread_mutex_lock(&v->v->mutex);
				if (!(v->v->heal_flag[i] || v->v->credits_flag))
					heal(v->v, i);
				pthread_mutex_unlock(&v->v->mutex);
			}
			v->p[i].nblive++;
			v->p[i].last_live_cycle = v->ncycle;
			v->last_live_id = i;
		}
}

void	save_player(char *file, t_vm *v, int i, int num) // сохраняем игрока в структуры
{
	int	fd;
	int len;

	if ((fd = open(file, O_RDONLY)) != -1) // открываем его файл
	{
		read(fd, &(v->p[i].exec_magic), sizeof(int)); // читаем magic header
		read(fd, &(v->p[i].name), PROG_NAME_LENGTH); // читаем имя чемпиона
		lseek(fd, 8, SEEK_CUR); // пропускаем пропуск
		read(fd, &(v->p[i].comment), COMMENT_LENGTH); // читаем комментарий чемпиона
		lseek(fd, 4, SEEK_CUR); // пропускаем пропуск
		len = read(fd, &(v->p[i].code), CHAMP_MAX_SIZE); // читаем код чемпиона
		v->p[i].nplayer = num; // пишем номер чемпиона
		v->p[i].prog_len = len; // пишем длину кода чемпиона
		v->p[i].nblive = 0;
		v->p[i].last_live_cycle = 0;
	}
	else
		xerror("Error: cannot open file", -1); // иначе ошибка не смогли открыть файл
	close(fd); // закрыли файл
}

void	get_player_custom(char **argv, int i, t_vm *v) // функция кастомного считывания чемпиона (после флага -n)
{
	int num;
	int j;

	num = ft_atoi(argv[i + 1]); // считываем номер с помощью фещш
	j = 0;
	while (j < v->nplayer) // проходим по номерам игроков
		if (v->p[j++].nplayer == num)
			xerror("Error: player number already assigned", -1); // ошибка если такой номер уже есть
	if (is_valid_player(argv[i + 2])) // проверяем что игрок валиден
	{
		if (v->nplayer < MAX_PLAYERS) // если кол-во игроков не превышено
			save_player(argv[i + 2], v, v->nplayer, num); // сохраняем
		else
			xerror("Error: too many players", -1); // иначе ошибка - слишком много игроков
		v->nplayer++;
		v->nplayer_cust++;
	}
	else
		xerror("Error: invalid champion", -1); // иначе ошибка - не валидный чемпион
}

void	get_player(char **argv, int i, t_vm *v) // функция считывания чемпиона
{
	int j;
	int num;
	int doublon;

	doublon = 0;
	num = -v->nplayer - 1; // присваиваем первичный номер
	j = 0;
	while (j < v->nplayer) // проходим по номерам игроков
	{
		if (v->p[j++].nplayer == num) // проверяем есть ли чеспион с таким же номером
			doublon = 1; // есть двойник
		num -= doublon ? 1 : 0; // получаем номер игрока (в случае если у нас будет -n флаг нам нужно это сделать, чтобы не было двух игроков с одинаковыми номерами)
		doublon = 0;
	}
	if (is_valid_player(argv[i])) // проверяем валидный ли чемпион
	{
		if (v->nplayer < MAX_PLAYERS) // если номер игрока меньше чем максимальное кол-во игрокоа
			save_player(argv[i], v, v->nplayer, num); // сохраняем
		else
			xerror("Error: too many players", -1); // иначе ошибка (слишком много игроков)
		v->nplayer++;
	}
	else
		xerror("Error: invalid champion", -1); //  иначе ошибка (не валидный чемпион)
}
