#include "Actors.h"
#include <stdlib.h>

void Homer::Act(Actors& actors)
{
	// Marge на карту для продуктов
	if (SendMoney(actors.marge->GetAccountId(), 100))
	{
		std::cout << "Homer sent  to Marge`s card\n";
	}

	// MrBurns`у за электричество
	if (SendMoney(actors.mrBurns->GetAccountId(), 250))
	{
		std::cout << "Homer paid  for electricity\n";
	}

	// Детям наличкой поровну
	if (WithdrawMoney(50))
	{
		if (SendCash(*actors.lisa, 25))
		{
			std::cout << "Homer gave cash to Lisa\n";
		}

		if (SendCash(*actors.bart, 25))
		{
			std::cout << "Homer gave cash to Bart\n";
		}
	}
}

void Marge::Act(Actors& actors)
{
	// Покупает продукты у Апу переводом
	if (SendMoney(actors.apu->GetAccountId(), 100))
	{
		std::cout << "Marge bought products from Apu\n";
	}
}

void Apu::Act(Actors& actors)
{
	// Если есть наличка, переводит ее на счет
	if (GetCash() > 0)
	{
		if (DepositMoney(GetCash()))
		{
			std::cout << "Apu deposited cash to his bank account\n";
		}
	}

	// Платит за электричество
	if (SendMoney(actors.mrBurns->GetAccountId(), 250))
	{
		std::cout << "Apu paid for electricity\n";
	}
}

void MrBurns::Act(Actors& actors)
{
	// Платит ЗП работникам
	if (SendMoney(actors.homer->GetAccountId(), 500))
	{
		std::cout << "Mr. Burns paid Homer for his work\n";
	}

	if (SendMoney(actors.smithers->GetAccountId(), 350))
	{
		std::cout << "Mr. Burns paid Smithers for his work\n";
	}
}

void Snake::Act(Actors& actors)
{
	// Крадет деньги со счета Гомера
	if (StealMoney(actors.homer->GetAccountId(), 69))
	{
		std::cout << "Snake stole money from Homer's bank account\n";
	}
}

void Smithers::Act(Actors& actors)
{
	// Покупает продукты у Апу
	if (SendMoney(actors.apu->GetAccountId(), 250))
	{
		std::cout << "Smithers paid for Apu's products\n";
	}

	m_paranoia++;
	if (m_paranoia >= m_paranoia_border)
	{
		m_paranoia = 0;
		Money cash = CloseAccount();
		std::cout << "Smithers closed his bank account\n";

		OpenAccount();
		if (DepositMoney(cash))
		{
			std::cout << "Smithers opened new bank account and put cash\n";
		}
	}
}

void Bart::Act(Actors& actors)
{
	if (SendCash(*actors.apu, 17))
	{
		std::cout << "Bart spend some cash in Apu`s shop\n";
	}
}

void Lisa::Act(Actors& actors)
{
	if (SendCash(*actors.apu, 9))
	{
		std::cout << "Lisa spend some cash in Apu`s shop\n";
	}
}

void Nelson::Act(Actors& actors)
{
	int cashToSteal = 1 + (std::rand() % 20);
	if (StealCash(*actors.bart, cashToSteal))
	{
		std::cout << "Nelson stole cash from Bart\n";
	}

	if (SendCash(*actors.apu, 15))
	{
		std::cout << "Nelson bought cigaretes from Apu\n";
	}
}
