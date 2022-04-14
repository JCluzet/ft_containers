// #pragma once
#include <iostream>
#include <memory>
#include <algorithm>
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
        typedef Compare key_compare;
        typedef ptrdiff_t difference_type;
        typedef size_t size_type;
        typedef T &reference;
        typedef T *pointer;

        // pair structure that represents a node in the tree
        struct Node
        {
            value_type pair; // holds the key
            Node *parent;    // pointer to the parent
            Node *left;      // pointer to left child
            Node *right;     // pointer to right child
            // Node *next;      // pointer to next node in the list
            int bf; // balance factor of the node

            				Node*	getParent() {
					Node* node = this;
					while (node->parent)
						node = node->parent;
					return node;
				}

            Node *min()
            {
                Node *cur = this;
                while (cur->left != nullptr)
                    cur = cur->left;
                return cur;
            }

            Node *max()
            {
                Node *cur = this;
                while (cur->right != nullptr)
                    cur = cur->right;
                return cur;
            }
        };

        void swap(Tree &other)
        {
				Node* tmp = this->_root;
				this->_root = other._root;
				other._root = tmp;
        }

        typedef Node *NodePtr;

        size_type count(const key_type &key) const
        {
            NodePtr cur = _root;
            while (cur != nullptr)
            {
                if (_comp(key, cur->pair.first))
                    cur = cur->left;
                else if (_comp(cur->pair.first, key))
                    cur = cur->right;
                else
                    return 1;
            }
            return 0;
        }

        void clear()
        {
            _size = 0;
            _root = 0;
            set_end_node();
            
        }

        // void clear()
        // {
        //     for (iteratorit=begin
        //     // this->set_end_node();
        //     this->_end_node->parent = 0;
        // }

    private:
        NodePtr _root;
        NodePtr _end_node;
        allocator_type _allocValue;
        std::allocator<Node> _allocNode;
        size_type _size;
        key_compare _comp;
        // initializes the nodes with appropirate values
        // all the pointers are set to point to the null pointer
        void initializeNode(NodePtr node, value_type key)
        {
            node->pair = key;
            node->parent = nullptr;
            node->left = nullptr;
            node->right = nullptr;
            node->bf = 0;
        }

        // void clear(NodePtr node)
        // {
        //     if (node == nullptr)
        //         return;
        //     clear(node->left);
        //     clear(node->right);
        //     _allocNode.destroy(node);
        //     _allocNode.deallocate(node, 1);
        // }

        void preOrderHelper(NodePtr node)
        {
            if (node != nullptr)
            {
                std::cout << node->pair << " ";
                preOrderHelper(node->left);
                preOrderHelper(node->right);
            }
        }

        void inOrderHelper(NodePtr node)
        {
            if (node != nullptr)
            {
                inOrderHelper(node->left);
                std::cout << node->pair << " ";
                inOrderHelper(node->right);
            }
        }

        // void set_nester(NodePtr node)
        // {
        //     if (node != nullptr)
        //     {
        //         set_nester(node->left);
        //         set_nester(node->right);
        //         node->next = node->max();
        //     }
        // }

        void postOrderHelper(NodePtr node)
        {
            if (node != nullptr)
            {
                postOrderHelper(node->left);
                postOrderHelper(node->right);
                std::cout << node->pair << " ";
            }
        }

        NodePtr searchTreeHelper(NodePtr node, key_type key)
        {
            if (node == nullptr || key == node->pair.first)
            {
                return node;
            }

            if (_comp(key, node->pair.first))
            {
                return searchTreeHelper(node->left, key);
            }
            return searchTreeHelper(node->right, key);
        }

        NodePtr deleteNodeHelper(NodePtr node, value_type key)
        {

            if (_size == 0)
            {
                return nullptr;
            }
            // search the key
            if (node == nullptr)
                return node;
            else if (_comp(key.first, node->pair.first))
                node->left = deleteNodeHelper(node->left, key);
            else if (_comp(node->pair.first, key.first))
                node->right = deleteNodeHelper(node->right, key);
            else
            {
                // the key has been found, now delete it

                // case 1: node is a leaf node
                if (node->left == nullptr && node->right == nullptr)
                {
                    // delete node;
                    _allocValue.destroy(&node->pair);
                    _allocNode.deallocate(node, 1);
                    _size--;
                    node = nullptr;
                    // set_end_node();
                    // printf("case 1\n");
                    // set_nester(node);
                    // node = nullptr;
                }

                // case 2: node has only one child
                else if (node->left == nullptr)
                {
                    NodePtr temp = node;
                    node = node->right;
                    // delete temp;
                    _allocValue.destroy(&temp->pair);
                    _allocNode.deallocate(temp, 1);
                    _size--;
                    node = nullptr;
                    // set_end_node();
                    // printf("case 2\n");
                    // set_nester(node);
                }

                else if (node->right == nullptr)
                {
                    NodePtr temp = node;
                    node = node->left;
                    // delete temp;
                    _allocValue.destroy(&temp->pair);
                    _allocNode.deallocate(temp, 1);
                    _size--;
                    node = nullptr;
                    // set_end_node();
                    // printf("case 3\n");
                    // set_nester(node);
                }

                // case 3: has both children
                else
                {
                    NodePtr temp = minimum(node->right);
                    node->pair = temp->pair;
                    node->right = deleteNodeHelper(node->right, temp->pair);
                    // printf("case 4\n");
                    // _size--;
                    // set_end_node();
                }
            }
            return node;
        }

        // update the balance factor the node
        void updateBalance(NodePtr node)
        {
            if (node->bf < -1 || node->bf > 1)
            {
                rebalance(node);
                return;
            }

            if (node->parent != nullptr)
            {
                if (node == node->parent->left)
                {
                    node->parent->bf -= 1;
                }

                if (node == node->parent->right)
                {
                    node->parent->bf += 1;
                }

                if (node->parent->bf != 0)
                {
                    updateBalance(node->parent);
                }
            }
        }

        // rebalance the tree
        void rebalance(NodePtr node)
        {
            if (node->bf > 0)
            {
                if (node->right->bf < 0)
                {
                    rightRotate(node->right);
                    leftRotate(node);
                }
                else
                {
                    leftRotate(node);
                }
            }
            else if (node->bf < 0)
            {
                if (node->left->bf > 0)
                {
                    leftRotate(node->left);
                    rightRotate(node);
                }
                else
                {
                    rightRotate(node);
                }
            }
        }

    public:
        // AVLTree()
        // {
        // root = nullptr;
        // _size = 0;
        // }

        size_type size() const
        {
            return _size;
        }

        size_type max_size() const
        {
            return _allocNode.max_size();
        }

        // Tree()
        // {
        //     _root = nullptr;
        //     _size = 0;
        // }

        Tree(const key_compare &comp = key_compare(),
             const allocator_type &alloc = allocator_type())
            : _allocValue(alloc), _comp(comp)
        {
            _size = 0;
            _root = 0;
            _end_node = _allocNode.allocate(1);
            set_end_node();
        }

        // Pre-Order traversal
        // Node->Left Subtree->Right Subtree
        void preorder()
        {
            preOrderHelper(this->_root);
        }

        // In-Order traversal
        // Left Subtree -> Node -> Right Subtree
        void inorder()
        {
            inOrderHelper(this->_root);
        }

        // Post-Order traversal
        // Left Subtree -> Right Subtree -> Node
        void postorder()
        {
            postOrderHelper(this->_root);
        }

        // search the tree for the key k
        // and return the corresponding node

        NodePtr find(key_type k)
        {
            return searchTreeHelper(this->_root, k);
        }

        // NodePtr searchTree(end_nodvalue_type k)
        // {
        //     return searchTreeHelper(this->_root, k);
        // }

        // find the node with the minimum key
        NodePtr minimum(NodePtr node)
        {
            while (node->left != nullptr)
            {
                node = node->left;
            }
            return node;
        }

        // find the node with the maximum key
        NodePtr maximum(NodePtr node)
        {
            while (node->right != nullptr)
            {
                node = node->right;
            }
            return node;
        }

        // find the successor of a given node
        NodePtr successor(NodePtr x)
        {
            // if the right subtree is not null,
            // the successor is the leftmost node in the
            // right subtree
            if (x->right != nullptr)
            {
                return minimum(x->right);
            }

            // else it is the lowest ancestor of x whose
            // left child is also an ancestor of x.
            NodePtr y = x->parent;
            while (y != nullptr && x == y->right)
            {
                x = y;
                y = y->parent;
            }
            return y;
        }

        // key_compare key_comp() const { return _comp; }

			void			set_end_node() {
				if (this->_root)
					this->_end_node->parent = this->_root->max();
				else
					this->_end_node->parent = 0;
				this->_end_node->right = 0;
				this->_end_node->left = 0;
                // prettyPrint();
                // std::cout << "endnode: " << this->_end_node->pair.first << std::endl;
			}

        NodePtr _last(void) const { return _end_node; }

        // find the predecessor of a given node
        NodePtr predecessor(NodePtr x)
        {
            // if the left subtree is not null,
            // the predecessor is the rightmost node in the
            // left subtree
            if (x->left != nullptr)
            {
                return maximum(x->left);
            }

            NodePtr y = x->parent;
            while (y != nullptr && x == y->left)
            {
                x = y;
                y = y->parent;
            }

            return y;
        }

        // rotate left at node x
        void leftRotate(NodePtr x)
        {
            NodePtr y = x->right;
            x->right = y->left;
            if (y->left != nullptr)
            {
                y->left->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr)
            {
                this->_root = y;
            }
            else if (x == x->parent->left)
            {
                x->parent->left = y;
            }
            else
            {
                x->parent->right = y;
            }
            y->left = x;
            x->parent = y;

            // update the balance factor
            x->bf = x->bf - 1 - std::max(0, y->bf);
            y->bf = y->bf - 1 + std::min(0, x->bf);
        }

        // rotate right at node x
        void rightRotate(NodePtr x)
        {
            NodePtr y = x->left;
            x->left = y->right;
            if (y->right != nullptr)
            {
                y->right->parent = x;
            }
            y->parent = x->parent;
            if (x->parent == nullptr)
            {
                this->_root = y;
            }
            else if (x == x->parent->right)
            {
                x->parent->right = y;
            }
            else
            {
                x->parent->left = y;
            }
            y->right = x;
            x->parent = y;

            // update the balance factor
            x->bf = x->bf + 1 - std::min(0, y->bf);
            y->bf = y->bf + 1 + std::max(0, x->bf);
        }

        // insert the key to the tree in its appropriate position
        void insert(value_type pair)
        {
            // PART 1: Ordinary BST insert
            // NodePtr node = new Node;
            if (find(pair.first) != nullptr)
            {
                return;
            }
            NodePtr node = _allocNode.allocate(1);
            node->parent = nullptr;
            node->left = nullptr;
            node->right = nullptr;
            // node->pair = key;
            _allocValue.construct(&node->pair, pair);
            _size++;
            node->bf = 0;
            NodePtr y = nullptr;
            NodePtr x = this->_root;
            // for (unsigned int i = 0; i < 1000000; i++)
            // {

            // }

            while (x != nullptr)
            {
                y = x;
                if (_comp(node->pair.first, x->pair.first))
                {
                    x = x->left;
                }
                else
                {
                    x = x->right;
                }
            }

            // y is parent of x
            node->parent = y;
            if (y == nullptr)
            {
                _root = node;
            }
            else if (_comp(node->pair.first, y->pair.first))
            {
                y->left = node;
            }
            else
            {
                y->right = node;
            }

            // PART 2: re-balance the node if necessary
            updateBalance(node);
            // set_nester(node);
            set_end_node();
        }

        NodePtr root() { return this->_root; }

        // delete the node from the tree

        NodePtr deleteNode(value_type pair)
        {
            NodePtr deletedNode = deleteNodeHelper(this->_root, pair);
            // set_end_node();
            return deletedNode;
        }

        // print the tree structure on the screen

        // -------------------------------------------------------------
        // --------------------------  PRINT  --------------------------
        // -------------------------------------------------------------
        void printHelper(NodePtr root, std::string indent, bool last)
        {
            // print the tree structure on the screen
            if (root != nullptr)
            {
                std::cout << indent;
                if (last)
                {
                    std::cout << "R----";
                    indent += "     ";
                }
                else
                {
                    std::cout << "L----";
                    indent += "|    ";
                }

                std::cout << root->pair.first << "( BF = " << root->bf << ")" << std::endl;

                printHelper(root->left, indent, false);
                printHelper(root->right, indent, true);
            }
        }

        void prettyPrint()
        {
            printHelper(this->_root, "", true);
        }
    };
}

// int main()
// {
//     ft::Tree<ft::pair<int, int> > bst;
//     // bst.createSampleTree1();
//     int i = 50;
//     bst.insert(ft::pair<int, int>(i, i));
//     i = 30;
//     bst.insert(ft::pair<int, int>(i, i));
//     i = 70;
//     bst.insert(ft::pair<int, int>(i, i));
//     i = 23;
//     bst.insert(ft::pair<int, int>(i, i));
//     bst.prettyPrint();
//     while(1)
//     {
//         std::string in;
//         std::cin >> in;
//         bst.deleteNode(ft::pair<int, int>(std::stoi(in), std::stoi(in)));
//     bst.prettyPrint();
//     }
//     return 0;
// }