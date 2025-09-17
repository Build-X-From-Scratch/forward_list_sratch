#include <iostream>
#include <initializer_list>
#include <type_traits>
#include <iterator>
#include <cstddef>
#include <limits>
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
         * @brief constructor range,adalah constructor yang menginialisasi nilai dari 
         * sebuah container dengan element dari suatu rentang  yang di tentukan oleh
         * 2 iterator awal(first) dan akhir(last) 
         * @details time complexity o(n), dan space complexity O(n)
         * 
         */
        template<typename inputIterator>
        requires std::input_iterator<inputIterator>
        forward_lists(inputIterator begin,inputIterator end): head(nullptr),size(0){
            head = new Node(T{});
            head->next = nullptr;
            size = 0;
            Node** curr = &head->next; //curr menunjuk head->next
            while(begin != end){
                *curr = new Node(*begin); //isi node
                curr = &((*curr)->next); //curr = curr->next
                size++; //increment size
                ++begin; //increment iterator
            }
        }
        /**
         * @brief initializer list constructor
         * @details
         */
        forward_lists(std::initializer_list<T> arr): head(nullptr),size(0){
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
            if(others.head->next == nullptr){
                head = nullptr;
                return;
            }
            head = new Node(others.head->data);
            head->next = new Node(others.head->next->data); //inialisasi data pertama
            Node* curr = head->next; //pointer penggerak
            Node* temp = others.head->next->next;
            while(temp != nullptr){
                curr->next = new Node(temp->data);
                curr = curr->next;
                temp = temp->next;
            }
        }
        //copy assignment
        forward_lists& operator=(const forward_lists& others){
            if(this == &others){
                return *this;
            }
            clear();
            if(!others.head->next){ //nullptr
                head = nullptr;
                return *this;
            }
            head->next = new Node(others.head->next->data); //inialisasi data pertama
            Node* curr = head->next; //pointer penggerak
            Node* temp = others.head->next->next;
            while(temp != nullptr){
                curr->next = new Node(temp->data);
                curr = curr->next;
                temp = temp->next;
            }
            return *this;
        }
        /**
         * @brief move constructor
         * dipakai ketika ingin memindahkan node pada list a ke list b 
         * @details others.head dipakai untuk menghindari double delete
         * ketika others keluar dari scope function maka destructor dipanggil
         * karena head = others.head maka head == nullptr,akan mengakibatkan
         * undefined behavior
         */
        forward_lists(forward_lists&& others) noexcept : head(nullptr){
            head = others.head;
            others.head == nullptr; //kosongkan others lama agar tidak memory leak
        }
        /**
         * @brief move assignment constructor
         */
        forward_lists& operator=(forward_lists&& others)noexcept{
            if(this != others){
                clear();
                head = others.head;
                others.head = nullptr;
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
        /**
         * @brief method getter yang mengembalikan nilai node pada pos front
         * @details time complexity O(1)
         */
        T front(){
            return head->next->data;
        }
        /**
         * @brief method getter yang mengembalilkan jumlah element saat ini
         * @details time complexity O(1)
         */
        int get_size(){
            return this->size;
        }
        /**
         * @brief method getter yang mengembalilkan true jika list empty,sebalik false jika tidak kosong
         * @details time complexity O(1)
         */
        bool is_empty(){
            if(size == 0){
                return true;
            }
            return false;
        }
        /**
         * @brief mengembalikan jumlah maksimum yang dapat di tampung list
         * 
         * @details
         * konsep adalah maksimum byte element yang dapat ditampung type data
         * dibagi oleh jumlah memory untuk 1 node
         * satu node terdiri dari:
         * - data (misal int ) ->4 byte
         * - pointer ke node berikut nya(Node) -> 8 byte pada arsitektur 64 byte
         * jadi perhitungannya:
         * @code
         * std::numeric_limits<size_t>::max() / sizeof(Node)
         * @endcode
         * Time complexity O(1),Space Complexity O(1)
         */
        std::size_t max_size()const noexcept{
            return std::numeric_limits<T>::max() / sizeof(Node);
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
            Node* temp = first;
            first = first->next;
            pos->next = first;
            size--;
            delete temp;
        }
        /**
         * @brief Menyisipkan elemen setelah posisi iterator tertentu.
         *
         * Method ini memiliki beberapa bentuk (overload) untuk menyesuaikan kebutuhan:
         *
         * 1. `insert_after(iterator pos, const T& value)`  
         *    Menyisipkan satu elemen setelah posisi `pos`.
         *
         * 2. `insert_after(iterator pos, size_type n, const T& value)`  
         *    Menyisipkan `n` elemen dengan nilai `value` setelah posisi `pos`.
         *
         * 3. `insert_after(iterator pos, InputIterator first, InputIterator last)`  
         *    Menyisipkan elemen dari rentang `[first, last)` setelah posisi `pos`.
         *
         * 4. `insert_after(iterator pos, std::initializer_list<T> ilist)`  
         *    Menyisipkan seluruh elemen dari `ilist` setelah posisi `pos`.
         */
       /**
         * @brief Overload insert_after(iterator pos, const T& value)
         *
         * Method ini biasanya membutuhkan 2 overload function agar dapat bekerja optimal:
         *
         * 1. Overload dengan parameter **const reference** (`const T&`):  
         *    - Digunakan ketika argumen yang diberikan adalah **lvalue**.  
         *    - Objek tidak dipindahkan, tetapi disalin (copy).  
         *    - Efisien karena tidak membuat salinan tambahan saat menerima lvalue.  
         *    - Keterbatasan: tidak bisa langsung menerima rvalue.
         *
         * 2. Overload dengan parameter **rvalue reference** (`T&&`) / **forwarding reference**:  
         *    - Digunakan ketika argumen adalah **rvalue** atau ketika kita ingin memanfaatkan
         *      move semantics.  
         *    - Bisa juga menerima lvalue, karena forwarding reference tunduk pada
         *      *reference collapsing rules*.  
         *    - Harus dipanggil dengan `std::forward<T>(val)` agar semantik lvalue/rvalue
         *      tetap terjaga.
         *
         * @details Catatan penting mengenai forwarding reference:
         * - Jika argumen adalah **lvalue**, maka `T` akan terdeduksi sebagai `T&`, dan parameter
         *   `T&&` akan menjadi `T& &&` → dikecilkan (collapse) menjadi `T&`.
         * - Jika argumen adalah **rvalue**, maka `T` akan terdeduksi sebagai `T`, dan parameter
         *   `T&&` benar-benar menjadi rvalue reference.
         *
         * Dengan dua overload ini:
         * - `insert_after(pos, x)` → memanggil versi `const T&` (copy dari lvalue).  
         * - `insert_after(pos, std::move(x))` atau `insert_after(pos, T("..."))`
         *   → memanggil versi `T&&` (move dari rvalue).
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
            if(!curr->next){
                return;
            }
            Node* temp = curr->next;
            curr->next = temp->next;
            delete temp;
        }
        void erase_after(const Iterator pos_begin,const Iterator pos_end){
            Node* first = pos_begin.get_raw();
            Node* curr = first->next;
            Node* last = pos_end.get_raw();
         //   curr = curr->next;
            while(curr != last){
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
            first->next = last;
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
            while(head->next != nullptr){
                Node* temp = head->next;
                head->next = head->next->next;
                delete temp;
            }
        }
};
#endif