#include <iostream>
#ifndef __forwardList
#define __forwardList
template <typename T>
class forward_lists{
    private:
        struct Node{
            T data;
            Node* next;
            Node(const T& data){
                this->data = data;
                this->next = nullptr;
            }
        };
        int size;
        Node* head;
    public:
        forward_lists(){
            this->head = nullptr;
            this->size = 0;
        }
        //copy constructor
        forward_lists(const forward_lists& others){
            if(*this == &others){
                return *this;
            }
            head = new Node(others.head->data); //inialisasi data pertama
            Node* curr = head; //pointer penggerak
            Node* temp = others.head->next;
            while(temp != nullptr){
                curr->next = new Node(temp->data);
                curr = curr->next;
                temp = temp->next;
            }
            return *this;
        }
        //copy assignment
        forward_lists& operator==(const forward_lists& others){
            if(this == &others){
                return *this;
            }
            clear();
            if(!others.head){ //nullptr
                head = nullptr;
                return *this;
            }
            head = new Node(others.head->data);
            Node* curr = head;
            Node* temp = others.head->next;
            while(temp != nullptr){
                curr->next = new Node(temp->data);
                curr = curr->next;
                temp = temp->next;
            }
            return *this;
        }
        ~forward_lists(){
            clear();
        }
    private:
        class Iterator{
            private:
                Node* node;
            public:
                Iterator(Node n){
                    this->node = n;
                }   
                Iterator& operator*(){
                    return node->data;
                }
                T& operator++(){
                    if(node) node = node->next;
                    return *this;
                }
                Iterator& operator++(int){
                    Iterator temp = *this; //simpan keadaan sebelum di geser
                    ++(*this);//geser
                    return temp; //kembalikan keadaan sebelum di geser
                }
                bool operator!=(const Iterator& others){
                    return node != others.node;
                }
        };
    public: //inialisasi Iterator
        Iterator begin(){
            return Iterator(head);
        }
        Iterator end(){
            return Iterator(nullptr);
        }
    public: //getter
        T front(){
            return head->data;
        }
        int get_size(){
            return this->size;
        }
    public:
        void push_front(const T& data){
            Node* new_node = new Node(data);
            new_node->next = head;
            head = new_node;
            size++;
        }
        void pop_front(){
            Node* temp = head;
            head = head->next;
            size--;
            delete temp;
        }
        /**
         * @brief insert after
         */
        void insert_after(T begin,T val){
            Node* curr = head;
            while(curr != val){
                curr = curr->next;
            }
            if(curr == nullptr){
                return;
            }
            Node* new_node = new_node(val);
            new_node->next = curr->next;
            curr->next  = new_node;
        }   
        void insert_after(T begin,int n,T val){
            Node* curr = head;
            while(curr != nullptr){
                curr = curr->next;
            }
            if(curr == nullptr){
                return;
            }
            if(n < 1){
                return;
            }
            if(n == 1){
                Node* new_node = new Node(val);
                new_node->next = curr->next;
                curr->next = new_node;
            }else{
                Node* new_node = new Node(val);
                Node* temp = new_node;
                for(int i = 0;i < n;i++){
                    Node* n_node = new Node(val);
                    new_node->next = n_node;
                }
                new_node->next = curr->next;
                curr->next = temp;
            }
        }
    public:
        void print_all(T begin,T end){
            while(begin != end){
                std::cout << *begin << " ";
                ++begin;
            }
            std::cout << std::endl;
        }
        void clear(){
            while(head != nullptr){
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
};

#endif