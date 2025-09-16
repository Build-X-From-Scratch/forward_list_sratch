#include <iostream>
#include <initializer_list>
#include <type_traits>
#include <iterator>
#ifndef __forwardList
#define __forwardList
template <typename T>
class forward_lists{
    private:
        struct Node{
            T data;
            Node* next;
            Node(const T& data = T{},Node* n = nullptr){
                this->data = data;
                this->next = n;
            }
        };
        int size;
        Node* head;
    public:
        forward_lists(){
            this->head = new Node(T{});
            this->head->next = nullptr;
            this->size = 0;
        }
        /**
         * @brief initializer list constructor
         * @details
         */
        forward_lists(std::initializer_list<T> arr): head(nullptr){
            head = new Node(T{});
            head->next = nullptr;
            size = 0;
            Node** curr = &head->next; //store alamat memory head ke curr
            for(const T& it: arr){
                *curr = new Node(it); //deference pointer
                //head = new Node(it) ->meaning
                curr = &((*curr)->next); //store alamat curr->next
               //curr = head->next
               //curr selalu menunjuk ke posisi kosong
               size++;
            }   
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
            Iterator(Node* n){
                this->node = n;
            }   
            friend std::ostream& operator<<(std::ostream& os,const Iterator& it){
                if(it.node){
                    os << it.node->data;
                }else{
                    os << "no output";
                }
                return os;
                }
                T& operator*(){
                    return node->data;
                }
                Iterator& operator++(){ //harus mengembalikan reference ke object saat ini
                    if(node) node = node->next;
                    return *this;
                }
                Iterator& operator->(){
                    return node;
                }
                Iterator operator++(int){ //harus mengambalikan salin bukan referensi
                    Iterator temp = *this; //simpan keadaan sebelum di geser
                    ++(*this);//geser
                    return temp; //kembalikan keadaan sebelum di geser
                }
                bool operator!=(const Iterator& others)const{
                    return node != others.node;
                }
                Node* get_raw()const{
                    return node;
                }
        };
    public: //inialisasi Iterator
        Iterator before_begin(){
            return Iterator(head);
        }
        Iterator begin(){
            return Iterator(head->next);
        }
        Iterator end(){
            return Iterator(nullptr);
        }
        Iterator cbegin()const{
            return Iterator(head->next);
        }
        Iterator cend()const{
            return Iterator(nullptr);
        }
        Iterator cbefore_begin()const{
            return Iterator(head);
        }
    public: //getter
        T front(){
            return head->next->data;
        }
        int get_size(){
            return this->size;
        }
        bool is_empty(){
            if(size == 0){
                return true;
            }
            return false;
        }
    public:
        void push_front(const T&& data){
            Node* pos = head; 
            Node* new_node = new Node(data);
            new_node->next = pos->next;
            pos->next = new_node;
            size++;
        }
        void push_front(const T& data){
            Node* pos = before_begin().get_raw();
            Node* new_node = new Node(data);
            new_node->next = pos->next;
            pos->next = new_node;
            size++;
        }
        void pop_front(){   
            Node* pos = head;
            Node* first = head->next;
            if(!first){
                return;
            }
            Node* temp = first; //deferencing
            first = first->next;
            pos->next = first;
            size--;
            delete temp;
        }
        /**
         * @brief insert after
         */
        void insert_after(Iterator iter_position,T&& val){
            Node* curr = iter_position.get_raw();
            Node* new_node = new Node(val);
            new_node->next = curr->next;
            curr->next  = new_node;
        }
        void insert_after(Iterator iter_position,const T& val){
            Node* curr = iter_position.get_raw();
            Node* new_node = new Node(val);
            new_node->next = curr->next;
            curr->next  = new_node;
        }      
        void insert_after(Iterator Iterator_position,int n,T&& val){
            Node* curr = Iterator_position.get_raw();
            if(n < 1){
                return;
            }
            if(n == 1){
                Node* new_node = new Node(val);
                new_node->next = curr->next;
                curr->next = new_node;
            }else{
                Node* new_node = new Node(val);
                Node* tail = new_node;
                for(int i = 0;i < n - 1;i++){
                    Node* baru = new Node(val);
                    tail->next = baru;
                    tail = baru;
                }
                tail->next = curr->next; 
                curr->next = new_node;
            }
        }
        void insert_after(Iterator Iterator_position,int n,const T& val){
            Node* curr = Iterator_position.get_raw();
            if(n < 1){
                return;
            }
            if(n == 1){
                Node* new_node = new Node(val);
                new_node->next = curr->next;
                curr->next = new_node;
            }else{
                Node* new_node = new Node(val);
                Node* tail = new_node;
                for(int i = 0;i < n - 1;i++){
                    Node* baru = new Node(val);
                    tail->next = baru;
                    tail = baru;
                }
                tail->next = curr->next; 
                curr->next = new_node;
            }
        }
        template<typename pos>
        void insert_after(Iterator iter_position,pos itr1,pos itr2){
            using category = typename std::iterator_traits<pos>::iterator_category;
            static_assert(
                std::is_base_of_v<std::input_iterator_tag,category>,
                "parameter harus iterator"
            );
            Node* curr = iter_position.get_raw();
            Node* new_node = new Node(*itr1);
            Node* tail = new_node;
            ++itr1;
            while(itr1 != itr2){
                Node* n_node = new Node(*itr1);
                ++itr1;
                tail->next = n_node;
                tail = n_node;
            }
            tail->next = curr->next;
            curr->next = new_node;
        }
        void insert_after(const Iterator iter_position,Iterator listBegin,const Iterator listEnd){
            Node* curr = iter_position.get_raw();
            Node* new_head = listBegin.get_raw();
            Node* new_node = new Node(new_head->data);
            Node* tail = new_node;
            new_head = new_head->next;   
            while(listBegin != listEnd){
                Node* n_node = new Node(new_head->data);
                tail->next = n_node;
                tail = n_node;
                new_head = new_head->next; 
            }
            tail->next = curr->next;
            curr->next = new_node;
        }
    public://overload erase after
        void erase_after(const Iterator iter_position){
            Node* curr = iter_position.get_raw();
            Node* temp = curr;
            ++curr; //curr = curr->next,gerakkan curr
            Node* dlt = curr;
            ++curr;//curr = curr->next,gerakkan curr
            delete dlt;
            temp->next = curr;
        }
        void erase_after(const Iterator pos_begin,const Iterator pos_end){
            Node* curr = pos_begin.get_raw();
            curr = curr->next;
            while(curr != pos_end){
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    public:
        void print_all(Iterator begin,Iterator end){
            while(begin != end){
                std::cout << *begin << " ";
                ++begin;
            }
            std::cout << std::endl;
        }
        void clear(){
            while(before_begin() != end()){
                Node* temp = head;
                head = head->next;
                delete temp;
            }
        }
};
#endif