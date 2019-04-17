#define private public

#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"

using namespace std;

int main(int argv, char** argc){
  	if(argv != 3){
    		cout << "Please provide 2 file names" << endl;
    		return 1;
  	}
  
	ifstream cardFile1 (argc[1]);
 	ifstream cardFile2 (argc[2]);
  	string line;

  	if (cardFile1.fail()){
   	 	cout << "Could not open file " << argc[1];
   	 	return 1;
  	}

	if (cardFile2.fail()){
	    	cout << "Could not open file " << argc[2];
	    	return 1;
	}

	// Create two objects of the class you defined 
	// to contain two sets of cards in two input files

	// Read each file and store cards
	Player p1("Alice");
	Player p2("Bob");
	
	while (getline (cardFile1, line) && (line.length() > 0)){
 		if(line!="")
			p1.insert(line.at(0),line.substr(2));
	}	
  	cardFile1.close();

	while (getline (cardFile2, line) && (line.length() > 0)){
		if(line!="")
			p2.insert(line.at(0),line.substr(2));
	}
	cardFile2.close();

	// Start the game
	
	//Set Alice's selected to the smallest Card in Hand
	p1.selectSmallest();
	//set Bob's selected to largest Card in Hand
	p2.selectLargest();
		
	//Set bool flags
	bool gameOver = false;
	bool isAliceTurn = true;
	while(!gameOver && !p1.isEmpty() && !p2.isEmpty()){
		//Taking turns
		Player& currentP = (isAliceTurn) ? (p1) : (p2);
		Player& otherP = (isAliceTurn) ? (p2) : (p1);
		char currentSuit;
		string currentNumber;
		bool cardFound = false;
		
		//Contines while no matching cards are found and there are no new Cards left to select
		while(!cardFound && !currentP.noSelected()){
			//Update based on selected Cards's suit and number
			currentSuit=currentP.getSelectSuit();
			currentNumber=currentP.getSelectNumber();
			
			//Update bool by checking if other Player has and identical Card to the  current Player's selected Card
			cardFound=otherP.search(currentSuit,currentNumber); 
			
			//Move Selected onto next larger/smaller Card depending on whose turn it is
			if(isAliceTurn)
				currentP.selectSuccessor();
			else
				currentP.selectPredecessor();
		}

		if(cardFound){
			//Discard matching Card from both Player's Hands
			currentP.discard(currentSuit, currentNumber);
			otherP.discard(currentSuit, currentNumber);
			
			cout<<currentP.getName()<<" picked matching card "<<currentSuit<<" "<<currentNumber<<endl;
		}
		else if(!cardFound){
			//"Game" will now end
			gameOver=true;
		}
		//Resetting bool flags for next person's turn
		isAliceTurn = !isAliceTurn;
	}		

	//Post processing after game has ended
	//Print out remaning cards and delete all Cards on heap
	cout<<endl;

	cout<<p1.getName()<<"\'s cards:"<<endl;
	p1.showAll();
	
	cout<<endl<<p2.getName()<<"\'s cards:"<<endl;
	p2.showAll();

	return 0;
}
 
