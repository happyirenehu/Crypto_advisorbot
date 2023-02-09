//
//  advisorbot.hpp
//  test string cin
//
//  Created by Irene's macbook on 2022/12/24.
//  Copyright © 2022 Irene Hu. All rights reserved.
//
#pragma once

#ifndef advisorbot_h
#define advisorbot_h

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
 
class Advisorbot
{
public:
    Advisorbot();
    /** Call this to start the sim */
    void init();
    
    
private:
    void printHelp();
    void gotoNextTimeframe();

    void listProduct();
    void printMenu();
    void printTime();
    void printMin(std::string product_name, std::string orderBookType);
    void printMax(std::string product_name, std::string orderBookType);
    void nextTimeFrame();
    void previousTimeFrame();
    void printAvg(std::string product_name, std::string orderBookType, std::string timestamp);
    void printPredict(std::string product_name, std::string orderBookType, std::string timestamp);
    void printVolume(std::string product);
    void printPrevTime();
    std::string currentTime;
    unsigned int timeStepTaken = 0;
    
    OrderBook orderBook{"20200601.csv"};
    
    int saleCount;
//    void printMarketStats();
//  void getBTC_USDT(std::string product_name, OrderBookType orderType);
//  void getCurrentTime();
//  int getUserOption();
//  void processUserOption(int userOption);
};

#endif /* advisorbot_h
*/
