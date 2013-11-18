// *************************************************************************
// ************* Homework 4: Implement Hex Board ***************************
// *************************************************************************

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

static const int defaultBoardSize = 7;
static const string empty  = ".";
static const string player = "x";
static const string comp   = "O";

typedef enum GAMER
{
    PLAYER,
    COMPUTER
} gamer_t;

typedef struct hexCell_st
{
    string symbol;
} hexCell_t;

/**
 * @brief The HexBoard class - Implementation of hex board
 */
class HexBoard
{
private:
    int         boardSize;
    hexCell_t** hexBoard;

    void cleanConsole()
    {
        cout << string(100, '\n');
    }

    void showHelp()
    {
        cout << "Input coordinates of empty cell and mark it! \n";
        cout << "For exit press Ctrl+C \n\n";
    }

    int getRandNumber(int max)
    {
        return (rand() % (int)(max + 1));
    }

public:
    HexBoard();
    HexBoard(int size);
    ~HexBoard();

    void showBoard();
    void setCell(int& x, int& y);
    bool markCell(int x, int y, gamer_t gamer);
    void doStep(gamer_t gamer);
    void simulateGame();
};

/**
 * @brief HexBoard::HexBoard - default constructor. Creates 7x7 board
 */
HexBoard::HexBoard()
{
    boardSize = defaultBoardSize;

    hexBoard = new hexCell_t*[boardSize];
    for (int i = 0; i < boardSize; i++) {
        hexBoard[i] = new hexCell_t[boardSize];
    }

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            hexBoard[i][j].symbol = empty;
        }
    }
}

/**
 * @brief HexBoard::HexBoard - creates hex board with given size
 * @param size - size of hex board
 */
HexBoard::HexBoard(int size)
{
    boardSize = size;

    hexBoard = new hexCell_t*[boardSize];
    for (int i = 0; i < boardSize; i++) {
        hexBoard[i] = new hexCell_t[boardSize];
    }

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            hexBoard[i][j].symbol = empty;
        }
    }
}

/**
 * @brief HexBoard::~HexBoard - main destructor
 */
HexBoard::~HexBoard()
{
    for (int i = 0; i < boardSize; i++) {
        delete[] hexBoard[i];
    }
    delete[] hexBoard;
}

/**
 * @brief HexBoard::showBoard - print board in current state
 */
void HexBoard::showBoard()
{
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {

            if (j != 0)
                cout << "- ";
            cout << hexBoard[i][j].symbol << " ";
        }
        cout << endl;
        for (int spaces = 0; spaces < 2*i+1; spaces++) {
            cout << " ";
        }

        if (i != boardSize-1)
            for (int j = 0; j < boardSize; j++) {

                cout << "\\ ";
                if (j != boardSize-1) {
                    cout << "/ ";
                }
            }
        cout << endl;
        for (int spaces = 0; spaces < 2*i+2; spaces++) {
            cout << " ";
        }
    }
}

/**
 * @brief HexBoard::setCell - set coordinates of cell to mark
 */
void HexBoard::setCell(int& x, int& y)
{
    int getX, getY;

    cout << "\rEnter new location [0.." << boardSize-1 << " 0.." << boardSize-1 << "] : ";
    cin >> getX >> getY;

    if ((getX < 0 || getX > boardSize-1) ||
        (getY < 0 || getY > boardSize-1)) {
        cout << "Invalid input values! Try again" << endl;
        setCell(x, y);
    }
    else {
        x = getX;
        y = getY;
    }
}

/**
 * @brief HexBoard::markCell - mark cell by gamer
 * @return true if cell can be marked, otherwise false
 */
bool HexBoard::markCell(int x, int y, gamer_t gamer)
{
    if ((x < 0 || x > boardSize-1) ||
        (y < 0 || y > boardSize-1)) {
        return false;
    }

    if (hexBoard[x][y].symbol.compare(empty) != 0) {
        return false;
    }

    hexBoard[x][y].symbol = (gamer == COMPUTER) ? comp : player;
    return true;
}

/**
 * @brief HexBoard::doStep - do game step by gamer
 */
void HexBoard::doStep(gamer_t gamer)
{
    bool isMarked = false;
    int  x = 0;
    int  y = 0;

    if (PLAYER == gamer) {
        do {
            setCell(x, y);
            isMarked = markCell(x, y, PLAYER);
        } while (!isMarked);
    }
    else {
        do {
            isMarked = markCell(getRandNumber(boardSize-1),
                                getRandNumber(boardSize-1),
                                COMPUTER);
        } while (!isMarked);
    }
}

/**
 * @brief HexBoard::simulateGame - simple game simulation
 */
void HexBoard::simulateGame()
{
    srand(time(NULL));

    while(1) {
        cleanConsole();
        showHelp();
        showBoard();
        doStep(PLAYER);
        doStep(COMPUTER);
    }
}

int main()
{
    int size;
    cout << "Input size of board : ";
    cin >> size;

    HexBoard board = HexBoard(size);

    board.simulateGame();
    
    board.~HexBoard();

    return 0;
}
