#include <cstring>
#include <vector>
#include <iostream>
#include <cctype>
#include <fstream>

using namespace std;

int main() {

    //Obtaining the key
    ifstream dataFS; //filestream creation
    string keyword; //temporary holder for keyword
    vector<string> keywords; //builds vector of keywords
    dataFS.open("4.txt");
    string encryptedMessage;
    vector<char> encryptedChar;
    getline(dataFS, encryptedMessage);
    vector<int> alphabet(26);

    /*Below is the logic for the frequency analysis*/
    //Encrypted message in 1 long string
    for (unsigned int i = 0; i < encryptedMessage.length(); i++) {
        if (isalpha(encryptedMessage.at(i))) {
            encryptedChar.push_back(encryptedMessage.at(i));
        }
        cout << encryptedChar.at(i) << endl;
    }



    if (dataFS.bad() || dataFS.fail()) {
        cout << "It broke\n";
    }

    if (dataFS.good()) {
        cout << "We good\n";
    }

    //65 is A, 26 characters, range is 0-25
    for (unsigned int i = 0; i < alphabet.size(); i++) {
        for (unsigned int j = 0; j < encryptedChar.size(); j++) {
            if (65 + i == static_cast<int>(encryptedChar.at(j))) {
                alphabet.at(i)++;
            }
        }
        //cout << alphabet.at(i) << endl;
    }



    /*
    cout << "Frequency Analysis-------------------------" << endl;
    for (unsigned int i = 0; i < alphabet.size(); i++) {
        cout << static_cast<char>(i+65) << ": " << alphabet.at(i) << endl;
    }*/

    /*
    while (!dataFS.eof()) {
        dataFS >> keyword;
        keywords.push_back(keyword);
    }*/

    /*
    if (dataFS.fail()) {
        cout << "Failure is beneath DOOOM.";
    } */

	/*Keyword Vector test
	for (unsigned int i; i < keywords.size(); i++) {
        cout << keywords.at(i) << endl;
    }*/

    //User varaiables
    string user;
    char quit = 'n';
    string key;
    vector<char> aliceTxt;
    vector<char> bobTxt;

    while (quit != 'y') {
        break; //DONT FORGET TO REMOVE ME
        cout << "Are you Alice, Bob, or Eve?\n";
        cin >> user;

        while (user != "Alice" && user!= "Bob" && user!= "Eve"){
            cout << "Pick a valid user please!\n";
            cin >> user;
        }

        if (user == "Alice") {
            //
        }

        if (user == "Bob") {
            //
        }

        if (user == "Eve") {
            quit = 'y';
            cout << "Shouldn't you speak to Adam?\n";
            break;
        }

        cout << "Would you like to quit?\n";
        cin >> quit;
        quit = static_cast<char>(tolower(quit));



        while (quit != 'y' && quit!= 'n') {
            cout << "Please input a valid response! Would you like to quit? (y/n)\n";
            cin >> quit;
            quit = static_cast<char>(tolower(quit));
        }


    }

    return 0;
}