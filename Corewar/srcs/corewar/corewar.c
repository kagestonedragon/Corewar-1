/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emedea <emedea@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 17:04:38 by bduron            #+#    #+#             */
/*   Updated: 2020/10/03 17:15:50 by emedea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char **argv)
{
	t_vm		vm;
	t_viewer	v;

	vm_init(&vm); // инициализация виртуальной машины
	parse_opt(argc, argv, &vm); // парсинг входных параметров
	if (!vm.nplayer)
		print_help(); // выводим функционал, если кол-во игроков равно нулю
	vm.display_mode = (vm.opt_flags & FLAG_OPT_NCURSES) ? 2 : 3;
	vm.display_mode = (vm.opt_flags & FLAG_OPT_VERBOSE) ? 1 : vm.display_mode;
	load_arena(&vm); // никита
	if (vm.display_mode == 2)
	{
		viewer_init(&v, &vm); // 04-05 октября
		viewer_run(&v); // 04-05 октября
	}
	else
		run_game(&vm); // никита
	return (0);
}
