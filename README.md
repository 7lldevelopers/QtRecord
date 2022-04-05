## 学习QT  源码学习

### ![image-20220405162454069](README/image-20220405162454069.png)



1. 利用 QHBoxLayout 布局为两个区域,左边区域用 Left 实现，右边由 Right 实
2. 水平布局
3.  QGroupBox *Left = createStu();/*分组框  left*/
       QGroupBox *Right = createMenu();/*分组框 right*/
4. 添加到水平布局管理器中
5. QVBoxLayout 局部工具中放置 QFormLayout 和 QHBoxLayout
   * QFormLayout 中放置多个单行输入框
   * QHBoxLayout 中放置两个按钮
6. 
