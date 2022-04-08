#include <memory>
#include <iostream>
#include "../utils/pair.hpp"

namespace ft
{

    template <class T, class Compare = std::less<typename T::first_type>, class Alloc = std::allocator<T> >
    class Tree
    {
    public:
        typedef Compare key_compare;
        typedef typename T::first_type key_type;
        typedef typename T::second_type mapped_type;

        typedef size_t size_type;
        typedef Alloc allocator_type;
        typedef T value_type;
        typedef value_type *pointer;
        typedef T &reference;

        struct Node
        {
            value_type pair;
            Node *left;
            Node *right;
            Node *parent;
            Node *min()
            {
                Node *node = this;
                while (node->left)
                    node = node->left;
                return node;
            }
        };

        Node *minimum(Node *node)
        {
            if (node->left == nullptr)
                return node;
            return minimum(node->left);
        }

        ~Tree(void)
        {
        }

        Tree(const key_compare &comp = key_compare(),
             const allocator_type &alloc = allocator_type()) : _allocValue(alloc), _size(0), _comp(comp)
        {
            this->_begin = 0;
            _lastNode = _allocNode.allocate(1);
        }

        Node *newNode(value_type pair, Node *parent)
        {
            Node *node = _allocNode.allocate(1);
            _allocValue.construct(&node->pair, pair);
            node->parent = parent;
            node->left = NULL;
            node->right = NULL;
            _size++;
            return node;
        }
        // key_compare		key_comp() const { return this->_comp; }

        // insert function
        void insert(value_type pair)
        {
            Node *last;
            if (!_begin)
            {
                _begin = newNode(pair, NULL);
                last = _begin;
            }
            else
            {
                // if the key of the pair is already in the tree, we don't insert it
                if (find(pair.first, _begin) != NULL)
                    return;
                last = insert(pair, _begin);
                set_end_node();
            }
        }

        Node *insert(value_type pair, Node *node) // utiliser key_comp!!
        {
            if (_comp(pair.first, node->pair.first))
            {
                if (node->left != NULL)
                    insert(pair, node->left);
                else
                {
                    node->left = newNode(pair, node);
                    return node->left;
                }
            }
            else
            {
                if (node->right != NULL)
                    insert(pair, node->right);
                else
                {
                    node->right = newNode(pair, node);
                    return node->right;
                }
            }
            return node;
        }

        // find function
        Node *find(const typename T::first_type &key, Node *node)
        {
            if (node == NULL)
                return NULL;
            if (_comp(key, node->pair.first))
                return find(key, node->left);
            else if (_comp(node->pair.first, key))
                return find(key, node->right);
            else
                return node;
        }

        // Tree &operator=(const Tree &tree)
        // {
        //     if (this != &tree)
        //     {
        //         clear();
        //         _size = tree._size;
        //         _begin = copy(tree._begin, _begin);
        //         set_end_node();
        //     }
        //     return *this;
        // }

        Node *find(const typename T::first_type &key)
        {
            return find(key, this->_begin);
        }

        size_type size(void) const { return _size; }
        size_type max_size(void) const { return _allocNode.max_size(); }
        bool empty(void) const { return _size == 0; }
        key_compare key_comp(void) const { return _comp; }
        // value_compare value_comp(void) const { return _comp; }

        void clear(void)
        {
            // clear using destroyNode function
            destroyNode(_begin); // ca en clear qu'un seul !
            _begin = NULL;
            _size = 0;
        }

        allocator_type get_allocator(void) const { return _allocNode; }

        void
        print2DUtil(Node *root, int space)
        {
            if (root == NULL)
                return;

            space += 10;

            print2DUtil(root->right, space);

            std::cout << std::endl;
            for (int i = 10; i < space; i++)
                std::cout << " ";
            std::cout << root->pair.first << "::" << root->pair.second << "\n";
            print2DUtil(root->left, space);
        }

        void destroyNode(Node *node)
        {
            if (!node)
                return;
            destroyNode(node->left);
            destroyNode(node->right);
            this->_allocValue.destroy(&node->pair);
            this->_allocNode.deallocate(node, 1);
        }

        Node *maximum(Node *node) const
        {
            if (node->right == NULL)
                return node;
            return maximum(node->right);
        }

        void set_end_node()
        {
            if (_begin)
                _lastNode->parent = maximum(_begin);
            else
                _lastNode->parent = 0;
            _lastNode->right = 0;
            _lastNode->left = 0;
        }

        void print2D() { print2DUtil(_begin, 0); }

        Node *root() { return _begin; }
        Node *_last() { return _lastNode; }

    private:
        allocator_type _allocValue;
        std::allocator<Node> _allocNode;
        Node *_begin;
        size_type _size;
        key_compare _comp;
        Node *_lastNode;
    };
}
