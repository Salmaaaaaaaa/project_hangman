#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QRandomGenerator>
#include <QPixmap>
#include <QVector>
#include <QTextStream>

QPushButton* Letters[26];
QString secret_word;
QString current_word;
int attempts;
int cnt_words;
int solved;
QString hangImg[7] = {":/re/try0.png",":/re/try1.png",":/re/try2.png",":/re/try3.png",":/re/try4.png",":/re/try5.png",":/re/try6.png"};
QVector<QString> clicked;
bool playing=false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    for(int i = 0;i<26;i++){
        QString name = "pushButtonA";
        name[10] = QChar(name[10].unicode() + i);
        Letters[i] = MainWindow::findChild<QPushButton*>(name);
        connect(Letters[i],SIGNAL(released()),this,SLOT(LetterClick()));
    }


    QPixmap pix(hangImg[0]);
    ui->label_pic->setPixmap(pix.scaled(260,300));

}

MainWindow::~MainWindow()
{
    delete ui;
}



QString randomWord(){
//here
    QFile file(":/re/dico.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return "no word found";
    QTextStream in(&file);

    QRandomGenerator* gen = QRandomGenerator::system();
    int n = gen->bounded(0,323577);

    QString word;
    while(n>0 and !file.atEnd()){
        n--;
        word = in.readLine();
    }
    return word;
}

void resetButtons(){
    clicked.clear();
    for(int i = 0;i<26;i++){
        Letters[i]->setStyleSheet("");
    }
}

void MainWindow::on_actionNew_Game_triggered()
{
    secret_word = randomWord();
    current_word.clear();
    current_word.resize(secret_word.length(),'-');

    ui->label_word->setText(current_word);

    resetButtons();

    attempts = 0;
    //here
    QPixmap pix(hangImg[attempts]);
    ui->label_pic->setPixmap(pix.scaled(260,300));

    ui->label_win->setText("");
    ui->label_win->setStyleSheet("");

    cnt_words = 0;
    solved = 0;
    playing = true;
    ui->label_ntotal->setText(QString::number(solved)+"/"+QString::number(cnt_words));
}

void MainWindow::LetterClick(){

    if(!playing)
        return;

   QPushButton* button = (QPushButton*)sender();
  // button->setStyleSheet("background-color: rgb(199,148,212);");

  button->setStyleSheet("background-color: rgb(137,210,236);");
   QString Lettre = button->text();
   if(clicked.count(Lettre)>0){
       return;
   }
   else clicked.push_back(Lettre);


   bool found = false;
   for(int i = 0;i<secret_word.length();i++){
       if(secret_word[i] == Lettre[0]){
           found=true;
           current_word[i] = Lettre[0];
       }
   }

   if(!found)
       attempts = (attempts<7)?attempts+1:attempts;

   if(attempts <= 7 and secret_word == current_word){
       ui->label_win->setText("WIN");
       ui->label_win->setStyleSheet("background-color: rgb(0,255,0);");
       solved++;
       int nrow = ui->label_nrow->text().toInt();
       ui->label_nrow->setText(QString::number(nrow+1));
       playing = false;
   }
   else if(attempts == 7){
       ui->label_word->setText(secret_word);
       ui->label_win->setText("GAME OVER");
       ui->label_win->setStyleSheet("background-color: rgb(255,0,0);");
       ui->label_nrow->setText("0");
       playing = false;
   }

   if(attempts<7){
       //here
       QPixmap pix(hangImg[attempts]);
       ui->label_pic->setPixmap(pix.scaled(260,300));
   }

   ui->label_ntotal->setText(QString::number(solved)+"/"+QString::number(cnt_words));

   ui->label_word->setText(current_word);
}


void MainWindow::on_pushButtonNext_clicked()
{
    secret_word = randomWord();
    current_word.clear();
    current_word.resize(secret_word.length(),'-');
    ui->label_word->setText(current_word);

    resetButtons();
    attempts = 0;
    //here
    QPixmap pix(hangImg[attempts]);
    ui->label_pic->setPixmap(pix.scaled(260,300));


    ui->label_win->setText("");
    ui->label_win->setStyleSheet("");

    cnt_words++;
    playing=true;
    ui->label_ntotal->setText(QString::number(solved)+"/"+QString::number(cnt_words));
}


void MainWindow::on_actionReveal_triggered()
{
    playing=false;
    ui->label_word->setText(secret_word);
}


void MainWindow::on_actionSkip_triggered()
{
    cnt_words--;
    on_pushButtonNext_clicked();
}

