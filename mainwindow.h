#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidget>
#include <QTableWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLineEdit>
#include <QMainWindow>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include"EditStuMessBox.h"
#include"student.h"
#include"ShowPicture.h"
class MainWindow : public QWidget
{
    Q_OBJECT

public:

    MainWindow();/*zhu chuang kou*/ /**/
    void AddStu();/*show  xue  sheng  */
    void showpp();
    ~MainWindow();
public slots:/*cao*/

    void GenXinTable();/*gen xin biao ge */
    void Genxinliebiao(int row);/*gen xin lie biao xue sheng*/
    void DelStu();/*del*/
    void findStu();/*find student*/
    void changeStu(int row);/*change student*/
   void saveStu();/*save  student*/

private:

    QGroupBox * createStu();/*mian window messang*/
    QGroupBox * createMenu();/*left meun*/
private:
    QTableWidget * TableWidget;/* table*/
    QListWidget *ListWidget;/* list*/
    QPushButton * AddStuBtn;/**/
    QPushButton * DelStuBtn;/**/
    QLineEdit * FindStuEdit;/**/
    QPushButton * SaveBtn;/**/
    QPushButton * ExitBtn;/**/
    QPushButton * showp;/*tupian*/
    EditStuMessBox * messBox;/* add student messge*/
   // ShowPicture * show;





};
#endif // MAINWINDOW_H
