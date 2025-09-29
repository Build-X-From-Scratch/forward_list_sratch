#include <iostream>
struct Node{
    int x;
    Node* next;
    Node(int val){
        this->x = val;
        this->next = nullptr;
    }
};
//helper merge
Node* merge(Node* left,Node* right){
    //base case jika salah satu list sudah habis
    if(!left){return right;}
    if(!right){return left;}


    Node* result = nullptr;
    if(left->x <= right->x){
        result = left;
        result->next = merge(left->next,right);
    }else {
        result = right;
        result->next = merge(left,right->next);
    }
    return result;
}
//helper get middle
Node* getMiddle(Node* head){
    if(!head){
        return head;
    }
    Node* slow = head;
    Node* fast = head->next;
    while(fast && fast->next){//fast != nullptr && fast->next != nullptr    
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

Node* merge_sort(Node* head){
    if(!head || !head->next){
        return head;
    }
    //1.cari middle 
    //belah list
    Node* middle = getMiddle(head);
    Node* nextMiddle = middle->next;
    //putuskan list menjadi 2 bagian    
    middle->next = nullptr;

    //2.rekursif sort
    Node* left = merge_sort(head);
    Node* right = merge_sort(nextMiddle);


    return merge(left,right);
}
void print(Node* head){
    Node* curr = head;
    while(curr != nullptr){
        std::cout << curr->x << "  " ;
        curr = curr->next;
    }
}
int main(){
    Node* head = new Node(3);
    head->next = new Node(2);
    head->next->next = new Node(1);
    head = merge_sort(head);
    print(head);
    std::cin.get();
    return 0;
}