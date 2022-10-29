/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melperri <melperri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 04:51:16 by melperri          #+#    #+#             */
/*   Updated: 2021/10/26 17:44:32 by melperri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minishell.h"

/*		ms_create_lst_cmd.c */
int		ms_create_lst_pipe(t_m_shl *g, char *line);

/*		ms_split_cmd.c */
int		ms_add_elem_lst_cmd(t_m_shl *g, int index);
int		ms_search_end_of_word(char *line);
int		ms_ultimate_realloc_split(char ***split, char *start, int size);

/*		ms_pars_pipe_and_redirector.c */
int		ms_index_on_space(t_m_shl *g, char *line);
int		ms_index_on_rafter(t_m_shl *g, char *line);
int		ms_set_redirector_tab(t_list *lst, char **array);
int		ms_check_double_pipe(t_m_shl *g, char *line);
int		ms_index_on_pipe(t_m_shl *g, char *line);

/*		ms_parsing_utils.c */
int		ms_trim_space(char *line, int i);
bool	ms_is_quote_open(bool quote[2], int c);
int		ms_last_char(t_m_shl *g, char *start, int i);
int		ms_check_end_of_line(t_m_shl *g);

/*		ms_pipe_lst_utils.c */
t_list	*ms_found_index_node(t_m_shl *g, int index);
void	ms_add_prev_red(char **prev_red, char red[3]);
char	**ms_return_prev_red_addr(t_list *lst);
char	***ms_return_cmd_addr(t_list *lst);
void	ms_print_lst_pipe(t_m_shl *g);

/*		ms_redirector_tab.c */
int		ms_set_redirector_tab(t_list *lst, char **array);

/*		ms_substitute_dollar.c */
int		ms_substitute_dollar(t_m_shl *g, char **token);

/*		ms_substitute_dollar_utils.c */
int		ms_len_env_val(t_list *lst);
char	*ms_dup_dollar_tosub(t_m_shl *g, char *token, char *tosub);
int		ms_close_quote_dollar(t_m_shl *g, char *token, int type);
int		ms_join_sub(t_m_shl *g, char **token, char *tosub);

/*		ms_substitute_quote.c */
int		ms_open_quote(t_m_shl *g, char *s, int i, int type);
int		ms_substitute_quote(t_m_shl *g, char **s, int i_open);

/*		ms_rafter_error.c */
int		ms_count_rafter(t_m_shl *g, char *line);

/*		ms_parsing_error.c */
char	*ms_check_only_space_line(char *line);
int		ms_check_redirector_tab(int *tab_red, int len);
int		ms_is_missing_quote(t_m_shl *g);
int		ms_return_error(t_m_shl *g);

#endif
