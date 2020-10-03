/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_players_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pboutelo <pboutelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/22 17:59:13 by pboutelo          #+#    #+#             */
/*   Updated: 2017/04/27 15:02:17 by pboutelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	xerror(char *error_msg, int error_id) // функция ошибки
{
	ft_putendl_fd(error_msg, 2);
	exit(error_id);
}

int		is_corewar_execmagic(char *file) // проверяем содержится ли в начале файла magic header
{
	unsigned char	exec_magic[4];
	int				fd;

	if ((fd = open(file, O_RDONLY)) != -1)
	{
		read(fd, &exec_magic[3], 1);
		read(fd, &exec_magic[2], 1);
		read(fd, &exec_magic[1], 1);
		read(fd, &exec_magic[0], 1);
		if (*(unsigned int *)exec_magic != COREWAR_EXEC_MAGIC)
			xerror("Error: wrong exec_magic", -1);
	}
	else
		xerror("Error: cannot open file", -1);
	close(fd);
	return (1);
}

int		get_prog_size(char *file) // получаем размер файла с чемпионом
{
	int fd;
	int size;

	size = -1;
	if ((fd = open(file, O_RDONLY)) != -1)
		size = lseek(fd, 0, SEEK_END);
	else
		xerror("Error: cannot open file", -1);
	close(fd);
	return (size - sizeof(t_header));
}

int		is_cor_file(char *file) // проверяем действительно ли это .cor файл
{
	if (!file)
		return (1);
	while (*file)
		file++;
	return (ft_strcmp(file - 4, ".cor"));
}

int		is_valid_player(char *file)
{
	if (is_cor_file(file) != 0) // проверяем действительно ли это .cor файл
		return (0);
	if (get_prog_size(file) > CHAMP_MAX_SIZE) // проверяем что размер чемпиона не больше чем максимально возможный
		return (0);
	if (!is_corewar_execmagic(file)) // проверяем что есть magic header
		return (0);
	return (1);
}
