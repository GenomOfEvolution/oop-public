#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <CBank.h>

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