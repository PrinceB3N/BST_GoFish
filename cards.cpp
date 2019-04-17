//cards.cpp
//Authors: Benjamin Prince
//Implementation of the classes defined in cards.h
#include "cards.h"

#include <string>
#include <iostream>
#include <iomanip>
//Initialize members to null (starting with Empty hand)
Player::Player(const std::string& name){
	root=0;
	selected=0;
	this->name=name;
}
//Deletes all Cards in Hand until all are freed from mem
Player::~Player(){
	recDestructHelp(root);
	root=selected=0;
}
//Paramterized constructor, sets selected to NULL, name to name due to it being a copy
Player::Player(const Player& h){
	if(!h.root){
		root=selected=0;
		this->name=h.name;
		return;
	}
	else{
	
	root=selected=0;

	//Recursively builds BST from param's root
	recConstructHelp(h.root);
	
	this->name=h.name;
	selected=getCardFor(identifyCharFrom(h.selected->suit),identifyStringFrom(h.selected->num));
	}
}
//Inserts a new card at the end of the Hand
void Player::insert(const char& s, const string& n){
	//If no cards in hand, set new Card as root
	if(!root){
		root = selected = new Card(s,n);
		return;
	}
	else{
		Card* tmp = root;
		while(tmp){
			//If suit is less than
			if(identifySuit(s) < tmp->suit){
				if(tmp->left)
					tmp=tmp->left;
				else{
					tmp->left=new Card(s,n);
					tmp->left->parent=tmp;
					return;
				}
			}
			//If suit is greater than
			else if(identifySuit(s) > tmp->suit){
				if(tmp->right)
					tmp=tmp->right;
				else{
					tmp->right=new Card(s,n);
					tmp->right->parent=tmp;
					return;
				}
			}
			//If suit is same but num is less than
			else if(identifyNum(n)<tmp->num){
				if(tmp->left){
					tmp=tmp->left;
				}
				else{
					tmp->left=new Card(s,n);
					tmp->left->parent=tmp;
					return;
				}
			}
			//If suit is same but num is greater than
			else{
				if(tmp->right)
					tmp=tmp->right;
				else{
					tmp->right=new Card(s,n);
					tmp->right->parent=tmp;
					return;
				}
			}
		}
	}
}
//Looks for a Card in Hand with a specific Suit and Number
//Return: true if found, false if not found
bool Player::search(const char& suit, const string& num) const{
	Card* p = getCardFor(suit,num);
	if(p)
		return true;

	//If reach end of Hand without finding specific Card return false
	return false;
}

//Deletes a Card from the Hand with corresponding Suit and Number
//Return: True if successfully deleted Card, false if could not delete Card
 bool Player::discard(const char& suit, const string& num){
 	//Pre-processing
     	Card* todel = getCardFor(suit,num);
     	Card* toswp = NULL;
     	bool issuccessor;
     	if(!todel){
         	return false;
     	}

     	if(todel->right){
 		toswp = successor(suit,num);
 		issuccessor = true;
     	}
     	else if(todel->left){
 		toswp = predecessor(suit,num);
 		issuccessor = false;
     	}
     	else{
 		//If selected is the same as todel, make it equal to parent
 		if(todel->parent){
 			if(selected==todel){
				Card* tmp = successor(identifyCharFrom(todel->suit),identifyStringFrom(todel->num));
				if(tmp)
	 				selected=tmp;
				else
 					selected=predecessor(identifyCharFrom(todel->suit),identifyStringFrom(todel->num));

 			}
 	    		if(todel->parent->left==todel)
   				todel->parent->left=NULL;
 	    		else
 				todel->parent->right=NULL;
 	    		delete todel;
 		}
 		else{
 	   		delete todel;
 	    		root=selected=NULL;
 		}	
 		return true;
     	}
	
	//If selected points to same place as swapped Card, make it equal to the Card that was about to be deleted
	if(selected==toswp){
		selected=todel;
	}
	//Swap data
     	todel->suit = toswp->suit;
 	todel->num = toswp->num;
  
     	if(issuccessor){
         	if(toswp->parent->right==toswp)
     	    		toswp->parent->right = toswp->right;
 		else
 	    		toswp->parent->left = toswp->right;
      
 		if(toswp->right==NULL);
 		else
 	     		toswp->right->parent = toswp->parent;
     	}
     	else{
 		if(toswp->parent->left==toswp)
 	    		toswp->parent->left = toswp->left;
 		else
 	    			toswp->parent->right = toswp->left;
 		if(toswp->left==NULL);	
 		else
         	    toswp->left->parent = toswp->parent;
     	}
      
 	delete toswp;
    	return true;		
 }
//Changes selected to point to next larger Card
//Return: true if selected now points to successor, false if selected has been deleted or
//	selected has reached the end of Player
bool Player::selectSuccessor(){
	if(!selected)
		return false;
	else
		selected=successor(getSelectSuit(),getSelectNumber());
	
	if(!selected)
		return false;
	else
		return true;
}
//Changes selected to point to next smaller Card
//Return: true if selected now points to predecessor, false if selected has been deleted or 
//	  selected has reached end of Player
bool Player::selectPredecessor(){
	if(!selected)
		return false;
	else
		selected=predecessor(getSelectSuit(),getSelectNumber());

	if(!selected)
		return false;
	else
		return true;
}
//Changes selected to point to largest Card in Player
//return: false if no Cards in Hand, true if Cards in Hand
bool Player::selectLargest(){
	if(!root)
		return false;

	selected=max(root);
	if(!selected)
		return false;
	else
		return true;
}
//Changes selected to point to the smallest Card in Hand
//return: false if no Cards in Hand, true if Cards in Hand
bool Player::selectSmallest(){
	if(!root)
		return false;

	selected=min(root);
	if(!selected)
		return false;
	else 
		return true;
}
string Player::getName() const{
	return name;
}
//cout all cards in hand
void Player::showAll() const{
	printInOrder(root);
}
//Returns true if hand has no Cards, else false
bool Player::isEmpty() const{
	return root==0;
}
//Returns suit of card in Card that selected points to
char Player::getSelectSuit() const{
	return identifyCharFrom(selected->suit);
}
//Returns number of card in Card that selected points to
string Player::getSelectNumber() const{
	return identifyStringFrom(selected->num);
}
//Returns true if selected is pointing to a real Card, false if to NULL
bool Player::noSelected() const{
	return selected==0;
}
//Assignment operator
Player& Player::operator=(const Player& h){
	//Delete everything in this
	recDestructHelp(root);
	this->root=0;

	//If h has no Cards
	if(!h.root){
		root=selected=0;
		return *this;
	}
	//Else reconstruct this Player's hand with h's Hand
	recConstructHelp(h.root);
	selected=getCardFor(h.getSelectSuit(),h.getSelectNumber());
	return *this;
}

//PRIVATE MEMBER FUNCTIONS

//Resets selected to root
void Player::resetSelected(){
	selected=root;
}
//Pass in the Suit and Number of current selected to find the successor of it
//Return: pointer to the successor, NULL if none exists
Player::Card* Player::successor(const char& suit, const string& num) const{
    	Card* tmp = getCardFor(suit,num);
    	if(!tmp)
        	return NULL;

    	Card* srch = tmp->right;
    	Card* srchUp = tmp->parent;

    	if(srch){
       		while(srch->left){
	    		srch=srch->left;	    
        	}
		return srch;
    	}
    	else if(!srch){
		Card* prev = tmp;
		while(srchUp&&srchUp->left!=prev){
	    		prev=srchUp;
	    		srchUp=srchUp->parent;
		}
		return srchUp;
    	}
    	else{
    		return NULL;	
	}
}
//Pass in Suit and Number of current selected to find predecessor of it
//Return: pointer to predecessor, NULL if none exists
Player::Card* Player::predecessor(const char& suit, const string& num) const{
 	Card* tmp = getCardFor(suit,num);
    	if(!tmp)
        	return NULL;

    	Card* search = tmp->left;
    	Card* searchUp = tmp->parent;

    	if(search){
       		while(search->right){
	    		search=search->right;	    
        	}
		return search;
    	}
    	else if(!search){
		Card* prev = tmp;
		while(searchUp){
	    		if(searchUp->right==prev)
	        		return searchUp;
	    		prev=searchUp;
	    		searchUp=searchUp->parent;
		}
    	}
    
    	return NULL;	
}
//Precondition: use with pointer to Card object that is not NULL
//Postcondition: returns pointer to max of BST 
Player::Card* Player::max(Card* c) const{
	if(!c->right)
		return c;
	else
		return max(c->right);

}
//Precondition: use with pointer to a Card Object that is not NULL
//Postcondition: returns pointer to min of BST
Player::Card* Player::min(Card* c) const{
	if(!c->left)
		return c;
	else 
		return min(c->left);

}
//Helper function to constructor: inserts new Cards into Hand at the same order of another Hand
void Player::recConstructHelp(Card* c){
	if(c){
		insert(identifyCharFrom(c->suit),identifyStringFrom(c->num));
		recConstructHelp(c->left);
		recConstructHelp(c->right);
	}
}
//Helper function to destructor, clears all Cards in Hand in heap
void Player::recDestructHelp(Card* c){
  if(c){
		recDestructHelp(c->left);
		recDestructHelp(c->right);
		delete c;
	}
}
//Helper function that prints all Cards in Hand from least to greatest
void Player::printInOrder(Card* c) const{
	if(c){
		printInOrder(c->left);
		cout<<identifyCharFrom(c->suit)<<" "<<identifyStringFrom(c->num)<<endl;
		printInOrder(c->right);
	}
}
//Takes in the char value of a suit of a Card
//Return: the corresponding Suit value of the char passed in
Player::Suit Player::identifySuit(const char& c){
	switch(c){
		case 'c': return CLUBS;
		case 'd': return DIAMONDS;
		case 's': return SPADES;
		case 'h': return HEARTS;
	
	}	

	return CLUBS;
}
//Takes in string value of a Number of a Card
//Return: corresponding Number value of the string passed in
Player::Number Player::identifyNum(const string& s){
	
	if(s=="a")
		return ACE;
	else if(s=="2")
		return TWO;
	else if(s=="3")
		return THREE;
	else if(s=="4")
		return FOUR;
	else if(s=="5")
		return FIVE;
	else if(s=="6")
		return SIX;
	else if(s=="7")
		return SEVEN;
	else if(s=="8")
		return EIGHT;
	else if(s=="9")
		return NINE;
	else if(s=="10")
		return TEN;
	else if(s=="j")
		return JACK;
	else if(s=="q")
		return QUEEN;
	else if(s=="k")
		return KING;
	else
		return ACE;
}
//Takes in Suit value 
//Return: corresponding char value to Suit value passed in
char Player::identifyCharFrom(const Suit& s){
	if(s==CLUBS)
		return 'c';
	if(s==DIAMONDS)
		return 'd';
	if(s==SPADES)
		return 's';
	if(s==HEARTS)
		return 'h';

	return 'c';
}
//Takes in Number value
//Return: corresponding string value to Number value passed in
string Player::identifyStringFrom(const Number& n){
	switch(n){
		case ACE: return "a";
		case TWO: return "2";
		case THREE: return "3";
		case FOUR: return "4";
		case FIVE: return "5";
		case SIX: return "6";
		case SEVEN: return "7";
		case EIGHT: return "8";
		case NINE: return "9";
		case TEN: return "10";
		case JACK: return "j";
		case QUEEN: return "q";
		case KING: return "k";
		default: return "a";
	}
}
//Helper function to any functions requiring search 
//Takes in suit and number values
//Return: a pointer to the Card in Hand with corresponding suit and number values
//		,NULL if none is found
Player::Card* Player::getCardFor(const char& suit, const string& num) const{       
	Card* p = root;
        while(p){
                //Check if suit and num match
                if(p->suit==identifySuit(suit) && p->num==identifyNum(num))
	                return p;
                //Compare suits and numbers as necessary
                if(p->suit>identifySuit(suit))
                        p=p->left;
                else if(p->suit<identifySuit(suit))
                         p=p->right;
                else if(p->num>identifyNum(num))
                        p=p->left;
                else
                        p=p->right;
        }

        //If reach end of Hand without finding specific Card return NULL
        return NULL;
}
