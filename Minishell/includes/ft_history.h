/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_history.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 17:16:56 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/15 18:19:56 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HISTORY_H
# define FT_HISTORY_H

# include <sys/types.h>
# include <sys/stat.h>

t_list	*ft_initialise_history(void);
int		ft_add_history(char *entry);
int		ft_seek_history(char next, size_t *col);

#endif
