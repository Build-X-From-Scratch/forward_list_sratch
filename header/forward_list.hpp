/*
MIT License

Copyright (c) 2025 Build X  From  Scratch

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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
template <typename T,typename Allocator = std::allocator<T>>
class forward_lists{
    private:
        struct Node{
            T data;
            Node* next;
        };
        //allocator khusus node
        using node_allocator_type = 
        typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
        using node_traits = std::allocator_traits<node_allocator_type>;
        node_allocator_type alloc; //instance allocator
        Node* head  = nullptr; //head pointer
        Node* tail; //tail pointer
        int size; //banyak element pada linked list
    /**
     * @brief Allocator explanation
     * Allocator adalah abstraksi cara mengelola memory pada container
     * alih2 melakukan new dan delete,STL memakai allocator yaitu semacam
     * policy class yang akan menentukan:
     * 1.bagaimana alokasi memory dilakukan(allocate)
     * 2.bagaimana membangun object di memori(construct)
     * 3.bagaimana menghancurkan object(destroy)
     * 4.bagaimana membebaskan memory(deallocate)
     * 
     * @details policy class
     * Policy class adalah konsep desain di C++ di mana sebuah class tidak
     * menentukan perilaku sendiri, tapi “mendelegasikan” perilaku tertentu
     * ke class lain
     */
    private:
        Node* _create_node(const T& value){
            Node* n = node_traits::allocate(alloc,1); //alokasi memory mentah sebanyak 1 blok memory untuk node(allocate)
            try{
                node_traits::construct(alloc,std::addressof(n->data),value); //membangun object di memory(construct)
            }catch(...){ //catch all handler
                node_traits::deallocate(alloc,n,1); //dealokasi
            }
            //set next menjadi null
            n->next = nullptr;
            //kembalikan node
            return n;
        }
        void _destroy_node(Node* n)noexcept{
                node_traits::destroy(alloc,std::addressof(n->data));
                node_traits::deallocate(alloc,n,1);
        }
    public:
    //default constructor allocator 
        explicit forward_lists():
            alloc(node_allocator_type()),head(_create_node(T{})),tail(head),size(0){}
        //default constructor   
        forward_lists(const Allocator& a):
        alloc(a),head(_create_node(T{})),tail(head),size(0){}
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
            Node* new_node = _create_node(T{}); //create dummy node
            head = new_node;
            size = 0;
            tail = head;
            Node** curr = &head->next; //curr menunjuk head->next
            while(begin != end){
                Node* n_node = _create_node(*begin);
                *curr = n_node; //isi node dengan deferencing begin
                tail = *curr;
                curr = &((*curr)->next); //curr = curr->next
                ++size; //increment size
                ++begin; //increment iterator
            }
        }
        /**
         * @brief initializer list constructor
         * @details time complexity O(n),Space Complexity O(n)
         */
        forward_lists(std::initializer_list<T> arr): head(nullptr){
            Node* new_node = _create_node(T{});
            head = new_node;
            tail = head;
            size = 0;
            Node** curr = &head->next; //store alamat memory head ke curr
            for(const T& it: arr){
                Node* n_node = _create_node(it);
                *curr = n_node; //curr menunjuk n_noed
                tail = *curr; //tail ikut menunjuk curr
                curr = &((*curr)->next); //store alamat curr->next
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
            head = _create_node(T{}); //isi dummy 
            head->next = _create_node(others.head->next->data); //inialisasi data pertama
            Node* curr = head->next; //pointer penggerak
            Node* temp = others.head->next->next; //mulai dari node ke 2
            while(temp != nullptr){
                curr->next = _create_node(temp->data);
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
            head = _create_node(T{}); //isi dummy 
            head->next = _create_node(others.head->next->data);//inialisasi data pertama
            Node* curr = head->next; //pointer penggerak
            Node* temp = others.head->next->next; //mulai dari node ke 2
            while(temp != nullptr){
                curr->next = _create_node(temp->data);
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
        forward_lists(forward_lists&& others) noexcept: head(_create_node(T{})),tail(head),size(0){
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
        /**
         * @brief destructor
         * - panggil method clear
         * head harus tetap menunjuk dummy node
         */
        ~forward_lists(){
            clear(); //panggil method clear
        }
    private:
        class Iterator{
            private:
                Node* node;
            public:
                /**
                 * @brief iterator category 
                 * iterator category adalah label yang menjelaskan kemampuan
                 * sebuah 
                 * 
                 * @details Iterator traits
                 * - iterator_category  
                 * traits ini adalah menandakan kemampuan sebuah iterator pada
                 * forward_list kita memakai forward_iterator dikarenakan singly
                 * linked list hanya punya pointer next yang memunkinkan node hanya 
                 * bisa bergerak maju
                 * - value_type
                 * traits ini adalah type data yg digunakan oleh forward_list
                 * karena sudah ada Template,maka kita dapat langsung memakai Templates
                 * tersebut
                 * - difference_type
                 * tipe integer untuk menyatakan selisih dua iterator,ini dipakai
                 * pada std::distance untuk menghitung banyak node diantara 2 iterator
                 * - using pointer = T*;
                 * tipe pointer ke elemen yang ditunjuk iterator
                 * - using reference = T&;
                 * tipe referensi ke elemen,Memungkinkan penggunaan *it untuk mengakses elemen.
                 */
                using iterator_category = std::forward_iterator_tag;
                using value_type        = T;
                using difference_type   = std::ptrdiff_t;
                using pointer           = T*;
                using reference         = T&;
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
                reference operator*()const{
                    return node->data;
                }
                pointer operator->()const{
                    return &(node->data);
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
                Node* new_node = _create_node(data);
                head->next = tail = new_node;
                size++;
            }else{
                Node* new_node  = _create_node(data);
                new_node->next = head->next;
                head->next = new_node;
                size++;
            }
        }
        void push_front(const T& data){
            if(tail == head){
                Node* new_node = _create_node(data);
                head->next = tail = new_node;
                size++;
            }else{
                Node* new_node  = _create_node(data);
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
            _destroy_node(temp);
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
            Node* new_node = _create_node(val);
            new_node->next = curr->next;
            curr->next  = new_node;
            if(curr == tail){ //jika posisi curr sama dengan tail
                tail = new_node;
            }
            size++; //update size
        }
        void insert_after(Iterator iter_position,const T& val){
            Node* curr = iter_position.get_raw();
            Node* new_node = _create_node(val);
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
                Node* new_node = _create_node(val);
                new_node->next = curr->next;
                curr->next = new_node;
                if(curr == tail){
                    tail = new_node;
                }
            }else{
                Node* new_node = _create_node(val);
                Node* n_tail = new_node;
                for(int i = 0;i < n - 1;i++){
                    Node* baru = _create_node(val);
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
                Node* new_node = _create_node(val);
                new_node->next = curr->next;
                curr->next = new_node;
                if(curr == tail){
                    tail = new_node;
                }
            }else{
                Node* new_node = _create_node(val);
                Node* n_tail = new_node;
                for(int i = 0;i < n - 1;i++){
                    Node* baru = _create_node(val);
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
            Node* new_node = _create_node(*itr1);
            size++;
            Node* n_tail = new_node;
            ++itr1;
            while(itr1 != itr2){
                Node* n_node = _create_node(*itr1); //deferencing itr1
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
            Node* new_node = _create_node(new_head->data);
            size++;
            Node* n_tail = new_node;
            new_head = new_head->next;   
            while(new_head != end){
                Node* n_node = _create_node(new_head->data);
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
                _destroy_node(temp);
                size--; 
            }else{ //
                Node* temp = curr->next;
                curr->next = temp->next;
                size--;
                _destroy_node(temp);
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
                    _destroy_node(temp);
                    size--;
                }else{
                    Node* temp = curr;
                    curr = curr->next;
                    _destroy_node(temp);
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
                curr->next = _create_node(value);
                curr = curr->next;
                size++;
            }
        }
        void assign(std::size_t n,T&& value){
            clear();
            Node* curr = head;
            for(std::size_t i = 0;i < n;i++){
                curr->next = _create_node(value);
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
                *curr = _create_node(value); //curr = new Node
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
                curr->next = _create_node(*itr1);//deferencing itr1
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
         * @details Time complexity overloads
         * - void splice_after( const_iterator pos, forward_list& other ) -> O(1)
         * - void splice_after( const_iterator pos, forward_list&& other ) -> O(1) 
         * - void splice_after( const_iterator pos, forward_list& other,
                   const_iterator it ) -> O(1)
         * - void splice_after( const_iterator pos, forward_list&& other,
                   const_iterator it ) ->O(1)
         * - void splice_after( const_iterator pos, forward_list& other,
                   const_iterator first, const_iterator last ) -> O(n)
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
            if(this == &others){
                return;
            }
            Node* src = pos.get_raw();//pos object saat ini
            Node* begin = others.head->next ; //begin object lain
            Node* end = others.tail; //end object lain

            end->next = src->next;
            src->next = begin;
            //update tail
            if(src == tail){
                tail = end;
            }
            //update size
            size += others.size;
            //kosong object lain
            others.head->next = nullptr; //harus menunjuk nullptr
            others.tail = others.head;//reset tail,tail menunjuk head(dummy node)
            others.size = 0;
        }
        void splice_after(const Iterator pos,forward_lists&& others){ //global reference
            if(this == &others){
                return;
            }
            Node* src = pos.get_raw();//pos object saat ini
            Node* begin = others.head->next ; //begin object lain
            Node* end = others.tail; //end object lain
            end->next = src->next;
            src->next = begin;
            //update tail
            if(src == tail){
                tail = end;
            }
            //update size
            size += others.size;
            //kosong object lain
            others.head->next = nullptr; //harus menunjuk nullptr
            others.tail = others.head;//reset tail,tail menunjuk head(dummy node)
            others.size = 0;
        }
        void splice_after(const Iterator pos,forward_lists& others,const Iterator first,const Iterator last){
            //relingking dari range (first,last)
            Node* curr = pos.get_raw();
            Node* other_begin = first.get_raw()->next;
            Node* other_end = last.get_raw();
            Node* after_node = curr->next; //simpan first this
            if(other_begin == other_end){
                return; //nullptr   
            }
            //update size,update size sebelum di linking
            auto moved = (std::distance(first, last)) - 1;
            size += moved;
            others.size -= moved;
            //simpan last_node
            Node* last_node = other_begin;
            //cari node sebelum lasr
            while(last_node->next != other_end){
                last_node = last_node->next;
                //loop sampai last_node tepat menunjuk sebelum pos last
            }
            //sembungkan ke list tujuan
            last_node->next = curr->next;
            curr->next = other_begin;
            //lingking curr->next with to others_begin  

            //update tail
            if(after_node == tail || other_end == nullptr){
                tail = last_node;
            }
            //relingking object lain
            first.get_raw()->next = other_end;
            if(other_end == nullptr){
                others.tail = first.get_raw();
            }

        }
        void splice_after(const Iterator pos,forward_lists&& others,const Iterator first,const Iterator last){
            //relingking dari range (first,last)
            Node* curr = pos.get_raw();
            Node* other_begin = first.get_raw()->next;
            Node* other_end = last.get_raw();
            Node* after_node = curr->next;
            if(other_begin == other_end){
                return; //nullptr   
            }
            //update size,update size sebelum di linking
            auto moved = std::distance(std::next(first),(last));
            size += moved;
            Node* last_node = other_begin;
            others.size -= moved;
            //cari node sebelum lasr
            while(last_node->next != other_end){
                last_node = last_node->next;
                //loop sampai last_node tepat menunjuk sebelum pos last
            }
            //sembungkan ke list tujuan
            last_node->next = curr->next;
            curr->next = other_begin;
            //lingking curr->next with to others_begin  

            //update tail
            Node* new_begin = first.get_raw();
            if(after_node == tail){
                tail = last_node;
            }
            //relingking object lain
            first.get_raw()->next = other_end;
            if(other_end == nullptr){
                others.tail = first.get_raw();
            }

        }
    public:
        void swap(forward_lists& others)noexcept{
            if(this == &others){//jika this sama dengan object lain
                return;
            }
            //swap head;
            Node* tempHead = head;
            head = others.head;
            others.head = tempHead; 
            //swap tail
            Node* tempTail = tail;
            tail = others.tail;
            others.tail = tempTail;
            //swap size
            int tempSize = size;
            size = others.size;
            others.size = tempSize;
        }
        void swap(forward_lists&& others)noexcept{
            if(this == &others){//jika this sama dengan object lain
                return;
            }
            //swap head;
            Node* tempHead = head;
            head = others.head;
            others.head = tempHead;
            //swap tail
            Node* tempTail = tail;
            tail = others.tail;
            others.tail = tempTail;
            //swap size
            int tempSize = size;
            size = others.size;
            others.size = tempSize;
        }
    private: //helper sort
        Node* merge(Node* left, Node* right) {
            if (!left) return right;
            if (!right) return left;

            if (left->data <= right->data) {
                left->next = merge(left->next, right);
                return left;
            } else {
                right->next = merge(left, right->next);
                return right;
            }
        }
        Node* getMiddle(Node* head){
            //mulai dari note pertama
            Node* slow = head;
            Node* fast = head->next;
            while(fast && fast->next){
                slow = slow->next;
                fast = fast->next->next;
            }
            return slow;
        }
        Node* helper(Node* head){
            if(!head || !head->next){
                return head;
            }
            Node* middle = getMiddle(head);
            Node* nextMiddle = middle->next;
            //putushkan hubungan list
            middle->next = nullptr;
            Node* left = helper(head);
            Node* right = helper(nextMiddle);
            return merge(left,right);
        }
    public:
        void sort(){
            head->next = helper(head->next  );
            Node* curr = head;
            while(curr && curr->next){
                curr = curr->next;
            }
            tail = curr;
        }
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
            Node* next = curr->next; //simpan curr->next
            _destroy_node(curr);  //hancurkan curr
            curr = next;//curr menunjuk next
        }
        head->next = nullptr;  // dummy menunjuk ke kosong
        tail = head;           // tail kembali ke dummy
        size = 0;
    }
};
#endif