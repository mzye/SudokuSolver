/*
    Created on Monday Nov 3, 2014
    @author: Mingna Zheng
*/

#include "sudokusolver.h"

SudokuSolver::SudokuSolver(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SudokuSolver)
{
    ui->setupUi(this);
    ui->tableView_2->hide();
    checker.resize(10);
    for (int i=0; i<2;i++)
    {
        model[i] = new QStandardItemModel(this);
        model[i]->setColumnCount(9);
        model[i]->setRowCount(9);
    }
}

SudokuSolver::~SudokuSolver()
{
    delete ui;
}

/* Load the csv file and dsiplay the Sudoku puzzle */
void SudokuSolver::on_action_Open_triggered()
{
    ui->tableView->setModel(model[0]);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->hide();
    for (int i=0; i<9; i++)
    {
        ui->tableView->setColumnWidth(i,25);
        ui->tableView->setRowHeight(i,25);
    }
    QString fileName = QFileDialog::getOpenFileName (this, "Open CSV file",
                                                     QDir::currentPath(), "CSV (*.csv)");
    QFile file (fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        QString data = file.readAll();
        data.replace( QRegExp("[\r\n]+"), "," ); //remove all ocurrences of CR (Carriage Return)
        csv = data.split(",");
    }
    file.close();
//    qDebug() << csv;

    converttoGrid();
    if (!sudokuCheck())
    {
    fillModel(0);
    }
}

/* Click the 'Solve puzzle' button to run the solving process, and the reulst will be showed in a new table. */
void SudokuSolver::on_pushButton_clicked()
{
     solve();
     ui->tableView_2->show();
     this->adjustSize();
     ui->tableView_2->setModel(model[1]);
     ui->tableView_2->verticalHeader()->hide();
     ui->tableView_2->horizontalHeader()->hide();
     for (int i=0; i<9; i++)
     {
         ui->tableView_2->setColumnWidth(i,25);
         ui->tableView_2->setRowHeight(i,25);
     }
     fillModel(1);
//     qDebug()<<Grid;
}

/* Save the solution to a csv file. */
void SudokuSolver :: on_actionSave_Solution_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    "DialogTitle", "solution.csv", "CSV files (*.csv);;Zip files (*.zip, *.7z)", 0, 0);
    QFile result(filename);
    if(result.open(QFile::WriteOnly |QFile::Truncate))
    {
        QTextStream output(&result);
        QStringList strList;

        for (int i=0; i<model[1]->rowCount(); ++i)
        {
          strList.clear();
          for (int j=0; j<model[1]->columnCount(); j++)
          {
            strList<<model[1]->item(i,j)->text();
           }
          output<<strList.join(",")+"\n";
         }
        result.close();
    }
}

/* Check if the input is a validate Sudoku puzzle. */
int SudokuSolver::sudokuCheck()
{
    QMessageBox messageBox;
    messageBox.setFixedSize(400,200);

    for(int i=0; i<9;i++)
    {
        if(!Is_Row_Valid(i))
        {
            messageBox.critical(0, "Error", "Bad Sudoku File -- Bad row!\n");
            return 1;
        }

        if(!Is_Col_Valid(i))
        {
            messageBox.critical(0, "Error", "Bad Sudoku File -- Bad col!\n");
            return 1;
        }
    }

    for(int i=0; i<9; i+=3)
    {
        for (int j=0; j<9; j+=3)
        {
            if (!Is_Panel_Valid(i,j))
            {
                messageBox.critical(0,"Error", "Bad Sudoku File -- Bad panel!\n");
            }
        }
    }

    return 0;
}

/* Fill the model with numbers for tableview. */
void SudokuSolver::fillModel(int m)
{
    const int NUM_ROWS = 9;
    const int NUM_COLS = 9;
    QStandardItem *item;

    for (int row = 0; row < NUM_ROWS; row++)
    {
        for(int col = 0; col < NUM_COLS; col++)
        {
            if (Grid[row][col] != 0)
            {
                 item = new QStandardItem(QString("%0").arg(Grid[row][col]));
            }
            else
            {
                 item = new QStandardItem(QString(" "));
            }
            model[m]->setItem(row, col,item);
        }
    }
}

/* Convert numbers to 9*9 grid. */
void SudokuSolver :: converttoGrid()
{
    const int NUM_ROWS = 9;
    const int NUM_COLS = 9;

    for (int row = 0; row < NUM_ROWS; row++)
    {
        for(int col = 0; col < NUM_COLS; col++)
        {
            Grid[row][col] = csv[col + (row * NUM_COLS)].toInt();
        }
    }
//    qDebug()<<Grid;
}

/* Recursive backstracking. */
int SudokuSolver :: solve()
{
    return Recursive_Solve(0, 0);
}

int SudokuSolver::Recursive_Solve(int r, int c)
{
    int i;

      while (r < 9 && Grid[r][c] != 0)
      {
        c++;
        if (c == 9)
        {
          r++;
          c = 0;
        }
      }

      /* Base case -- we're done */
      if (r == 9) return 1;

      /* Try each value.  If successful, then return true. */
      for (i = 1; i <= 9; i++)
      {
        Grid[r][c] = i;
        if (Is_Row_Valid(r) &&
            Is_Col_Valid(c) &&
            Is_Panel_Valid(r-r%3, c-c%3) &&
            Recursive_Solve(r, c))
        {
          return 1;
        }
      }

      /* If unsuccessful, reset the element and return false. */

      Grid[r][c] = 0;
      return 0;
}

/* Check no row contains the same number twice. */
int SudokuSolver :: Is_Row_Valid(int r)
{
  int i;

  for (i = 1; i <= 9; i++) checker[i] = 0;

  for (i = 0; i < 9; i++)
  {
    if (Grid[r][i] != 0)
    {
      if (checker[Grid[r][i]]) return 0;
      checker[Grid[r][i]] = 1;
    }
  }
  return 1;
}

/* Check no column contains the same number twice. */
int SudokuSolver:: Is_Col_Valid(int c)
{
  int i;

  for (i = 1; i <= 9; i++) checker[i] = 0;

  for (i = 0; i < 9; i++)
  {
    if (Grid[i][c] != 0)
    {
      if (checker[Grid[i][c]]) return 0;
      checker[Grid[i][c]] = 1;
    }
  }
  return 1;
}

/*Check there are 9 3x3 panels in the grid, starting with the upper left-hand corner. No 3x3 panel may contain the same number twice.*/
int SudokuSolver :: Is_Panel_Valid(int sr, int sc)
{
  int r, c, i;
  for (i = 1; i <= 9; i++) checker[i] = 0;

  for (r = sr; r < sr+3; r++)
  {
    for (c = sc; c < sc+3; c++)
    {
      if (Grid[r][c] != 0)
      {
        if (checker[Grid[r][c]]) return 0;
        checker[Grid[r][c]] = 1;
      }
    }
  }
  return 1;
}



