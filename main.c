#include <stdio.h>
#include <stdlib.h>
// R->Rocks, N->knights, B->bishops, Q->Queen, K->King, P->pawns, w->white pawns, '+':mean white square , and '-' :mean black square.
int whitecheck=0,blackcheck=0,checkmate[1]={0},stealmate[1]={0}, protect[9][9];
int  M[2]={0,0},New[2]={0,0},WKI[2]={0,0}, WKC[1]={0}, BKC[1]={0}, BKI[2]={0,0};
int tempo[1]={0};
int j;

char board[9][9] = {
    {' ','A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
    {'1','R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
    {'2','P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
    {'3','+', '-', '+', '-', '+', '-', '+', '-'},
    {'4','-', '+', '-', '+', '-', '+', '-', '+'},
    {'5','+', '-', '+', '-', '+', '-', '+', '-'},
    {'6','-', '+', '-', '+', '-', '+', '-', '+'},
    {'7','w', 'w', 'w', 'w', 'w', 'w', 'w', 'w'},
    {'8','r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
};

//board to Know white and black squares
char PlusMinus[9][9]={
    {' ','A','B','C','D','E','F','G','H'},
    {'1','+','-','+','-','+','-','+','-'},
    {'2','-','+','-','+','-','+','-','+'},
    {'3','+','-','+','-','+','-','+','-'},
    {'4','-','+','-','+','-','+','-','+'},
    {'5','+','-','+','-','+','-','+','-'},
    {'6','-','+','-','+','-','+','-','+'},
    {'7','+','-','+','-','+','-','+','-'},
    {'8','-','+','-','+','-','+','-','+'},
};
char board1[9][9];
int validity[9][9],validity2[9][9],validity3[9][9],validitytemp[9][9];
int check[9][9];
void intializeValidity (int v[9][9]);
void printBoard (char c[9][9]);
void printBoardint (int c[9][9]);
int TurnToIndex(char a);
void GetMove(char a[9][9],int j);
void GetValidMove(char a[9][9],int a1[9][9] );
void Blackpromotion (char a[9][9],int N[2]);
void whitepromotion (char a[9][9],int N[2]);
void WhitePawnMoves (char a[9][9],int temp);
void BlackPawnMoves (char a[9][9],int temp);
void WhiteKnightMoves(char a[9][9],int temp);
void BlackKnightMoves(char a[9][9],int temp);
void WhiteRookMoves(char a[9][9],int temp);
void BlackRookMoves(char a[9][9],int temp);
void WhiteBishopMoves(char a[9][9],int temp);
void BlackBishopMoves(char a[9][9],int temp);
void WhiteQueenMoves(char a[9][9],int temp);
void BlackQueenMoves(char a[9][9],int temp);
void WhiteKingMoves(char a[9][9],int temp);
void BlackKingMoves(char a[9][9],int temp);
void Moves (char a[9][9]);
void getwhitekingindex(char a[9][9],int b[2]);
void getblackkingindex(char a[9][9],int b[2]);
void allwhitecheck(char a[9][9]);
void Instructions (int n);
void allblackcheck(char a[9][9]);
void ProtectionWhite (char a[9][9]);
void ProtectionBlack (char a[9][9]);
void FinalProtection();
void WhiteCheckMate(char a[9][9]);
void BlackCheckMate(char a[9][9]);
void SMove(int m,int n,int l,int k);
void equaling();
void WhiteCheckMove();
void BlackCheckMove();
void equalingint(int a1[9][9],int a2[9][9]);
void WhitestealkMove();
void BlackstealMove();
void CheckWhiteKingProtection(int i,int j,int r,int c);
void CheckBlackKingProtection(int i,int j,int r,int c);

//The main function which include the other functions.
int main()
{
    char n;
    printf("Enter the number for the task\n1- Instructions.\n2- Play.\n3- Exit.\n");
    scanf("%c",&n);
    while(n!='1'&&n!='2'&&n!='3'){printf("Enter valid number:\n");scanf("%c",&n);}
    if (n=='1'){Instructions(n);}
    else if (n=='2'){
        while(checkmate[0]!=1){
            printBoard(board);
            printf("white turn:\n");
            j = 1;
            ProtectionBlack(board);
            allwhitecheck(board);
            FinalProtection();
            WhiteCheckMate(board);
            if (WKC[0]==1){
                WhiteCheckMove();

                if (checkmate[0]==1){printf("The Black Pieces Player Win\n"); return 0;}
                else {ProtectionBlack(board);allwhitecheck(board);FinalProtection();GetMove(board,1);
                while(validity2[M[0]][M[1]]==0){
                    printf("The King is checked You have to protect him\n");
                    GetMove(board,1);}
                Moves(board);}}
            else {
                WhitestealkMove();
                if (stealmate[0]== 1){printf("The Game Ended by StealMate\n");return 0;}
;           ProtectionBlack(board);allwhitecheck(board);FinalProtection();
            GetMove(board,1);Moves(board);while(tempo[0]==1){ProtectionBlack(board);allwhitecheck(board);FinalProtection();GetMove(board,1);Moves(board);}}
            printf("black turn:\n");
            j = 0;
            ProtectionWhite(board);
            allblackcheck(board);
            FinalProtection();
            BlackCheckMate(board);
            if (BKC[0]==1){
                BlackCheckMove();
                if (checkmate[0]==1){printf("The White Pieces Player Win\n"); return 0;}
                else {ProtectionWhite(board);allblackcheck(board);FinalProtection();GetMove(board,0);
                while(validity2[M[0]][M[1]]==0){
                    printf("The King is checked You have to protect him\n");
                    GetMove(board,0);}
                Moves(board);}}
            else {
                BlackstealMove();
                if (stealmate[0]== 1){printf("The Game Ended by StealMate\n");return 0;}
;               ProtectionWhite(board);allblackcheck(board);FinalProtection();
                GetMove(board,0);Moves(board);while(tempo[0]==1){ProtectionWhite(board);allblackcheck(board);FinalProtection();GetMove(board,0);Moves(board);}}
        }
    }
    else if (n=='3'){return 0;}
    return 0;}

//intialize The validity to Zero.
void intializeValidity (int v[9][9]){
int i, j;
 for (i=0;i<9;i++){
    for(j=0;j<9;j++){
        v[i][j]=0;}}}

//function Printing the board.
void printBoard (char c[9][9]){
    int i,j;
    printf("\n");
    for(j=0;j<9;j++){
        printf("%c   ",c[0][j]);}
printf("\n\n\n");
 for (i=1;i<9;i++){
    for (j=0;j<9;j++){
        printf("%c   ",c[i][j]);
    }
    printf("\n\n"); }}

//Function equaling two integer boards.
void equalingint(int a1[9][9],int a2[9][9])
{
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){a1[i][j]=a2[i][j];}
    }
}

//Function equaling two boards.
void equaling(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
           board1[i][j]=board[i][j];}}}

//function turn the user input into index in the board.
int TurnToIndex(char a)
{
    int m=0;
    if(a == '1'){m = 1;}
    else if(a == '2'){m = 2;}
    else if(a == '3'){m = 3;}
    else if(a == '4'){m = 4;}
    else if(a == '5'){m = 5;}
    else if(a == '6'){m = 6;}
    else if(a == '7'){m = 7;}
    else if(a == '8'){m = 8;}
    else if(a == 'a'){m = 1;}
    else if(a == 'b'){m = 2;}
    else if(a == 'c'){m = 3;}
    else if(a == 'd'){m = 4;}
    else if(a == 'e'){m = 5;}
    else if(a == 'f'){m = 6;}
    else if(a == 'g'){m = 7;}
    else if(a == 'h'){m = 8;}
    return m;}

//function take user input and check if it valid index or not, and if he has piece in this index or not.
void GetMove(char a[9][9],int j)
{
    int r,c;
    char row  ,column;
    printf("insert row number, then press enter, then insert column character small :\n");
    scanf(" %c",&row);
    while(row!='1'&&row!='2'&&row!='3'&&row!='4'&&row!='5'&&row!='6'&&row!='7'&&row!='8'){
        printf("wrong row index please re-enter:\n");scanf("%c",&row);
    }
    scanf(" %c",&column);
    while(column!='a'&&column!='b'&&column!='c'&&column!='d'&&column!='e'&&column!='f'&&column!='g'&&column!='h'){
        printf("wrong column index please re-enter:\n");scanf("%c",&column);
    }
    r=TurnToIndex(row);
    c=TurnToIndex(column);
    if (j==1){
        if(a[r][c] =='-'||a[r][c] =='+'||a[r][c] =='R'||a[r][c] =='N'||a[r][c] =='B'||a[r][c] =='Q'||a[r][c] =='K'||a[r][c] =='P'){
         printf("There is no Pieces for you in this square\nre-enter your piece index.\n");
         GetMove(board,j);}else{M[0]=r; M[1]=c;}
   }
   else if(j==0){
       if(a[r][c] =='-'||a[r][c] =='+'||a[r][c] =='r'||a[r][c] =='n'||a[r][c] =='b'||a[r][c] =='q'||a[r][c] =='k'||a[r][c] =='w'){
        printf("There is no Pieces for you in this square\nre-enter your piece index.\n");
        GetMove(board,j);}else{M[0]=r; M[1]=c;}
   }}

//function take the move index and check if it valid or not.
void GetValidMove(char a[9][9],int a1[9][9] )
{
    int r=M[0];
    int c=M[1];
    equalingint(validitytemp,a1);
    int r1,c1;
    char row  ,column;
    printf("insert row number, then press enter, then insert column character small :\n");
    scanf(" %c",&row);
    while(row!='1'&&row!='2'&&row!='3'&&row!='4'&&row!='5'&&row!='6'&&row!='7'&&row!='8'){
        printf("wrong row index please re-enter:\n");scanf("%c",&row);}
    scanf(" %c",&column);
    while(column!='a'&&column!='b'&&column!='c'&&column!='d'&&column!='e'&&column!='f'&&column!='g'&&column!='h'){
        printf("wrong column index please re-enter:\n");scanf("%c",&column);}
    r1=TurnToIndex(row);
    c1=TurnToIndex(column);
    if (WKC[0]==1 || BKC[0]==1){
        if (a[M[0]][M[1]]=='k'||a[M[0]][M[1]]=='K'){
            while ((validity3[r1][c1]!=1&&validity3[r1][c1]!=2)&&validity[r1][c1]==1){
                    printf("Invalid !!\n");
                    printf("insert row number, then press enter, then insert column character small :\n");
    scanf(" %c",&row);
    while(row!='1'&&row!='2'&&row!='3'&&row!='4'&&row!='5'&&row!='6'&&row!='7'&&row!='8'){
        printf("wrong row index please re-enter:\n");scanf("%c",&row);}
    scanf(" %c",&column);
    while(column!='a'&&column!='b'&&column!='c'&&column!='d'&&column!='e'&&column!='f'&&column!='g'&&column!='h'){
        printf("wrong column index please re-enter:\n");scanf("%c",&column);}
    r1=TurnToIndex(row);
    c1=TurnToIndex(column);
            }}
            else {
                while(validity3[r1][c1]!=1 && validity[r1][c1]==1){
                        printf("Invalid !!\n");
                        printf("insert row number, then press enter, then insert column character small :\n");
    scanf(" %c",&row);
    while(row!='1'&&row!='2'&&row!='3'&&row!='4'&&row!='5'&&row!='6'&&row!='7'&&row!='8'){
        printf("wrong row index please re-enter:\n");scanf("%c",&row);}
    scanf(" %c",&column);
    while(column!='a'&&column!='b'&&column!='c'&&column!='d'&&column!='e'&&column!='f'&&column!='g'&&column!='h'){
        printf("wrong column index please re-enter:\n");scanf("%c",&column);}
    r1=TurnToIndex(row);
    c1=TurnToIndex(column);
    }}}
    if ((a[r][c]=='w'||a[r][c]=='r'||a[r][c]=='n'||a[r][c]=='b'||a[r][c]=='q')&&WKC[0]==0){
        CheckWhiteKingProtection(r1,c1,r,c);if(tempo[0]==1){return;}}
    if ((a[r][c]=='P'||a[r][c]=='R'||a[r][c]=='N'||a[r][c]=='B'||a[r][c]=='Q')&&BKC[0]==0){
        CheckBlackKingProtection(r1,c1,r,c);if(tempo[0]==1){return;}}
    if(validitytemp[r1][c1] != 1){printf("invalid move re-enter piece index:\n");if(j==1){ProtectionBlack(a);allwhitecheck(a);FinalProtection();}else{ProtectionWhite(a);allblackcheck(a);FinalProtection();}GetMove(a,j);Moves(a);}
    else{a[r1][c1]=a[r][c];a[r][c]=PlusMinus[r][c];
    New[0]=r1;New[1]=c1;printBoard(a);return;}}

//Function for Black pawn promotion.
void Blackpromotion (char a[9][9],int N[2]){
 char p;
 printf("Choose one of 'R, N, B, Q'.");
 scanf(" %c", &p);
 if (p=='R'||p=='N'||p=='B'||p=='Q'){a[N[0]][N[1]]=p;printBoard(a);}
 else{printf("This Promotion is invalid .\nre-enter you propmotion\n");
 Blackpromotion (a,N);}}

//Function for white pawn promotion.
void whitepromotion (char a[9][9],int N[2]){
 char p;
 printf("Choose one of 'r,n,b,q'");
 scanf(" %c", &p);
 if (p=='r'||p=='n'||p=='b'||p=='q'){a[N[0]][N[1]]=p;printBoard(a);}
 else{printf("This Promotion is invalid .\nre-enter you propmotion\n");
 whitepromotion(a,N);}}

//Function to get valid white pawns moves.
void WhitePawnMoves(char a[9][9],int temp){
intializeValidity(validity);
int r, c,V;
r=M[0];
c=M[1];
if (r==7 && (a[r-1][c]=='+'||a[r-1][c]=='-')){V=99;validity[r-1][c]=1; if(a[r-2][c]=='+'||a[r-2][c]=='-'){validity[r-2][c]=1; }}
if((a[r-1][c]=='+'||a[r-1][c]=='-')&&r!=7){V=99;validity[r-1][c]=1;}
if(a[r-1][c-1]=='P'||a[r-1][c-1]=='B'||a[r-1][c-1]=='N'||a[r-1][c-1]=='R'||a[r-1][c-1]=='Q'||a[r-1][c-1]=='K'){V=99;check[r-1][c-1]=1;validity[r-1][c-1]=1;}
if(a[r-1][c+1]=='P'||a[r-1][c+1]=='B'||a[r-1][c+1]=='N'||a[r-1][c+1]=='R'||a[r-1][c+1]=='Q'||a[r-1][c+1]=='K'){V=99;check[r-1][c+1]=1;validity[r-1][c+1]=1;}
if(temp == 0){if(a[r-1][c-1]=='+'||a[r-1][c-1]=='-'){check[r-1][c-1]=1;}if(a[r-1][c+1]=='+'||a[r-1][c+1]=='-'){check[r-1][c+1]=1;}return;}
if (V==99){GetValidMove(a,validity );if (New[0]==1){whitepromotion(a,New);}}
else {printf("There is no Moves for this pawn.\nEnter another piece index.\n");
GetMove(a,1);
Moves(a);}}

//Function to get valid Black pawns moves.
void BlackPawnMoves (char a[9][9],int temp) {
intializeValidity(validity);
int r,c,V=0;
r=M[0];
c=M[1];
if (r==2 && (a[r+1][c]=='+'||a[r+1][c]=='-')){V=99;validity[r+1][c]=1; if(a[r+2][c]=='+'||a[r+2][c]=='-'){validity[r+2][c]=1; }}
if((a[r+1][c]=='+'||a[r+1][c]=='-')&&r!=2){V=99;validity[r+1][c]=1;}
if(a[r+1][c-1]=='w'||a[r+1][c-1]=='b'||a[r+1][c-1]=='n'||a[r+1][c-1]=='r'||a[r+1][c-1]=='q'||a[r+1][c-1]=='k'){V=99;check[r+1][c-1]=1;validity[r+1][c-1]=1;}
if(a[r+1][c+1]=='w'||a[r+1][c+1]=='b'||a[r+1][c+1]=='n'||a[r+1][c+1]=='r'||a[r+1][c+1]=='q'||a[r+1][c+1]=='k'){V=99;check[r+1][c+1]=1;validity[r+1][c+1]=1;}
if(temp == 0){if(a[r+1][c-1]=='+'||a[r+1][c-1]=='-'){check[r+1][c-1]=1;}if(a[r+1][c+1]=='+'||a[r+1][c+1]=='-'){check[r+1][c+1]=1;}return;}
if (V==99){GetValidMove(a,validity );if (New[0]==8){Blackpromotion(a,New);}}
else {printf("There is no Moves for this pawn.\nEnter another piece index.\n");
GetMove(a,0);
Moves(a);}}

//Function to get valid White Knights moves.
void WhiteKnightMoves(char a[9][9],int temp){
    intializeValidity(validity);
    int r,c,v=0;
    r=M[0];c=M[1];
    if((r+2<9)&&(c-1>0)&&(a[r+2][c-1]=='+'||a[r+2][c-1]=='-'||a[r+2][c-1]=='P'||a[r+2][c-1]=='B'||a[r+2][c-1]=='N'||a[r+2][c-1]=='Q'||a[r+2][c-1]=='R'||a[r+2][c-1]=='K')){v=100;check[r+2][c-1]=1;validity[r+2][c-1]=1;}
    if((r+2<9)&&(c+1<9)&&(a[r+2][c+1]=='+'||a[r+2][c+1]=='-'||a[r+2][c+1]=='P'||a[r+2][c+1]=='B'||a[r+2][c+1]=='N'||a[r+2][c+1]=='Q'||a[r+2][c+1]=='R'||a[r+2][c+1]=='K')){v=100;check[r+2][c+1]=1;validity[r+2][c+1]=1;}
    if((r-2>0)&&(c-1>0)&&(a[r-2][c-1]=='+'||a[r-2][c-1]=='-'||a[r-2][c-1]=='P'||a[r-2][c-1]=='B'||a[r-2][c-1]=='N'||a[r-2][c-1]=='Q'||a[r-2][c-1]=='R'||a[r-2][c-1]=='K')){v=100;check[r-2][c-1]=1;validity[r-2][c-1]=1;}
    if((r-2>0)&&(c+1<9)&&(a[r-2][c+1]=='+'||a[r-2][c+1]=='-'||a[r-2][c+1]=='P'||a[r-2][c+1]=='B'||a[r-2][c+1]=='N'||a[r-2][c+1]=='Q'||a[r-2][c+1]=='R'||a[r-2][c+1]=='K')){v=100;check[r-2][c+1]=1;validity[r-2][c+1]=1;}
    if((r-1>0)&&(c+2<9)&&(a[r-1][c+2]=='+'||a[r-1][c+2]=='-'||a[r-1][c+2]=='P'||a[r-1][c+2]=='B'||a[r-1][c+2]=='N'||a[r-1][c+2]=='Q'||a[r-1][c+2]=='R'||a[r-1][c+2]=='K')){v=100;check[r-1][c+2]=1;validity[r-1][c+2]=1;}
    if((r+1<9)&&(c+2<9)&&(a[r+1][c+2]=='+'||a[r+1][c+2]=='-'||a[r+1][c+2]=='P'||a[r+1][c+2]=='B'||a[r+1][c+2]=='N'||a[r+1][c+2]=='Q'||a[r+1][c+2]=='R'||a[r+1][c+2]=='K')){v=100;check[r+1][c+2]=1;validity[r+1][c+2]=1;}
    if((r-1>0)&&(c-2>0)&&(a[r-1][c-2]=='+'||a[r-1][c-2]=='-'||a[r-1][c-2]=='P'||a[r-1][c-2]=='B'||a[r-1][c-2]=='N'||a[r-1][c-2]=='Q'||a[r-1][c-2]=='R'||a[r-1][c-2]=='K')){v=100;check[r-1][c-2]=1;validity[r-1][c-2]=1;}
    if((r+1<9)&&(c-2>0)&&(a[r+1][c-2]=='+'||a[r+1][c-2]=='-'||a[r+1][c-2]=='P'||a[r+1][c-2]=='B'||a[r+1][c-2]=='N'||a[r+1][c-2]=='Q'||a[r+1][c-2]=='R'||a[r+1][c-2]=='K')){v=100;check[r+1][c-2]=1;validity[r+1][c-2]=1;}
    if(temp == 0){return;}
    if (v==100){GetValidMove(a,validity );}
    else {printf("There is no Moves for this knight.\nEnter another piece index.\n");
    GetMove(a,1);
    Moves(a);}}

//Function to get valid Black Knights moves.
void BlackKnightMoves(char a[9][9],int temp){
    intializeValidity(validity);
    int r,c,v=0;
    r=M[0];c=M[1];
    if((r+2<9)&&(c-1>0)&&(a[r+2][c-1]=='+'||a[r+2][c-1]=='-'||a[r+2][c-1]=='w'||a[r+2][c-1]=='b'||a[r+2][c-1]=='n'||a[r+2][c-1]=='q'||a[r+2][c-1]=='r'||a[r+2][c-1]=='k')){v=100;check[r+2][c-1]=1;validity[r+2][c-1]=1;}
    if((r+2<9)&&(c+1<9)&&(a[r+2][c+1]=='+'||a[r+2][c+1]=='-'||a[r+2][c+1]=='w'||a[r+2][c+1]=='b'||a[r+2][c+1]=='n'||a[r+2][c+1]=='q'||a[r+2][c+1]=='r'||a[r+2][c+1]=='k')){v=100;check[r+2][c+1]=1;validity[r+2][c+1]=1;}
    if((r-2>0)&&(c-1>0)&&(a[r-2][c-1]=='+'||a[r-2][c-1]=='-'||a[r-2][c-1]=='w'||a[r-2][c-1]=='b'||a[r-2][c-1]=='n'||a[r-2][c-1]=='q'||a[r-2][c-1]=='r'||a[r-2][c-1]=='k')){v=100;check[r-2][c-1]=1;validity[r-2][c-1]=1;}
    if((r-2>0)&&(c+1<9)&&(a[r-2][c+1]=='+'||a[r-2][c+1]=='-'||a[r-2][c+1]=='w'||a[r-2][c+1]=='b'||a[r-2][c+1]=='n'||a[r-2][c+1]=='q'||a[r-2][c+1]=='r'||a[r-2][c+1]=='k')){v=100;check[r-2][c+1]=1;validity[r-2][c+1]=1;}
    if((r-1>0)&&(c+2<9)&&(a[r-1][c+2]=='+'||a[r-1][c+2]=='-'||a[r-1][c+2]=='w'||a[r-1][c+2]=='b'||a[r-1][c+2]=='n'||a[r-1][c+2]=='q'||a[r-1][c+2]=='r'||a[r-1][c+2]=='k')){v=100;check[r-1][c+2]=1;validity[r-1][c+2]=1;}
    if((r+1<9)&&(c+2<9)&&(a[r+1][c+2]=='+'||a[r+1][c+2]=='-'||a[r+1][c+2]=='w'||a[r+1][c+2]=='b'||a[r+1][c+2]=='n'||a[r+1][c+2]=='q'||a[r+1][c+2]=='r'||a[r+1][c+2]=='k')){v=100;check[r+1][c+2]=1;validity[r+1][c+2]=1;}
    if((r-1>0)&&(c-2>0)&&(a[r-1][c-2]=='+'||a[r-1][c-2]=='-'||a[r-1][c-2]=='w'||a[r-1][c-2]=='b'||a[r-1][c-2]=='n'||a[r-1][c-2]=='q'||a[r-1][c-2]=='r'||a[r-1][c-2]=='k')){v=100;check[r-1][c-2]=1;validity[r-1][c-2]=1;}
    if((r+1<9)&&(c-2>0)&&(a[r+1][c-2]=='+'||a[r+1][c-2]=='-'||a[r+1][c-2]=='w'||a[r+1][c-2]=='b'||a[r+1][c-2]=='n'||a[r+1][c-2]=='q'||a[r+1][c-2]=='r'||a[r+1][c-2]=='k')){v=100;check[r+1][c-2]=1;validity[r+1][c-2]=1;}
    if(temp == 0){return;}
    if (v==100){GetValidMove(a,validity );}
    else {printf("There is no Moves for this knight.\nEnter another piece index.\n");
    GetMove(a,0);
    Moves(a);}}

//Function to get valid white Rook moves.
void WhiteRookMoves(char a[9][9],int temp)
{
    intializeValidity(validity);
    int r,c,v=0;
    r=M[0];c=M[1];
    for(int i=1;i<8;i++){
        if((r<9)&&(c+i<9)&&(a[r][c+i]=='+'||a[r][c+i]=='-'||a[r][c+i]=='P'||a[r][c+i]=='N'||a[r][c+i]=='B'||a[r][c+i]=='Q'||a[r][c+i]=='R'||a[r][c+i]=='K')){
            v=100;check[r][c+i]=1;validity[r][c+i]=1;}
        if(a[r][c+i]!='+'&&a[r][c+i]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r<9)&&(c-i>0)&&(a[r][c-i]=='+'||a[r][c-i]=='-'||a[r][c-i]=='P'||a[r][c-i]=='N'||a[r][c-i]=='B'||a[r][c-i]=='Q'||a[r][c-i]=='R'||a[r][c-i]=='K')){
            v=100;check[r][c-i]=1;validity[r][c-i]=1;}
        if(a[r][c-i]!='+'&&a[r][c-i]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r+i<9)&&(c<9)&&(a[r+i][c]=='+'||a[r+i][c]=='-'||a[r+i][c]=='P'||a[r+i][c]=='N'||a[r+i][c]=='B'||a[r+i][c]=='Q'||a[r+i][c]=='R'||a[r+i][c]=='K')){
            v=100;check[r+i][c]=1;validity[r+i][c]=1;}
        if(a[r+i][c]!='+'&&a[r+i][c]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r-i>0)&&(c>0)&&(a[r-i][c]=='+'||a[r-i][c]=='-'||a[r-i][c]=='P'||a[r-i][c]=='N'||a[r-i][c]=='B'||a[r-i][c]=='Q'||a[r-i][c]=='R'||a[r-i][c]=='K')){
            v=100;check[r-i][c]=1;validity[r-i][c]=1;}
        if(a[r-i][c]!='+'&&a[r-i][c]!='-'){break;}
    }
    if(temp == 0){return;}
    if (v==100){GetValidMove(a,validity);}
    else {printf("There is no Moves for this rook.\nEnter another piece index.\n");
    GetMove(a,1);
    Moves(a);}}

//Function to get valid Black Rook moves.
void BlackRookMoves(char a[9][9],int temp){
    intializeValidity(validity);
    int r,c,v=0;
    r=M[0];c=M[1];
    for(int i=1;i<8;i++){
        if((r<9)&&(c+i<9)&&(a[r][c+i]=='+'||a[r][c+i]=='-'||a[r][c+i]=='w'||a[r][c+i]=='n'||a[r][c+i]=='b'||a[r][c+i]=='q'||a[r][c+i]=='r'||a[r][c+i]=='k')){
            v=100;check[r][c+i]=1;validity[r][c+i]=1;}
        if(a[r][c+i]!='+'&&a[r][c+i]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r<9)&&(c-i>0)&&(a[r][c-i]=='+'||a[r][c-i]=='-'||a[r][c-i]=='w'||a[r][c-i]=='n'||a[r][c-i]=='b'||a[r][c-i]=='q'||a[r][c-i]=='r'||a[r][c-i]=='k')){
            v=100;check[r][c-i]=1;validity[r][c-i]=1;}
        if(a[r][c-i]!='+'&&a[r][c-i]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r+i<9)&&(c<9)&&(a[r+i][c]=='+'||a[r+i][c]=='-'||a[r+i][c]=='w'||a[r+i][c]=='n'||a[r+i][c]=='b'||a[r+i][c]=='q'||a[r+i][c]=='r'||a[r+i][c]=='k')){
            v=100;check[r+i][c]=1;validity[r+i][c]=1;}
        if(a[r+i][c]!='+'&&a[r+i][c]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r-i>0)&&(c>0)&&(a[r-i][c]=='+'||a[r-i][c]=='-'||a[r-i][c]=='w'||a[r-i][c]=='n'||a[r-i][c]=='b'||a[r-i][c]=='q'||a[r-i][c]=='r'||a[r-i][c]=='k')){
            v=100;check[r-i][c]=1;validity[r-i][c]=1;}
        if(a[r-i][c]!='+'&&a[r-i][c]!='-'){break;}
    }
    if(temp == 0){return;}
    if (v==100){GetValidMove(a,validity );}
    else {printf("There is no Moves for this rook.\nEnter another piece index.\n");
    GetMove(a,0);
    Moves(a);}}

//Function to get valid white Bishop moves.
void WhiteBishopMoves(char a[9][9],int temp){
    intializeValidity(validity);
    int r,c,v=0;
    r=M[0];c=M[1];
    for(int i=1;i<8;i++){
        if((r-i>0)&&(c+i<9)&&(a[r-i][c+i]=='+'||a[r-i][c+i]=='-'||a[r-i][c+i]=='P'||a[r-i][c+i]=='Q'||a[r-i][c+i]=='R'||a[r-i][c+i]=='N'||a[r-i][c+i]=='B'||a[r-i][c+i]=='K')){
            v=100;check[r-i][c+i]=1;validity[r-i][c+i]=1;}
        if(a[r-i][c+i]!='+'&&a[r-i][c+i]!='-'){break;}
    }
     for(int i=1;i<8;i++){
        if((r-i>0)&&(c-i<9)&&(a[r-i][c-i]=='+'||a[r-i][c-i]=='-'||a[r-i][c-i]=='P'||a[r-i][c-i]=='Q'||a[r-i][c-i]=='R'||a[r-i][c-i]=='N'||a[r-i][c-i]=='B'||a[r-i][c-i]=='K')){
            v=100;check[r-i][c-i]=1;validity[r-i][c-i]=1;}
        if(a[r-i][c-i]!='+'&&a[r-i][c-i]!='-'){break;}
    }
     for(int i=1;i<8;i++){
        if((r+i>0)&&(c+i<9)&&(a[r+i][c+i]=='+'||a[r+i][c+i]=='-'||a[r+i][c+i]=='P'||a[r+i][c+i]=='Q'||a[r+i][c+i]=='R'||a[r+i][c+i]=='N'||a[r+i][c+i]=='B'||a[r+i][c+i]=='K')){
            v=100;check[r+i][c+i]=1;validity[r+i][c+i]=1;}
        if(a[r+i][c+i]!='+'&&a[r+i][c+i]!='-'){break;}
    }
     for(int i=1;i<8;i++){
        if((r+i<9)&&(c-i>0)&&(a[r+i][c-i]=='+'||a[r+i][c-i]=='-'||a[r+i][c-i]=='P'||a[r+i][c-i]=='Q'||a[r+i][c-i]=='R'||a[r+i][c-i]=='N'||a[r+i][c-i]=='B'||a[r+i][c-i]=='K')){
            v=100;check[r+i][c-i]=1;validity[r+i][c-i]=1;}
        if(a[r+i][c-i]!='+'&&a[r+i][c-i]!='-'){break;}
    }
    if(temp == 0){return;}
    if (v==100){GetValidMove(a,validity );}
    else {printf("There is no Moves for this bishop.\nEnter another piece index.\n");
    GetMove(a,1);
    Moves(a);}}

//Function to get valid Black Bishop moves.
void BlackBishopMoves(char a[9][9],int temp){
    intializeValidity(validity);
    int r,c,v=0;
    r=M[0];c=M[1];
    for(int i=1;i<8;i++){
        if((r-i>0)&&(c+i<9)&&(a[r-i][c+i]=='+'||a[r-i][c+i]=='-'||a[r-i][c+i]=='w'||a[r-i][c+i]=='q'||a[r-i][c+i]=='r'||a[r-i][c+i]=='n'||a[r-i][c+i]=='b'||a[r-i][c+i]=='k')){
            v=100;check[r-i][c+i]=1;validity[r-i][c+i]=1;}
        if(a[r-i][c+i]!='+'&&a[r-i][c+i]!='-'){break;}
    }
     for(int i=1;i<8;i++){
        if((r-i>0)&&(c-i<9)&&(a[r-i][c-i]=='+'||a[r-i][c-i]=='-'||a[r-i][c-i]=='w'||a[r-i][c-i]=='q'||a[r-i][c-i]=='r'||a[r-i][c-i]=='n'||a[r-i][c-i]=='b'||a[r-i][c-i]=='k')){
            v=100;check[r-i][c-i]=1;validity[r-i][c-i]=1;}
        if(a[r-i][c-i]!='+'&&a[r-i][c-i]!='-'){break;}
    }
     for(int i=1;i<8;i++){
        if((r+i>0)&&(c+i<9)&&(a[r+i][c+i]=='+'||a[r+i][c+i]=='-'||a[r+i][c+i]=='w'||a[r+i][c+i]=='q'||a[r+i][c+i]=='r'||a[r+i][c+i]=='n'||a[r+i][c+i]=='b'||a[r+i][c+i]=='k')){
            v=100;check[r+i][c+i]=1;validity[r+i][c+i]=1;}
        if(a[r+i][c+i]!='+'&&a[r+i][c+i]!='-'){break;}
    }
     for(int i=1;i<8;i++){
        if((r+i<9)&&(c-i>0)&&(a[r+i][c-i]=='+'||a[r+i][c-i]=='-'||a[r+i][c-i]=='w'||a[r+i][c-i]=='q'||a[r+i][c-i]=='r'||a[r+i][c-i]=='n'||a[r+i][c-i]=='b'||a[r+i][c-i]=='k')){
            v=100;check[r+i][c-i]=1;validity[r+i][c-i]=1;}
        if(a[r+i][c-i]!='+'&&a[r+i][c-i]!='-'){break;}
    }
    if(temp == 0){return;}
    if (v==100){GetValidMove(a,validity );}
    else {printf("There is no Moves for this bishop.\nEnter another piece index.\n");
    GetMove(a,0);
    Moves(a);}}

//Function to get valid White Queen moves.
void WhiteQueenMoves(char a[9][9],int temp){
    intializeValidity(validity);
    int r,c,v=0;
    r=M[0];c=M[1];
    for(int i=1;i<8;i++){
        if((r<9)&&(c+i<9)&&(a[r][c+i]=='+'||a[r][c+i]=='-'||a[r][c+i]=='P'||a[r][c+i]=='N'||a[r][c+i]=='B'||a[r][c+i]=='Q'||a[r][c+i]=='R'||a[r][c+i]=='K')){
            v=100;check[r][c+i]=1;validity[r][c+i]=1;}
        if(a[r][c+i]!='+'&&a[r][c+i]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r<9)&&(c-i>0)&&(a[r][c-i]=='+'||a[r][c-i]=='-'||a[r][c-i]=='P'||a[r][c-i]=='N'||a[r][c-i]=='B'||a[r][c-i]=='Q'||a[r][c-i]=='R'||a[r][c-i]=='K')){
            v=100;check[r][c-i]=1;validity[r][c-i]=1;}
        if(a[r][c-i]!='+'&&a[r][c-i]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r+i<9)&&(c<9)&&(a[r+i][c]=='+'||a[r+i][c]=='-'||a[r+i][c]=='P'||a[r+i][c]=='N'||a[r+i][c]=='B'||a[r+i][c]=='Q'||a[r+i][c]=='R'||a[r+i][c]=='K')){
            v=100;check[r+i][c]=1;validity[r+i][c]=1;}
        if(a[r+i][c]!='+'&&a[r+i][c]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r-i>0)&&(c>0)&&(a[r-i][c]=='+'||a[r-i][c]=='-'||a[r-i][c]=='P'||a[r-i][c]=='N'||a[r-i][c]=='B'||a[r-i][c]=='Q'||a[r-i][c]=='R'||a[r-i][c]=='K')){
            v=100;check[r-i][c]=1;validity[r-i][c]=1;}
        if(a[r-i][c]!='+'&&a[r-i][c]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r-i>0)&&(c+i<9)&&(a[r-i][c+i]=='+'||a[r-i][c+i]=='-'||a[r-i][c+i]=='P'||a[r-i][c+i]=='Q'||a[r-i][c+i]=='R'||a[r-i][c+i]=='N'||a[r-i][c+i]=='B'||a[r-i][c+i]=='K')){
            v=100;check[r-i][c+i]=1;validity[r-i][c+i]=1;}
        if(a[r-i][c+i]!='+'&&a[r-i][c+i]!='-'){break;}
    }
     for(int i=1;i<8;i++){
        if((r-i>0)&&(c-i<9)&&(a[r-i][c-i]=='+'||a[r-i][c-i]=='-'||a[r-i][c-i]=='P'||a[r-i][c-i]=='Q'||a[r-i][c-i]=='R'||a[r-i][c-i]=='N'||a[r-i][c-i]=='B'||a[r-i][c-i]=='K')){
            v=100;check[r-i][c-i]=1;validity[r-i][c-i]=1;}
        if(a[r-i][c-i]!='+'&&a[r-i][c-i]!='-'){break;}
    }
     for(int i=1;i<8;i++){
        if((r+i>0)&&(c+i<9)&&(a[r+i][c+i]=='+'||a[r+i][c+i]=='-'||a[r+i][c+i]=='P'||a[r+i][c+i]=='Q'||a[r+i][c+i]=='R'||a[r+i][c+i]=='N'||a[r+i][c+i]=='B'||a[r+i][c+i]=='K')){
            v=100;check[r+i][c+i]=1;validity[r+i][c+i]=1;}
        if(a[r+i][c+i]!='+'&&a[r+i][c+i]!='-'){break;}
    }
     for(int i=1;i<8;i++){
        if((r+i<9)&&(c-i>0)&&(a[r+i][c-i]=='+'||a[r+i][c-i]=='-'||a[r+i][c-i]=='P'||a[r+i][c-i]=='Q'||a[r+i][c-i]=='R'||a[r+i][c-i]=='N'||a[r+i][c-i]=='B'||a[r+i][c-i]=='K')){
            v=100;check[r+i][c-i]=1;validity[r+i][c-i]=1;}
        if(a[r+i][c-i]!='+'&&a[r+i][c-i]!='-'){break;}
    }
    if(temp == 0){return;}
    if (v==100){GetValidMove(a,validity );}
    else {printf("There is no Moves for this queen.\nEnter another piece index.\n");
    GetMove(a,1);
    Moves(a);}}

//Function to get valid Black Queen moves.
void BlackQueenMoves(char a[9][9],int temp){
    intializeValidity(validity);
    int r,c,v=0;
    r=M[0];c=M[1];
    for(int i=1;i<8;i++){
        if((r<9)&&(c+i<9)&&(a[r][c+i]=='+'||a[r][c+i]=='-'||a[r][c+i]=='w'||a[r][c+i]=='n'||a[r][c+i]=='b'||a[r][c+i]=='q'||a[r][c+i]=='r'||a[r][c+i]=='k')){
            v=100;check[r][c+i]=1;validity[r][c+i]=1;}
        if(a[r][c+i]!='+'&&a[r][c+i]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r<9)&&(c-i>0)&&(a[r][c-i]=='+'||a[r][c-i]=='-'||a[r][c-i]=='w'||a[r][c-i]=='n'||a[r][c-i]=='b'||a[r][c-i]=='q'||a[r][c-i]=='r'||a[r][c-i]=='k')){
            v=100;check[r][c-i]=1;validity[r][c-i]=1;}
        if(a[r][c-i]!='+'&&a[r][c-i]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r+i<9)&&(c<9)&&(a[r+i][c]=='+'||a[r+i][c]=='-'||a[r+i][c]=='w'||a[r+i][c]=='n'||a[r+i][c]=='b'||a[r+i][c]=='q'||a[r+i][c]=='r'||a[r+i][c]=='k')){
            v=100;check[r+i][c]=1;validity[r+i][c]=1;}
        if(a[r+i][c]!='+'&&a[r+i][c]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r-i>0)&&(c>0)&&(a[r-i][c]=='+'||a[r-i][c]=='-'||a[r-i][c]=='w'||a[r-i][c]=='n'||a[r-i][c]=='b'||a[r-i][c]=='q'||a[r-i][c]=='r'||a[r-i][c]=='k')){
            v=100;check[r-i][c]=1;validity[r-i][c]=1;}
        if(a[r-i][c]!='+'&&a[r-i][c]!='-'){break;}
    }
    for(int i=1;i<8;i++){
        if((r-i>0)&&(c+i<9)&&(a[r-i][c+i]=='+'||a[r-i][c+i]=='-'||a[r-i][c+i]=='w'||a[r-i][c+i]=='q'||a[r-i][c+i]=='r'||a[r-i][c+i]=='n'||a[r-i][c+i]=='b'||a[r-i][c+i]=='k')){
            v=100;check[r-i][c+i]=1;validity[r-i][c+i]=1;}
        if(a[r-i][c+i]!='+'&&a[r-i][c+i]!='-'){break;}
    }
     for(int i=1;i<8;i++){
        if((r-i>0)&&(c-i<9)&&(a[r-i][c-i]=='+'||a[r-i][c-i]=='-'||a[r-i][c-i]=='w'||a[r-i][c-i]=='q'||a[r-i][c-i]=='r'||a[r-i][c-i]=='n'||a[r-i][c-i]=='b'||a[r-i][c-i]=='k')){
            v=100;check[r-i][c-i]=1;validity[r-i][c-i]=1;}
        if(a[r-i][c-i]!='+'&&a[r-i][c-i]!='-'){break;}
    }
     for(int i=1;i<8;i++){
        if((r+i>0)&&(c+i<9)&&(a[r+i][c+i]=='+'||a[r+i][c+i]=='-'||a[r+i][c+i]=='w'||a[r+i][c+i]=='q'||a[r+i][c+i]=='r'||a[r+i][c+i]=='n'||a[r+i][c+i]=='b'||a[r+i][c+i]=='k')){
            v=100;check[r+i][c+i]=1;validity[r+i][c+i]=1;}
        if(a[r+i][c+i]!='+'&&a[r+i][c+i]!='-'){break;}
    }
     for(int i=1;i<8;i++){
        if((r+i<9)&&(c-i>0)&&(a[r+i][c-i]=='+'||a[r+i][c-i]=='-'||a[r+i][c-i]=='w'||a[r+i][c-i]=='q'||a[r+i][c-i]=='r'||a[r+i][c-i]=='n'||a[r+i][c-i]=='b'||a[r+i][c-i]=='k')){
            v=100;check[r+i][c-i]=1;validity[r+i][c-i]=1;}
        if(a[r+i][c-i]!='+'&&a[r+i][c-i]!='-'){break;}
    }
    if(temp == 0){return;}
    if (v==100){GetValidMove(a,validity );}
    else {printf("There is no Moves for this queen.\nEnter another piece index.\n");
    GetMove(a,0);
    Moves(a);}}

//Function get Moves of the Black king.
void WhiteKingMoves(char a[9][9],int temp){
intializeValidity(validity);
int r, c,V;
r=M[0];c=M[1];
if((a[r][c-1]=='-'||a[r][c-1]=='+'||a[r][c-1]=='P'||a[r][c-1]=='B'||a[r][c-1]=='N'||a[r][c-1]=='R'||a[r][c-1]=='Q'||a[r][c-1]=='K')&&check[r][c-1]==0){V=99;check[r][c-1]=1;validity[r][c-1]=1;}
if((a[r][c+1]=='-'||a[r][c+1]=='+'||a[r][c+1]=='P'||a[r][c+1]=='B'||a[r][c+1]=='N'||a[r][c+1]=='R'||a[r][c+1]=='Q'||a[r][c+1]=='K')&&check[r][c+1]==0){V=99;check[r][c+1]=1;validity[r][c+1]=1;}
if((a[r+1][c]=='-'||a[r+1][c]=='+'||a[r+1][c]=='P'||a[r+1][c]=='B'||a[r+1][c]=='N'||a[r+1][c]=='R'||a[r+1][c]=='Q'||a[r+1][c]=='K')&&check[r+1][c]==0){V=99;check[r+1][c]=1;validity[r+1][c]=1;}
if((a[r+1][c-1]=='-'||a[r+1][c-1]=='+'||a[r+1][c-1]=='P'||a[r+1][c-1]=='B'||a[r+1][c-1]=='N'||a[r+1][c-1]=='R'||a[r+1][c-1]=='Q'||a[r+1][c-1]=='K')&&check[r+1][c-1]==0){V=99;check[r+1][c-1]=1;validity[r+1][c-1]=1;}
if((a[r+1][c+1]=='-'||a[r+1][c+1]=='+'||a[r+1][c+1]=='P'||a[r+1][c+1]=='B'||a[r+1][c+1]=='N'||a[r+1][c+1]=='R'||a[r+1][c+1]=='Q'||a[r+1][c+1]=='K')&&check[r+1][c+1]==0){V=99;check[r+1][c+1]=1;validity[r+1][c+1]=1;}
if((a[r-1][c]=='-'||a[r-1][c]=='+'||a[r-1][c]=='P'||a[r-1][c]=='B'||a[r-1][c]=='N'||a[r-1][c]=='R'||a[r-1][c]=='Q'||a[r-1][c]=='K')&&check[r-1][c]==0){V=99;check[r-1][c]=1;validity[r-1][c]=1;}
if((a[r-1][c-1]=='-'||a[r-1][c-1]=='+'||a[r-1][c-1]=='P'||a[r-1][c-1]=='B'||a[r-1][c-1]=='N'||a[r-1][c-1]=='R'||a[r-1][c-1]=='Q'||a[r-1][c-1]=='K')&&check[r-1][c-1]==0){V=99;check[r-1][c-1]=1;validity[r-1][c-1]=1;}
if((a[r-1][c+1]=='-'||a[r-1][c+1]=='+'||a[r-1][c+1]=='P'||a[r-1][c+1]=='B'||a[r-1][c+1]=='N'||a[r-1][c+1]=='R'||a[r-1][c+1]=='Q'||a[r-1][c+1]=='K')&&check[r-1][c+1]==0){V=99;check[r-1][c+1]=1;validity[r-1][c+1]=1;}
if(temp == 0){return;}
if (V==99){GetValidMove(a,validity );}
else {printf("There is no Moves for this king.\nEnter another piece index.\n");
GetMove(a,1);
Moves(a);}}

//Function get Moves of the Black king.
void BlackKingMoves(char a[9][9],int temp){
intializeValidity(validity);
int r, c,V;
r=M[0];c=M[1];
if((a[r][c-1]=='-'||a[r][c-1]=='+'||a[r][c-1]=='w'||a[r][c-1]=='b'||a[r][c-1]=='n'||a[r][c-1]=='r'||a[r][c-1]=='q'||a[r][c-1]=='k')&&check[r][c-1]==0){V=99;check[r][c-1]=1;validity[r][c-1]=1;}
if((a[r][c+1]=='-'||a[r][c+1]=='+'||a[r][c+1]=='w'||a[r][c+1]=='b'||a[r][c+1]=='n'||a[r][c+1]=='r'||a[r][c+1]=='q'||a[r][c+1]=='k')&&check[r][c+1]==0){V=99;check[r][c+1]=1;validity[r][c+1]=1;}
if((a[r+1][c]=='-'||a[r+1][c]=='+'||a[r+1][c]=='w'||a[r+1][c]=='b'||a[r+1][c]=='n'||a[r+1][c]=='r'||a[r+1][c]=='q'||a[r+1][c]=='k')&&check[r+1][c]==0){V=99;check[r+1][c]=1;validity[r+1][c]=1;}
if((a[r+1][c-1]=='-'||a[r+1][c-1]=='+'||a[r+1][c-1]=='w'||a[r+1][c-1]=='b'||a[r+1][c-1]=='n'||a[r+1][c-1]=='r'||a[r+1][c-1]=='q'||a[r+1][c-1]=='k')&&check[r+1][c-1]==0){V=99;check[r+1][c-1]=1;validity[r+1][c-1]=1;}
if((a[r+1][c+1]=='-'||a[r+1][c+1]=='+'||a[r+1][c+1]=='w'||a[r+1][c+1]=='b'||a[r+1][c+1]=='n'||a[r+1][c+1]=='r'||a[r+1][c+1]=='q'||a[r+1][c+1]=='k')&&check[r+1][c+1]==0){V=99;check[r+1][c+1]=1;validity[r+1][c+1]=1;}
if((a[r-1][c]=='-'||a[r-1][c]=='+'||a[r-1][c]=='w'||a[r-1][c]=='b'||a[r-1][c]=='n'||a[r-1][c]=='r'||a[r-1][c]=='q'||a[r-1][c]=='k')&&check[r-1][c]==0){V=99;check[r-1][c]=1;validity[r-1][c]=1;}
if((a[r-1][c-1]=='-'||a[r-1][c-1]=='+'||a[r-1][c-1]=='w'||a[r-1][c-1]=='b'||a[r-1][c-1]=='n'||a[r-1][c-1]=='r'||a[r-1][c-1]=='q'||a[r-1][c-1]=='k')&&check[r-1][c-1]==0){V=99;check[r-1][c-1]=1;validity[r-1][c-1]=1;}
if((a[r-1][c+1]=='-'||a[r-1][c+1]=='+'||a[r-1][c+1]=='w'||a[r-1][c+1]=='b'||a[r-1][c+1]=='n'||a[r-1][c+1]=='r'||a[r-1][c+1]=='q'||a[r-1][c+1]=='k')&&check[r-1][c+1]==0){V=99;check[r-1][c+1]=1;validity[r-1][c+1]=1;}
if(temp == 0){return;}
if (V==99){GetValidMove(a,validity );}
else {printf("There is no Moves for this king.\nEnter another piece index.\n");
GetMove(a,0);
Moves(a);}}

//Function make the moves.
void Moves (char a[9][9]){
int r, c;
    r=M[0];
    c=M[1];
   if(a[r][c]=='w'){WhitePawnMoves(a,1);}
   else if(a[r][c]=='P'){BlackPawnMoves(a,1);}
   else if(a[r][c]=='r'){WhiteRookMoves(a,1);}
   else if(a[r][c]=='R'){BlackRookMoves(a,1);}
   else if(a[r][c]=='n'){WhiteKnightMoves(a,1);}
   else if(a[r][c]=='N'){BlackKnightMoves(a,1);}
   else if(a[r][c]=='b'){WhiteBishopMoves(a,1);}
   else if(a[r][c]=='B'){BlackBishopMoves(a,1);}
   else if(a[r][c]=='q'){WhiteQueenMoves(a,1);}
   else if(a[r][c]=='Q'){BlackQueenMoves(a,1);}
   else if(a[r][c]=='k'){WhiteKingMoves(a,1);}
   else if(a[r][c]=='K'){BlackKingMoves(a,1);}
}

//Function get the index of the white king.
void getwhitekingindex(char a[9][9],int b[2])
{
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j] == 'k'){b[0]=i;b[1]=j;}
        }
    }
}

//Function get the index of the Black king.
void getblackkingindex(char a[9][9],int b[2])
{
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j] == 'K'){b[0]=i;b[1]=j;}
        }
    }
}

//Function get all Possible moves of all black piece.
void allwhitecheck(char a[9][9])
{
    intializeValidity(check);
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j]=='P'){M[0]=i;M[1]=j;BlackPawnMoves(a,0);}
        }
    }
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j]=='N'){M[0]=i;M[1]=j;BlackKnightMoves(a,0);}
        }
    }
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j]=='B'){M[0]=i;M[1]=j;BlackBishopMoves(a,0);}
        }
    }
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j]=='R'){M[0]=i;M[1]=j;BlackRookMoves(a,0);}
        }
    }
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j]=='Q'){M[0]=i;M[1]=j;BlackQueenMoves(a,0);}
        }
    }
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j]=='K'){M[0]=i;M[1]=j;BlackKingMoves(a,0);}
        }
    }
}

//Function get all Possible moves of all white piece.
void allblackcheck(char a[9][9])
{
    intializeValidity(check);
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j]=='w'){M[0]=i;M[1]=j;WhitePawnMoves(a,0);}
        }
    }
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j]=='n'){M[0]=i;M[1]=j;WhiteKnightMoves(a,0);}
        }
    }
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j]=='b'){M[0]=i;M[1]=j;WhiteBishopMoves(a,0);}
        }
    }
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j]=='r'){M[0]=i;M[1]=j;WhiteRookMoves(a,0);}
        }
    }
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j]=='q'){M[0]=i;M[1]=j;WhiteQueenMoves(a,0);}
        }
    }
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(a[i][j]=='k'){M[0]=i;M[1]=j;WhiteKingMoves(a,0);}
        }
    }
}

//Function read the protected pieces
void FinalProtection(){
int i, j;
for(i=1;i<9;i++){
    for(j=1;j<9;j++){
        if(protect[i][j]==8){check[i][j]=1;}}}}

//Function check if white piece is protected.
void ProtectionWhite (char a[9][9]){
intializeValidity(protect);
int i, j;
char pro;
for (i=1;i<9;i++){
    for (j=1;j<9;j++){
        if(a[i][j]=='w'||a[i][j]=='n'||a[i][j]=='b'||a[i][j]=='r'||a[i][j]=='q'||a[i][j]=='k'){
            pro=a[i][j];
            a[i][j]='-';
            allblackcheck(a);
            if(check[i][j]==1){
                protect[i][j]=8;
                a[i][j]=pro;}
            else{a[i][j]=pro;}}}}}

////Function check if Black piece is protected.
void ProtectionBlack(char a[9][9]){
intializeValidity(protect);
int i, j;
char pro;
for (i=1;i<9;i++){
    for (j=1;j<9;j++){
        if(a[i][j]=='P'||a[i][j]=='N'||a[i][j]=='B'||a[i][j]=='R'||a[i][j]=='Q'||a[i][j]=='K'){
            pro=a[i][j];
            a[i][j]='-';
            allwhitecheck(a);
            if(check[i][j]==1){
                protect[i][j]=8;
                a[i][j]=pro;}
            else{a[i][j]=pro;}}}}}

//Function to know if white king checked or not.
void WhiteCheckMate(char a[9][9]){
  getwhitekingindex(a,WKI);
  if (check[WKI[0]][WKI[1]]==1){
    WKC[0]=1;
    printf("The White king is in a check state.\n");}
  else {WKC[0]=0;}}

//Function to know if black king checked or not.
void BlackCheckMate(char a[9][9]){
  getblackkingindex(a,BKI);
  if (check[BKI[0]][BKI[1]]==1){
    BKC[0]=1;
    printf("The black king is in a check state.\n");}
  else {BKC[0]=0;}}

//Function make moves in board1.
void SMove(int m,int n,int l,int k){board1[m][n]=board1[l][k];board1[l][k]=PlusMinus[l][k];}

//Function to get moves for the white Pieces when it the King is checked.
void WhiteCheckMove()
{
    int n[2];
    intializeValidity(validity2);
    intializeValidity(validity3);
    equaling();
     M[0]=WKI[0];M[1]=WKI[1];
    for(int i=1;i<9;i++){for(int j=1;j<9;j++){
            if(board1[i][j]=='k'){M[0]=i;M[1]=j;WhiteKingMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);getwhitekingindex(board1,n);allwhitecheck(board1);M[0]=i;M[1]=j;if(check[n[0]][n[1]]==0){validity2[i][j]=1;validity3[k][l]=2;}equaling();WhiteKingMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){for(int j=1;j<9;j++){
            if(board1[i][j]=='w'){M[0]=i;M[1]=j;WhitePawnMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionBlack(board1);allwhitecheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[WKI[0]][WKI[1]]==0){validity2[i][j]=1;validity3[k][l]=1;}equaling();WhitePawnMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){for(int j=1;j<9;j++){
            if(board1[i][j]=='n'){M[0]=i;M[1]=j;WhiteKnightMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionBlack(board1);allwhitecheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[WKI[0]][WKI[1]]==0){validity2[i][j]=1;validity3[k][l]=1;}equaling();WhiteKnightMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(board1[i][j]=='b'){M[0]=i;M[1]=j;WhiteBishopMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionBlack(board1);allwhitecheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[WKI[0]][WKI[1]]!=1){validity2[i][j]=1;validity3[k][l]=1;}equaling();WhiteBishopMoves(board,0);}
       }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(board1[i][j]=='r'){M[0]=i;M[1]=j;WhiteRookMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionBlack(board1);allwhitecheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[WKI[0]][WKI[1]]!=1){validity2[i][j]=1;validity3[k][l]=1;}equaling();WhiteRookMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(board1[i][j]=='q'){M[0]=i;M[1]=j;WhiteQueenMoves(board1,0);
               for(int k=1;k<9;k++){
                for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionBlack(board1);allwhitecheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[WKI[0]][WKI[1]]!=1){validity2[i][j]=1;validity3[k][l]=1;}equaling();WhiteQueenMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){if(validity2[i][j]==1){return;}}
    }
    checkmate[0] = 1;
}

//Function to get moves for the Black Pieces when it the King is checked.
void BlackCheckMove()
{
    int n[2];
    intializeValidity(validity2);
    intializeValidity(validity3);
    equaling();
     M[0]=BKI[0];M[1]=BKI[1];
      for(int i=1;i<9;i++){for(int j=1;j<9;j++){
            if(board1[i][j]=='K'){M[0]=i;M[1]=j;BlackKingMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);getblackkingindex(board1,n);allblackcheck(board1);M[0]=i;M[1]=j;if(check[n[0]][n[1]]==0){validity2[i][j]=1;validity3[k][l]=2;}equaling();BlackKingMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){for(int j=1;j<9;j++){
            if(board1[i][j]=='P'){M[0]=i;M[1]=j;BlackPawnMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionWhite(board1);allblackcheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[BKI[0]][BKI[1]]==0){validity2[i][j]=1;validity3[k][l]=1;}equaling();BlackPawnMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){for(int j=1;j<9;j++){
            if(board1[i][j]=='N'){M[0]=i;M[1]=j;BlackKnightMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionWhite(board1);allblackcheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[BKI[0]][BKI[1]]==0){validity2[i][j]=1;validity3[k][l]=1;}equaling();BlackKnightMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(board1[i][j]=='B'){M[0]=i;M[1]=j;BlackBishopMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionWhite(board1);allblackcheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[BKI[0]][BKI[1]]!=1){validity2[i][j]=1;validity3[k][l]=1;}equaling();BlackBishopMoves(board,0);}
       }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(board1[i][j]=='R'){M[0]=i;M[1]=j;BlackRookMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionWhite(board1);allblackcheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[BKI[0]][BKI[1]]!=1){validity2[i][j]=1;validity3[k][l]=1;}equaling();BlackRookMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(board1[i][j]=='Q'){M[0]=i;M[1]=j;BlackQueenMoves(board1,0);
               for(int k=1;k<9;k++){
                for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionWhite(board1);allblackcheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[BKI[0]][BKI[1]]!=1){validity2[i][j]=1;validity3[k][l]=1;}equaling();BlackQueenMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){if(validity2[i][j]==1){return;}}
    }
    checkmate[0] = 1;
}

//Function check if the white king not checked and there is no moves for white pieces.
void WhitestealkMove(){
int n[2];
    intializeValidity(validity2);
    intializeValidity(validity3);
    equaling();
     M[0]=WKI[0];M[1]=WKI[1];
    for(int i=1;i<9;i++){for(int j=1;j<9;j++){
            if(board1[i][j]=='k'){M[0]=i;M[1]=j;WhiteKingMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);getwhitekingindex(board1,n);allwhitecheck(board1);M[0]=i;M[1]=j;if(check[n[0]][n[1]]==0){validity2[i][j]=1;validity3[k][l]=2;}equaling();WhiteKingMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){for(int j=1;j<9;j++){
            if(board1[i][j]=='w'){M[0]=i;M[1]=j;WhitePawnMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionBlack(board1);allwhitecheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[WKI[0]][WKI[1]]==0){validity2[i][j]=1;validity3[k][l]=1;}equaling();WhitePawnMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){for(int j=1;j<9;j++){
            if(board1[i][j]=='n'){M[0]=i;M[1]=j;WhiteKnightMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionBlack(board1);allwhitecheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[WKI[0]][WKI[1]]==0){validity2[i][j]=1;validity3[k][l]=1;}equaling();WhiteKnightMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(board1[i][j]=='b'){M[0]=i;M[1]=j;WhiteBishopMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionBlack(board1);allwhitecheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[WKI[0]][WKI[1]]!=1){validity2[i][j]=1;validity3[k][l]=1;}equaling();WhiteBishopMoves(board,0);}
       }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(board1[i][j]=='r'){M[0]=i;M[1]=j;WhiteRookMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionBlack(board1);allwhitecheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[WKI[0]][WKI[1]]!=1){validity2[i][j]=1;validity3[k][l]=1;}equaling();WhiteRookMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(board1[i][j]=='q'){M[0]=i;M[1]=j;WhiteQueenMoves(board1,0);
               for(int k=1;k<9;k++){
                for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionBlack(board1);allwhitecheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[WKI[0]][WKI[1]]!=1){validity2[i][j]=1;validity3[k][l]=1;}equaling();WhiteQueenMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){if(validity2[i][j]==1){return;}}
    }
    stealmate[0] = 1;}
//Function check if the Black king not checked and there is no moves for Black pieces.
void BlackstealMove()
{
    int n[2];
    intializeValidity(validity2);
    intializeValidity(validity3);
    equaling();
     M[0]=BKI[0];M[1]=BKI[1];
      for(int i=1;i<9;i++){for(int j=1;j<9;j++){
            if(board1[i][j]=='K'){M[0]=i;M[1]=j;BlackKingMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);getblackkingindex(board1,n);allblackcheck(board1);M[0]=i;M[1]=j;if(check[n[0]][n[1]]==0){validity2[i][j]=1;validity3[k][l]=2;}equaling();BlackKingMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){for(int j=1;j<9;j++){
            if(board1[i][j]=='P'){M[0]=i;M[1]=j;BlackPawnMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionWhite(board1);allblackcheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[BKI[0]][BKI[1]]==0){validity2[i][j]=1;validity3[k][l]=1;}equaling();BlackPawnMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){for(int j=1;j<9;j++){
            if(board1[i][j]=='N'){M[0]=i;M[1]=j;BlackKnightMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionWhite(board1);allblackcheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[BKI[0]][BKI[1]]==0){validity2[i][j]=1;validity3[k][l]=1;}equaling();BlackKnightMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(board1[i][j]=='B'){M[0]=i;M[1]=j;BlackBishopMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionWhite(board1);allblackcheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[BKI[0]][BKI[1]]!=1){validity2[i][j]=1;validity3[k][l]=1;}equaling();BlackBishopMoves(board,0);}
       }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(board1[i][j]=='R'){M[0]=i;M[1]=j;BlackRookMoves(board1,0);
               for(int k=1;k<9;k++){for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionWhite(board1);allblackcheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[BKI[0]][BKI[1]]!=1){validity2[i][j]=1;validity3[k][l]=1;}equaling();BlackRookMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){
            if(board1[i][j]=='Q'){M[0]=i;M[1]=j;BlackQueenMoves(board1,0);
               for(int k=1;k<9;k++){
                for(int l=1;l<9;l++){
                    if(validity[k][l]==1){SMove(k,l,i,j);ProtectionWhite(board1);allblackcheck(board1);FinalProtection();M[0]=i;M[1]=j;if(check[BKI[0]][BKI[1]]!=1){validity2[i][j]=1;validity3[k][l]=1;}equaling();BlackQueenMoves(board,0);}
        }}}}}
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){if(validity2[i][j]==1){return;}}
    }
    stealmate[0] = 1;
}
//Function Check The move of white Piece will make the white king in check or not.
void CheckWhiteKingProtection(int i,int j,int r,int c)
{
    equaling();SMove(i,j,r,c);ProtectionBlack(board1);allwhitecheck(board1);FinalProtection();getwhitekingindex(board1,WKI);if(check[WKI[0]][WKI[1]]==1){printf("invalid move!! re-enter piece index:\n");tempo[0]=1;}
    else{tempo[0]=0;}
}
//Function Check The move of Black Piece will make the Black king in check or not.
void CheckBlackKingProtection(int i,int j,int r,int c)
{
    equaling();SMove(i,j,r,c);ProtectionWhite(board1);allblackcheck(board1);FinalProtection();getblackkingindex(board1,BKI);if(check[BKI[0]][BKI[1]]==1){printf("invalid move!! re-enter piece index:\n");tempo[0]=1;}
    else{tempo[0]=0;}
}

//function represent the Instructions of the game.
void Instructions (int n){
    printf("\n\n1- R->Rocks, N->knights, B->bishops, Q->Queen, K->King, P->pawns, w->white pawns.");
    printf("\n2- Capital letter for black pieces and small letter for white ones, '+':mean white square , and '-' :mean black square.");
    printf("\n3- white will start first then black.");
    printf("\n4- you will choose your piece index, then Choose the index of the square you want yo go for it, if it valid your piece will move but if not you will insert piece index again then move index");
}
