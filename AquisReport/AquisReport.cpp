
#include <iostream>
#include "Security.h"
#include <sstream>
#include <fstream>
#include <string>
#include <map>


std::string getKeyValue(std::string line, std::string key) {
    std::size_t start = line.find(key);

    if (start != std::string::npos) {
        line = line.substr(start);
        std::string value = line.substr(0, line.find_first_of(",}"));
        value = value.substr(value.find(":") + 1);
        if (value.front() == '"') {
            value.erase(0, 1);
            value.erase(value.size() - 1);
        }

        return value;
    }

    return std::string("");
}

std::vector<std::string> generateReport(std::vector<std::unique_ptr<Security>> const& securities) {
    std::vector<std::string> report;

    for (auto& security : securities) {
        std::string securityAggregate;
        uint64_t totalBuyCount = 0;
        uint64_t totalSellCount = 0;
        uint64_t totalBuyQuantity = 0;
        uint64_t totalSellQuantity = 0;
        double averageBuyPrice = 0;
        double averageSellPrice = 0;
        long long maxBuyPrice = 0;
        long long maxSellPrice = 0;

        std::vector<std::unique_ptr<Order>> const& orders = security->getOrders();
        for (auto& order : orders) {

            if (order->m_side == true) {//BUY
                totalBuyCount++;
                totalBuyQuantity += order->m_quantity;
                if (order->m_price > maxBuyPrice) {
                    maxBuyPrice = order->m_price;
                }
                averageBuyPrice += (order->m_price - averageBuyPrice) * (order->m_quantity / (double)totalBuyQuantity);
            }
            else { //SELL
                totalSellCount++;
                totalSellQuantity += order->m_quantity;
                if (order->m_price > maxSellPrice) {
                    maxSellPrice = order->m_price;
                }
                averageSellPrice += ((double)order->m_price - averageSellPrice) * ((double)order->m_quantity / (double)totalSellQuantity);
            }
        }

        securityAggregate =
            security->getISIN() + "\t" +
            security->getCurrency() + "\t" +
            std::to_string(totalBuyCount) + "\t" +
            std::to_string(totalSellCount) + "\t" +
            std::to_string(totalBuyQuantity) + "\t" +
            std::to_string(totalSellQuantity) + "\t" +
            std::to_string(averageBuyPrice) + "\t" +
            std::to_string(averageSellPrice) + "\t" +
            std::to_string(maxBuyPrice) + "\t" +
            std::to_string(maxSellPrice) + "\t";

        report.emplace_back(securityAggregate);

    }

    return report;
}

std::vector<std::unique_ptr<Security>> parseMarketData(std::string path) {

    std::vector<std::unique_ptr<Security>> securities;

    std::ifstream marketData(path);
    std::string line;

    while (std::getline(marketData, line))
    {
        //std::cout << line;
        std::string value = getKeyValue(line, "\"msgType_\"");
        if (value == "8") { //Reference data
            auto security = std::make_unique<Security>();
            security->setSecurityID(std::stoi(getKeyValue(line, "\"securityId_\"")));
            security->setISIN(getKeyValue(line, "\"isin_\""));
            security->setCurrency(getKeyValue(line, "\"currency_\""));

            securities.emplace_back(std::move(security));
        }
        else if (value == "12") { //Order
            uint16_t securityID = std::stoi(getKeyValue(line, "\"securityId_\""));
            auto it = std::find_if(std::begin(securities), std::end(securities),
                [&](std::unique_ptr<Security>& sec) { return sec->getSecurityID() == securityID; });

            if (it != securities.end()) { //security found
                std::string sideString = getKeyValue(line, "\"side_\"");
                bool side;
                if (sideString == "BUY") {
                    side = true;
                }
                else {
                    side = false;
                }
                uint16_t quantity = std::stoi(getKeyValue(line, "\"quantity_\""));
                long long price = std::stoll(getKeyValue(line, "\"price_\""));
                uint16_t orderID = std::stoi(getKeyValue(line, "\"orderId_\""));
                (*it)->addOrder(side, quantity, price, orderID);
            }

        }

    }

    return securities;
}

int main()
{

    std::vector<std::unique_ptr<Security>> secs = parseMarketData("pretrade.txt");
    std::vector<std::string> report = generateReport(secs);

    std::ofstream file;
    file.open("newReport.txt");

    for (auto orderAggregate : report) {
        file << orderAggregate << "\n";
    }
    file.close();


}

