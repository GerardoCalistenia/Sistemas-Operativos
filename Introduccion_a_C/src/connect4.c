#include <stdlib.h>
#include <stdio.h>
#include "connect4.h"
#include <math.h>


void connect4_init(connect4 *game, int rows, int columns, int num_of_players, int win_size)
{

  game->rows = rows;
  game->columns = columns;
  game->num_of_players = num_of_players;
  game->win_size = win_size;


  game->board = (int **)malloc(rows * sizeof(int *));
  for (int i = 0; i < rows; i++)
  {
    game->board[i] = (int *)malloc(columns * sizeof(int));
  }

  /*Initializa el tablero*/
  for (int i = 0; i < game->rows; i++) {
    for (int j = 0; j < game->columns; j++) {
      game->board[i][j] = 0;
    }
  }
}

void connect4_free(connect4 *game)
{
  for (int i = 0; i < game->rows; i++)
  {
    free(game->board[i]);
  }
  free(game->board);
}

char *connect4_to_string(connect4 *game)
{
  /*Sacamos la longitud del tablero*/
  int longitud = game->rows * (game->columns + 1) + 1;
  /*usamos malloc para reservar memoria*/
  char* aux = (char *)malloc(longitud * sizeof(char));
  int puntero = 0;

  for (int i = 0; i < game->rows; i++)
  {
    for (int j = 0; j < game->columns; j++)
    {
      int coordenada = game->board[i][j];
      puntero += sprintf(aux + puntero, "%d", coordenada);
    }
    if (i != game->rows - 1)
    {
      puntero += sprintf(aux + puntero, "\n");
    }
  }
  return aux;
}

int connect4_make_play(connect4 *game, int player, int column)
{

  /*primero checamos que la columna no exceda el limite*/
  if (column < 0 || column >= game->columns)
  {
    return INVALID_COLUMN;
  }
  /*Checamos si el jugador no es valido*/
  if (player <= 0 || player > game->num_of_players)
  {
    return INVALID_PLAYER;
  }

  /*Checamos si la columna aun no se llena*/
  for (int i = game->rows - 1; i >= 0; i--)
  {
    if (game->board[i][column] == 0)
    {
      game->board[i][column] = player;
      if(game-> rows >1){
        return fabs(i - (game->rows - 1));
      }else
        return i;
    }
  }
  return FULL_COLUMN;
}

bool connect4_player_won(connect4 *game, int player, int row, int column){

  int count=0;

  int newRows = fabs( row - (game->rows - 1));

  //Verificar horizontal
  for(int i=0;i< game->columns;i++){
    if( game-> board[newRows][i]==player){
      count++;
      if(count == game->win_size)
        return true;
    }else
      count=0;
  }


  //Verificar vertical
   for(int i=0;i < game->rows;i++){
    if( game-> board[i][column]==player){
      count++;
      if(count == game->win_size)
        return true;      
    }else
      count=0;
  }


  //Verificar Diagonal
  int itRow = game->rows - 1;
  int itColumn = 0;
  for (int i = 0; i < game->rows; ++i){
    if( game -> board[itRow][itColumn]==player){
      count++;
      if(count == game->win_size)
        return true;
    }else
      count=0;
    itRow--;
    itColumn++;
  }
  
  itRow = game->rows - 1;
  itColumn = game -> columns -1;
  for (int i = 0; i < game->rows; ++i){
    if( game -> board[itRow][itColumn]==player){
      count++;
      if(count == game->win_size)
        return true;
    }else
      count=0;
    itRow--;
    itColumn--;
  }
  

  return false;

}


