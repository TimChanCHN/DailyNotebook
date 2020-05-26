# C++学习
## 1. 引用
1. 定义： 某一个变量或对象的别名，对引用的操作与对其所绑定的变量或对象的操作完全等价；
        引用变量并不会新开辟一片空间，其对应的空间与原变量同属一片空间。
2. 备注：
   1. &不是求地址运算符，而是起标志作用；
   2. 引用的类型必须和其所绑定的变量的类型相同；
   3. 声明引用的同时必须对其初始化；
   4. 引用相当于变量或对象的别名，因此不能再将已有的引用名作为其他变量或对象的名字或别名；
   5. 对数组的引用：类型 (&引用名)[数组中元素数量]=数组名；
   6. 指针的引用：类型 *&引用名=指针名;【可以理解为：（类型*） &引用名=指针名，即将指针的类型当成类型*】
   7. 引用用作函数参数时，其作用和指针一样，都是对实参所在的地址进行操作，不过指针是需要开辟新的指针变量指向实参，而引用不是，
      所以引用效率更高
   8. 引用作为函数返回值，内存中不返回被返回值的副本，如一个右值一样
3. 右值引用&&：被定义为右值引用的变量，可以使用为右值，并且使用过程中不产生内存副本
4. [引用的详细说明](https://www.cnblogs.com/duwenxing/p/7421100.html)

## 2.类
1. 类：本质上是定义一个数据类型的蓝图，即定义了一个类的对象包括了的内容。
2. 类的成员函数
   1. 直接在类内部进行函数定义。
   2. 当在类内部进行函数声明时，需要在外部进行函数定义，此时需要使用范围解析运算符：：
   ```c++
   class A
   {
       public:
        int a;
        int b;
        int c;
        void D(void)
        {
            return NULL;
        }
   }；

   //或者
   void A::D(void)
   {
       return NULL;
   }
   ```

3. 类的访问修饰符
   1. public: 在类外部是可以访问的
   2. private: 在类的外部是不可访问的，甚至是不可查看的，只有类和友元函数可以访问私有成员。
    > private的读写只能在类中通过public来访问，因此不能直接赋值
   3. protect: 与private十分相似，保护成员在派生类中可访问。
   > 备注：
   > public 继承：基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：public, protected, private  
   > protected 继承：基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：protected, protected, private  
   > 基类 public 成员，protected 成员，private 成员的访问属性在派生类中分别变成：private, private, private

4. 类的构造函数
   1. 类的一种特殊的成员函数，它会在每次创建类的新对象时执行。它的名称与类的名称是完全相同的，并且不会返回任何类型，也不会返回 void。构造函数可用于为某些成员变量设置初始值。
   2. 带参数的构造函数：
        > 可以通过构造函数对private参数进行初始化。
   3. 使用初始化列表来初始化字段
   ```c++
    C::C( double a, double b, double c): X(a), Y(b), Z(c)       //a,b,c是实参，X,Y,Z是形参
    {
    ....
    }
   ```

5. 类的析构函数
   1. 类的一种特殊的成员函数，它会在每次删除所创建的对象时执行。名称与类的名称是完全相同的，只是在前面加了个波浪号（~）作为前缀，它不会返回任何值，也不能带有任何参数。析构函数有助于在跳出程序（比如关闭文件、释放内存等）前释放资源。
   2. 例子
   ```c++
    class A
    {
        public:
        A(args);        //构造函数
        ~A(args);      //析构函数
    }
   ```
   > 备注： 构造函数和析构函数无需调用，自动执行。

6. 拷贝构造函数
   1. 在创建对象时，是使用同一类中之前创建的对象来初始化新创建的对象
   2. 使用场合：
      1. 使用另一个同类型的对象来初始化新创建的对象；
      2. 复制对象把它作为参数传递给函数；
      3. 复制对象，并从函数返回这个对象。
   3. 形式:
   ```c++
    classname (const classname &obj) {
    // 构造函数的主体
    }
   ```
   1. 问题：
   > 使用这个拷贝构造函数时，当复制了多个对象时，会发现程序结束时，析构函数调用次数会比对象个数多一个。

7. 友元函数
   1. 定义在类外部，但有权访问类的所有私有（private）成员和保护（protected）成员。尽管友元函数的原型有在类的定义中出现过，但是友元函数并不是成员函数。
   2. 友元函数用friend修饰；
   3. 友元可以是一个函数，该函数被称为友元函数；友元也可以是一个类，该类被称为友元类，在这种情况下，整个类及其所有成员都是友元。

8. 内联函数
   1. 内联函数类似于宏定义，程序在编译器编译的时候，编译器将程序中出现的内联函数的调用表达式用内联函数的函数体进行替换；
   2. 在类定义中定义的函数都是内联函数；
   3. 内联函数使用inline修饰；
   4. 内联函数使用要点：
      1. 不允许使用循环语句和开关语句；
      2. 定义必须出现在内联函数第一次调用之前；
      3. 类结构中所在的类说明内部定义的函数是内联函数；
      4. 内联函数行数应该尽量少，一般10行以内。

9. this指针
   1.  在 C++ 中，每一个对象都能通过 this 指针来访问自己的地址。this 指针是所有成员函数的隐含参数。因此，在成员函数内部，它可以用来指向调用对象。
   2.  友元函数没有 this 指针，因为友元不是类的成员。只有成员函数才有 this 指针。
   3.  备注： 指向类的指针，类似于指向结构体的指针。 

10. 类的静态数据
    1.  当类的成员为静态时，无论创建多少个类的对象，静态成员都只有一个副本（即共用同一个成员）；
    2.  若没有对静态成员进行初始化时，创建第一个对象时所有静态数据会被初始化为0.
    3.  静态成员函数只能访问类中的静态成员变量，所以在该函数中没有this指针。

## 3. 类的继承
1. 继承允许依据原有的类定义一个新类，这使得创建和维护一个应用程序变得更容易。这样做，也达到了重用代码功能和提高执行效率的效果。
   原有的类称为基类，生成的类称为派生类。

2. 格式： class [派生类]：[修饰符] [基类类] 
   1. 公有继承public：当一个类派生自公有基类时，基类的公有成员也是派生类的公有成员，基类的保护成员也是派生类的保护成员，基类的私有成员不能直接被派生类访问，但是可以通过调用基类的公有和保护成员来访问；
   2. 保护继承protected： 当一个类派生自保护基类时，基类的公有和保护成员将成为派生类的保护成员；
   3. 私有继承private：私有继承（private）：当一个类派生自私有基类时，基类的公有和保护成员将成为派生类的私有成员。
   4. 备注：一般使用共有继承。

## 4. 重载函数和重载运算符
1. 重载函数
   1. 在同一个作用域内，可以声明几个功能类似的同名函数，但是这些同名函数的形式参数（指参数的个数、类型或者顺序）必须不同。
   ```c++
    class printdata
    {
        public:
            void print(int a)...
            void print(float b)...
            void print(char c[])...
    }
   ```
2. 重载运算符
   1. 重载的运算符是带有特殊名称的函数，函数名是由关键字 operator 和其后要重载的运算符符号构成的。
   2. 重载运算符可以实现多个同类对象之间运算。
3. [可重载运算符/不可重载运算符](https://www.runoob.com/cplusplus/cpp-overloading.html)

## 5. 多态
1. 当类之间存在层次结构，并且类之间是通过继承关联时，就会用到多态。[同一个事物在不同场景下的多种形态 ]
2. [多态的实例](https://www.runoob.com/cplusplus/cpp-polymorphism.html)
   > 当多个派生类与基类存在着同名的类内部函数，需要对基类的内部同名函数用`virtual`进行修饰，告诉编译器不要静态链接该函数。  
   > 使用基类对象的指针去访问派生类对象空间。
3. 纯虚函数：
   1. 用父类型别的指针指向其子类的实例，然后通过父类的指针调用实际子类的成员函数；
   2. 目的是让父类指针有多种形态
   ```c++
    //在基类中，如此定义纯虚函数
    virtual int func_name()  = 0;
   ```

4. 多态的形式
   1. 静态多态--重载函数就是一种静态多态；
   2. 动态多态--1)基类中必须包含虚函数，并在派生类中对基类的虚函数进行重写；2）通过街垒对象的指针或引用/调用虚函数
   > 函数并不占用空间，因此对于类所占用的空间而言，就是变量所占据的空间。但是对于拥有虚函数的类而言，则需要多出4个字节  
    （对于32位系统而言）的空间，用于存储虚函数地址，同时给派生类提供虚函数的地址。

## 6.lambda表达式
1. [函数对象参数](参数){函数体}
2. 匿名函数，可以看成是一种函数表达式
3. 可以看作是一种函数参数，把函数体赋值给参数


## 7.类模板和函数模板
1. 类模板
   1. 格式： template <typename 参数, typename 参数> （typename 可以用class代替）
   2. 作用： 定义一个类模板，可以用一套类模板，适用于不同数据类型的类，在实例的时候才会确定什么类型。
   3. 实例：
      ```c++
         template <typename T>
         class EXAMPLE
         {
            public:
            T  a;                   
            int b;
            T  c;
         }

         EXAMPLE<std::string> lizi;          // typename是std::string，因此成员变量a,c在该实例中类型是string
      ```
2. 函数模板
   1. 函数模板和类模板有同样的效果，作用对象是函数
   2. 例子：
      ```c++
         template <class T>
         void set_time(T a)
         {
            auto m_time = a;
         }

         set_time<int>(10);               // m_time被赋值10，并且类型为int
      ```

## 8.enum class
   1. 对于C/C++以前的枚举，只是有enum这个关键字定义。枚举的本质是宏，假如enum中有元素是和其他全局变量同名，会造成冲突。因此C++11推出了该enum class，
      从而可以在不同的enum中出现同名元素。
   2. 调用enum class的枚举类时，需要加上它的作用空间，否则编译器会报错。


## 9. 迭代器(iterator)
   > 一种检查容器内元素并遍历元素的数据类型（理解为容器里的一个实例）。C++更趋向于使用迭代器而不是下标操作，因为标准库为每一种标准容器定义了一种迭代器类型.
1. 说明实例
   ```c++
   // 定义以及初始化
   std::vector<int> vec;
   std::vector<int>::iterator iter = vec.begin();     // iter指向容器vec的第一个元素

   // 常用操作
   *iter                //对iter进行解引用，返回迭代器iter指向的元素的引用
   iter->men            //对iter进行解引用，获取指定元素中名为men的成员。等效于(*iter).men
   ++iter/iter++        //给iter加1，使其指向容器的下一个元素
   --iter/iter--        //给iter减1，使其指向容器的前一个元素
   iter1==iter2        //比较两个迭代器是否相等，当它们指向同一个容器的同一个元素或者都指向同同一个容器的超出末端的下一个位置时，它们相等 
   iter1!=iter2   

   // 只有容器vector/queue提供除==, !=以外的运算
   // 参与运算的迭代器，或者运算结果必须是指向容器中的元素或者超出容器末端的下一个元素
   iter+/-n     //在迭代器上加（减）整数n，将产生指向容器中钱前面（后面）第n个元素的迭代器。新计算出来的迭代器必须指向容器中的元素或超出容器末端的下一个元素
   iter1+=iter2

   // const_iterator， 只读迭代器不能修改的值
   std::vector<int>::const_iterator vec1;   
   
   ```

## 10.多线程


## 11.C++使用正则表达式
1. 正则表达式：描述了一种字符串匹配的模式（pattern），可以用来检查一个串是否含有某种子串、将匹配的子串替换或者从某个串中取出符合某个条件的子串等。
2. 标准C/C++均不支持正则表达式，若要使程序支持正则表达式的话，则需要添加额外库`<regex.h>`/`<regex>`;
3. 对于C++,编译正则表达式时，需要增加c++11：-std=c++11
4. 与正则表达式相关的库：
   ```c++
   #include <regex>

   /* 从标准输入流中获得键盘值 */
   !getline(cin,str);
   /* 定义一个正则表达式，存储到r中 */
   regex r("\\d");
   /* 定义一个容器，用于存储当字符串和正则表达式匹配后，存储结果到match[0]中 */
   smatch match;
   /* 匹配函数：用于判断参数1中是否符合参数3正则表达式的内容，有，则把内容送至match中，并返回1，无，返回0 */
   regex_match(str, match, r)；
   /* 查找函数：用于判断参数1中是否包含参数3正则表达式的内容，有，则返回1，无，返回0 */
   regex_search(str, r);
   /* 替换函数：找出参数1字符串中包含参数2正则表达式的内容，替换成参数3字符串，返回最终的字符串 */
   regex_replace(str, r, " ");
   /* 扩展函数：调整字符串内容 */
   string str = "Hello_2018!";	
   regex pattern2("(.{3})(.{2})_(\\d{4})");				         //匹配3个任意字符+2个任意字符+下划线+4个数字
   cout << regex_replace(str, pattern2, "$1$3") << endl;	      //输出：Hel2018，将字符串替换为第一个和第三个表达式匹配的内容
   cout << regex_replace(str, pattern2, "$1$3$2") << endl;	   //输出：Hel2018lo，交换位置顺序
   /* 忽略大小写：regex::icase：匹配时忽略大小写(Regex的语法选项) */
   regex_match("aaaAAA", regex("a*", regex::icase));              //结果为1
   ```
5. 对于预查（正向肯定预查、正向否定预查、反向肯定预查、反向否定预查），利用`regex_match`是无法获取到正确的字符串，要获取正确的字符串，需要用`regex_search`









# 附录
## 1. C++设计思想
1. 数据抽象
   1. 只向外界提供关键信息，并隐藏其后台的实现细节，即只表现必要的信息而不呈现细节。
   2. 是把代码分离成接口和实现，保持接口独立于实现，改变底层实现，接口也将保持不变
2. 数据封装
   1. 是一种把数据和操作数据函数捆绑在一起的机制，尽可能地减少数据地直接访问；
   2. 把变量定义为private，对变量操作则改为public。



# C++11新特性
## 1. 函数模板类
   > 所有模板类的<>中包含着参数的类型

1. std::function<>          
   1. <>里面为函数的型，结果是定义一个函数指针;等号右边可以是函数、lambda表达式等
   2. #include <functional>
   3. 实例：
   ```c++
      void display(int a)
      {
         ...;
      }

      std::function<void(int)> fp = display;
      display(4);
   ```
   

2. std::queue<>
   1. 定义一个队列，<>为该队列元素的类型
   2. #include <queue>
   3. 使用接口：
   ```c++
    std::queue<int> myqueue;
    myqueue.push(1);                    //把1放到该队列尾
    myqueue.pop();                      //弹出队首元素，不返回
    myqueue.front();                    //返回该队列的头元素，但队列元素并不受影响
    myqueue.back();                     //返回该队列的末尾元素，但队列元素并不受影响
    myqueue.size();                     //队列大小
   ```


3. std::vector<>
   1. 定义一个容器，<>为数组的类型
   2. #include <vetcor>
   3. 容器不能认为是一个数组，因此不能用索引来对对象进行访问
   4. 使用接口
   ```c++
    std::vector<int> vec(100,1);                    //有100个元素并且值为1
    std::vector<std::string> vec{"a","b","c"};      //单纯地初始化
    std::vector<int>::iterator iter = nVec.begin();   //指向vector其中一个元素

    int i = 5;
    vec.push_back(i);                               // 把i压倒vec的尾端，这也是vector的赋值方法
    vec[5] = i;                                     // 对于空vector，不能这样赋值

    // 判断vector大小
    vector.size();
    // 判断vector是否为空
    vector.empty();

    // 插入元素
    vector.insert(pos, num);                        // 在pos中插入值为num的值
    vector.insert(pos, n, num);                     // 在pos位置中插入n个值为num的值
    vector.insert(pos, beg, end);                   // 在pos位置中插入范围为[begin,end)的值

    //删除元素
    vector.clear();                                 // 删除所有元素
    vector.erase(p);                               // 删除p指向的元素
    // 删除元素会导致迭代器失效，应该使用以下删除方法
    
    for(; iter != vector.end(); )
    {
       if(*iter == 0 )
       {
          iter = vectro.erase(iter);
       }
       else
       {
          iter++;
       }
    }

    /* vector类似于堆栈等，用push/pop等操作，这里用的是push_back */
    //在队尾添加一个对象：push_back
    //插入对象：insert
    //删除对象：erase
    
   ```
   > [更详细用法请见](https://blog.csdn.net/tpriwwq/article/details/80609371)
   
4. std::map<>
   1. 有序键值对容器:可以理解为一个列表，其中左边为索引，右边为表格内容,<type1, type2>有两种类型提供选择
   2. #include <map>
   3. 实例
   ```c++
   // 定义
   std::map<std::string, int> strmap={
                                 {"abc", 10},
                                 {"aaa",100},
                                 ...
                                 };

   // 访问迭代器, 也可以利用该方式赋值（插入）
   strmap[string] = xxx;

   // 迭代器
   strmap.begin(); strmap.cbegin();       // 返回容器第一个迭代器
   strmap.end(); strmap.cend();           // 返回容器最后一个迭代器

   // 容量
   strmap.empty();                        // 判断容器是否为空，是返回true
   strmap.size();                         // 返回的容纳的元素数 
   strmap.max_size();	                  //返回可容纳的最大元素数

   // 修改器
   strmap.clear();		                  //清空容器
   strmap.insert();	                     //插入元素
   strmap.erase();		                  //擦除元素
   strmap.swap();		                     //交换内容

   // 查找
   strmap.find(key);                		//寻找带有特定键的元素,函数返回一个迭代器指向键值为key的元素，如果没找到就返回指向map尾部的迭代器

   ```
   4. [详细介绍看这里](https://blog.csdn.net/mayue_web/article/details/86514521)


5. Json class
   1. 三种基本类型： Json::Value, Json::Reader, Json::Writer
   2. 作用：解析Json格式的文件
   3. Json::Value 是jsoncpp 中最基本、最重要的类，用于表示各种类型的对象
    ```c++
        root["key_string"] = Json::Value("value_string");         // 新建一个 Key（名为：key_string），赋予字符串值："value_string"
        root["key_object"] = Json_temp;                           // 新建一个 Key（名为：key_object），赋予 json::Value 对象值
    ```
    4.  Json::Writer 类是一个纯虚类,不能直接使用，使用 Json::Writer 的子类：Json::FastWriter、Json::StyledWriter、Json::StyledStreamWriter。
    ```c++
          Json::FastWriter fast_writer;
        　std::cout << fast_writer.write(root) << std::endl;        //快速输入root
          Json::StyledWriter styled_writer;                         
          std::cout << styled_writer.write(root) << std::endl;      //格式化输入root
    ```

6. std::shared_ptr
   1. 智能指针，和C指针一样功能，本身还有计数功能，当指向同一对象的智能指针，`shared_ptr.use_count()`会加一；
   2. share_ptr的三种初始化方法，头文件<memory>
   3. 实例：
   ```c++
    #include <memory>
    int a = new int(100);

   // 实例初始化
    std::shared_ptr ptr(a);                                    //指向一个对上申请的空间指针，不能写成std::shared_ptr ptr = a;
    std::shared_ptr ptr1 = std::make_shared<int>(15);           //通过make_shared函数获得
    std::shared_ptr<int> ptr2(ptr1);                            //拷贝初始化

    // 注销智能指针, use_cout()会减一
    ptr2.reset();
   ```
   4. shared_ptr每指向同一对象时，会析构一次对象，会导致多次释放同一内存，利用`enable_shared_from_this`和`shared_from_this`可以避免该问题
   ```c++
    class student : public enable_shared_from_this<student>
    {
        ~student()
        {
            std::cout << "~student()被调用" << std::endl;
        }
        /* 避免析构两次 */
        std::shared_ptr<student> getstudent()           
        {
            return shared_from_this();
        }
        ...
    }

   ```

7. std::ifstream
   1. 文件输入流，类似于标准C下的文件流
   2. 头文件<fstream>
   3. 常用接口
   ```c++
    std::ifstream file("path");                     //打开文件，通过判断file是否为NULL判断文件是否成功打开
   ```
   4. 对应的还有ofstream,文件输出流
   

8. std::stringstream
   1. 对流进行输入输出操作，对字符串与其他数据类型转换十分方便
   2. 头文件<sstream>
   3. 常用接口
   ```c++
    std::stringstream stream;
    stram << i ;                    //向流中传值
    stream >> a;                    //把流中的值传到a中

   ```
   4. 类似的流：istringstream,ostringstream

9.  std::move/std::forward【需要多多重温】
    1.  std::move:对参数执行到右值的无条件转换，即输出结果是<T&&>，右值引用。
    2.  std::forward:完美转发,实现了参数在传递过程中保持其值属性的功能，即若是左值，则传递之后仍然是左值，若是右值，则传递之后仍然是右值
         是std:move的扩展类型。  
   3. #include <utility>
   4. 例子：
   ```c++
   #include <iostream>
   using namespace std;

   void f(int x) { cout << "重载1" << endl; }
   void f(int&& x) { cout << "重载2" << endl; }

   int main() {
   int&& ri = 5;      // 5是右值，ri是右值引用，ri是左值
   //f(5);              // 编译失败，5是右值，即可以被int绑定也可以被int&&绑定
   f(ri);             // ri是左值，只可以被int绑定，无法被int&&绑定，选择重载1
   //f(std::move(ri));  // 编译失败，std::move(ri)是右值，既可以被int绑定也可以被int&&绑定
   return 0;
   }
   ```
   [详细说明见此处](https://www.jianshu.com/p/b90d1091a4ff)

10.  std::bind
     1.   std::bind函数看作一个通用的函数适配器，它接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表。
     2.   #include <functional>
     3.   例子：
   ```c++
   // 绑定函数
   int f1(int x, int y) {return x*y;}
   auto f1_bind = std::bind(f1, std::placeholders::_1, 2);     // 绑定普通函数，f1即为函数入口地址，第一个参数用占位符占着，第二个参数默认为2
   cout << f1_bind(1) << endl;               // cout == 2

   // 绑定类成员函数
   class task
   {
      public:
      int f2(int x, int y) {return x*y;}
   };
    //绑定类成员函数，且无法自动获取它的成员函数，因此需要用取地址符号，第二个参数为类地址，之后的参数同绑定函数
   auto f2_bind = std::bind(&task::f2, &task, std::placeholders::_1, 2);  

   ```

11. std::placeholders
    1.  可以理解为一种占位符，
    2.  #include <functional>
    3.  使用：std::placeholders::_1

12. std::multiset
    1.  可以看成一个序列，插入一个数，删除一个数都能够在O(logn)的时间内完成，而且他能时刻保证序列中的数是有序的，而且序列中可以存在重复的数。
   ```c++
      multiset<int> multi;

      for( int i = 0; i < 10; i++ )
      {   
         cin >> data;
         multi.insert(data);                                 // 往容器里插入data,并且会自动排序
      }
   ```

13. std::stack
    1. 堆栈的应用
    ```c++
    // 当需要调用栈顶元素时，不能使用pop()，该函数的作用是弹出栈顶元素，应该使用.top()
    stack<string> s;
    s.top();                    //栈的栈顶元素
    
    ```


## 2. 关键字
1. auto
   1. 自动判断参数的数据类型
   
2. string
   1. 关键字为string的变量，其指向const char*型的指针变量
   2. c_str函数返回当前字符串的首字符地址, 假如返回值是const char*的，不能直接赋值给char*，所以就需要我们进行相应的操作转化
   3. 实例：
   ```c++
   string s = "123";
   s.size();                           // size()等同于C标准库的strlen()，不包括字符串结束符' '
   printf("s:%s\n",s.c_str());         // c_str是指把const char*类型的数据转换为char*类型数据
   ```


## 3. 相关库函数说明
1. stod/stoi
   1. 作用：stod会截取string最前面的浮点数，直到遇到不满足浮点数为止;而stoi则是转换为int
   2. #include <string>
   3. 实例：
   ```c++
      std::string str="123.456.789";         //这种形式的string实际上并不是一个正常的数，但是可以获取；但是包括了字母的就不行
      double a = stod(str);
      int b = stoi(str);
   ```

2. assert 
   1. 现计算表达式expression ，如果其值为假（即为0），那么它先向 stderr 打印一条出错信息,然后通过调用 abort 来终止程序运行
   2. 缺点：频繁调用会极大影响程序性能，增加额外开销
   3. 例子：
   ```c++
   assert(expression);
   ```


## 4. 备注
1. 使用gcc5.4编译c++新特性时，需要添加条件：`-std=c++11`；老版本gcc使用`-std=c++`即可。
2. 某A类继承了B类，B类是基类 
3. C++左值右值：
   1. 左值(lvalue)：占据指定的内存空间
   2. 右值(rvalue)：占据临时的内存空间




