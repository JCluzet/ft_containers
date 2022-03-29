/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:17 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/29 16:19:55 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterators.hpp"

#include "Tree.hpp"
#include "../utils/pair.hpp"
// #include "enable_if.hpp"
#include <memory>

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>,
              class Alloc = std::allocator<std::pair<const Key, T> > >
    class map
    {

    public:
    //                ----------------  TypeDEF ----------------
        typedef Key                                         key_type;
        typedef T                                           mapped_type;
        typedef ft::pair<const key_type,mapped_type>            value_type;
        typedef	Compare										key_compare;
        //typedef ???                                       value_compare;
        typedef	Alloc										allocator_type;
        typedef typename allocator_type::reference                     reference;
        typedef typename allocator_type::const_reference               const_reference;
        typedef typename allocator_type::pointer                       pointer;
        typedef typename allocator_type::const_pointer                 const_pointer;
        // typedef ???                                             iterator;
        // typedef ???                                             const_iterator;
        // typedef ???                                             reverse_iterator;
        // typedef ???                                             const_reverse_iterator;
        typedef ptrdiff_t                                   difference_type;
        typedef size_t                                      size_type;
        // typedef iterator <std::bidirectional_iterator_tag, value_type, value_type &, value_type *> iterator;
        // typedef Tree<value_type, Alloc>			tree;

        //               ----------------  Constructor ----------------
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type()) : _tree(comp, alloc) {}

        //              ----------------  Capacity ----------------
        size_type size() const { return _tree.size(); }
        size_type max_size() const { return _tree.max_size(); }
        bool empty() const { return _tree.empty(); }

        //              ----------------  Element access ----------------
        

        //             ----------------  Modifiers ----------------


        //            ----------------  Operations ----------------


        //           ----------------  Observers ----------------
        key_compare key_comp() const
        {
            return _tree.key_comp();
        }
        ~map() {}
    private:
        Tree<value_type, Compare, Alloc> _tree;
    };
}