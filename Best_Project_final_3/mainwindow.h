#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void LetterClick();

    void on_actionNew_Game_triggered();

    void on_pushButtonNext_clicked();

    void on_actionReveal_triggered();

    void on_actionSkip_triggered();

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
