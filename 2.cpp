#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct LinkedList {
    Node* head;
    LinkedList() {
        head = nullptr;
    }

    // Hàm thêm phần tử vào cuối danh sách liên kết đơn
    void append(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    // Hàm thêm phần tử vào đầu danh sách liên kết đơn
    void prepend(int value) {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = head;
        head = newNode;
    }

    // Hàm xuất các giá trị đang có trong danh sách ra màn hình
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Hàm sắp xếp danh sách liên kết đơn tăng dần
    void sortAscending() {
        if (head == nullptr) return;
        Node* i = head;
        while (i != nullptr) {
            Node* j = i->next;
            while (j != nullptr) {
                if (i->data > j->data) {
                    swap(i->data, j->data);
                }
                j = j->next;
            }
            i = i->next;
        }
    }

    // Hàm sắp xếp danh sách liên kết đơn giảm dần
    void sortDescending() {
        if (head == nullptr) return;
        Node* i = head;
        while (i != nullptr) {
            Node* j = i->next;
            while (j != nullptr) {
                if (i->data < j->data) {
                    swap(i->data, j->data);
                }
                j = j->next;
            }
            i = i->next;
        }
    }
};
int main() {
    LinkedList list;
    int choice, n, value;

    while (true) {
        cout << "Menu:\n";
        cout << "1. Nhập số lượng phần tử và dãy số liên tiếp\n";
        cout << "2. Xuất danh sách\n";
        cout << "3. Thêm phần tử vào cuối danh sách\n";
        cout << "4. Thêm phần tử vào đầu danh sách\n";
        cout << "5. Sắp xếp danh sách tăng dần\n";
        cout << "6. Sắp xếp danh sách giảm dần\n";
        cout << "7. Thoát\n";
        cout << "Nhập lựa chọn của bạn: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Nhập số lượng phần tử: ";
            cin >> n;
            cout << "Nhập dãy số liên tiếp: ";
            for (int i = 0; i < n; i++) {
                cin >> value;
                list.append(value);
            }
            break;
        case 2:
            cout << "Danh sách hiện tại: ";
            list.display();
            break;
        case 3:
            cout << "Nhập giá trị cần thêm vào cuối danh sách: ";
            cin >> value;
            list.append(value);
            break;
        case 4:
            cout << "Nhập giá trị cần thêm vào đầu danh sách: ";
            cin >> value;
            list.prepend(value);
            break;
        case 5:
            list.sortAscending();
            cout << "Danh sách sau khi sắp xếp tăng dần: ";
            list.display();
            break;
        case 6:
            list.sortDescending();
            cout << "Danh sách sau khi sắp xếp giảm dần: ";
            list.display();
            break;
        case 7:
            cout << "Thoát chương trình.\n";
            return 0;
        default:
            cout << "Lựa chọn không hợp lệ, vui lòng chọn lại.\n";
        }

    }
    system("Pause");
    return 0;
}
