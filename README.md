# stl
**我的小型stl,裁剪了一些算法和数据结构,增加了一些数据结构,有一些算法用到了std里的**

**主要目标:** 练习算法和数据结构,熟练一下c++模板的运用,增加代码量

**参考资料：**[cppreference](http://zh.cppreference.com/w/cpp)以及[cplusplus](http://www.cplusplus.com/reference/)还有**STL源码剖析**(侯捷)

#### 1.Vector.h //一些成员函数裁掉了，但基本保持与STL中的一致,用三个测试程序测试,在写的途中遇到几个问题:<br>
    (1. insert算法的有一点要注意，必须比较插入元素个数和插入点之后的元素个数然后再实行不同的算法,必须构造<code>alloc.construct</code>多出来的元素<br>
    (2. swap成员函数仅仅是交换了成员变量中的几个指针(m_first, m_last, m_end),所以交换后原来的迭代器没有失效<br>
    (3. erase的算法仅仅是将后面的元素拷贝（copy）至需要erase的起始位置，然后将m_last(指向最后一个元素的下一个位置)前移了n个<br>
    (4. shrink_to_fit 算法：递归的缩小容量直到容量不大于大小（size）的2倍<br>
    (5. clear 清除元素但不改变容量<br>
  
---

#### 2.List.h//所有测试均在list_test1()(test.h)中，总结如下：
  >(0. list为双向循环链表，是一个环状的，list包含了一个node该node为end节点，node->next为首节点，node->prev为尾节点,所以node可以看作list两端，push和pop既可以在node前后操作<br>
  >(1. list的节点类(list_node)与迭代器(_list_iterator),其中迭代器重载了符号++，++(int),--,--(int),=,*,->以及==和！=实现了将不连续的内存空间通过抽象将他们‘连续’起来<br>
  >(2. 在list中transfer函数比较重要，它将另一个List（可以是*this）中指定范围[first,last)裁剪下来转移到参数position，算法通过几个指针的移动即可，**但要注意移动顺序，因为如果不注意则前面的移动会影响到后面**，需要注意的是，insert的参数与transfer一致，但insert通过复制制定范围的元素后，才将复制好的链表链接到相应位置。**复杂度为O(n)**<br>
  >(3. swap函数比较简单，仅仅是交换了List所包含的哨兵节点（既是end（）迭代器所指向的节点）**复杂度为O(1)**<br>
  >(4. merge 将指定链表混入，该指定链表清空,该函数调用到了transfer**复杂度为O(n)**<br>
  >(5. spice 与transfer类似，只不过指定的参数是const List&而不是迭代器<br>
  >(6. unique删除连续的重复元素<br>实现算法：检查后面的元素，若重复删除当前元素，将当前指针指向后面元素重复操作指导end()**复杂度为O(n)**<br>
  >(7. sort 仅仅用的是insertion sort **复杂度为O(n^2)**<br>
  
  ---
  
#### 3.hashtable.h :
  > (1. hashtable的迭代器(继承foward_iterator)指向非null的_hash_node(链表节点)，++操作会将迭代器中的节点指向下一个非null的节点
  
