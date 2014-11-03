/*
    Created on Monday Nov 3, 2014
    @author: Mingna Zheng
*/

#include "sudokusolver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SudokuSolver w;
    w.show();
    
    return a.exec();
}
