/// algorithm to reversed a singly linked list. for practice
#include <iostream>

using namespace std;

struct node {
    int val;
    struct node* next;
};

void print_list(node * head) {
    node * cur = head;
    while (cur != NULL) {
	cout << cur->val << endl;
	cur = cur->next;
    }
}

struct node * reverse_recursive(node * ptr, node * prev) {
    if (ptr->next == NULL) { /// base case, tail
	ptr->next = prev;
	return ptr;
    } else {
	node * tmp = reverse_list(ptr->next, ptr);
	ptr->next = prev;
	return tmp;
    }
}

int main(int argc, char** argv) {
    node * head;
    node * tail;
    const int LIST_SZ = 10;

    for (int i = 0; i < LIST_SZ; i++) {
	if (i == 0) {
	    head = new node;
	    tail = head;
	} else {
	    tail->next = new node;
	    tail = tail->next;
	}
	
	tail->val = i;
	tail->next = NULL;
    }
    
    head = reverse_recursive(head, NULL);
    print_list(head);

    return 0;
}
