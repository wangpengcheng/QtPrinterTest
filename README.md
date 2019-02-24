# QtPrinterTest
Qt静默打印
利用Qt实现压缩文件中图片的静默打印
## 主要设计思路
 - 1. 设计文件面板，帮助选择，文件夹/压缩文件/单张图片
 - 2. 不同文件使用不同方式，读取文件列表
     + a. 查找当前文件夹下面，所有文件夹
     + b. 遇到非文件夹，添加到打印文件列表文件 
     + c. 压缩文件：解压缩，并遍历解压后的文件夹
     + d. 输出打印所有文件列表，将列表输入数组
     + e. 点击打印按钮设置，打印格式。
     + d. 选择打印机，进行打印。 
 - 3. 打印结束，返回操作界面。
