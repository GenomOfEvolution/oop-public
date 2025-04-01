#include "CBank.h"
#include <iostream>

// Инициализирует монетарную систему. cash — количество денег в наличном обороте
// При отрицательном количестве денег, выбрасывается BankOperationError
CBank::CBank(Money cash)
{
	if (cash < 0)
	{
		throw BankOperationError("Initial cash should be greater than 0");
	}
	m_cash = cash;
}

// Перевести деньги с исходного счёта (srcAccountId) на целевой (dstAccountId)
// Нельзя перевести больше, чем есть на исходном счёте
// Нельзя перевести отрицательное количество денег
// Исключение BankOperationError выбрасывается, при отсутствии счетов или
// недостатке денег на исходном счёте
// При отрицательном количестве переводимых денег выбрасывается std::out_of_range
void CBank::SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	ValidateMoney(amount);

	auto src = GetAccount(srcAccountId);
	auto dst = GetAccount(dstAccountId);

	if (src->second < amount)
	{
		throw BankOperationError("Not enough money in src account");
	}

	src->second -= amount;
	dst->second += amount;
}

bool CBank::TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount)
{
	try
	{
		SendMoney(srcAccountId, dstAccountId, amount);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return false;
	}

	return true;
}

// Возвращает количество наличных денег в обороте
Money CBank::GetCash() const noexcept
{
	return m_cash;
}

// Сообщает о количестве денег на указанном счёте
// Если указанный счёт отсутствует, выбрасывается исключение BankOperationError
Money CBank::GetAccountBalance(AccountId accountId) const
{
	return GetAccount(accountId)->second;
}

// Снимает деньги со счёта. Нельзя снять больше, чем есть на счете
// Нельзя снять отрицательное количество денег
// Снятые деньги переходят добавляются к массе наличных денег
// При невалидном номере счёта или отсутствии денег, выбрасывается исключение BankOperationError
// При отрицательном количестве денег выбрасывается std::out_of_range
void CBank::WithdrawMoney(AccountId account, Money amount)
{
	ValidateMoney(amount);
	auto it = GetAccount(account);

	if (it->second < amount)
	{
		throw BankOperationError("Not enough money in account " + std::to_string(account));
	}

	it->second -= amount;
	m_cash += amount;
}

// Попытаться снять деньги в размере amount со счёта account.
// Объем денег в наличном обороте увеличивается на величину amount
// При нехватке денег на счёте возвращается false, а количество наличных денег остаётся неизменным
// При невалидном номере аккаунта выбрасывается BankOperationError.
// При отрицательном количестве денег выбрасывается std::out_of_range
bool CBank::TryWithdrawMoney(AccountId account, Money amount)
{
	try
	{
		WithdrawMoney(account, amount);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		return false;
	}

	return true;
}

// Поместить наличные деньги на счёт. Количество денег в наличном обороте
// уменьшается на величину amount.
// Нельзя поместить больше, чем имеется денег в наличном обороте
// Нельзя поместить на счёт отрицательное количество денег
// Нельзя поместить деньги на отсутствующий счёт
// При невалидном номере аккаунта или нехватке наличных денег в обороте выбрасывается BankOperationError.
// При отрицательном количестве денег выбрасывается std::out_of_range
void CBank::DepositMoney(AccountId account, Money amount)
{
	ValidateMoney(amount);
	auto it = GetAccount(account);

	if (m_cash < amount)
	{
		throw BankOperationError("Not enough money in the bank");
	}

	it->second += amount;
	m_cash -= amount;
}

// Открывает счёт в банке. После открытия счёта на нём нулевой баланс.
// Каждый открытый счёт имеет уникальный номер.
// Возвращает номер счёта
AccountId CBank::OpenAccount()
{
	AccountId newId = GetNewAccountId();
	m_clients.emplace(newId, 0);

	return newId;
}

// Закрывает указанный счёт.
// Возвращает количество денег, которые были на счёте в момент закрытия
// Эти деньги переходят в наличный оборот
Money CBank::CloseAccount(AccountId accountId)
{
	auto it = GetAccount(accountId);
	Money remainder = it->second;
	m_clients.erase(it);
	m_cash += remainder;

	return remainder;
}

void CBank::ValidateMoney(Money money)
{
	if (money < 0)
	{
		throw std::out_of_range("Money must be not negative");
	}
}

std::unordered_map<AccountId, Money>::iterator CBank::GetAccount(AccountId accountId)
{
	auto it = m_clients.find(accountId);
	if (it == m_clients.end())
	{
		throw BankOperationError("Can`t find account with id " + std::to_string(accountId));
	}

	return it;
}

std::unordered_map<AccountId, Money>::const_iterator CBank::GetAccount(AccountId accountId) const
{
	auto it = m_clients.find(accountId);
	if (it == m_clients.end())
	{
		throw BankOperationError("Can`t find account with id " + std::to_string(accountId));
	}

	return it;
}

AccountId CBank::GetNewAccountId() noexcept
{
	return ++m_nextСlientId;
}
