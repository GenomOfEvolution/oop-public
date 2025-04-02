#pragma once

#include <stdexcept>
#include <string>
#include <unordered_map>

using AccountId = unsigned long long;
using Money = long long;

class BankOperationError : public std::runtime_error
{
public:
	using std::runtime_error::runtime_error;
};

// Контролирует все деньги в обороте (как наличные, так и безналичные)
class CBank
{
public:
	explicit CBank(Money cash);

	CBank(const CBank&) = delete;
	CBank& operator=(const CBank&) = delete;

	void SendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
	[[nodiscard]] bool TrySendMoney(AccountId srcAccountId, AccountId dstAccountId, Money amount);
	[[nodiscard]] Money GetCash() const noexcept;
	Money GetAccountBalance(AccountId accountId) const;
	void WithdrawMoney(AccountId account, Money amount);
	[[nodiscard]] bool TryWithdrawMoney(AccountId account, Money amount);
	void DepositMoney(AccountId account, Money amount);
	[[nodiscard]] AccountId OpenAccount();
	[[nodiscard]] Money CloseAccount(AccountId accountId);

private:
	Money m_cash;
	std::unordered_map<AccountId, Money> m_clients;
	AccountId m_nextСlientId = 0;

	static void ValidateMoney(Money money);

	[[nodiscard]] std::unordered_map<AccountId, Money>::iterator GetAccount(AccountId accountId);
	[[nodiscard]] std::unordered_map<AccountId, Money>::const_iterator GetAccount(AccountId accountId) const;
	[[nodiscard]] AccountId GetNewAccountId() noexcept;
};