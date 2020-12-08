# **THE GAME:**  
Alice and Bob are playing a game a bit like Go Fish, although neither of them is very good at it. Rather than randomly guessing what card the other person has, they take turns to find a matching card. Each player goes through their list of cards in order and asks the other player to list all of their cards in order until a match is found. However, Alice starts from the leftmost card while Bob starts from the rightmost card in hand. The game ends once they do not have any cards in common. Note that they do not draw any new cards during this process.

# **HOW TO USE:** 
Download the files and keep them in the same folder in the UNIX environment. Call "make game" and then "./game &lt; text file &gt; &lt; text file &gt;" to run the game. It will output all the matches that Alice and Bob make, then print out the remainder of their held cards. For testing purposes, call "make tests" and then "./tests" to run all the tests on functions of cards.cpp.

# **FILES:**  
* "Makefile" is the makefile to make the executables game and tests.
* "cards.cpp" contains the custom BST data structure used in the game.
* "cards.h" is the header file of cards.cpp.
* "main.cpp" is the actual implementation of the game using functions from cards.cpp.
* "tests.cpp" contains the testing methods.
* "utility.cpp" and "utility.h" were for misc. helper implementations, but ended up being unused.
* "*.txt" files are the ones formatted to work as inputs with game.
