#include <iostream>
#include <stack>
#include <queue>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

// Hàm khởi tạo cây nhị phân tìm kiếm
Node* createNode(int data) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Memory error\n";
        return NULL;
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Hàm thêm phần tử vào cây nhị phân tìm kiếm
Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        root = createNode(data);
        return root;
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
    }
    else {
        root->right = insertNode(root->right, data);
    }
    return root;
}

// Hàm duyệt LRN không sử dụng đệ quy
void postOrderIterative(Node* root) {
    if (root == NULL)
        return;

    stack<Node*> s1, s2;
    s1.push(root);
    Node* node;

    while (!s1.empty()) {
        node = s1.top();
        s1.pop();
        s2.push(node);

        if (node->left)
            s1.push(node->left);
        if (node->right)
            s1.push(node->right);
    }

    while (!s2.empty()) {
        node = s2.top();
        s2.pop();
        cout << node->data << " ";
    }
}

// Hàm duyệt NLR không sử dụng đệ quy
void preOrderIterative(Node* root) {
    if (root == NULL)
        return;

    stack<Node*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Node* node = nodeStack.top();
        cout << node->data << " ";
        nodeStack.pop();

        if (node->right)
            nodeStack.push(node->right);
        if (node->left)
            nodeStack.push(node->left);
    }
}

// Hàm duyệt LNR không sử dụng đệ quy
void inOrderIterative(Node* root) {
    stack<Node*> s;
    Node* curr = root;

    while (curr != NULL || s.empty() == false) {
        while (curr != NULL) {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();

        cout << curr->data << " ";

        curr = curr->right;
    }
}

// Hàm kiểm tra số nguyên tố
bool isPrime(int n) {
    if (n <= 1)
        return false;
    for (int i = 2; i <= n / 2; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

// Hàm đếm số node là số nguyên tố trong cây nhị phân tìm kiếm
int countPrimeNodes(Node* root) {
    if (root == NULL)
        return 0;

    int count = 0;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();

        if (isPrime(node->data))
            count++;

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }

    return count;
}

// Hàm đếm số node có đủ 2 thành phần: node con trái và node con phải
int countFullNodes(Node* root) {
    if (root == NULL)
        return 0;

    int count = 0;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* node = q.front();
        q.pop();

        if (node->left && node->right)
            count++;

        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }

    return count;
}

// Hàm tìm node cha của node cần tìm
Node* findParent(Node* root, int key) {
    if (root == NULL || root->data == key)
        return NULL;

    if ((root->left && root->left->data == key) || (root->right && root->right->data == key))
        return root;

    if (key < root->data)
        return findParent(root->left, key);
    else
        return findParent(root->right, key);
}

// Hàm xóa node cha của node cần tìm
Node* deleteNode(Node* root, int key) {
    Node* parent = findParent(root, key);
    if (parent == NULL)
        return root;

    Node* nodeToDelete = NULL;
    if (parent->left && parent->left->data == key) {
        nodeToDelete = parent->left;
        parent->left = NULL;
    }
    else if (parent->right && parent->right->data == key) {
        nodeToDelete = parent->right;
        parent->right = NULL;
    }

    delete nodeToDelete;
    return root;
}

// Hàm main để kiểm chứng toàn bộ chương trình dưới dạng menu lựa chọn
int main() {
    Node* root = NULL;
    int choice, value, key,n;

    do {
        cout << "\nMenu:\n";
        cout << "1. Thêm phần tử vào cây\n";
        cout << "2. Duyệt cây theo LRN\n";
        cout << "3. Duyệt cây theo NLR\n";
        cout << "4. Duyệt cây theo LNR\n";
        cout << "5. Đếm số node là số nguyên tố\n";
        cout << "6. Đếm số node có đủ 2 thành phần\n";
        cout << "7. Xóa node cha của node cần tìm\n";
        cout << "0. Thoát\n";
        cout << "Lựa chọn của bạn: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Nhap so luong: ";
            cin >> n;
            for (int i = 0; i < n; i++) {
                cout << "Nhập giá trị: " << i + 1 << ": ";
                cin >> value;
                root = insertNode(root, value);
            }
            break;
        case 2:
            cout << "Duyệt LRN: ";
            postOrderIterative(root);
            cout << endl;
            break;
        case 3:
            cout << "Duyệt NLR: ";
            preOrderIterative(root);
            cout << endl;
            break;
        case 4:
            cout << "Duyệt LNR: ";
            inOrderIterative(root);
            cout << endl;
            break;
        case 5:
            cout << "Số node là số nguyên tố: " << countPrimeNodes(root) << endl;
            break;
        case 6:
            cout << "Số node có đủ 2 thành phần: " << countFullNodes(root) << endl;
            break;
        case 7:
            cout << "Nhập giá trị node cần tìm: ";
            cin >> key;
            root = deleteNode(root, key);
            break;
        case 0:
            cout << "Thoát chương trình.\n";
            break;
        default:
            cout << "Lựa chọn không hợp lệ!\n";
        }
    } while (choice != 0);

    return 0;
}
