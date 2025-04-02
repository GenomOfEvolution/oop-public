#pragma once
#include "CBank.h"
#include <memory>

struct Actors;

class CActor
{
public:
	explicit CActor(Money cash);

	[[nodiscard]] Money GetCash() const;
	[[nodiscard]] bool SendCash(CActor& recipient, Money amount);
	[[nodiscard]] bool StealCash(CActor& victim, Money amount);

	virtual void Act(Actors& actors) = 0;
	virtual ~CActor() = default;

protected:
	void AddCash(Money money);
	bool SpendCash(Money money);

private:
	Money m_cash;
};

class CActorCard : public CActor 
{
public:
    CActorCard(Money cash, CBank& bank) 
        : m_bank(bank)
        , CActor(cash)
    {
        m_accountId = m_bank.OpenAccount();
    }

    [[nodiscard]] Money GetAccountBalance() const;
    [[nodiscard]] AccountId GetAccountId() const;
    [[nodiscard]] bool SendMoney(AccountId dstAccountId, Money amount);
    [[nodiscard]] bool StealMoney(AccountId victimAccountId, Money amount);
    [[nodiscard]] bool WithdrawMoney(Money amount);
    bool DepositMoney(Money amount);
	
	[[nodiscard]] Money CloseAccount();
	void OpenAccount();

    virtual ~CActorCard() = default;

private:
    AccountId m_accountId;
    CBank& m_bank;
};

struct Actors
{
	CActorCard* homer;
	CActorCard* marge;
	CActor* bart;
	CActor* lisa;
	CActorCard* apu;
	CActorCard* mrBurns;
	CActor* nelson;
	CActorCard* snake;
	CActorCard* smithers;
};