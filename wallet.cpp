#include <bitcoin/bitcoin.hpp>
#include <string.h>
#include <iostream>
#include "bip44wallet.h"
#include <sstream>

using namespace bc;
void genericConstructor()
{
	bip44wallet wallet = bip44wallet();
	wallet.setCoinPrefixes(wallet.BTC);
	wallet.dumpKeys();
}
void testMnemonic_MasterKey()
{	
	wallet::hd_private master(to_chunk(wallet::decode_mnemonic(split("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha"))));
	bip44wallet wallet("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha");
	if(master == wallet.getMasterKey()){
		std::cout << "testMnemonic_MasterKey: Success!" << std::endl;
		std::cout << master.encoded() << std::endl;
		wallet.displayMasterKey();
	}
}
void testCoin_address(Prefixes coin)
{
	uint32_t coinCode = coin.bip44_code;
	uint8_t addyPrefix = coin.P2KH; 
	bip44wallet wallet("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha", coin);
	wallet::payment_address address(wallet::hd_private(to_chunk(wallet::decode_mnemonic(split("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha")))).derive_private(44).derive_private(coinCode).derive_private(0).derive_public(0).derive_public(0).point(), addyPrefix);
	if(address == wallet.childAddress(0))
	{
		std::cout << "testCoin_address: Success! \n" << std::endl;
	}
	wallet.displayChildAddress(0);
	std::cout << address.encoded() << std::endl;

}
void testCoinConstructor_childKeyDisplay()
{
	int BTC = bip44wallet().BTC.bip44_code;
	bip44wallet wallet1("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha", bip44wallet().BTC);
	wallet::ec_public publicPoint = wallet::hd_private(to_chunk(wallet::decode_mnemonic(split("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha")))).derive_private(44).derive_private(BTC).derive_private(0).derive_public(0).derive_public(0).point();
	ec_secret secretKey = wallet::hd_private(to_chunk(wallet::decode_mnemonic(split("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha")))).derive_private(44).derive_private(BTC).derive_private(0).derive_private(0).derive_private(0).secret();
	if(publicPoint.point() == wallet1.childPublicKey(0).point())
	{
		std::cout << "testCoinConstructor_childKeyDisplay: Success! \n" << std::endl;
	}
	wallet1.displayChildPublicKey(0);
	std::cout << publicPoint.encoded() << std::endl;
	if (secretKey == wallet1.childSecretKey(0))
	{
		std::cout << "testCoinConstructor_childKeyDisplay: Success! \n" << std::endl;
	}
	wallet1.displayChildSecretKey(0);
	std::cout << encode_base16(secretKey) << std::endl;

}
void testCustomCoinPath(int coinPath)
{
	bip44wallet wallet1("label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha", bip44wallet().tBTC);
	int customCoinPath = coinPath;
	wallet1.setCoin(coinPath);
	if(coinPath == wallet1.getCoinPrefixes().bip44_code)
	{
		std::cout << "Success: " << std::endl;
	}
	std::cout << "Key Path: M / 44 / " << wallet1.getCoinPrefixes().bip44_code << " / 0 / 0 / 0" << std::endl;


}
Prefixes matchPrefixTicker(std::string coin)
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
void basetest()
{
	bip44wallet wallet = bip44wallet();
	wallet.setCoinPrefixes(matchPrefixTicker("BTC"));
	wallet.dumpKeys();
	
	wallet.displayMasterKey();

	wallet.displayChildSecretKey(index);

	wallet.displayChildAddress(index);

	std::cout << "Master Key / Purpose Code / Coin Code / Account / Change(T/F) / Child Index" << std::endl;
	std::cout << "Master / 44 / " << wallet.getCoinPrefixes().bip44_code << " / " << wallet.getCurrentAccount() << " / 0 / Child Index" << std::endl;
}
int main(int argc, char *argv[])
{
	
	basetest();
	return 0;
}