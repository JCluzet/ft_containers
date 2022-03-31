/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:17 by jcluzet           #+#    #+#             */
/*   Updated: 2022/04/01 00:17:20 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterators.hpp"

#include "Tree.hpp"
#include "../utils/pair.hpp"
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
        typedef typename allocator_type::const_pointer                 const_pointer;
        // typedef ???                                             iterator;
        // typedef ???                                             const_iterator;
        // typedef ???                                             reverse_iterator;
        // typedef ???                                             const_reverse_iterator;
        typedef ptrdiff_t                                   difference_type;
        typedef size_t                                      size_type;

        //              ----------------  Constructor ----------------
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type()) : _tree(comp, alloc) {}

        template <class InputIterator>
        map (InputIterator first, InputIterator last,
        const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _tree(comp, alloc)
        {
            for (; first != last; ++first)
                insert(*first);
        }

        map (const map& x)
        {
            _tree = x._tree;
        }

        //              ----------------  Iterators ----------------
        iterator end() { return iterator(_tree._last(), _tree._last()); }
        iterator begin() { return iterator(_tree.root(), _tree._last()); }
        
        //              ----------------  Capacity ----------------
        size_type size() const { return _tree.size(); }
        size_type max_size() const { return _tree.max_size(); }
        bool empty() const { return _tree.empty(); }

        //              ----------------  Element access ----------------  ✅
        mapped_type& operator[] (const key_type& k)
        {
            iterator it = find(k);
            if (it != end())
                return (*it).second;
            else
            {
                insert(value_type(k, mapped_type()));
                return (*find(k)).second;
            }
        }

        //              ----------------  Modifiers ---------------- 
        pair<iterator,bool>		insert(const value_type& val) {
				size_type n = this->size();
				_tree.insert(val);
				pair<iterator,bool> ret;
				ret.second = (n != this->size());
				ret.first = iterator(this->_tree.root(), this->_tree.root());
				return ret;
			}

        // iterator insert (iterator position, const value_type& val);

        // template <class InputIterator>
        // void insert (InputIterator first, InputIterator last);


        // void erase (iterator position)
        // {
        //     _tree.erase(position.node);
        // }

        // size_type eralse (const key_type& k)l
        // {
        //     return _tree.erase(k);
        // }

        // void clear() { _tree.clear(); }


        //           ----------------  Observers ----------------


        //            ----------------  Operations ----------------
        iterator find(const key_type& k)
        {
            Node *tmp = _tree.find(k);
            if (tmp)
                return iterator(tmp, _tree._last());
            return end();
        }
        
        
        //          ----------------  Capacity ----------------
        void print() {
            _tree.print2D();
        }

        //         ----------------  Allocator ----------------
        allocator_type get_allocator() const { return _tree.get_allocator(); }
        
        key_compare key_comp() const
        {
            return _tree.key_comp();
        }
        ~map() {}
    private:
        tree _tree;
    };
}