
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/client.hpp>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
// #include "coin_type.h"
#include "bip44wallet.h"
#include "interface.h"
// #include <stdlib.h>
// #include <stdio.h>

using namespace bc;
voidstar walletInitFromMnemonic(const char* mnemonic)
{
	bip44wallet * ret = new bip44wallet(std::string(mnemonic));
  	return (voidstar)ret;
}
voidstar walletInit()
{
	bip44wallet * ret = new bip44wallet();
  	return (voidstar)ret;
}

voidstar walletInitFromCointype(Prefixes coin_code)
{
	bip44wallet * ret = new bip44wallet(coin_code);
  	return (voidstar)ret;
}
voidstar walletInitFromCointypeAndMnemonic(const char* mnemonicSeed, Prefixes coin_code)
{
	bip44wallet * ret = new bip44wallet(mnemonicSeed,coin_code);
  	return (voidstar)ret;
}













void walletFree(voidstar f)
{
	bip44wallet * foo = (bip44wallet*)f;
    delete foo;
}
char* getMnemonic(voidstar f)
{
	bip44wallet * foo = (bip44wallet*)f;
  	std::string ret=foo->getMnemonic();
	char *buf = (char *)malloc(ret.length());
	sprintf(buf, "%s", ret.c_str());
	return buf;
}
char* getMasterKey(voidstar f)
{
	bip44wallet * foo = (bip44wallet*)f;
  	std::string ret=foo->getMasterKey();
	char *buf = (char *)malloc(ret.length());
	sprintf(buf, "%s", ret.c_str());
	return buf;
}
char* getChildKeyPath(voidstar f)
{
	bip44wallet * foo = (bip44wallet*)f;
  	std::string ret=foo->getChildKeyPath();
	char *buf = (char *)malloc(ret.length());
	sprintf(buf, "%s", ret.c_str());
	return buf;
}
char* getChildSecretKey(voidstar f,int index)
{
	bip44wallet * foo = (bip44wallet*)f;
  	std::string ret=foo->getChildSecretKey(index);
	char *buf = (char *)malloc(ret.length());
	sprintf(buf, "%s", ret.c_str());
	return buf;
}
char* getChildPublicKey(voidstar f,int index)
{
	bip44wallet * foo = (bip44wallet*)f;
  	std::string ret=foo->getChildPublicKey(index);
	char *buf = (char *)malloc(ret.length());
	sprintf(buf, "%s", ret.c_str());
	return buf;
}
char* getChildAddress(voidstar f,int index)
{
	bip44wallet * foo = (bip44wallet*)f;
  	std::string ret=foo->getChildAddress(index);
	char *buf = (char *)malloc(ret.length());
	sprintf(buf, "%s", ret.c_str());
	return buf;
}
void set_account(voidstar f,int account_num)
{
	bip44wallet * foo = (bip44wallet*)f;
  	foo->set_account(account_num);
}
int getCurrentAccount(voidstar f)
{
	bip44wallet * foo = (bip44wallet*)f;
  	return foo->getCurrentAccount();
}
// void set_account(voidstar f,int account_num);
// int getCurrentAccount(voidstar f);

char* FromMnemonicToMasterKey(const char* mnemonic)
{	
	//"label stick flat innocent brother frost rebel aim creek six baby copper need side cannon student announce alpha"
	wallet::hd_private master(to_chunk(wallet::decode_mnemonic(split(std::string(mnemonic)))));
	char *buf = (char *)malloc(300);
	sprintf(buf, "%s", master.encoded().c_str());
	return buf;
	// return master.encoded().c_str();
}

// char* createrawtransaction(voidstar f,const char* reqjson)
// {
// 	//UniValue createrawtransaction(const JSONRPCRequest& request)
// 	// JSONRPCRequest request;
//  //    request.strMethod = "createrawtransaction";
//  //    request.params = RPCConvertValues(strMethod, vArgs);
//  //    request.fHelp = false;
// 	// std::string req="createrawtransaction "+std::string(reqjson);
// 	//\"[{\"txid\":\"6c3f611cbd624e8a094f08b10f849b765d3548c13ace1704de050a44f504caff\",\"vout\":0}]\" \"{\"mxu9tvJsuZq1rxiaevcUJkuu6mv2LFhpSr\":0.1}\"";
// 	bip44wallet * foo = (bip44wallet*)f;
//   	std::string ret=foo->Callcreaterawtransaction(reqjson);
// 	char *buf = (char *)malloc(ret.length());
// 	sprintf(buf, "%s", ret.c_str());
// 	return buf;
// 	// UniValue raw=Callcreaterawtransaction(req);
// 	// char *buf = (char *)malloc(raw.get_str().length());
// 	// sprintf(buf, "%s", raw.get_str().c_str());
// 	// return buf;

// 	// return raw.get_str().c_str();
// }
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