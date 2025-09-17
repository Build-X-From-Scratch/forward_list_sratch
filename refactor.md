## Pengingat refactor
refactor method erase_after pertama
```cpp
Node* dlt = iter_position->next;
iter_position->next = dlt->next;
delete dlt;
```