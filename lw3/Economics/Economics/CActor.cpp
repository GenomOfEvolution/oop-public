#include "CActor.h"

CActor::CActor(Money cash)
{
	if (cash < 0)
	{
		throw std::out_of_range("Initial cash can`t be negative");
	}
	m_cash = cash;
}

Money CActor::GetCash() const
{
	return m_cash;
}

bool CActor::SendCash(CActor& recipient, Money amount)
{
	if (m_cash < amount)
	{
		return false;
	}

	m_cash -= amount;
	recipient.AddCash(amount);

	return true;
}

bool CActor::StealCash(CActor& victim, Money amount)
{
	return victim.SendCash(*this, amount);
}

void CActor::AddCash(Money money)
{
	m_cash += money;
}

bool CActor::SpendCash(Money money)
{
	if (m_cash < money)
	{
		return false;
	}

	m_cash -= money;
	return true;
}

Money CActorCard::GetAccountBalance() const
{
	return m_bank.GetAccountBalance(m_accountId);
}

AccountId CActorCard::GetAccountId() const
{
	return m_accountId;
}

bool CActorCard::SendMoney(AccountId dstAccountId, Money amount)
{
	return m_bank.TrySendMoney(m_accountId, dstAccountId, amount);
}

bool CActorCard::StealMoney(AccountId victimAccountId, Money amount)
{
	return m_bank.TrySendMoney(victimAccountId, m_accountId, amount);
}

bool CActorCard::WithdrawMoney(Money amount)
{
	if (!m_bank.TryWithdrawMoney(m_accountId, amount))
	{
		return false;
	}

	AddCash(amount);
	return true;
}

bool CActorCard::DepositMoney(Money amount)
{
	if (!SpendCash(amount))
	{
		return false;
	}

	m_bank.DepositMoney(m_accountId, amount);
	return true;
}

[[nodiscard]] Money CActorCard::CloseAccount()
{
	Money remainder = m_bank.CloseAccount(m_accountId);
	AddCash(remainder);
	return remainder;
}

void CActorCard::OpenAccount()
{
	m_accountId = m_bank.OpenAccount();
}
