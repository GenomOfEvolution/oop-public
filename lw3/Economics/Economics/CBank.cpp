#include "CBank.h"
#include <iostream>

// �������������� ���������� �������. cash � ���������� ����� � �������� �������
// ��� ������������� ���������� �����, ������������� BankOperationError
CBank::CBank(Money cash)
{
	if (cash < 0)
	{
		throw BankOperationError("Initial cash should be greater than 0");
	}
	m_cash = cash;
}

// ��������� ������ � ��������� ����� (srcAccountId) �� ������� (dstAccountId)
// ������ ��������� ������, ��� ���� �� �������� �����
// ������ ��������� ������������� ���������� �����
// ���������� BankOperationError �������������, ��� ���������� ������ ���
// ���������� ����� �� �������� �����
// ��� ������������� ���������� ����������� ����� ������������� std::out_of_range
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

// ���������� ���������� �������� ����� � �������
Money CBank::GetCash() const noexcept
{
	return m_cash;
}

// �������� � ���������� ����� �� ��������� �����
// ���� ��������� ���� �����������, ������������� ���������� BankOperationError
Money CBank::GetAccountBalance(AccountId accountId) const
{
	return GetAccount(accountId)->second;
}

// ������� ������ �� �����. ������ ����� ������, ��� ���� �� �����
// ������ ����� ������������� ���������� �����
// ������ ������ ��������� ����������� � ����� �������� �����
// ��� ���������� ������ ����� ��� ���������� �����, ������������� ���������� BankOperationError
// ��� ������������� ���������� ����� ������������� std::out_of_range
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

// ���������� ����� ������ � ������� amount �� ����� account.
// ����� ����� � �������� ������� ������������� �� �������� amount
// ��� �������� ����� �� ����� ������������ false, � ���������� �������� ����� ������� ����������
// ��� ���������� ������ �������� ������������� BankOperationError.
// ��� ������������� ���������� ����� ������������� std::out_of_range
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

// ��������� �������� ������ �� ����. ���������� ����� � �������� �������
// ����������� �� �������� amount.
// ������ ��������� ������, ��� ������� ����� � �������� �������
// ������ ��������� �� ���� ������������� ���������� �����
// ������ ��������� ������ �� ������������� ����
// ��� ���������� ������ �������� ��� �������� �������� ����� � ������� ������������� BankOperationError.
// ��� ������������� ���������� ����� ������������� std::out_of_range
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

// ��������� ���� � �����. ����� �������� ����� �� �� ������� ������.
// ������ �������� ���� ����� ���������� �����.
// ���������� ����� �����
AccountId CBank::OpenAccount()
{
	AccountId newId = GetNewAccountId();
	m_clients.emplace(newId, 0);

	return newId;
}

// ��������� ��������� ����.
// ���������� ���������� �����, ������� ���� �� ����� � ������ ��������
// ��� ������ ��������� � �������� ������
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
	return ++m_next�lientId;
}
