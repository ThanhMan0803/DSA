#include<iostream>
using namespace std;
struct node
{
	int value;
	node* next;
};
void init(node*& head)
{
	head = NULL;
}
node* createNode(int x)
{
	node* p = new node;
	p->value = x;
	p->next = NULL;
	return p;
}
void addFirst(node*& head, int x)
{
	node* p = createNode(x);
	p->next = head;
	head = p;
}
void addAfter(node* head, int v, int x)
{
	node* p = createNode(x);
	node* q = head;
	while (q!=NULL&&q->value != v)
		q = q->next;
	if (q != NULL)
	{
		p->next = q->next;
		q->next = p;
	}
}
void addLast(node*& head, int x)
{
	node* p = createNode(x);
	if (head == NULL)
	{
		head = p;
	}
	else
	{
		node* p = createNode(x);
		node* last = head;
		while (last->next != NULL)
			last = last->next;
		last->next = p;
	}
}
void output(node* head)
{
	node* p = head;
	while (p != NULL) {
		cout << p->value << " ";
		p = p->next;
	}
	cout << endl;
}
void sortAscending(node *&head) {
	if (head == nullptr) return;
	node* i = head;
	while (i != nullptr) {
		node* j = i->next;
		while (j != nullptr) {
			if (i->value > j->value) {
				swap(i->value, j->value);
			}
			j = j->next;
		}
		i = i->next;
	}
}
int main()
{
	node* head;
	init(head);
	int value;
	int n;
	int choice;
	while (true)
	{
		cout << "===============================================" << endl;
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
		switch (choice)
		{
		case 1:
			cout << "Nhap sl: ";
			cin >> n;
			for (int i = 0; i < n; i++)
			{
				cout << "Nhap gia tri thu " << i + 1 << " :";
				cin >> value;
				addLast(head,value );
				
			}
			break;
		case 2:
			cout << "DSLK: ";
			output(head);
			break;
		case 7:
			cout << "Thoat!" << endl;
			return 0;
		default:
			cout << "Vui long chon lai";
		
		}

	}
	system("Pause");
	return 0;
}