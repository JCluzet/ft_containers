#include <memory>
#include <iostream>

namespace ft
{

    template <class T, class Compare = std::less<typename T::first_type>, class Alloc = std::allocator<T> >
    class Tree
    {
    public:
        typedef	Compare						key_compare;
        typedef size_t                      size_type;
        typedef Alloc allocator_type;
        typedef T value_type;

        struct Node
        {
            // typename T::first_type key;
            // typename T::second_type value;
            value_type pair;
            Node *left;
            Node *right;
            Node *parent;
        };


        ~Tree(void) {}

        Tree(const key_compare &comp = key_compare(),
             const allocator_type &alloc = allocator_type()) : _allocValue(alloc), _size(0), _comp(comp){ this->_root = 0; }

        Node *newNode(T pair, Node *parent)
        {
            Node *node = _allocNode.allocate(1);
            _allocValue.construct(&node->pair, pair);
            node->parent = parent;
            node->left = NULL;
            node->right = NULL;
            // node->value = key.second;
            _size++;
            return node;
        }

        // pair<std::iterator,bool> insert (const value_type& key)
        // {
        //     Node *last;
        //     if (!_root)
        //     {
        //         _root = newNode(key, NULL);
        //         last = _root;
        //     }
        //     else
        //         last = insert(key, _root);
        // }

        Node *insert(value_type pair, Node *node)
        {
            if (pair.first < node->pair.first)
            {
                if (node->left != NULL)
                    insert(pair, node->left);
                else
                {
                    node->left = newNode(pair, node);
                    return node->left;
                }
            }
            else if (pair.first > node->pair.first)
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

        size_type size(void) const { return _size; }
        size_type max_size(void) const { return _allocNode.max_size(); }
        bool empty(void) const { return _size == 0; }

        key_compare key_comp(void) const { return _comp; }

        void insert(value_type pair)
        {
            Node *last;
            if (!_root)
            {
                _root = newNode(pair, NULL);
                last = _root;
            }
            else
                last = insert(pair, _root);
        }

        void print2DUtil(Node *root, int space)
        {
            // Base case
            if (root == NULL)
                return;

            // Increase distance between levels
            space += 10;

            // Process right child first
            print2DUtil(root->right, space);

            // Print current node after space
            // count
            std::cout << std::endl;
            for (int i = 10; i < space; i++)
                std::cout << " ";
            std::cout << root->pair.first << "\n";

            // Process left child
            print2DUtil(root->left, space);
        }

        void print2D() { print2DUtil(_root, 0); }

        Node *root() { return _root; }

    private:
        allocator_type _allocValue;
        std::allocator<Node> _allocNode;
        Node *_root;
        size_type _size;
        key_compare				_comp;
        Node *_lastNode;
    };
}
