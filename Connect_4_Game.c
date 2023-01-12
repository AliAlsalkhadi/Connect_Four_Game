#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

bool make_move(char board[6][7], int column, char player);

bool check_win(char board[6][7], char player);
bool check_horizontal(char board[6][7], char player, int row, int column);   
bool check_vertical(char board[6][7], char player, int row, int column);    
bool check_diag_up(char board[6][7], char player, int row, int column);
bool check_diag_down(char board[6][7], char player, int row, int column);
bool check_tie(char board[6][7]);
void game_board(char board[6][7]);

char first_capital(const char str[], int n);

void deepest_substring(const char str[], char out[]);

int main(void) {
    
  char Board[6][7] = {"-------",
                      "-------",
                      "-------",
                      "-------",
                      "-------",
                      "-------"};
  printf("Connect 4\n");
  printf("Player X -vs- Player O\n");
  int loop = 1;
  int turn = 0;
  while(loop) {
    char player_T;
    game_board(Board);
    if(turn % 2 == 0) {
      player_T = 'X';
    }
    else {
      player_T = 'O';
    }
    printf("%c it is your turn\n", player_T);
    while(1) {
      printf("Enter a number: ");
      int position;
      char c;
      if(scanf("%d", &position)) {
        bool valid_move = make_move(Board, position-1, player_T);
        if(valid_move == true) {
          break;
        }
        else {
          printf("Invalid Move\n");
        }
      }
    }
    bool Winner = check_win(Board, player_T);
    if(Winner == true) {
      printf("*-----------------*\n");
      game_board(Board);
      printf("Player %c has won\n", player_T);
      loop = 0;
    }
    bool Tie = check_tie(Board);
    if(Tie == true) {
      printf("There is a tie\n");
      game_board(Board);
      loop = 0;
    }
    turn++;
  } 

  char test1[6][7] = {"-------",
                      "-------",
                      "-------",
                      "-------",
                      "----XXX",
                      "X--OOOO"};
  assert(check_win(test1, 'O'));

  char test2[6][7] = {"-------",
                      "-------",
                      "X------",
                      "X-----O",
                      "X-----O",
                      "X-----O"};             
  assert(check_win(test2, 'X'));

  char test3[6][7] = {"-------",
                      "-------",
                      "---O---",
                      "--OX---",
                      "-OXX---",
                      "OXXXO--"};
  assert(check_win(test3, 'O'));

  char test4[6][7] = {"-------",
                      "-------",
                      "X------",
                      "OX-----",
                      "OOX----",
                      "OOOXX--"};
  assert(check_win(test4, 'X'));

  char test5[6][7] = {"-------",
                      "-------",
                      "-------",
                      "X-----O",
                      "X-----O",
                      "X-----O"};
  assert(check_win(test5, 'X') == false);
  assert(check_win(test5, 'O') == false);

  char test6[6][7] = {"OXXOOXX",
                      "OXXOOXX",
                      "OXXOOXX",
                      "XOOXXOO",
                      "XOOXXOO",
                      "XOOXXOO"};
  assert(check_tie(test6) == true);

  assert(first_capital("batMAN", 6) == 'M');
  assert(first_capital("batman", 6) == 0);
  assert(first_capital("BATMAN", 6) == 'B');
  assert(first_capital("batmaN", 6) == 'N');
  assert(first_capital("baTMan", 6) == 'T');
  
  char try1[] = "(a+((b+c)+d)";
  char out1[4] = "";
  deepest_substring(try1, out1);
  assert(strcmp(out1, "b+c") == 0);

  char try2[] = "m+a(c+d)+a+((h+g))";
  char out2[4] = "";
  deepest_substring(try2, out2);
  assert(strcmp(out2, "h+g") == 0);

  char try3[] = "hi()";
  char out3[4] = "";
  deepest_substring(try3, out3);
  assert(strcmp(out3, "") == 0);

  char try4[] = "((a+(a))+b+(+g+(h)))";
  char out4[3] = "";
  deepest_substring(try4, out4);
  assert(strcmp(out4, "a") == 0);

  char try5[] = "hi(how(are(you))doing";
  char out5[4] = "";
  deepest_substring(try5, out5);
  assert(strcmp(out5, "you") == 0);
  
  printf("All tests were successful\n");
}

bool make_move(char board[6][7], int column, char player) {
  if(player == 'X') {
    for(int i=5; i>=0; i--) { 
      if(board[i][column] == '-') {
        board[i][column] = 'X';
        return true;
      }
    }
    }
  else {
    for(int i=5; i>=0; i--) {
      if(board[i][column] == '-') {
        board[i][column] = 'O';
        return true;
      }
    }
  }
  return false;
}

bool check_win(char board[6][7], char player) {
  bool win;
  for(int i=0; i<6; i++) {
    for(int j = 0; j < 7; j++) {
      if(board[i][j] == player) {
        if(i>=0 && i<=2 && j>=0 && j<=6) {
          win = check_vertical(board, player, i, j);
          if(win == true) {
            return true;
          }
        }
        if(i >= 0 && i <= 5 && j >= 0 && j <= 3) {
          win = check_horizontal(board, player, i, j);
          if(win == true) {
            return true;
          }
        }
        if(i>=3 && i<=5 && j>=0 && j<=3) {
          win = check_diag_up(board, player, i, j);
          if(win == true) {
            return true;
          }
        }
        if(i>=0 && i<=2 && j>=0 && j<=3) {
          win = check_diag_down(board, player, i, j);
          if(win == true) {
            return true;
          }
        }
      }
    }
  }
  return false;        
}

bool check_vertical(char board[6][7], char player, int row, int column) {
  if(board[row][column] == player && board[row + 1][column] == player && board[row + 2][column] == player && board[row + 3][column] == player) {
    return true;
  }
  return false;
}

bool check_horizontal(char board[6][7], char player, int row, int column) {
  if(board[row][column] == player && board[row][column + 1] == player && board[row][column + 2] == player && board[row][column + 3] == player) {
    return true;           
  }
  return false;
}

bool check_diag_up(char board[6][7], char player, int row, int column) {
  if(board[row][column] == player && board[row - 1][column + 1] == player && board[row - 2][column + 2] == player && board[row - 3][column + 3] == player) {
    return true;
  }
  return false;
}

bool check_diag_down(char board[6][7], char player, int row, int column) {
  if(board[row][column] == player && board[row + 1][column + 1] == player && board[row + 2][column + 2] == player && board[row + 3][column + 3] == player) {
    return true;
  }
  return false;
}

bool check_tie(char board[6][7]) {
  for(int i = 0; i < 6; i++) {
    for(int j = 0; j < 7; j++) {
      if(board[i][j] == '-') {
        return false;
      }
    }
  }
  return true;
}

void game_board(char board[6][7]) {
  for(int y = 0; y < 6; y ++) {
    printf("%c %c %c %c %c %c %c\n",board[y][0],board[y][1],board[y][2],board[y][3],board[y][4],board[y][5],board[y][6]);
  }
}

char first_capital(const char str[], int n) {
  int lower = 0;
  int upper = n - 1;
  while (lower <= upper) {
    int middle = (lower + upper) / 2;
    if (str[middle] <= 'Z') {
      if (middle == 0) {
        return str[middle];
      } 
      else if (str[middle - 1] > 'Z') {
        return str[middle];
      } 
      else {
        upper = middle - 1;
      }
    } 
    else {
      lower = middle + 1;
    }
  }
  return 0;
}

void deepest_substring(const char str[], char out[]) {
  int max_n = 0;
  int total_n = 0;
  int loc_high_n = 0;
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (str[i] == '(') {
      total_n ++;
      if (max_n < total_n) {
        max_n ++;
        loc_high_n = i;
      }
    } 
    else if (str[i] == ')') {
      total_n --;
    }
  }
  int loop = 1;
  int i = 0;
  while (loop) {
    if (str[loc_high_n + i + 1] != ')') {
      out[i] = str[loc_high_n + i + 1];
    } 
    else {
      loop = 0;
    }
    i ++;
  }
}
