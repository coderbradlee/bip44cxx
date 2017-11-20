
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/client.hpp>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
#include "coin_type.h"
#include "bip44wallet.h"
#include "interface.h"
using namespace bc;
std::string testMnemonic_MasterKey(std::string mnemonic)
{	
	//"label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha"
	wallet::hd_private master(to_chunk(wallet::decode_mnemonic(split(mnemonic))));
	return master.encoded();
}
void test()
{
	int index=0;
	bip44wallet wallet = bip44wallet();
	
	wallet.setCoinPrefixes(matchPrefixTicker2("BTC"));
	//wallet.dumpKeys();
	
	wallet.displayMasterKey();

	wallet.displayChildSecretKey(index);

	wallet.displayChildAddress(index);

	std::cout << "Master Key / Purpose Code / Coin Code / Account / Change(T/F) / Child Index" << std::endl;
	std::cout << "Master / 44 / " << wallet.getCoinPrefixes().bip44_code << " / " << wallet.getCurrentAccount() << " / 0 / Child Index" << std::endl;
}