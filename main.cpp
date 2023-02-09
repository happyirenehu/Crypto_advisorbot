//
//  main.cpp
//  test string cin
//
//  Created by Irene's macbook on 2022/12/13.
//  Copyright © 2022 Irene Hu. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "CSVReader.h"
#include "OrderBookEntry.h"
#include "Advisorbot.h"

using namespace std;

int main(int argc, char * argv[]) {
    Advisorbot o;
    o.init();
    
    
//    string command;
//    cout << "Hello, World!\n";
//    cout << "Type a command, seperate by space" << endl;
//
//    getline(cin, command);
//    cout << "You typed command: " << command << endl;
//    string line;
//    string load;
//    string help = "help";
//    string productname = "prod";
//
//
//    //spilt the string
//    vector<string> v;
//    string s;
//
//    while(true){
//    cout << "Type a command" << endl;
//
//    getline(cin, line);
//
//
//    stringstream ss(line);
//
//
////    if(line.size() == 3){
////
////    }
//    while (getline(ss, s, ' ')) {
//        // store token string in the vector
//        v.push_back(s);
//    }
//
//
//    cout << "you typed " << line <<endl;
//    cout << "The size of your vecotor is: " << v.size() << endl;
//
//
//    if(v.size()==1){
//        if (find(v.begin(), v.end(), "help") != v.end()){
//                // Element in vector.
//                //substring found
//                cout << "List all available products" << endl;
//            }
//        else if (find(v.begin(), v.end(), "prod") != v.end()){
//            // Element in vector.
//            //substring found
//            cout << "List all available products" << endl;
//            //CSVReader::readCSV("20200601.csv");
//            Advisorbot m;
//            m.listProduct();
//            cout << endl;
//
//        }
//        else if (find(v.begin(), v.end(), "time") != v.end()){
//            // Element in vector.
//            //substring found
//            cout << "state current time in dataset, i.e. which timeframe are we looking at" << endl;
//            string t;
//            Advisorbot m;
//            m.printTime();
//        }
//        else if (find(v.begin(), v.end(), "step") != v.end()){
//            // Element in vector.
//            //substring found
//            cout << "move to next time step" << endl;
//            Advisorbot m;
//            m.nextTimeFrame();
//        }else if(find(v.begin(), v.end(), "p") != v.end()){
//            cout <<"Prdict"<<endl;
//            Advisorbot o;
//            o.printPredict(10);
//        }else cout << "invalid input"<<endl;
//    }
//
//    if(v.size() == 2){
//        if (find(v.begin(), v.end(), "help") != v.end()){
//            // Element in vector.
//            //substring found
//            if(find(v.begin(), v.end(), "avg") != v.end()){
//                cout <<"average ETH/BTC bid 10 -> average ETH/BTC bid over last 10 time steps"<<endl;
//            }else if(find(v.begin(), v.end(), "prod") != v.end()){
//                cout <<"prod -> List all avaliable products."<<endl;
//            }else if(find(v.begin(), v.end(), "min") != v.end()){
//                cout <<" Find the lowest price: min ETH/BTC ask ->The min ask for ETH/BTC is 1.0"<<endl;
//            }else if(find(v.begin(), v.end(), "max") != v.end()){
//                cout <<"Find maximum bid or ask for product in current time stepmax: ETH/BTC ask -> The max ask for ETH/BTC is 1.0"<<endl;
//            }else cout <<"no command can be found!" << endl;
//        }
//    }
//    if(v.size() == 3){
//        if(find(v.begin(), v.end(), "min") != v.end()){
//            cout << "min" << endl;
//            Advisorbot m;
//            //m.printMin("ETH/BTC", OrderBookType::ask);
//            m.printMin(v[1], v[2]);
//        }
//        if(find(v.begin(), v.end(), "max") != v.end()){
//            Advisorbot m;
//            m.printMax(v[1], v[2]);
//        }
//        if(find(v.begin(), v.end(), "avg") != v.end()){
//            Advisorbot m;
//            m.printAvg(v[1], v[2]);
//        }
//    }
//
//    //clear previous getline input by clear all the elements in vector v to 0
//    if(v.size() > 0){
//            v.clear();
//        }
//    }
////    if(line == help){
////        //map<string, int> map;
////        cout <<"The available commands are help, help <cmd>, avg, time" << help <<endl;
////    }
////
////    if(v.size() == 1){
////        if(line.find("prod", 0) ==0){
////            cout << "List all available products" << endl;
////        }
////        if(line.find("help", 0) ==0){
////            cout << "The available commands are help, help <cmd>, avg, time" << endl;
////        }
////    }
////
////    if(v.size() == 2){
////        if(line.find("help", 0) == 0 && line.find("avg", 1,1) == 1){
////            cout << "Avg is to calculate the average price" <<endl;
////        }
////    }
////
////    if(line.find("help", 0) ==0 && line.find("prod", 1) ==0){
////        cout << "List all available products" << endl;
////    }//else cout << "Can't find command"<<endl;
//
   
  
}
