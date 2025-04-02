#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <CBank.h>
#include "CActor.h"
#include "Actors.h"
#include <memory>

namespace
{
	constexpr Money bankInitialCash = 45000;
	constexpr Money homerInitialCash = 8000;
	constexpr Money margeInitialCash = 2000;
	constexpr Money bartInitialCash = 250;
	constexpr Money lisaInitialCash = 250;
	constexpr Money mrBurnsInitialCash = 20000;
	constexpr Money apuInitialCash = 5000;
	constexpr Money nelsonInitialCash = 250;
	constexpr Money snakeInitialCash = 250;
	constexpr Money smithersInitialCash = 9000;
}

struct ActorsTestMiddleware
{
	std::unique_ptr<CBank> bank;
	std::unique_ptr<Homer> homer;
	std::unique_ptr<Marge> marge;
	std::unique_ptr<Bart> bart;
	std::unique_ptr<Lisa> lisa;
	std::unique_ptr<Apu> apu;
	std::unique_ptr<MrBurns> mrBurns;
	std::unique_ptr<Nelson> nelson;
	std::unique_ptr<Snake> snake;
	std::unique_ptr<Smithers> smithers;

	Actors actors;

	ActorsTestMiddleware()
		: bank(std::make_unique<CBank>(bankInitialCash))
	{
		homer = std::make_unique<Homer>(homerInitialCash, *bank);
		marge = std::make_unique<Marge>(margeInitialCash, *bank);
		bart = std::make_unique<Bart>(bartInitialCash);
		lisa = std::make_unique<Lisa>(lisaInitialCash);
		apu = std::make_unique<Apu>(apuInitialCash, *bank);
		mrBurns = std::make_unique<MrBurns>(mrBurnsInitialCash, *bank);
		nelson = std::make_unique<Nelson>(nelsonInitialCash);
		snake = std::make_unique<Snake>(snakeInitialCash, *bank);
		smithers = std::make_unique<Smithers>(smithersInitialCash, *bank);

		actors.homer = homer.get();
		actors.marge = marge.get();
		actors.bart = bart.get();
		actors.lisa = lisa.get();
		actors.apu = apu.get();
		actors.mrBurns = mrBurns.get();
		actors.nelson = nelson.get();
		actors.snake = snake.get();
		actors.smithers = smithers.get();
	}
};

const AccountId invalidId = -1;

TEST_CASE("Bank constructor tests")
{
	CHECK_THROWS_AS(CBank(-100), BankOperationError);

	CBank bank(100);
	CHECK(bank.GetCash() == 100);
}

TEST_CASE("Bank account open/close tests")
{
	CBank bank(100);
	AccountId firstClient = bank.OpenAccount();
	AccountId secondClient = bank.OpenAccount();
	REQUIRE(firstClient != secondClient);

	CHECK(bank.GetAccountBalance(firstClient) == 0);
	CHECK(bank.GetAccountBalance(secondClient) == 0);

	CHECK_THROWS_AS(bank.GetAccountBalance(invalidId), BankOperationError);
	CHECK_THROWS_AS(bank.CloseAccount(invalidId), BankOperationError);
	
	Money firstClientMoney = bank.CloseAccount(firstClient);
	CHECK(firstClientMoney == 0);
	CHECK_THROWS_AS(bank.GetAccountBalance(firstClient), BankOperationError);
}

TEST_CASE("Bank money transfer tests")
{
	CBank bank(100);
	AccountId firstClient = bank.OpenAccount();
	AccountId secondClient = bank.OpenAccount();

	CHECK_THROWS_AS(bank.DepositMoney(firstClient, 1000), BankOperationError);
	CHECK_THROWS_AS(bank.DepositMoney(firstClient, -1), std::out_of_range);

	// Депозит
	bank.DepositMoney(firstClient, 25);
	CHECK(bank.GetAccountBalance(firstClient) == 25);
	CHECK(bank.GetCash() == 75);

	// Транзакция
	CHECK_THROWS_AS(bank.SendMoney(firstClient, invalidId, 25), BankOperationError);
	CHECK_THROWS_AS(bank.SendMoney(invalidId, firstClient, 25), BankOperationError);

	CHECK_THROWS_AS(bank.SendMoney(firstClient, secondClient, 50), BankOperationError);
	CHECK_THROWS_AS(bank.SendMoney(firstClient, secondClient, -25), std::out_of_range);

	bank.SendMoney(firstClient, secondClient, 15);
	CHECK(bank.GetAccountBalance(firstClient) == 10);
	CHECK(bank.GetAccountBalance(secondClient) == 15);

	// Снятие
	CHECK_THROWS_AS(bank.WithdrawMoney(secondClient, -10), std::out_of_range);
	CHECK_THROWS_AS(bank.WithdrawMoney(invalidId, 10), BankOperationError);
	CHECK_THROWS_AS(bank.WithdrawMoney(secondClient, 50), BankOperationError);

	bank.WithdrawMoney(secondClient, 10);
	CHECK(bank.GetCash() == 85);
	CHECK(bank.GetAccountBalance(secondClient) == 5);
}

TEST_CASE("Test Homer act")
{
	ActorsTestMiddleware testMiddleware;

	testMiddleware.homer->DepositMoney(4000);
	testMiddleware.homer->Act(testMiddleware.actors);

	// 100 Marge, 250 mrBurns, 50 kids
	CHECK(testMiddleware.homer->GetAccountBalance() == 4000 - 100 - 250 - 50);
	// 8k cash => 4k to bank
	CHECK(testMiddleware.homer->GetCash() == 4000);

	// evrebody got their money
	CHECK(testMiddleware.marge->GetAccountBalance() == 100);
	CHECK(testMiddleware.mrBurns->GetAccountBalance() == 250);
	CHECK(testMiddleware.bart->GetCash() == bartInitialCash + 25);
	CHECK(testMiddleware.lisa->GetCash() == lisaInitialCash + 25);
}

TEST_CASE("Test Marge act")
{
	ActorsTestMiddleware testMiddleware;

	testMiddleware.marge->DepositMoney(200);
	CHECK(testMiddleware.marge->GetCash() == margeInitialCash - 200);
	CHECK(testMiddleware.marge->GetAccountBalance() == 200);

	testMiddleware.marge->Act(testMiddleware.actors);
	CHECK(testMiddleware.apu->GetAccountBalance() == 100);
	CHECK(testMiddleware.marge->GetAccountBalance() == 100);
}

TEST_CASE("Test Bart & Lisa act")
{
	ActorsTestMiddleware testMiddleware;
	testMiddleware.bart->Act(testMiddleware.actors);
	testMiddleware.lisa->Act(testMiddleware.actors);

	CHECK(testMiddleware.bart->GetCash() == bartInitialCash - 17);
	CHECK(testMiddleware.lisa->GetCash() == lisaInitialCash - 9);
	CHECK(testMiddleware.apu->GetCash() == apuInitialCash + 26);
}

TEST_CASE("Test Apu act")
{
	ActorsTestMiddleware testMiddleware;
	testMiddleware.apu->Act(testMiddleware.actors);
	CHECK(testMiddleware.apu->GetCash() == 0);
	CHECK(testMiddleware.apu->GetAccountBalance() == apuInitialCash - 250);
}

TEST_CASE("Test mr.Burns act")
{
	ActorsTestMiddleware testMiddleware;
	testMiddleware.mrBurns->DepositMoney(5000);

	testMiddleware.mrBurns->Act(testMiddleware.actors);
	CHECK(testMiddleware.mrBurns->GetAccountBalance() == 5000 - 500 - 350);
	CHECK(testMiddleware.homer->GetAccountBalance() == 500);
	CHECK(testMiddleware.smithers->GetAccountBalance() == 350);
}

TEST_CASE("Test Nelson act")
{
	ActorsTestMiddleware testMiddleware;
	testMiddleware.nelson->Act(testMiddleware.actors);

	CHECK(testMiddleware.bart->GetCash() < bartInitialCash);
	CHECK(testMiddleware.apu->GetCash() == apuInitialCash + 15);

	Money stolenFromBart = bartInitialCash - testMiddleware.bart->GetCash();
	CHECK(testMiddleware.nelson->GetCash() == nelsonInitialCash + stolenFromBart - 15);
}

TEST_CASE("Test Snake act")
{
	ActorsTestMiddleware testMiddleware;
	testMiddleware.homer->DepositMoney(500);
	testMiddleware.snake->Act(testMiddleware.actors);
	CHECK(testMiddleware.snake->GetAccountBalance() == 69);
	CHECK(testMiddleware.homer->GetAccountBalance() == 500 - 69);
}

TEST_CASE("Test Smithers act")
{
	ActorsTestMiddleware testMiddleware;
	const AccountId initialAccountId =  testMiddleware.smithers->GetAccountId();

	Money expectedMoney = 2000;
	testMiddleware.smithers->DepositMoney(expectedMoney);
	
	for (int i = 0; i < 2; i++)
	{
		CHECK(testMiddleware.smithers->GetAccountBalance() == expectedMoney);
		testMiddleware.smithers->Act(testMiddleware.actors);
		CHECK(testMiddleware.smithers->GetAccountId() == initialAccountId);
		expectedMoney -= 250;
	}

	testMiddleware.smithers->Act(testMiddleware.actors);
	CHECK(testMiddleware.smithers->GetAccountId() != initialAccountId);
	CHECK(testMiddleware.apu->GetAccountBalance() == 250 * 3);
}