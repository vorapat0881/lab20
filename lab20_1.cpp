#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(const string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream A(filename);
    string file;
    int x,y,z;
    char name[100];
    int score;
    while(getline(A,file)){
        char format[] = "%[^:]: %d %d %d";
        sscanf(file.c_str(),format,&name,&x,&y,&z);
        names.push_back(name);
        score = x+y+z;
        scores.push_back(score);
        grades.push_back(score2grade(score));
    }
}

void getCommand(string &command, string &key){
    string a;
    cout << "Please input your command: ";
    cin >> command;
    a = toUpperStr(command);
    if(a == "GRADE" || a == "NAME" ){
    cin.ignore();
    getline(cin,key);
}
}

void searchName(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key){
    bool found = false;
    for (size_t i = 0; i < names.size(); ++i) {
        if (toUpperStr(names[i]) == key) {
            found = true;
            cout << "---------------------------------\n";
            cout << names[i] << "'s" << " score = " << scores[i] << "\n" << names[i] << "'s" << " grade = " << grades[i] << "\n";
        }
    }
    if (!found) {
        cout << "---------------------------------\n";
        cout << "Cannot found." << "\n";
    }   cout << "---------------------------------\n";
}

void searchGrade(const vector<string>& names, const vector<int>& scores, const vector<char>& grades, const string& key){
    bool found = false;
    char X = toupper(key[0]);
    cout << "---------------------------------\n";
    for (size_t i = 0; i < grades.size(); ++i) {
        if (grades[i] == X) {
            found = true;
            cout << names[i] << " (" << scores[i] << ")"<< "\n";
        }
    }
    if (!found) {
        cout << "Cannot found.\n";
    }
    cout << "---------------------------------\n";
}



int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
