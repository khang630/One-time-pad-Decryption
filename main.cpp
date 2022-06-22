/*
Name: Khang Nguyen 11340263
Course: CSCE 3550.001 Mark Thompson
Date: 11/27/2021
Description: This program takes in 6 lines of ciphertext and uses XOR techniques 
to decrypt the secret messages based on the re-use of a one time pad.
*/


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    //arrays to hold the six ciphertext messages
    int cipher1[60];
    int cipher2[60];
    int cipher3[60];
    int cipher4[60];
    int cipher5[60];
    int cipher6[60];

    ifstream fin;      //for reading in
    string cipherfile; //ciphertext.txt file

    cout << "Enter the name of the ciphertext file: "; //prompt user to enter ciphertext file
    cin >> cipherfile;

    fin.open(cipherfile); //open ciphertext file
    if (fin.is_open())    //if ciphertext file is opened
    {
        int asciiform;
        stringstream ss;
        string str;  //for each line of the ciphertext
        string temp; //temp string to store the 2 char hex

        cout << "Ciphertext: " << endl;
        int linecount = 1;        //skip storting the first char of each ciphertext line
        while (getline(fin, str)) //while there is a line, read
        {
            int arraycount = 0;
            cout << str << endl; //print ciphertext for reference

            for (auto it = str.begin(); it != str.end(); ++it) //iterate through every single char in the line
            {
                if (temp.length() > 1) //if temp has 2 char, turn that "hex" into ascii int and reset temp to nothing
                {
                    asciiform = stoi(temp, nullptr, 16); //turn 2 char string into integer and store in corresponding cipher array
                    if (linecount == 1)
                    {
                        cipher1[arraycount] = asciiform;
                        arraycount++;
                    }
                    else if (linecount == 2)
                    {
                        cipher2[arraycount] = asciiform;
                        arraycount++;
                    }
                    else if (linecount == 3)
                    {
                        cipher3[arraycount] = asciiform;
                        arraycount++;
                    }
                    else if (linecount == 4)
                    {
                        cipher4[arraycount] = asciiform;
                        arraycount++;
                    }
                    else if (linecount == 5)
                    {
                        cipher5[arraycount] = asciiform;
                        arraycount++;
                    }
                    else if (linecount == 6)
                    {
                        cipher6[arraycount] = asciiform;
                        arraycount++;
                    }
                    temp = ""; //reset temp to empty
                }
                temp += *it; //add char to temp string variable
            }
            asciiform = stoi(temp, nullptr, 16); //store last "hex" char since for loop does not iterate 1 last time
            if (linecount == 1)
            {
                cipher1[arraycount] = asciiform;
            }
            else if (linecount == 2)
            {
                cipher2[arraycount] = asciiform;
            }
            else if (linecount == 3)
            {
                cipher3[arraycount] = asciiform;
            }
            else if (linecount == 4)
            {
                cipher4[arraycount] = asciiform;
            }
            else if (linecount == 5)
            {
                cipher5[arraycount] = asciiform;
            }
            else if (linecount == 6)
            {
                cipher6[arraycount] = asciiform;
            }
            temp = "";   //fixes first array's first index having previous array's last index
            linecount++; //increase line count
        }
    }

    int keyarray[60] = {0}; //Array to hold the key for each index. Initialized with all 0s.

    //Arrays to hold the Line1 ciphertext XORs.
    int cipher12[60];
    int cipher13[60];
    int cipher14[60];
    int cipher15[60];
    int cipher16[60];

    //Arrays to hold whether a ciphertext has a space at a certain index. All initialized to false.
    bool cipher1spaces[60] = {false};
    bool cipher2spaces[60] = {false};
    bool cipher3spaces[60] = {false};
    bool cipher4spaces[60] = {false};
    bool cipher5spaces[60] = {false};
    bool cipher6spaces[60] = {false};

    //Line1 ciphertext is XOR'ed with all other lines and stored in their corresponding cipher arrays
    for (int i = 1; i < 60; ++i)
    {
        cipher12[i] = cipher1[i] ^ cipher2[i];
        cipher13[i] = cipher1[i] ^ cipher3[i];
        cipher14[i] = cipher1[i] ^ cipher4[i];
        cipher15[i] = cipher1[i] ^ cipher5[i];
        cipher16[i] = cipher1[i] ^ cipher6[i];
    }

    bool case2; //case where Line 1 XOR with every other line results in >=65 for all. This means Line1 has a space there
    for (int i = 1; i < 60; ++i)
    {
        case2 = true; //reset to true

        //if line1 XOR gives an answer <65 and it is not = 0, it means that there is not a space on this index in line 1
        if (cipher12[i] < 65 && cipher12[i] != 0)
        {
            case2 = false;
        }

        if (cipher13[i] < 65 && cipher13[i] != 0)
        {
            case2 = false;
        }

        if (cipher14[i] < 65 && cipher14[i] != 0)
        {
            case2 = false;
        }

        if (cipher15[i] < 65 && cipher15[i] != 0)
        {
            case2 = false;
        }

        if (cipher16[i] < 65 && cipher16[i] != 0)
        {
            case2 = false;
        }

        //if line1 XOR all gives >=65 with the exception of 0s, it means that there is a space in this index in line 1
        if (case2 == true)
        {
            int key;
            key = cipher1[i] ^ 32;   //Since we know a space has an ascii value of 32, we XOR 32 with our ciphertext at this index to get the plaintext
            keyarray[i] = key;       //store key in the corresponding index
            cipher1spaces[i] = true; //say that an index has a space in the corresponding line
            continue;                //skip to next loop since this index will already have a 0, so we are done.
        }

        //Else if not all line1 XOR results in >=65, the lines that DO result in XOR of >=65 have a space on that index
        if (cipher12[i] >= 65)
        {
            int key;
            key = cipher2[i] ^ 32;
            keyarray[i] = key;
            cipher2spaces[i] = true;
        }

        if (cipher13[i] >= 65)
        {
            int key;
            key = cipher3[i] ^ 32;
            keyarray[i] = key;
            cipher3spaces[i] = true;
        }

        if (cipher14[i] >= 65)
        {
            int key;
            key = cipher4[i] ^ 32;
            keyarray[i] = key;
            cipher4spaces[i] = true;
        }

        if (cipher15[i] >= 65)
        {
            int key;
            key = cipher5[i] ^ 32;
            keyarray[i] = key;
            cipher5spaces[i] = true;
        }

        if (cipher16[i] >= 65)
        {
            int key;
            key = cipher6[i] ^ 32;
            keyarray[i] = key;
            cipher6spaces[i] = true;
        }
    }

    cout << endl;
    cout << "Message decrypted >%70:" << endl;
    cout << endl;
    int first; //variable to hold the first variable
    char firstchar;
    first = cipher1[0] ^ 218; //218 is xda in hex
    firstchar = first;
    cout << firstchar; //display first char
    for (int i = 1; i < 60; ++i)
    {
        int decrypted;
        char asciivalue;

        if (keyarray[i] != 0) //if there is a key
        {
            if (cipher1spaces[i] == false) //and if there is no space on that index
            {
                decrypted = cipher1[i] ^ keyarray[i]; //XOR key and ciphertext
                asciivalue = decrypted;
                cout << asciivalue; //display plaintext char
            }
            else //else if there is a space
            {
                cout << " "; //display a space
            }
        }
        else //display unknown char
        {
            cout << "?";
        }
    }

    cout << endl;
    first = cipher2[0] ^ 218; //218 is xda in hex
    firstchar = first;
    cout << firstchar; //display first char
    for (int i = 1; i < 60; ++i)
    {
        int decrypted;
        char asciivalue;

        if (keyarray[i] != 0) //if there is a key
        {
            if (cipher2spaces[i] == false) //and if there is no space on that index
            {
                decrypted = cipher2[i] ^ keyarray[i]; //XOR key and ciphertext
                asciivalue = decrypted;
                cout << asciivalue; //display plaintext char
            }
            else //else if there is a space
            {
                cout << " "; //display a space
            }
        }
        else //display unknown char
        {
            cout << "?";
        }
    }

    cout << endl;
    first = cipher3[0] ^ 218; //218 is xda in hex
    firstchar = first;
    cout << firstchar; //display first char
    for (int i = 1; i < 60; ++i)
    {
        int decrypted;
        char asciivalue;

        if (keyarray[i] != 0) //if there is a key
        {
            if (cipher3spaces[i] == false) //and if there is no space on that index
            {
                decrypted = cipher3[i] ^ keyarray[i]; //XOR key and ciphertext
                asciivalue = decrypted;
                cout << asciivalue; //display plaintext char
            }
            else //else if there is a space
            {
                cout << " "; //display a space
            }
        }
        else //display unknown char
        {
            cout << "?";
        }
    }

    cout << endl;
    first = cipher4[0] ^ 218; //218 is xda in hex
    firstchar = first;
    cout << firstchar; //display first char
    for (int i = 1; i < 60; ++i)
    {
        int decrypted;
        char asciivalue;

        if (keyarray[i] != 0) //if there is a key
        {
            if (cipher4spaces[i] == false) //and if there is no space on that index
            {
                decrypted = cipher4[i] ^ keyarray[i]; //XOR key and ciphertext
                asciivalue = decrypted;
                cout << asciivalue; //display plaintext char
            }
            else //else if there is a space
            {
                cout << " "; //display a space
            }
        }
        else //display unknown char
        {
            cout << "?";
        }
    }

    cout << endl;
    first = cipher5[0] ^ 218; //218 is xda in hex
    firstchar = first;
    cout << firstchar; //display first char
    for (int i = 1; i < 60; ++i)
    {
        int decrypted;
        char asciivalue;

        if (keyarray[i] != 0) //if there is a key
        {
            if (cipher5spaces[i] == false) //and if there is no space on that index
            {
                decrypted = cipher5[i] ^ keyarray[i]; //XOR key and ciphertext
                asciivalue = decrypted;
                cout << asciivalue; //display plaintext char
            }
            else //else if there is a space
            {
                cout << " "; //display a space
            }
        }
        else //display unknown char
        {
            cout << "?";
        }
    }

    cout << endl;
    first = cipher6[0] ^ 218; //218 is xda in hex
    firstchar = first;
    cout << firstchar; //display first char
    for (int i = 1; i < 60; ++i)
    {
        int decrypted;
        char asciivalue;

        if (keyarray[i] != 0) //if there is a key
        {
            if (cipher6spaces[i] == false) //and if there is no space on that index
            {
                decrypted = cipher6[i] ^ keyarray[i]; //XOR key and ciphertext
                asciivalue = decrypted;
                cout << asciivalue; //display plaintext char
            }
            else //else if there is a space
            {
                cout << " "; //display a space
            }
        }
        else //display unknown char
        {
            cout << "?";
        }
    }
    cout << endl;
    cout << endl;

    //Using the english language to figure out words which leads to figuring out certain chars at certain indexes.
    //Which will then lead me to know the key and I will hardcode to solve that index column.

    keyarray[15] = 20;  //unknown index 16
    keyarray[20] = 61;  //unknown index 21
    keyarray[26] = 213; //unknown index 27
    keyarray[27] = 84;  //unknown index 28

    keyarray[29] = 8; //unknown index 30
    //keyarray[32] = 0; //unknown index 33
    keyarray[33] = 64; //unknown index 34

    keyarray[37] = 230; //unknown index 38
    //keyarray[40] = 0; //unknown index 41

    keyarray[47] = 231; //unknown index 48
    keyarray[49] = 21;  //unknown index 50
    keyarray[50] = 248; //unknown index 51

    keyarray[54] = 51; //unknown index 55

    //keyarray[57] = 218; //unknown index 58
    //keyarray[58] = 170; //unknown index 59

    cout << "Using the English language to figure out more of the message:" << endl;
    cout << endl;

    first = cipher1[0] ^ 218; //218 is xda in hex
    firstchar = first;
    cout << firstchar; //display first char
    for (int i = 1; i < 60; ++i)
    {
        int decrypted;
        char asciivalue;

        if (keyarray[i] != 0) //if there is a key
        {
            if (cipher1spaces[i] == false) //and if there is no space on that index
            {
                decrypted = cipher1[i] ^ keyarray[i]; //XOR key and ciphertext
                asciivalue = decrypted;
                cout << asciivalue; //display plaintext char
            }
            else //else if there is a space
            {
                cout << " "; //display a space
            }
        }
        else //display unknown char
        {
            cout << "?";
        }
    }

    cout << endl;
    first = cipher2[0] ^ 218; //218 is xda in hex
    firstchar = first;
    cout << firstchar; //display first char
    for (int i = 1; i < 60; ++i)
    {
        int decrypted;
        char asciivalue;

        if (keyarray[i] != 0) //if there is a key
        {
            if (cipher2spaces[i] == false) //and if there is no space on that index
            {
                decrypted = cipher2[i] ^ keyarray[i]; //XOR key and ciphertext
                asciivalue = decrypted;
                cout << asciivalue; //display plaintext char
            }
            else //else if there is a space
            {
                cout << " "; //display a space
            }
        }
        else //display unknown char
        {
            cout << "?";
        }
    }

    cout << endl;
    first = cipher3[0] ^ 218; //218 is xda in hex
    firstchar = first;
    cout << firstchar; //display first char
    for (int i = 1; i < 60; ++i)
    {
        int decrypted;
        char asciivalue;

        if (keyarray[i] != 0) //if there is a key
        {
            if (cipher3spaces[i] == false) //and if there is no space on that index
            {
                decrypted = cipher3[i] ^ keyarray[i]; //XOR key and ciphertext
                asciivalue = decrypted;
                cout << asciivalue; //display plaintext char
            }
            else //else if there is a space
            {
                cout << " "; //display a space
            }
        }
        else //display unknown char
        {
            cout << "?";
        }
    }

    cout << endl;
    first = cipher4[0] ^ 218; //218 is xda in hex
    firstchar = first;
    cout << firstchar; //display first char
    for (int i = 1; i < 60; ++i)
    {
        int decrypted;
        char asciivalue;

        if (keyarray[i] != 0) //if there is a key
        {
            if (cipher4spaces[i] == false) //and if there is no space on that index
            {
                decrypted = cipher4[i] ^ keyarray[i]; //XOR key and ciphertext
                asciivalue = decrypted;
                cout << asciivalue; //display plaintext char
            }
            else //else if there is a space
            {
                cout << " "; //display a space
            }
        }
        else //display unknown char
        {
            cout << "?";
        }
    }

    cout << endl;
    first = cipher5[0] ^ 218; //218 is xda in hex
    firstchar = first;
    cout << firstchar; //display first char
    for (int i = 1; i < 60; ++i)
    {
        int decrypted;
        char asciivalue;

        if (keyarray[i] != 0) //if there is a key
        {
            if (cipher5spaces[i] == false) //and if there is no space on that index
            {
                decrypted = cipher5[i] ^ keyarray[i]; //XOR key and ciphertext
                asciivalue = decrypted;
                cout << asciivalue; //display plaintext char
            }
            else //else if there is a space
            {
                cout << " "; //display a space
            }
        }
        else //display unknown char
        {
            cout << "?";
        }
    }

    cout << endl;
    first = cipher6[0] ^ 218; //218 is xda in hex
    firstchar = first;
    cout << firstchar; //display first char
    for (int i = 1; i < 60; ++i)
    {
        int decrypted;
        char asciivalue;

        if (keyarray[i] != 0) //if there is a key
        {
            if (cipher6spaces[i] == false) //and if there is no space on that index
            {
                decrypted = cipher6[i] ^ keyarray[i]; //XOR key and ciphertext
                asciivalue = decrypted;
                cout << asciivalue; //display plaintext char
            }
            else //else if there is a space
            {
                cout << " "; //display a space
            }
        }
        else //display unknown char
        {
            cout << "?";
        }
    }

    cout << endl;
    cout << endl;
    cout<<"The full message decryption is in the README.txt file"<<endl;

    return 0;
}