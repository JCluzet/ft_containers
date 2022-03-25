/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcluzet <jcluzet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 01:39:17 by jcluzet           #+#    #+#             */
/*   Updated: 2022/03/25 01:20:24 by jcluzet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "iterators.hpp"

#include "Tree.hpp"
// #include "enable_if.hpp"
#include <memory>

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, 
              class Alloc = std::allocator<std::pair<const Key, T> > >
    class map
    {

    public:
        typedef T                                           value_type;
        typedef	Alloc										allocator_type;
        // typedef iterator <std::bidirectional_iterator_tag, value_type, value_type &, value_type *> iterator;
        typedef	Compare										key_compare;
        typedef Tree< value_type, Alloc>			tree;
        explicit map(const key_compare &comp = key_compare(),
                     const allocator_type &alloc = allocator_type()) : _tree(comp, alloc) {}
        ~map() {}
        // std::pair<std::iterator,bool> insert (const value_type& key) // renvoi un pair avec l'iterateur de l'element et 0 si l'element n'a pas ete ajoute (il existait deja)
        // {
        //     return _tree.insert(key);
        // }
        // {
        //     std::pair<std::iterator,bool> ret;
        //     ret.second = false;
        //     if (!_tree.root)
        //     {
        //         _tree.root = _tree.newNode(key, NULL);
        //         ret.second = true;
        //         ret.first = _tree.root;
        //     }
        //     else
        //         ret = _tree.insert(key, _tree.root);
        //     return ret;
        // }
        // {
        //     std::pair<std::iterator,bool> ret = _tree.insert(key);
        //     return ret;
        // }
        // void insert(int key);
    private:
        tree _tree;
    };
}