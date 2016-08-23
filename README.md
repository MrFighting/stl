# stl
## 一个小型stl容器库
<br>

**主要目标:** 练习算法和数据结构,熟练一下c++模板的运用,增加代码量

**参考资料：**[cppreference](http://zh.cppreference.com/w/cpp)以及[cplusplus](http://www.cplusplus.com/reference/)还有**STL源码剖析**(侯捷)以及[Algorithm(Sedgewick)](http://algs4.cs.princeton.edu/home/)

---
### ****以下所以测试均在<code>test.h</code>中****
<br>
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
  
---

#### 4.Stack,Queque(较为简单,适配Vector即可)

---

#### 5.Priority_Queue(优先级队列，并未按照std::priority_queue的写法)
　　1. <code>Priority_Queue</code>的底层固定为<code>Vector</code>,通过上升和下层元素实现heap的功能
　　2. **注意**元素的起始位置是从vec的第0开始,并未像是Algorithm书中从1开始,这里就讲算法复杂化了,比如某个需要下沉某个位置index需要知道其右子节点<code>(index*2+2)</code>然后比较左右子节点大小,大的那个再与index所在节点比较,如果index处小,则交换他们,更新<code>index =child_index(子节点的位置)</code>,<code>child_index=index*2+2</code>,重复该过程,直到没有比index位置元素大的时候停止比较(或者子节点index > 容器size时终止循环).**而且**还要判断是否最终的子节点的父节点没有右节点的情况,然后比大小,需要时再交换一次<br>
　　3. <code>make_heap</code>的算法较为简单,直接从元素中间到元素起始位置分别下沉(<code>percolate_down</code>)<br>
　　4. <code>heap_sort</code>直接从pq的顶出取出元素,删除(pop)该元素,然后平衡,重复,直到为空就排好序了<br>
　　
---
　　
#### 6.Memory.h(包括unique_ptr和shared_ptr)
　　1. <code>unique_ptr</code>的实现相对简单,就是对一个指针封装,一个指针只能存在于一个对象中,若要转移则调用<code>release</code>方法也可以<code>reset</code>指针(会delete原来的指针),拷贝构造和赋值是<code>delete</code>的,但可以对该类的**右值**进行赋值.<br>
　　2. <code>shared_ptr</code>内涵了一个原子的(atomic)的计数器<code>std::atomic<size_t>* ref_count</code>需要**注意**的是:<br>
　　　　1. **为什么为atomic:**<br>
　　　　  因为如果两个线程同时对<code>ref_count</code>进行++或--操作,非原子操作可能会造成看起来只进行一次++操作(实际上是两次)<br>
　　　　2. **为什么把ref_count放在堆上:**<br> 
```c++
Shared_Ptr<int> a(new int(1));//ref_count = 1
Shared_Ptr<int> b(a);//
//此时若ref_count不在堆上则a.use_count == 1
//否则a.use_count会得到更新a.use_count == 2
```
　　　  <br>
　　　  4. 增加<code>ref_count</code>只能是在拷贝,赋值时,赋值时会调用<code>decrease_count</code>减去先前的<code>ref_count</code><br>
　　　  5. 析构时,调用<code>decrease_count</code>该函数在count为0时会释放掉计数器和指针<br>
　　　  
