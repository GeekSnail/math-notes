**考纲**

查找基本概念，查找算法的分析及应用

顺序查找，分块查找，折半查找

**树型查找：二叉搜索树、平衡二叉树、红黑树**

B 树及其操作、B+ 树的概念

散列Hash表

字符串模式匹配

查找算法的分析与应用

**知识框架**

![image-20210721041249387](../assets/image-20210721041249387.png)

## 1. 查找的基本概念

平均查找长度 $ASL=\frac{1}{n}\sum_{i=1}^nC_i,\ C_i$：找到第 i 个数据元素所需进行的比较次数

## 2. 顺序查找和折半查找

### 顺序查找

平均查找长度 $ASL=\frac{1}{n}\sum_{i=1}^ni=\frac{n+1}{2}$

### 折半查找（二分查找）

二分查找仅适用于有序的顺序表

二分查找思想：将给定key与表中中间位置元素比较，若相等，则查找成功返回位置；若小于，则在左子表继续查；若大于，则在右子表继续查

```cpp
int B_Search(vector<int> L, int key) {
    int low=0, high=L.size(), mid;
    while (low <= high) {
        mid = (low+high) / 2;
        if (key == L[mid])
            return mid;
        else if (key < L[mid]) 
            high = mid - 1;
        else
            low = mid + 1;
    }
    return -1;
}
```

![image-20210721200557125](../assets/image-20210721200557125.png)

描述二分查找的判定树：AVL 树（平衡二叉搜索树）

查找成功长度：根节点到目的结点路径上的结点数

查找成功 $ASL\le\frac{1}{n}\sum_{i=1}^{h=\lfloor log_2n\rfloor+1}i·2^{i-1}=\frac{2^h(h-1)+1}{n}\approx log_2n$，本例成功 ASL=(1+2x2+3x4+4x4)/11=3

查找失败长度：根节点到空指针的父节点路径上的结点数

查找失败 $ASL\le\frac{1}{n}\lceil log_2(n+1)\rceil n\approx log_2n$，本例失败 ASL=(3x4+4x8)/12=11/3

### 分块查找

分块查找又称索引顺序查找

分块查找思想：将查找表分为若干子块，块内元素无序，块间有序；通过索引表（含各块最大关键字&各块第一元素地址）确定块；再在块内顺序查找

## 3. 树型查找

### 二叉搜索树BST

#### BST查找

```cpp
//非递归
Node* bstSearch(Node *T, int key) {
	while (T && key != T.data) {
        if (key < T->data)
            T = T->lchild;
        else
            T = T->rchild;
    }
    return T;
}
```

```cpp
//递归
Node* bstSearch(Node* T, int key) {
    if (!T || key == T->data) 
        return T;
    if (key < T->data) 
        return bstSearch(T->lchild, key);
    else
        return bstSearch(T->rchild, key);    
}
```

#### BST树查找效率

BST 查找效率取决于树的高度

若 BST 的左、右子树的高度之差绝对值 $\le 1$，为平衡二叉树，平均查找长度 $O(log_2n)$

若 BST 是一个只有左（右）子树的单支树，平均查找长度 $O(n)$

![image-20210716024916302](../assets/image-20210716024916302.png)

第 i 层的结点需查找 i 次

$ASL_a=(1+2*2+4*3+3*4)/10\\
ASL_b=(1+...+10)/10$ 

### 平衡二叉树AVL

#### AVL 树查找

> 定义 $n_h$：深度 h 的 AVL 树的最少结点数
>
> $n_0=0,n_1=1,n_2=2,n_3=4,...,n_h=n_{h-1}+n_{h-2}+1$

函数 N(h) 与斐波那契数相关

n 个结点的 AVL树最大深度=平均查找长度=$O(log_2n)$​

### 红黑树

#### 查找

![image-20210928030454174](../assets/image-20210928030454174.png)

## 4. B树 和 B+树

### B树及其操作

m阶B树的定义：

- 若节点数N=0，为空树；

- 若节点数N>0，则每个结点至多m棵子树，至多有m-1个关键字；结点孩子数=关键字数+1

  若根结点（非叶），子树棵数 $[2,m]$，关键字数 $[1,m-1]$

  普通结点（非根非叶）子树棵数 $[\lceil m/2\rceil,m]$，关键字数 $[\lceil m/2\rceil-1,m-1]$
  
  所有叶结点（空结点）都在同一层，作为查找失败的空指针节点
  
  结点关键字从左到右递增有序（类似 AVL 树）

非叶结点结构：

$k_i$ 结点关键字，$k_1<...<k_n$

$p_i$ 指向子树根结点的指针，$k_i<\{p_i子树所有关键字\}< k_{i+1}\\
p_0\rightarrow k_{1...n_0}<k_1<...<p_i\rightarrow k_{1...n_i}<...<k_n<p_n\rightarrow k_{1...n_n}$

![image-20210722005855588](../assets/image-20210722005855588.png)

#### B树高度（磁盘存取次数）

关键字数 $n\ge 1$，高度 h，m 阶 B 树，

- $h_{min}$：结点至多m棵子树，m-1个关键字，$n\le (m-1)(1+m+...+m^{h-1})=m^h-1\Rightarrow h\ge log_m(n+1)$

  ![image-20210722014026205](../assets/image-20210722014026205.png)

- $h_{max}$：根节点至少2棵子树，普通结点至少 $\lceil m/2\rceil$ 棵子树，第 h+1 层空叶节点至少 $2(\lceil m/2\rceil)^{h-1}$ 个

  $n+1\ge 2(\lceil m/2\rceil)^{h-1}\Rightarrow h\le log_{\lceil m/2\rceil}(\frac{n+1}{2})+1$
  
  ![image-20210722020359087](../assets/image-20210722020359087.png)

例：3阶B树共8个关键字，高度范围：$log_39=2\le h\le 1+log_24.5$

#### B树查找

- 对某个子树结点x，先顺序查找关键字，若找到则返回 $(结点, 关键字索引)$

  若 `k < x->key[i]`，则从磁盘读取 `x->p[i]` 页面到内存，递归查找 `x->p[i]` 结点

  若 x 是空叶结点，返回空

```cpp
tuple<Node*,int> BTree_Search(Node* x, int k) {
	int i = 1;
    for (; i <= x->n && k >= x->key[i]; i++);
    if (i <= x->n && k == x->key[i])
        return (x, i);
    else if (x->leaf)
        return NULL;
    //DISK_READ(x, x->p[i]);
    return BTree_Search(x->p[i], k);
}
```

#### B树插入

插入位置是终端结点，插入后可能需要调整：结点自底(向上)分裂(甚至升高)；保证每个结点关键字数 $[\lceil m/2\rceil-1,m-1]$

- 插入后若关键字数 = m，则对结点分裂：
- 若为根结点，则向上新建根结点作为父节点，B树高度+1
- 若父结点关键字数 < m-1 未满，则新建结点；在原结点中间划分$[1...\lceil m/2\rceil-1],\lceil m/2\rceil,[\lceil m/2\rceil+1...m]$，左部分在原结点，右部分放新节点，中间插入到其父节点；
- 若父结点关键字数 = m-1 满了，则对父节点分裂

例：5阶B树插入关键字：

![image-20210722031729166](../assets/image-20210722031729166.png)

#### B树删除

删除后，可能需要移动替换或合并；保证每个结点关键字数 $\ge \lceil m/2\rceil-1$

- 关键字在终端结点（删除前）：

  - 关键字数 $>\lceil m/2\rceil-1$，直接删除

  - 关键字数 $=\lceil m/2\rceil-1$，若左(右)兄弟结点存在关键字数 $>\lceil m/2\rceil-1$，则该兄弟上去一个关键字，父结点下来一个关键字替换；

    ![image-20210722042023677](../assets/image-20210722042023677.png)
    
  - 关键字数 $=\lceil m/2\rceil-1$，若左(右)兄弟结点关键字数均 $=\lceil m/2\rceil-1$，则父结点下来一个关键字替换被删关键字，将该节点与兄弟结点合并；

    ![image-20210722042103157](../assets/image-20210722042103157.png)
    
    合并时若父节点关键字数$-1=\lceil m/2\rceil-1$，则继续替换或合并；可能减少到0，则合并后结点作为根节点

- 关键字不在终端结点，可用其前驱结点最右关键字（或后继结点最左关键字）替代；前驱后继结点一定是终端结点，再用上述方法删除终端结点的关键字

### B+树

m阶B+树的定义：

- 若节点数N=0，为空树；

- 若节点数N>0，则每个分支结点至多m棵子树，至多m个关键字；结点孩子数=索引(或关键字)数

  根结点（非叶）子树棵数 $[2,m]$

  普通结点（非根）子树棵数 $[\lceil m/2\rceil,m]$

  所有分支结点包含其各子节点最大索引（或关键字）及其指针，仅起到索引作用

  所有叶结点都在同一层，包含全部关键字及指向对应记录的指针

  结点索引（或关键字）从左到右递增有序，相邻叶结点从小到大相连形成线性链表

![image-20210722045151679](../assets/image-20210722045151679.png)

B+树的每次查找都是一条从根结点到叶结点的路径

## 5. 散列表

### 概念

**散列函数**：一个把查找表中的关键字映射成该关键字对应地址的函数.

*addr=Hash(key)* (addr：数组索引、内存地址)

**冲突**：$\exist\ k_1\ne k_2,\ H(k_1)=H(k_2)$ 散列函数把多个不同关键字映射到同一地址

**同义词**：映射到同一地址发生碰撞的不同关键字

**散列表**：根据关键字直接进行访问的数据结构，它建立了关键字和存储地址之间的直接映射关系，理想情况下，查找的时间复杂度 $O(1)$

### 散列函数的构造方法
原则:

- 散列函数的 **定义域需包含全部需要存储的关键字**，而值域范围依赖于散列表大小或地址范围

- 散列函数计算出来的 **地址应该能等概率, 均匀地分布** 在整个地址空间中，以减少冲突的发生

- 散列函数应尽量简单, 能在较短时间内计算出任一关键字的散列地址



#### 直接定址法

取关键字的某个线性函数值为散列地址：

$H(key)=key,\ or\ H(key)=a·key+b$

特点：适合关键字分布基本连续（否则不连续会造成多空位）

#### 除留余数法 (简单)
假定散列表表长 m，取质数 p，满足 $p\le m,p\rightarrow m$

$H(key)=key \% p$

特点：等概率地散列

### 冲突处理方法
冲突处理：即为产生冲突的关键字寻找下一个“空”的 Hash 地址

- 用 $H_i$ 表示处理冲突中第 i 次探测得到的散列地址
- 假设得到的另一散列地址 $H_1$ 仍发生冲突，继续求下一地址 $H_2$，直到 $H_k$ 不发生冲突位置

#### 开放定址法
空闲地址既向它的同义词表项开放，又向它的非同义词表项开放

递推式：$H_i=(H(key)+d_i)\%m$

$H(key)$ 散列函数，m 散列表表长，$d_i$ 增量序列

##### 增量序列取法
- **线性探测法** $d_i=0,1,2,...,m-1$，冲突发生时，顺序查找表中下一单元，直到找到一个空闲单元
  
  问题：可能使第 i 个散列地址的同义词存入第 i+1 个散列地址，本来应存入第 i+1 个散列地址的元素争夺第 i+2 个散列地址的元素的地址，造成大量元素在相邻散列地址上“**聚集堆积**”，降低查找效率

- **平方探测法** $d_i=0,1^2,-1^2,2,-2^2,...,i^2,-i^2\ (i\leq m/2,\ m\xlongequal{素数}4k+3 )$

  特点：可避免“堆积”问题，但不能探测散列表所有单元（至少一半）

- **再散列法** $d_i=Hash_2(key)$，第二个散列函数计算关键字的地址增量
  
  $H_i=(H(key)+i·Hash_2(key))\%m$（ i 为冲突次数）

- **伪随机序列法** $d_i=$ 伪随机数序列

> 注意：在开放定址情形下，不能随便物理删除表中的已有元素，因为若删除元素，则会截断其他具有相同散列地址的元素的查找地址；应做一个删除标记——逻辑删除

#### 分离链接法
为了避免非同义词发生冲突，可把所有同义词存储在一个线性链表中，这个线性链表由其散列地址唯一标识，即散列地址 i 的同义词链表的头指针存放在散列表第 i 个单元中

![image-20210723182411336](../assets/image-20210723182411336.png)

### 散列查找及性能分析
查找步骤: 

- 初始化地址 $addr=Hash(key)$

- 若 `HashTable[addr]` 为空，则查找失败；

- 若 `HashTable[addr]==key` ，则查找成功；

  否则用冲突处理计算下一散列地址：`addr=Hi(key)`，继续探测；

**查找成功的 ASL**：对 HashTable 中每个关键字的比较次数。查找一关键字不冲突时比较1次，冲突一次时比较次数+1

**查找失败的 ASL**：对 HashTable 中每个地址 i 从该位置到空位置的比较次数。

例：关键字序列 $keys[]=\{19,14,23,01,68,20,84,27,55,11,10,79\}$，散列构造函数 $H(key)=key \% 13$，散列表长 L=16；

用线性探测法处理冲突，递推式：$H_i=(H(key)+i)\%16,\ d_i=i$

![image-20210723182235458](../assets/image-20210723182235458.png)

查找 key=84：$H(84)=6,\ L[6]\neq$ 84

处理冲突：$H_1(84)=(6+1)\%16=7,\ L[7]\neq 84$

处理冲突：$H_2(84)=(6+2)\%16=8,\ L[8]=84$，查找成功

![image-20210723182315276](../assets/image-20210723182315276.png)

查找成功的 ASL=(1x6+2+3x3+4+9)/keys.size=2.5​

**查找效率的影响因素**

- 散列函数
- 冲突处理方法
- 装填因子：$\alpha=\frac{表中记录数n}{散列表长度m}$



**平均查找长度ASL影响因素**：装填因子 $\alpha$ 

$\alpha$ 越大，记录越满，发生冲突的可能性越大

## 6. 字符串模式匹配-KMP算法

> 给定字符串 `T[0..N-1]` 和模式 `P[0..M-1]` ，写一个函数`search(string P, string T)` 打印所有的 `P` 出现在 `T` 中的位置（*n > m*）

**有限状态自动机**

状态集合 {0...7}，初始状态 0，接受状态 7，有向弧：根据输入发生状态转移

![image-20210723050411993](../assets/image-20210723050411993.png)

![image-20210723050620625](../assets/image-20210723050620625.png)

**KMP 算法思想**

KMP 算法预处理模式串 `pat`，构造一个状态转移数组 `lps[M]`，用来跳过已经匹配的字符串：

若 `pat[k+1]!=T[i]`，则 `k=lps[k]`（k：已匹配的末位索引 `pat[0...k]`，k+1：已匹配长度，下一个待匹配索引）

$lps[i]$：the longest proper prefix of $pat[0..i]$ which is also a suffix of $pat[0..i]$.（恰当的前缀不包含字符串的末位，恰当的后缀不包含字符串的首位）

$lps[i]=max\{k+1:\ k<i,\ pat[0...k]\sqsupset pat[0...i]\}$

[Examples of lps[] construction:](https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/)

```
For the pattern “AAAA”, 
lps[] is [0, 1, 2, 3]

For the pattern “ABCDE”, 
lps[] is [0, 0, 0, 0, 0]

For the pattern “AABAACAABAA”, 
lps[] is [0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5]

For the pattern “AAACAAAAAC”, 
lps[] is [0, 1, 2, 0, 1, 2, 3, 3, 3, 4] 

For the pattern “AAABAAA”, 
lps[] is [0, 1, 2, 0, 1, 2, 3]
```

根据《算法导论》kmp 算法伪代码 [修正索引从0开始](https://www.hackerearth.com/practice/algorithms/string-algorithm/string-searching/tutorial/)

```cpp
void prefix(const string pat, int lps[]) {
  int m = pat.size();
  int k = 0;
  lps[0] = 0;
  for (int i=1; i<m; i++) {
    while (k > 0 && pat[k] != pat[i])
      k = lps[k-1];
    if (pat[k] == pat[i])
      k++; //update length and also the next compared index
    lps[i] = k;
  }
}
```



```cpp
//example: kmp("ababaca", "abababacaba");
void kmp(const string P, const string T) {
  const int m = P.size();
  const int n = T.size();
  int lps[m] = {0};
  int k = 0;
  prefix(P, lps);
  for (int i=0; i<n; i++) {
    while (k > 0 && P[k] != T[i])
      k = lps[k-1];
    if (P[k] == T[i]) {
      k++; //update length and also the next compared index
      if (k == m) {
        cout << "found pattern at index " << i-(k-1);
        k = lps[k-1]; //look for the next match
      }
    }
  } 
}
```

**习题**

![image-20210723171917447](../assets/image-20210723171917447.png)

