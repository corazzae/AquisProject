#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <vector>

struct Order {

	Order(bool side, uint16_t quantity, uint64_t price, uint16_t orderID) :
		m_side(side), m_quantity(quantity), m_price(price), m_orderID(orderID) {}

	bool m_side; //0 = BUY, 1 = SELL
	uint16_t m_quantity;
	uint64_t m_price; //assuming scaling factor is applied to make price integer? 
	uint16_t m_orderID;
};

class Security
{
private:

	std::vector<std::unique_ptr<Order>> m_orderList;

	uint16_t m_securityID;
	uint16_t m_tickTableID;
	std::string m_umtf;
	std::string m_isin;
	std::string m_currency;
	std::string m_mic;

	//flags
	bool m_closingEnabled;
	bool m_testStock;
	bool m_illiquid;
	bool m_live;
	bool m_aodEnabled;

public:

	void addOrder(bool side, uint16_t quantity, uint64_t price, uint16_t orderID);
	std::vector<std::unique_ptr<Order>> const& getOrders();

	void setSecurityID(uint16_t securityID);
	void setTickTableID(uint16_t tickTableID);
	void setUMTF(std::string umtf);
	void setISIN(std::string isin);
	void setCurrency(std::string currency);
	void setMIC(std::string mic);
	void setClosingEnabled(bool closingEnabled);
	void setTestStock(bool testStock);
	void setIlliquid(bool illiguid);
	void setLive(bool live);
	void setaodEnabled(bool aodEnabled);
	uint16_t getSecurityID();
	uint16_t getTickTable();
	std::string getUMTF();
	std::string getISIN();
	std::string getCurrency();
	std::string getMIC();
	bool getClosingEnabled();
	bool getTestStock();
	bool getIlliquid();
	bool getLive();
	bool getaodEnabled();

};

