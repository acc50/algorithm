#include <iostream>
#include <random>
#include <cassert>
//#include "treePrint.h"

using namespace std;

random_device rd;
default_random_engine dre(rd());
uniform_int_distribution <int> uid(100, 1000);

enum Color {
	Color_Red,
	Color_Black
};

struct Node {
	int data;
	int color;
	Node *left;
	Node *right;
	Node *parent;
};

void check_tree_recursion(struct Node *p, struct Node *NIL, int B_sofar, int B_total) {

	if (p == NIL) {

		assert(B_sofar == B_total);

		return;

	}



	check_tree_recursion(p->left, NIL, B_sofar + (p->left && p->left->color), B_total);

	check_tree_recursion(p->right, NIL, B_sofar + (p->right && p->right->color), B_total);

	if (p->left)

		assert(!(!p->left->color && !p->color));

	if (p->right)

		assert(!(!p->right->color && !p->color));

}



void check_tree(struct Node *root, struct Node *NIL) {

	int cnt = 0;

	struct Node *p;

	if (root == NIL) return;

	//root->color = BLACK;

	for (p = root; p != NIL; p = p->left)

		cnt += p->color;

	check_tree_recursion(root, NIL, 0, cnt);

}

void Check_PrintAll(struct Node *node, struct Node *NIL)
{
	if (node == NIL)
		cout << "NIL " << endl << endl;

	else if (node != NIL) {

		cout << "���� ����" << endl;
		Check_PrintAll(node->left, NIL);

		cout << node->data << " ";

		if (node->color == Color_Red)
			cout << "RED" << endl << endl;
		else
			cout << "Black" << endl << endl;

		cout << "������ ����" << endl;
		Check_PrintAll(node->right, NIL);
	}

}

void PrintAll(struct Node *node, struct Node *NIL)
{

	if (node != NIL) {

		PrintAll(node->left, NIL);
		cout << node->data << " ";
		PrintAll(node->right, NIL);
	}

}

void Tree_Rotation(struct Node *node, struct Node *Parent, struct Node *&root, int type)		// pivot, pivot�� �θ�, root�� ����, ȸ������
{
	if (type == 1) {				// ������
		Parent->left = node->right;
		node->right = Parent;
		node->parent = Parent->parent;

		if (Parent->parent != nullptr) {				// ȸ���� ��Ʈ��尡 ������ ����
			if (Parent == Parent->parent->left) {	//�θ��尡 �� �θ����� ����
				Parent->parent->left = node;
			}
			else {
				Parent->parent->right = node;
			}
		}
		else {					// node �� ��Ʈ��尡 ��
			root = node;
		}

		Parent->parent = node;
		Parent->left->parent = Parent;
	}

	else {							// ���� ȸ��

		Parent->right = node->left;
		node->left = Parent;
		node->parent = Parent->parent;

		if (Parent->parent != nullptr) {
			if (Parent == Parent->parent->left) {		// �θ��尡 �� �θ����� �����̸�
				Parent->parent->left = node;
			}
			else {
				Parent->parent->right = node;
			}
		}
		else {					// node �� ��Ʈ��尡 ��
			root = node;
		}

		Parent->parent = node;
		Parent->right->parent = Parent;
	}
}

void RB_Insert(struct Node *node, struct Node *Parent, struct Node *&root)
{
	if (Parent == nullptr) {					// ��Ʈ���
		node->color = Color_Black;
	}

	else if (Parent->parent == nullptr) {		// ��Ʈ���  �ڽĳ�� ����
		node->color = Color_Red;
	}

	else {						// ��Ʈ����� �ڽĳ�尡 �ƴ�

		if (Parent->color == Color_Black) {		// �θ��尡 ��
			node->color = Color_Red;
		}

		else {		// ��Ʈ����� �ڽĳ�尡 �ƴϰ� �θ��尡 ����

			if (Parent == Parent->parent->left) {			// �θ��尡 �� �θ����� ����
				if (Parent->parent->right->color == Color_Red) {	// Case 1
					Parent->color = Color_Black;					// p = ������
					Parent->parent->right->color = Color_Black;		// s  = ������
					Parent->parent->color = Color_Red;

					// ���
					RB_Insert(Parent->parent, Parent->parent->parent, root);	// p' �� ���� �˻�
				}

				else if (Parent->parent->right->color == Color_Black) {	// Case 2
					if (node == Parent->right) {
						// x ���� ����ȸ��
						Tree_Rotation(node, Parent, root, 2);
						// x ���� ������ȸ��
						Tree_Rotation(node, node->parent, root, 1);
						node->color = Color_Black;
						node->right->color = Color_Red;
					}

					else if (node == Parent->left) {
						// p ���� ������ȸ��
						// p = ��, p' ����� �ٲ�
						Tree_Rotation(Parent, Parent->parent, root, 1);
						Parent->color = Color_Black;
						Parent->right->color = Color_Red;
					}
				}

			}

			else if (Parent == Parent->parent->right) {		// �θ��尡 �� �θ����� ������
				if (Parent->parent->left->color == Color_Red) {	// Case 1
					Parent->color = Color_Black;
					Parent->parent->left->color = Color_Black;
					Parent->parent->color = Color_Red;
					// ���
					RB_Insert(Parent->parent, Parent->parent->parent, root);	// p' �� ���� �˻�
				}

				else if (Parent->parent->left->color == Color_Black) {	// Case 2

					if (node == Parent->right) {			//  �����ϴ� ��尡 �θ����� ������
															// p ���� ����ȸ��
															// p = ��, p' ����� �ٲ�
						Tree_Rotation(Parent, Parent->parent, root, 2);
						Parent->color = Color_Black;
						Parent->left->color = Color_Red;
					}

					else if (node == Parent->left) {		//  �����ϴ� ��尡 �θ����� ����
															// x ���� ������ȸ��
						Tree_Rotation(node, Parent, root, 1);
						// x ���� ���� ȸ��
						Tree_Rotation(node, node->parent, root, 2);
						node->color = Color_Black;
						node->left->color = Color_Red;
					}
				}

			}

		}		// �θ��尡 �� �θ����� �������� ���

	}
}

void Insert(struct Node *node, struct Node *new_node, struct Node *NIL, struct Node *&root)	// root, node, NIL�� ���纻  root�� ���� ����
{
	if (root == nullptr)		// ��Ʈ�� ���������
		root = new_node;

	else {
		if (new_node->data <= node->data) {		// ���ο� ����� �����Ͱ� ���ϴ� ��庸�� ����
			if (node->left == NIL) {		// ����� ������ ���������
				node->left = new_node;
				new_node->parent = node;
				RB_Insert(new_node, new_node->parent, root);
			}
			else {
				Insert(node->left, new_node, NIL, root);
			}
		}

		else if (new_node->data > node->data) {		// ���ο� ����� �����Ͱ� ���ϴ� ��庸�� ŭ
			if (node->right == NIL) {
				node->right = new_node;
				new_node->parent = node;
				RB_Insert(new_node, new_node->parent, root);
			}
			else {
				Insert(node->right, new_node, NIL, root);
			}
		}
	}
}

void RB_Delete_Red(struct Node *node, struct Node *NIL, bool &red_check)	// ������� Ȥ�� �ڽĳ�尡 ����, ���� ���� �� ������ �Ѿ
{
	if (node->color == Color_Black) {
		if (node->left != NIL) {	// �ڽĳ��� ����
			if (node->left->color == Color_Red) {
				node->left->color = Color_Black;
				cout << "���� ����" << endl;
				red_check = true;
			}
		}
		else {
			if (node->right->color == Color_Red) {
				node->right->color = Color_Black;
				cout << "���� ����" << endl;
				red_check = true;
			}
		}
	}
}

void RB_Delete_Black(struct Node *node, struct Node *Parent, struct Node *&root)	// ������ �� ������ ����� �ڽĳ��, �� �θ���  2-1, 2-4, 1-1, *-3, *-2 ������ ó��
{
	if (node == Parent->left) {		// x �� p�� ����

		struct Node *x = node;
		struct Node *s = Parent->right;
		struct Node *l = Parent->right->left;
		struct Node *r = Parent->right->right;
		int Color_temp = Color_Black;

		if (Parent->color == Color_Black && s->color == Color_Black &&
			l->color == Color_Black && r->color == Color_Black)  // 2-1
		{
			s->color = Color_Red;
			cout << "case 2-1" << endl;
			RB_Delete_Black(Parent, Parent->parent, root);	// Parent �� ����Լ��� x�� ��
		}

		else if (Parent->color == Color_Black && s->color == Color_Red &&
			l->color == Color_Black && r->color == Color_Black) // 2-4
		{
			Tree_Rotation(s, Parent, root, 2);		// s, p ���� ȸ��
			Color_temp = Parent->color;
			Parent->color = s->color;
			s->color = Color_temp;				// p, s ���� �ٲٱ�
			cout << "case 2-4" << endl;
			RB_Delete_Black(x, Parent, root);		// ���̽� 1�� �������� ���
		}

		else if (Parent->color == Color_Red && l->color == Color_Black &&
			r->color == Color_Black)	// 1-1		p = red, s,l,r = black
		{
			Color_temp = Parent->color;
			Parent->color = s->color;
			s->color = Color_temp;			// p, s ���� �ٲٱ�
			cout << "case 1-1" << endl;
		}

		else if (s->color == Color_Black && r->color == Color_Red) // *-2		s = black r = red
		{
			Tree_Rotation(s, Parent, root, 2);		// s, p ����ȸ��
			Color_temp = Parent->color;
			Parent->color = s->color;
			s->color = Color_temp;			// p, s ���� �ٲٱ�
			r->color = Color_Black;
			cout << "case *-2" << endl;
		}

		else if (s->color == Color_Black && r->color == Color_Black &&
			l->color == Color_Red) // *-3
		{
			Tree_Rotation(l, s, root, 1);		// l, s ������ ȸ��
			Color_temp = l->color;
			l->color = s->color;
			s->color = Color_temp;		// l, s ���� �ٲٱ�
			cout << "case *-3" << endl;
			RB_Delete_Black(x, Parent, root);		// *-2 �� �Ѿ���� ��
		}
	}

	else {					// x �� Parent �� ������
		struct Node *x = node;
		struct Node *s = Parent->left;
		struct Node *l = Parent->left->left;
		struct Node *r = Parent->left->right;
		int Color_temp = Color_Black;

		if (Parent->color == Color_Black && s->color == Color_Black &&
			l->color == Color_Black && r->color == Color_Black)  // 2-1
		{
			s->color = Color_Red;
			cout << "case 2-1" << endl;
			RB_Delete_Black(Parent, Parent->parent, root);	// Parent �� ����Լ��� x�� ��
		}

		else if (Parent->color == Color_Black && s->color == Color_Red &&
			l->color == Color_Black && r->color == Color_Black) // 2-4
		{
			Tree_Rotation(s, Parent, root, 1);		// s, p ������ ȸ��
			Color_temp = Parent->color;
			Parent->color = s->color;
			s->color = Color_temp;				// p, s ���� �ٲٱ�
			cout << "case 2-4" << endl;
			RB_Delete_Black(x, Parent, root);		// ���̽� 1�� �������� ���
		}

		else if (Parent->color == Color_Red && l->color == Color_Black &&
			r->color == Color_Black)	// 1-1		p = red, s,l,r = black
		{
			Color_temp = Parent->color;
			Parent->color = s->color;
			s->color = Color_temp;			// p, s ���� �ٲٱ�
			cout << "case 1-1" << endl;
		}

		else if (s->color == Color_Black && l->color == Color_Red) // *-2		s = black l = red
		{
			Tree_Rotation(s, Parent, root, 1);		// s, p ������ȸ��
			Color_temp = Parent->color;
			Parent->color = s->color;
			s->color = Color_temp;			// p, s ���� �ٲٱ�
			l->color = Color_Black;
			cout << "case *-2" << endl;
		}

		else if (s->color == Color_Black && l->color == Color_Black &&			// s = black , l=black, r=red
			r->color == Color_Red) // *-3
		{
			Tree_Rotation(r, s, root, 2);		// r, s ���� ȸ��
			Color_temp = r->color;
			r->color = s->color;
			s->color = Color_temp;		// l, s ���� �ٲٱ�
			cout << "case *-3" << endl;
			RB_Delete_Black(x, Parent, root);		// *-2 �� �Ѿ���� ��
		}
	}
}

void DeleteNode(struct Node *node, struct Node *NIL, struct Node *&root)
{
	bool red_check = false;

	if (node->left == NIL && node->right == NIL) {		// �ڽĳ�� X
		if (node->parent->left == node) {		// ������� ��尡 �θ����� ����
			RB_Delete_Red(node, NIL, red_check);
			node->parent->left = NIL;
			if(node->color == Color_Black && !red_check)
				RB_Delete_Black(node->parent->left, node->parent, root);	// NIL �� x, Parent �� p�� ��
			delete node;
		}

		else {
			RB_Delete_Red(node, NIL, red_check);
			node->parent->right = NIL;
			if (node->color == Color_Black && !red_check)
				RB_Delete_Black(node->parent->right, node->parent, root);	// NIL �� x, Parent �� p�� ��
			delete node;
		}
	}

	else if (node->left != NIL && node->right != NIL) {		// �ڽĳ�� 2��

		struct Node *temp = node->right;		// ���� ���

		while (temp->left != NIL) {			// temp �� ����� ���� ������ ã�ư�
			temp = temp->left;
		}

		node->data = temp->data;

		if (temp->parent->left == temp) {	// ������ ��尡 �� �θ����� ����
			if (temp->right == NIL) {				// temp -> right�� NIL �̸�		�ڽ� x
				RB_Delete_Red(temp, NIL, red_check);
				temp->parent->left = NIL;
				if (temp->color == Color_Black && !red_check)
					RB_Delete_Black(temp->parent->left, temp->parent, root);	// NIL�� x, temp->parent �� p
			}

			else if (temp->right != NIL) {			// temp->right �� �ִٸ�
				RB_Delete_Red(temp, NIL, red_check);
				temp->parent->left = temp->right;
				temp->right->parent = temp->parent;
				if (temp->color == Color_Black && temp->right->color == Color_Black && !red_check)
					RB_Delete_Black(temp->parent->left, temp->parent, root);	// temp�� right �� x, temp->parent �� p
			}
		}

		else if (temp->parent->right == temp) {	// ������ ��尡 �� �θ����� ������
			if (temp->right == NIL) {				// temp -> right�� NIL �̸�		�ڽ� x
				RB_Delete_Red(temp, NIL, red_check);
				temp->parent->right = NIL;
				if (temp->color == Color_Black && !red_check)
					RB_Delete_Black(temp->parent->right, temp->parent, root);	// NIL �� x, temp->parent �� p
			}

			else if (temp->right != NIL) {			// temp->right �� �ִٸ�
				RB_Delete_Red(temp, NIL, red_check);
				temp->parent->right = temp->right;
				temp->right->parent = temp->parent;
				if (temp->color == Color_Black && temp->right->color == Color_Black && !red_check)
					RB_Delete_Black(temp->parent->right, temp->parent, root);	// temp�� right �� x, temp->parent �� p
			}
		}

		delete temp;

	}

	else if (node->left != NIL || node->right != NIL) {
		if (node->parent->left == node) {		// ������� ��尡 �θ����� ����

			if (node->left != NIL) {			// ������� ����� ���� ��尡 ����
				RB_Delete_Red(node, NIL, red_check);
				node->parent->left = node->left;
				node->left->parent = node->parent;
				if (node->color == Color_Black && node->left->color == Color_Black && !red_check)
					RB_Delete_Black(node->left, node->parent, root);	// ����� ������x, ����� �θ� p
				delete node;
			}

			else {
				RB_Delete_Red(node, NIL, red_check);
				node->parent->left = node->right;
				node->right->parent = node->parent;
				if (node->color == Color_Black && node->right->color == Color_Black && !red_check)
					RB_Delete_Black(node->right, node->parent, root);	// ����� ��������x, ����� �θ� p
				delete node;
			}

		}

		else {					// ������� ��尡 �θ����� ������

			if (node->left != NIL) {			// ������� ����� ���� ��尡 ����
				RB_Delete_Red(node, NIL, red_check);
				node->parent->right = node->left;
				node->left->parent = node->parent;
				if (node->color == Color_Black && node->left->color == Color_Black && !red_check)
					RB_Delete_Black(node->left, node->parent, root);	// ����� ������x, ����� �θ� p
				delete node;
			}

			else {
				RB_Delete_Red(node, NIL, red_check);
				node->parent->right = node->right;
				node->right->parent = node->parent;
				if (node->color == Color_Black && node->right->color == Color_Black && !red_check)
					RB_Delete_Black(node->right, node->parent, root);	// ����� ��������x, ����� �θ� p
				delete node;
			}

		}
	}
}

void Delete(struct Node *node, struct Node *NIL, struct Node *&root, int key)
{
	if (node == NIL) {
		cout << "������� ���� �����ϴ�" << endl;
	}

	else {
		if (node->data == key) {
			DeleteNode(node, NIL, root);
		}

		else if (node->data > key) {				// �ش� ����� ���� ã�� ������ ŭ
			Delete(node->left, NIL, root, key);
		}

		else {
			Delete(node->right, NIL, root, key);
		}
	}
}

void Search(struct Node *root, int key)
{
	if (root == NULL) {
		cout << key << "�� ã�� ���߽��ϴ� " << endl;
	}

	else {
		if (root->data == key) {
			cout << key << " �� ã�ҽ��ϴ�" << endl;
		}

		else if (root->data <= key) {				// ��Ʈ�� �����Ͱ� ã�� ������ ������
			Search(root->right, key);
		}

		else if (root->data > key) {				// ��Ʈ�� �����Ͱ� ã�� ������ ũ��
			Search(root->left, key);
		}
	}
}

void DeleteAll(struct Node *node, struct Node *NIL)
{
	if (node != NIL) {

		DeleteAll(node->left, NIL);
		DeleteAll(node->right, NIL);
		cout << node->data << "����" << endl;
		delete node;
	}
}

int main()
{
	struct Node *NIL = new Node;

	NIL->left = nullptr;
	NIL->right = nullptr;
	NIL->parent = nullptr;
	NIL->data = -1;
	NIL->color = Color_Black;

	int n = 0;
	int loop = 1;
	while (loop) {
		cout << "�ڷ��� ������ �Է��Ͻÿ�: ";
		cin >> n;

		if (n >= 1)
			loop = 0;
	}

	struct Node *root = nullptr;

	for (int i = 0; i < n; i++) {

		struct Node *node = new Node;
		node->left = NIL;
		node->right = NIL;
		node->parent = nullptr;
		node->color = Color_Red;
		node->data = uid(dre);				// ����� �ʱ�ȭ

		cout << node->data << "����" << endl;

		Insert(root, node, NIL, root);		// ��Ʈ���� ��ȸ�ؼ� ���ο� ���� ��, NIL�� ������ ���, root�� �׻� Ʈ���� �Ӹ��� ����Ŵ

		cout << "��Ʈ�� ���� : " << root->data << endl << endl;
	}


	cout << "���� ��ȸ: " << endl;
	Check_PrintAll(root, NIL);
	cout << endl;

	char command;
	int search_data = -1;
	int input_data = 0;
	struct Node *parent = new Node;
	parent = root;

	loop = 1;
	while (loop) {

		cout << "��ɾ �Է��Ͻÿ�: (P : ���  S : �˻�  D : ����  I : ����  C : Ʈ�� üũ  Q : ����)";
		cin >> command;

		switch (command) {
		case 'P':

			PrintAll(root, NIL);
			cout << endl;


			cout << "��Ʈ�� �� : " << root->data << endl;
			//print_ascii_tree(ROOT);
			break;

		case 'C':

			check_tree(root, NIL);
			cout << "Ʈ�� ���� ����" << endl;
			break;

		case 'S':

			cout << "ã�� �����͸� �Է��Ͻÿ�: ";
			cin >> search_data;
			Search(root, search_data);
			break;

		case 'D':

			cout << "ã�� �����͸� �Է��Ͻÿ�: ";
			cin >> search_data;
			Delete(root, NIL, root, search_data);

			check_tree(root, NIL);
			cout << "Ʈ�� ���� ����" << endl;
			break;

		case 'Q':
			loop = 0;
			DeleteAll(root, NIL);

			break;

		default:
			cout << "���� ��ɾ��Դϴ�" << endl;
			cout << root->data << endl;
			break;

		case 'I':
			cout << "���� �Է��Ͻÿ�: ";
			cin >> input_data;

			struct Node *node = new Node;
			node->left = NIL;
			node->right = NIL;
			node->parent = nullptr;
			node->data = input_data;
			node->color = Color_Red;

			Insert(root, node, NIL, root);
			break;


		}
	}
}