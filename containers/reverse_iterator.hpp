/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:00:40 by jcluzet           #+#    #+#             */
/*   Updated: 2022/04/15 19:17:50 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template <class T>
	class reverse_iterator
	{

            // -----------------------------------------------------------
            // --------------------- TYPEDEF -----------------------------
            // -----------------------------------------------------------

		public:
			typedef T        	        										iterator_type;
			typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;
			typedef typename iterator_traits<iterator_type>::value_type			value_type;
			typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename iterator_traits<iterator_type>::pointer			pointer;
			typedef typename iterator_traits<iterator_type>::reference			reference;

            // ------------------------------------------------------------
            // ----------------- CONSTRUCTOR ------------------------------
            // ------------------------------------------------------------

			reverse_iterator() {}
			explicit reverse_iterator (iterator_type it) : _ptr(it) {}
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it) : _ptr(rev_it.base()) {}

			iterator_type base() const { return this->_ptr; }
			

			// -------------------------------------------------------------
            // ---------------------- OPERATORS ----------------------------
            // -------------------------------------------------------------

			template <class Iter>
			reverse_iterator&	operator=(const reverse_iterator<Iter> &rev_it) {
				this->_it = rev_it.base();
				return *this;
			}
			reverse_iterator&	operator+=(difference_type n) { this->_ptr -= n; return *this; }
			reverse_iterator&	operator-=(difference_type n) { this->_ptr += n; return *this; }

			reference   		operator*() const {
				iterator_type tmp = this->_ptr;
				return *--tmp;
			}
			pointer				operator->() const { return &(operator*()); }
			reverse_iterator	operator-(difference_type n) const { return reverse_iterator(this->_ptr + n); }
			reverse_iterator&   operator--() { ++this->_ptr; return *this; }
			reverse_iterator&   operator++() { --this->_ptr; return *this; }
			reverse_iterator	operator+(difference_type n) const { return reverse_iterator(this->_ptr - n); }
			reference			operator[](difference_type n) { return this->_it[-n-1]; }
			reverse_iterator    operator++(int) { reverse_iterator tmp = *this; --this->_ptr; return tmp; }
			reverse_iterator    operator--(int) { reverse_iterator tmp = *this; ++this->_ptr; return tmp; }


		private:
			iterator_type	_ptr;
	};

	template<class It>
	reverse_iterator<It> operator+(typename reverse_iterator<It>::difference_type n, const reverse_iterator<It>& rev_it) 
	{
        reverse_iterator<It> tmp(rev_it);
        tmp += n;
        return tmp;
    }

	template<class It>
	typename reverse_iterator<It>::difference_type	operator-(const reverse_iterator<It>& lhs, const reverse_iterator<It>& rhs)
	{
        return rhs.base() - lhs.base();
    }
	
    template<class It1, class It2>
	typename reverse_iterator<It1>::difference_type	operator-(const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs)
	{ 
        return rhs.base() - lhs.base();
    }
	
	template< class It1, class It2 >
	bool operator== (const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) { return lhs.base() == rhs.base(); }
	template< class It1, class It2 >
	bool operator!= (const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) { return lhs.base() != rhs.base(); }
	template< class It1, class It2 >
	bool operator< (const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) { return lhs.base() > rhs.base(); }
	template< class It1, class It2 >
	bool operator<= (const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) { return lhs.base() >= rhs.base(); }
	template< class It1, class It2 >
	bool operator> (const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) { return lhs.base() < rhs.base(); }
	template< class It1, class It2 >
	bool operator>= (const reverse_iterator<It1>& lhs, const reverse_iterator<It2>& rhs) { return lhs.base() <= rhs.base(); }
}
