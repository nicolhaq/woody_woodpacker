/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elf64_private.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrumbac <agrumbac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:43:25 by agrumbac          #+#    #+#             */
/*   Updated: 2019/05/10 08:35:36 by agrumbac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELF64_PRIVATE_H
# define ELF64_PRIVATE_H

# include <linux/elf.h>
# include "elf64.h"

/*
** Data
*/

struct				entry
{
	struct elf64_phdr	*safe_phdr;
	struct elf64_shdr	*safe_shdr;
	size_t			file_offset;
};

typedef	void	*(*f_safe_accessor)(const size_t offset, const size_t size);
typedef	void	*(*f_iter_callback)(f_safe_accessor safe, const size_t offset);

/*
** Utils
*/

bool	iterate_phdr(f_safe_accessor safe, f_iter_callback callback);
bool	iterate_shdr(f_safe_accessor safe, f_iter_callback callback);

/*
** Packer
*/

bool	find_entry(struct entry *original_entry, f_safe_accessor safe);
bool	copy_until_end_of_text(void *clone, const struct entry *original_entry);
bool	setup_payload(void *clone, const struct entry *original_entry);
bool	copy_after_end_of_text(void *clone);

/*
** Vicious payload !
*/

void	begin_payload(void);
void	end_payload(void);

#endif