//cards.h
//Authors: Benjamin Prince
//All class declarations go here

#ifndef CARDS_H
#define CARDS_H

#include <string>

#define private public

using namespace std;

class Player{
	public:		
		//Constructors/Destructors
		Player(const string& name = "No Name");
		Player(const Player& h);
		~Player();
		
		void insert(const char& suit, const string& num);
		bool discard(const char& suit, const string& num);
		bool selectSuccessor();
		bool selectPredecessor();
		bool selectSmallest();
		bool selectLargest();
		Player& operator=(const Player& h);

		//Const functions
		string getName() const;
		bool search(const char& suit, const string& num) const;
		void showAll() const;
		bool isEmpty() const;
		char getSelectSuit() const;
		string getSelectNumber() const;
		bool noSelected() const;
	private:

		enum Suit {CLUBS=1,DIAMONDS,SPADES,HEARTS};
                enum Number {ACE=1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};

		struct Card{
			Suit suit;
			Number num;
			Card* left;
			Card* right;
			Card* parent;

			//Constructor
			Card(char s, string n){
				suit=identifySuit(s);
				num=identifyNum(n);
				left=right=parent=0;
			}
		};

		Card* root;
		Card* selected;
		std::string name;

		void resetSelected();
		void recConstructHelp(Card* c);
                void recDestructHelp(Card* c);
		static Suit identifySuit(const char& c);
		static Number identifyNum(const string& s);
		static char identifyCharFrom(const Suit& s);
		static string identifyStringFrom(const Number& n);
		
		//Const functions
		Card* getCardFor(const char& suit,const string& num) const;
		Card* successor(const char& suit,const string& num) const;
                Card* predecessor(const char& suit,const string& num) const;
		Card* max(Card* c) const;
		Card* min(Card* c) const;
                void printInOrder(Card* c) const;
};

#endif
