// C++ program to sort Linked List 
// using Bubble Sort

#include <iostream>
using namespace std;

class Node {
  public:
    int data;
    Node *next;
    Node(int x) {
        data = x;
        next = nullptr;
    }
};

// Function to get the length
// of the linked list
int getLength(Node *head) {
    int len = 0;
    Node *curr = head;
    while (curr != nullptr) {
        len++;
        curr = curr->next;
    }
    return len;
}

// Function to perform bubble sort on 
// the linked list
Node *bubbleSort(Node *head) {
    Node *currNode = head;
    int len = getLength(head);
    int itr = 0;
    bool swapped;

    // Iterating over the whole linked list
    while (itr < len) {
        Node *traverseNode = head;
        Node *prevNode = head;
        swapped = false;

        while (traverseNode->next) {

            // Temporary pointer to store the next
            // pointer of traverseNode
            Node *ptr = traverseNode->next;
            if (traverseNode->data > ptr->data) {
                swapped = true;
                if (traverseNode == head) {

                    // Performing swap operations and
                    // updating the head of the linked list
                    traverseNode->next = ptr->next;
                    ptr->next = traverseNode;
                    prevNode = ptr;
                    head = prevNode;
                }
                else {

                    // Performing swap operation
                    traverseNode->next = ptr->next;
                    ptr->next = traverseNode;
                    prevNode->next = ptr;
                    prevNode = ptr;
                }
                continue;
            }
            prevNode = traverseNode;
            traverseNode = traverseNode->next;
        }

        // If no swap occurred, break the loop
        if (!swapped) {
            break;
        }

        ++itr;
    }

    // Returning the head of the linked list
    return head;
}

void printList(Node *curr) {
    while (curr != nullptr) {
        cout << curr->data << " ";
        curr = curr->next;
    }
}

int main() {
      
      // Create a hard-coded linked list:
    // 5 -> 1 -> 32 -> 10 -> 78
    Node *head = new Node(5);
    head->next = new Node(1);
    head->next->next = new Node(32);
    head->next->next->next = new Node(10);
    head->next->next->next->next = new Node(78);
  
    head = bubbleSort(head);
    printList(head);

    return 0;
}
