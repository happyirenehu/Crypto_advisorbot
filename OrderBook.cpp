#include "OrderBook.h"
#include "CSVReader.h"
#include <map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>
/** construct, reading a csv data file */
OrderBook::OrderBook(std::string filename)
{
    orders = CSVReader::readCSV(filename);
}
/** return vector of all know products in the dataset*/
std::vector<std::string> OrderBook::getKnownProducts()
{
    std::vector<std::string> products;
    std::map<std::string,bool> prodMap;

    for (OrderBookEntry& e : orders)
    {
        prodMap[e.product] = true;
    }
    
    // now flatten the map to a vector of strings
    for (auto const& e : prodMap)
    {
        products.push_back(e.first);
    }

    return products;
}
std::vector<OrderBookEntry> OrderBook::getVolStoragePrice()
{   std::vector<OrderBookEntry> s;
//    std::map<int, OrderBookEntry> prodMap;
//
//
//
//    // now flatten the map to a vector of strings
//    for (auto const& e : prodMap)
//    {
//        s.push_back(e.first);
//    }
    
    return s;
}

/** return vector of Orders according to the sent filters*/
std::vector<OrderBookEntry> OrderBook::getOrders(OrderBookType type,
                                        std::string product, 
                                        std::string timestamp)
{
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e : orders)
    {
        if (e.orderType == type && 
            e.product == product && 
            e.timestamp == timestamp )
            {
                orders_sub.push_back(e);
                //std::cout << "order found" <<std::endl;
            }
    }
    return orders_sub;
}
std::vector<OrderBookEntry> OrderBook::getOrders2(OrderBookType type,
                                                 std::string product,
                                                 std::string timestamp,
                                                  double price,
                                                  std::vector<OrderBookEntry> vector)
{
    std::vector<OrderBookEntry> orders_sub;
    for (OrderBookEntry& e : vector)
    {
        if (e.orderType == type &&
            e.product == product &&
            e.timestamp == timestamp &&
            e.price == price)
        {
            orders_sub.pop_back();
            std::cout << "order duplicate found" <<std::endl;
        }else {
            orders_sub.push_back(e);

        }
    }
    return orders_sub;
}
double OrderBook::getPrice(std::vector<OrderBookEntry>& orders){
     return 0;
}

double OrderBook::getHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    for (OrderBookEntry& e : orders)
    {
        if (e.price > max)max = e.price;
    }
    return max;
}

double OrderBook::getOneHighPrice(std::vector<OrderBookEntry>& orders)
{
    double max = orders[0].price;
    for (OrderBookEntry& e : orders){
        if (e.price > max)max = e.price;
    }
    return max;
}


double OrderBook::getLowPrice(std::vector<OrderBookEntry>& orders)
{
    double min = orders[0].price;
    for (OrderBookEntry& e : orders)
    {
        if (e.price < min)min = e.price;
    }
    return min;
}

double OrderBook::getAvgPrice(std::vector<OrderBookEntry>& orders)
{
    double sum = 0;
    for (OrderBookEntry& e : orders)
    {
        sum = e.price + sum;
    }
    
    return sum/orders.size();
}

double OrderBook::predict(std::vector<OrderBookEntry>& orders, int timestamp) {
    double sum = 0;
    
    for(OrderBookEntry& e: orders){
        sum = e.price + sum;
    }
    
    return sum / timestamp;
}

std::string OrderBook::getEarliestTime()
{
    return orders[0].timestamp;
}

std::string OrderBook::getNextTime(std::string timestamp)
{
    std::string next_timestamp = "";
    for (OrderBookEntry& e : orders)
    {
        if (e.timestamp > timestamp) 
        {
            next_timestamp = e.timestamp;
            std::cout <<"found next time step" << std::endl;
            break;
        }
    }
    if (next_timestamp == "")
    {
        next_timestamp = orders[0].timestamp;
    }
    return next_timestamp;
}

std::string OrderBook::getPreTime(std::string timestamp)
{
    std::string pre_timestamp = "";
    int index = 0;
    for (OrderBookEntry& e : orders)
    {
        if (e.timestamp == timestamp && timestamp != orders[0].timestamp) { // matches current timestep to dataset's timestep & not the first timestep
            pre_timestamp = orders[index-1].timestamp; // minus 1 to the index to get the previous timestep
            break;
        } else {
            index = index + 1;
        }
    }

    if (pre_timestamp == "")
    {
        pre_timestamp = orders[0].timestamp;
    }
    return pre_timestamp;
}


void OrderBook::insertOrder(OrderBookEntry& order)
{
    orders.push_back(order);
    std::sort(orders.begin(), orders.end(), OrderBookEntry::compareByTimestamp);
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids(std::string product, std::string timestamp)
{
// asks = orderbook.asks
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask,
                                                 product,
                                                 timestamp);
// bids = orderbook.bids
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid,
                                                 product,
                                                    timestamp);
    //
    std::vector<OrderBookEntry> vol_storage;
    // check if there were any ask left that couldn't match with bid in the previous timeframe
    bool unmatch = false;
    int count = 0;


    for(OrderBookEntry& e: n){
        asks.push_back(e);
    }


    // sales = []
    std::vector<OrderBookEntry> sales;
    // sort asks lowest first
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    // sort bids highest first
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
    // for ask in asks:
    std::cout << "max ask " << asks[asks.size()-1].price << std::endl;
    std::cout << "min ask " << asks[0].price << std::endl;
    std::cout << "max bid " << bids[0].price << std::endl;
    std::cout << "min bid " << bids[bids.size()-1].price << std::endl;



    std::cout << "ask size: " << asks.size() << std::endl;
    std::cout << "bid size: " << bids.size() << std::endl;
    for (OrderBookEntry& ask : asks)
    {
        //std::cout << "Ask p: " << ask.price << " a: " << ask.amount << std::endl;
    //     for bid in bids:
        for (OrderBookEntry& bid : bids)
        {
            //std::cout << "bid p: " << bid.price << " a: " << bid.amount << std::endl;

    //         if bid.price >= ask.price # we have a match
            if (bid.price >= ask.price)
            {
                std::cout << "bid price is right " << std::endl;
                std::cout << bid.price << std::endl;

                //ask_storage.erase(std::remove(ask_storage.begin(), ask_storage.end(), ask.price), ask_storage.end());

                 // std::vector<OrderBookEntry> ss = remove(ask_storage.begin(), ask_storage.end(), ask);
//                if(find(ask_storage.begin(), ask_storage.end(), ask.price) != ask_storage.end()){
//                    std::cout << "F ";
//                }
    //             sale = new order()
    //             sale.price = ask.price
                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::sale};
    //             # now work out how much was sold and
    //             # create new bids and asks covering
    //             # anything that was not sold
    //             if bid.amount == ask.amount: # bid completely clears ask
                if (bid.amount == ask.amount)
                {
    //                 sale.amount = ask.amount
                    sale.amount = ask.amount;
    //                 sales.append(sale)
                    sales.push_back(sale);
    //                 bid.amount = 0 # make sure the bid is not processed again
                    bid.amount = 0;
    //                 # can do no more with this ask
    //                 # go onto the next ask
    //                 break
                    break;
                }
    //           if bid.amount > ask.amount:  # ask is completely gone slice the bid
                if (bid.amount > ask.amount)
                {
    //                 sale.amount = ask.amount
                    sale.amount = ask.amount;
    //                 sales.append(sale)
                    sales.push_back(sale);
    //                 # we adjust the bid in place
    //                 # so it can be used to process the next ask
    //                 bid.amount = bid.amount - ask.amount
                    bid.amount =  bid.amount - ask.amount;
    //                 # ask is completely gone, so go to next ask
    //                 break
                    break;
                }


    //             if bid.amount < ask.amount # bid is completely gone, slice the ask
                if (bid.amount < ask.amount)
                {
    //                 sale.amount = bid.amount
                    sale.amount = bid.amount;
    //                 sales.append(sale)
                    sales.push_back(sale);
    //                 # update the ask
    //                 # and allow further bids to process the remaining amount
    //                 ask.amount = ask.amount - bid.amount
                    ask.amount = ask.amount - bid.amount;
    //                 bid.amount = 0 # make sure the bid is not processed again
                    bid.amount = 0;
    //                 # some ask remains so go to the next bid
    //                 continue
                    continue;
                }
            }else {
                //std::cout << "bid price not match" << std::endl;
                //std::cout << "bid price: "<< bid.price<< " "  << "ask price: "<< ask.price<< std::endl;
                //
                //std::cout << "unmatched ask price: " << ask.price << std::endl;
                unmatch = true;
            }
        }
        if(unmatch == true){
            std::cout << "add one more unmtached ask price " << ask.price <<  std::endl;
            vol_storage.push_back(ask);
            n = getOrders2(OrderBookType::ask, product, timestamp, ask.price, vol_storage);

            //std::cout << n.price;
            unmatch = false;
            count ++;
        }
    }
    std::cout << "ask_storage size: " << vol_storage.size() << std::endl;
    std::cout << "ask_storage:";
    for(OrderBookEntry& e : vol_storage){
        std::cout << " " << e.price;
    }

    std::cout <<std::endl;
    return sales;
}

std::vector<OrderBookEntry> OrderBook::matchAsksToBids1(std::string product, std::string timestamp)
{
    // asks = orderbook.asks
    std::vector<OrderBookEntry> asks = getOrders(OrderBookType::ask,
                                                 product,
                                                 timestamp);
    // bids = orderbook.bids
    std::vector<OrderBookEntry> bids = getOrders(OrderBookType::bid,
                                                 product,
                                                 timestamp);
    //
    //store the unmatch ask

    // check if there were any ask left that couldn't match with bid in the previous timeframe
    //bool unmatch = false;
    //int count = 0;
    
    
//    for(OrderBookEntry& e: n){
//        asks.push_back(e);
//    }
    
    //add the previous unmatched ask to compare with bids in the next time frame
    for(OrderBookEntry& e: wait_for_next_match){
        asks.push_back(e);
    }
    
      //print out the unmatched asks and amount left
//    for(OrderBookEntry& i : wait_for_next_match){
//
//        std::cout << "wait_for_next_match currently holds, price: " << i.price  << " " << " amount: "<<  i.amount << std::endl;
//
//    }
    
    // sales = []
    std::vector<OrderBookEntry> sales;
    // sort asks lowest first
    std::sort(asks.begin(), asks.end(), OrderBookEntry::compareByPriceAsc);
    // sort bids highest first
    std::sort(bids.begin(), bids.end(), OrderBookEntry::compareByPriceDesc);
    // for ask in asks:
    std::cout << "max ask " << asks[asks.size()-1].price << std::endl;
    std::cout << "min ask " << asks[0].price << std::endl;
    std::cout << "max bid " << bids[0].price << std::endl;
    std::cout << "min bid " << bids[bids.size()-1].price << std::endl;
    
    //bid = 買方  ask ＝ 賣方
    // if the maximum bid price is >= minimum asking
    //買的最高 >= 賣的最低 才會成交
    double min_ask = asks[0].price;
    double max_bid = bids[0].price;
    
    if(max_bid >= min_ask){
        std::cout << "max bid >= min ask: sale succesful" << std::endl;
        
    }else {
        std::cout << "min ask >= max bid: sale FAIL" << std::endl;
        std::cout << "Add the ask to wait_for_next_match" << std::endl;
        
        for(OrderBookEntry& ask: asks){
            wait_for_next_match.push_back(ask);
        }
//        for(OrderBookEntry& e : wait_for_next_match){
//            std::cout << "wait_for_next_match price: "<< " " << e.price << std::endl;
//        }
    }
    
    std::cout << "ask size: " << asks.size() << std::endl;
    std::cout << "bid size: " << bids.size() << std::endl;
    for (OrderBookEntry& ask : asks)
    {
        //std::cout << "Ask p: " << ask.price << " a: " << ask.amount << std::endl;
        //     for bid in bids:
        if(ask.amount == 0){
            std::cout << "ask amount is zero" << std::endl;
        }
        for (OrderBookEntry& bid : bids)
        {
            //std::cout << "bid p: " << bid.price << " a: " << bid.amount << std::endl;
           
            //         if bid.price >= ask.price # we have a match
            if (bid.price >= ask.price)
            {
                if(ask.amount > 0){
                    //std::cout << "bid price is right " << std::endl;
                }
                //std::cout << bid.price << std::endl;
                
                //ask_storage.erase(std::remove(ask_storage.begin(), ask_storage.end(), ask.price), ask_storage.end());
                
                // std::vector<OrderBookEntry> ss = remove(ask_storage.begin(), ask_storage.end(), ask);
                //                if(find(ask_storage.begin(), ask_storage.end(), ask.price) != ask_storage.end()){
                //                    std::cout << "F ";
                //                }
                //             sale = new order()
                //             sale.price = ask.price
                OrderBookEntry sale{ask.price, 0, timestamp, product, OrderBookType::sale};
                //             # now work out how much was sold and
                //             # create new bids and asks covering
                //             # anything that was not sold
                //             if bid.amount == ask.amount: # bid completely clears ask
                if (bid.amount == ask.amount)
                {
                    //                 sale.amount = ask.amount
                    sale.amount = ask.amount;
                    //                 sales.append(sale)
                    sales.push_back(sale);
                    //                 bid.amount = 0 # make sure the bid is not processed again
                    bid.amount = 0;
                    //                 # can do no more with this ask
                    //                 # go onto the next ask
                    //                 break
                    break;
                }
                //           if bid.amount > ask.amount:  # ask is completely gone slice the bid
                if (bid.amount > ask.amount)
                {
                    //                 sale.amount = ask.amount
                    sale.amount = ask.amount;
                    //                 sales.append(sale)
                    sales.push_back(sale);
                    //                 # we adjust the bid in place
                    //                 # so it can be used to process the next ask
                    //                 bid.amount = bid.amount - ask.amount
                    bid.amount =  bid.amount - ask.amount;
                    //                 # ask is completely gone, so go to next ask
                    //                 break
                    break;
                }
                
                
                //             if bid.amount < ask.amount # bid is completely gone, slice the ask
                if (bid.amount < ask.amount)
                {
                    //                 sale.amount = bid.amount
                    sale.amount = bid.amount;
                    //                 sales.append(sale)
                    sales.push_back(sale);
                    //                 # update the ask
                    //                 # and allow further bids to process the remaining amount
                    //                 ask.amount = ask.amount - bid.amount
                    ask.amount = ask.amount - bid.amount;
                    //                 bid.amount = 0 # make sure the bid is not processed again
                    bid.amount = 0;
                    //                 # some ask remains so go to the next bid
                    //                 continue
                    continue;
                }
            }else {
                //std::cout << "bid price not match" << std::endl;
                //std::cout << "bid price: "<< bid.price<< " "  << "ask price: "<< ask.price<< std::endl;
                //
                //std::cout << "unmatched ask price: " << ask.price << std::endl;
                //unmatch = true;
            }
        }
//        if(unmatch == true){
//            std::cout << "add one more unmtached ask price " << ask.price <<  std::endl;
//            //add the unmatched ask to ask_storage
//            ask_storage.push_back(ask);
//            //n = getOrders2(OrderBookType::ask, product, timestamp, ask.price, ask_storage);
//
//            //std::cout << n.price;
//            unmatch = false;
//            //count ++;
//        }
    }

    
//    std::cout << "ask_storage size: " << ask_storage.size() << std::endl;
//    std::cout << "ask_storage:";
//    for(OrderBookEntry& e : ask_storage){
//        std::cout << " " << e.price;
//    }
//
//    std::cout <<std::endl;
    return sales;
}

