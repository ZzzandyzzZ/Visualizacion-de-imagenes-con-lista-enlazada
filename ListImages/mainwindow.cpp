#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    list = new DoubleLinkedList(20);
    current_image=nullptr;
    ui->btn_confirm->setVisible(false);
    update_image();
    loadBinaryFile("database.data");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_add_clicked(){
    if(list->getMaxSize()==list->getSize())
    {
        msgBox.setText("Ya no hay espacio para mas imagenes");
        msgBox.exec();
        return;
    }
    QString ubication=QFileDialog::getOpenFileName(this,tr("Escoger"),"",tr("Images(*.png *.jpg *.jpeg *.bmp *..gif)"));
    if(QString::compare(ubication,QString())!=0){
        QPixmap image;
        bool valid =image.load(ubication);
        if(valid){
            ui->btn_add->setVisible(false);
            ui->btn_confirm->setVisible(true);
            update_image();
            ui->lbl_image->setPixmap(image);
            ui->txtName->setText("");
            ui->txtTags->setText("");
            msgBox.setText("Llene los campos necesarios y confirme");
            msgBox.exec();
        }
        else{
            msgBox.setText("No se puedo cargar la imagen");
            msgBox.exec();
        }

    }
}

void MainWindow::on_btn_search_clicked()
{
    if(verify_insertion())return;
}

void MainWindow::on_btn_delete_clicked()
{
    if(verify_insertion())return;
    DoubleLinkedList::iterator temp=current_image;
    int option;
    if(current_image==nullptr)
        option=0;
    else
    {
        ++current_image;
        option=list->deleteN(temp);
    }
    switch (option){
        case 0:
            current_image=nullptr;
            msgBox.setText("Lista vacia");
            msgBox.exec();
        break;
        case 1:
            msgBox.setText("Primera imagen eliminada ");
            msgBox.exec();
        break;
        case 2:
            msgBox.setText("Ultima imagen correctamente");
            msgBox.exec();
        break;
        case 3:
            msgBox.setText("Imagen eliminada correctamente");
            msgBox.exec();
        break;
    }
    update_data();
    update_image();

}

void MainWindow::on_btn_edit_clicked()
{
    if(verify_insertion())return;
    if(current_image==nullptr)
    {
        msgBox.setText("Lista vacia");
        msgBox.exec();
        return;
    }
    QString title = ui->txtName->text();
    QString txt_tags=ui->txtTags->text();
    Imagen_ image((*current_image).image(),title,txt_tags);
    current_image.getPNode()->setDato(image);
    msgBox.setText("Actualizacion correcta");
    msgBox.exec();
}

void MainWindow::on_btn_n_clicked()
{
    if(verify_insertion())return;
    if(list->fsize()==0||list->fsize()==1)
    {
        msgBox.setText("No hay imagenes");
        msgBox.exec();
        return;
    }
    ++current_image;
    update_image();
    update_data();
}

void MainWindow::on_btn_p_clicked()
{
    if(verify_insertion())return;
    if(list->fsize()==0||list->fsize()==1)
    {
        msgBox.setText("No hay imagenes");
        msgBox.exec();
        return;
    }
    --current_image;
    update_image();
    update_data();
}

void MainWindow::update_image()
{
    if(current_image==nullptr)
    {
        QPixmap pixmap = QPixmap (":/images/default.png");
        ui->lbl_image->setPixmap(pixmap);
        return;
    }
    ui->lbl_image->setPixmap(QPixmap::fromImage((*current_image).image()));

}

void MainWindow::update_data()
{
    if(current_image==nullptr)
    {
        ui->txtName->setText("");
        ui->txtTags->setText("");
        return;
    }
    ui->txtName->setText((*current_image).getTitle());
    ui->txtTags->setText((*current_image).getTags());
}

void MainWindow::on_btn_confirm_clicked(){
    QPixmap image= *(ui->lbl_image->pixmap());
    QString title = ui->txtName->text();
    QString txt_tags=ui->txtTags->text();
    Imagen_ image_(image.toImage(),title,txt_tags);
    ListImages[list->getSize()]=image_;
    //ListImages.push_back(image_);
    list->push_back(image_);
    current_image=list->end();
    ui->btn_add->setVisible(true);
    ui->btn_confirm->setVisible(false);
    msgBox.setText("Imagen insertada correctamente");
    msgBox.exec();
    saveBinaryFile("database.data");
}

bool MainWindow::verify_insertion()
{
    if(ui->btn_confirm->isVisible()){
        ui->btn_confirm->setVisible(false);
        ui->btn_add->setVisible(true);
        msgBox.setText("Se cancelo la insercion");
        msgBox.exec();
        update_data();
        update_image();
        return true;
    }
    return false;
}
/*
void MainWindow::saveBinaryFile(QString nameFile)
{
   // FILE*pfile;
   // pfile=fopen(nameFile.toStdString().c_str(),"wb+");
    ofstream out;
    out.open(nameFile.toStdString().c_str());
    qDebug()<<"NUEVO";
    for(int i=0;i<list->getSize();i++)
    {
        qDebug()<<sizeof(ListImages[i]);
        fwrite(&ListImages[i],sizeof(Imagen_),1,pfile);
    }
    fflush(pfile);
    fclose(pfile);
}*/
void MainWindow::saveBinaryFile(QString nameFile)
{
    qDebug()<<"A";
    qDebug()<<ListImages[0].getTitle();
    qDebug()<<"B";
    ui->lbl_image->setPixmap(QPixmap::fromImage(ListImages[0].image()));
    qDebug()<<"C";
    ofstream out(nameFile.toStdString().c_str(),ios::binary);
    out.write((char*)&ListImages, sizeof(ListImages));
    out.close();
}
/*
void MainWindow::loadBinaryFile(QString nameFile)
{
    FILE*pfile;
    pfile=fopen(nameFile.toStdString().c_str(),"rb");
    if(pfile==nullptr)
    {
        return;
    }

    fread(&ListImages[0],sizeof(Imagen_),1,pfile);

    fclose(pfile);
    qDebug()<<"A";
    qDebug()<<ListImages[0].getTitle();
    qDebug()<<"B";
    ui->lbl_image->setPixmap(QPixmap::fromImage(ListImages[0].image()));
}*/

void MainWindow::loadBinaryFile(QString nameFile)
{
    ifstream out(nameFile.toStdString().c_str(),ios::binary);
    out.read((char*)&ListImages, sizeof(ListImages));
    out.close();
    qDebug()<<"A";
    size_t i=0;
    qDebug()<<ListImages[i].getTitle();
    qDebug()<<"B";
    ui->lbl_image->setPixmap(QPixmap::fromImage(ListImages[i].image()));
    qDebug()<<"C";
}
