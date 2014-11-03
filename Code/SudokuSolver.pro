QMAKE_CFLAGS = -fpermissive
QMAKE_CXXFLAGS = -fpermissive
QMAKE_LFLAGS = -fpermissive

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SudokuSolver
TEMPLATE = app


SOURCES += main.cpp\
        SudokuSolver.cpp

HEADERS  += sudokusolver.h

FORMS    += sudokusolver.ui
