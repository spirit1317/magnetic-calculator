#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include"mc_classes.hpp"
#include <QDebug>
#include<fstream>
#include<cmath>
#include <stdlib.h>//system
#include<QMessageBox>
#include<QFileDialog>
#include <stdio.h>
#include <iostream>
#include <QDir> //toNativeSeparator()

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //LOGO
    item_logo.setPixmap(QPixmap(".\\logo.jpg"));
    scene_logo.addItem(&item_logo);
    ui->graphicsView_2->setScene(&scene_logo);
    ui->graphicsView_2->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()//W PUNKCIE
{
    double x,y,z,d1,d2,d3,Jx,Jy,Jz,Hx,Hy,Hz;

    //POBIERANIE DANYCH Z MENU
    d1=ui->doubleSpinBox_6->value()*pow(10,ui->comboBox_37->currentIndex());
    d2=ui->doubleSpinBox_31->value()*pow(10,ui->comboBox_38->currentIndex());
    d3=ui->doubleSpinBox_2->value()*pow(10,ui->comboBox->currentIndex());
    Jx=ui->doubleSpinBox_3->value()*pow(1000,ui->comboBox_2->currentIndex());
    Jy=ui->doubleSpinBox_4->value()*pow(1000,ui->comboBox_3->currentIndex());
    Jz=ui->doubleSpinBox_5->value()*pow(1000,ui->comboBox_4->currentIndex());
    x=ui->doubleSpinBox_7->value()*pow(10,ui->comboBox_5->currentIndex());
    y=ui->doubleSpinBox_8->value()*pow(10,ui->comboBox_6->currentIndex());
    z=ui->doubleSpinBox_9->value()*pow(10,ui->comboBox_7->currentIndex());

    //TWORZENIE MAGNESU I OBLICZENIA
    magnet m(d1,d2,d3,Jx,Jy,Jz);
    Hx=m.Hx(x,y,z);
    Hy=m.Hy(x,y,z);
    Hz=m.Hz(x,y,z);
    qDebug()<<"Hx";
    if(Hz==Hz && Hy==Hy && Hx==Hx){
        //WYPISANIE WYNIKOW DO GUI
        ui->lineEdit->setText(QString::number(Hx));
        ui->lineEdit_2->setText(QString::number(Hy));
        ui->lineEdit_3->setText(QString::number(Hz));
    }else{
        QMessageBox msgBox;
        msgBox.setText("UWAGA: Chciano przeprowadzić obliczenia w punkcie osobliwym!");
        msgBox.exec();
    }

}

void MainWindow::on_pushButton_2_clicked()//KILKA PUNKTOW
{
    double x,y,z,d1,d2,d3,Jx,Jy,Jz,Hx,Hy,Hz;

    //POBIERANIE DANYCH Z MENU
    d1=ui->doubleSpinBox_6->value()*pow(10,ui->comboBox->currentIndex());
    d2=ui->doubleSpinBox_31->value()*pow(10,ui->comboBox->currentIndex());
    d3=ui->doubleSpinBox_2->value()*pow(10,ui->comboBox->currentIndex());
    Jx=ui->doubleSpinBox_3->value()*pow(1000,ui->comboBox_2->currentIndex());
    Jy=ui->doubleSpinBox_4->value()*pow(1000,ui->comboBox_3->currentIndex());
    Jz=ui->doubleSpinBox_5->value()*pow(1000,ui->comboBox_4->currentIndex());
     //qDebug()<<"Hx";
    double arrw=d1/10;
    double H_lng=1;
    std::fstream file_r;
    QMessageBox msgBox;
     msgBox.setText("UWAGA: Blad otwierania pliku!");
     msgBox.exec();


    //TWORZENIE MAGNESU I OBLICZENIA
    magnet m(d1,d2,d3,Jx,Jy,Jz);

    //PLIK WEJSCIOWY
    QString nazwa_qstr = ui->lineEdit_5->displayText();
    std::string nazwa = nazwa_qstr.toStdString();

    file_r.open(nazwa.c_str(),std::fstream::in);

    //PLIK WYJSCIOWY
    nazwa_qstr = ui->lineEdit_6->displayText();
    nazwa = nazwa_qstr.toStdString();
    std::fstream file_w;
    file_w.open(nazwa.c_str(),std::fstream::out);
    file_w.precision(15);
    //OBLICZANIE I WPISYWANIE
    if(file_r.is_open()&&file_w.is_open())
        {
            file_w<<"x[m]\ty[m]\tz[m]\tHx[a/m]\t\t\tHy[a/m]\t\t\tHz[a/m]\t\t\tarrow lenght delta x\tarrow lenght delta y\tarrow lenght delta z"<<std::endl;
            while(!file_r.eof())
            {
            file_r>>x;
            file_r>>y;
            file_r>>z;
            Hx=m.Hx(x,y,z);
            Hy=m.Hy(x,y,z);
            Hz=m.Hz(x,y,z);

            if(Hx == Hx && Hy == Hy && Hz == Hz)
            {
                H_lng=sqrt(Hx*Hx+Hy*Hy+Hz*Hz);
                file_w<<x<<"\t"<<y<<"\t"<<z<<"\t"<<Hx<<"\t"<<Hy<<"\t"<<Hz<<"\t"<<Hx*(arrw/H_lng)<<"\t"<<Hy*(arrw/H_lng)<<"\t"<<Hz*(arrw/H_lng)<<std::endl;
            }
            }
            file_r.close();
            file_w.close();
        }else{
         file_r.close();
         file_w.close();
         //QMessageBox msgBox;
         msgBox.setText("UWAGA: Blad otwierania pliku!");
         msgBox.exec();
        }

}

void MainWindow::on_pushButton_4_clicked()//NA PROSTEJ
{
    double x0,y0,z0,x1,y1,z1,d1,d2,d3,Jx,Jy,Jz;
    int N;    //POBIERANIE DANYCH Z MENU
    d1=ui->doubleSpinBox_6->value()*pow(10,ui->comboBox->currentIndex());
    d2=ui->doubleSpinBox_31->value()*pow(10,ui->comboBox->currentIndex());
    d3=ui->doubleSpinBox_2->value()*pow(10,ui->comboBox->currentIndex());
    Jx=ui->doubleSpinBox_3->value()*pow(1000,ui->comboBox_2->currentIndex());
    Jy=ui->doubleSpinBox_4->value()*pow(1000,ui->comboBox_3->currentIndex());
    Jz=ui->doubleSpinBox_5->value()*pow(1000,ui->comboBox_4->currentIndex());

    x0=ui->doubleSpinBox_10->value()*pow(10,ui->comboBox_10->currentIndex());
    y0=ui->doubleSpinBox_11->value()*pow(10,ui->comboBox_11->currentIndex());
    z0=ui->doubleSpinBox_12->value()*pow(10,ui->comboBox_12->currentIndex());
    x1=ui->doubleSpinBox_13->value()*pow(10,ui->comboBox_13->currentIndex());
    y1=ui->doubleSpinBox_14->value()*pow(10,ui->comboBox_14->currentIndex());
    z1=ui->doubleSpinBox_15->value()*pow(10,ui->comboBox_15->currentIndex());
    N=ui->spinBox->value();

    double Hx,Hy,Hz;
    double vx=x1-x0,vy=y1-y0,vz=z1-z0;//skladowe wektora prostej
    double x,y,z;

    //PLIK ZAPISU
    std::string nazwa2 = ".\\wyniki\\prosta.txt";
    system("if not exist \"wyniki\" mkdir wyniki");
    std::fstream file_w;
    file_w.open(nazwa2.c_str(),std::fstream::out);
    file_w.precision(15);
    if(file_w.good()){
            magnet m(d1,d2,d3,Jx,Jy,Jz);
            if(ui->comboBox_34->currentIndex()==1){//sprawdzenie czy obliczamy pole, czy gradient
                //GRADIENT
                file_w<<"x[m]\ty[m]\tz[m]\txgradB[T/m]\t\t\tygradB[T/m]\t\t\tzgradB[T/m]\t\t\tl[m]"<<std::endl;
                for(int n=0;n<=N;n++)
                {
                    x=x0+vx*n/N;
                    y=y0+vy*n/N;
                    z=z0+vz*n/N;
                    Hx=m.xgradB(x,y,z);
                    Hy=m.ygradB(x,y,z);
                    Hz=m.zgradB(x,y,z);
                    file_w<<x<<"\t"<<y<<"\t"<<z<<"\t"<<Hx<<"\t"<<Hy<<"\t"<<Hz<<"\t"<<sqrt(vx*vx+vy*vy+vz*vz)*vx*n/N<<std::endl;
                }
            }else{//POLE H
                file_w<<"x[m]\ty[m]\tz[m]\tHx[a/m]\t\t\tHy[a/m]\t\t\tHz[a/m]\t\t\tl[m]"<<std::endl;
                for(int n=0;n<=N;n++)
                {
                    x=x0+vx*n/N;
                    y=y0+vy*n/N;
                    z=z0+vz*n/N;
                    Hx=m.Hx(x,y,z);
                    Hy=m.Hy(x,y,z);
                    Hz=m.Hz(x,y,z);
                    file_w<<x<<"\t"<<y<<"\t"<<z<<"\t"<<Hx<<"\t"<<Hy<<"\t"<<Hz<<"\t"<<sqrt(vx*vx+vy*vy+vz*vz)*vx*n/N<<std::endl;
                }
            }


            //KOPIOWANIE PLIKU DO SCIEZKI UZYTKOWNIKA
            QString nazwa_qstr = ui->lineEdit_4->displayText();
            QString nazwa_qstr_sys = QDir::toNativeSeparators(nazwa_qstr);
            std::string kopia_path = nazwa_qstr_sys.toStdString();
            std::string polecenie_kopiowania = "copy ";
            polecenie_kopiowania.append(nazwa2);
            polecenie_kopiowania.push_back(' ');
            polecenie_kopiowania.append(kopia_path);
            system(polecenie_kopiowania.c_str());

            //PLOTOWANIE
            if(ui->checkBox->isChecked()){
                system("if not exist \"rysunki\" mkdir rysunki");
                if(ui->comboBox_34->currentIndex()==1){
                    system("gnuplot instru_prosta_grad.txt");
                }else{
                    system("gnuplot instru_prosta.txt");
                }


                //WIZUALIZACJA
                if(ui->comboBox_34->currentIndex()==1){
                    viewed_img_path=".\\rysunki\\prostagradB_x.png";
                    item_wiz.setPixmap(QPixmap(".\\rysunki\\prostagradB_x.png"));
                }else{
                    viewed_img_path=".\\rysunki\\prostaHx.png";
                    item_wiz.setPixmap(QPixmap(".\\rysunki\\prostaHx.png"));
                }

                scene_wiz.addItem(&item_wiz);
                ui->graphicsView->setScene(&scene_wiz);
                ui->graphicsView->fitInView(scene_wiz.itemsBoundingRect(),Qt::KeepAspectRatio);
                ui->graphicsView->show();
                //ODBLOKOWANIE COMBOBOXA 9
                ui->comboBox_9->clear();//clear()
                if(ui->comboBox_34->currentIndex()==1){
                    QString combo_text = "odcinek - wykres gradB skladowa x";
                    ui->comboBox_9->insertItem(0,combo_text);
                    combo_text = "odcinek - wykres gradB skladowa y";
                    ui->comboBox_9->insertItem(1,combo_text);
                    combo_text = "odcinek - wykres gradB skladowa z";
                    ui->comboBox_9->insertItem(2,combo_text);
                    ui->comboBox_9->setEnabled(true);
                }else{
                    QString combo_text = "odcinek - wykres Hx";
                    ui->comboBox_9->insertItem(0,combo_text);
                    combo_text = "odcinek - wykres Hy";
                    ui->comboBox_9->insertItem(1,combo_text);
                    combo_text = "odcinek - wykres Hz";
                    ui->comboBox_9->insertItem(2,combo_text);
                    ui->comboBox_9->setEnabled(true);
                }


                //ODBLOKOWANIE PRZYCISKU ZAPISU WIZUALIZACJI
                ui->pushButton_6->setEnabled(true);
            }else{
            //nie wizualizuj
            }
    }else{
        qDebug()<<"Blad otwierania pliku";
        file_w.close();
    }

    file_w.close();


}

void MainWindow::on_pushButton_3_clicked()//MAPA
{
    double x0,y0,z0,a,b,c,Nx,Ny,Nz,d1,d2,d3,Jx,Jy,Jz;

    //POBIERANIE DANYCH Z MENU
    d1=ui->doubleSpinBox_6->value()*pow(10,ui->comboBox->currentIndex());
    d2=ui->doubleSpinBox_31->value()*pow(10,ui->comboBox->currentIndex());
    d3=ui->doubleSpinBox_2->value()*pow(10,ui->comboBox->currentIndex());
    Jx=ui->doubleSpinBox_3->value()*pow(1000,ui->comboBox_2->currentIndex());
    Jy=ui->doubleSpinBox_4->value()*pow(1000,ui->comboBox_3->currentIndex());
    Jz=ui->doubleSpinBox_5->value()*pow(1000,ui->comboBox_4->currentIndex());

    //PUDLO
    x0=ui->doubleSpinBox_16->value()*pow(10,ui->comboBox_25->currentIndex());//wsporzedne poczatku
    y0=ui->doubleSpinBox_17->value()*pow(10,ui->comboBox_26->currentIndex());
    z0=ui->doubleSpinBox_18->value()*pow(10,ui->comboBox_27->currentIndex());
    a=ui->doubleSpinBox_28->value()*pow(10,ui->comboBox_28->currentIndex());//rozmiar pudla obliczeniowego
    b=ui->doubleSpinBox_29->value()*pow(10,ui->comboBox_29->currentIndex());
    c=ui->doubleSpinBox_30->value()*pow(10,ui->comboBox_30->currentIndex());
    Nx=ui->spinBox_4->value();//wezlow w jednym wymiarze
    Ny=ui->spinBox_5->value();
    Nz=ui->spinBox_6->value();
    //double Hmax=0.2;//ekstrema H
    //double Hscale=20;//skala do plotowania
    double arrw=a/10;//stala dlugosc strzalki
    //bool arrwsequal=1; //czy wszystki strzelki jednakowej dlugosci plotowac

    //TWORZENIE MAGNESU
    magnet m(d1,d2,d3,Jx,Jy,Jz);

    //PLIK WYJSCIOWY
    std::string nazwa = ".\\wyniki\\mapa.txt";
    system("if not exist \"wyniki\" mkdir wyniki");
    std::fstream mapa;
    mapa.open(nazwa.c_str(),std::fstream::out);
    if(mapa.good() == 0){
        mapa.close();
        qDebug()<<"Blad otwierania pliku";
    }
    else{
        mapa.precision(15);
        //OBLICZANIE MAPY
        double x,y,z;
        double Hx_tmp,Hy_tmp,Hz_tmp;
        double H_lng;
        mapa<<"x[m]\ty[m]\tz[m]\tHx\t\t\tHy\t\t\tHz\t\t\tarrow lenght delta x\tarrow lenght delta y\tarrow lenght delta z"<<std::endl;
        for(int nz=0;nz<=Nz;nz++) //N + 1 obiegów
        {
            for(int ny=0;ny<=Ny;ny++)
            {
                for(int nx=0;nx<=Nx;nx++)
                {
                    x=x0+nx*a/Nx;
                    y=y0+ny*b/Ny;
                    z=z0+nz*c/Nz;
                    Hx_tmp=m.Hx(x,y,z);
                    Hy_tmp=m.Hy(x,y,z);
                    Hz_tmp=m.Hz(x,y,z);

                    if(Hx_tmp==Hx_tmp && Hy_tmp==Hy_tmp && Hz_tmp==Hz_tmp)
                    {
                        H_lng=sqrt(Hx_tmp*Hx_tmp+Hy_tmp*Hy_tmp+Hz_tmp*Hz_tmp);
                        mapa<<x<<"\t"<<y<<"\t"<<z<<"\t"<<Hx_tmp<<"\t"<<Hy_tmp<<"\t"<<Hz_tmp<<"\t"<<Hx_tmp*(arrw/H_lng)<<"\t"<<Hy_tmp*(arrw/H_lng)<<"\t"<<Hz_tmp*(arrw/H_lng)<<std::endl;

                    }
                 }
            }
        }

        //KOPIOWANIE PLIKU DO SCIEZKI UZYTKOWNIKA

        QString nazwa_qstr = ui->lineEdit_7->displayText();
        QString nazwa_qstr_sys = QDir::toNativeSeparators(nazwa_qstr);
        std::string kopia_path = nazwa_qstr_sys.toStdString();
        std::string polecenie_kopiowania = "copy ";
        polecenie_kopiowania.append(nazwa);
        polecenie_kopiowania.push_back(' ');
        polecenie_kopiowania.append(kopia_path);
        system(polecenie_kopiowania.c_str());
        //qDebug()<<polecenie_kopiowania.c_str();

        //PLOTOWANIE
        if(ui->checkBox_2->isChecked()){
            system("if not exist \"rysunki\" mkdir rysunki");
            system("gnuplot instru.txt");

            //WIZUALIZACJA
            viewed_img_path=".\\rysunki\\mapa.png";
            item_wiz.setPixmap(QPixmap(".\\rysunki\\mapa.png"));
            scene_wiz.addItem(&item_wiz);
            ui->graphicsView->setScene(&scene_wiz);
            ui->graphicsView->fitInView(scene_wiz.itemsBoundingRect(),Qt::KeepAspectRatio);
            ui->graphicsView->show();

            ui->comboBox_9->clear();//clear()
            QString combo_text = "mapa";
            ui->comboBox_9->insertItem(0,combo_text);
            ui->comboBox_9->setEnabled(true);




            //ODBLOKOWANIE PRZYCISKU ZAPISU WIZUALIZACJI
            ui->pushButton_6->setEnabled(true);
        }else{
        //nie wizualizuj
        }

    }

     mapa.close();
}

void MainWindow::on_pushButton_6_clicked()//ZAPIS OBRAZKA
{
    QString nazwa_obrazka;
    nazwa_obrazka = QFileDialog::getSaveFileName(this,tr("Zapisz dane wynikowe."), ".\\", tr("Pliki .png (*.png *.png *.png)"));
    //qDebug() << nazwa_obrazka;
    std::string outputFilePath = nazwa_obrazka.toStdString();
    std::string initialFilePath = viewed_img_path;

    std::ifstream initialFile(initialFilePath.c_str(), std::ios::in|std::ios::binary);
    std::ofstream outputFile(outputFilePath.c_str(), std::ios::out|std::ios::binary);
    //defines the size of the buffer
    initialFile.seekg(0, std::ios::end);
    long fileSize = initialFile.tellg();
    //Requests the buffer of the predefined size


    if(initialFile.is_open() && outputFile.is_open())
    {
        short * buffer = new short[fileSize/2];
        //Determine the file's size
        //Then starts from the beginning
        initialFile.seekg(0, std::ios::beg);
        //Then read enough of the file to fill the buffer
        initialFile.read((char*)buffer, fileSize);
        //And then write out all that was read
        outputFile.write((char*)buffer, fileSize);
        delete[] buffer;
    }
    else if(!outputFile.is_open())
    {
        QMessageBox msgBox;
        msgBox.setText("Blad przy zapisie pliku.");
        msgBox.exec();
    }
    else if(!initialFile.is_open())
    {
        QMessageBox msgBox;
        msgBox.setText("Blad przy zapisie pliku.");
        msgBox.exec();
    }

    initialFile.close();
    outputFile.close();
}

void MainWindow::on_checkBox_clicked()//CHECKBOX - WIZUALIZACJA NA PROSTEJ
{
    //SPRAWDZENIE CZY ZAINSTALOWANY JEST GNUPLOT
    if(!system("gnuplot -V")){//zwraca 1 jesli komenda jest zla
    //teraz check box jest zaznaczony
    }else{
        ui->checkBox->setChecked(false);
        QMessageBox msgBox;
        msgBox.setText("UWAGA: Aby wizualizowac zainstaluj program GNUPLOT.");
        msgBox.exec();
    }
}

void MainWindow::on_checkBox_2_clicked()//CHECKBOX - WIZUALIZACJIA MAPY
{
    //SPRAWDZENIE CZY ZAINSTALOWANY JEST GNUPLOT
    if(!system("gnuplot -V")){//zwraca 1 jesli komenda jest zla
    //teraz check box jest zaznaczony
    }else{
        ui->checkBox_2->setChecked(false);
        QMessageBox msgBox;
        msgBox.setText("UWAGA: Aby wizualizowac zainstaluj program GNUPLOT.");
        msgBox.exec();
    }
}

void MainWindow::on_toolButton_4_clicked()//SCIEZKA OUT KILKA PUNKTOW
{
    ui->lineEdit_7->setText(QFileDialog::getSaveFileName(this,tr("Zapisz dane wynikowe."), ".\\", tr("Pliki .txt (*.txt *.txt *.txt)")));
}

void MainWindow::on_toolButton_3_clicked()//SCIEZKA OUT PROSTA
{
    ui->lineEdit_4->setText(QFileDialog::getSaveFileName(this,tr("Zapisz dane wynikowe."), ".\\", tr("Pliki .txt (*.txt *.txt *.txt)")));
}

void MainWindow::on_toolButton_clicked()//SCIEZKA IN MAP
{
    ui->lineEdit_5->setText(QFileDialog::getOpenFileName(this,tr("Pobierz punkty obliczeniowe. UWAGA: DANE MUSZA BYC W FORMACIE x[m] | y[m] | z[m] !!!"), ".\\", tr("Pliki .txt (*.txt *.txt *.txt)")));
}

void MainWindow::on_toolButton_2_clicked()//SCIEZKA OUT MAP
{
    ui->lineEdit_6->setText(QFileDialog::getSaveFileName(this,tr("Zapisz dane wynikowe."), ".\\", tr("Pliki .txt (*.txt *.txt *.txt)")));
}


void MainWindow::on_comboBox_9_currentIndexChanged(int index)
{
    QString current_box_text = ui->comboBox_9->currentText();
    if(current_box_text == "mapa"){
        viewed_img_path=".\\rysunki\\mapa.png";
        item_wiz.setPixmap(QPixmap(".\\rysunki\\mapa.png"));
    }else if(current_box_text == "odcinek - wykres Hx"){
        viewed_img_path=".\\rysunki\\prostaHx.png";
        item_wiz.setPixmap(QPixmap(".\\rysunki\\prostaHx.png"));
    }else if(current_box_text == "odcinek - wykres Hy"){
        viewed_img_path=".\\rysunki\\prostaHy.png";
        item_wiz.setPixmap(QPixmap(".\\rysunki\\prostaHy.png"));
    }else if(current_box_text == "odcinek - wykres Hz"){
        viewed_img_path=".\\rysunki\\prostaHz.png";
        item_wiz.setPixmap(QPixmap(".\\rysunki\\prostaHz.png"));
    }else if(current_box_text == "odcinek - wykres gradB skladowa x"){
        viewed_img_path=".\\rysunki\\prostagradB_x.png";
        item_wiz.setPixmap(QPixmap(".\\rysunki\\prostagradB_x.png"));
    }else if(current_box_text == "odcinek - wykres gradB skladowa y"){
        viewed_img_path=".\\rysunki\\prostagradB_y.png";
        item_wiz.setPixmap(QPixmap(".\\rysunki\\prostagradB_y.png"));
    }else if(current_box_text == "odcinek - wykres gradB skladowa z"){
        viewed_img_path=".\\rysunki\\prostagradB_z.png";
        item_wiz.setPixmap(QPixmap(".\\rysunki\\prostagradB_z.png"));
    }
    scene_wiz.addItem(&item_wiz);
    ui->graphicsView->setScene(&scene_wiz);
    ui->graphicsView->fitInView(scene_wiz.itemsBoundingRect(),Qt::KeepAspectRatio);
    ui->graphicsView->show();
}
