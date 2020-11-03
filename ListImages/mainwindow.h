#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <doublelinkedlist.h>
#include <QMessageBox>
#include <fstream>
#include<vector>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_btn_add_clicked();

    void on_btn_search_clicked();

    void on_btn_delete_clicked();

    void on_btn_edit_clicked();

    void on_btn_n_clicked();

    void on_btn_p_clicked();

    void update_image();

    void update_data();

    void on_btn_confirm_clicked();

    bool verify_insertion();

    void saveBinaryFile(QString);

    void loadBinaryFile(QString);
private:
    Ui::MainWindow *ui;
    DoubleLinkedList*list;
    DoubleLinkedList::iterator current_image;
    QMessageBox msgBox;
   // vector<Imagen_> ListImages;
    Imagen_ ListImages[20];
};

#endif // MAINWINDOW_H
