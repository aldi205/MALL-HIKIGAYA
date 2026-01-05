
#ifndef AVL_TREE_H
#define AVL_TREE_H


template<typename K, typename V>
class AVLTree {
private:
    struct Node {
        K key;
        V value;
        int height;
        Node* left;
        Node* right;
        Node(const K &k, const V &v)
            : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    static int nodeHeight(Node* n) {
        return n ? n->height : 0;
    }

    static void updateHeight(Node* n) {
        int hl = nodeHeight(n->left);
        int hr = nodeHeight(n->right);
        n->height = (hl > hr ? hl : hr) + 1;
    }

    static int balanceFactor(Node* n) {
        return n ? nodeHeight(n->left) - nodeHeight(n->right) : 0;
    }

    static Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        updateHeight(y);
        updateHeight(x);
        return x;
    }

    static Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        updateHeight(x);
        updateHeight(y);
        return y;
    }

    static Node* balance(Node* n) {
        if (!n) return n;
        updateHeight(n);
        int bf = balanceFactor(n);
        if (bf > 1) {
            if (balanceFactor(n->left) < 0)
                n->left = rotateLeft(n->left);
            return rotateRight(n);
        }
        if (bf < -1) {
            if (balanceFactor(n->right) > 0)
                n->right = rotateRight(n->right);
            return rotateLeft(n);
        }
        return n;
    }

    Node* insertRec(Node* n, const K &k, const V &v) {
        if (!n) return new Node(k, v);
        if (k < n->key)
            n->left = insertRec(n->left, k, v);
        else if (n->key < k)
            n->right = insertRec(n->right, k, v);
        else {
            n->value = v; // replace
            return n;
        }
        return balance(n);
    }

    static Node* minNode(Node* n) {
        Node* cur = n;
        while (cur && cur->left) cur = cur->left;
        return cur;
    }

    Node* removeRec(Node* n, const K &k) {
        if (!n) return nullptr;
        if (k < n->key)
            n->left = removeRec(n->left, k);
        else if (n->key < k)
            n->right = removeRec(n->right, k);
        else {
            // found node
            if (!n->left || !n->right) {
                Node* tmp = n->left ? n->left : n->right;
                if (!tmp) {
                    delete n;
                    return nullptr;
                } else {
                    Node* ret = tmp;
                    delete n;
                    n = ret;
                }
            } else {
                Node* succ = minNode(n->right);
                n->key = succ->key;
                n->value = succ->value;
                n->right = removeRec(n->right, succ->key);
            }
        }
        if (!n) return nullptr;
        return balance(n);
    }

    V* findRec(Node* n, const K &k) const {
        if (!n) return nullptr;
        if (k < n->key) return findRec(n->left, k);
        if (n->key < k) return findRec(n->right, k);
        return &n->value;
    }

    template<typename Func>
    void inorderRec(Node* n, Func f) const {
        if (!n) return;
        inorderRec(n->left, f);
        f(n->key, n->value);
        inorderRec(n->right, f);
    }

    void clearRec(Node* n) {
        if (!n) return;
        clearRec(n->left);
        clearRec(n->right);
        delete n;
    }

public:
    AVLTree() : root(nullptr) {}
    ~AVLTree() { clearRec(root); }

    void insert(const K &k, const V &v) { root = insertRec(root, k, v); }

    bool remove(const K &k) {
        if (!find(k)) return false;
        root = removeRec(root, k);
        return true;
    }

    V* find(const K &k) const { return findRec(root, k); }

    template<typename Func>
    void inorder(Func f) const { inorderRec(root, f); }
};

#endif // AVL_TREE_H

