#pragma once

#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>

class OrderBook
{
    public:
    /** construct, reading a csv data file */
        OrderBook(std::string filename);
    /** return vector of all know products in the dataset*/
        std::vector<std::string> getKnownProducts();
    /** return vector of Orders according to the sent filters*/
        std::vector<OrderBookEntry> getOrders(OrderBookType type, 
                                              std::string product, 
                                              std::string timestamp);
    
        std::vector<OrderBookEntry> getOrders2(OrderBookType type,
                                               std::string product,
                                               std::string timestamp,
                                               double price,
                                               std::vector<OrderBookEntry> vector);
        /** returns the earliest time in the orderbook*/
    std::string getEarliestTime();
        /** returns the next time after the 
         * sent time in the orderbook  
         * If there is no next timestamp, wraps around to the start
         * */
        std::string getNextTime(std::string timestamp);
        std::string getPreTime(std::string timestamp);
        void insertOrder(OrderBookEntry& order);
    
        std::vector<OrderBookEntry> getVolStoragePrice();

        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp);
        std::vector<OrderBookEntry> matchAsksToBids1(std::string product, std::string timestamp);

        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        static double getLowPrice(std::vector<OrderBookEntry>& orders);
        static double getAvgPrice(std::vector<OrderBookEntry>& orders);
        static double predict(std::vector<OrderBookEntry>& orders, int timestamp);
        double getPrice(std::vector<OrderBookEntry>& orders);
        //only read one input
        static double  getOneHighPrice(std::vector<OrderBookEntry>& orders);
    
    
        std::vector<OrderBookEntry> vol_storage;
        std::vector<OrderBookEntry> ask_storage;
    
        std::vector<OrderBookEntry> wait_for_next_match;
    
        std::vector<OrderBookEntry> previous_storage;
        std::vector<OrderBookEntry> n;

private:
        std::vector<OrderBookEntry> orders;

};
