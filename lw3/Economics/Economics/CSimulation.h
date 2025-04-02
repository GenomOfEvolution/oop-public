#pragma once
#include "Actors.h"
#include <memory>

class CSimulation
{
public:
	CSimulation();
	
	void RunSimulation(int iterations);

private:
	[[nodiscard]] bool IsAgreedState() const;

	std::unique_ptr<CBank> m_bank;

	std::unique_ptr<Homer> m_homer;
	std::unique_ptr<Marge> m_marge;
	std::unique_ptr<Bart> m_bart;
	std::unique_ptr<Lisa> m_lisa;
	std::unique_ptr<Apu> m_apu;
	std::unique_ptr<MrBurns> m_mrBurns;
	std::unique_ptr<Nelson> m_nelson;
	std::unique_ptr<Snake> m_snake;
	std::unique_ptr<Smithers> m_smithers;

	Actors m_actors;

	Money m_initialCash = 67950;
};
