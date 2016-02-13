// MyMain.cpp: implementation of the MyMain class.
//
//////////////////////////////////////////////////////////////////////
#pragma warning(disable:4786)
#include <iostream>

#include "Wheel.h"
#include "Axle.h"


#include <string>
#include <cctype>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>



using namespace std;

/////////////////////////
//define functions here
/////////////////////////
bool validateStartQuitInput(string a);
bool isUserSelectionValid(string x, string y, string gameBoard[][3]);
void getCurrentPlayerInput(string* curPlayer, string gameBoard[][3]);
void updateGameBoardDisplay(string a[][3]);
bool checkForWinner(string gameBoard[][3], string* currentPlayer);
bool checkForTie(string gameBoard[][3]);
void aiSmartSelect(string* curPlayer, string gb[][3]);
int aiScanArrayForWinningIndex(string strArr[], string* curPlayer);

bool aiScanRowsForWin(string* curPlayer, string gameboard[][3]);
void resetGameBoard(string gameboard[][3], int maxRow, int maxCol);

int main(){

	/*
	//create axle with default constructor
	Axle axe;
	//create wheel pointer
	Wheel * ptr = NULL;
	//create wheel with mod constructor
	Wheel w(99,'c',"green");
	//assign wheel address to pointer
	ptr = &w;
	//add wheel onto axle through a pointer
	axe.addWheel(ptr);


	//add pass wheel ptr into axle
	Wheel w2(22,'d',"purple");
	ptr = &w2;
	axe.addWheel(ptr);


	

	//Wheel * ptr = axe.wheels[0];
	//cout << ptr->size << endl;
	//printf("wheel size is %d", ptr->size);
	
	for(int i =0; i<axe.wheels.size(); i++){

		cout << axe.wheels[i].size << " " << axe.wheels[i].color << endl;
	}

	cout << "size of vec is : " << axe.wheels.size() << endl;

	//return wheel from vector
	ptr = axe.getWheel(0);
	//print
	std::cout << ptr->c << endl;
	//modify wheel size
	ptr = axe.getWheel(1);
	std::string co = ptr->c;
	std::cout << co << endl;
	*/

	/////////////////////////////////////////////////
	//Define all global game setting variables here
	//////////////////////////////////////////////////
	bool isWinnerFound = false;
	bool isTie = false;
	int maxRow = 3;
	int maxCol = 3;
	string gameBoard[3][3];	//creates a 3x3 matrix of strings

	//populate the gameboard with one empty string space in each tile
	//| , , |
	//| , , |
	//| , , |
	resetGameBoard(gameBoard, maxRow, maxCol);

	//gameBoardPtr = gameBoard;

	string p1 = "X";	//human player
	string p2 = "O";	//AI
	string * currentPlayer = &p1; 

	string title = "Let's Play Tic Tac Toe\n";

	string g0 = "Instructions:\n\n";
	string g1 = "	: 0 0 : 0 1 : 0 2 :\n\n";
	string g2 = "	: 1 0 : 1 1 : 1 2 :\n\n";
	string g3 = "	: 2 0 : 2 1 : 2 2 :\n\n";
	string grid = g0 + g1 + g2 + g3;

	//instruction
	string instruction = "Enter two coords with space to mark your decision\n";
	
	//prompts
	string n1 = "-----------------------------------------------------------\n";
	string n2 = "New Game!\n";
	string newGameText = n1 + n2 + n1;

	string prompt1 = "   A) Press A to begin\n";
	string prompt2 = "   B) Press B to quit\n";
	string promptFinalStartQuitMessage = prompt1 + prompt2;

	//random seed - only do this once upon app start
	srand (time(0) );
	//allows you to later do something like
	// x = rand()%50+1

	////////////////////////////////////
	//display title, grid, and instructions
	////////////////////////////////////

	//enable all cout below when final
	//cout << title << endl;
	//cout << grid << endl;
	//cout << instruction << endl;
	//cout << newGameText << endl;

	///////////////////////////////////
	// display start or quit options
	///////////////////////////////////
	//cout << promptFinalStartQuitMessage << endl;

	//prompt user
	string ans;
	cin >> ans;

	////////////////////
	//validate input
	////////////////////
	if(validateStartQuitInput(ans)){

		//////////////////
		//Game Loop
		//////////////////
		//before we allow a player or ai to go on their turn
		//we check if there is a winner or a tie
		//game can only proceed neither has occured
		//obviously first round isn't going to have a winner or tie
		while(!isWinnerFound && !isTie){

			//player's input
			getCurrentPlayerInput(currentPlayer, gameBoard);
			
			//update gameboard display after player goes
			updateGameBoardDisplay(gameBoard);

			//check for winner
			isWinnerFound = checkForWinner(gameBoard, currentPlayer);

			//check for tie if no winner
			if(!isWinnerFound){
				//check for a tie, will return true if all spaces are filled
				isTie = checkForTie(gameBoard);
			}

			//alternate to next player's turn if no winner or no tie found
			if(!isWinnerFound && !isTie){
				
				//check if current player is player1
				//because we are using a string pointer
				//we need the ( ) around *currentPlayer to call compare method
				if( (*currentPlayer).compare(p1) == 0){

					//switch player to player 2
					currentPlayer = &p2;
				}else{

					//switch player to player1
					currentPlayer = &p1;
				}
			}
			
		}

		if(isWinnerFound){
			cout << "Winner is: " << *currentPlayer <<  " - Thanks for playing" << endl;
		}else if(isTie){
			cout << "Game is a TIE - Thanks for playing" << endl;
		}else{
			cout << "serious error has occured!! Quiting Game" << endl;
		}

	}else{

		//display quit message
		cout << "Game is Quitting" << endl;
		
	}

	//end the app
	return 0;
}

//############################
//////////////////////////////
// Function Implementations //
//////////////////////////////
//############################

bool validateStartQuitInput(string a){

	if(a.compare("a") == 0 || a.compare("A") == 0) {
		//cout << "equals\n" << endl;
		return true;
	}else{
		return false;
	}
}

//curPlayer aka current player
//this method handles the user's input and the AI's input
void getCurrentPlayerInput(string* curPlayer, string gb[][3]){

	string playerValue = *curPlayer;
	
	//check if AI or real player
	if(playerValue.compare("X") == 0){

		//run real player codes
		cout << "Player " << *curPlayer << " Turn. Choose Coordinates Now." << endl;

		
		string x, y;	//prepare variables for inputs
		cin >> x >> y;	//prompt user and read in user x,y inputs

		//check if inputs are valid
		if(isUserSelectionValid(x,y, gb)){
			
			//convert string to int
			int x_int = atoi(x.c_str());
			int y_int = atoi(y.c_str());

			//put the user's choice on the gameboard
			gb[x_int][y_int] = *curPlayer;

		}else{
			//invalid user inputs - computers turn
			cout << "Invalid inputs!! Your turn is skipped." << endl;
		}

	}else{

		//run AI codes
		cout << "AI's turn. AI is thinking..." << endl;

		//TESETS - apply custom ai selection -- turn this off when finalize, this is just a tester
		//gb[2][0] = *curPlayer;
		//gb[2][2] = *curPlayer;

		//pass the gameboard and the ai into a separate method
		//this method will help the AI make a smart move
		aiSmartSelect(curPlayer, gb);

		
	}

}

//it will check the entire gameboard and scan row by row and col by col and diagonal by diagonal
//in order to know how the AI should proceed
//example of rows:
//   | X |   | = row [  ,X,  ]
// O |   | X | = row [ O, ,X ]
// O | X | O | = row [ O,X,O ]
//
// each row,col,diagonal is scanned thoroughly to 
// see if the ai has made any mark in it or not
void aiSmartSelect(string* curPlayer, string gb[][3]){
	
	//FIND ALL FREE SPACES - EASIER THIS WAY THEN SCANNING ROW BY ROW AND COL BY COL
	//then check each free space using checkForWinner()
	//revert back one by by if not a winner

	//we use a vector to store our coordinates of free spaces
	//stores x,y coordinates that are free open spaces on the gameboard
	//ex1 of freeSpaceArray populated
	//[ (0,0), (0,2), (1,2) ]
	// ex1 means that three spaces are available
	// to access the first set of coordinates do freeSpaceArray[0]
	// then to get into the x and y value of the first set, change the 2nd number to 0 or 1
	// int x = freeSpaceArray[0][0]	//
	// int y = freeSpaceArray[0][1]	//
	vector< vector<int> > freeSpaceArray;

	//track ai made a final move or not
	bool aiMadeMove = false;

	//find all available spaces not yet taken
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			
			//collect empty spaces
			if(gb[i][j].compare(" ") == 0){
				
				//created a vector to store the coordinates of x and y
				vector<int> coord; // we cannot do vector<int> coord = {i, j}; because i and j are dynamically created
				//instead use push_back to create copies of i and j and push into the coord array
				coord.push_back(i);
				coord.push_back(j);
				freeSpaceArray.push_back(coord);
			}
		}
	}

	//scan all free spaces (One at a time) and check if AI is winner or not
	for(int k=0; k<freeSpaceArray.size(); k++){

		//get x and y coordinate from detected free space
		int x = freeSpaceArray[k][0];
		int y = freeSpaceArray[k][1];

		//put ai marker on this specific gameboard
		gb[x][y] = *curPlayer;
		aiMadeMove = true;

		//this allow the ai to test where it placed it's marker, see if ai is a winner
		if(!checkForWinner(gb, curPlayer)){
			//if AI didn't win, revert the space back to empty
			gb[x][y] = " ";
			aiMadeMove = false;
		}else{
			//if selected space is a winnner, break from this loop
			break;
		}
		
	}

	//if no winning move found, make a random move instead
	//on any of the free spaces found
	if(!aiMadeMove){

		//pick a random free slot within range of the array
		int randomCoordIndex = rand() % freeSpaceArray.size();
			//test index
			//cout << "rand: " << randomCoordIndex << endl;
		int x = freeSpaceArray[randomCoordIndex][0];
		int y = freeSpaceArray[randomCoordIndex][1];

		//put ai marker on this specific gameboard
		gb[x][y] = *curPlayer;
	}
	

	///END OF TEST

	/*
	string colArr[3];
	string diaArr[3];

	//if you get a lot of warnings using map, 
	//turn off the warning with #pragma
	std::map<string, int> strMap;

	//to track when a winning move is found
	bool aiMadeWinningMove = false;

	//scan rows for a win
	aiMadeWinningMove = aiScanRowsForWin(curPlayer, gb);

	//scan col for a win if row didn't catch any wins
	if(!aiMadeWinningMove){
		//aiScanColsForWin(curPlayer, gb);
	}
	*/

}

//helper method to scan rows for ai
bool aiScanRowsForWin(string* curPlayer, string gb[][3]){

	string rowArr[3];

	//scan for winning rows
	for(int i=0; i<3; i++){

		for(int k=0; k<3; k++){

			//gather each mark
			string t = gb[i][k];
			rowArr[k] = t;

		}

		//each iteration, here
		//we are able to collect a row arr of 3 string values
		//ex1: ["X", "X", "O"]
		//ex2: ["O", " ", " "]
		//we scan this array if any of the value belongs to ai - ai uses "O" value

		//if return index is:
		//3 = not a winning row
		//0,1,2 = the winning index
		int index = aiScanArrayForWinningIndex(rowArr, curPlayer);
		if(index != 3){

			//ai will now select this space
			//i is the current row that was just scanned
			//index is the col the empty space was found in
			//we set the AI's marker on the gameboard
			gb[i][index] = *curPlayer;
			
			//break out of this method
			return true;
		}
		

	} // end of for-loop

	return false;
}

//The array coming into here should always have a size of 3, no less no more

int aiScanArrayForWinningIndex(string strArr[], string* curPlayer){


	//index to return with available space
	int index = 3;	//starts out of range

	//tracks how many times the AI has already marked in the array
	int playerMarkedSlotcounter = 0;

	//tracks empty spaces counted in array
	int emptySpaceCounter = 0;

	//we know the arr is size three
	for(int i=0; i<3; i++){

		if(strArr[i].compare(*curPlayer) == 0){
			//for each match increment the counter to track how many matched the AI
			playerMarkedSlotcounter++;
		}else if(strArr[i].compare(" ") == 0){
			emptySpaceCounter++;
			index = i;
		}
	}

	
	if(playerMarkedSlotcounter == 2 && emptySpaceCounter == 1){
		//this means that there are 2 marks for the AI and there is an empty
		//slot for the AI to make and take the win
		//return this winning index
		return index;
	}

	//no good  match found
	//return a 3 (it could be any number greater than 3, we just chose 3)
	return 3;
}

void updateGameBoardDisplay(string a[][3]){

	for(int row=0; row<3; row++){

		for(int col=0; col<3; col++){

			cout << a[row][col] << " : ";
		}
		
		cout << endl;
	}
}

bool isUserSelectionValid(string x, string y, string gameBoard[][3]){

	//validate x is digit
	for(int i=0; i<x.length(); i++){
		if(!isdigit( x[i] )){
			return false;
		}
	}

	//validate y is digit
	for(int j=0; j<y.length(); j++){
		if(!isdigit( y[j] )){
			return false;
		}
	}

	//convert string to int for range validation
	int x_val = atoi(x.c_str());
	int y_val = atoi(y.c_str());

	//validate x y are in range
	if(x_val >= 3 || y_val >= 3){
		return false;
	}

	//validate is the space already taken on the gameboard
	if(gameBoard[x_val][y_val].compare(" ") != 0){
		return false;
	}
	
	//if it gets to this point, this method will return true
	//meaning everything was validated and passed
	return true;
	
}

// gb = gameboard
bool checkForWinner(string gb[][3], string* currentPlayer){
	
	//string cp = currentPlayer;
	//1st row
	if(		gb[0][0].compare(*currentPlayer) == 0 
		&&	gb[0][1].compare(*currentPlayer) == 0  
		&&	gb[0][2].compare(*currentPlayer) == 0

		|| 
		//2nd row
			gb[1][0].compare(*currentPlayer) == 0 
		&&	gb[1][1].compare(*currentPlayer) == 0  
		&&	gb[1][2].compare(*currentPlayer) == 0
		
		|| 
		//3rd row
			gb[2][0].compare(*currentPlayer) == 0 
		&&	gb[2][1].compare(*currentPlayer) == 0  
		&&	gb[2][2].compare(*currentPlayer) == 0
		
		|| 
		//1st col
			gb[0][0].compare(*currentPlayer) == 0 
		&&	gb[1][0].compare(*currentPlayer) == 0  
		&&	gb[2][0].compare(*currentPlayer) == 0
		
		|| 
		//2nd col
			gb[0][1].compare(*currentPlayer) == 0 
		&&	gb[1][1].compare(*currentPlayer) == 0  
		&&	gb[2][1].compare(*currentPlayer) == 0
		
		|| 
		//1st col
			gb[0][2].compare(*currentPlayer) == 0 
		&&	gb[1][2].compare(*currentPlayer) == 0  
		&&	gb[2][2].compare(*currentPlayer) == 0
		
		|| 
		//1st diaganol
			gb[0][0].compare(*currentPlayer) == 0 
		&&	gb[1][1].compare(*currentPlayer) == 0  
		&&	gb[2][2].compare(*currentPlayer) == 0
		
		|| 
		//2nd diagnol
			gb[0][2].compare(*currentPlayer) == 0 
		&&	gb[1][1].compare(*currentPlayer) == 0  
		&&	gb[2][0].compare(*currentPlayer) == 0) 
	{
		return true;
	};



	return false;
}

bool checkForTie(string gb[][3]){

	//check all spaces are filled
	for(int row=0; row<3; row++){

		for(int col=0; col<3; col++){

			//return false if any one empty space is detected
			if( gb[row][col].compare(" ") == 0){
				return false;
			}
		}
	}

	//no empty space detected, return true for a tie detection
	return true;
}

void resetGameBoard(string gameboard[][3], int maxRow, int maxCol){
	for(int row=0; row<maxRow; row++){
		for(int col=0; col<maxCol; col++){
			gameboard[row][col] = " ";
		}
	}
}
