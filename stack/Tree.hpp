#include <memory>
#include <iostream>

namespace ft
{

    template <class T, class Alloc = std::allocator<T>,
    class Compare = std::less<T> >
    class Tree
    {
    public:
        typedef	Compare						key_compare;
        typedef Alloc allocator_type;
        typedef T value_type;

        struct Node
        {
            value_type key;
            Node *left;
            Node *right;
            // Node *parent;
        };

        Tree(void)
        {
            _root = NULL;
        }
        ~Tree(void) {}

        Tree(const key_compare &comp = key_compare(),
             const allocator_type &alloc = allocator_type()) : _comp(comp), _allocValue(alloc)
        {
            this->_root = 0;
            // this->_end_node = this->_allocNode.allocate(1);
            // this->set_end_node();
        }

        Node *newNode(T key, Node *parent)
        {
            Node *node = _allocNode.allocate(1);
            _allocValue.construct(&node->key, key);
            // node->parent = parent;
            node->left = NULL;
            node->right = NULL;
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

        Node *insert(T key, Node *node)
        {
            if (key < node->key)
            {
                if (node->left != NULL)
                    insert(key, node->left);
                else
                {
                    node->left = newNode(key, node);
                    return node->left;
                }
            }
            else if (key > node->key)
            {
                if (node->right != NULL)
                    insert(key, node->right);
                else
                {
                    node->right = newNode(key, node);
                    return node->right;
                }
            }
            return node;
        }

        void insert(T key)
        {
            Node *last;
            if (!_root)
            {
                _root = newNode(key, NULL);
                last = _root;
            }
            else
                last = insert(key, _root);
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
            std::cout << root->key << "\n";

            // Process left child
            print2DUtil(root->left, space);
        }

        void print2D() { print2DUtil(_root, 0); }

        Node *root() { return _root; }

    private:
        allocator_type _allocValue;
        std::allocator<Node> _allocNode;
        Node *_root;
        key_compare				_comp;
        Node *_lastNode;
    };
}