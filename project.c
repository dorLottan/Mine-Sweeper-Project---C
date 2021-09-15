
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//default values of the max arrys size because we haven't learned dynamic assignments yet
#define COLS 22
#define ROWS 22

void menu();
void createGameBoards(char visibleUserGameBoard[][COLS], char userGameBoard[][COLS], int numberOfRows, int numberOfCols, int numberOfMines);
void placeMines(char userGameBoard[][COLS], int numberOfRows, int numberOfCols, int numberOfMines);
void calcNumbers(char userGameBoard[][COLS], int numberOfRows, int numberOfCols);
void printBoard(char board[][COLS], int numberOfRows, int numberOfCols);
int countMines(char userGameBoard[][COLS], int row, int col, int numberOfRows, int numberOfCols);
bool validMove(char visibleUserGameBoard[][COLS], int userRowSelection, int userColSelection, int numberOfRows, int numberOfCols, int userCharSelection);
bool autoOpen(char userGameBoard[][COLS], char visibleUserGameBoard[][COLS], int numberOfRows, int numberOfCols, int userColSelection);
bool validAutoOpen(char userGameBoard[][COLS], char visibleUserGameBoard[][COLS], int rowOfEmptyBox, int colOfEmptyBox);
void playGame(char userGameBoard[][COLS], char visibleUserGameBoard[][COLS], int numberOfRows, int numberOfCols, int numberOfMines);
int startGame(int level);
bool isValid(int row, int col);
bool isMine(int row, int col, char userGameBoard[][COLS]);
bool playMinesweeperUtil(char visibleUserGameBoard[][COLS], char userGameBoard[][COLS], int row, int col, int *movesLeft);

int main()
{
  int level;
  menu();
  scanf("%d", &level);

  while (level > 4 || level < 0)
  {
    menu();
    scanf("%d", &level);
  }
  if (level == 0)
  {
    return 0;
  }
  else
  {
    startGame(level);
  }
}

//Prints the game menu
void menu()
{
  printf("Welcome to MineSweepers");
  printf("\n");
  printf("Please choose one of the following options and enter it's number: \n");
  printf("1 - for size 8X8 \n");
  printf("2 - for size 12X12 \n");
  printf("3 - for size 15X15 \n");
  printf("4 - for custom size \n");
  printf("0 - Exit \n");
}

//Initializing the user visable board with 'X' in every box, and the game board with spaces
void createGameBoards(char visibleUserGameBoard[][COLS], char userGameBoard[][COLS], int numberOfRows, int numberOfCols, int numberOfMines)
{
  int i, j;

  for (i = 0; i < numberOfRows; i++)
  {
    for (j = 0; j < numberOfCols; j++)
    {
      visibleUserGameBoard[i][j] = 'X';
      userGameBoard[i][j] = ' ';
    }
  }

  placeMines(userGameBoard, numberOfRows, numberOfCols, numberOfMines);
  calcNumbers(userGameBoard, numberOfRows, numberOfCols);
}

//This func places mines randomly into the game board matrix
void placeMines(char userGameBoard[][COLS], int numberOfRows, int numberOfCols, int numberOfMines)
{
  int count = numberOfMines;
  srand(time(NULL));
  while (count > 0)
  {
    int x = rand() % numberOfRows;
    int y = rand() % numberOfCols;
    if (userGameBoard[x][y] == ' ')
    {
      userGameBoard[x][y] = '*';
      count--;
    }
  }
}

//This func runs at the begging. It gets coords of a box on the game board, calls to count the surrounding mines of it, and saves that number in the non-visual game board.
void calcNumbers(char userGameBoard[][COLS], int numberOfRows, int numberOfCols)
{
  int i, j;

  for (i = 0; i < numberOfRows; i++)
  {
    for (j = 0; j < numberOfCols; j++)
    {
      if (userGameBoard[i][j] == ' ')
      {
        userGameBoard[i][j] = countMines(userGameBoard, i, j, numberOfRows, numberOfCols) + '0';
      }
    }
  }
}

//This func prints the game board that it gets
void printBoard(char board[][COLS], int numberOfRows, int numberOfCols)
{
  int i, j, k, f;
  printf("         ");
  for (i = 0; i < numberOfCols; i++)
  {
    if (i < 9)
    {
      printf("%d   ", i);
    }
    else
    {
      printf("%d  ", i);
    }
  }
  printf("\n");
  printf("    ----");
  for (f = 0; f < numberOfCols; f++)
  {
    printf("----");
  }
  printf("\n");

  for (j = 0; j < numberOfRows; j++)
  {
    if (j < 10)
    {
      printf("     %d |", j);
    }
    else
    {
      printf("    %d |", j);
    }
    for (k = 0; k < numberOfCols; k++)
    {
      if (board[j][k] == '0')
      {
        printf("   |");
      }
      else
      {
        printf(" %c |", board[j][k]);
      }
    }
    printf("\n");
  }
  printf("    ----");
  for (f = 0; f < numberOfCols; f++)
  {
    printf("----");
  }
  printf("\n");
}

//This func gets coords from the game board and returns the number of mines that are surround it
int countMines(char userGameBoard[][COLS], int row, int col, int numberOfRows, int numberOfCols)
{
  int count = 0;

  //LEFT
  if (isValid(row, col - 1) == true)
  {
    if (isMine(row, col - 1, userGameBoard) == true)
      count++;
  }
  //RIGHT
  if (isValid(row, col + 1) == true)
  {
    if (isMine(row, col + 1, userGameBoard) == true)
      count++;
  }
  //UP_LEFT
  if (isValid(row - 1, col - 1) == true)
  {
    if (isMine(row - 1, col - 1, userGameBoard) == true)
      count++;
  }
  //UP
  if (isValid(row - 1, col) == true)
  {
    if (isMine(row - 1, col, userGameBoard) == true)
      count++;
  }
  //UP_RIGHT
  if (isValid(row - 1, col + 1) == true)
  {
    if (isMine(row - 1, col + 1, userGameBoard) == true)
      count++;
  }
  //DOWN_LEFT
  if (isValid(row + 1, col - 1) == true)
  {
    if (isMine(row + 1, col - 1, userGameBoard) == true)
      count++;
  }
  //DOWN
  if (isValid(row + 1, col) == true)
  {
    if (isMine(row + 1, col, userGameBoard) == true)
      count++;
  }
  //DOWN_RIGHT
  if (isValid(row + 1, col + 1) == true)
  {
    if (isMine(row + 1, col + 1, userGameBoard) == true)
      count++;
  }

  return count;
}

//Returns T\F if the char that enterd by the user is valid
//and if the coords that the user choose are inside the game borders
//and that the chosen box is closed or is already flagged
bool validMove(char visibleUserGameBoard[][COLS], int userRowSelection, int userColSelection, int numberOfRows, int numberOfCols, int userCharSelection)
{
  return (((userCharSelection == 'F') || (userCharSelection == 'f') || (userCharSelection == 'O') || (userCharSelection == 'o')) &&
          (userRowSelection >= 0) && (userRowSelection < numberOfRows) && (userColSelection >= 0) && (userColSelection < numberOfCols) &&
          ((visibleUserGameBoard[userRowSelection][userColSelection] == 'X') || visibleUserGameBoard[userRowSelection][userColSelection] == 'F'));
};

// Returns T\F if row and column numbers are inside the boarders
bool isValid(int row, int col)
{
  return (row >= 0) && (row < ROWS) &&
         (col >= 0) && (col < COLS);
}

//Check if the selected move is on a mine
bool isMine(int row, int col, char userGameBoard[][COLS])
{
  if (userGameBoard[row][col] == '*')
    return (true);
  else
    return (false);
}

//This func opens a number of boxes that are chosen by user (that aren't mines or opened) automatically
bool autoOpen(char userGameBoard[][COLS], char visibleUserGameBoard[][COLS], int numberOfRows, int numberOfCols, int userColSelection)
{
  bool firstEmptyBox = false;
  int rowOfEmptyBox, colOfEmptyBox;

  //gets the coords of the first close box without mines
  for (int i = 0; i < numberOfRows; i++)
  {
    for (int j = 0; j < numberOfCols; j++)
    {
      if (!firstEmptyBox)
      {
        if (validAutoOpen(visibleUserGameBoard, userGameBoard, i, j))
        {
          rowOfEmptyBox = i;
          colOfEmptyBox = j;
          firstEmptyBox = true;
          break;
        }
      }
    }
  }

  bool isOpening = true;
  int counter = 0;

  while (isOpening)
  {
    if (validAutoOpen(visibleUserGameBoard, userGameBoard, rowOfEmptyBox, colOfEmptyBox))
    {
      visibleUserGameBoard[rowOfEmptyBox][colOfEmptyBox] = userGameBoard[rowOfEmptyBox][colOfEmptyBox];
      counter++;
    }
    if (colOfEmptyBox == (numberOfCols - 1))
    {
      colOfEmptyBox = 0;
      if (rowOfEmptyBox == (numberOfRows - 1))
      {
        //the user opened all the boxes and the game is over
        isOpening = false;
        return true;
      }
      else
      {
        rowOfEmptyBox++;
      }
    }
    else
    {
      colOfEmptyBox++;
    }
    if (counter == userColSelection)
    {
      isOpening = false;
    }
  }

  printBoard(visibleUserGameBoard, numberOfRows, numberOfCols);
  return false;
}

//Checks if the coords of the autoOpen points on a valid box to open (not on a mine, only boxes that are closed or flagged)
bool validAutoOpen(char visibleUserGameBoard[][COLS], char userGameBoard[][COLS], int rowOfEmptyBox, int colOfEmptyBox)
{
  return (((visibleUserGameBoard[rowOfEmptyBox][colOfEmptyBox] == 'X') || (visibleUserGameBoard[rowOfEmptyBox][colOfEmptyBox] == 'F')) && (userGameBoard[rowOfEmptyBox][colOfEmptyBox] != '*'));
}

//This func gets the chosen level and starts the game according to it
int startGame(int level)
{
  int numberOfRows = 0, numberOfCols = 0, numberOfMines = 0;
  char userGameBoard[ROWS][COLS];
  char visibleUserGameBoard[ROWS][COLS];

  switch (level)
  {
  case (1):
    numberOfRows = 8;
    numberOfCols = 8;
    numberOfMines = 8;
    break;
  case (2):
    numberOfRows = 12;
    numberOfCols = 12;
    numberOfMines = 12;
    break;
  case (3):
    numberOfRows = 15;
    numberOfCols = 15;
    numberOfMines = 15;
    break;
  case (4):
    printf("Please enter the size of the board (Rows <=22 and Cols <=22): ");
    scanf("%d%d", &numberOfRows, &numberOfCols);
    if ((numberOfRows == 1) && (numberOfCols == 1))
    {
      printf("YOU WON! \n");
      return 0;
    }
    while ((numberOfRows > 22) || (numberOfRows < 1) || (numberOfCols > 22) || (numberOfCols < 1))
    {
      if ((numberOfRows > 22) || (numberOfRows < 1))
      {
        printf("Number of rows is out of range!\n");
      }
      if ((numberOfCols > 22) || (numberOfCols < 1))
      {
        printf("Number of cols is out of range! \n");
      }
      printf("Please enter the size of the board (Rows <=22 and Cols <=22): ");
      scanf("%d%d", &numberOfRows, &numberOfCols);
    }
    numberOfMines = sqrt(numberOfRows * numberOfCols);
    break;
  default:
    return 0;
    break;
  }

  createGameBoards(visibleUserGameBoard, userGameBoard, numberOfRows, numberOfCols, numberOfMines);
  printBoard(visibleUserGameBoard, numberOfRows, numberOfCols);
  playGame(visibleUserGameBoard, userGameBoard, numberOfRows, numberOfCols, numberOfMines);
  return 0;
}

//The process of the game, scans the move coords from the user, checks if they are valid and then prints the board with the updated result
//(The chosen box is opens and shows the number of the mines surrounding it)
//The function repeats itself until the user has hit a mine or until he has opened all possible boxes
void playGame(char visibleUserGameBoard[][COLS], char userGameBoard[][COLS], int numberOfRows, int numberOfCols, int numberOfMines)
{
  int userRowSelection = 0;
  int userColSelection = 0;
  char userCharSelection;
  int countMoves = 0;
  int rowOfEmptyBox, colOfEmptyBox;
  bool gameOver = false;

  while (gameOver == false)
  {
    printf("Please enter your move, row and column : ");
    scanf(" %c%d%d", &userCharSelection, &userRowSelection, &userColSelection);

    //autoOpen also needs to scan the char 'O'/'o' before the coords to run
    if ((userCharSelection == 'o') && (userRowSelection == -1) && (userColSelection > 0))
    {
      //If the user opened all the boxes via the auto open the game is over
      //otherwise the open boxes counts as moves
      if (autoOpen(userGameBoard, visibleUserGameBoard, numberOfRows, numberOfCols, userColSelection))
      {
        printBoard(userGameBoard, numberOfRows, numberOfCols);
        printf("YOU WON! \n");
        return;
      }
      countMoves = countMoves + userColSelection;
    }
    else if (validMove(visibleUserGameBoard, userRowSelection, userColSelection, numberOfRows, numberOfCols, userCharSelection))
    {
      if (isMine(userRowSelection, userColSelection, userGameBoard) && ((userCharSelection == 'o') || (userCharSelection == 'O')))
      {
        printf("YOU LOST!! \n");
        printBoard(userGameBoard, numberOfRows, numberOfCols);
        gameOver = true;
      }
      else
      {
        if ((userCharSelection == 'f') || (userCharSelection == 'F'))
        {
          visibleUserGameBoard[userRowSelection][userColSelection] = 'F';
          printBoard(visibleUserGameBoard, numberOfRows, numberOfCols);
        }
        else
        {
          //if the box is flagged, the func opens only that box, without floodfill
          if (visibleUserGameBoard[userRowSelection][userColSelection] == 'F')
          {
            visibleUserGameBoard[userRowSelection][userColSelection] = userGameBoard[userRowSelection][userColSelection];
            countMoves++;
          }
          gameOver = playMinesweeperUtil(visibleUserGameBoard, userGameBoard, userRowSelection, userColSelection, &countMoves);
          printBoard(visibleUserGameBoard, numberOfRows, numberOfCols);
        }
      }
    }
    else
    {
      printf("Please enter a valid choice!\n");
    }
    if ((gameOver == false) && (countMoves == (numberOfRows * numberOfCols) - numberOfMines))
    {
      printf("\n YOU WON !\n");
      gameOver = true;
    }
  }
}
//Recursive function that opens all the empty boxes next to the selected box, until it reaches a non-empty box
bool playMinesweeperUtil(char visibleUserGameBoard[][COLS], char userGameBoard[][COLS], int row, int col, int *countMoves)
{
  // Base
  if ((visibleUserGameBoard[row][col] != 'X'))
  {
    return false;
  }

  visibleUserGameBoard[row][col] = userGameBoard[row][col];
  (*countMoves)++;

  if (userGameBoard[row][col] == '0')
  {
    //LEFT
    if (isValid(row, col - 1) == true)
    {
      playMinesweeperUtil(visibleUserGameBoard, userGameBoard, row, col - 1, countMoves);
    }

    //RIGHT
    if (isValid(row, col + 1) == true)
    {
      playMinesweeperUtil(visibleUserGameBoard, userGameBoard, row, col + 1, countMoves);
    }

    //UP_LEFT
    if (isValid(row - 1, col - 1) == true)
    {
      playMinesweeperUtil(visibleUserGameBoard, userGameBoard, row - 1, col - 1, countMoves);
    }

    //UP
    if (isValid(row - 1, col) == true)
    {
      playMinesweeperUtil(visibleUserGameBoard, userGameBoard, row - 1, col, countMoves);
    }

    //UP_RIGHT
    if (isValid(row - 1, col + 1) == true)
    {
      playMinesweeperUtil(visibleUserGameBoard, userGameBoard, row - 1, col + 1, countMoves);
    }

    //DOWN_LEFT
    if (isValid(row + 1, col - 1) == true)
    {
      playMinesweeperUtil(visibleUserGameBoard, userGameBoard, row + 1, col - 1, countMoves);
    }

    //DOWN
    if (isValid(row + 1, col) == true)
    {
      playMinesweeperUtil(visibleUserGameBoard, userGameBoard, row + 1, col, countMoves);
    }

    //DOWN_RIGHT
    if (isValid(row + 1, col + 1) == true)
    {
      if (isMine(row + 1, col + 1, userGameBoard) == false)
        playMinesweeperUtil(visibleUserGameBoard, userGameBoard, row + 1, col + 1, countMoves);
    }
  }
  return false;
}
