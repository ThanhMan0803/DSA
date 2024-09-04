#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <cmath>

struct Node {
    int data;
    Node* left;
    Node* right;
};

// Hàm khởi tạo cây nhị phân tìm kiếm
Node* createNode(int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Hàm thêm 1 giá trị vào cây nhị phân tìm kiếm
Node* insertNode(Node* root, int data) {
    if (root == nullptr) {
        root = createNode(data);
    }
    else if (data < root->data) {
        root->left = insertNode(root->left, data);
    }
    else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Hàm đọc dữ liệu từ file Input.txt và thêm vào cây
Node* buildTreeFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Không thể mở file!" << std::endl;
        return nullptr;
    }

    int n, value;
    file >> n;
    Node* root = nullptr;
    for (int i = 0; i < n; ++i) {
        file >> value;
        root = insertNode(root, value);
    }
    file.close();
    return root;
}

// Hàm duyệt LRN không sử dụng đệ quy
void postOrderNonRecursive(Node* root) {
    if (root == nullptr) return;
    std::stack<Node*> s1, s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* node = s1.top();
        s1.pop();
        s2.push(node);
        if (node->left) s1.push(node->left);
        if (node->right) s1.push(node->right);
    }
    while (!s2.empty()) {
        std::cout << s2.top()->data << " ";
        s2.pop();
    }
}

// Hàm duyệt NLR không sử dụng đệ quy
void preOrderNonRecursive(Node* root) {
    if (root == nullptr) return;
    std::stack<Node*> s;
    s.push(root);
    while (!s.empty()) {
        Node* node = s.top();
        s.pop();
        std::cout << node->data << " ";
        if (node->right) s.push(node->right);
        if (node->left) s.push(node->left);
    }
}

// Hàm duyệt LNR không sử dụng đệ quy
void inOrderNonRecursive(Node* root) {
    if (root == nullptr) return;
    std::stack<Node*> s;
    Node* current = root;
    while (current != nullptr || !s.empty()) {
        while (current != nullptr) {
            s.push(current);
            current = current->left;
        }
        current = s.top();
        s.pop();
        std::cout << current->data << " ";
        current = current->right;
    }
}

// Hàm kiểm tra số nguyên tố
bool isPrime(int n) {
    if (n <= 1) return false;
    for (int i = 2; i <= std::sqrt(n); ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

// Hàm đếm số node là số nguyên tố trong cây nhị phân tìm kiếm
int countPrimeNodes(Node* root) {
    if (root == nullptr) return 0;
    int count = 0;
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        if (isPrime(node->data)) ++count;
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    return count;
}

// Hàm đếm số node có đủ 2 thành phần: node con trái và node con phải
int countFullNodes(Node* root) {
    if (root == nullptr) return 0;
    int count = 0;
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* node = q.front();
        q.pop();
        if (node->left && node->right) ++count;
        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
    return count;
}

// Hàm tìm node cha của node cần tìm
Node* findParent(Node* root, int key) {
    if (root == nullptr || root->data == key) return nullptr;
    if ((root->left && root->left->data == key) || (root->right && root->right->data == key)) {
        return root;
    }
    if (key < root->data) return findParent(root->left, key);
    return findParent(root->right, key);
}

// Hàm xóa node cha của node cần tìm
Node* deleteParentNode(Node* root, int key) {
    Node* parent = findParent(root, key);
    if (parent == nullptr) return root; // Không tìm thấy node cha

    Node* nodeToDelete = nullptr;
    if (parent->left && parent->left->data == key) {
        nodeToDelete = parent->left;
        parent->left = nullptr;
    }
    else if (parent->right && parent->right->data == key) {
        nodeToDelete = parent->right;
        parent->right = nullptr;
    }

    delete nodeToDelete;
    return root;
}

// Hàm main để kiểm chứng toàn bộ chương trình dưới dạng menu lựa chọn
int main() {
    Node* root = buildTreeFromFile("b1.txt");

    int choice, value;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Duyệt cây theo LRN\n";
        std::cout << "2. Duyệt cây theo NLR\n";
        std::cout << "3. Duyệt cây theo LNR\n";
        std::cout << "4. Đếm số node là số nguyên tố\n";
        std::cout << "5. Đếm số node có đủ 2 thành phần\n";
        std::cout << "6. Xóa node cha của node cần tìm\n";
        std::cout << "0. Thoát\n";
        std::cout << "Lựa chọn của bạn: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            postOrderNonRecursive(root);
            break;
        case 2:
            preOrderNonRecursive(root);
            break;
        case 3:
            inOrderNonRecursive(root);
            break;
        case 4:
            std::cout << "Số node là số nguyên tố: " << countPrimeNodes(root) << std::endl;
            break;
        case 5:
            std::cout << "Số node có đủ 2 thành phần: " << countFullNodes(root) << std::endl;
            break;
        case 6:
            std::cout << "Nhập giá trị node cần tìm: ";
            std::cin >> value;
            root = deleteParentNode(root, value);
            break;
        case 0:
            std::cout << "Thoát chương trình.\n";
            break;
        default:
            std::cout << "Lựa chọn không hợp lệ!\n";
            break;
        }
    } while (choice != 0);

    return 0;
}
