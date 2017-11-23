#pragma once
// #ifdef __cplusplus
// extern "C"{
// #endif
#undef WORDS_BIGENDIAN 
#undef HAVE_BYTESWAP_H 
#undef HAVE_ENDIAN_H 
#undef BUILD_BITCOIN_INTERNAL
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/client.hpp>
#include <vector>
using namespace bc;
// #include "coin_type.h"
#include "interface.h"
#include "univalue.h"

template<class T>
std::string ToHex(const T &value)
{
  std::ostringstream oss;
  if(!(oss<<std::hex<<value))throw "Invalid argument";
  return oss.str();
}
Prefixes matchPrefixTicker2(std::string coin);
// std::string bitcoin_address(const bc::ec_secret& se);
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
	std::string getMasterKey();
	void displayMnemonic();
	std::string getMnemonic();
	void displayChildSecretKey(int index);
	// void displayChildWif(int index)
	// {
	// 	std:cout <<"\n WIF: " << childWif(index).encoded() << std::endl;
	// }

	void displayChildPublicKey(int index);

	void displayChildAddress(int index);
	void displayData_chunk(const data_chunk& data);
	std::string getChildKeyPath();
	void addressRange(int start, int end);

	//accesor
	// wallet::hd_private getMasterKey();
	
	ec_secret childSecretKey(int index);
	// wallet::hd_private childWif(int index)
	// {
	// 	return account.derive_private(0).derive_private(index);
	// }
	std::string getChildSecretKey(int index);
	std::string getChildPublicKey(int index);
	std::string getChildAddress(int index);
	wallet::ec_public childPublicKey(int index);

	wallet::payment_address childAddress(int index);
	Prefixes getCoinPrefixes();
	int getCurrentAccount();

	UniValue Callcreaterawtransaction(std::string args);
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
//sign
// static hash_digest generate_signature_hash(const transaction& tx,
//         uint32_t input_index, const script& script_code, uint8_t sighash_type);

// static bool check_signature(const ec_signature& signature,
//         uint8_t sighash_type, const data_chunk& public_key,
//         const script& script_code, const transaction& tx,
//         uint32_t input_index);
// #ifdef __cplusplus
// }
// #endif