#pragma once
#include <iostream>
#include <memory>
#include "../utils/pair.hpp"

struct Node;

namespace ft
{
    template <class T, class Compare = std::less<typename T::first_type>, class Alloc = std::allocator<Node> >
    class Tree
    {
    public:
        // ---------------------------------------------------------------------
        //                                TypeDEF
        // ---------------------------------------------------------------------

        typedef Alloc allocator_type;
        typedef T value_type;
        typedef typename T::first_type key_type;
        typedef typename T::second_type mapped_type;
        typedef Node node_type;
        typedef Compare key_compare;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef T &reference;
        typedef T *pointer;

        // ---------------------------------------------------------------------
        //                                NODE
        // ---------------------------------------------------------------------

        struct Node
        {
            value_type pair;
            Node *parent;
            Node *left;
            Node *right;
            difference_type height;

            Node *min()
            {
                Node *node = this;
                while (node->left)
                    node = node->left;
                return node;
            }

            Node *max()
            {
                Node *node = this;
                while (node->right)
                    node = node->right;
                return node;
            }
        };

        // ---------------------------------------------------------------------
        //                                CONSTRUCTOR
        // ---------------------------------------------------------------------

        Tree(void)
        {
            _end_node = allocator_type().allocate(1);
            allocator_type().construct(_last, node_type());
            _root = NULL;
            _size = 0;
            set_end_node();
        }

        Tree(const key_compare &comp = key_compare(),
             const allocator_type &alloc = allocator_type())
            : _allocValue(alloc), _comp(comp)
        {
            _root = NULL;
            _size = 0;
            _end_node = _allocNode.allocate(1);
            set_end_node();
        }

        Tree(const Tree &x)
            : _allocValue(x._allocValue), _comp(x._comp)
        {
            *this = x;
        }

        // ---------------------------------------------------------------------
        //                                OPERATORS=
        // ---------------------------------------------------------------------

        Tree &operator=(const Tree &x)
        {
            _root = x._root;
            _size = 0;
            _end_node = _allocNode.allocate(1);
            set_end_node();
            copy(x._root);
            return *this;
        }

        void copy(Node *node)
        {
            if (node)
            {
                // std::cout << "HEY" << std::endl;
                insert(node->pair);
                copy(node->left);
                copy(node->right);
            }
        }

        // ---------------------------------------------------------------------
        //                                DESTRUCTOR
        // ---------------------------------------------------------------------

        ~Tree(void)
        {
            _allocNode.deallocate(_end_node, 1);
        }

        // ---------------------------------------------------------------------
        //                                CAPACITY
        // ---------------------------------------------------------------------

        size_type size(void) const { return _size; }

        bool empty(void) const { return _size == 0; }

        size_type max_size() const { return _allocNode.max_size(); }

        // ---------------------------------------------------------------------
        //                                MODIFIERS
        // ---------------------------------------------------------------------

        void insert(value_type pair) { _root = insert(_root, pair); } // ICI 3

        void erase(key_type key)
        {
            if (getNode(_root, key))
                _root = erase(_root, key);
        }

        void swap(Tree &x)
        {
            Node *sw = _root;
            _root = x._root;
            x._root = sw;
        }

        key_compare key_comp() const { return _comp; }

        void print2D(void)
        {
            print_tree(_root);
        }

        void print_tree(Node *root, int lvl = 0) const
        {
            if (root == NULL)
            {
                padding('\t', lvl);
                std::cout << "~";
            }
            else
            {
                print_tree(root->left, lvl + 1);
                padding('\t', lvl);
                std::cout << root->pair.first << ":" << root->pair.second << ";";
                if (root->parent)
                    std::cout << root->parent->pair.second;
                else
                    std::cout << "NULL";
                std::cout << std::endl;
                print_tree(root->right, lvl + 1);
            }
            std::cout << std::endl;
        }

        Node *root() const { return _root; }
        Node *_last() const { return _end_node; }

        // ---------------------------------------------------------------------
        //                                Operations
        // ---------------------------------------------------------------------

        Node *find(key_type k) const
        {
            return getNode(_root, k);
        }

        size_type count(const key_type key) const
        {
            return getNode(_root, key) != NULL;
        }

        // iterator lower_bound(const key_type k)
        // {
        //     Node *node = getNode(_root, k);
        //     if (node)
        //         return iterator(node);
        //     else
        //         return iterator(_end_node);
        // }

        mapped_type get(key_type key)
        {
            Node *node = getNode(_root, key);
            return node == NULL ? NULL : node->pair.second;
        }

        Node *minimum(Node *node)
        {
            if (node->left == NULL)
                return node;
            return minimum(node->left);
        }

        Node *maximum(Node *node)
        {
            if (node->right == NULL)
                return node;
            return maximum(node->right);
        }

        void clear()
        {
            for (unsigned int i = 0; i < _size; i++)
                erase(_root->pair.first);
            this->_root = 0;
            this->set_end_node();
        }

    private:
        Node *erase(Node *node, key_type key)
        {
            if (node == NULL)
                return NULL;
            else if (_comp(key, node->pair.first))
                node->left = erase(node->left, key);
            else if (_comp(node->pair.first, key))
                node->right = erase(node->right, key);
            else
            {
                if (!node->left || !node->right)
                {
                    Node *tmp = node;
                    node = node->left ? node->left : node->right;
                    if (node)
                        node->parent = tmp->parent;
                    _allocValue.destroy(&tmp->pair);
                    _allocNode.deallocate(tmp, 1);
                }
                else
                {
                    Node *tmp = minimum(node->right);
                    if (tmp != node->right)
                    {
                        tmp->right = node->right;
                        node->right->parent = tmp;
                    }
                    if (tmp != node->left)
                    {
                        tmp->left = node->left;
                        node->left->parent = tmp;
                    }
                    tmp->parent->left = NULL;
                    tmp->parent = node->parent;
                    _allocValue.destroy(&node->pair);
                    _allocNode.deallocate(node, 1);
                    node = tmp;
                }
                _size--;
            }
            if (!node)
                return NULL;
            difference_type bf = getBalanceFactor(node);
            if (bf < -1 && getBalanceFactor(node->left) <= 0)
                return rightRotate(node);
            if (bf > 1 && getBalanceFactor(node->right) >= 0)
                return leftRotate(node);
            if (bf < -1 && getBalanceFactor(node->left) > 0)
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            if (bf > 1 && getBalanceFactor(node->right) < 0)
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            return node;
        }

        difference_type getBalanceFactor(Node *node)
        {
            if (node == NULL)
                return 0;
            return height(node->left) - height(node->right);
        }

        /**
         * Paire de noeuds y Tourner à droite , Retour au nouveau noeud racine après la rotation x
         *            y                                      x
         *           / \                                    / \
         *          x   T4          Tourner à droite       z   y
         *         /     \       - - - - - - - - ->      / \   / \
         *        z      T3                            T1  T2 T3  T4
         *       / \
         *      T1 T2
         */
        Node *rightRotate(Node *y)
        {

            Node *x = y->left;
            Node *T3 = x->right;

            //  Processus de rotation à droite
            x->right = y;
            y->left = T3;
            if (T3)
                T3->parent = y;
            if (x)
                x->parent = y->parent;
            if (y)
                y->parent = x;
            // Mise à jourheight
            y->height = height(y->left) > height(y->right) ? height(y->left) + 1 : height(y->right) + 1;
            x->height = height(x->left) > height(x->right) ? height(x->left) + 1 : height(x->right) + 1;
            return x;
        }

        difference_type height(Node *node) const
        {
            if (node == NULL)
                return 0;
            return node->height;
        }
        /**
         * Paire de noeuds y Faire tourner à gauche , Retour au nouveau noeud racine après rotation x
         *        y                                    x
         *      /  \                                 /  \
         *    T1    x     Tourner à gauche (y)      y     z
         *        /  \        - - - - - - - - ->  / \   /  \
         *       T2   z                          T1 T2 T3  T4
         *          /  \
         *         T3  T4
         */
        Node *leftRotate(Node *y)
        {
            Node *x = y->right;
            Node *T2 = x->left; // ICI 5
            //  Processus de rotation à gauche
            x->left = y;
            y->right = T2;
            if (T2)
                T2->parent = y;
            if (x)
                x->parent = y->parent;
            if (y)
                y->parent = x;
            // Mise à jourheight
            y->height = height(y->left) > height(y->right) ? height(y->left) + 1 : height(y->right) + 1;
            x->height = height(x->left) > height(x->right) ? height(x->left) + 1 : height(x->right) + 1;
            return x;
        }
        // Retour node Pour le noeud racineAVLMoyenne,keyLe noeud sur lequel
        Node *getNode(Node *node, key_type key) const
        {
            if (node == NULL)
                return NULL;
            if (key == node->pair.first /*key.equals(node.key)*/)
                return node;
            else if (key < node->pair.first /*key.compareTo(node.key) < 0*/)
                return getNode(node->left, key);
            else // if(key.compareTo(node.key) > 0)
                return getNode(node->right, key);
        }

        Node *newNode(value_type pair, Node *parent)
        {
            Node *node = _allocNode.allocate(1);
            _allocValue.construct(&node->pair, pair);
            node->left = NULL;
            node->right = NULL;
            node->parent = parent;
            return node;
        }

        void padding(char c, int n) const
        {
            for (int i = 0; i < n; i++)
                std::cout << c;
        }

        void set_end_node()
        {
            if (_root)
                _end_node->parent = maximum(_root);
            else
                _end_node->parent = 0;
            _end_node->right = 0;
            _end_node->left = 0;
        }
        // Xiang YinodePour la racineAVLInsérer un élément dans(key, value),Algorithme récursif
        //  Retour après l'insertion d'un nouveau noeud AVLRacine de
        Node *insert(Node *node, value_type pair, Node *parent = NULL)
        {
            if (node == NULL)
            {
                _size++;
                return newNode(pair, parent);
            }
            if (pair.first < node->pair.first)
                node->left = insert(node->left, pair, node);
            else if (pair.first > node->pair.first)
                node->right = insert(node->right, pair, node);
            else // key.compareTo(node.key) == 0
            {
                // node->value = value;
                node->pair.second = pair.second;
            }
            // Mise à jourheight
            node->height = height(node->left) > height(node->right) ? height(node->left) + 1 : height(node->right) + 1;
            // Calculer le facteur d'équilibre
            difference_type balanceFactor = getBalanceFactor(node);
            //  Entretien équilibré
            if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0)
            {
                return rightRotate(node);
            }
            if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0)
            {
                return leftRotate(node); // ICI 4
            }
            if (balanceFactor > 1 && getBalanceFactor(node->left) < 0)
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            if (balanceFactor < -1 && getBalanceFactor(node->right) > 0)
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            set_end_node();
            return node;
        }

        allocator_type _allocValue;
        std::allocator<Node> _allocNode;
        Node *_root;
        Node *_end_node;
        size_type _size;
        key_compare _comp;
    };
}