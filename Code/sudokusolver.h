/*
    Created on Monday Nov 3, 2014
    @author: Mingna Zheng
*/

#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <QMainWindow>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QVector>
#include <QStandardItemModel>
#include <QDebug>
#include <QMessageBox>

#include "ui_sudokusolver.h"

using namespace std;

class SudokuSolver : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit SudokuSolver(QWidget *parent = 0);
    ~SudokuSolver();
    
private slots:
    void on_action_Open_triggered();
    void on_pushButton_clicked();
    void on_actionSave_Solution_triggered();

    bool sudokuCheck();
    bool lengthCheck();
    void converttoGrid();
    void fillModel(int m);
    int solve();
    int Recursive_Solve(int r, int c);
    int Is_Row_Valid(int r);
    int Is_Col_Valid(int c);
    int Is_Panel_Valid(int sr, int sc);



private:
    Ui::SudokuSolver *ui;
    QStringList csv;
    QStandardItemModel *model[2];
    int Grid[9][9];
    QVector <int> checker;
    bool ready;
};

#endif
