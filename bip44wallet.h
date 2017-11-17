#pragma once
#include "coin_type.h"

using namespace bc;


class bip44wallet
{
public:
	
	Prefixes BTC =  {0x80000000, 0x0488ADE4, 0x0488B21E, 0x00, 0x05};
	Prefixes tBTC = {0x80000001, 0x04358394, 0x043587CF, 0x6f, 0xC4};
	Prefixes LTC =  {0x80000002, 0x0488ADE4, 0x0488B21E, 0x30, 0x32};
	Prefixes tLTC = {0x80000001, 0x04358394, 0x04358394, 0x6f, 0xC0};
	Prefixes POT =  {0x80000081, 0x0488ADE4, 0x0488B21E, 55, 0x05};
	Prefixes ETC =  {0x8000003d, 0x0488ADE4, 0x0488B21E, 55, 0x05};
	Prefixes ETH =  {0x8000003c, 0x0488ADE4, 0x0488B21E, 55, 0x05};
	//constructor
	bip44wallet();
	bip44wallet(Prefixes coin_code);

	bip44wallet(const data_chunk userSeed);
	bip44wallet(const data_chunk userSeed, Prefixes coin_code);

	bip44wallet(const std::string mnemonicSeed);
	bip44wallet(const std::string mnemonicSeed, Prefixes coin_code);
	void setCoin(int bip44coin_code);
	void setCoinPrefixes(Prefixes coin_code);
	void set_account(int account_num);
	//display output
	void dumpKeys();
	void displayMasterKey();

	void displayMnemonic();

	void displayChildSecretKey(int index);
	// void displayChildWif(int index)
	// {
	// 	std:cout <<"\n WIF: " << childWif(index).encoded() << std::endl;
	// }

	void displayChildPublicKey(int index);

	void displayChildAddress(int index);
	std::string getChildKeyPath();
	void addressRange(int start, int end);

	//accesor
	wallet::hd_private getMasterKey();
	
	ec_secret childSecretKey(int index);
	// wallet::hd_private childWif(int index)
	// {
	// 	return account.derive_private(0).derive_private(index);
	// }

	wallet::ec_public childPublicKey(int index);

	wallet::payment_address childAddress(int index);
	Prefixes getCoinPrefixes();
	int getCurrentAccount();
private:
	//members
	//data_chunk entropy;
	data_chunk seed;
	Prefixes coin_type;
	int currentAccount;
	wallet::word_list mnemonic;
	wallet::hd_private purpose44Key;
	wallet::hd_private coin;
	wallet::hd_private account;
};