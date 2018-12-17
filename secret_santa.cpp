#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

typedef struct Person{
    string name;
    int gotten;
    struct Person* got;
} Person;

main(int argc, char const *argv[])
{
    string line, command;
    int num = 1;
    vector<Person*> names;

    cout << "Enter q at anytime to stop entering names" << endl;
    cout << "Enter 1st name: ";
    getline(cin, command);

    while(!cin.eof()) {
        //stringstream lineStream(line);
        //lineStream >> command;

        if (command == "q") {
            break;
        }
        else {
            Person* newEntry = (Person*)malloc(sizeof(Person));
            newEntry->name = command;
            newEntry->gotten = 0;
            newEntry->got = NULL;
            names.push_back(newEntry);
        }
        num++;
        if (num % 100 == 11 || num % 100 == 12 || num % 100 == 13) {
            cout << "Enter " << num << "th name: ";
        }
        else if (num % 10 == 1) {
            cout << "Enter " << num << "st name: ";
        }
        else if (num % 10 == 2) {
            cout << "Enter " << num << "nd name: ";
        }
        else if (num % 10 == 3) {
            cout << "Enter " << num << "rd name: ";
        }
        else {
            cout << "Enter " << num << "th name: ";
        }
        getline(cin, command);
    }
    if (num == 1) {
        cout << "Error: nothing entered" << endl;
        return 0;
    }
    else if (num == 2) {
        cout << "Error: please enter more than 1 name" << endl;
        return 0;
    }

    cout << endl;

    //actual amount of names entered
    num--;

    bool disconnectedCheck = false;
    while (disconnectedCheck == false) {
        int random = -1;
        for (int i = 0; i < num; i++) {
            random = rand() % num;
            if (i != random && names[random]->gotten == 0) {
                //add the random person to first persons pointer
                names[i]->got = names[random];
                names[random]->gotten = 1;
            }
            else {
                i--;
            }
        }

        //check for disconnections
        Person* iterator = names[0];
        for (int i = 0; i < num; i++) {
            if (iterator->got == names[0] && i != num-1) {
                disconnectedCheck = false;
                for(int j = 0; j < num; j++) {
                    names[j]->gotten = 0;
                    names[j]->got = NULL;
                }
                break;
            }
            else {
                disconnectedCheck = true;
                iterator = iterator->got;
            }
        }
    }

    for(int i = 0; i < num; i++) {
        cout << names[i]->name << " got " << names[i]->got->name << endl;
    }

    for(int i = 0; i < num; i++) {
        names[i]->got = NULL;
        free(names[i]);
    }

    return 0;
}
