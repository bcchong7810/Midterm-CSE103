/*Please add citations for cin.ignore()
 * for list of 10,000 words from MIT
 * for list of most common words
 * Zybooks 9.5
 */

#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <fstream> //Zybooks 9.5 File input

using namespace std;

int main() {
    //Obtaining the key

    ifstream dataFS; //filestream creation
    dataFS.open("4.txt"); //opens fstream to read encrypted message

    string keyword; //temporary holder for keyword
    vector<string> keywords; //builds vector of keywords

    string encryptedMessage;
    vector<char> encryptedChar;
    vector<char> decryptedChar;
    vector<int> alphabet(26); //Vector to hold frequencies


    getline(dataFS, encryptedMessage); //fstream reads encrypted message maybe change if input is different
    dataFS.close();
    dataFS.clear();

    //Below is the logic for the frequency analysis

    for (unsigned int i = 0; i < encryptedMessage.length(); i++) { //Encrypted message in 1 long string
        if (isalpha(encryptedMessage.at(i))) {
            encryptedChar.push_back(encryptedMessage.at(i));
        }
    }

    //Cycles through encryptedChar to check input
    /* for (unsigned int i = 0; i < encryptedChar.size(); i++) {
        cout << encryptedChar.at(i);
    } */


    //Alphabet frequency holder
    /*for (unsigned int i = 0; i < alphabet.size(); i++) { //65 is A, 26 characters, range is 0-25
        for (unsigned int j = 0; j < encryptedChar.size(); j++) {
            if (65 + i == static_cast<unsigned int>(encryptedChar.at(j))) {
                alphabet.at(i)++;
            }
        }
    }
    cout << endl;


    cout << "-------------------------Frequency Analysis-------------------------" << endl;
    for (unsigned int i = 0; i < alphabet.size(); i++) { //Frequency analysis report
        cout << static_cast<char>(i+65) << ": " << alphabet.at(i) << endl;
    } */

    //Turning keys.txt into vector of keywords
    dataFS.open("keys.txt");
    while (!dataFS.eof() && dataFS.good()) {
        dataFS >> keyword;
        keywords.push_back(keyword);
    }

    /* DELETE ME
    //Test to see if data is corrupted
    if (dataFS.fail()) {
        cout << "Failure is beneath Doom.";
    } */

    dataFS.close();
    dataFS.clear();

    //Capitalization of lowercase to upperuppercase
    for (unsigned int i = 0; i < keywords.size(); i++) {
        for (unsigned int j = 0; j < keywords.at(i).size(); j++) {
            keywords.at(i).at(j) = toupper(keywords.at(i).at(j));
        }
    }

    //Brute force decryption of original statement OUTPUT
    /* for (unsigned int i = 0; i < keywords.size(); i++) { //Iterate through list of keywords
        for (unsigned int j = 0; j < encryptedChar.size(); j++) { //Iterate through string in keywords AND in length of text
            if ((encryptedChar.at(j) - (keywords.at(i).at(j % keywords.at(i).length()))) < 0) {
                cout << static_cast<char>((encryptedChar.at(j) - (keywords.at(i).at(j % keywords.at(i).length()))) + 91); //Underflow
            } else {
                cout << static_cast<char>(encryptedChar.at(j) - (keywords.at(i).at(j % keywords.at(i).length())) + 65); //Overflow
            }
            //Encrypted - key = original
        }
        cout << endl << endl;
    } */

    //Keyword
    //cout << keywords.at(25) << endl;

    //Decryption algorithm specifically for index 25 (REPAIR)
    for (unsigned int i = 0; i < encryptedChar.size(); i++) {
        if (encryptedChar.at(i) - keywords.at(25).at(i % keywords.at(25).length()) < 0) {
            decryptedChar.push_back((encryptedChar.at(i) - keywords.at(25).at(i % keywords.at(25).length())) + 91);
        } else {
            decryptedChar.push_back((encryptedChar.at(i) - keywords.at(25).at(i % keywords.at(25).length())) + 65);
        }
    }

    //Print out of mashed character vector
    /*
    for (unsigned int i = 0; i < decryptedChar.size(); i++) {
        cout << decryptedChar.at(i);
    }
    cout << endl;
    */


   	//Keyword Vector test with human eyes
    /*for (unsigned int i = 0; i < keywords.size(); i++) {
        cout << keywords.at(i) << endl;
    } */

    //Top common english words to look for the match

    /* SPACE MAKER
     * To avoid prefixes and cutting off suffixes from the list of 10,000 words,
     * we will process the sentence backwards which requires a backwards.
     * This requires a backwards list of 10,000! */
    string mitWord;
    string reverseMITWord;
    vector<string> mitWords;
    vector<string> reverseMITWords;
    vector<char> reverseDecryptedChar;

    dataFS.open("MIT.txt");
    while (!dataFS.eof() && dataFS.good()) {
        dataFS >> mitWord;
        if (mitWord.length() < 2) {
            continue;
        }
        mitWords.push_back(mitWord);
        if (dataFS.bad()){
            cout << "Failure is beneath Doom.";
            break;
        }
    }
    dataFS.close();
    dataFS.clear();


    //MIT word checker
    /*
    for (unsigned int i = 0; i < mitWords.size(); i++) {
        cout << mitWords.at(i) << " ";
    } */

    //Word reverser
    /*
    for (unsigned int i = 0; i < mitWords.size(); i++) {
        reverseMITWord = "";
        for (int j = mitWords.at(i).size() - 1; j >= 0; j--) {
            reverseMITWord.push_back(toupper(mitWords.at(i).at(j)));
        }
        reverseMITWords.push_back(reverseMITWord);
    } */


    //Word reverser checker
    /*
    for (unsigned int i = 0; i < reverseMITWords.size(); i++) {
        cout << reverseMITWords.at(i) << " ";
    } */

    //Decrypted message reverser
    /*
    for (int i = decryptedChar.size() - 1; i >= 0; i--) {
        reverseDecryptedChar.push_back(decryptedChar.at(i));
    }*/

    //Reversed decrypted message test
    /* for (int i = 0; i < reverseDecryptedChar.size(); i++) {
        cout << reverseDecryptedChar.at(i);
    } */

    //space finder
    /*
    string comparedWord;
    vector<int> spaces;
    vector<char> sRDC; //Spaced Reverse Decrypted Char
    for (unsigned int i = 0; i < reverseMITWords.size(); i++) {
        comparedWord = reverseMITWords.at(i);
        for(unsigned int j = 0; j < reverseDecryptedChar.size(); j++) {
            if (comparedWord.at(j) != reverseDecryptedChar.at(j)) {
                break;
            } else if(comparedWord.at(j) == comparedWord.length() - 1) {
                spaces.push_back(j);
            }
        }
    }

    for (unsigned int i = 0; i < spaces.size(); i++) {
        cout << spaces.at(i);
    }

    cout << "Program completed." << endl;
    */



    //User varaiables
    /*
    string user;
    char quit = 'n';
    string key;
    vector<char> encryptedMessage;
    string newMessage;

    while (quit != 'y') {
        break;
        cout << "Are you Alice, Bob, or Eve?\n";
        getline(cin, user);

        while (user != "Alice" && user!= "Bob" && user!= "Eve"){
            cout << "Pick a valid user please!\n";
            getline(cin, user);
        }
        cout << "Welcome, " << user << "! ";

        //Decryption, message sender
        if (user == "Alice") {
            char answer;
            cout << "Okay, what is your message? ";
            getline(cin, newMessage);
            cout << "\"" << newMessage << "\"" << "| Is this the correct message to send? (y/n) ";
        */
            /* Confirmation below: */
            /*
            cin >> answer;
            while (tolower(answer) != 'y') {
                cin.ignore(); //cin.ignore() citation
                cout << "Please enter the correct message, " << user << ". ";
                getline(cin, newMessage);
                cout <<"\"" << newMessage << "\"" <<"| Is this the message you want to send? (y/n) ";
                cin >> answer;
            }

            for (unsigned int i = 0; i < newMessage.length(); i++) {
                if (newMessage.at(i) != ' ') {
                    encryptedMessage.push_back(newMessage.at(i));
                }
            } */

            /* Vector of characters checker
            for (unsigned int i = 0; i < encryptedMessage.size(); i++) {
                cout << encryptedMessage.at(i);
            } */

            //Encryption algorithm

        /*
        } else if (user == "Bob") {
            //
        } else if (user == "Eve") {
            quit = 'y';
            cout << "Shouldn't you speak to Adam? Stop trying to intercept messages. There are no secret messages here.\n";
            break;
        }

        cout << "Would you like to quit? (y/n)\n";
        cin >> quit;
        quit = static_cast<char>(tolower(quit));



        while (quit != 'y' && quit!= 'n') {
            cout << "Please input a valid response! Would you like to quit? (y/n)\n";
            cin >> quit;
            quit = static_cast<char>(tolower(quit));
        }
    } */
    return 0;
}
