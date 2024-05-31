#include <iostream>

template <typename T>
class BinaryTreeNode {
public:
    T data;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree {
private:
    BinaryTreeNode<T>* root;
    int size;

public:
    BinaryTree() : root(nullptr), size(0) {}

    // Thêm phần tử vào cây
    void Insert(T value) {
        root = InsertRecursive(root, value);
    }

    // Tìm một nút có giá trị bằng x trong cây
    BinaryTreeNode<T>* FindNode(T value) {
        return FindNodeRecursive(root, value);
    }

    // Lấy kích thước của cây
    int GetSize() const {
        return size;
    }

private:
    // Hàm đệ quy để thêm phần tử vào cây
    BinaryTreeNode<T>* InsertRecursive(BinaryTreeNode<T>* node, T value) {
        if (node == nullptr) {
            size++;
            return new BinaryTreeNode<T>(value);
        }

        if (value < node->data) {
            node->left = InsertRecursive(node->left, value);
        } else if (value > node->data) {
            node->right = InsertRecursive(node->right, value);
        }

        return node;
    }

    // Hàm đệ quy để tìm nút có giá trị bằng x trong cây
    BinaryTreeNode<T>* FindNodeRecursive(BinaryTreeNode<T>* node, T value) {
        if (node == nullptr || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return FindNodeRecursive(node->left, value);
        } else {
            return FindNodeRecursive(node->right, value);
        }
    }
};

int main() {
    BinaryTree<int> tree;
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);

    BinaryTreeNode<int>* foundNode = tree.FindNode(5);
    if (foundNode) {
        std::cout << "Found node with value 5." << std::endl;
    } else {
        std::cout << "Node with value 5 not found." << std::endl;
    }

    std::cout << "Size of the tree: " << tree.GetSize() << std::endl;

    return 0;
}
