#include <iostream>
#include <random>

class Account
{
public:
	explicit Account(int accountNumber)
		: m_accountNumber(accountNumber)
	{
		std::cout << "Account " << m_accountNumber << ": Created\n";
	}

	int64_t balance() const
	{
		return m_balance;
	}

	int accountNumber() const
	{
		return m_accountNumber;
	}

	bool transaction(int64_t amount, const std::string& reason)
	{
		std::cout << "Account " << m_accountNumber << ": Transaction (Amount: " << amount
				  << " Reason: " << reason << ")\n";
		m_balance += amount;
		return true;
	}

private:
	int m_accountNumber;
	int64_t m_balance = 0;
};

int main()
{
	// TODO: Adjust this type to store all account types
	std::vector<Account> m_accounts;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::bernoulli_distribution youthAccountDistrib(0.25);
	std::uniform_int_distribution initDepositDistrib(0, 50);

	constexpr int accountCount = 20;
	for (int i = 0; i < accountCount; ++i)
	{
		m_accounts.push_back(Account(i)); // TODO: Remove this line and create specific account instead
		if (youthAccountDistrib(gen))
		{
			// Create YouthAccount
		}
		else
		{
			// Create SavingAccount
		}
		m_accounts.back().transaction(initDepositDistrib(gen), "Deposit");
	}

	std::uniform_int_distribution transactionDistrib(-100, 100);
	constexpr int simulationRuns = 5;
	for (int i = 0; i < simulationRuns; ++i)
	{
		for (auto& account : m_accounts)
		{
			account.transaction(transactionDistrib(gen), "Random transaction");
		}
	}

	return 0;
}
