/* Citations
 * cin.ignore() https://cplusplus.com/forum/beginner/173682/ Reply by Peter87,
 * follow up with https://www.geeksforgeeks.org/cpp/cin-ignore-function-in-cpp/ confirms how to use cin.ignore()
 *
 * MIT.txt created with https://www.mit.edu/~ecprice/wordlist.10000
 *
 * Zybooks 9.5 used for help with file input
 *
 * Note: Test code was removed
 */


#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <fstream> //Zybooks 9.5 cited above

using namespace std;

int main() {
    //Obtaining the key
    ifstream dataFS; //filestream creation
    dataFS.open("4.txt"); //Opens fstream called dataFS to read encrypted message

    string keyword; //Temporary holder for keyword
    vector<string> keywords; //Builds vector of keywords

    string encryptedMessage;
    vector<char> encryptedChar;
    vector<char> decryptedChar;
    vector<int> alphabet(26); //Vector to hold frequencies


    getline(dataFS, encryptedMessage); //dataFS inputs 4.txt into encryptedMessage
    dataFS.close();
    dataFS.clear();

    //Below is the logic for the frequency analysis
    // Encrypted message in 1 long string
    for (unsigned int i = 0; i < encryptedMessage.length(); i++) {
        if (isalpha(encryptedMessage.at(i))) {
            encryptedChar.push_back(encryptedMessage.at(i));
        }
    }

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
    //Frequency analysis report
    for (unsigned int i = 0; i < alphabet.size(); i++) {
        cout <<static_cast<char>(i + 65) << ": " << alphabet.at(i) << "| ";
    }
    cout << endl << endl << endl;
    cout << "Brute force output below ----------------------------------------------" << endl << endl;

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
    for (unsigned int i = 0; i < keywords.size(); i++) { //Iterate through list of keywords
        cout << i <<") ";
        for (unsigned int j = 0; j < encryptedChar.size(); j++) { //Iterate through string in keywords AND in length of text
            if ((encryptedChar.at(j) - (keywords.at(i).at(j % keywords.at(i).length()))) < 0) {
                cout << static_cast<char>((encryptedChar.at(j) - (keywords.at(i).at(j % keywords.at(i).length()))) + 91); //Underflow
            } else {
                cout << static_cast<char>(encryptedChar.at(j) - (keywords.at(i).at(j % keywords.at(i).length())) + 65); //Overflow
            }
            //Encrypted - key = original
        }
        cout << endl << endl;
    }
    cout << "End of brute force output-----------------------------------------------------------------------------";

    cout << endl << endl << "Please use your human eyes to look for the english looking phrase." << endl << endl;
    //Keyword
    cout << "The keyword is at 25 and is " << keywords.at(25) << " when you find english." << endl;

    //Decryption algorithm specifically for index 25 (REPAIR)
    for (unsigned int i = 0; i < encryptedChar.size(); i++) {
        if (encryptedChar.at(i) - keywords.at(25).at(i % keywords.at(25).length()) < 0) {
            decryptedChar.push_back((encryptedChar.at(i) - keywords.at(25).at(i % keywords.at(25).length())) + 91);
        } else {
            decryptedChar.push_back((encryptedChar.at(i) - keywords.at(25).at(i % keywords.at(25).length())) + 65);
        }
    }


    /* SPACE MAKER
     * To avoid prefixes and cutting off suffixes from the list of 10,000 words,
     * we will process the sentence backwards which requires reverser code
     * This requires a backwards list of 10,000!
     *
     * edit: Above was the initial plan, it turns out after further testing.. the spacing is weird because of suffixes, prefixes and compound words.
     * New theory: Run the code once forwards and only include MIT words that are 4 characters in length. The intuition is that most prefixes are 3 letters in size.
     *
     * edit edit: This also did not work. Plural "s" is removed. The intuition is there is likely more functions/set theory required in order to better separate a stream of characters into words
        There may be redudant code from prior attempts. Our output is the best we could do without adding extra spaces that may confuse Bob i.e. pre tensions getting cut in half
     */
    string mitWord;
    string reverseMITWord;
    string mitWordTemp;
    vector<string> mitWords;
    vector<string> mitWordsTemp; //Added to add capitalizer before reverse to prevent changing all other variables
    vector<string> reverseMITWords;
    vector<char> reverseDecryptedChar;

    //MITword looper variables
    string comparedWordOne;
    vector<int> spacesOne;
    vector<char> sDecryptedCharOne; //Spaced Reverse Decrypted Char

    //mitWord maker
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

    //Word reverser
    for (unsigned int i = 0; i < mitWords.size(); i++) {
        reverseMITWord = "";
        for (int j = mitWords.at(i).size() - 1; j >= 0; j--) {
            reverseMITWord.push_back(mitWords.at(i).at(j));
        }
        reverseMITWords.push_back(reverseMITWord);
    }

    //Decrypted message reverser
    for (int i = decryptedChar.size() - 1; i >= 0; i--) { //Has to be int since it will dip under 0
        reverseDecryptedChar.push_back(decryptedChar.at(i));
    }

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


    //Adds spaces to the reverseDecryptedChar vector
    for (unsigned int i = 0; i < reverseDecryptedChar.size(); i++) {
        for (unsigned int j = 0; j < spaces.size(); j++) {
            if (i == spaces.at(j)) {
                sRDC.push_back(' ');
            }
        }
        sRDC.push_back(reverseDecryptedChar.at(i));
    }

    //Creates decrypted message with spaces
    string spaceDecryptedString;
    for (int i = sRDC.size() - 1; i >= 0; i--) { //Has to be int since it will dip under 0
        spaceDecryptedString.push_back(sRDC.at(i));
    }

    //Prints out decrypted message with spaces
    cout << endl << "Unfortunately, we ask you to add spaces as needed below while we work on this feature :(" << endl << endl << "-------------------Please double check with your human eyes below-------------------------";
    cout << endl << spaceDecryptedString << "\n\n\n";

    cout << "The correct text with spaces added by a human is as follows: " << "THE ANALYTICAL ENGINE HAS NO PRETENSIONS WHATEVER TO ORIGINATE ANYTHING IT CAN DO WHATEVER";
    cout << " WE KNOW HOW TO ORDER IT TO PERFORM IT CAN FOLLOW ANALYSIS BUT IT HAS NO POWER OF ANTICIPATING ANY ANALYTICAL RELATIONS OR TRUTHS ITS PROVINCE IS TO ASSIST US IN MAKING AVAILABLE WHAT WE ARE ALREADY ACQUAINTED WITH THE ANALYTICAL ENGINE WEAVES ALGEBRAIC PATTERNS JUST AS THE JACQUARD LOOM WEAVES FLOWERS AND LEAVES" << "\n\n\n";

    ifstream answerFS;
    string adaAnswer;
    answerFS.open("adaQuote.txt");
    while (!answerFS.eof() && answerFS.good()) {
        getline(answerFS, adaAnswer);
        cout << adaAnswer;
        if (dataFS.bad()){
            cout << "Failed to input the MIT.txt";
            break;
        }
    }

    cout << endl << "-----------------------------------------------------------------------------" << endl;


    //User varaiables
    string user;
    char quit = 'n';

    //Alice variables
    string newMessage;
    char answer;
    vector<char> outgoingMessageChar;
    string defaultKey = "PNEUMONOULTRAMICROSCOPICSILICOVOLCANOCONIOSIS";
    char encryptedCharHolder;
    string encryptedOutgoingMessage;

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

        if (user == "Alice") {
            cout << "Okay, what is your message? ";
            getline(cin, newMessage);

            cout << "-----------------------------------------------------------------------------";

            cout << "\n\"" << newMessage << "\"" << "| Is this the correct message to send? (y/n) ";

            cin >> answer;
            while (tolower(answer) != 'y') {
                cin.ignore(); //cin.ignore() citation
                cout << "Please enter the correct message, " << user << ". ";
                getline(cin, newMessage);
                cout <<"\n\"" << newMessage << "\"" <<"| Is this the message you want to send? (y/n) ";
                cin >> answer;
            }

            //Vector of characters maker and capitalization
            for (unsigned int i = 0; i < newMessage.length(); i++) {
                if (newMessage.at(i) == ' ') {
                    continue;

                } else {
                    outgoingMessageChar.push_back(toupper(newMessage.at(i)));
                }
            }

            //Vector of characters checker
            /*
            for (unsigned int i = 0; i < outgoingMessageChar.size(); i++) {
                cout << outgoingMessageChar.at(i);
            } */
//------------- code above okay
            //Default Encryption algorithm - below

            for (unsigned int i = 0; i < outgoingMessageChar.size(); i++) {
                if (outgoingMessageChar.at(i) != ' ') {
                    encryptedCharHolder = (((outgoingMessageChar.at(i) + defaultKey.at(i % 45)) % 26) +65);
                    encryptedOutgoingMessage.push_back(encryptedCharHolder);
                }
            }

            cout << "-----------------------------------------------------------------------------" << endl;

            cout << "This is your encrypted message: \n";
            for (unsigned int i = 0; i <encryptedOutgoingMessage.size(); i++) {
                cout << encryptedOutgoingMessage.at(i);
            }

            cout << endl;



//------------------------------------------------------------------Bob
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
//-------------------------------------------------------------------- EVE
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
