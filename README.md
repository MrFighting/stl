# stl
**我的小型stl,裁剪了一些算法和数据结构,增加了一些数据结构**

**主要目标:** 练习算法和数据结构,熟练一下c++模板的运用,增加代码量

**参考资料：**[cppreference](http://zh.cppreference.com/w/cpp)以及[cplusplus](http://www.cplusplus.com/reference/)还有**STL源码剖析**(侯捷)

1.Vector.h //一些成员函数裁掉了，但基本保持与STL中的一致,用三个测试程序测试,在写的途中遇到几个问题:<br>
  >(1. insert算法的有一点要注意，必须比较插入元素个数和插入点之后的元素个数然后再实行不同的算法,必须构造<code>alloc.construct</code>多出来的元素<br>
  >(2. swap成员函数仅仅是交换了成员变量中的几个指针(m_first, m_last, m_end),所以交换后原来的迭代器没有失效<br>
  >(3. erase的算法仅仅是将后面的元素拷贝（copy）至需要erase的起始位置，然后将m_last(指向最后一个元素的下一个位置)前移了n个<br>
  >(4. shrink_to_fit 算法：递归的缩小容量直到容量不大于大小（size）的2倍<br>
  >(5. clear 清除元素但不改变容量<br>
