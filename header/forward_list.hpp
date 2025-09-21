#include <iostream>
#include <initializer_list>
#include <type_traits>
#include <iterator>
#include <cstddef>
#include <limits>
#include <concepts>
#ifndef __forwardList
#define __forwardList
template <typename It>
concept my_input_iterator = requires(It it){
    *it; //bisa di deferencing
    ++it; //bisa post increment
    it++; //bisa pre increment
};
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
        Node* tail;
    public:
        forward_lists(){
            this->head = new Node(T{});
            this->head->next = nullptr;
            this->tail = this->head;    
            this->size = 0;
        }
        /**
         * @brief constructor range,adalah constructor yang menginialisasi nilai dari 
         * sebuah container dengan element dari suatu rentang  yang di tentukan oleh
         * 2 iterator awal(first) dan akhir(last) 
         * @details time complexity o(n), dan space complexity O(n)
         * 
         */
        template <typename It>  
        requires my_input_iterator<It>
        forward_lists(It begin,It end){
            head = new Node(T{});
            size = 0;
            head->next = nullptr;
            tail = head;
            Node** curr = &head->next; //curr menunjuk head->next
            while(begin != end){
                *curr = new Node(*begin); //isi node dengan deferencing begin
                tail = *curr;
                curr = &((*curr)->next); //curr = curr->next
                size++; //increment size
                ++begin; //increment iterator
            }
        }
        /**
         * @brief initializer list constructor
         * @details time complexity O(n),Space Complexity O(n)
         */
        forward_lists(std::initializer_list<T> arr): head(nullptr){
            head = new Node(T{});
            head->next = nullptr;
            tail = head;
            size = 0;
            Node** curr = &head->next; //store alamat memory head ke curr
            for(const T& it: arr){
                *curr = new Node(it); //deference pointer
                //head = new Node(it) ->meaning
                tail = *curr;
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
        forward_lists(forward_lists&& others) noexcept: head(new Node(T{})),tail(head),size(0){
            head->next = others.head->next;
            tail = others.tail == head ? head: others.tail; //ternery operator,if you dont understand please read documentation 
            size = others.size;

            //kosongkan object lama
            others.head->next = nullptr; 
            others.tail = others.head;
            others.size = 0;
        }
        /**
         * @brief move assignment constructor
         */
        forward_lists& operator=(forward_lists&& others)noexcept{
            if(this != &others){
                clear();
                head->next = others.head->next;
                tail = others.tail == head ? head: others.tail; //ternery operator,if you dont understand please read documentation 
                size = others.size;

                //kosongkan object lama
                others.head->next = nullptr; 
                others.tail = others.head;
                others.size = 0;
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
        /**
         * @brief iterator yang menunjuk dummy node yaitu head
         */
        Iterator before_begin(){
            return Iterator(head);
        }
        /**
         * @brief iterator yang menunjuk node pada element pertama pada list
         */
        Iterator begin(){
            return Iterator(head->next);
        }
        /**
         * @brief iterator yang menunjuk pointer setelah node terakhir(tail)
         */
        Iterator end(){
            return Iterator(nullptr);
        }
        Iterator cbegin()const{//constant iterator
            return Iterator(head->next);
        }
        Iterator cend()const{ //constant iterator
            return Iterator(nullptr);
        }
        Iterator cbefore_begin()const{ //constant iterator
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
        T back()const noexcept{
            return this->tail->data;
        }
    public:
        /**
         * @brief method untuk insertion val pada pos front
         * 
         * @details Time complexity O(1),Space Complexity O(1)
         */
        void push_front(T&& data){ //forwadding reference
            if(tail == head){
                Node* new_node = new Node(data);
                head->next = tail = new_node;
                size++;
            }else{
                Node* new_node  = new Node(data);
                new_node->next = head->next;
                head->next = new_node;
                size++;
            }
        }
        void push_front(const T& data){
            if(tail == head){
                Node* new_node = new Node(data);
                head->next = tail = new_node;
                size++;
            }else{
                Node* new_node  = new Node(data);
                new_node->next = head->next;
                head->next = new_node;
                size++;
            }
        }
        /**
         * @brief method untuk deletion val pada pos front
         * 
         * @details Time complexity O(1),Space Complexity O(1)
         */
        void pop_front(){   
            if(tail == head){
                return;
            }
            Node* temp = head->next;
            head->next = temp->next;
            if(temp == tail){
                tail = head;
            }
            delete temp;
            size--;
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
            if(curr == tail){ //jika posisi curr sama dengan tail
                tail = new_node;
            }
            size++; //update size
        }
        void insert_after(Iterator iter_position,const T& val){
            Node* curr = iter_position.get_raw();
            Node* new_node = new Node(val);
            new_node->next = curr->next;
            curr->next  = new_node;
            if(curr == tail){
                tail = new_node; //update tail
            }
            size++; //increment size
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
                if(curr == tail){
                    tail = new_node;
                }
            }else{
                Node* new_node = new Node(val);
                Node* n_tail = new_node;
                for(int i = 0;i < n - 1;i++){
                    Node* baru = new Node(val);
                    n_tail->next = baru;
                    n_tail = baru;
                }
                n_tail->next = curr->next; 
                curr->next = new_node;
                if(curr == tail){
                    tail = n_tail; //karena n_tail menunju node terakhir saat insertion
                }
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
                if(curr == tail){
                    tail = new_node;
                }
            }else{
                Node* new_node = new Node(val);
                Node* n_tail = new_node;
                for(int i = 0;i < n - 1;i++){
                    Node* baru = new Node(val);
                    n_tail->next = baru;
                    n_tail = baru;
                }
                n_tail->next = curr->next; 
                curr->next = new_node;
                if(curr == tail){
                    tail = n_tail;
                }
            }
        }
        template<std::input_iterator It>
        requires (!std::same_as<It,Iterator>)
        void insert_after(Iterator iter_position,It itr1,It itr2){
            Node* curr = iter_position.get_raw();
            Node* new_node = new Node(*itr1);
            size++;
            Node* n_tail = new_node;
            ++itr1;
            while(itr1 != itr2){
                Node* n_node = new Node(*itr1); //deferencing itr1
                ++itr1; //increment iterator itr1
                n_tail->next = n_node;
                n_tail = n_node;
                size++;
            }
            n_tail->next = curr->next;
            curr->next = new_node;
            if(curr == tail){
                tail = n_tail;
            }
        }
        void insert_after(const Iterator iter_position,Iterator listBegin,const Iterator listEnd){
            Node* curr = iter_position.get_raw();
            Node* new_head = listBegin.get_raw();
            Node* end = listEnd.get_raw();
            Node* new_node = new Node(new_head->data);
            size++;
            Node* n_tail = new_node;
            new_head = new_head->next;   
            while(new_head != end){
                Node* n_node = new Node(new_head->data);
                n_tail->next = n_node;
                n_tail = n_node;
                new_head = new_head->next; 
                size++;
            }
            n_tail->next = curr->next;
            curr->next = new_node;
            if(curr == tail){
                tail = new_node;
            }
        }
    public://overload erase after
        void erase_after(const Iterator iter_position){
            Node* curr = iter_position.get_raw();
            if(!curr->next){//tidak ada node setelah posisi iterator 
                return; //return
            }
            if(curr->next == tail){ //jika node selanjutnya tail
                Node* temp = curr->next;
                tail = curr; // tail sekarang curr 
                delete temp;
                size--; 
            }else{ //
                Node* temp = curr->next;
                curr->next = temp->next;
                size--;
                delete temp;
            }
        }
        void erase_after(const Iterator pos_begin,const Iterator pos_end){
            Node* first = pos_begin.get_raw();
            Node* fst = pos_begin.get_raw();
            Node* curr = first->next;
            Node* last = pos_end.get_raw();
         //   curr = curr->next;
            while(curr != last){
                if(curr == tail){
                    Node* temp = curr;
                    tail = fst;
                    curr = curr->next;
                    delete temp;
                    size--;
                }else{
                    Node* temp = curr;
                    curr = curr->next;
                    delete temp;
                    size--;
                }
            }
            first->next = last;
            if(last == nullptr){
                tail = first;
            }
        }

    public: //reverse method
        void reverse(){
            Node* prev = nullptr;
            Node* curr = head->next;    
            while(curr != nullptr){
                Node* next = curr->next;
                curr->next = next;
                prev = curr;
                curr = next;
            }
            head->next = prev;
        }
    public:
        /**
         * @brief Method Assign
         * Assign dipakai untuk mereplace list saat ini dengan list baru
         * overload method assign
         * assign(n,value) ->insert value sebanyak n kali
         * assign(initializer_list<T>)->replace value pada initializer list ke list saat ini
         * assign(iterator begin,iterator end) ->replace mulai dari iterator begin sampai sebelum iterator end
         * 
         * @details Time complexity O(n),Space Complexity O(n)
         */
        void assign(std::size_t n,const T& value){
            clear();
            Node* curr = head;
            for(std::size_t i = 0;i < n;i++){
                curr->next = new Node(value);
                curr = curr->next;
                size++;
            }
        }
        void assign(std::size_t n,T&& value){
            clear();
            Node* curr = head;
            for(std::size_t i = 0;i < n;i++){
                curr->next = new Node(value);
                curr = curr->next;
                size++;
            }
        }
        void assign(std::initializer_list<T> arr){
            clear();
            head = new Node(T{});
            head->next = nullptr;
            Node** curr = &head->next;
            //size++;
            for(const T& value: arr){
                *curr = new Node(value); //curr = new Node
                curr = &((*curr)->next); //curr = curr->next
                size++;
            }   
        }   
        template<typename It>
        requires my_input_iterator<It>
        void assign(It itr1,It itr2){
            clear();
            Node* curr = head;
            while(itr1 != itr2){
                curr->next = new Node(*itr1);
                curr = curr->next;
                size++;
                ++itr1;
            }
        }
    public:  //slice after
        /**
         * @brief slice after
         * method untuk memindahkan node dari satu list ke list lain
         * tanpa menyalin data,tetapi move node pointer
         * 
         * @details Time complexity O(1),Space Complexity O(1)
         */
        void splice_after(const Iterator pos,forward_lists& others,const Iterator It){
            Node* src = It.get_raw();
            Node* moved = src->next;
            src->next = moved->next; //src->next = src->next->next
            
            Node* dest = pos.get_raw();
            moved->next = dest->next; //hubungkan ke list tujuan
            dest->next = moved;
            others.size--;
            size++;
        }
        void splice_after(const Iterator pos,forward_lists&& others,const Iterator It){
            Node* src = It.get_raw();
            Node* moved = src->next;
            src->next = moved->next; //src->next = src->next->next
            
            Node* dest = pos.get_raw();
            moved->next = dest->next; //hubungkan ke list tujuan
            dest->next = moved;
            others.size--;
            size++;
        }
        void splice_after(const Iterator pos,forward_lists& others){
            Node* src = pos.get_raw();//pos object saat ini
            Node* begin = others.head->next ; //begin object lain
            Node* end = others.tail; //end object lain

            //lingking node pertama others ke object saat ini
            Node* moved = src->next; 
            moved->next = begin->next; //tunjuk node setelah begin

            begin->next = moved; //linking begin ke node setelah iterator
            //linking node terakhir object lain ke src->next
            end->next = src->next;

            //linking node pertama object saat ini ke head object lain
            src->next = begin;
            size += others.size;
            others.size = 0;
        }
        // void splice_after(const Iterator pos,forward_lists& others,const Iterator first,const Iterator last){
        //     Node* curr = pos.get_raw();
        // }
    public:
        /**
         * @brief method untuk print semua node list 
         * 
         * @details Time complexity O(n),Space Complexity O(n)
         */
        void print_all(Iterator begin,Iterator end){
            while(begin != end){
                std::cout << *begin << " ";
                ++begin;
            }
            std::cout << std::endl;
        }
        /**
         * @brief method untuk menghapus semua node pada head
         * berguna pada destructor
         * @details time complexity O(n),Space Complexity O(n)
         */
    void clear(){
        Node* curr = head->next;   // mulai dari setelah dummy
        while(curr != nullptr){
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        head->next = nullptr;  // dummy menunjuk ke kosong
        tail = head;           // tail kembali ke dummy
        size = 0;
    }
};
#endif