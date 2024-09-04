#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Cấu trúc cây nhị phân tìm kiếm
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Hàm khởi tạo cây nhị phân tìm kiếm
TreeNode* insertNode(TreeNode* root, int val) {
    if (root == NULL) {
        return new TreeNode(val);
    }
    if (val < root->val) {
        root->left = insertNode(root->left, val);
    }
    else if (val > root->val) {
        root->right = insertNode(root->right, val);
    }
    return root;
}

// Hàm đọc dữ liệu từ file Input.txt và thêm vào cây nhị phân tìm kiếm
TreeNode* createTreeFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Khong the mo file " << filename << endl;
        return NULL;
    }

    int n;
    file >> n;
    TreeNode* root = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        file >> val;
        root = insertNode(root, val);
    }
    file.close();
    return root;
}

// Hàm duyệt LNR (InOrder) không sử dụng đệ quy và không dùng stack
void inOrder(TreeNode* root) {
    TreeNode* current = root;
    TreeNode* pre;

    while (current != NULL) {
        if (current->left == NULL) {
            cout << current->val << " ";
            current = current->right;
        }
        else {
            pre = current->left;
            while (pre->right != NULL && pre->right != current) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            }
            else {
                pre->right = NULL;
                cout << current->val << " ";
                current = current->right;
            }
        }
    }
    cout << endl;
}

// Hàm duyệt NLR (PreOrder) không sử dụng đệ quy và không dùng stack
void preOrder(TreeNode* root) {
    TreeNode* current = root;
    TreeNode* pre;

    while (current != NULL) {
        if (current->left == NULL) {
            cout << current->val << " ";
            current = current->right;
        }
        else {
            pre = current->left;
            while (pre->right != NULL && pre->right != current) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
                cout << current->val << " ";
                pre->right = current;
                current = current->left;
            }
            else {
                pre->right = NULL;
                current = current->right;
            }
        }
    }
    cout << endl;
}

// Hàm duyệt LRN (PostOrder) không sử dụng đệ quy và không dùng stack
void postOrder(TreeNode* root) {
    TreeNode* dummy = new TreeNode(0);
    dummy->left = root;
    TreeNode* current = dummy;
    TreeNode* pre;

    while (current != NULL) {
        if (current->left == NULL) {
            current = current->right;
        }
        else {
            pre = current->left;
            while (pre->right != NULL && pre->right != current) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            }
            else {
                TreeNode* temp = current->left;
                while (temp != current) {
                    cout << temp->val << " ";
                    temp = temp->right;
                }
                cout << current->val << " ";
                pre->right = NULL;
                current = current->right;
            }
        }
    }
    delete dummy;
    cout << endl;
}

// Hàm kiểm tra số nguyên tố
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

// Hàm đếm số node là số nguyên tố trong cây nhị phân tìm kiếm
int countPrimeNodes(TreeNode* root) {
    if (root == NULL) return 0;
    int count = 0;
    TreeNode* current = root;
    TreeNode* pre;

    while (current != NULL) {
        if (current->left == NULL) {
            if (isPrime(current->val)) count++;
            current = current->right;
        }
        else {
            pre = current->left;
            while (pre->right != NULL && pre->right != current) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            }
            else {
                pre->right = NULL;
                if (isPrime(current->val)) count++;
                current = current->right;
            }
        }
    }
    return count;
}

// Hàm đếm số node có đủ 2 thành phần: node con trái và node con phải
int countFullNodes(TreeNode* root) {
    if (root == NULL) return 0;
    int count = 0;
    TreeNode* current = root;
    TreeNode* pre;

    while (current != NULL) {
        if (current->left == NULL) {
            if (current->left != NULL && current->right != NULL) count++;
            current = current->right;
        }
        else {
            pre = current->left;
            while (pre->right != NULL && pre->right != current) {
                pre = pre->right;
            }

            if (pre->right == NULL) {
                if (current->left != NULL && current->right != NULL) count++;
                pre->right = current;
                current = current->left;
            }
            else {
                pre->right = NULL;
                current = current->right;
            }
        }
    }
    return count;
}

// Hàm tìm node cha của node cần tìm
TreeNode* findParent(TreeNode* root, TreeNode* node) {
    if (root == NULL || root == node) return NULL;
    if (root->left == node || root->right == node) return root;
    if (node->val < root->val) {
        return findParent(root->left, node);
    }
    else {
        return findParent(root->right, node);
    }
}

// Hàm xoá node cha của node cần tìm
TreeNode* deleteParent(TreeNode* root, int key) {
    TreeNode* nodeToDelete = root;
    TreeNode* parent = findParent(root, nodeToDelete);
    while (nodeToDelete && nodeToDelete->val != key) {
        parent = nodeToDelete;
        if (key < nodeToDelete->val) {
            nodeToDelete = nodeToDelete->left;
        }
        else {
            nodeToDelete = nodeToDelete->right;
        }
    }

    if (!nodeToDelete) return root;

    if (!nodeToDelete->left) {
        if (nodeToDelete == root) {
            root = nodeToDelete->right;
        }
        else if (parent->left == nodeToDelete) {
            parent->left = nodeToDelete->right;
        }
        else {
            parent->right = nodeToDelete->right;
        }
    }
    else if (!nodeToDelete->right) {
        if (nodeToDelete == root) {
            root = nodeToDelete->left;
        }
        else if (parent->left == nodeToDelete) {
            parent->left = nodeToDelete->left;
        }
        else {
            parent->right = nodeToDelete->left;
        }
    }
    else {
        TreeNode* minNode = nodeToDelete->right;
        while (minNode->left) {
            minNode = minNode->left;
        }
        int minValue = minNode->val;
        deleteParent(root, minNode->val);
        nodeToDelete->val = minValue;
    }
    return root;
}

// Hàm menu lựa chọn
void menu() {
    TreeNode* root = NULL;
    int choice;
    do {
        cout << "--------------------------\n";
        cout << "1. Tao cay BST tu file\n";
        cout << "2. Duyet cay theo LNR (InOrder)\n";
        cout << "3. Duyet cay theo NLR (PreOrder)\n";
        cout << "4. Duyet cay theo LRN (PostOrder)\n";
        cout << "5. Dem so node la so nguyen to\n";
        cout << "6. Dem so node co day du hai con\n";
        cout << "7. Xoa node cha cua node co gia tri nhap vao\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "Lua chon: ";
        cin >> choice;
        switch (choice) {
        case 1:
            root = createTreeFromFile("b1.txt");
            break;
        case 2:
            inOrder(root);
            break;
        case 3:
            preOrder(root);
            break;
        case 4:
            postOrder(root);
            break;
        case 5:
            cout << "So node la so nguyen to: " << countPrimeNodes(root) << endl;
            break;
        case 6:
            cout << "So node co day du hai con: " << countFullNodes(root) << endl;
            break;
        case 7: {
            int key;
            cout << "Nhap gia tri node can xoa: ";
            cin >> key;
            root = deleteParent(root, key);
            break;
        }
        case 0:
            cout << "Thoat chuong trinh.\n";
            break;
        default:
            cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

// Hàm main
int main() {
    menu();
    return 0;
}
