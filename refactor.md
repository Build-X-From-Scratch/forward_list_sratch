```cpp
Node* tail = head;
while(begin != end){
    tail->next = new Node(*begin);
    tail = tail->next;
    ++begin;
}
```