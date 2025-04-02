#include "CSimulation.h"

CSimulation::CSimulation()
{
	m_bank = std::make_unique<CBank>(m_initialCash);

	m_homer = std::make_unique<Homer>(2500, *m_bank);
	m_marge = std::make_unique<Marge>(1000, *m_bank);
	m_bart = std::make_unique<Bart>(50);
	m_lisa = std::make_unique<Lisa>(50);
	m_apu = std::make_unique<Apu>(5000, *m_bank);
	m_mrBurns = std::make_unique<MrBurns>(50000, *m_bank);
	m_nelson = std::make_unique<Nelson>(100);
	m_snake = std::make_unique<Snake>(250, *m_bank);
	m_smithers = std::make_unique<Smithers>(9000, *m_bank);

	m_actors.homer = m_homer.get();
	m_actors.marge = m_marge.get();
	m_actors.bart = m_bart.get();
	m_actors.lisa = m_lisa.get();
	m_actors.apu = m_apu.get();
	m_actors.mrBurns = m_mrBurns.get();
	m_actors.nelson = m_nelson.get();
	m_actors.snake = m_snake.get();
	m_actors.smithers = m_smithers.get();
}

void CSimulation::RunSimulation(int iterations)
{
	for (int i = 0; i < iterations; ++i)
	{
		m_homer->Act(m_actors);
		m_marge->Act(m_actors);
		m_bart->Act(m_actors);
		m_lisa->Act(m_actors);
		m_apu->Act(m_actors);
		m_mrBurns->Act(m_actors);
		m_nelson->Act(m_actors);
		m_snake->Act(m_actors);
		m_smithers->Act(m_actors);

		std::cout << "\n";
	}

	if (IsAgreedState())
	{
		std::cout << "Simulation is in agreed state\n";
	}
	else
	{
		std::cout << "Simulation is NOT in agreed state\n";
	}
}

bool CSimulation::IsAgreedState() const
{
	const Money bankBalance = m_bank->GetCash();

	const Money totalCharacterCash = 
		m_homer->GetCash() + 
		m_marge->GetCash() +
		m_bart->GetCash() +
		m_lisa->GetCash() +
		m_apu->GetCash() +
		m_mrBurns->GetCash() +
		m_nelson->GetCash() +
		m_snake->GetCash() +
		m_smithers->GetCash();


	const Money totalCharacterBalance = 
		m_homer->GetAccountBalance() +
		m_marge->GetAccountBalance() +
		m_apu->GetAccountBalance() +
		m_mrBurns->GetAccountBalance() +
		m_snake->GetAccountBalance() +
		m_smithers->GetAccountBalance();

	const Money totalMoney = totalCharacterBalance + totalCharacterCash;

	std::cout << "\nStats: \n"
		<< "Bank Balance = " << bankBalance << "\n"
		<< "Character cash = " << totalCharacterCash << "\n"
		<< "Character Balance = " << totalCharacterBalance << "\n"
		<< "Total Money = " << totalMoney << "\n"
		<< "Initital = " << m_initialCash << "\n";

	return totalMoney == m_initialCash;
}
