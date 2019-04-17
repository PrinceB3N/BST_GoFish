// This file should contain unit tests for all the 
// public interfaces of the classes that you implement
#define private public

#include <iostream>
#include <fstream>
#include <string>
#include "cards.h"

using namespace std;

/*--------------TEST HELPER FUNCTIONS----------------*/

void check(Player::Suit expected, char actual, string message) {
	if(actual!=Player::identifyCharFrom(expected)) {
         	cout << "   FAILED: " << message << "\n"
                     	<< "     Expected: " << Player::identifyCharFrom(expected) << " Actual: " << actual << "\n";
        }
        else {
        	cout << "PASSED: "<< message<<"\n";
        }
}
void check(Player::Number expected, string actual, string message) {
        if(actual!=Player::identifyStringFrom(expected)) {
		cout << "   FAILED: " << message << "\n"
                          << "     Expected: " << Player::identifyStringFrom(expected) << " Actual: " << actual << "\n";
        }
        else {
                cout << "PASSED: "<< message<<"\n";
        }
}

void check(Player::Card* expected, Player::Card* actual, string message) {
          if(expected!=actual) {
                 cout << "   FAILED: " << message << "\n"
  	                 << "     Expected: " << expected << " Actual: " << actual << "\n";
          }
          else {
		 cout << "PASSED: "<< message<<"\n";
          }
}

void check(bool expression, string message) {
        if (expression) {
                cout << "PASSED: " << message << "\n";
        }
        else {
                cout << "   FAILED: " << message << "\n"
 	             	 << "     Expected true, but was false " << "\n";
        }
}
void startMainTestGroup(string className){
	cout << "++++++++++++++++++++++++++++++++++" << "TESTING" << className << "+++++++++++++++++++++++++++++++++++++" << "\n";
}
void startTestGroup(string name){
        cout << "\n" << "--------------" << name << "--------------" << "\n";
}
void startSubTestGroup(string name){
	cout << "\n" << "~~~~~" << name << "~~~~~" << "\n";
}
void testAlert(string message){
	cout << "\n" << "//////////////" << message <<"////////////" << "\n";
}

/*--------------[TESTING Player FUNCTIONS]--------------*/

	//----Constructors/Destructors----
	

//Player(const string& name="No Name");
void testPlayerDefault(){
	startTestGroup("testPlayerDefault");

	Player h;
	check(h.root, 0, "h.root==0");
	check(h.name=="No Name","h.name==No Name");

	Player h2("Lucy");
	check(h2.name=="Lucy","h2.name==Lucy");
}
//Player(const Player& h);
void testPlayerParams(){
	startTestGroup("testPlayerParams");

	Player h1;
	h1.root=new Player::Card('h',"a");
	h1.root->left=new Player::Card('d',"2");
	h1.root->left->parent=h1.root;
	h1.root->right=new Player::Card('h',"k");
	h1.root->right->parent=h1.root;
	h1.selected=h1.root;

	Player h2(h1);
	check(h2.root->suit, 'h', "h2.root->suit==h");
	check(h2.root->num, "a", "h2.root->num==a");
	check(h2.root->left->suit, 'd', "h2.root->left->suit==d");
	check(h2.root->left->num, "2", "h2.root->left->num==2");
	check(h2.root->right->suit, 'h',"h2.root->right->suit==h");
	check(h2.root->right->num, "k","h2.root->right->num==k");
}
//~Player();
void testPlayerDestructor(){
	startTestGroup("testPlayerDestructor");
	
	Player* h1 = new Player;
        h1->root=new Player::Card('d',"a");
        h1->root->left=new Player::Card('c',"j");
        h1->root->left->parent=h1->root;
	delete h1;
	
	testAlert(string("A filled Player object, h1, was just deleted. If there are no memory leaks or errors,\n"
		  	 + string("then the destructor is working properly.")));
	Player* h2 = new Player;
	delete h2;
	
	testAlert(string("An empty Player object, h2, was just deleted. If there are no memory leaks or errors,\n"
			+ string("then the destructor is working properly.")));
}

	//----Mutator functions----
	

//void insert(const char& suit, const string& num);
void testPlayerinsert(){
	startTestGroup("testPlayerinsert");

	Player h1;
	h1.insert('d',"a");
	h1.insert('c',"2");
	
	check(h1.root->suit, 'd', "h1.root->suit==d");
	check(h1.root->num, "a", "h1.root->num==a");
	check(h1.root->left->suit, 'c', "h1.root->left->suit==c");
	check(h1.root->left->num, "2", "h1.root->left->num==2");
}
//bool discard(const char& suit, const string& num);
void testPlayerdiscard(){
	startTestGroup("testPlayerdiscard");

	startSubTestGroup("Regular case: discard smallest Card");
		Player h1;
		h1.insert('d',"a"); h1.insert('d',"j"); h1.insert('c',"k");
		h1.discard('c',"k");

		check(h1.root->left==NULL,"h1.root->suit==NULL");
		check(h1.root->suit,'d',"h1.root->suit==d");
		check(h1.root->num,"a","h1.root->num==a");

	startSubTestGroup("Regular case: discard largest Card");
		Player h2;
		h2.insert('d',"a"); h2.insert('h',"j"); h2.insert('c',"k");
		h2.discard('h',"j");

		check(h2.root->right==NULL,"h2.root->right==NULL");
		check(h2.root->suit,'d',"h2.root->suit==d");
		check(h2.root->num,"a","h2.root->num==a");

	startSubTestGroup("Regular case: discard Card that has a parent and only one child");
		Player h3;
		h3.insert('d',"a"); h3.insert('d',"j"); h3.insert('d',"k");
		h3.discard('d',"j");

		check(h3.root->suit,'d',"h3.root->suit==d");
		check(h3.root->num,"a","h3.root->num==a");
		check(h3.root->right->suit,'d',"h3.root->right->suit==d");
		check(h3.root->right->num,"k","h3.root->right->num==j");
	
	startSubTestGroup("Regular case: discard Card that has a parent and two children");
		Player h4;
		h4.insert('d',"a"); h4.insert('d',"j"); h4.insert('d',"10"); h4.insert('d',"k");
		h4.discard('d',"j");
		
		check(h4.root->suit,'d',"h4.root->suit==d");
		check(h4.root->num,"a","h4.root->suit==a");
		check(h4.root->right->suit,'d',"h4.root->right->suit==d");
		check(h4.root->right->num,"k","h4.root->suit-right->num==k");
		check(h4.root->right->left->suit,'d',"h4.root->right->left->suit==d");
		check(h4.root->right->left->num,"10","h4.root->right->left->num==10");

	startSubTestGroup("Regular case: discard Card that is the root");
		Player h5;
                h5.insert('d',"a"); h5.insert('d',"j"); h5.insert('d',"10"); h5.insert('c',"k"); 
		h5.discard('d',"a");

                check(h5.root->suit,'d',"h5.root->suit==d");
                check(h5.root->num,"10","h5.root->suit==j");
                check(h5.root->right->suit,'d',"h5.root->right->suit==d");
                check(h5.root->right->num,"j","h5.root->suit-right->num==10");
                check(h5.root->left->suit,'c',"h5.root->left->suit==c");
                check(h5.root->left->num,"k","h5.root->left->num==k");

	startSubTestGroup("Regular case: discard called, but no matching Card is found. EXPECT: No actual discard happens");
		Player h6;
		h6.insert('d',"a");
		h6.discard('d',"j");
	
		check(h6.root->suit,'d',"h6.root->suit==d");
		check(h6.root->num,"a","h6.root->num==a");

	startSubTestGroup("Edge case: discard called on empty Player. EXPECT: No discarding happens");
		Player h7;
		h7.discard('d',"a");

		check(h7.root==NULL,"h7.root==NULL");
	startSubTestGroup("Edge case: discard called on leaf Card that is also pointed to by selected. EXPECT: select moves to parent");
		Player p8;
		p8.insert('d',"a");
		p8.insert('d',"j");
		p8.selected=p8.root->right;
		p8.discard('d',"j");
		
		check(p8.selected->suit,'d',"p8.selected->suit==d");
		check(p8.selected->num,"a","p8.selected->suit==j");
}
//bool selectSuccessor();
void testPlayerselectSuccessor(){
	startTestGroup("testPlayerselectSuccessor");
	
	startSubTestGroup("Regular case: simply select the next larger Card");
		Player h1;
	        h1.insert('d',"a"); h1.insert('d',"6");
		
		check(h1.selectSuccessor()==true, "h1.selectSuccessor()==true");
		check(h1.selected->suit, 'd', "h1.selected->suit==c");
		check(h1.selected->num, "6", "h1.selected->num==6");
	
	startSubTestGroup("Edge case: when no successor exists, set selected to NULL. EXPECT: selected==NULL && selectSuccessor==false");
		Player h2;
		h2.insert('d',"a");
		check(h2.selectSuccessor()==false, "h2.selectSuccessor()==false");
		check(h2.selected==NULL,"h2.selected==NULL");

	startSubTestGroup("Edge case: when function called when selected=NULL, EXPECT: selected==NULL && selectSuccessor==false");
		Player p3;
		check(p3.selectSuccessor()==false,"p3.selectSuccessor()==false");
		check(p3.selected==NULL,"p3.selected==NULL");
		
}
//bool selectPredecessor();
void testPlayerselectPredecessor(){
	startTestGroup("testPlayerselectPredecessor");
	
	startSubTestGroup("Regular case: simply select the next smaller Card");
		Player h1;
	        h1.insert('c',"10"); h1.insert('c',"6");
		
		check(h1.selectPredecessor()==true, "h1.selectPredecessor()==true");
		check(h1.selected->suit, 'c', "h1.selected->suit==c");
		check(h1.selected->num, "6", "h1.selected->num==6");
	
	startSubTestGroup("Edge case: when no predecessor exists, set selected to NULL. EXPECT: selected==NULL && selectPredeccessor==false");
		Player h2;
		h2.insert('d',"a");
		check(h2.selectPredecessor()==false, "h2.selectPredecessor()==false");
		check(h2.selected==NULL,"h2.selected==NULL");

	startSubTestGroup("Edge case: when function called when selected=NULL, EXPECT: selected==NULL && selectPredeccessor==false");
		Player p3;
		check(p3.selectPredecessor()==false,"p3.selectPredecessor()==false");
		check(p3.selected==NULL,"p3.selected==NULL");
}
//bool selectSmallest();
void testPlayerselectSmallest(){
	startTestGroup("testPlayerselectSmallest");

	startSubTestGroup("Regular case: simply select smallest Card");
		Player p1;
		p1.insert('d',"a"); p1.insert('d',"6"); p1.insert('c',"a"); p1.insert('c',"2");
		check(p1.selectSmallest()==true,"p1.selectSmallest()==true");
		check(p1.selected->suit,'c',"p1.selected->suit==c");
		check(p1.selected->num,"a","p1.selected->num==a");

	startSubTestGroup("Edge case: calling function on empty Player. EXPECT: selected==NULL, selectSmallest()==false");
		Player p2;
		check(p2.selectSmallest()==false,"p2.selectSmallest()==false");
		check(p2.selected==NULL,"p2.selected==NULL");
}
//bool selectLargest();
void testPlayerselectLargest(){
	startTestGroup("testPlayerselectLargest");

	startSubTestGroup("Regular case: simply select largest Card");
		Player p1;
		p1.insert('d',"a"); p1.insert('d',"6"); p1.insert('c',"a"); p1.insert('c',"2");
		check(p1.selectLargest()==true,"p1.selectLargest()==true");
		check(p1.selected->suit,'d',"p1.selected->suit==c");
		check(p1.selected->num,"6","p1.selected->num==a");

	startSubTestGroup("Edge case: calling function on empty Player. EXPECT: selected==NULL, selectLargest()==false");
		Player p2;
		check(p2.selectLargest()==false,"p2.selectSmallest()==false");
		check(p2.selected==NULL,"p2.selected==NULL");
}
//Player& operator=(const Player& h);
void testPlayeroperatorEquals(){
	startTestGroup("testPlayeroperatorEquals");

	Player h1;
        h1.insert('s',"10"); h1.insert('h',"9"); h1.insert('h',"10");
	
	startSubTestGroup("Case: Copying filled Player onto filled Player");
		Player p2;
		p2.insert('c',"k");
		p2=h1;
		check(p2.root->suit,'s',"p2.root->suit==s");
		check(p2.root->num,"10","p2.root->num==10");
		check(p2.root->right->suit,'h',"p2.root->right->suit==h");
                check(p2.root->right->num,"9","p2.root->right->num==9");
		check(p2.root->right->right->suit,'h',"p2.root->right->right->suit==h");
		check(p2.root->right->right->num,"10","p2.root->right->right->num==10");
		check(p2.selected==p2.root,"p2.selected==p2.root");

	startSubTestGroup("Case: Copying filled Player onto empty Player");	
		Player p3;
		p3 = h1;
		check(p3.root->suit,'s',"p3.root->suit==s");
                check(p3.root->num,"10","p3.root->num==10");
                check(p3.root->right->suit,'h',"p3.root->right->suit==h");
                check(p3.root->right->num,"9","p3.root->right->num==9");
                check(p3.root->right->right->suit,'h',"p3.root->right->right->suit==h");
                check(p3.root->right->right->num,"10","p3.root->right->right->num==10");
		check(p3.selected==p3.root,"p3.selected==p3.root");

	startSubTestGroup("Case: Copying empty Player onto filled Player");
		Player p4;
		h1=p4;
		check(h1.root==NULL, "h1.root==NULL");
		check(h1.selected==NULL,"h1.selected==NULL");

	startSubTestGroup("Case: Copying empty Player onto empty Player");
		Player p5;
		Player p6;
		p5=p6;
		check(p5.root==NULL,"p5.root==NULL");
		check(p5.selected==NULL,"p5.selected==NULL");
}


	//----Const Functions----
	

//bool search(const char& suit, const char& num) const;
void testPlayersearch(){
	startTestGroup("testPlayersearch");
	
	startSubTestGroup("Case: searching for a Card in empty Player");
		Player p1;
		check(p1.search('d',"a")==false, "p1.search(d,a)==false");

	startSubTestGroup("Case: searching for a Card with suit and num NOT in Player");
		Player p2;
		p2.insert('d', "a");
		check(p2.search('c',"j")==false, "p2.search(c,j)==false");

	startSubTestGroup("Case: searching for a Card that IS in Player");
		Player p3;
		p3.insert('d',"a");
		check(p3.search('d',"a")==true, "p3.search(d,a)==true");
}
//void showAll() const;
void testPlayershowAll(){
	startTestGroup("testPlayershowAll");
	
	Player p1;
	p1.insert('d',"a"); p1.insert('c',"j"); p1.insert('h',"q");
	p1.showAll();
	testAlert("MANUAL test: Did the h1.showAll() print out\nc, j\nd, a\nh, q\n");
	
	Player p2;
	p2.insert('d',"a");
	p2.showAll();
	testAlert("MANUAL test: Did the h2.showAll() print out\nd, a\n");
}
//bool isEmpty() const;
void testPlayerisEmpty(){
	startTestGroup("testPlayerisEmpty");
	
	Player h1;
	h1.insert('d',"a");
	check(h1.isEmpty()==false, "h1.isEmpty()==false");
	
	Player h2;
	check(h2.isEmpty()==true, "h2.isEmpty()==true");
}
//char getSelectSuit() const;
void testPlayergetSelectSuit(){
	startTestGroup("testPlayergetSelectSuit");

	Player h1;
	h1.insert('d',"a");
	check(h1.getSelectSuit()== 'd',"h1.getSelectSuit()==d");
}
//char getSelectNumber() const;
void testPlayergetSelectNumber(){
	startTestGroup("testPlayergetSelectNumber");

	Player h1;
	h1.insert('d',"a");
	check(h1.getSelectNumber()=="a","h1.getSelectSuit()==a");
}
//bool noSelected() const;
void testPlayernoSelected(){
	startTestGroup("testPlayernoSelected");

	Player h1;
	check(h1.noSelected()==true,"h1.noSelected()==true");
	h1.insert('d',"a");
	h1.noSelected();
	check(h1.noSelected()==false,"h1.noSelected()==false");

	Player h2;

	h2.insert('d',"a");
	check(h2.noSelected()==false,"h2.noSelected()==false");
}

void testPlayer(){
	//Print out Player test title
	startMainTestGroup("Player");
	
	//Player test functions
	testPlayerDefault();	
	testPlayerParams();
	testPlayerDestructor();
	testPlayerinsert();
	testPlayerdiscard();
	testPlayerselectSuccessor();
	testPlayerselectPredecessor();
	testPlayerselectSmallest();
	testPlayerselectLargest();
	testPlayeroperatorEquals();

	testPlayersearch();
	testPlayershowAll();
	testPlayerisEmpty();
	testPlayergetSelectSuit();
	testPlayergetSelectNumber();
	testPlayernoSelected();	
}

int main(){
	testPlayer();
	return 0;
}

