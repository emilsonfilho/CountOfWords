#ifndef BASE_TREE_HPP
#define BASE_TREE_HPP

template <typename Tree, typename Node, typename Key, typename Value>
class BaseTree {
    void count() const {
        static_cast<const Tree*>(this)->incrementCounter();
    }
protected:
    Node* root = nullptr;

    Node* findNode(const Key& key) const {
        Node* aux = root;

        while (aux) {
            if (key < aux->getKey()) {
                count();
                aux = aux->left;
            } else if (key > aux->getKey()) {
                count();
                aux = aux->right;
            } else {
                count();
                return aux;
            }
        }

        return nullptr;        
    }
};

#endif
