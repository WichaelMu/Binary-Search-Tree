#include "stdc++.h"

using namespace std;

template <typename T>
struct Node {
        string node;
        Node<T>* left;
        Node<T>* parent;
        Node<T>* right;
        T weight;

        Node(const string& u, const T& v, Node<T>* parent) {
                this->node = u;
                this->left = nullptr;
                this->parent = parent;
                this->right = nullptr;
                this->weight = v;
        }

        ~Node() {
                delete this->left;
                delete this->parent;
                delete this->right;
        }

        bool is_adj(const string& u) {
                if (this->left && this->left->node == u) { return true; }
                if (this->right && this->right->node == u) { return true; }
                if (this->parent && this->parent->node == u) { return true; }

                return false;
        }

        size_t degree() {
                size_t degree = 0;

                if (this->left) { degree++; }
                if (this->right) { degree++; }
                if (this->parent) { degree++; }

                return degree;
        }

        bool is_left() {
                return this->weight < this->parent->weight;
        }


        bool operator>  (const string& u) { return this->node > u; }
        bool operator<  (const string& u) { return this->node < u; }
        bool operator>= (const string& u) { return this->node >= u; }
        bool operator<= (const string& u) { return this->node <= u; }
        bool operator== (const string& u) { return this->node == u; }
        bool operator== (const Node<T>& u) { return this->node == u->node; }
};