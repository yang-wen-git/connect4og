#include <iostream>

struct Node {
    std::string name;
    int age;
    Node* next;
};

Node* copy_vent(Node* &head);
void final_vent(Node* &head);
int main() {
    Node* head = new Node;
    std::string names[5] = {"Akiko", "Asa", "Minami", "Naho", "Yukiko"};
    int ages[5] = {21, 20, 25, 23, 22};
    Node* iter = head;
    for (int i = 0; i < 5; i++) {
        iter -> name = names[i];
        iter -> age = ages[i];
        if (i == 4) {
            iter -> next = nullptr;
        } else {
            iter -> next = new Node;
        }  
        iter = iter -> next;
    }
    iter = head;
    while (iter!=nullptr) {
        std::cout << iter -> name << ' ' << iter -> age << ", ";
        iter = iter -> next;
    }
    std::cout << std::endl;
    iter = head;
    Node *head2 = copy_vent(head);
    // Node *copy_head = new Node;
    // Node *copy_iter = copy_head;
    // while (iter != nullptr) {
    //     copy_iter -> name = iter -> name;
    //     copy_iter -> age = iter -> age;
    //     if (iter -> next == nullptr) {
    //         copy_iter -> next = nullptr;
    //     } else {
    //         copy_iter -> next = new Node;
    //     }
    //     iter = iter -> next;
    //     copy_iter = copy_iter -> next;
    // }
    // iter = head;
    // copy_iter = copy_head;
    Node* copy_iter = head2;
    while (copy_iter!=nullptr) {
        std::cout << copy_iter -> name << ' ' << copy_iter -> age << ", ";
        copy_iter = copy_iter -> next;
    }
    std::cout << std::endl;

    iter -> name = "Akane";
    while (iter!=nullptr) {
        std::cout << iter -> name << ' ' << iter -> age << ", ";
        iter = iter -> next;
    }
    std::cout << std::endl;
    copy_iter = head2;
    while (copy_iter!=nullptr) {
        std::cout << copy_iter -> name << ' ' << copy_iter -> age << ", ";
        copy_iter = copy_iter -> next;
    }
    std::cout << std::endl;
    final_vent(head);
    final_vent(head2);
    return 0;
}

Node* copy_vent(Node* &head) {
    Node* iter = head;
    Node* copy_head = new Node;
    Node* copy_iter = copy_head;
    while (iter != nullptr) {
        copy_iter -> name = iter -> name;
        copy_iter -> age = iter -> age;
        if (iter -> next == nullptr) {
            copy_iter -> next = nullptr;
        } else {
            copy_iter -> next = new Node;
        }
        iter = iter -> next;
        copy_iter = copy_iter -> next;
    }
    return copy_head;
}

void final_vent(Node* &head) {
    Node* iter = head;
    while (iter != nullptr) {
        head = iter -> next;
        delete iter;
        iter = head;
    }
}