#include "Security.h"
#include "Security.h"

void Security::addOrder(bool side, uint16_t quantity, uint64_t price, uint16_t orderID)
{
	m_orderList.emplace_back(std::make_unique<Order>(side, quantity, price, orderID));
}

std::vector<std::unique_ptr<Order>> const& Security::getOrders()
{
	return m_orderList;
}

void Security::setSecurityID(uint16_t securityID) {
	m_securityID = securityID;
}

void Security::setTickTableID(uint16_t tickTableID) {
	m_tickTableID = tickTableID;
}

void Security::setUMTF(std::string umtf) {
	m_umtf = umtf;
}

void Security::setISIN(std::string isin) {
	m_isin = isin;
}

void Security::setCurrency(std::string currency) {
	m_currency = currency;
}

void Security::setMIC(std::string mic) {
	m_mic = mic;
}

void Security::setClosingEnabled(bool closingEnabled) {
	m_closingEnabled = closingEnabled;
}

void Security::setTestStock(bool testStock) {
	m_testStock = testStock;
}

void Security::setIlliquid(bool illiguid) {
	m_illiquid = illiguid;
}

void Security::setLive(bool live) {
	m_live = live;
}

void Security::setaodEnabled(bool aodEnabled) {
	m_aodEnabled = aodEnabled;
}

uint16_t Security::getSecurityID() {
	return m_securityID;
}

uint16_t Security::getTickTable() {
	return m_tickTableID;
}

std::string Security::getUMTF() {
	return m_umtf;
}

std::string Security::getISIN() {
	return m_isin;
}

std::string Security::getCurrency() {
	return m_currency;
}

std::string Security::getMIC() {
	return m_mic;
}

bool Security::getClosingEnabled() {
	return m_closingEnabled;
}

bool Security::getTestStock() {
	return m_testStock;
}

bool Security::getIlliquid() {
	return m_illiquid;
}

bool Security::getLive() {
	return m_live;
}

bool Security::getaodEnabled() {
	return m_aodEnabled;
}
