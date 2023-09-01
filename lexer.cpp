#include <iostream>
#include <string>
#include <regex>
#include <fstream> 
#include <vector>
using namespace std;

int main(void){
ifstream file; 
file.open("filee.txt");
if (file.is_open()) {
    string line;
    vector<string> keywords, operators, others, numbers, punc, strings, identifiers;
while (getline(file, line)) {
    regex keywords_regex("read|show|int|float|double|default|main|if|elif|else|for|while|do|def|break|continue|bool|struct|switch|case|void|return");
    regex operators_regex("==|!=|<=|>=|\\+\\+|\\-\\-|\\+=|\\-=|\\*=|/=|%=|\\|\\||&&|<<|>>|\\+|\\-|\\*|/|%|=|!|\\||&|~");
    regex string_regex("\".*\"");
    regex others_regex("sizeof|\\?:|\\$|->|\\.");
    regex integers_regex("[+-]?\\d+(?!\\.)");
    regex float_regex("[+-]?[0-9]*(\\.[0-9]+)?");
    regex punc_regex("[,;(){}\\[\\]']");
    regex identifiers_regex("[a-zA-Z_][a-zA-Z0-9_]*([ ]*)?");
    smatch match;
while(regex_search(line, match, keywords_regex)){
    keywords.push_back(match.str(0));
    line = match.suffix().str(); }
while(regex_search(line, match, operators_regex)){
    operators.push_back(match.str(0));
    line = match.suffix().str(); }
while(regex_search(line, match, others_regex)){
    others.push_back(match.str(0));
    line = match.suffix().str(); }
while(regex_search(line, match, integers_regex)){
    numbers.push_back(match.str(0));
    line = match.suffix().str(); }
while(regex_search(line, match, float_regex)){ 
    numbers.push_back(match.str(0));
    line = match.suffix().str(); }
while(regex_search(line, match, punc_regex)){
    punc.push_back(match.str(0));
    line = match.suffix().str(); }  
while(regex_search(line, match, string_regex)){
    strings.push_back(match.str(0));
    line = match.suffix().str(); }
while(regex_search(line, match, identifiers_regex)){
    identifiers.push_back(match.str(0));
    line = match.suffix().str(); }
    }
    cout << "Keywords: " ;
     for (const auto& str : keywords) {
        cout << str << ", ";
    }

    cout << "\nOperators: " ;
     for (const auto& str : operators) {
        cout << str << ", ";
    }

    cout << "\nNumbers: " ;
     for (const auto& str : numbers) {
        cout << str << ", ";
    }

cout << "\nPunctuations: " ;
     for (const auto& str : punc) {
        cout << str << ", ";
    }

cout << "\nStrings: " ;
     for (const auto& str : strings) {
        cout << str << ", ";
    }

cout << "\nIdentifiers: " ;
     for (const auto& str : identifiers) {
        cout << str << ", ";
    }

    cout << "\nOthers: \n" ;
     for (const auto& str : others) {
        cout << str << ", ";
    }
    file.close(); 
}
else{
        cout << "File doesnt exist." << endl;
    }
    
    }