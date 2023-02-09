//
//  advisorbot.cpp
//  test string cin
//
//  Created by Irene's macbook on 2022/12/24.
//  Copyright © 2022 Irene Hu. All rights reserved.
//

#include "Advisorbot.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include "OrderBook.h"
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

Advisorbot::Advisorbot()
{
    
    
}

void Advisorbot::init()
{
    //int input;
    currentTime = orderBook.getEarliestTime();

    while(true)
    {
        printMenu();

//        input = getUserOption();
//        processUserOption(input);
    }
}
void Advisorbot::listProduct(){
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << p << ",";
    }
}

void Advisorbot::printTime()
{
    if(timeStepTaken == 0){
        currentTime = orderBook.getEarliestTime();
        std::cout << currentTime << std::endl;
        std::cout << "timeStepTaken:" << timeStepTaken <<std::endl;
    }else if(timeStepTaken > 0){
        //timeStepTaken -= 1;
        std::cout << "current time is: "<< currentTime << std::endl;
        std::cout << "timeStepTaken:" << timeStepTaken <<std::endl;

    }
}
//void Advisorbot::getCurrentTime(){
//    std::cout << currentTime;
//}

void Advisorbot::printMin(std::string product_name, std::string orderBookType){
    //std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    std::vector<OrderBookEntry> entries;
    //std::cout << "product: " << product_name << std::endl;
    OrderBookType orderType = OrderBookEntry::stringToOrderBookType(orderBookType);
    entries = orderBook.getOrders(orderType,
                                  product_name,
                                  currentTime);
    //std::cout << orderBookType << " seen :" << entries.size() << std::endl;
    std::cout << "The min " << orderBookType << " for " << product_name << " is " << OrderBook::getLowPrice(entries) << std::endl;
}

void Advisorbot::printMax(std::string product_name, std::string orderBookType){
    std::vector<OrderBookEntry> entries;
    OrderBookType orderType = OrderBookEntry::stringToOrderBookType(orderBookType);
    //std::cout << "product: " << product_name << std::endl;
    entries = orderBook.getOrders(orderType,
                                  product_name,
                                  currentTime);
    std::cout << "The max " <<  orderBookType << " for " << product_name << " is " << OrderBook::getHighPrice(entries) << std::endl;
}

void Advisorbot::printAvg(std::string product_name, std::string orderBookType, string timestamp){
    std::vector<OrderBookEntry> entries;
    
    // temperory storage for sum of the average prices in each time step
    std::vector<OrderBookEntry> storage;
    
    // convert from string to OrderBookType
    OrderBookType orderType = OrderBookEntry::stringToOrderBookType(orderBookType);
    
    entries = orderBook.getOrders(orderType,
                                  product_name,
                                  currentTime);

    
//    std::cout << "product: " << product_name << std::endl;
//    std::cout << "The average " << product_name << " " <<  orderBookType << " price over the last " << timestamp << " timestamps was " << OrderBook::getAvgPrice(entries) << std::endl;
//    std::cout << orderBookType << " seen :" << entries.size() << std::endl;

    double steps = stoi(timestamp); //convert input string to double
//    std::cout << "how mang timesteps to go back: " << steps;
    
    double sum = 0;
    
    //add the avg price from previou timeframe to sum
   do{
        previousTimeFrame();
//      cout << currentTime << endl;
        steps = steps - 1;
        storage = orderBook.getOrders(orderType,
                                      product_name,
                                      currentTime);
//       cout << "name: " << product_name << endl;
//       cout << "size: " << storage.size() << endl;
//       cout << "avg: " << OrderBook::getAvgPrice(storage) << endl;
         sum = OrderBook::getAvgPrice(storage) + sum;
//       cout << "sum: " << sum <<endl;
   }while(steps > 0 && timeStepTaken > steps);
    
    if(timeStepTaken < steps){
        std::cout << "Warning: You've reached the earliest data, no previous data avaliable." << std::endl;
    }
    
    //calculate the total sum of average price in different time steps
    double t = stoi(timestamp); //count how many timesteps to go back with
    double result = sum/t; //divide total sum by number of time steps taken
    std::cout << "The average " << product_name << " " <<  orderBookType << " price over the last " << timestamp << " timestamps was " << result << std::endl;
    
    //same as above
//    for(std::string const& p :orderBook.getKnownProducts()){
//        if(p == product_name){
//            entries = orderBook.getOrders(orderType, p, currentTime);
//            cout << product_name << endl;
//            std::cout << orderBookType << " seen :" << entries.size() << std::endl;
//
//        }
//    }
 }

void Advisorbot::printPredict(std::string max_min, std::string product_name, std::string orderBookType){
//    std::vector<OrderBookEntry> entries;
    
    // temperory storage for sum of the average prices in each time step
    std::vector<OrderBookEntry> storage;
    
    // convert from string to OrderBookType
    OrderBookType orderType = OrderBookEntry::stringToOrderBookType(orderBookType);
    
//    entries = orderBook.getOrders(orderType,
//                                  product_name,
//                                  currentTime);
    if(timeStepTaken > 0){
        if (max_min == "max")
        {
            if(timeStepTaken == 0){
                cout<< "no previous data avaliable, you've reached the earlier timeframe."<<endl;
            }else{
                int record= timeStepTaken;
                int steps = timeStepTaken;
                double sum = 0;
                do{
                    previousTimeFrame();
                    //cout << currentTime << endl;
                    steps = steps - 1;
                    storage = orderBook.getOrders(orderType,
                                                  product_name,
                                                  currentTime);
//                    cout << "name: " << product_name << endl;
//                    cout << "size: " << storage.size() << endl;
//                    cout << "avg: " << OrderBook::getAvgPrice(storage) << endl;
//                    cout << "high: " << OrderBook::getHighPrice(storage) <<endl;
//                    cout << "low: " << OrderBook::getLowPrice(storage) << endl;
                    sum = OrderBook::getHighPrice(storage) + sum;
                    //cout << "OrderBook::getHighPrice sum: " << sum <<endl;
                }while(timeStepTaken > 0);
                
                cout << "high price sum/timesteptaken: " << sum/record << endl;
                cout << "The prediction for " << max_min  << " " << product_name << " " << orderBookType <<" price is " << sum/record << endl;
            }
        }else if (max_min == "min"){
            if(timeStepTaken == 0){
                cout<< "no previous data avaliable, you've reached the earlier timeframe."<<endl;
            }else{
                int record= timeStepTaken;
                int steps = timeStepTaken;
                double sum = 0;
                do{
                    previousTimeFrame();
                    //      cout << currentTime << endl;
                    steps = steps - 1;
                    storage = orderBook.getOrders(orderType,
                                                  product_name,
                                                  currentTime);
                    //                cout << "name: " << product_name << endl;
                    //                cout << "size: " << storage.size() << endl;
                    //                cout << "avg: " << OrderBook::getAvgPrice(storage) << endl;
                    //                cout << "high: " << OrderBook::getHighPrice(storage) <<endl;
                    //                cout << "low: " << OrderBook::getLowPrice(storage) << endl;
                    sum = OrderBook::getLowPrice(storage) + sum;
                    //                cout << "OrderBook::getLowPrice sum: " << sum <<endl;
                }while(timeStepTaken > 0);
                
                //            cout << "low price sum/timesteptaken: " << sum/record << endl;
                cout << "The prediction for " << max_min  << " " << product_name << " " << orderBookType <<" price is " << sum/record << endl;
            }
        }
        else cout << "invalid input, type help for valid command." << endl;
    }else cout << "not enough previous data to generate prediction, please go to next timeframe." << endl;
}

//parse the argument to make the input change and display only one product
//void Advisorbot::getBTC_USDT(std::string product_name, OrderBookType orderType){
//    std::vector<OrderBookEntry> entries;
//    std::cout << "product: " << product_name << std::endl;
//    entries = orderBook.getOrders(orderType,
//                                  product_name,
//                                  "2020/06/01 11:57:30.328127");
//    std::cout << "Ask seen: " << entries.size() << std::endl;
//    std::cout << "Avg ask: " << OrderBook::getAvgPrice(entries) << std::endl;
//
//}
void Advisorbot::printVolume(std::string product){
        //count the number of inva id sale
        int count = 0;
    
        std::cout <<"now at " << currentTime << std::endl;

        std::vector<OrderBookEntry> vol = orderBook.matchAsksToBids1(product, currentTime);
        
        for(OrderBookEntry& e: vol){
            //std::cout << "sale price: " << e.price << " " << "sale amount: " << e.amount<<  std::endl;
            //eliminate the sales with amount less than 0
            if(e.amount == 0){
                count ++;
            }
//            if(e.amount > 0){
//                vec.push_back(e);
//            }
        }
    
        std::cout << "How many matching sales in this time frame:" << vol.size() - count <<endl;
    
        //count previous succesful sale numbers with current time frame sals numbers
        saleCount += vol.size() - count;
    
        std::cout << "Total sale: " << saleCount<< std::endl;
//        std::cout << "Total sale vec: " <<  vec.size() + saleCount << std::endl;

        //go to next time frame
        currentTime = orderBook.getNextTime(currentTime);
    
        std::cout << "Type volume <product/product> to get the matching sale of next time frame, all previous unmatched asks will be save to compare later" << std::endl;
    
    //      std::vector<OrderBookEntry> vol = orderBook.matchAsksToBids1(product, timestamp);
    //
    //      std::cout << "How many matching sales:" << vol.size() <<endl;
    //      for(OrderBookEntry& e: vol){
    //        std::cout << "sale price: " << e.price << " " << "sale amount: " << e.amount<<  std::endl;
    //        std::vector<OrderBookEntry> vec;
}


void Advisorbot::nextTimeFrame()
{
  //  int count = 0;
    std::cout << "Going to next time frame. " << std::endl;
    currentTime = orderBook.getNextTime(currentTime);
    std::cout <<"now at " << currentTime << std::endl;
    timeStepTaken ++;
    std::cout << "timestep taken: " << timeStepTaken << endl;
    
//    std::vector<OrderBookEntry> vol = orderBook.matchAsksToBids("ETH/BTC", currentTime);
//
//    for(OrderBookEntry& e: vol){
//        //std::cout << "sale price: " << e.price << " " << "sale amount: " << e.amount<<  std::endl;
//        if(e.amount == 0){
//            count ++;
//        }
//    }
//    std::cout << "How many matching sales in this time frame:" << vol.size() - count <<endl;
//    saleCount += vol.size() - count;
//    std::cout << "Total sale: " << saleCount<< std::endl;
//    currentTime = orderBook.getNextTime(currentTime);
}

void Advisorbot::previousTimeFrame()
{
//    std::cout << "Going to previous time frame. " << std::endl;
    currentTime = orderBook.getPreTime(currentTime);
//    std::cout <<"now at " << currentTime << std::endl;
    timeStepTaken --;
//    cout<< "timestep taken: "<< timeStepTaken <<endl;
}

void Advisorbot::printPrevTime(){
    if(timeStepTaken > 0){
    currentTime = orderBook.getPreTime(currentTime);
    timeStepTaken --;
    cout << "go back to previous time: " << currentTime << endl;
    }else cout << "You reached the earlier timeframe;" << endl;
    
}
void Advisorbot::printMenu()
{
    string line;
//    string load;
//    string help = "help";
//    string productname = "prod";
    
    
    vector<string> v;
    string s;
    cout << "Type a command" << endl;
    getline(cin, line);
    
    //spilt the user input string
    stringstream ss(line);
    
    
    //    if(line.size() == 3){
    //
    //    }
    
    //add each split string/words to vector v
    while (getline(ss, s, ' ')) {
        // store token string in the vector
        v.push_back(s);
    }
    
    
    cout << "you typed " << line <<endl;
    
    
    //cout << "The size of your vecotor is: " << v.size() << endl;
    
    //check how many strings is in the command
    
    //if there's only 1 words in v
    if(v.size() == 1){
        if (find(v.begin(), v.end(), "help") != v.end()){
            // Element in vector.
            //substring found
            cout << "The available commands are help, help <cmd>, prod, max, min, avg, time, predict, step, prev, trading volum" << endl;
        }
        else if (find(v.begin(), v.end(), "prev") != v.end()){
            // Element in vector.
            //substring found
            cout << "previous time frame" << endl;
            printPrevTime();
        }
        else if (find(v.begin(), v.end(), "prod") != v.end()){
            // Element in vector.
            //substring found
            cout << "List all available products" << endl;
            listProduct();
            cout << endl;
            
        }
        else if (find(v.begin(), v.end(), "time") != v.end()){
            // Element in vector.
            //substring found
            cout << "state current time in dataset, i.e. which timeframe are we looking at" << endl;
            string t;
            printTime();
        }
        else if (find(v.begin(), v.end(), "step") != v.end()){
            // Element in vector.
            //substring found
            cout << "move to next time step" << endl;
            nextTimeFrame();
        }else cout << "no command can be found! Please type in valid command."<<endl;
    }
    
    //if there's 2 words in v
    if(v.size() == 2){
        if (find(v.begin(), v.end(), "help") != v.end()){
            // Element in vector.
            //substring found
            if(find(v.begin(), v.end(), "avg") != v.end()){
                cout <<"average ETH/BTC bid 10 -> average ETH/BTC bid over last 10 time steps"<<endl;
            }else if(find(v.begin(), v.end(), "prod") != v.end()){
                cout <<"prod -> List all avaliable products."<<endl;
            }else if(find(v.begin(), v.end(), "min") != v.end()){
                cout <<" Find the lowest price: min ETH/BTC ask ->The min ask for ETH/BTC is 1.0"<<endl;
            }else if(find(v.begin(), v.end(), "max") != v.end()){
                cout <<"Find maximum bid or ask for product in current time step: max ETH/BTC ask -> The max ask for ETH/BTC is 1.0"<<endl;
            }else if(find(v.begin(), v.end(), "predict") != v.end()){
                cout << "predict max or min ask or bid for the sent product in all avaliable previous timesteps." << endl;
            }else if(find(v.begin(), v.end(), "volume") != v.end()){
                cout << "volume ETH/BTC -> Total sale: 0. Sale in this time frame: 0" << endl;
            }else cout <<"no command can be found! Please type in valid command." << endl;
        }
        else if (find(v.begin(), v.end(), "volume") != v.end()){
            cout << "Volume of sales:" << endl;
            printVolume(v[1]);
        }
        else cout << "no command can be found! Please type in valid command." << endl;
    }
    //if there's 3 words in v
    if(v.size() == 3){
        if(find(v.begin(), v.end(), "min") != v.end()){
            //cout << "min" << endl;
       
            //m.printMin("ETH/BTC", OrderBookType::ask);
            printMin(v[1], v[2]);
        }
        else if(find(v.begin(), v.end(), "max") != v.end()){
            printMax(v[1], v[2]);
        }else cout <<"no command can be found! Please type in valid command." << endl;
        
    }
    //if there's 4 words in v
    if(v.size() == 4){
        if(find(v.begin(), v.end(), "avg") != v.end()){
            printAvg(v[1], v[2], v[3]);
        }else if(find(v.begin(), v.end(), "predict") != v.end()){
            //cout <<"Prdict"<<endl;
            printPredict(v[1], v[2], v[3]);
        }else cout <<"no command can be found! Please type in valid command." << endl;
    }
    //clear previous getline input by removing all the elements in vector v
    if(v.size() > 0){
        v.clear();
    }
}


void Advisorbot::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}


void Advisorbot::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string& p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
}

//void Advisorbot::printMarketStats()
//{
//    for(std::string const& p :orderBook.getKnownProducts()){
//        std::cout <<" Product " << p << std::endl;
//
//        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask, p, "2020/03/17 17:01:24.884492");
//        std::cout << "Asks seen :" << entries.size() << std::endl;
//        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
//        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
//    }
//}


//
//std::string getCurrentTime(){
//    std::string time = orderBook.getEarliestTime();
//    return time;
//}

//int Advisorbot::getUserOption()
//{
//    int userOption = 0;
//    std::string line;
//    std::cout << "Type in 1-6" << std::endl;
//    std::getline(std::cin, line);
//    try{
//        userOption = std::stoi(line);
//    }catch(const std::exception& e)
//    {
//        //
//    }
//    std::cout << "You chose: " << userOption << std::endl;
//    return userOption;
//}

//void Advisorbot::processUserOption(int userOption)
//{
//    if (userOption == 0) // bad input
//    {
//        std::cout << "Invalid choice. Choose 1-6" << std::endl;
//    }
//    if (userOption == 1)
//    {
//        printHelp();
//    }
//    if (userOption == 2)
//    {
//        printMarketStats();
//    }
//    if (userOption == 3)
//    {
//        enterAsk();
//    }
//    if (userOption == 4)
//    {
//        enterBid();
//    }
//    if (userOption == 5)
//    {
//        printWallet();
//    }
//    if (userOption == 6)
//    {
//        gotoNextTimeframe();
//    }
//}
