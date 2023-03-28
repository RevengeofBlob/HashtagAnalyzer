/* File:	proj1.cpp
 * Project:	Project 1
 * Author:	Ryan Baker
 * Date:	9/23/22
 * Section:	50/53
 * E-mail:	rbaker8@umbc.edu
 * Description:	Main file for project 1. User inputs a file of hashtags and a file with equal number of hashtags
 *		and messages. Displays each message and the amount of times each hashtag is represented.
 */

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX_SIZE = 20; 	// The max number of elements in each array.
const int CHECK_NULL = 0; 	// Used to check if the first index is empty.

void loadMessages(string fileName, string messageArr[]);
void loadHashes(string fileName, string hashArr[]);
void processMessages(string hashArr[], string messagesArr[], int numHashes[]);
void reset(string hashes[], string messages[], int numHashes[]);
void displayCounts(string hashArr[], int numHashes[]);
void displayMessages(string hashArr[], string messageArr[]);
int numAppearances(string hash, string messageArr[]);

int main(){
  string hashFile; 		// Name of the hashtag file.
  string hashes[MAX_SIZE]; 	// An array to hold the hashtags from hashFile.
  string messageFile; 		// Name of the message file.
  string messages[MAX_SIZE]; 	// An array to hold the hashtags and messages from messageFile.
  string playAgain = "y"; 	// Used to enter/repeat the while loop.
  int hashCount[MAX_SIZE] = {};	// The matching count array for the hashtags.
  
  while (playAgain == "y"){
    reset(hashes, messages, hashCount);

    cout << "Welcome to the Hashtag Analyzer\n"
	 << "You will choose a file of hashtags to search for\n"
	 << "Then you will choose a file to search for the hashtags\n"
	 << "Please enter the file with the hashtags you would like to use:\n";
    cin >> hashFile;

    // Attempts to load in hashtags from the given file.
    // If nothing is inputted into the array, ask for another file.
    do {
      loadHashes(hashFile, hashes);
      if (hashes[CHECK_NULL] == ""){
	cout << "Please enter a nonempty file.\n";
	cin >> hashFile;
      }
    } while (hashes[CHECK_NULL] == "");

    cout << "Please enter the file with the messages you would like to parse:\n";
    cin >> messageFile;

    // Attempts to load in hashtags and messages from the given file.
    // If nothing is inputted into the array, ask for another file.
    do {
      loadMessages(messageFile, messages);
      if (messages[CHECK_NULL] == ""){
	cout << "Please enter a nonempty file.\n";
	cin >> messageFile;
      }
    } while (messages[CHECK_NULL] == "");

    cout << "Your file was imported!\n";
    cout << "Your file was imported!\n";

    processMessages(hashes, messages, hashCount);
    displayMessages(hashes, messages);
    displayCounts(hashes, hashCount);
    
    cout << "Would you like to analyze another file? (y/n)\n";
    cin >> playAgain;
  }

  cout << "Thank you for using the hashtag analyzer!\n";
  return 0;
}

//Function Name: loadMessages
//Pre-Condition: fileName ends in .txt and messageArr is empty.
//Post-Condition: Each even index in messageArr is a hashtag and each odd index is a message.
//Description: Loads in the messages and inputs them into the message array.
void loadMessages(string fileName, string messageArr[]){
  string message;     	// An entire line of text.
  string hash; 	  	// One connect block starting with '#'.
  ifstream messageFile;	// An input file containing messages and hashtags.
  int index = 0; 	// Index that the current message/hash will go into.
  int count = 0;	// The number of message/hashtag pairs.
  
  messageFile.open(fileName);

  // Goes through each line in the input file.
  // For each pair of lines, the first line is inputted into hash and the second into message.
  while(getline(messageFile, hash, '\n'), getline(messageFile, message, '\n')){
    messageArr[index] = hash;
    index++;
    messageArr[index] = message;
    index++;
    count++;
  }

  if (count > 0){
    cout << count << " messages have been loaded.\n";
  }
  
  messageFile.close();
}

//Function Name: loadHashes
//Pre-Condition: fileName ends in .txt and hashArr is empty.
//Post-Condition: Each line in fileName inputted into hashArr.
//Description: Loads in the hashtags and inputs them into the hashtag array.
void loadHashes(string fileName, string hashArr[]){
  string hash; 		// A line of text starting with #.
  ifstream hashFile; 	// An input file containing hashtags.
  int index = 0; 	// Index that the current hashtag will go into.
  int count = 0;	// The number of hashtags.
  
  hashFile.open(fileName);

  // Goes through each line of the hashtag file and inputs the line into hashArr.
  while(hashFile >> hash){
    hashArr[index] = hash;
    index++;
    count++;
  }

  if (count > 0){
    cout << index << " hashtags have been loaded.\n";
  }
  
  hashFile.close();
}

//Function Name: processMessages
//Pre-Condition: hashArr and messageArr are nonempty and each index in numHashes is 0.
//Post-Condition: The values in numHashes add up to the ammount of messages with hashtags in hashArr.
//Description: Iterates over the messages to see if any message match the hashtag.
void processMessages(string hashArr[], string messagesArr[], int numHashes[]){
  string hash; 	// The current hashtag being checked.

  // For each hashtag, check to see how many times it appears in messageArr and set the value in numHashes to the number of appearances.
  for (int i = 0; i < MAX_SIZE; i++){
    hash = hashArr[i];
    numHashes[i] = numAppearances(hash, messagesArr); 
  }
}

//Function Name: reset
//Pre-Condition: hashes[] and messages[] is a string array.
//Post-Condition: Each index of hashes, messages, and numHashes is its zero value.
//Description: Iterate through each index of hashes, messages, numHashes and set each of the values to the zero value.
void reset(string hashes[], string messages[], int numHashes[]){
  for (int i = 0; i < MAX_SIZE; i++){
    hashes[i] = "";
    messages[i] = "";
    numHashes[i] = 0;
  }
}

//Function Name: displayCounts
//Pre-Condition: Each index in hashArr and numHashes has a value.
//Post-Condition: None.
//Description: Displays each hashtag and the amount of messages with the corresponding hashtag.
void displayCounts(string hashArr[], int numHashes[]){
  
  // Iterates through each hashtag in hashArr and outputs a numbered list of each hashtag and their corresponding amounts.
  for (int i = 0; i < MAX_SIZE; i++){
    cout << setw(2) << right << i + 1 << setw(20) << right << hashArr[i] << setw(5) << right << numHashes[i] << "\n";
  }
}

//Function Name: numAppearances
//Pre-Condition: hash starts with '#' and messageArr is a nonempty array
//Post-Condition: count either increases or stays the same.
//Description: Counts the amount of times hash appears in messageArr
int numAppearances(string hash, string messageArr[]){
  int count = 0; // Amount of times the hashtag appears in messageArr.

  //Iterates through messageArr. If hash matches the string, increment count by one.
  for (int i = 0; i < MAX_SIZE - 2; i++){
    if(messageArr[i] == hash){
      count++;
    }
  }
  
  return count;
}

//Function Name: displayMessages
//Pre-Condition: Each index in hashArr has a value and there are en equal amount of hashtags and messages in messageArr.
//Post-Condition: None.
//Description: Iterates through messageArr. If the hashtag is in hashArr, outputs the hashtag followed by the corresponding message.
void displayMessages(string hashArr[], string messageArr[]){
  int messageNum = 1; // Which message is being outputted

  cout << "Messages with matching hashtags\n";

  // Iterates through each hashtag in messageArr and hashArr.
  // If the hashtag from the message array is in the hash array, output the hashtag with its corresponding message.
  for (int i = 0; i < MAX_SIZE - 1; i += 2){
    if (messageArr[i] != ""){
      for (int k = 0; k < MAX_SIZE; k++){
	if (messageArr[i] == hashArr[k]){
	  cout << messageNum << setw(5) << left << "." << messageArr[i] << " " << messageArr[i + 1] << "\n";
	  messageNum++;
	}
      }
    }
  }
}
