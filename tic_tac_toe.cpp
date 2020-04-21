#include <bits/stdc++.h>
using namespace std;

char board[3][3] = {{' ', ' ', ' '},
					{' ', ' ', ' '},
					{' ', ' ', ' '}};
string currentPlayer = "AI";

char AI = 'X';
char HUMAN = 'O';

void displayBoard() {
	cout << "     1     2     3   \n";
	cout << "  -----------------\n";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j ++) {
			if (j == 0)
				cout << (i + 1) << " || " << board[i][j] << " ";
			else
				cout << "|| " << board[i][j] << " ";
		}
		cout << "||\n";
		cout << "  -----------------\n";
	}
}

char isWinner(char symbol) {
	if (
		board[0][0] == symbol && board[0][1] == symbol && board[0][2] == symbol ||
		board[1][0] == symbol && board[1][1] == symbol && board[1][2] == symbol ||
		board[2][0] == symbol && board[2][1] == symbol && board[2][2] == symbol 
	) return symbol;
	if (
		board[0][0] == symbol && board[1][0] == symbol && board[2][0] == symbol ||
		board[0][1] == symbol && board[1][1] == symbol && board[2][1] == symbol ||
		board[0][2] == symbol && board[1][2] == symbol && board[2][2] == symbol
	) return symbol;
	if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) 
		return symbol;
	if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
		return symbol;
	int emptyCell = 0;
	for (int i = 0; i < 3; i ++) {
		for (int j = 0; j < 3; j ++) {
			if (board[i][j] == ' ') {
				emptyCell++;
			}
		}
	}
	if (emptyCell == 0) return 'T';
	else return 'N';
}

void humanTurn() {
	int x, y;
	cout << "\nYour Turn:";
	do {
		cout << "\nEnter your position: \n\tRow : ";
		cin >> x;
		cout << "\tCol : ";
		cin >>y;
		if (x > 4 || y > 4) {
			cout << "\nOut of Bounds!! Please try enter again ";
			continue;
		}
		if (board[x - 1][y - 1] == ' ')
			break;
		else
			cout << "The entered position has already been taken!";
	} while(true);
	board[x - 1][y - 1] = HUMAN;
	currentPlayer = "AI";
}

int aiMinimax(int depth, bool isMaximizing, char player) {
	char winner = isWinner(player);
	if (winner == AI)
		return 1;
	else if (winner == HUMAN)
		return -1;
	else {
		if (winner == 'T')
			return 0;
	}
	if (isMaximizing) {
		int best_score = -99999;
		int score;
		for (int i = 0; i < 3; i ++) {
			for (int j = 0; j < 3; j ++) {
				if (board[i][j] == ' ') {
					board[i][j] = AI;
					score = aiMinimax(depth + 1, false, HUMAN);
					board[i][j] = ' ';
					best_score = max(best_score, score);
				}
			}
		}
		return best_score;
	}
	else {
		int best_score = INT_MAX;
		int score;
		for (int i = 0; i < 3; i ++) {
			for (int j = 0; j < 3; j ++) {
				if (board[i][j] == ' ') {
					board[i][j] = HUMAN;
					score = aiMinimax(depth + 1, true, AI);
					board[i][j] = ' ';
					best_score = min(best_score, score);
				}
			}
		}
		return best_score;		
	}
}

int main() {
	char winner;
	while (true) {
		if (currentPlayer == "AI") {	
			int score = 0;
			int best = -999999;
			int move_x, move_y;
			for (int i = 0; i < 3; i ++) {
				for (int j = 0; j < 3; j ++) {
					if (board[i][j] == ' ') {
						board[i][j] = AI;
						score = aiMinimax(0, false, AI);
						board[i][j] = ' ';
						if (score > best) {
							best = score;
							move_x = i;
							move_y = j;
						}
					}
				}
			}
			board[move_x][move_y] = AI;
			winner = isWinner(AI);
			if (winner == AI || winner == 'T')
				break;
			currentPlayer = "HUMAN";
			cout << "\n AI's Turn:\n";
			displayBoard();
		}
		else {
			humanTurn();
			winner = isWinner(HUMAN);
			if (winner == HUMAN || winner == 'T')
				break;
			displayBoard();
		}
	}
	if (winner == 'T')
		cout << "\n" << "TIE!\n";
	else if (currentPlayer == "HUMAN")
		cout << "\n" << "YOU (" << HUMAN << ") WIN!\n";
	else
		cout << "\n" << "AI (" << AI << ") WINS!\n";
	displayBoard();
	return 0;
}

/*
OUTPUT:
    1     2     3
  -----------------
1 || X ||   ||   ||
  -----------------
2 ||   ||   ||   ||
  -----------------
3 ||   ||   ||   ||
  -----------------

Enter your position:
        Row : 1
        Col : 3
    1     2     3
  -----------------
1 || X ||   || O ||
  -----------------
2 ||   ||   ||   ||
  -----------------
3 ||   ||   ||   ||
  -----------------
    1     2     3
  -----------------
1 || X ||   || O ||
  -----------------
2 || X ||   ||   ||
  -----------------
3 ||   ||   ||   ||
  -----------------

Enter your position:
        Row : 3
        Col : 1
    1     2     3
  -----------------
1 || X ||   || O ||
  -----------------
2 || X ||   ||   ||
  -----------------
3 || O ||   ||   ||
  -----------------
    1     2     3
  -----------------
1 || X ||   || O ||
  -----------------
2 || X || X ||   ||
  -----------------
3 || O ||   ||   ||
  -----------------

Enter your position:
        Row : 3
        Col : 3
    1     2     3
  -----------------
1 || X ||   || O ||
  -----------------
2 || X || X ||   ||
  -----------------
3 || O ||   || O ||
  -----------------

HUMAN (O) WINS!    1     2     3
  -----------------
1 || X ||   || O ||
  -----------------
2 || X || X || X ||
  -----------------
3 || O ||   || O ||
  -----------------

C:\Users\admin\Desktop\Trimester 9\Artificial Intelligence>g++ tic_tac_toe.cpp

C:\Users\admin\Desktop\Trimester 9\Artificial Intelligence>a.exe
    1     2     3
  -----------------
1 || X ||   ||   ||
  -----------------
2 ||   ||   ||   ||
  -----------------
3 ||   ||   ||   ||
  -----------------

Enter your position:
        Row :   ^C
C:\Users\admin\Desktop\Trimester 9\Artificial Intelligence>g++ tic_tac_toe.cpp

C:\Users\admin\Desktop\Trimester 9\Artificial Intelligence>a.exe

 AI's Turn:
    1     2     3
  -----------------
1 || X ||   ||   ||
  -----------------
2 ||   ||   ||   ||
  -----------------
3 ||   ||   ||   ||
  -----------------

Your Turn:

Enter your position:
        Row :   ^C
C:\Users\admin\Desktop\Trimester 9\Artificial Intelligence>g++ tic_tac_toe.cpp

C:\Users\admin\Desktop\Trimester 9\Artificial Intelligence>a.exe

 AI's Turn:
    1     2     3
  -----------------
1 || X ||   ||   ||
  -----------------
2 ||   ||   ||   ||
  -----------------
3 ||   ||   ||   ||
  -----------------

Your Turn:
Enter your position:
        Row : 1
        Col : 2
    1     2     3
  -----------------
1 || X || O ||   ||
  -----------------
2 ||   ||   ||   ||
  -----------------
3 ||   ||   ||   ||
  -----------------

 AI's Turn:
    1     2     3
  -----------------
1 || X || O ||   ||
  -----------------
2 || X ||   ||   ||
  -----------------
3 ||   ||   ||   ||
  -----------------

Your Turn:
Enter your position:
        Row : 3
        Col : 1
    1     2     3
  -----------------
1 || X || O ||   ||
  -----------------
2 || X ||   ||   ||
  -----------------
3 || O ||   ||   ||
  -----------------

 AI's Turn:
    1     2     3
  -----------------
1 || X || O ||   ||
  -----------------
2 || X || X ||   ||
  -----------------
3 || O ||   ||   ||
  -----------------

Your Turn:
Enter your position:
        Row : 3
        Col : 3
    1     2     3
  -----------------
1 || X || O ||   ||
  -----------------
2 || X || X ||   ||
  -----------------
3 || O ||   || O ||
  -----------------

AI (X) wins!    
     1     2     3
  -----------------
1 || X || O ||   ||
  -----------------
2 || X || X || X ||
  -----------------
3 || O ||   || O ||
  -----------------
*/