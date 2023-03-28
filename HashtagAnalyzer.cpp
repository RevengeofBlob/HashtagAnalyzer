/*File:proj1.cpp
 * Procjet:Project 1
 * Author:Ryan Baker
 * Date:2/27/22
 * E-mail:rbaker8@umbc.edu
 * Description: Word guessing program where users have six attempts to guess a random five-letter word.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>

const int MAX_GUESSES = 6; //Number of words the user can guess.
const int LETTERS = 5; //The amount of letters the word has.
const char CORRECT_SPACE = '!'; //Character to represent a letter is in the word and in the right spot.
const char IN_WORD = '?'; //Character to represent a letter is in the word but not in the right spot.
const int WORD_LIST_SIZE = 2315; //The amount of words in the list.

void runner();
void loadWordList(std::string wordArr[]);
std::string guessWord(std::string wordArr[]);
void resetGame();
std::string chooseWord(std::string words[]);
void displayGame(std::string guess[], std::string lines[], std::string mysteryWord);

int main() {

  std::cout << "Welcome to UMBC Wordle!\nYou have 6 tries to guess a 5 letter word. Good Luck!\n";
  runner();

  return 0;
}

//Main hub for the game and function calls.
void runner() {
  std::string guess; //5-letter word the user enters.
  int guesses = 0; //How many words have been guesed.
  std::string guessedWords[MAX_GUESSES]; //Creates an empty array to store the guessed words in.
  std::string spaces[MAX_GUESSES] = { "_____", "_____", "_____", "_____", "_____", "_____"}; //Array of lines corresponding to each word and each of the word's position.
  std::string wordList[WORD_LIST_SIZE]; //Creates an empty array to store all the words from the .txt file in.

  loadWordList(wordList);
  std::string word = chooseWord(wordList); //Sets word to a random word from wordList every time this function is called.
  
  //Asks user for their guess and displays the game board until the word has been guessed or they have reached the max guesses.
  do{
    guess = guessWord(wordList);
    guessedWords[guesses] = guess;
    guesses++;
    displayGame(guessedWords, spaces, word);
  } while ((guess != word) && (guesses < MAX_GUESSES));

  if (guess == word){
    std::cout << "Congratulations on guesing the word!\n";
  }
  else{
    std::cout << "Better luck next time!\n";
  }
  
  resetGame();
}

//Loads in the word list and puts the words into an array.
void loadWordList(std::string wordArr[]) {
  std::ifstream wordList;
  wordList.open("proj1_data.txt");
  std::string nextWord; //temp variable to store individual words from the .txt file.

  //Goes through each word and adds it to the array.
  for (int i = 0; i < WORD_LIST_SIZE; i++) {
    if (wordList >> nextWord) {
      wordArr[i] = nextWord;
    }
  }

  wordList.close();
}

//User guesses word and validates that it is in the word list.
std::string guessWord(std::string wordArr[]) {
  std::string newGuess; //Stores the input from user.
  bool inList = false; //Flag for if the input is in the array.

  //Asks user for a word until they enter one that is in the array.
  while (!inList){
    std::cout << "Guess a word!\n";
    std::cin >> newGuess;
    for (int i = 0; i < WORD_LIST_SIZE; i++){
      if (newGuess == wordArr[i]){
	inList = true;
      }
    }
    if (!inList){
      std::cout << "Word entered not in list\n";
    }
  }
  
  return newGuess;
}

//Asks if user wants to play again, if so, starts another game with a new word.
void resetGame(){
  std::string playAgain;
  std::cout << "Would you like to play again? 'y/n'\n";
  std::cin >> playAgain;

  if (playAgain == "y"){
    runner();
  }
  else{
    std::cout << "Thanks for playing!\n";
  }
}

//Generates a random word using an array of words.
std::string chooseWord(std::string words[]){
  std::string word; //String that will be assigned a random word from the array

  //Selects a random word from the array and assigns it to word.
  srand(time(NULL));
  word = words[rand() % WORD_LIST_SIZE];
  
  return word;
}

//Compares each guess and the mystery word and changes each letter's representation in line depending on if it is correct and/or in the correct spot.
void displayGame(std::string guesses[], std::string lines[], std::string mysteryWord){
  std::string guess; //Will be assigned to any non-empty string in guesses array.

  //Goes through each non-empty string in guesses and compares it to the mystery word.
  for (int i = 0; i < MAX_GUESSES; i++){
    if (guesses[i] != ""){
      guess = guesses[i];
      //Sets each character in lines[] depending on its correctness and position.
      //Nothing changes is a letter is not in the mystery word.
      for (int j = 0; j < LETTERS; j++){
	for (int k = 0; k < LETTERS; k++){
	  if (guess[j] == mysteryWord[k]){
	    if (j == k){
	      lines[i][j] = CORRECT_SPACE;
	    }
	    else{
	      lines[i][j] = IN_WORD;
	    }
	  }
	}
      }
      std::cout << guess + "\n";
    }
    std::cout << lines[i] + "\n";
  }
}
