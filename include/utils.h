/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csejault <csejault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 00:10:18 by csejault          #+#    #+#             */
/*   Updated: 2021/10/26 15:19:12 by melperri         ###   ########.fr       */
/*   Updated: 2021/09/20 14:30:38 by csejault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

/*			ms_atoi.c */
long		ms_atol(const char *nptr);

/*			ms_atoi.c */
int			ms_atoi(const char *nptr);

/*			ms_atoll.c */
long long	ms_atoll(const char *nptr);

/*			ms_bzero.c */
void		ms_bzero(void *s, size_t n);

/*			ms_calloc.c */
void		*ms_calloc(size_t nmemb, size_t size);

/*			ms_close_fd.c */
int			ms_close_fd(int *fd);

/*			ms_free_split.c */
int			ms_free_split(char ***split);
int			ms_free_split_upside_down(char ***split, int i);
int			ms_free_split_since(char ***split, int i);
int			ms_free_one_line_and_split(char ***split, int i);

/*			get_next_line.c */
char		*get_next_line(int fd);

/*			ms_isalpha.c */
int			ms_isalpha(int c);

/*			ms_isalnum.c */
int			ms_isalnum(int c);

/*			ms_str_is_alnum_undscr.c */
int			ms_str_is_alnum_undscr(char *str);

/*			ms_isdigit.c */
int			ms_isdigit(int c);

/*			ms_isspace.c */
int			ms_isspace(int c);

/*			ms_itoa.c */
char		*ms_itoa(int n);

/*			ms_itoa.c */
char		*ms_ltoa(long n);

/*			ms_lltoa(long long n) */
char		*ms_lltoa(long long n);

/*			ms_len_split.c */
int			ms_len_split(char **split);

/*			ms_memcpy.c*/
void		*ms_memcpy(void *dest, const void *src, size_t n);

/*			ms_memset.c */
void		ms_memset(void *s, int c, size_t n);

/*			ms_print_split.c */
void		ms_print_split(char *name, char **split);

/*			ms_split.h */
char		**ms_split(char const *s, char c);

/*			ms_split_first_limiter.c */
int			ms_split_first_limiter(char *str, char limiter,
				char **s1, char **s2);

/*			ms_read_input.c */
int			ms_recurse_read(t_read_input *g, int nb_l);
int			ms_read_file(t_m_shl *sh, int fd, char ***file, char *eof);

/*			ms_str_is_nbr.c */
int			ms_str_is_nbr(char *str);

/*			ms_strcat_w_len.c */
void		ms_strcat_w_len(char *dest, char *source, int l1, int l2);

/*			ms_strchr.c */
char		*ms_strchr(const char *s, int c);

/*			ms_strcmp.c */
int			ms_strcmp(const char *s1, const char *s2);

/*			ms_strcmp.c */
int			ms_strncmp(const char *s1, const char *s2, size_t n);

/*			ms_strcpy.c */
char		*ms_strcpy(char *dest, const char *src);

/*			ms_strcpy.c */
char		*ms_strncpy(char *dest, const char *src, int n);

/*			ms_strdup.c */
char		*ms_strdup(const char *s);

/*			ms_strlen.c */
size_t		ms_strlen(const char *str);

/*			ms_strjoin.c */
char		*ms_strjoin(char const *s1, char const *s2);

/*			ms_strj_fr_1.c */
char		*ms_strj_fr_1(char *s1, char const *s2);

/*			ms_substr.c */
char		*ms_substr(char const *s, unsigned int start, size_t len);

/*			ms_t_list.c */
t_list		*ms_lstnew(void *content);
void		ms_lstadd_back(t_list **alst, t_list *new);
void		ms_lstadd_front(t_list **alst, t_list *new);
void		ms_lstclear(t_list **lst, void (*del)(void*));
void		ms_lstdelone(t_list *lst, void (*del)(void*));

/*			ms_t_list_env.c */
void		ms_lstadd_back_env(t_m_shl *g, t_list *new);
void		ms_lstadd_front_env(t_m_shl *g, t_list *new);
void		ms_pop_one_env(t_m_shl *g, char *key_to_pop);
void		ms_lstdelone_env(t_m_shl *g, t_list **lst);
void		ms_lstclear_env(t_m_shl *g);

/*			ms_t_list2.c */
void		ms_lstiter(t_list *lst, void (*f)(void *));
t_list		*ms_lstlast(t_list *lst);
int			ms_lstsize(t_list *lst);

/*			ms_t_list_cmd.c */
t_list		*ms_lstnew_cmd(void *content);
void		ms_lstadd_back_cmd(t_list **alst, t_list *new);
void		ms_lstadd_front_cmd(t_list **alst, t_list *new);
void		ms_lstclear_cmd(t_list **lst, void (*del)(void*));
void		ms_lstdelone_cmd(t_list *lst, void (*del)(void*));

/*			ms_t_list2_cmd.c */
void		ms_lstiter_cmd(t_list *lst, void (*f)(void *));
t_list		*ms_lstlast_cmd(t_list *lst);
int			ms_lstsize_cmd(t_list *lst);

#endif
