#include "mainwindow.h"

MainWindow::MainWindow()
{
    /*利用 QHBoxLayout 布局为两个区域,左边区域用 Left 实现，右边由 Right 实现*/
    setWindowTitle("学生信息管理系统");
    this->resize(1000,600);/*set size*/  /**/
    QHBoxLayout *HBoxLayout = new QHBoxLayout(this);/*水平布局,dang qian window*/
    QGroupBox *Left = createStu();/*分组框  left*/
    QGroupBox *Right = createMenu();/*分组框 right*/

    HBoxLayout->addWidget(Left,4);/*添加到水平布局管理器中,*/
    HBoxLayout->addWidget(Right,2);/**/

}

QGroupBox * MainWindow::createStu(){/* return **/
    QGroupBox * box = new QGroupBox("学生信息");/*分组框*/
    TableWidget = new QTableWidget;/**/
    TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);/*设置表格数据区内的所有单元格都不允许编辑*/
    TableWidget->setColumnCount(7);/*设置表格 7 ge */
    TableWidget->setHorizontalHeaderLabels(QStringList() <<"学号"<< "姓名"<<"年龄"<<"性别"<<"语文成绩"<<"数学成绩"<<"英文成绩");/**/
    //flushTable();
    QHBoxLayout * AutoHBoxLayout = new QHBoxLayout;/**/
    AutoHBoxLayout->addWidget(TableWidget);/*添加到水平布局管理器中*/
    box->setLayout(AutoHBoxLayout);/*Auto布局*/

    //当用户点击某个单元格时，更新列表中显示的学生信息
    connect(TableWidget,&QTableWidget::cellClicked,this,&MainWindow::GenXinTable);
    //当用户更改某个单元格内的内容时，调用 changeStu() 方法处理
    connect(TableWidget,&QTableWidget::cellChanged,this,&MainWindow::changeStu);
    //将用户更改某个单元格内的内容时，同时还要更新表格中显示的学生信息
    connect(TableWidget,&QTableWidget::cellChanged,this,&MainWindow::Genxinliebiao);
    return box;
}
QGroupBox * MainWindow::createMenu(){
    QGroupBox * box = new QGroupBox("功能面板");/*分组框*/
    QVBoxLayout *VBoxLayout = new QVBoxLayout;/*QVBoxLayout垂直布局*/
    ListWidget = new QListWidget;/* list */
    QGridLayout * Buts = new QGridLayout;/**/
    AddStuBtn = new QPushButton("添加");
    DelStuBtn = new QPushButton("删除");
    SaveBtn = new QPushButton("保存");
    ExitBtn = new QPushButton("退出");
    showp =new QPushButton("picture");
    FindStuEdit = new QLineEdit;/*一个单行文本编辑控件*/
    FindStuEdit->setPlaceholderText("输入学生姓名查找...");/**/
    FindStuEdit->setClearButtonEnabled(true);/**/
    FindStuEdit->setStyleSheet("QLineEdit{padding:3,3,3,3;}");/**/
    Buts->addWidget(AddStuBtn,0,0);/*将 widget 控件添加到网格中的 (row,column) 位置处，并且可以自定义该控件的对齐方式。*/
    Buts->addWidget(DelStuBtn,0,1);
    Buts->addWidget(FindStuEdit,1,0,1,0);
    Buts->addWidget(SaveBtn,2,0);
    Buts->addWidget(ExitBtn,2,1);
    Buts->addWidget(showp,3,0);
    VBoxLayout->addWidget(ListWidget,4);/*list  rot  4*/
    VBoxLayout->addLayout(Buts,2);/*  button rot 2*/

    box->setLayout(VBoxLayout);
    //点击添加按钮，执行 addStuBox() 方法
    connect(AddStuBtn,&QPushButton::clicked,this,&MainWindow::AddStu);
    //点击删除按钮，执行 delStuFun() 方法
    connect(DelStuBtn,&QPushButton::clicked,this,&MainWindow::DelStu);/**/
    //当向输入框内输入信息后，执行 findStuMess() 方法
    connect(FindStuEdit,&QLineEdit::returnPressed,this,&MainWindow::findStu);
    //点击退出按钮，关闭主窗口
    connect(ExitBtn,&QPushButton::clicked,this,&MainWindow::close);
    //点击保存按钮，执行 saveStuMess() 方法
    connect(SaveBtn,&QPushButton::clicked,this,&MainWindow::saveStu);
    connect(showp,&QPushButton::clicked,this,&MainWindow::showpp);
    return box;
}
void MainWindow::AddStu(){/*弹出添加学生信息的子窗口*/
    messBox = new EditStuMessBox;/*new window*/
    QObject::connect(messBox,&EditStuMessBox::closeBox,this,&MainWindow::GenXinTable); //学生信息窗口关闭时 更新表格
    QObject::connect(messBox,&EditStuMessBox::closeBox,ListWidget,&QListWidget::clear); //学生信息窗口关闭时 清空列表中显示的学生信息
    messBox->exec();
}

void MainWindow::showpp(){
   // show = new ShowPicture();

}



void MainWindow::GenXinTable(){/*刷新表格中的内容*/
    disconnect(TableWidget,&QTableWidget::cellChanged,0,0);//更新表格内容前，要断开与 cellChanged 信号关联的所有槽，否则会导致程序闪退student.txt
       QFile file("student.txt");
       file.open(QIODevice::ReadOnly);
       QDataStream dataStr(&file);/*指向文件的头部*/
       QString id,name,age,sex,chinese_score,math_score,english_score; /*保存的数据*/
       /*Sets the number of rows in this table's model to rows. If this is less than rowCount(), the data in the unwanted rows is discarded.*/
       TableWidget->setRowCount(0);
       while(!dataStr.atEnd()){
           TableWidget->setRowCount(TableWidget->rowCount()+1);
           dataStr>>id>>name>>age>>sex>>chinese_score>>math_score>>english_score; /*file  data  save id,name,age,sex,chinese_score,math_score,english_score*/
           TableWidget->setItem(TableWidget->rowCount()-1,0,new QTableWidgetItem(id));
           TableWidget->setItem(TableWidget->rowCount()-1,1,new QTableWidgetItem(name));
           TableWidget->setItem(TableWidget->rowCount()-1,2,new QTableWidgetItem(age));
           TableWidget->setItem(TableWidget->rowCount()-1,3,new QTableWidgetItem(sex));
           TableWidget->setItem(TableWidget->rowCount()-1,4,new QTableWidgetItem(chinese_score));
           TableWidget->setItem(TableWidget->rowCount()-1,5,new QTableWidgetItem(math_score));
           TableWidget->setItem(TableWidget->rowCount()-1,6,new QTableWidgetItem(english_score));
       }
       file.close();
       //完成更新表格的任务后，重新关联与 cellChanged 相关的槽。
       connect(TableWidget,&QTableWidget::cellChanged,this,&MainWindow::changeStu);
       connect(TableWidget,&QTableWidget::cellChanged,this,&MainWindow::GenXinTable);
};
void MainWindow::Genxinliebiao(int row){/*更新列表中显示的学生信息*/
    if(ListWidget->count() > 0){/**/
            ListWidget->item(0)->setText("学   号：" + TableWidget->item(row,0)->text());
            ListWidget->item(1)->setText("姓   名：" + TableWidget->item(row,1)->text());
            ListWidget->item(2)->setText("年   龄：" + TableWidget->item(row,2)->text());
            ListWidget->item(3)->setText("性   别：" + TableWidget->item(row,3)->text());
            ListWidget->item(4)->setText("语文成绩：" + TableWidget->item(row,4)->text());
            ListWidget->item(5)->setText("数学成绩：" + TableWidget->item(row,5)->text());
            ListWidget->item(6)->setText("英语成绩：" + TableWidget->item(row,6)->text());
        }else{
            ListWidget->addItem("学   号：" + TableWidget->item(row,0)->text());
            ListWidget->addItem("姓   名：" + TableWidget->item(row,1)->text());
            ListWidget->addItem("年   龄：" + TableWidget->item(row,2)->text());
            ListWidget->addItem("性   别：" + TableWidget->item(row,3)->text());
            ListWidget->addItem("语文成绩：" + TableWidget->item(row,4)->text());
            ListWidget->addItem("数学成绩：" + TableWidget->item(row,5)->text());
            ListWidget->addItem("英语成绩：" + TableWidget->item(row,6)->text());
        }

};
void MainWindow::DelStu()
{
    QList<QTableWidgetItem*>items = TableWidget->selectedItems();
    //判断用户是否在表格中选中了某个学生信息，只有选中之后，才能执行删除操作
    if(items.count() > 0){
        QMessageBox::StandardButton result=QMessageBox::question(this, "删除","确定要删除学号为【"+items.at(0)->text()+"】的同学吗？");
        if(result == QMessageBox::Yes){
            QString ID,name,age,sex,chinese_score,math_score,english_score;
            QFile file("student.txt");
            file.open(QIODevice::ReadOnly);
            QDataStream readDataStr(&file);

            QFile tempFile("student1.txt");
            tempFile.open(QIODevice::WriteOnly);
            QDataStream writeDataStr(&tempFile);

            while (!readDataStr.atEnd()) {
                readDataStr >> ID >> name >> age >> sex >> chinese_score >> math_score >> english_score;
                if(ID != items.at(0)->text()){
                    writeDataStr << ID << name << age << sex << chinese_score << math_score << english_score;
                }
            }
            tempFile.close();
            file.close();
            //删除原文件，将临时文件重命名为和原文件相同的名字
            file.remove();
            tempFile.rename("student.txt");
            GenXinTable();
            ListWidget->clear();
        }
    }else{
        QMessageBox::warning(this,"提示","请选择要删除的学生");
    }
}
/*逐一将学生信息拷贝到另一个临时文件中，当读取到要更改的学生信息时，将更改后的学生信息写入临时文件。最终，临时文件中存储的是更改后所有学生的信息。*/
void MainWindow::changeStu(int row)
{
    QString ID,name,age,sex,chinese_score,math_score,english_score;
    QString stuName = TableWidget->item(row,1)->text();
    QFile file("student.txt");
    file.open(QIODevice::ReadOnly);
    QDataStream readDataStr(&file);

    QFile tempFile("student1.txt");
    tempFile.open(QIODevice::WriteOnly);
    QDataStream writeDataStr(&tempFile);

    while (!readDataStr.atEnd()) {
        readDataStr >> ID >> name >> age >> sex >> chinese_score >> math_score >> english_score;
        if(name != stuName){
            writeDataStr << ID << name << age << sex << chinese_score << math_score << english_score;
        }else{
            for(int i=0;i<TableWidget->columnCount();i++){//重写写入到表
                writeDataStr<<TableWidget->item(row,i)->text();//di  row  hang   i  lie
            }
        }
    }
    tempFile.close();
    file.close();
    file.remove();
    tempFile.rename("student.txt");
}
void MainWindow::findStu()
{
    qint32 count = TableWidget->rowCount();
    bool findSuccess = false;
    if(count>0){
        for(qint32 i=0;i<count;i++){
            QString name = TableWidget->item(i,1)->text();// di  i hang  1 lei
            if(name == FindStuEdit->text()){
                findSuccess = true;
                TableWidget->selectRow(i);
                Genxinliebiao(i);
                break;
            }
        }
        if(findSuccess == false){
            QMessageBox::information(this,"查找失败","当前表格中没有【"+FindStuEdit->text()+"】同学");
        }
    }

}
void MainWindow::saveStu()
{
    QFile file("student.txt");
    file.open(QIODevice::WriteOnly);
    QDataStream dataStr(&file);

    for(int i=0;i<TableWidget->rowCount();i++){
        for(int j=0;j<TableWidget->columnCount();j++){
            dataStr << TableWidget->item(i,j)->text();
        }
    }
    file.close();
    QMessageBox::information(this,"保存","保存成功！");
}

MainWindow::~MainWindow()
{
}

