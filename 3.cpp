#include <iostream>
using namespace std;

// Cấu trúc node của danh sách liên kết kép
struct Node {
    int data;
    Node* prev;
    Node* next;
};

// Khai báo cấu trúc danh sách liên kết kép
struct DoublyLinkedList {
    Node* head;
    Node* tail;
    DoublyLinkedList() : head(NULL), tail(NULL) {}
};

// Hàm tạo node mới
Node* createNode(int value) {
    Node* newNode = new Node();
    if (!newNode) {
        cout << "Loi cap phat bo nho!\n";
        exit(1);
    }
    newNode->data = value;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

// Hàm thêm phần tử vào cuối danh sách liên kết kép
void append(DoublyLinkedList& list, int value) {
    Node* newNode = createNode(value);
    if (list.head == NULL) {
        list.head = list.tail = newNode;
    }
    else {
        list.tail->next = newNode;
        newNode->prev = list.tail;
        list.tail = newNode;
    }
}

// Hàm nhập các phần tử vào danh sách
void inputList(DoublyLinkedList& list) {
    int n;
    cout << "Nhap so luong phan tu: ";
    cin >> n;
    cout << "Nhap cac phan tu:\n";
    for (int i = 0; i < n; i++) {
        int value;
        cin >> value;
        append(list, value);
    }
}

// Hàm xuất các giá trị đang có trong danh sách
void displayList(DoublyLinkedList list) {
    Node* temp = list.head;
    cout << "Danh sach lien ket kep: ";
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Hàm đếm số lượng phần tử trong danh sách liên kết kép
int countNodes(DoublyLinkedList list) {
    int count = 0;
    Node* temp = list.head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Hàm kết hợp hai danh sách liên kết kép thành một danh sách duy nhất
DoublyLinkedList mergeLists(DoublyLinkedList list1, DoublyLinkedList list2) {
    if (list1.head == NULL) return list2;
    if (list2.head == NULL) return list1;
    list1.tail->next = list2.head;
    list2.head->prev = list1.tail;
    list1.tail = list2.tail;
    return list1;
}

// Hàm xoá toàn bộ phần tử danh sách liên kết kép
void deleteAllNodes(DoublyLinkedList& list) {
    Node* temp = list.head;
    while (temp != NULL) {
        Node* next = temp->next;
        delete temp;
        temp = next;
    }
    list.head = list.tail = NULL;
    cout << "Da xoa toan bo phan tu trong danh sach.\n";
}

// Hàm menu lựa chọn
void menu() {
    DoublyLinkedList list1, list2, mergedList;
    int choice;
    do {
        cout << "------------------------------\n";
        cout << "1. Nhap danh sach\n";
        cout << "2. Xuat danh sach\n";
        cout << "3. Them phan tu vao cuoi danh sach\n";
        cout << "4. Dem so luong phan tu trong danh sach\n";
        cout << "5. Ket hop hai danh sach\n";
        cout << "6. Xoa toan bo phan tu trong danh sach\n";
        cout << "0. Thoat\n";
        cout << "Lua chon cua ban: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Nhap danh sach 1:\n";
            inputList(list1);
            break;
        case 2:
            displayList(list1);
            break;
        case 3: {
            int value;
            cout << "Nhap gia tri can them: ";
            cin >> value;
            append(list1, value);
            break;
        }
        case 4:
            cout << "So luong phan tu trong danh sach: " << countNodes(list1) << endl;
            break;
        case 5:
            cout << "Nhap danh sach 2:\n";
            inputList(list2);
            mergedList = mergeLists(list1, list2);
            cout << "Danh sach sau khi ket hop:\n";
            displayList(mergedList);
            break;
        case 6:
            deleteAllNodes(list1);
            break;
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
