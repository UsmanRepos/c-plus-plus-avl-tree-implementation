#include<iostream>
using namespace std;

struct Avl_Node
{
	int data;
	Avl_Node* lptr;
	Avl_Node* rptr;
};	

int  avl_height(Avl_Node* node);
int  avl_balanceFactor(Avl_Node* node);
Avl_Node* avl_rrRotation(Avl_Node* node);
Avl_Node* avl_llRotation(Avl_Node* node);
Avl_Node* avl_lrRotation(Avl_Node* node);
Avl_Node* avl_rlRotation(Avl_Node* node);
Avl_Node* avl_Balance(Avl_Node* node);
Avl_Node* avl_Insertion(Avl_Node* node, int data);
void Traverse_inorder(Avl_Node* node);
void Traverse_preorder(Avl_Node* node);
void Traverse_postorder(Avl_Node* node);

int avl_height(Avl_Node* node)
{
	int height = 0;
	int l_height, r_height;

	if (node != NULL)
	{
		l_height = avl_height(node->lptr);
		r_height = avl_height(node->rptr);

		if (l_height > r_height)
			height = l_height + 1;
		else
			height = r_height + 1;
	}
	return height;
}
int avl_balanceFactor(Avl_Node* node)
{
	int b_factor = 0;
	int l_height, r_height;

	l_height = avl_height(node->lptr);
	r_height = avl_height(node->rptr);

	b_factor = l_height - r_height;

	return b_factor;
}
Avl_Node* avl_rrRotation(Avl_Node* node)//anticlockwise
{
	Avl_Node* temp;

	temp = node->rptr;
	node->rptr = temp->lptr;
	temp->lptr = node;

	return temp;

}

Avl_Node* avl_llRotation(Avl_Node* node)//clockwise
{
	Avl_Node* temp;

	temp = node->lptr;
	node->lptr = temp->rptr;
	temp->rptr = node;

	return temp;
}
Avl_Node* avl_lrRotation(Avl_Node* node)
{
	Avl_Node* temp;

	temp = node->lptr;
	node->lptr = avl_rrRotation(temp);
	
	return avl_llRotation(node);
}
Avl_Node* avl_rlRotation(Avl_Node* node)
{
	Avl_Node* temp;

	temp = node->rptr;
	node->lptr = avl_llRotation(temp);

	return avl_rrRotation(node);
}
Avl_Node* avl_Balance(Avl_Node* node)
{
	int b_factor = avl_balanceFactor(node);
	if (b_factor > 1)
	{
		if (avl_balanceFactor(node->lptr) > 0)
			node = avl_llRotation(node);
		else
			node = avl_lrRotation(node);
	}
	if (b_factor < -1)
	{
		if (avl_balanceFactor(node->rptr) > 0)
			node = avl_rlRotation(node);
		else
			node = avl_rrRotation(node);
	}
	return node;
}
Avl_Node* avl_Insertion(Avl_Node* node, int data)
{
	if (node == NULL)
	{
		Avl_Node* r = new Avl_Node;
		r->data = data;
		r->lptr = r->rptr = NULL;
		return r;
	}
	else
	{
		if (data < node->data)
		{
			node->lptr = avl_Insertion(node->lptr, data);
			node = avl_Balance(node);
		}
		else
		{
			node->rptr = avl_Insertion(node->rptr, data);
			node = avl_Balance(node);
		}
		return node;
	}
}
void Traverse_inorder(Avl_Node* node)
{
	if (node != NULL)
	{
		Traverse_inorder(node->lptr);
		cout << node->data << " ";
		Traverse_inorder(node->rptr);
	}
	
}
void Traverse_preorder(Avl_Node* node)
{
	if (node != NULL)
	{
		cout << node->data << " ";
		Traverse_preorder(node->lptr);
		Traverse_preorder(node->rptr);
	}
	
}
void Traverse_postorder(Avl_Node* node)
{
	if (node != NULL)
	{
		Traverse_postorder(node->lptr);
		Traverse_postorder(node->rptr);
		cout << node->data << " ";
	}
}
int main()
{
	Avl_Node* root = NULL;
	int ch, data;

	while (true)
	{
		cout << "----------(MAIN Menu)-----------\n";
		cout << "1) Insertion\n";
		cout << "2) Traversing\n";
		cout << "3) Exit\n";
		cout << "Enter Choice: ";
		cin >> ch;

		switch (ch)
		{
		case 1:
			cout << "Enter Data: ";
			cin >> data;
			root = avl_Insertion(root, data);
			break;
		case 2:
			Traverse_inorder(root);
			cout << endl;
			Traverse_preorder(root);
			cout << endl;
			Traverse_postorder(root);
			cout << endl;
			break;
		case 3:
			exit(-1);
		}
	}
}