#pragma once
#ifdef __cplusplus
extern "C"{
#endif
#include <stdint.h>
// #include "coin_type.h"
struct Prefixes
{
	uint32_t bip44_code;
	uint32_t HDprivate;
	uint32_t HDpublic;
	uint32_t P2KH;
	uint32_t P2SH;

};

void test();
char* FromMnemonicToMasterKey(const char* mnemonic);
typedef void* voidstar;
voidstar walletInitFromMnemonic(const char* mnemonic);
voidstar walletInit();
voidstar walletInitFromCointype(struct Prefixes coin_code);
voidstar walletInitFromCointypeAndMnemonic(const char* mnemonicSeed, struct Prefixes coin_code);
// void setCoin(int bip44coin_code);
// void setCoinPrefixes(Prefixes coin_code);
// void set_account(int account_num);

char* getMasterKey(voidstar f);

// void getMnemonic();

char* getChildAddress(voidstar f,int index);

char* getChildPublicKey(voidstar f,int index);

// void getChildAddress(int index);
// void getData_chunk(const data_chunk& data);
char* getChildKeyPath(voidstar f);
// void addressRange(int start, int end);

// //accesor
// wallet::hd_private getMasterKey();

char* getChildSecretKey(voidstar f,int index);

// wallet::ec_public childPublicKey(int index);

// wallet::payment_address childAddress(int index);
// Prefixes getCoinPrefixes();
// int getCurrentAccount();

char* getMnemonic(voidstar f);
void walletFree(voidstar f);

#ifdef __cplusplus
}
#endif
