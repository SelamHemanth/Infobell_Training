#Memory Management
---

***Cont  kmalloc***
---

 * The ksize API, given a pointer to slab-allocated memory (in effect, memory allocated via the kmalloc), returns the actual number of bytes allocated.
size_t ksize(const void *objp);
 * It could be more than what was requested. F.e.

```javascript
size_t actual=0;
void *ptr = kmalloc(160, GFP_KERNEL); // ask for 160 bytes
actual = ksize(ptr); // will get 192 bytes (actual ← 192)
Thus, ksize() helps us detect the wastage (internal fragmentation)!
```
 * The way to check which slabs suffer from wastage: use the kernel’s slabinfo utility
 * Note: By using `sudo vmstat -m` , we can see the chache page sizes.

***vmalloc***
---



