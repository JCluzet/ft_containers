/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 16:29:26 by jcluzet           #+#    #+#             */
/*   Updated: 2022/04/15 16:29:44 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once	
    
    template <class Iterator>
	class iterator_traits
	{
		public:
			typedef typename Iterator::reference			reference;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::iterator_category	iterator_category;
	};