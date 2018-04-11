

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define CONVERSIONS "sSpdDioOuUxXcC"
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "locale.h"
# include "wchar.h"
# include <stdio.h>


typedef enum			e_size_specificators
{
	hh, h, l, ll, j, z
}						t_ts;

typedef struct			s_main
{
	int					bp;  	 	   /*byte write returned*/
	int 				p;		   	  /*precision*/
	long long int		w;	     	 /*width*/
	int					l;		    /*bytes of char or str*/
	int 				c;		   /*count*/
	int					cur_max;  /*if locale  = 4 else = 1*/
	int     		    sign;    /*for UTF ONLY if width < 0 */
	wint_t				i;
	char 				res;
	const char 			*begin;
	t_ts				ts;
	int					pl;			/*plus*/
	int					min;	   /*minus*/
	int					hes;
	int					spa;
	int					zer;
	long long int		tmp;
}						t_var;



int		ft_printf(const char *format, ...);
void	f_chk(va_list ap, const char *format, t_var *v);
int		f_no_perc_at_all(const char **format, t_var *v);
void	f_chk_let_conv(const char **format, va_list ap, t_var *v);
int		f_perc_s_small(va_list ap, const char **format, t_var *v);
int 	f_perc_S_big(va_list ap, const char **format, t_var *v);
int		f_w_e_l(char c, int length);
int		ft_atoi(const char *str);
int		ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
int     f_from_per_to_per(va_list ap, const char **format, t_var *v);
int     f_perc_c_small(va_list ap, const char **format, t_var *v);
int     f_perc_C_big(va_list ap, const char **format, t_var *v);
int     f_perc_d_small(va_list ap, const char **format, t_var *v);
int     f_sign(const char **format, t_var *v);
char    *f_itoa(long long int number);
void	f_for_d_and_i_flags(t_var *v, long long int v_arg, char *argv);
int     f_spec_the_size_for_d_and_i(long long int *v_arg, t_var *v);
int     f_perc_x_X(va_list ap, const char **format, t_var *v);
int     f_reset_init(t_var *v);
int     f_spec_the_size_for_x_and_X(unsigned long long int *v_arg, t_var *v);
char	*ft_itoa_base(unsigned long long int value, int base, char res);
void	f_handl_x_X(t_var *v, unsigned long long int v_arg, char *argv);
int     f_perc_o_O(va_list ap, const char **format, t_var *v);
void    f_handl_o_O(t_var *v, unsigned long long int v_arg, char *argv);
int     f_perc_p_small(va_list ap, const char **format, t_var *v);
#endif
