#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"

class MerkelMain
{
    public:
        MerkelMain();
        /** Call this to start the sim */
        void init();
    
        void listProduct();
        void printMenu();
        //void getCurrentTime();
        void printTime();
        void printMin(std::string product_name, std::string orderBookType);
        void printMax(std::string product_name, std::string orderBookType);
        void printMarketStats();
        void nextTimeFrame();
        void printAvg(std::string product_name, std::string orderBookType);
        void getBTC_USDT(std::string product_name, OrderBookType orderType);
    
    private:
        void printHelp();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        int getUserOption();
        void processUserOption(int userOption);
    

        std::string currentTime;

    OrderBook orderBook{"20200601.csv"};


};
