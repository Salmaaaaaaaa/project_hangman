

 ![](./hang.png)


![](./goal.gif)


The goal of this project is to build an application of hangman.     
It's basically a game of guessing words.
In case you are not familiar with the hangman game, here is
how it is played.           
A puzzle category is provided and a series of blank spaces are given to the player in order to guess
letters to solve the puzzle.     
We will  allow
the user 9 guesses in order to get the puzzle correct, if not he's gonna fail.      
 Here is a sample:
Let's say the word is TEACHER:                 
_ _
_
_
_ _ 
_

The player tries to guess the letters in the word.
Each time they guess a letter correctly, the first player fills in the
blanks for each occurrence of that letter. For example, if the guessing player guessed the letter E, the first player would fill in the Es
in the word TEACHER like so:

_ E _ _ _ E _

![](./rules.gif)


* The user sees a label with one "_" for each letter in the word
* The user will enter letters one at a time
* If the user guesses a correct letter, all instances of that word are made visible in the label
* If the user guesses an incorrect letter, the hangman gets one body part added
* The user wins when all the correct letters are revealed and they see the full word
* The user loses when they have made 9 incorrect guesses and the full hangman is visible


<h2><span style="color:black"><strong>Required </strong></span></h2>	

* A <strong>Skip</strong> Button (to start a New Game and also skip words)

* A <strong>Reveal</strong>  action 

* A method of guessing letters

* A UILabel that indicates the incorrect guesses (on the same screen).

* A square-dimensioned UIImageView that represents the "state" of the Hangman.

* Appropriate design for each "state" of the Hangman 

* Use constraints - any and all views must scale to different devices

* A win state, indicated by an Alert 
Should prevent additional guesses

* A fail state, indicated by an Alert 
Should prevent additional guesses


![](./steps.gif)

  <h2><span style="color:darkgrey">   First: </span></h2>	
   
   * We're going to create a function called randomword in order to generate a random word to guess from our file using the syntax below:
   
   ``` cpp
   QString randomWord(){

    QFile file("dico.txt");
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
```
   
   <h2><span style="color:darkgrey">   Second: </span></h2>	

  * After that we're going to create a function that whenever you click on a letter:   

       It shows in the label of the word or you lose a guess and part of the body will be added.
       
       Either way the color of the push button will be changed and the player will no longer be able to press it

   *  This function will also allow us to show a win label if the player guesses the word correctly and a game over label if he loses.


 ``` cpp
void MainWindow::LetterClick(){

    if(!playing)
        return;

   QPushButton* button = (QPushButton*)sender();
   button->setStyleSheet("background-color: rgb(255,255,0);");
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
       QPixmap pix(hangImg[attempts]);
       ui->label_pic->setPixmap(pix.scaled(260,300));
   }

   ui->label_ntotal->setText(QString::number(solved)+"/"+QString::number(cnt_words));

   ui->label_word->setText(current_word);
}


 ``` 

<h2><span style="color:black"><strong>Main Window </strong></span></h2>	

#### Our tool bar will contain the following actions:

<strong>New game</strong>:

       This action will allow the player to start playing.

<strong>Reveal</strong>

       This action will allow the player to reveal the guessed word if he dosen't desire to continue the gmae.

<strong>Skip</strong>

       This action will allow the player to skip the word generated randomly and try to guess another one who will also be generated randomly.


<h2><span style="color:black"><strong>Widgets </span></strong></h2>	

#### In order to create our game we needed some widgets which are:

A <span style="color:grey"><strong>Push button </span></strong>

 We used this widget for all of the letters so that the player can be able to click on them and by that trigger and action.

 We also used in order to implement the action "next" that allow the player to start playing and also skip the word to be guessed.

 A <span style="color:grey"><strong>Label </span></strong>

 The label is used not only to see letters that are guessed in our word but also to know how many words are guessed in a row, and the words that are guessed in total.


![](./result.gif)

Here is a stimulation of our final result of the game, hope you enjoy it:
# 

![](./finaal.gif)









