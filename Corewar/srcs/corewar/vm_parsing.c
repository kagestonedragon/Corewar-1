/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bduron <bduron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 15:09:59 by bduron            #+#    #+#             */
/*   Updated: 2017/04/27 14:46:39 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_help(void) // выводим функционал, если кол-во игроков равно нулю
{
	ft_printf("Usage: ");
	ft_printf("./corewar [-dump nbr_cycles] [[-n number] champion1.cor] ...\n");
	ft_printf("  -v : Verbosity\n  -i : Interactive mode\n");
	exit(0);
}

void	parse_opt_dump(int argc, char **argv, t_vm *v, int *i) // функция парсинга флага dump
{
	v->opt_flags |= FLAG_OPT_DUMP; // ? (записываем куда то в структуру)
	if (*i + 1 < argc && ft_isdigit(*argv[*i + 1])) // проверка что после флага идет число
		v->dump_param = ft_atoi(argv[++*i]); // считка числа через atoi
	else
		xerror("Error: invalid dump parameter", -1); // иначе - ошибка
}

void	parse_opt_n(int argc, char **argv, t_vm *v, int *i) // парсинг флага n
{
	char	*c;

	if (*i + 1 < argc && (ft_isdigitstr(argv[*i + 1])) && *i + 2 < argc) // проверка на то что флаг n правильно записан (после -n должна быть цифра, а затем файл с чемпионом)
	{
		if ((c = ft_strstr(argv[*i + 2], ".cor")) && c != argv[*i + 2] && !c[4]) // проверка есть ли после цифры файл с чемпионом
		{
			get_player_custom(argv, *i, v); // кастомное получение игрока
			*i += 2;
		}
		else
			xerror("Error: invalid parameters", -1); // иначе ошибка
	}
	else
		xerror("Error: invalid parameters", -1); // иначе ошибка
}

void	parse_opt_verbose(int argc, char **argv, t_vm *v, int *i) // парсинг флага -v
{
	v->opt_flags |= FLAG_OPT_VERBOSE; // ? (записываем куда то в структуру)
	if (*i + 1 < argc && ft_isdigit(*argv[*i + 1])) // проверяем что после флага идет число
		v->verbose_param += ft_atoi(argv[++*i]); // читаем число с помощью atoi
}

void	parse_opt(int argc, char **argv, t_vm *v)
{
	int		i;
	char	*c;

	i = 1;
	while (i < argc) // перебираем все аргументы
	{
		if (!ft_strcmp("-i", argv[i])) // проверяем есть ли флаг -i
			v->opt_flags |= FLAG_OPT_NCURSES; // ? (записываем куда то в структуру)
		else if (!ft_strcmp("-v", argv[i])) // есть ли флаг -v
			parse_opt_verbose(argc, argv, v, &i); // парсим флаг -v
		else if (!ft_strcmp("-a", argv[i])) // есть ли флаг -a
		{
			v->opt_flags |= FLAG_OPT_VERBOSE; // ? (записываем куда то в структуру)
			v->verbose_param += FLAG_VERBOSE_AFF; // прибавляем что то к verbose
		}
		else if (!ft_strcmp("-dump", argv[i])) // проверяем совпадает ли с dump
			parse_opt_dump(argc, argv, v, &i); // парсим флаг dump
		else if ((c = ft_strstr(argv[i], ".cor")) && c != argv[i] && !c[4]) // если в строке есть .cor
			get_player(argv, i, v); // парсим игрока
		else if (!ft_strcmp("-n", argv[i])) // если есть флаг -n
			parse_opt_n(argc, argv, v, &i); // парсим флаг n
		else
			xerror("Error: invalid parameters", -1); // иначе ошибка
		i++;
	}
}

/*
** void	parse_opt(int argc, char **argv, t_vm *v)
** {
** 	int		i;
** 	char	*c;
**
** 	i = 1;
** 	while (i < argc)
** 	{
** 		if (!ft_strcmp("-i", argv[i]))
** 			v->opt_flags |= FLAG_OPT_NCURSES;
** 		else if (!ft_strcmp("-v", argv[i]))
** 		{
** 			v->opt_flags |= FLAG_OPT_VERBOSE;
** 			if (i + 1 < argc && ft_isdigit(*argv[i + 1]))
** 				v->verbose_param += ft_atoi(argv[++i]);
** 		}
** 		else if (!ft_strcmp("-a", argv[i]))
** 		{
** 			v->opt_flags |= FLAG_OPT_VERBOSE;
** 			v->verbose_param += FLAG_VERBOSE_AFF;
** 		}
** 		else if (!ft_strcmp("-dump", argv[i]))
** 		{
** 			v->opt_flags |= FLAG_OPT_DUMP;
** 			if (i + 1 < argc && ft_isdigit(*argv[i + 1]))
** 				v->dump_param = ft_atoi(argv[++i]);
** 			else
** 				xerror("Error: invalid dump parameter", -1);
** 		}
** 		else if ((c = ft_strstr(argv[i], ".cor")) && c != argv[i] && !c[4])
** 			get_player(argv, i, v);
**  		else if (!ft_strcmp("-n", argv[i]))
** 		{
** 			if (i + 1 < argc && (ft_isdigitstr(argv[i + 1])))
** 			{
** 				if ((c = ft_strstr(argv[i + 2], ".cor")) && c != argv[i + 2]
**					&& !c[4])
** 				{
** 					get_player_custom(argv, i, v);
** 					i += 2;
** 				}
** 				else
**  					xerror("Error: invalid parameters", -1);
** 			}
** 			else
**  				xerror("Error: invalid parameters", -1);
** 		}
** 		else
**  			xerror("Error: invalid parameters", -1);
** 		i++;
** 	}
** }
*/
