
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/client.hpp>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "coin_type.h"
#include "bip44wallet.h"
using namespace bc;
Prefixes matchPrefixTicker2(std::string coin)
{

	if(coin == "BTC")
	{
		return bip44wallet().BTC;
	} else if(coin == "tBTC"){

		return bip44wallet().tBTC;
	}else if(coin == "LTC"){

		return bip44wallet().LTC;

	} else if(coin == "tLTC"){

		return bip44wallet().tLTC;
	} else if(coin=="POT"){
		return bip44wallet().POT;
	}
	else {
		
		return bip44wallet().BTC;

	}
}
bip44wallet::bip44wallet()
{
	data_chunk entropy = data_chunk(16);
	pseudo_random_fill(entropy);
	mnemonic = wallet::create_mnemonic(entropy);
	seed = to_chunk(wallet::decode_mnemonic(mnemonic));
	purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
	// std::cout<<"seed:"<<displayData_chunk(seed)<<std::endl;
	// std::cout<<"entropy:"<<displayData_chunk(entropy)<<std::endl;
}
bip44wallet::bip44wallet(Prefixes coin_code)
{
	data_chunk entropy = data_chunk(16);
	pseudo_random_fill(entropy);
	mnemonic = wallet::create_mnemonic(entropy);
	seed = to_chunk(wallet::decode_mnemonic(mnemonic));
	purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
	setCoinPrefixes(coin_code);

}

bip44wallet::bip44wallet(const data_chunk userSeed)
{
	//defaults to BTC
	seed = userSeed;
	//mnemonic = wallet::create_mnemonic(entropy);
	//seed = entropy; //to_chunk(wallet::decode_mnemonic(mnemonic));
	purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
	setCoinPrefixes(BTC);
}

bip44wallet::bip44wallet(const data_chunk userSeed, Prefixes coin_code)
{
	seed = userSeed;
	//mnemonic = wallet::create_mnemonic(entropy);
	//seed = entropy; //to_chunk(wallet::decode_mnemonic(mnemonic));
	purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
	setCoinPrefixes(coin_code);
}

bip44wallet::bip44wallet(const std::string mnemonicSeed)
{
	//defaults to BTC
	mnemonic = split(mnemonicSeed);
	seed = to_chunk(wallet::decode_mnemonic(mnemonic));
	//seed = to_chunk(hashSeed);
	purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
	setCoinPrefixes(BTC);
}
bip44wallet::bip44wallet(const std::string mnemonicSeed, Prefixes coin_code)
{
	mnemonic = split(mnemonicSeed);
	seed = to_chunk(wallet::decode_mnemonic(mnemonic));
	//seed = to_chunk(hashSeed);
	purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
	setCoinPrefixes(coin_code);
}
void bip44wallet::setCoin(int bip44coin_code)
{
	coin_type.bip44_code = bip44coin_code;
	coin = purpose44Key.derive_private(bip44coin_code);
}
void bip44wallet::setCoinPrefixes(Prefixes coin_code)
{
	coin_type = coin_code;
	coin = purpose44Key.derive_private(coin_type.bip44_code);
	//to-do scan accounts
	set_account(0x80000000);

}
void bip44wallet::set_account(int account_num)
{
	currentAccount = account_num;
	account = coin.derive_private(account_num);
}
//display output
void bip44wallet::dumpKeys()
{
	displayMnemonic();
	displayMasterKey();
	displayChildSecretKey(0);
	displayChildAddress(0);

}
void bip44wallet::displayMasterKey()
{
	std::cout << "\nMaster Private Key: " << wallet::hd_private(seed).encoded() << std::endl;
}

void bip44wallet::displayMnemonic()
{
	if(wallet::validate_mnemonic(mnemonic))
	{
		std::cout << "\n" << join(mnemonic) << std::endl;

	}else{
		std::cout << "\n" << "Mnemonic Invalid! " << std::endl;
	}
}

void bip44wallet::displayChildSecretKey(int index)
{
	std::cout << "\nSecret Key: " << encode_base16(childSecretKey(index)) << std::endl;
}
// void displayChildWif(int index)
// {
// 	std:cout <<"\n WIF: " << childWif(index).encoded() << std::endl;
// }

void bip44wallet::displayChildPublicKey(int index)
{
	std::cout << "\nPublic Key: " << childPublicKey(index).encoded() << std::endl;
}

void bip44wallet::displayChildAddress(int index)
{
	std::cout << "\nAddress: " << childAddress(index).encoded() << std::endl;
}
void bip44wallet::displayData_chunk(const data_chunk& data)
{
	std::cout << "\ndata_chunk: ";
	for(const auto& d:data)
	{
		std::cout<<std::to_string(d);
	}
	std::cout<<std::endl;
}
std::string bip44wallet::getChildKeyPath()
{

	return "Master / 0x8000002C / " + std::to_string(getCoinPrefixes().bip44_code) + " / " + std::to_string(getCurrentAccount()) + " / 0 / Child Index";
}
void bip44wallet::addressRange(int start, int end)
{
	while(start != end)
	{
		displayChildAddress(start);
		start++;
	}
}

//accesor
wallet::hd_private bip44wallet::getMasterKey()
{
	return wallet::hd_private(seed);
}

ec_secret bip44wallet::childSecretKey(int index)
{
	return account.derive_private(0).derive_private(index);
}
// wallet::hd_private childWif(int index)
// {
// 	return account.derive_private(0).derive_private(index);
// }

wallet::ec_public bip44wallet::childPublicKey(int index)
{

	return account.derive_public(0).derive_public(index).point();
}

wallet::payment_address bip44wallet::childAddress(int index)
{
	return wallet::payment_address((childPublicKey(index).point()), coin_type.P2KH);
}

Prefixes bip44wallet::getCoinPrefixes(){
	return coin_type;
}

int bip44wallet::getCurrentAccount()
{
	return currentAccount;
}