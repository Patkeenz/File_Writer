#include <vector>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream>
using namespace std;

string split(string str, char splitchar){//this function returns the final string in a function after being split by a given character
    string temp = "";
    for(int i=0; i<(int)str.size(); i++){
        if(str[i] != splitchar){// If cur char is not the splitcharacter, then append it to the current string
            temp += str[i];
        }
        else{//if you find the splitchar restart the temp string 
            temp = "";
        }
    }
    if(temp.find('.') != string::npos){//if the last temp string has a '.' character (meaning that it is a file ending with a .filetype) return it
        return temp; //this will not filter out folders with a decimal character in them.. 
    }
    else{
        return "this is not a file";
    }
}

int getValue(string s){//gets the ASCII value of a given string
    int sum = 0;
    for (int i = 0; i < s.size(); i++) {
        sum += s[i];
    }
    return sum;
}
 
vector<string> sortStrings(vector<string> arr){//returns a vector of strings sorted by their ASCII values
    vector<pair<int, string>> pairvec;
    vector<string> newarr;
    for(int i = 0; i < arr.size(); i++) {//
        // Find the value of the string
        int val = getValue(arr[i]);
        //add string with its corresponding value
        pairvec.push_back({val, arr[i]});
    }
    //sort the strings by their values
    sort(pairvec.begin(), pairvec.end());
    // Print the sorted strings
    for (int i = 0; i < arr.size(); i++) {
        newarr.push_back(pairvec[i].second);
    }
    return newarr;
}

int main(){
    string directory;
    cout <<"Please enter the directory you wish to process" << endl;
    cin >> directory;
    vector <string> arr;
    arr.reserve(50);
    string curr;
    char splitchar = '\\';
    for (const auto & entry : filesystem::recursive_directory_iterator(directory)){
        curr = split(entry.path().string(), splitchar); //split the path by splitChar(\\) and give the last string to get the file name
        if(curr == "this is not a file"){
            continue;
        }
        transform(curr.begin(), curr.end(), curr.begin(), ::tolower);
        if (find(arr.begin(), arr.end(), curr) != arr.end()){//check if this file name is already in the vector
            //if its in the vector do nothing (don't want repeat file names)
        }
        else{ //if its not in the vector, add it 
            arr.push_back(curr); 
        }
    }
    arr = sortStrings(arr);
    ofstream file;
    file.open("SortedFileNames.txt"); //open output file
    if(file.is_open()){
        for(string s: arr){
            file << s + "\n"; //write every filename in the arr vector to the output file
        }
        file.close(); //close the file
    }
    else{
        cout << "Error opening file" << endl;
    }
    return 0;
}