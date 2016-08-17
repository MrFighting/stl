# stl
**我的小型stl,裁剪了一些算法和数据结构,增加了一些数据结构,有一些算法用到了std里的**

**主要目标:** 练习算法和数据结构,熟练一下c++模板的运用,增加代码量

**参考资料：**[cppreference](http://zh.cppreference.com/w/cpp)以及[cplusplus](http://www.cplusplus.com/reference/)还有**STL源码剖析**(侯捷)

#### 1.Vector.h //一些成员函数裁掉了，但基本保持与STL中的一致,用三个测试程序测试,在写的途中遇到几个问题:<br>
　　1. <code>insert</code>算法的有一点要注意，必须比较插入元素个数和插入点之后的元素个数然后再实行不同的算法,必须构造<code>alloc.construct</code>多出来的元素<br>
　　2. <code>swap</code>成员函数仅仅是交换了成员变量中的几个指针(m_first, m_last, m_end),所以交换后原来的迭代器没有失效<br>
　　3. <code>erase</code>的算法仅仅是将后面的元素拷贝（copy）至需要erase的起始位置，然后将m_last(指向最后一个元素的下一个位置)前移了n个<br>
　　4. <code>shrink_to_fit</code> 算法：递归的缩小容量直到容量不大于大小（size）的2倍<br>
　　5. <code>clear</code> 清除元素但不改变容量<br>
  
---

#### 2.List.h//所有测试均在list_test1()(test.h)中，总结如下：
　　0. <code>list</code>为双向循环链表，是一个环状的，list包含了一个node该node为end节点，<node>node->next</code>为首节点，<code>node->prev</code>为尾节点,所以node可以看作list两端，push和pop既可以在node前后操作<br>
　　1. list的节点类<code>(list_node)</code>与迭代器<code>(_list_iterator)</code>,其中迭代器重载了符号<code>++，++(int),--,--(int),=,*,->,==,！=</code>实现了将不连续的内存空间通过抽象将他们‘连续’起来<br>
　　2. 在list中<code>transfer</code>函数比较重要，它将另一个List（可以是*this）中指定范围<code>[first,last)</code>裁剪下来转移到参数position，算法通过几个指针的移动即可，**但要注意移动顺序，因为如果不注意则前面的移动会影响到后面**，需要注意的是，insert的参数与transfer一致，但insert通过复制制定范围的元素后，才将复制好的链表链接到相应位置。**复杂度为O(n)**<br>
　　3. <code>swap</code>函数比较简单，仅仅是交换了List所包含的哨兵节点（既是end（）迭代器所指向的节点）**复杂度为O(1)**<br>
　　4. <code>merge</code> 将指定链表混入，该指定链表清空,该函数调用到了transfer**复杂度为O(n)**<br>
　　5. <code>spice</code> 与transfer类似，只不过指定的参数是const List&而不是迭代器<br>
　　6. <code>unique</code>删除连续的重复元素<br>实现算法：检查后面的元素，若重复删除当前元素，将当前指针指向后面元素重复操作指导end()**复杂度为O(n)**<br>
　　7. <code>sort</code> 仅仅用的是<code>insertion sort</code> **复杂度为O(n^2)**<br>
  
  ---
  
#### 3.hashtable.h(unordered_map 和 unorderd_set仅仅就是hashtable的适配器这里不再赘述) :
　　1. <code>hashtable</code>的迭代器(继承<code>foward_iterator</code>)指向非null的<code>_hash_node</code>(链表节点)，++操作会将迭代器中的节点指向下一个非null的节点<br>
　　2. 模板有5个分别对应</ode>Key,Value(键值对),Hash_fun,Key_Equal,Extract_Key(从键值对取出Key)</code><br>
　　3. <code>erase(iterator pos)</code>的算法是将后一个元素的值给该迭代器处的元素,然后删除后一个元素(因为无法获取前一个节点),若该节点为尾节点,则删除之,并返回++重载操作符后的iterator<br>
　　4. <code>erase(iterator beg, iterator  end)</code>的算法要注意一点,因为调用了前面的算法,所以在下一个节点为end迭代器的节点时应该终止循环(end节点被删除从而前面那个迭代器替代end),要不然就死循环<br>
　　5. <code>swap(hashtable&)</code>交换<code>buckets</code>(代表桶的vector)和<code>element_count</code>(元素数量)即可<br>
　　6. <code>begin()</code>迭代器是指向第一个非null的节点,<code>end()</code>迭代器指向<code>iterator(nullptr,this)</code><br>
　　7. 可以设置最大装载因子<code>(max_load_facotr)</code>,当调用<code>reserve(size_t count)</code>--预留countge元素空间时候,确保装载因子不大于最大装载因子(既是调用<code>rehash(count/max_load_factor))</code><br>
  
