#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

void print_result(vector<string> name,vector<int> point){
    for (int i=0;i<name.size();i++){
        cout << name[i] << " " << point[i] <<endl;
    }
}

int main(){
    ifstream in_file {"response.txt"};
    string result{};
    string response{};
    string name{};
    int point{0};
    double sum;
    int count{0}; //dem so sv
    vector<string> namevt{};    //vector chứa các tên
    vector<int> responsevt{};   //vector chứa các câu trả lời
    if (!in_file) {
        cout << "file opening fail" <<endl;
        return -1;
    }
    in_file >> result;
    while(!in_file.eof()){
        in_file >> name;
        namevt.push_back(name);     //thêm tên vừa được đọc vào vector
        in_file >> response;
        for (int i=0;i<result.length();i++){
            if (toupper(result[i]) == toupper(response[i])){
                point +=1;}
        }
        responsevt.push_back(point);
        sum +=point;
        point =0;
    }
    print_result(namevt,responsevt);
    cout << "average = " << sum/responsevt.size() << endl; 
}