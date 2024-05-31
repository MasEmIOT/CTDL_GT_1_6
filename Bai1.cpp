#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Kieu cua cac nut tren cay (chua thong tin ve mot sinh vien).
struct Node {
    int sbd; // So bao danh
    string hoTen; // Ho ten sinh vien
    Node *left; // Con tro toi nut con trai
    Node *right; // Con tro toi nut con phai

    // Ham tao.
    Node(int s, string h, Node *l, Node *r) : sbd(s), hoTen(h), left(l), right(r) {}
};

// Lop cay nhi phan tim kiếm.
class BSTree {
private:
    Node *root; // Con tro toi nut goc cua cay

    // Xoa rong cay (viet theo kieu de quy).
    void makeEmpty(Node *&t) {
        if (t == nullptr) return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = nullptr;
    }

    // Chen mot sinh vien moi vao cay (viet theo kieu de quy).
    void insert(int sbd, string hoTen, Node *&t) {
        if (t == nullptr)
            t = new Node(sbd, hoTen, nullptr, nullptr);
        else if (sbd < t->sbd)
            insert(sbd, hoTen, t->left);
        else if (sbd > t->sbd)
            insert(sbd, hoTen, t->right);
    }

    // Tim sinh vien theo so bao danh (viet theo kieu de quy).
    Node *search(int sbd, Node *t) {
        if (t == nullptr) return nullptr;
        if (sbd < t->sbd) return search(sbd, t->left);
        else if (sbd > t->sbd) return search(sbd, t->right);
        else return t;
    }

    // Duyet cay theo thu tu truoc (NLR).
    void preorder(Node *t) {
        if (t != nullptr) {
            cout << t->sbd << " - " << t->hoTen << endl;
            preorder(t->left);
            preorder(t->right);
        }
    }

    // Duyet cay theo thu tu giua (LNR).
    void inorder(Node *t) {
        if (t != nullptr) {
            inorder(t->left);
            cout << t->sbd << " - " << t->hoTen << endl;
            inorder(t->right);
        }
    }

    // Duyet cay theo thu tu sau (LRN).
    void postorder(Node *t) {
        if (t != nullptr) {
            postorder(t->left);
            postorder(t->right);
            cout << t->sbd << " - " << t->hoTen << endl;
        }
    }

    // Chuyen doi cay BST thanh vector.
    void treeToVector(Node *t, vector<Node*> &vec) {
        if (t != nullptr) {
            treeToVector(t->left, vec);
            vec.push_back(t);
            treeToVector(t->right, vec);
        }
    }

    // Ham sap xep vun dong (heap sort).
    void heapify(vector<Node*> &vec, int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && vec[left]->sbd > vec[largest]->sbd)
            largest = left;

        if (right < n && vec[right]->sbd > vec[largest]->sbd)
            largest = right;

        if (largest != i) {
            swap(vec[i], vec[largest]);
            heapify(vec, n, largest);
        }
    }

    void heapSort(vector<Node*> &vec) {
        int n = vec.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(vec, n, i);

        for (int i = n - 1; i > 0; i--) {
            swap(vec[0], vec[i]);
            heapify(vec, i, 0);
        }
    }

public:
    // Ham tao (ban dau cay rong).
    BSTree() : root(nullptr) {}

    // Ham huy (xoa het cac nut tren cay).
    ~BSTree() {
        makeEmpty(root);
    }

    // Kiem tra cay co rong hay khong.
    bool isEmpty() {
        return root == nullptr;
    }

    // Xoa het cac nut tren cay.
    void makeEmpty() {
        makeEmpty(root);
    }

    // Chen mot sinh vien moi vao cay.
    void insert(int sbd, string hoTen) {
        insert(sbd, hoTen, root);
    }

    // Tim sinh vien theo so bao danh.
    Node *search(int sbd) {
        return search(sbd, root);
    }

    // Duyet cay theo thu tu truoc.
    void preorder() {
        preorder(root);
    }

    // Duyet cay theo thu tu giua.
    void inorder() {
        inorder(root);
    }

    // Duyet cay theo thu tu sau.
    void postorder() {
        postorder(root);
    }

    // Sap xep danh sach sinh vien theo so bao danh.
    void sortStudents() {
        vector<Node*> vec;
        treeToVector(root, vec);
        heapSort(vec);
        for (Node* n : vec) {
            cout << n->sbd << " - " << n->hoTen << endl;
        }
    }
};

int main() {
    BSTree bst;
    // Chen mot so sinh vien moi vao cay.
    bst.insert(5, "Tuan");
    bst.insert(6, "Lan");
    bst.insert(3, "Cong");
    bst.insert(8, "Huong");
    bst.insert(7, "Binh");
    bst.insert(4, "Hai");
    bst.insert(2, "Son");

    // Tim hai sinh vien co so bao danh 4 va 9.
    Node *n1 = bst.search(4);
    Node *n2 = bst.search(9);

    // In ket qua tim kiem
    if (n1 != nullptr)
        cout << "Sinh vien voi SBD=4 la " << n1->hoTen << endl;
    if (n2 == nullptr)
        cout << "Khong tim thay sinh vien voi SBD=9" << endl;

    // Duyet cay theo thu tu truoc.
    cout << "Duyet cay theo thu tu truoc:" << endl;
    bst.preorder();

    // Duyet cay theo thu tu giua.
    cout << "Duyet cay theo thu tu giua:" << endl;
    bst.inorder();

    // Duyet cay theo thu tu sau.
    cout << "Duyet cay theo thu tu sau:" << endl;
    bst.postorder();

    // Sap xep va in danh sach sinh vien theo so bao danh.
    cout << "Danh sach sinh vien sau khi sap xep:" << endl;
    bst.sortStudents();

    // Lam rong cay.
    bst.makeEmpty();
    if (bst.isEmpty())
        cout << "Cay da bi xoa rong" << endl;

    return 0;
}
