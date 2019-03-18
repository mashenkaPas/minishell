/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpas <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 21:31:03 by dkotov            #+#    #+#             */
/*   Updated: 2019/03/14 21:42:33 by mpas             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

int		b_printf(const char *restrict format, ...);
void	ft_putchar_a(char c);
void	ft_putstr_a(char *str);
char	*itoa_base_helper(char *tab, long long value, int base, int sign);
char	*ft_itoa_base(long long value, int base);
int		checker_c(char ch, va_list args);
int		checker_p_or_o(char ch, va_list args);
int		checker_id_or_u(char ch, va_list args);
int		checker_s(char ch, va_list args);
int		checker(int i, const char *restrict format, va_list args);
int		ft_strlen_a(char *s);

#endif
