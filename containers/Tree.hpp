#pragma once
#include <iostream>
#include <memory>
#include "../utils/pair.hpp"

namespace ft
{
template <class T, class Compare = std::less<typename T::first_type>, class Alloc = std::allocator<T> >
class Tree
    {
    public:
        typedef Alloc allocator_type;
        typedef T value_type;
        typedef typename T::first_type key_type;
        typedef typename T::second_type mapped_type;
        typedef Compare            key_compare;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef T&                      reference;
        typedef T*                      pointer;

        struct Node
        {
            value_type pair;
            Node *parent;
            Node *left;
            Node *right;
            difference_type height;

            Node*	min() {
				Node* node = this;
				while (node->left)
					node = node->left;
				return node;
			}
			
			Node*	max() {
				Node* node = this;
				while (node->right)
					node = node->right;
				return node;
			}
        };

        Tree(void)
        {
            _root = NULL;
            _size = 0;
            _end_node = _allocNode.allocate(1);
            // _comp = ;
            set_end_node();
        }

        Tree(const key_compare& comp = key_compare(),
	    const allocator_type& alloc = allocator_type())
        :_allocValue(alloc),  _comp(comp){
				_root = NULL;
                _size = 0;
				_end_node = _allocNode.allocate(1);
				set_end_node();
		}

        Tree(const Tree& x)
        :_allocValue(x._allocValue), _comp(x._comp)
        {
            _root = NULL;
            _size = 0;
            _end_node = _allocNode.allocate(1);
            set_end_node();
            copy(x._root);
        }

        void copy(Node* node)
        {
            if (node)
            {
                insert(node->pair);
                copy(node->left);
                copy(node->right);
            }
        }

        ~Tree(void) {
            _allocNode.deallocate(_end_node, 1);
        }

        size_type size(void) const
        {
            return _size;
        }

        bool empty(void) const
        {
            return _size == 0;
        }

        size_type max_size() const
        {
            return _allocNode.max_size();
        }
        
        difference_type height(Node *node) const{
            if (node == NULL)
                return 0;
            return node->height;
        }
            // VersAVL Ajouter un nouvel élément(key, value)
        void insert(value_type pair)
        {
            _root = insert(_root, pair);
        }

        key_compare key_comp() const
            { return _comp; }

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
                std::cout << root->pair.first << ":" << root->pair.second << ";" ;
                if (root->parent)
                    std::cout << root->parent->pair.second;
                else
                    std::cout <<  "NULL";
                std::cout  << std::endl;
                print_tree(root->right, lvl + 1);
            }
            std::cout << std::endl;
        }

        Node *root() const
            { return _root; }

        Node *find(key_type k) const 
            { return getNode(_root, k); }

        Node *_last() const
            { return _end_node; }

        bool contains(key_type key) const
            { return getNode(_root, key) != NULL; }

        mapped_type get(key_type key)
        {
            Node *node = getNode(_root, key);
            return node == NULL ? NULL : node->pair.second;
        }

        // Retour ànodePour la racineAVL Le noeud où se trouve la valeur minimale de
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

        // Retour ànodePour la racineAVL Le noeud où se trouve la valeur maximale de // DeAVL La clé de suppression est keyNode of
        void remove(key_type key)
        {
            if (getNode(_root, key))
                _root = remove(_root, key);
        }

        // Tree &operator=(const Tree &tree)
        // {
        //     _root = tree._root;
        //     _size = tree._size;
        //     return *this;
        // }

    private :

        allocator_type _allocValue;
        std::allocator<Node> _allocNode;
        Node *_root;
        Node *_end_node;
        size_type _size;
        key_compare _comp;

         Node *remove(Node *node, key_type key)
        {
            if (node == NULL)
                return NULL;
            Node *retNode;
            if (key < node->pair.first)
            {
                node->left = remove(node->left, key);
                retNode = node;
            }
            else if (key > node->pair.first)
            {
                node->right = remove(node->right, key);
                retNode = node;
            }
            else
            { // key.compareTo(node.key) == 0

                //  Si le Sous - arbre gauche du noeud à supprimer est vide
                if (node->left == NULL)
                {
                    Node *rightNode = node->right;
                    // node.right = NULL;
                    if (node->right){
                        _allocValue.destroy(&node->right->pair);
                        _allocNode.deallocate(node->right, 1);
                    }
                    _size--;
                    retNode = rightNode;
                }
                else if (node->right == NULL)
                { //  Si le Sous - arbre droit du noeud à supprimer est vide
                    Node *leftNode = node->left;
                    // node.left = NULL;
                    _allocValue.destroy(&node->left->pair);
                    _allocNode.deallocate(node->left, 1);
                    _size--;
                    retNode = leftNode;
                }
                else
                {
                    //  Les sous - arbres gauche et droit du noeud à supprimer ne sont pas vides

                    //  Trouver le plus petit noeud plus grand que le noeud à supprimer ,  C'est - à - dire le plus petit noeud du sous - arbre droit du noeud à supprimer
                    //  Remplacer le noeud à supprimer par ce noeud
                    Node *successor = minimum(node->right);
                    successor->right = remove(node->right, successor->pair.first);
                    successor->left = node->left;

                    // node.left = node.right = NULL;
                    _allocValue.destroy(&node->left->pair);
                    _allocNode.deallocate(node->left, 1);
                    _allocValue.destroy(&node->right->pair);
                    _allocNode.deallocate(node->right, 1);

                    retNode = successor;
                }
            }
            if (retNode == NULL)
                return NULL;
            // Mise à jourheight
            retNode->height = 1 + std::max(height(node->left), height(node->right));
            // Calculer le facteur d'équilibre
            difference_type balanceFactor = getBalanceFactor(retNode);
            //  Entretien équilibré
            if (balanceFactor > 1 && getBalanceFactor(retNode->left) >= 0)
            {
                return rightRotate(retNode);
            }
            if (balanceFactor < -1 && getBalanceFactor(retNode->right) <= 0)
            {
                return leftRotate(retNode);
            }
            if (balanceFactor > 1 && getBalanceFactor(retNode->left) < 0)
            {
                retNode->left = leftRotate(retNode->left);
                return rightRotate(retNode);
            }
            if (balanceFactor < -1 && getBalanceFactor(retNode->right) > 0)
            {
                retNode->right = rightRotate(retNode->right);
                return leftRotate(retNode);
            }
            return retNode;
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
        Node* rightRotate(Node* y)
        {

            Node* x = y->left;
            Node* T3 = x->right;

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
        Node* leftRotate(Node* y)
        {
            Node* x = y->right;
            Node* T2 = x->left;
            //  Processus de rotation à gauche
            x->left = y;
            y->right = T2;
            if(T2)
                T2->parent = y;
            if(x)
                x->parent = y->parent;
            if(y)
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


        void			set_end_node() {
        if (_root)
        	_end_node->parent = maximum(_root);
        else
        	_end_node->parent = 0;
        _end_node->right = 0;
        _end_node->left = 0;
   	    }
        // Xiang YinodePour la racineAVLInsérer un élément dans(key, value),Algorithme récursif
        //  Retour après l'insertion d'un nouveau noeud AVLRacine de
        Node* insert(Node *node, value_type pair, Node *parent = NULL)
        {
            if (node == NULL) {
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
            if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
                return rightRotate(node);
            }
            if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
                return leftRotate(node);
            }
            if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
            set_end_node();
            return node;
        }

    };
}