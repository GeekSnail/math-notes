**考纲**

文件：文件概念，**文件元数据和索引节点(inode)**，文件的操作：建立/删除/打开/关闭/读/写，文件逻辑结构，**文件物理结构**，文件保护

目录：概念，树形目录，**目录的操作**，硬链接和软链接，

文件系统：文件系统全局结构(layout)，**文件系统在外存/内存中的结构**，外存空闲空间管理，虚拟文件系统，**文件系统挂载(mounting)**

**知识框架**

![image-20210811031519672](../assets/image-20210811031519672.png)

[linux/fs.h](https://elixir.bootlin.com/linux/v3.0/source/include/linux/fs.h) | [linux/fs_struct.h](https://elixir.bootlin.com/linux/v3.0/source/include/linux/fs_struct.h) | [linux/dcache.h](https://elixir.bootlin.com/linux/v3.0/source/include/linux/dcache.h) | [linux/mount.h](https://elixir.bootlin.com/linux/v3.0/source/include/linux/mount.h)

真题考点：

- 设置文件目录的目的，文件结构及其功能，文件相关系统调用过程(open/read/write/delete)，符号/硬链接/引用计数，文件访问优化，多进程访问同一文件
- 文件物理结构，索引结点inode，索引与磁盘访问块，位图与磁盘块，管理空闲磁盘块的结构，磁盘空间分配，文件目录结构与文件数量上限
- SCAN电梯调度，磁头移动过程，磁盘格式化，调度算法与访问磁道的关系，磁盘快/扇区/内存块大小关系

## 1. 文件
### 文件概念

- 文件：包含指向目录项的指针
- 目录项：名称，指向索引结点的指针
- 索引结点：文件属性等元数据

### 文件元数据和索引节点(inode)

索引结点：文件属性等元数据

### 文件操作

create, open, read, write, seek, delete

truncate：文件属性不变，擦除内容，释放空间

#### 文件的打开与关闭

- open：根据文件名搜索到目录项，将其链接到系统打开文件表，引用计数 `count++`，返回文件描述符 fd，用来操作文件
- close：引用计数 `count--`，若 `count==0`，且文件执行了写入，则先写回外存，再删除文件结构及打开文件表的目录项

### 文件逻辑结构

- 字符流，如：源代码、目标代码文件

- 记录型文件：文件由一组相似的记录组成，每个记录包含若干个域名及对应的域值（基本数据项）

  - 顺序文件：记录包含一个关键字，用来唯一标识该记录；

    定长记录文件支持随机访问；平均查找 n/2 次

  - 索引文件：索引项顺序排列，存放文件指针，支持随机访问；共 n 个索引项

  - 索引顺序文件：索引项按文件关键字顺序排列，索引项包含关键字、指向一组文件的起始位置；共 $\sqrt n$ 个索引项；平均查找 $\sqrt n$ 次（查找索引、文件组内查找均为 $\frac{1}{2}\sqrt n$ ）

  - 散列文件：Hash Bucket 存储，$addr = Hash(key)$

### 文件物理结构



### 文件保护

#### 访问控制

**设置用户权限**

文件所属用户类型：owner, group, other

每个用户类型的操作类型：r, w, x（用户可 `cd` 到设置了 `x` 的子目录）

```c
drwxr-xr-x 1 35398 197609     0 8月  13 05:41 ./
drwxr-xr-x 1 35398 197609     0 8月   1 23:02 ../
-rw-r--r-- 1 35398 197609 17868 8月  13 05:41 file.md
```

**设置口令/密码**

加密/解密文件

## 2. 目录

### 目录概念

- 文件：包含指向目录项的指针
- 目录项：名称，指向索引结点的指针
- 索引结点：文件属性等元数据

### 目录结构

- ~~单级目录~~；一个目录项对应一个文件，按名存取；不允许重名，不适用多用户系统
- ~~两级目录~~：主目录包含若干用户目录，一个用户目录项指向一个单级目录表；没有对文件分类
- **树形目录**：由根目录逐层向下级联，进程相关的文件目录信息包括：根目录、当前工作目录 `pwd`；便于分类管理，但不便于实现文件共享
- ~~无环图目录~~：在树形目录基础上增加指向同一结点的有向边，结点包含使用计数器，实现文件共享

![image-20210813042752008](../assets/image-20210813042752008.png)

### 目录操作



### 硬链接和软链接

#### 索引结点（硬链接）

硬链接目录项的 `d_inode` 指向目标路径末端目录项对应的同一文件的 inode

即同一文件的 inode 可被若干不同路径的末端目录项 `d_inode` 指针引用

索引结点硬链接使用计数 `i_nlink` 为 0 时删除该文件

```c
int (*link) (struct dentry *old_dentry,struct inode *dir,struct dentry *dentry);
```

![image-20210813053315134](../assets/image-20210813053315134.png)

####符号链接

符号链接目录项的 `d_inode` 指向一个独立的 inode，该 inode 数据段包含目标路径的字符串；

文件删除后，其对应的符号链接均无效

```c
int (*symlink) (struct inode *dir,struct dentry *dentry,const char *symname);
```

## 2. 文件系统
### 文件系统结构(layout)
- 系统调用接口
- 虚拟文件系统VFS
- 各类独立文件系统，如：FAT32, NTFS, ext2/3/4, UFS, NFS, iso9660(CD-DOM), proc
- 设备驱动

#### 文件系统的外存结构



#### 文件系统的内存结构



### ~~目录实现~~

- 线性表
- hash表，根据文件名得到一个地址，指向线性列表的某个元素

### ~~文件存储块分配~~

#### 连续分配

文件在磁盘上占有一组连续的块，分配表目录项包含文件起始块号、块数

优点：支持顺序且直接访问，磁盘寻道数与寻道时间最小

缺点：文件长度不便动态增加（只适用长度固定的文件）

![image-20210813205819956](../assets/image-20210813205819956.png)

#### 链式分配

文件在磁盘上离散在不同位置的块

- 隐式：分配表目录项包含文件起始块号、最后一块号或块数，每个块隐式包含指向下一块号（磁盘链式查找）
- 显式：每个磁盘建立文件分配表FAT，存放所有物理块号，表的每一项包含指向该表下一分配项的指针（分配表链式查找）

优点：支持文件长度动态增长（动态分配）

缺点：需为文件多个块分配指针空间，不支持文件的直接访问，指针的可靠性问题

![image-20210813212946320](../assets/image-20210813212946320.png)

#### 索引分配

每个文件有一个索引块，存放文件若干物理块号，分配表目录项包含文件索引块号

优点：支持直接访问

缺点：需为索引块分配空间，索引块分配大小未知

![image-20210813205937411](../assets/image-20210813205937411.png)

**解决索引块分配问题**

- 一个物理块包含多个索引块
- 多级索引：针对大文件，一级索引块指向下一级索引块，最后一级索引块指向文件块
- 组合索引：直接索引块指向文件块，多级索引块指向下一级索引块

![image-20210813215136343](../assets/image-20210813215136343.png)

分配方式比较

![image-20210813213614751](../assets/image-20210813213614751.png)

### 磁盘空闲块管理

块设备的扇区长度都是512字节

块设备的块长度则有512、1024、2048、4096字节等。块的最大长度受特定体系结构的内存页长度的限制。如：IA-32系统支持的块长度为4096字节（内存页长度是4096字节）

设备驱动程序一次从块设备取出一个完全块的数据，因此对块设备的访问有大规模的缓存

#### 空闲表

表项包含：起始空闲块号，空闲块数

空闲块的分配类似内存块的动态分配

#### 空闲链表

- 空闲块链：每个空闲块包含指向下一空闲块的指针
- 空闲区链：将连续的空闲块内部链接成为一个空闲区，每个空闲区包含指向下一空闲块的指针（二维链式）

#### 位图/位表

每个字包含固定bit位长度，每一个bit位表示块，空闲0，已分配1

![image-20210814015205828](../assets/image-20210814015205828.png)

一个内存块可表示的磁盘块数 = 8*块大小(B)，磁盘总块数 = 磁盘容量(B) / 块大小(B)

位表占用的内存块字节数(B) = 磁盘总块数 / (8块/B) = 磁盘容量(B) / (8*块大小(B))

#### 成组链接

初始 0 号扇区保存第一组顺序 $1...n$​​​ 号空闲扇区地址，组末 n 号扇区存储第二组顺序 $n+1...2n$​​​ 号空闲扇区地址；……

![image-20210814014532857](../assets/image-20210814014532857.png)

### 虚拟文件系统VFS
文件结构：文件目录、文件操作

文件目录结构：目录名，索引结点、目录操作

索引结点结构：索引结点操作、文件操作、地址空间映射

一个文件系统对应一个超级块，超级块维持一个打开文件表；一个进程对应一个打开文件表

![image-20210812045931794](../assets/image-20210812045931794.png)

#### VFS 结构

```
super_block─╮
			file->dentry->inode->address_space->page
task_struct─╯
```

![image-20210812050025594](../assets/image-20210812050025594.png)

![image-20210812050107388](../assets/image-20210812050107388.png)

##### inode

```c
/* linux/fs.h#L738 */
struct inode {
    struct hlist_node	i_hash;
    struct list_head	i_list;
    struct list_head    i_sb_list;
    struct list_head    i_dentry; /* 所依附的同名硬链接目录 */
    unsigned long		i_ino; /* 编号标识 */
    atomic_t		    i_count; /* 使用计数，访问该inode结构的进程数目 */
    unsigned int	    i_nlink; /* 计数器，记录使用该inode的硬链接总数 */
    uid_t			    i_uid;
    gid_t			    i_gid;
    dev_t			    i_rdev; /* 表示与哪个设备进行通信 struct block_device */
    unsigned long	    i_version;
    loff_t			    i_size; /* 文件字节长度 */
    struct timespec	    i_atime; /* 最后访问的时间 */
    struct timespec	    i_mtime; /* 最后修改的时间 */
    struct timespec	    i_ctime; /* 最后修改inode的时间 */
    unsigned int	    i_blkbits; /* block size in bits */
    blkcnt_t		    i_blocks; /* 文件块长度 */
    umode_t			    i_mode; /* 文件类型和访问权限 */
    struct inode_operations *i_op; /* 管理文件结构性及元数据的操作 */
    const struct file_operations *i_fop; /* 操作文件中包含的数据 */
    struct super_block	*i_sb;
    struct address_space *i_mapping;
    struct address_space i_data; /* mapping for device */
    struct dquot	    *i_dquot[MAXQUOTAS]; /* disk quotas for inode */
    struct list_head    i_devices; /* 设备文件链表 */
    union {
        struct pipe_inode_info *i_pipe; /* 用于实现管道的inode的相关信息 */
        struct block_device *i_bdev; /* 用于块设备 */
        struct cdev *i_cdev; /* 用于字符设备 */
    };
    int				    i_cindex;
    __u32			    i_generation;
    unsigned long	    i_state;
    unsigned long	    dirtied_when; /* 第一个脏操作发生的时间，以jiffies计算 */
    unsigned int	    i_flags;
    atomic_t		    i_writecount;
    void			    *i_security;
}; 
```

##### inode_operations 

管理文件结构性及元数据的操作

```c
struct inode_operations {
    int (*create) (struct inode *,struct dentry *,int, struct nameidata *);
    struct dentry * (*lookup) (struct inode *,struct dentry *, struct nameidata *); /* 根据文件名查找其inode实例 */
    int (*link) (struct dentry *old_dentry,struct inode *dir,struct dentry *dentry); /* create a hard link of the file `old_dentry` in the directory `dir` with the new filename `dentry` */
    int (*unlink) (struct inode *dir,struct dentry *dentry); /* remove the inode specified by the directory entry `dentry` from the directory `dir` */
    int (*symlink) (struct inode *dir,struct dentry *dentry,const char *symname); /*  create a symbolic link named `symname` to the file represented by `dentry` in the directory `dir` */
    int (*mkdir) (struct inode *,struct dentry *,int);
    int (*rmdir) (struct inode *,struct dentry *);
    int (*mknod) (struct inode *,struct dentry *,int,dev_t);
    int (*rename) (struct inode *, struct dentry *, struct inode *, struct dentry *);
    int (*readlink) (struct dentry *dentry, char __user *buffer,int buflen); /* copy at most `buflen` bytes of the full path associated with the symbolic link specified by `dentry` into the specified `buffer` */
    void * (*follow_link) (struct dentry *, struct nameidata *); /* 根据符号链接查找目标文件的inode */
    void (*put_link) (struct dentry *, struct nameidata *, void *);
    void (*truncate) (struct inode *); /* 指定inode的长度 */ 
    int (*permission) (struct inode *, int, struct nameidata *);
    int (*setattr) (struct dentry *, struct iattr *);
    int (*getattr) (struct vfsmount *mnt, struct dentry *, struct kstat *);
    /* xattr: 建立、读取、删除文件的扩展属性 */
    int (*setxattr) (struct dentry *, const char *,const void *,size_t,int);
    ssize_t (*getxattr) (struct dentry *, const char *, void *, size_t);
    ssize_t (*listxattr) (struct dentry *, char *, size_t);
    int (*removexattr) (struct dentry *, const char *);
    void (*truncate_range)(struct inode *, loff_t, loff_t); /* 截断一个范围内的块 */
    long (*fallocate)(struct inode *inode, int mode, loff_t offset, loff_t len); /* 对文件预先分配空间 */
};
```

##### file

```c
/* linux/fs.h#L738 */
struct file {
	/* fu_list becomes invalid after file_free is called and queued via
	 * fu_rcuhead for RCU freeing */
	union {
		struct list_head	fu_list;
		struct rcu_head 	fu_rcuhead;
	} f_u;
	struct path		f_path;
#define f_dentry	f_path.dentry
#define f_vfsmnt	f_path.mnt
	const struct file_operations	*f_op;
	spinlock_t		f_lock;  /* f_ep_links, f_flags, no IRQ */
	atomic_long_t		f_count;
	unsigned int 		f_flags;
	fmode_t			f_mode;
	loff_t			f_pos;
	struct fown_struct	f_owner; /* 处理该文件的进程有关的信息 */
	const struct cred	*f_cred;
	struct file_ra_state	f_ra; /* 预读取特征 */
	u64			f_version;
	struct address_space	*f_mapping; /* 指向属于文件相关的inode实例的地址空间映射 */
};
```

##### file_operations

操作文件中包含的数据

```c
struct file_operations {
	struct module *owner;
	loff_t (*llseek) (struct file *, loff_t, int);
	ssize_t (*read) (struct file *, char __user *, size_t, loff_t *);
	ssize_t (*write) (struct file *, const char __user *, size_t, loff_t *);
	ssize_t (*aio_read) (struct kiocb *, const struct iovec *, unsigned long, loff_t); /* 异步读取 */
	ssize_t (*aio_write) (struct kiocb *, const struct iovec *, unsigned long, loff_t);
	int (*readdir) (struct file *, void *, filldir_t);
	unsigned int (*poll) (struct file *, struct poll_table_struct *); /* 用于poll和select系统调用，以便实现同步的I/O多路复用 */
    /* ioctl用于与硬件设备通信 */
	long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);
	long (*compat_ioctl) (struct file *, unsigned int, unsigned long);
	int (*mmap) (struct file *, struct vm_area_struct *);
	int (*open) (struct inode *, struct file *);
	int (*flush) (struct file *, fl_owner_t id); /* 文件描述符关闭时将调用，引用计数-1 */
	int (*release) (struct inode *, struct file *); /* file对象的使用计数器到0时调用 */
	int (*fsync) (struct file *, int datasync); /* 由fsync和fdatasync系统调用使用，用于将内存中的文件数据与存储介质同步 */
	int (*aio_fsync) (struct kiocb *, int datasync);
	int (*fasync) (int, struct file *, int); /* 启用/停用由信号控制的输入和输出 */
	int (*lock) (struct file *, int, struct file_lock *);
	ssize_t (*sendpage) (struct file *, struct page *, int, size_t, loff_t *, int); /* 通过sendfile系统调用在两个文件描述符之间交换数据 */
	unsigned long (*get_unmapped_area)(struct file *, unsigned long, unsigned long, unsigned long, unsigned long);
	int (*check_flags)(int);
	int (*flock) (struct file *, int, struct file_lock *);
	ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int); /* 从管道向文件传输数据 */
	ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
};
```

##### 与进程有关的文件信息

```c
struct task_struct {
    ...
    /* 文件系统信息 */
    struct fs_struct *fs;
    /* 打开文件信息 */
    struct files_struct *files;
    /* 命名空间 */
    struct nsproxy *nsproxy;
	...
}
```

```c
/* linux/fs_struct.h */
struct fs_struct {
	int users;
	spinlock_t lock;
	seqcount_t seq;
	int umask; /* 标准的掩码，用umask命令读取或设置新文件的权限 */
	int in_exec;
	struct path root, pwd; /* 进程相关的根目录、工作目录及各自所挂载的虚拟文件系统 */
};
/* linux/path.h */
struct path {
	struct vfsmount *mnt;
	struct dentry *dentry;
};
```

##### dentry 目录项缓存

只包含文件系统结构中最常用文件和目录对应的目录项

```c
/* linux/dcache.h */
struct dentry {
    atomic_t d_count;
    /*	DCACHE_DISCONNECTED:该dentry未连接到超级块的dentry树，
    	DCACHE_UNHASHED:	该dentry没有包含在任何inode的散列表中 */
    unsigned int d_flags;	
    spinlock_t d_lock;		/* 每个dentry的锁 */
    struct inode *d_inode;	/* 文件名所属的inode，如果为NULL，则表示不存在的文件名 */
    /* 接下来的3个字段由__d_lookup处理
     * 将它们放置在这里，使之能够装填到一个缓存行中*/
    struct hlist_node d_hash;	/* 用于查找的散列表 */
    struct dentry *d_parent;	/* 父目录的dentry实例 */
    struct qstr d_name;
    struct list_head d_lru;		/* LRU链表 */
    union {
        struct list_head d_child;
        /* 链表元素，用于将当前dentry连接到父目录dentry的d_subdirs链表中 */
        struct rcu_head d_rcu;
    } d_u;
    struct list_head d_subdirs;	/* 子目录/文件的目录项链表 */
    struct list_head d_alias;	/* 链表元素，用于将dentry连接到inode的i_dentry链表中 */
    unsigned long d_time;		/* 由d_revalidate使用 */
    struct dentry_operations *d_op;
    struct super_block *d_sb;	/* dentry树的根，超级块 */
    void *d_fsdata;				/* 特定于文件系统的数据 */
    int d_mounted;
    unsigned char d_iname[DNAME_INLINE_LEN_MIN]; /* 短文件名存储在这里 */
};
```

#### 处理VFS对象

##### file_system_type 注册

```c
/* linux/fs.h */
struct file_system_type {
    const char *name; /* 文件系统名，如reiserfs、ext3等 */
    int fs_flags;
    struct dentry *(*mount) (struct file_system_type *, int, const char *, void *);
    void (*kill_sb) (struct super_block *);
    struct module *owner;
    struct file_system_type * next;
    struct list_head fs_supers;
};
```

##### vfsmount 挂载的VFS

```c
/* linux/mount.h */
struct vfsmount {
    struct list_head mnt_hash;
    struct vfsmount *mnt_parent; /* 装载点所在的父文件系统 */
    struct dentry *mnt_mountpoint; /* 装载点在父文件系统中的dentry */
    struct dentry *mnt_root; /* 当前文件系统根目录的dentry */
    struct super_block *mnt_sb; /* 指向超级块的指针 */
    struct list_head mnt_mounts; /* 子文件系统链表 */
    struct list_head mnt_child; /* 链表元素，用于父文件系统中的mnt_mounts链表 */
    int mnt_flags;
    char *mnt_devname; /* 设备名称，例如/dev/dsk/hda1 */
    struct list_head mnt_list;
    struct list_head mnt_expire; /* 链表元素，用于特定于文件系统的到期链表中 */
    struct list_head mnt_share; /* 链表元素，用于共享装载的循环链表 */
    struct list_head mnt_slave_list;/* 从属装载的链表 */
    struct list_head mnt_slave; /* 链表元素，用于从属装载的链表 */
    struct vfsmount *mnt_master; /* 指向主装载，从属装载位于master->mnt_slave_list
    链表上 */
    struct mnt_namespace *mnt_ns; /* 所属的命名空间 */
    /* 我们把mnt_count和mnt_expiry_mark放置在struct vfsmount的末尾，
     * 以便让这些频繁修改的字段与结构的主体处于两个不同的缓存行中
     * （这样在SMP机器上读取mnt_flags不会造成高速缓存的颠簸）*/
    atomic_t mnt_count;
    int mnt_expiry_mark; /* 如果标记为到期，则其值为true */
};
```

##### super_block 

```c
struct super_block {
	struct list_head	s_list;		/* Keep this first */
	dev_t			s_dev;		/* search index; _not_ kdev_t */
	unsigned char		s_dirt;
	unsigned char		s_blocksize_bits;
	unsigned long		s_blocksize;
	loff_t			s_maxbytes;	/* Max file size */
	struct file_system_type	*s_type;
	const struct super_operations	*s_op;
	const struct dquot_operations	*dq_op;
	const struct quotactl_ops	*s_qcop;
	const struct export_operations *s_export_op;
	unsigned long		s_flags;
	unsigned long		s_magic;
	struct dentry		*s_root; /* 全局根目录 */
	struct rw_semaphore	s_umount;
	struct mutex		s_lock;
	int			s_count;
	atomic_t		s_active;
	const struct xattr_handler **s_xattr;

	struct list_head	s_inodes;	/* all inodes */
	struct hlist_bl_head	s_anon;		/* anonymous dentries for (nfs) exporting */
    struct list_head	s_files; /* 超级块表示的文件系统上所有打开的文件 */
	/* s_dentry_lru, s_nr_dentry_unused protected by dcache.c lru locks */
	struct list_head	s_dentry_lru;	/* unused dentry lru */
	int			s_nr_dentry_unused;	/* # of dentry on lru */

	struct block_device	*s_bdev;
	struct backing_dev_info *s_bdi;
	struct mtd_info		*s_mtd;
	struct list_head	s_instances;
	struct quota_info	s_dquot;	/* Diskquota specific options */

	int			s_frozen;
	wait_queue_head_t	s_wait_unfrozen;

	char s_id[32];				/* Informational name */
	u8 s_uuid[16];				/* UUID */
	void 			*s_fs_info;	/* Filesystem private info */
	fmode_t			s_mode;
	u32		   s_time_gran; /* Granularity of c/m/atime in ns. Cannot be worse than a second */
};
```

##### 查找inode

根据给定的文件名查找 inode，`nameidata `结构用来向查找函数传递参数，并保存查找结果

```c
/* fs.h */
struct nameidata {
    struct dentry	*dentry;
    struct vfsmount	*mnt;
    struct qstr		last; /* 包含字符串，字符串的长度和一个散列值 */
    unsigned int	flags;
    ...
}
```

内核使用 `path_lookup` 函数查找路径或文件名

```c
/* fs/namei.c */
int fastcall path_lookup(const char *name, unsigned int flags, struct nameidata *nd)
```

##### 内存地址空间

```c
/* linux/fs.h */
struct address_space {
    struct inode *host; /* 所有者：inode，或块设备 */
    struct radix_tree_root page_tree; /* 所有页的基数树 */
    unsigned int i_mmap_writable; /* VM_SHARED映射的计数 */
    struct prio_tree_root i_mmap; /* 私有和共享映射的树 */
    struct list_head i_mmap_nonlinear; /* VM_NONLINEAR映射的链表元素 */
    unsigned long nrpages; /* 页的总数 */
    pgoff_t writeback_index; /* 回写由此开始 */
    struct address_space_operations *a_ops; /* 方法，即地址空间操作 */
    unsigned long flags; /* 错误标志位/gfp掩码 */
    struct backing_dev_info *backing_dev_info; /* 设备预读 */
    struct list_head private_list;
}
struct address_space_operations {
    int (*writepage)(struct page *page, struct writeback_control *wbc);//将一页的内容从物理内存写回到块设备上对应的位置
    int (*readpage)(struct file *, struct page *); //从块设备读取一页到物理内存
    ...
    /* 回写该映射的一些脏页。 */
    int (*writepages)(struct address_space *, struct writeback_control *);
    /* 将页设置为脏的。如果设置成功则返回true。 */
    int (*set_page_dirty)(struct page *page);
    int (*readpages)(struct file *filp, struct address_space *mapping,
    struct list_head *pages, unsigned nr_pages);
    ...
};
```

### 文件系统挂载(mounting)

