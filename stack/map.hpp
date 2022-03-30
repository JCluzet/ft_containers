/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:17 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/30 18:48:54 by jcluzet          ###   ########.fr       */
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
        typedef Tree< value_type, Compare, Alloc>			tree;
        typedef typename tree::Node							Node;
        typedef	map_iterator<bidirectional_iterator_tag, tree>		iterator;
        typedef typename allocator_type::reference                     reference;
        typedef typename allocator_type::const_reference               const_reference;
        typedef typename allocator_type::pointer                       pointer;
        // typedef typename T::Node                                        Node;
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
        iterator end() { return iterator(_tree._last(), _tree._last()); }
        

        //             ----------------  Modifiers ----------------
        // pair<iterator,bool> insert (const value_type& val);
        pair<iterator,bool>		insert(const value_type& val) {
				size_type n = this->size();
				_tree.insert(val);
				pair<iterator,bool> ret;
				ret.second = (n != this->size());
				ret.first = iterator(this->_tree.root(), this->_tree.root());
				return ret;
			}

        //            ----------------  Operations ----------------
        iterator find(const key_type& k)
        {
            Node *tmp = _tree.find(k);
            if (tmp)
                return iterator(tmp, _tree._last());
            return end();
        }


        //           ----------------  Observers ----------------

        
        //          ----------------  Iterators ----------------
        // iterator begin() { return iterator(_tree.begin()); }

        void print() {
            _tree.print2D();
        }

        
        key_compare key_comp() const
        {
            return _tree.key_comp();
        }
        ~map() {}
    private:
        tree _tree;
    };
}