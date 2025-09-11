#include <iostream>
template<typename T>
class forward_list{
    private:
        struct Node{
            T data;
            Node* next;
            Node(const T& data){
                this->data = data;
                this->next = nullptr;
            }
        };
    private:
        Node* head;
    public:
        forward_list(){
            this->head = nullptr;
        }
        private:
        class Iterator{
            private:
                Node* node; //pointer untuk memegang alamat data
            public:
                //buat constructor
                Iterator(Node* n) : node(n) {}
                T& operator*(){ //deferennce
                    return node->data;
                }
                /**
                 * @brief pre increment
                 * cara kerja:
                 * geser iterator ke element berikutnya
                 * lalu kembali diri sendiri(*this)
                 */
                Iterator& operator++(){
                    if(node) node = node->next;
                    return *this;
                }
                /**
                 * @brief pos increment
                 * cara kerja:
                 * simpan iterator lama
                 * geser iterator ke element berikut nya
                 * kembalikan dalam salin kondisi lama
                 */
                Iterator operator++(int){
                    Iterator temp = *this; //simpan keadaan lama
                    ++(*this); //pre increment untuk geser
                    return temp;//kembalikan keadaan sebelum di geser
                }
                bool operator!=(const Iterator& others)const{
                    return node != others.node;
                }
        };  
    public:
        Iterator begin(){
            return Iterator(head);
        }
        Iterator end(){
            return Iterator(nullptr);
        }
    public:
        void push(const T& data){
            Node* new_node = new Node(data);
            new_node->next = head;
            head = new_node;
        }
        void deleteAtFront(){
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        void deleteAtEnd(){
            Node* temp = head;
            if(head == nullptr){
                return;
            }
            if(head->next == nullptr){
                delete head;
                return;
            }
            //1 2 3 4 5
            while(temp->next->next != nullptr){ //temukan element 
                temp = temp->next;
            }
            delete temp->next; //delete node setelah tempp
            temp->next = nullptr; ///set nullptr untuk node setelah temp
        }       
};
int main(){
    // Your code here
    /**
     * std::list<int>lst
     * while(lst.begin != lst.end)
     */
    forward_list<int>fl;
    fl.push(1);
    fl.push(2);
    fl.push(3);
    for(auto it = fl.begin();it != fl.end();++it){
        std::cout << *it << " " << std::endl;
    }
    for(auto x: fl){
        std::cout << x << " ";
    }
    std::cin.get();
    return 0;
}