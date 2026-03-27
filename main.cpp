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

    //Prints encryptedChar
    /*
    for (unsigned int i = 0; i < encryptedChar.size(); i++) {
        cout << encryptedChar.at(i);
    }*/


    //Alphabet frequency holder
    for (unsigned int i = 0; i < alphabet.size(); i++) { //65 is A, 26 characters, range is 0-25
        for (unsigned int j = 0; j < encryptedChar.size(); j++) {
            if (65 + i == static_cast<unsigned int>(encryptedChar.at(j))) {
                alphabet.at(i)++;
            }
        }
    }
    cout << endl;


    cout << "-------------------------Frequency Analysis of the Original Decrypted Message-------------------------" << endl;
    for (unsigned int i = 0; i < alphabet.size(); i++) { //Frequency analysis report
        cout <<static_cast<char>(i + 65) << ": " << alphabet.at(i) << "| ";
    }
    cout << endl;

    //Turning keys.txt into vector of keywords
    dataFS.open("keys.txt");
    while (!dataFS.eof() && dataFS.good()) {
        dataFS >> keyword;
        keywords.push_back(keyword);
    }
    dataFS.close();
    dataFS.clear();

    //Test to see if data is corrupted
    if (dataFS.fail()) {
        cout << "Failed to input keys.txt";
    }


    //Capitalization of lowercase to upperuppercase for keywords
    for (unsigned int i = 0; i < keywords.size(); i++) {
        for (unsigned int j = 0; j < keywords.at(i).size(); j++) {
            keywords.at(i).at(j) = toupper(keywords.at(i).at(j));
        }
    }

    //Brute force decryption of original statement OUTPUT
    /*
    for (unsigned int i = 0; i < keywords.size(); i++) { //Iterate through list of keywords
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

    //Top common english words to look for the match
    // Approximately 48 words with some added like where when why
    vector<string> commonWords = {"THE", "AND", "THAT", "HAVE", "FOR", "NOT", "WITH", "YOU", "BUT", "HIS", "HERE", "FROM", "THEY", "SAY", "HER", "SHE", "WILL", "ONE", "ALL", "WOULD", "THERE", "THEIR", "WHAT", "WHEN", "WHERE", "WHY", "WHICH"};
    // go through all encrypted messages and see if there is the top english words

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



    /* SPACE MAKER
     * To avoid prefixes and cutting off suffixes from the list of 10,000 words,
     * we will process the sentence backwards which requires reverser code
     * This requires a backwards list of 10,000!
     *
     * edit: Above was the initial plan, it turns out after further testing.. the spacing is weird because of suffixes and prefixes.
     * New theory: Run the code once forwards and only include MIT words that are 4 characters in length. The intuition is that most prefixes are 3 letters in size.
     * The spaces will be made behind the words _____________
     * We can clean up multiple spaces later */
    string mitWord;
    string reverseMITWord;
    string mitWordTemp;
    vector<string> mitWords;
    vector<string> mitWordsTemp; //Added to add capitalizer before reverse to prevent changing all other variables
    vector<string> reverseMITWords;
    vector<char> reverseDecryptedChar;

    //MITword looper
    string comparedWordOne;
    vector<int> spacesOne;
    vector<char> sDecryptedCharOne; //Spaced Reverse Decrypted Char

    //Modular(?) MIT word maker (add for (int i = 7; i > 5; i--))
    dataFS.open("MIT.txt");
    while (!dataFS.eof() && dataFS.good()) {
        dataFS >> mitWord;
        if (mitWord.length() < 8) {
            continue;
        }
        mitWordsTemp.push_back(mitWord);
        if (dataFS.bad()){
            cout << "Failed to input the MIT.txt";
            break;
        }
    }

    dataFS.close();
    dataFS.clear();


    //MIT word capitalizer
    for (unsigned int i = 0; i < mitWordsTemp.size(); i++) {
        mitWordTemp = "";
        for (unsigned int j = 0; j < mitWordsTemp.at(i).size(); j++) {
            mitWordTemp.push_back(toupper(mitWordsTemp.at(i).at(j)));
        }
        mitWords.push_back(mitWordTemp);
    }


    //MIT word checker
    /*
    for (unsigned int i = 0; i < mitWords.size(); i++) {
        cout << mitWords.at(i) << " ";
    } */


    //space finder1 Forwards
    /*
    for (unsigned int i = 0; i < mitWords.size(); i++) {
        comparedWordOne = mitWords.at(i);
        for (unsigned int j = 0; j < decryptedChar.size(); j++) {
            if (comparedWordOne.at(0) != decryptedChar.at(j)) {
                continue;
            } else {
                for (unsigned int k = 0; k < comparedWordOne.length(); k++) {
                    if (j + k == decryptedChar.size()) { //The MIT word might be compared is overflowing past the end of the message
                        break;
                    } else {
                        if (comparedWordOne.at(k) != decryptedChar.at(j + k)) {
                            break;
                        } else if (comparedWordOne.at(k) == decryptedChar.at(j + k) && k == comparedWordOne.length() - 1) {
                            spacesOne.push_back(j + k + 1); //j + k + 1 is where the space needs to be added
                        }
                    }
                }
            }
        }
    } */

    //Adds spaces to the sDecryptedCharOne vector
    /*
    for (unsigned int i = 0; i < decryptedChar.size(); i++) {
        for (unsigned int j = 0; j < spacesOne.size(); j++) {
            if (i == spacesOne.at(j)) {
                sDecryptedCharOne.push_back(' ');
            }
        }
        sDecryptedCharOne.push_back(decryptedChar.at(i));
    } */

    //Prints sDecryptedCharOne
    /*
    for (unsigned int i = 0; i < decryptedChar.size(); i++) {
        cout << sDecryptedCharOne.at(i);
    } */

    //Word reverser
    for (unsigned int i = 0; i < mitWords.size(); i++) {
        reverseMITWord = "";
        for (int j = mitWords.at(i).size() - 1; j >= 0; j--) {
            reverseMITWord.push_back(mitWords.at(i).at(j));
        }
        reverseMITWords.push_back(reverseMITWord);
    }


    //MIT word reverser checker
    /*
    for (unsigned int i = 0; i < reverseMITWords.size(); i++) {
        cout << reverseMITWords.at(i) << " ";
    }*/

    //Decrypted message reverser
    for (int i = decryptedChar.size() - 1; i >= 0; i--) { //Has to be int since it will dip under 0
        reverseDecryptedChar.push_back(decryptedChar.at(i));
    }

    //Reversed decrypted message test
    /*
    for (int i = 0; i < reverseDecryptedChar.size(); i++) {
        cout << reverseDecryptedChar.at(i);
    } */

    /*
    dataFS.open("MIT.txt");
    while (!dataFS.eof() && dataFS.good()) {
        dataFS >> mitWord;
        if (mitWord.length() < 4) {
            continue;
        }
        mitWords.push_back(mitWord);
        if (dataFS.bad()){
            cout << "Failed to input the MIT.txt";
            break;
        }
    }
    dataFS.close();
    dataFS.clear();
    */

    string comparedWord;
    vector<int> spaces;
    vector<char> sRDC; //Spaced Reverse Decrypted Char


    //space finder3 Backwards
    for (unsigned int i = 0; i < reverseMITWords.size(); i++) {
        comparedWord = reverseMITWords.at(i);
        for (unsigned int j = 0; j < reverseDecryptedChar.size(); j++) {
            if (comparedWord.at(0) != reverseDecryptedChar.at(j)) {
                continue;
            } else {
                for (unsigned int k = 0; k < comparedWord.length(); k++) {
                    if (j + k == reverseDecryptedChar.size()) { //The MIT word might be compared is overflowing past the end of the message
                        break;
                    } else {
                        if (comparedWord.at(k) != reverseDecryptedChar.at(j + k)) {
                            break;
                        } else if (comparedWord.at(k) == reverseDecryptedChar.at(j + k) && k == comparedWord.length() - 1) {
                            spaces.push_back(j + k + 1); //j + k + 1 is where the space needs to be added
                        }
                    }
                }
            }
        }
    }

    //Prints out where spaces will be added
    /*
    for (unsigned int i = 0; i < spaces.size(); i++){
        cout << spaces.at(i) << " ";
    } */


    //Adds spaces to the reverseDecryptedChar vector
    for (unsigned int i = 0; i < reverseDecryptedChar.size(); i++) {
        for (unsigned int j = 0; j < spaces.size(); j++) {
            if (i == spaces.at(j)) {
                sRDC.push_back(' ');
            }
        }
        sRDC.push_back(reverseDecryptedChar.at(i));
    }

    //Prints the reversedDecryptedChar Vector with spaces
    /*
    for (unsigned int i = 0; i < sRDC.size(); i++) {
        cout << sRDC.at(i);
    } */

    //Creates decrypted message with spaces
    string spaceDecryptedString;
    for (int i = sRDC.size() - 1; i >= 0; i--) { //Has to be int since it will dip under 0
        spaceDecryptedString.push_back(sRDC.at(i));
    }

    //Prints out decrypted message with spaces
    cout << endl << "Unfortunately, we ask you to add spaces as needed below while we work on this feature :(" << endl << endl << "-------------------Please double check with your human eyes below-------------------------";
    cout << endl << spaceDecryptedString << "\n\n\n";


    //User varaiables
    string user;
    char quit = 'n';

    //Alice variables
    string newMessage;
    char answer;

    //Bob variables
    string key;
    vector<char> keyChar;
    vector<char> decryptedMessageChar;
    string incomingMessage;
    vector<char> incomingMessageChar;
    vector<char> rDMC; //reverse decrypted message char
    vector<char> sRDMC; //spaced reverse decrypted message char
    string spaceDecryptedMessage;



    while (quit != 'y') {
        cout << "-------------------Booting up login sequence-------------------------\n" << "Are you Alice, Bob, or Eve? ";
        getline(cin, user);

        while (user != "Alice" && user!= "Bob" && user!= "Eve"){
            cout << "Pick a valid user please! ";
            getline(cin, user);
        }
        cout << "Welcome, " << user << "!\n\n";

        //Decryption, message sender
        if (user == "Alice") {
            cout << "Okay, what is your message? ";
            getline(cin, newMessage);
            cout << "\"" << newMessage << "\"" << "| Is this the correct message to send? (y/n) ";

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
            }

            /* Vector of characters checker
            for (unsigned int i = 0; i < encryptedMessage.size(); i++) {
                cout << encryptedMessage.at(i);
            } */

            //Encryption algorithm JUSTIN code
            string inputText;
            vector<char> plainText;
            char encryptedText;
            vector<char> cipherText;


            cout << "Plaintext: " << endl;
            getline(cin, inputText);

            for (unsigned int k = 0; k < inputText.length(); k++) {
                    plainText.push_back(toupper(inputText.at(k)));
            }

            string key = "PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS";

            for (unsigned int i = 0; i < plainText.size(); i++) {
                // check if character is alphabetical
                // shift using longest word
                // shift by 'A' to shift to ASCII values of alphabet
                if (isalpha(plainText.at(i))) {
                    if (isupper(plainText.at(i))) {
                        cipherText.at(i) = ((plainText.at(i) - 'A') + key.length()) % 26 + 'A';
                        cipherText.push_back(cipherText.at(i));
                    }
                }
                else {
                        // for non-alphabetic characters, don't shift with key
                        cipherText.at(i) = plainText.at(i);
                    }
                }

            cout << cipherText.size();

            for (unsigned int p = 0; p < cipherText.size(); p++) {
                cout << cipherText.at(p);
            }




        } else if (user == "Bob") {
            cout << user << ", What is the message you would like to decrypt? ";
            getline(cin, incomingMessage);
            cout << "\nWhat is the key? ";
            getline(cin, key);

            //Clean incomingMessage
            for (unsigned int i = 0; i < incomingMessage.size(); i++) {
                if (incomingMessage.at(i) == ' ') {
                    continue;
                } else {
                    incomingMessageChar.push_back(toupper(incomingMessage.at(i)));
                }
            }

            //prints incoming decrypted message
            /*
            for (unsigned int i = 0; i < incomingMessageChar.size(); i++) {
                cout << incomingMessageChar.at(i);
            }*/

            //Capitalize key
            for (unsigned int i = 0; i < key.size(); i++) {
                keyChar.push_back(toupper(key.at(i)));
            }

            //Print key
            /*
            for (unsigned int i = 0; i < key.size(); i++) {
                cout << keyChar.at(i);
            }*/

            //Decryption algorithm below
            for (unsigned int i = 0; i < incomingMessageChar.size(); i++) {
                if (incomingMessageChar.at(i) - keyChar.at(i % keyChar.size()) < 0) {
                    decryptedMessageChar.push_back((incomingMessageChar.at(i) - keyChar.at(i % key.size())) + 91);
                } else {
                    decryptedMessageChar.push_back((incomingMessageChar.at(i) - keyChar.at(i % key.size())) + 65);
                }
            }

            //Prints decrypted message
            /*
            for (unsigned int i = 0; i < decryptedMessageChar.size(); i++) {
                cout << decryptedMessageChar.at(i);
            }*/

            cout << endl;

            //decrypted messager reverser here
            for (int i = decryptedMessageChar.size() - 1; i >= 0; i--) {
                rDMC.push_back(decryptedMessageChar.at(i));
            }

            //spacefinder
            vector<int> bobSpaces;
            for (unsigned int i = 0; i < reverseMITWords.size(); i++) {
                comparedWord = reverseMITWords.at(i);
                for (unsigned int j = 0; j < rDMC.size(); j++) {
                    if (comparedWord.at(0) != rDMC.at(j)) {
                        continue;
                    } else {
                        for (unsigned int k = 0; k < comparedWord.length(); k++) {
                            if (j + k == rDMC.size()) { //The MIT word might be compared is overflowing past the end of the message
                                break;
                            } else {
                                if (comparedWord.at(k) != rDMC.at(j + k)) {
                                    break;
                                } else if (comparedWord.at(k) == rDMC.at(j + k) && k == comparedWord.length() - 1) {
                                    bobSpaces.push_back(j + k + 1); //j + k + 1 is where the space needs to be added
                                }
                            }
                        }
                    }
                }
            }

            //Prints reverse decrypted message
            /*
            for (unsigned int i = 0; i < rDMC.size(); i++) {
                cout << rDMC.at(i);
            } */

            //fix me?
            for (unsigned int i = 0; i < rDMC.size(); i++) {
                for (unsigned int j = 0; j < bobSpaces.size(); j++) {
                    if (i == bobSpaces.at(j)) {
                        sRDMC.push_back(' ');
                    }
                }
                sRDMC.push_back(rDMC.at(i));
            }

            //Prints the reversedDecryptedChar Vector with spaces
            /*
            for (unsigned int i = 0; i < sRDMC.size(); i++) {
                cout << sRDMC.at(i);
                }
            */

            for (int i = sRDMC.size() - 1; i >= 0; i--) { //Has to be int since it will dip under 0
                spaceDecryptedMessage.push_back(sRDMC.at(i));
            }

            cout << endl << endl << "Unfortunately, we ask you to add spaces as needed below while we work on this feature :(" << endl <<"-------------------------Please double check with your human eyes-------------------------" << endl;
            cout << spaceDecryptedMessage << endl;

        } else if (user == "Eve") {
            quit = 'y';
            cout << "Shouldn't you speak to Adam? Stop trying to intercept messages. There are no secret messages here.\n";
            break;
        }

        cout << "Would you like to logout? (y/n)\n";
        cin >> quit;
        quit = static_cast<char>(tolower(quit));

        while (quit != 'y' && quit!= 'n') {
            cout << "Please input a valid response! Would you like to logout? (y/n)\n";
            cin >> quit;
            quit = static_cast<char>(tolower(quit));
        }
    }
    return 0;
}
