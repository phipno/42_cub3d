/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 13:39:30 by pnolte            #+#    #+#             */
/*   Updated: 2022/07/06 11:35:30 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// # include <stdio.h>
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft.h"

int	ft_printf(const char *str, ...);
int	putchar_count(char c);
int	hp_itoa_count(int n);
int	hp_u_itoa_count(unsigned int n);
int	putstring_count(char *str);
int	hp_counter(long int number);
int	hp_hexa_conv(unsigned int nb, char con);
int	hp_hexa_ptr(unsigned long nb);
int	hp_hex_counter(unsigned long nb);

#endif
