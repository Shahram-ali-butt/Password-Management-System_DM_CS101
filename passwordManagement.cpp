#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include "crypto_functions.h"

const string userFile = "users.txt";
const string signUpFile = "signUpData.txt";
const string adminFile = "admin.txt";

//  PASSWORD MANAGEMENT (Implemented in existing Buisness Application Project)

void storeUserDataEnc(int currentUsers, string userNames[], string userPasswords[]) {
    ofstream file(userFile, ios::out);
    if (!file.is_open()) {
        cout << "File: "<< userFile << " not found" << endl;
    }
    
    string encryptedName, encryptedPassword, userNameFixed;

    file << currentUsers << '\n';

    for(int i = 0; i < currentUsers; i++){
        for(int j = 0; j < userNames[i].length(); j++){
            if(userNames[i][j] == ' ') userNameFixed += 'X';
            else userNameFixed += userNames[i][j];
    }

        encryptedName = affineEncrypt(userNameFixed, 5, 8);
        encryptedPassword = userPasswords[i];

        file << encryptedName << ',' << encryptedPassword << '\n';
        userNameFixed = "";
    }

    file.close();
}

bool verifyUser(string &currentUser, string userName, string userPassword) {
    ifstream file(userFile);
    bool verified = false;
    if (!file.is_open()){
        cout << "File: " << userFile << " not found" << endl;;
    }
    
    string line;
    string storedUser, encriptedUser, storedHash;
    string decryptedPassword;

    userPassword = hashPassword(userPassword);

    getline(file, line);

    while (getline(file, line)){
        stringstream ss(line);
        
        getline(ss, encriptedUser, ',');
        getline(ss, storedHash);
        
        storedUser = affineDecrypt(encriptedUser, 5, 8);

        for(int j = 0; j < storedUser.length(); j++){
            if(storedUser[j] == 'X') storedUser[j] = ' ';
        }

        if (storedUser == userName && userPassword == storedHash) {
            verified = true;
            currentUser = storedUser;
            break;
        }  
    }
    
    file.close();
    return verified;
}

bool verifyAdmin(string password) {
    ifstream file(adminFile);
    bool verified = false;
    if (!file.is_open()){
        cout << "File: " << adminFile << " not found" << endl;;
    }
    
    string storedHash;

    password = hashPassword(hashPassword(password));

    getline(file, storedHash);

    if (password == storedHash) {
        verified = true;
    }  
    
    file.close();
    return verified;
}

void storeSignUpDataEnc(int signUpRequests, string signUpRequestData[][2]) {
    ofstream file(signUpFile, ios::out);
    if (!file.is_open()) {
        cout << "File: " << signUpFile << " not found" << endl;
    }
    
    string encryptedName, encryptedPassword, userNameFixed;

    file << signUpRequests << '\n';

    for(int i = 0; i < signUpRequests; i++){
        for(int j = 0; j < signUpRequestData[i][0].length(); j++){
            if(signUpRequestData[i][0][j] == ' ') userNameFixed += 'X';
            else userNameFixed += signUpRequestData[i][0][j];
        }
        
        encryptedName = affineEncrypt(userNameFixed, 9, 15);
        encryptedPassword = signUpRequestData[i][1];

        file << encryptedName << ',' << encryptedPassword << '\n';
        userNameFixed = "";
    }

    file.close();
}

void loadSignUpDataDec(int &signUpRequests, string signUpRequestData[][2]) {
    ifstream file(signUpFile);
    if (!file.is_open()){
        cout << "File: " << signUpFile << " not found" << endl;;
    }
    
    string line;
    string storedUser, encriptedUser, storedPassword;
    string decryptedPassword;

    file >> signUpRequests;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i = 0; i < signUpRequests; i++){
        getline(file, line);
        stringstream ss(line);
        
        getline(ss, encriptedUser, ',');
        getline(ss, storedPassword);

        storedUser = affineDecrypt(encriptedUser, 9, 15);

        for(int j = 0; j < storedUser.length(); j++){
            if(storedUser[j] == 'X') storedUser[j] = ' ';
        }
        
        signUpRequestData[i][0] = storedUser;
        signUpRequestData[i][1] = storedPassword;

    }
         
    file.close();
}

bool checkUserExists(string userName) {
    ifstream file(userFile);
    bool exists = false;
    if (!file.is_open()){
        cout << "File: " << userFile << " not found" << endl;;
    }
    
    string line, storedHash, encriptedUser, storedUser;

    getline(file, line);

    while (getline(file, line)){
        stringstream ss(line);
        
        getline(ss, encriptedUser, ',');
        getline(ss, storedHash);
        
        storedUser = affineDecrypt(encriptedUser, 5, 8);

        for(int j = 0; j < storedUser.length(); j++){
            if(storedUser[j] == 'X') storedUser[j] = ' ';
        }

        if (storedUser == userName) {
            exists = true;
            break;
        }  
    }
    
    file.close();
    return exists;
}

void loadUserDataDec(int &currentUsers, string userNames[], string userPasswords[]) {
    ifstream file(userFile);
    if (!file.is_open()){
        cout << "File: " << userFile << " not found" << endl;;
    }
    
    string line;
    string storedUser, encriptedUser, storedPassword;

    file >> currentUsers;
    file.ignore(numeric_limits<streamsize>::max(), '\n');

    for(int i = 0; i < currentUsers; i++){
        getline(file, line);
        stringstream ss(line);
        
        getline(ss, encriptedUser, ',');
        getline(ss, storedPassword);

        storedUser = affineDecrypt(encriptedUser, 5, 8);

        for(int j = 0; j < storedUser.length(); j++){
            if(storedUser[j] == 'X') storedUser[j] = ' ';
        }
        
        userNames[i] = storedUser;
        userPasswords[i] = storedPassword;
    }
         
    file.close();
}
