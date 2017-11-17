
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/client.hpp>
#include <string.h>
#include <iostream>
#include <sstream>
#include <vector>
//       |  BIP 44    |      mainnet     |     mainnet     |     mainnet     |  EXT_SECRET_KEY   |
// Coin  | coin_type’ |    version_WIF   |  version_p2pkh  |  version_p2sh   | version_hd_secret | References
// ———————————————————————————————————————————————————————————————————————————————————————————————————————————————————
// BTC   |      0     |        128       |   0/('1')       |   5/('3')       | 76066276/('xprv') | https://github.com/bitcoin/bitcoin/blob/master/src/chainparams.cpp#L104
// TEST  |      1     |        239       | 111/('m' | 'n') | 196/('2')       | 70615956/('tprv') | https://github.com/bitcoin/bitcoin/blob/master/src/chainparams.cpp#L177
// LTC   |      2     |        176       |  48/('L')       |   5/('3')       | 76066276/('xprv') | https://github.com/litecoin-project/litecoin/blob/master-0.10/src/chainparams.cpp#L164
// DOGE  |      3     |        158       |  30/('D')       |  22/('9' | 'A') | 49988504/('dgpv') | https://github.com/dogecoin/dogecoin/blob/master/src/chainparams.cpp#L132
// RDD   |      4     | 189/'V'/c        |  61/('R')       |   5/('3')       | 76066276/('xprv') | https://github.com/reddcoin-project/reddcoin/blob/master/src/base58.h#L275 & https://github.com/reddcoin-project/rddnet/blob/master/params.go#L148
// DASH  |      5     |        204       |  76/('X')       |  16/('7')       | 50221772/('drkp') | https://github.com/dashpay/dash/blob/master/src/chainparams.cpp#L168
// PPC   |      6     |        183       |  55/('P')       | 117/('p')       |                   | https://github.com/belovachap/peercoin/blob/master/src/base58.h#L267 and https://github.com/super3/Peercoin.net -   see NBT base58.h
// NMC   |      7     |        180       |  52/('M' | 'N') |  13/('6')       | 76066276/('xprv') | https://github.com/domob1812/namecore/blob/master/src/chainparams.cpp#L133
// FTC   |      8     |        142       |  14/('6' | '7') |   5/('3')       |                   | https://github.com/FeatherCoin/Feathercoin/blob/master-0.8/src/base58.h#L275
// XCP   |      9     |     color_BTC    |   0/('1')       |       ?         |                   | Built on BTC, https://github.com/CounterpartyXCP/counterparty-lib  http://counterparty.io/docs/create_addresses/
// BLK   |     10     |        153       |  25/('B')       |  85/('b')       | 76066276/('xprv') | https://github.com/rat4/blackcoin/blob/master/src/chainparams.cpp#L91
// NSR   |     11     |     149/191 c/u  |  63/('S')       |  64/('S' | 'T') |                   | Built on PPC, https://nubits.com/nushares/introduction
// NBT   |     12     |     150/191 c/u  |  25/('B')       |  26/('B')       |                   | https://bitbucket.org/JordanLeePeershares/nubit/NuBit / src /base58.h
// MZC   |     13     |        224       |  50/('M')       |   9/('4' | '5') |      unknown      | https://github.com/MazaCoin/MazaCoin/blob/master/src/chainparams.cpp#L76
// VIA   |     14     |        199       |  71/('V')       |  33/('E')       | 76066276/('xprv') | https://github.com/viacoin/viacoin/blob/master/src/chainparams.cpp#L154
// XCH   |     15     |     color_VIA    |  71/('V')       |       ?         |                   | Built on VIA, https://github.com/ClearingHouse/clearinghoused/blob/master/lib/config.py#L55 
// RBY   |     16     |        189       |  61/('R')       |  85/('b')       |                   | https://github.com/rubycoinorg/rubycoin/blob/master/src/base58.h
// GRS   |     17     |        128       |  36/('F')       |   5/('3')       | 76066276/('xprv') | https://github.com/GroestlCoin/groestlcoin/blob/master/src/groestlcoin.cpp#L380
// DGC   |     18     |        158       |  30/('D')       |   5/('3')       | 76066276/('xprv') | https://github.com/DGCDev/digitalcoin/blob/master/src/chainparams.cpp#L74
// CCN   |     19     |        156       |  28/('C')       |   5/('3')       |                   | https://github.com/Cannacoin-Project/Cannacoin/blob/Proof-of-Stake/src/base58.h#L275
// DGB   |     20     |        128       |  30/('D')       |   5/('3')       | 76066276/('xprv') | https://github.com/digibyte/digibyte/blob/master/src/chainparams.cpp#L73
// ???   |     21     |  color_agnostic  |  19/'a'(168bits)|  23/('A')       |                   | See "Open Assets Test Vector Examples" below
// MONA  |     22     |        176       |  50/('M')       |   5/('3')       | 76066276/('xprv') | https://github.com/monacoinproject/monacoin/blob/master-0.10/src/chainparams.cpp#L159
// CLAM  |     23     |        133       | 137/('x')       |  13/('6')       | 76066276/('xprv') | https://github.com/nochowderforyou/clams/blob/master/src/chainparams.cpp#L97
// XPM   |     24     |        151       |  23/('A')       |  83/('a')       |                   | https://github.com/primecoin/primecoin/blob/master/src/base58.h#L275
// NEOS  |     25     |        239       |  63/('S')       | 188/('2')       |      unknown      | https://github.com/bellacoin/neoscoin/blob/master/src/chainparams.cpp#L123
// JBS   |     26     |        171       |  43/('J')       | 105/('j')       |                   | https://github.com/jyap808/jumbucks/blob/master/src/base58.h#L276
// ZRC   |     27     |        208       |  80/('Z')       |   5/('3')       | 76066276/('xprv') | https://github.com/ZiftrCOIN/ziftrcoin/blob/master/src/chainparams.cpp#L159
// VTC   |     28     |        199       |  71/('V')       |   5/('3')       |                   | https://github.com/vertcoin/vertcoin/blob/master/src/base58.h#L275
// NXT   |     29     |                  |                 |                 |                   | https://bitbucket.org/JeanLucPicard/nxt/src and unofficial at https://github.com/Blackcomb/nxt
// MUE   |     31     |        143       |  15/('7')       |   9/('4' | '5 ) |1297433939/('HRBy')| https://github.com/MonetaryUnit/MUE-Src/blob/master/src/chainparams.cpp#L221
// ZOOM  |     32     |        231       | 103/('i')       |  92/('e')       |                   | https://github.com/zoom-c/zoom/blob/master/src/base58.h#L275
// VPN   |     33     |        199       |  71/('V')       |   5/('3')       |                   | https://github.com/Bit-Net/VpnCoin/blob/master/src/base58.h#L279
// CDN   |     34     |        156       |  28/('C')       |   5/('3')       |                   | https://github.com/ThisIsOurCoin/canadaecoin/blob/master/src/base58.h#L275
// SDC   |     35     |        191       |  63/('S')       | 125/('s')       |4001378792/('sdcv')| https://github.com/ShadowProject/shadow/blob/master/src/chainparams.cpp#L164
// PKB   |     36     |        183       |  55/('P')       |  28/('C')       |                   | https://github.com/parkbyte/ParkByte/blob/master/src/base58.h#L278
// PND   |     37     |        183       |  55/('P')       |  22/('9' | 'A') |                   | https://github.com/coinkeeper/2015-04-19_21-22_pandacoin/blob/master/src/base58.h#L279
// START |     38     |        253       | 125/('s')       |   5/('3')       |                   | https://github.com/startcoin-project/startcoin/blob/master/src/base58.h#L275
// GCR   |     39     |        154       |  38/('G')       |  97/('g')       | 76066276/('xprv') | https://github.com/globalcurrencyreserve/gcr/blob/master/src/chainparams.cpp#L88
// NVC   |     50     |        136       |   8/('4')       |  20/('9')       |                   | https://github.com/novacoin-project/novacoin/blob/master/src/base58.h#L280
// AC    |     51     |        151       |  23/('A')       |   8/('4')       |                   | https://github.com/AsiaCoin/AsiaCoinFix/blob/master/src/base58.h#L279
// BTCD  |     52     |        188       |  60/('R')       |  85/('b')       |                   | https://github.com/jl777/btcd/blob/master/src/base58.h#L278
// DOPE  |     53     |        136       |   8/('4')       |   5/('3')       |                   | https://github.com/dopecoin-dev/DopeCoinV3/blob/master/src/base58.h#L279
// TPC   |     54     |        193       |  65/('T')       |   5/('3')       |                   | https://github.com/9cat/templecoin/blob/templecoin/src/base58.h#L275
// ???   |     55     |        151       |  23/('A')       |   5/('3')       |                   | https://github.com/iobond/aib/blob/master/src/base58.h#L276 and from ./aib/src/wtmint.h for #define WTMINT_PUBKEY_ADDRESS 23 // Dec.
// ETH   |     60     |                  |                 |                 |                   | https://github.com/ethereum/  and https://github.com/ethereum/cpp-ethereum/wiki
// ???   |     64     |                  |                 |                 |                   | https://github.com/openchain/
// OK    |     69     |        183       |  55/('P')       |  28/('C')       | 63708275/('okpv') | https://github.com/okcashpro/okcash/blob/master/src/chainparams.cpp#L168
// DOGED |     77     |        158       |  30/('D')       |  33/('E')       |                   | https://github.com/doged/dogedsource/blob/master/src/base58.h#L279
// EFL   |     78     |        176       |  48/('L')       |   5/('3')       |                   | https://github.com/Electronic-Gulden-Foundation/egulden/blob/master/src/base58.h#L275
// POT   |     81     |        183       |  55/('P')       |   5/('3')       |                   | https://github.com/potcoin/Potcoin/blob/master/src/base58.h#L275
// XRP   |     NR     | 96?/'s'(116 bits)|96?/'r'(136 bits)|                 |                   | https://github.com/stevenzeiler/ripple-wallet (OMG - Is Ripple using 96 bit secret keys?)
// XMR   |    128     |        N/A       |    /('4')       |    N/A          |  ???              |
// ZEC   |    133     |        128       | 28 & b8 prefix/('t1')| (28 & bd)/('t3')| 76066276/('xprv') | https://github.com/zcash/zcash/blob/master/src/chainparams.cpp#L105
// XTZ   |    ???     |        ???       | 6 & a19f prefix/('tz')|  ??             |  ??

using namespace bc;
// Coin  | coin_type’ |    version_WIF   |  version_p2pkh  |  version_p2sh   | version_hd_secret
// POT   |     81     |        183       |  55/('P')       |   5/('3')  
struct Prefixes
{
	uint32_t bip44_code;
	uint32_t HDprivate;
	uint32_t HDpublic;
	uint32_t P2KH;
	uint32_t P2SH;

};

class HD_Wallet
{
public:
	
	Prefixes BTC =  {0x80000000, 0x0488ADE4, 0x0488B21E, 0x00, 0x05};
	Prefixes tBTC = {0x80000001, 0x04358394, 0x043587CF, 0x6f, 0xC4};
	Prefixes LTC =  {0x80000002, 0x0488ADE4, 0x0488B21E, 0x30, 0x32};
	Prefixes tLTC = {0x80000001, 0x04358394, 0x04358394, 0x6f, 0xC0};
	Prefixes POT =  {0x80000081, 0x0488ADE4, 0x0488B21E, 55, 0x05};

	//constructor
	HD_Wallet()
	{
		data_chunk entropy = data_chunk(16);
		pseudo_random_fill(entropy);
		mnemonic = wallet::create_mnemonic(entropy);
		seed = to_chunk(wallet::decode_mnemonic(mnemonic));
		purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);

	}
	HD_Wallet(Prefixes coin_code)
	{
		data_chunk entropy = data_chunk(16);
		pseudo_random_fill(entropy);
		mnemonic = wallet::create_mnemonic(entropy);
		seed = to_chunk(wallet::decode_mnemonic(mnemonic));
		purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
		setCoinPrefixes(coin_code);

	}

	HD_Wallet(const data_chunk userSeed)
	{
		//defaults to BTC
		seed = userSeed;
		//mnemonic = wallet::create_mnemonic(entropy);
		//seed = entropy; //to_chunk(wallet::decode_mnemonic(mnemonic));
		purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
		setCoinPrefixes(BTC);
	}

	HD_Wallet(const data_chunk userSeed, Prefixes coin_code)
	{
		seed = userSeed;
		//mnemonic = wallet::create_mnemonic(entropy);
		//seed = entropy; //to_chunk(wallet::decode_mnemonic(mnemonic));
		purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
		setCoinPrefixes(coin_code);
	}

	HD_Wallet(const std::string mnemonicSeed)
	{
		//defaults to BTC
		mnemonic = split(mnemonicSeed);
		seed = to_chunk(wallet::decode_mnemonic(mnemonic));
		//seed = to_chunk(hashSeed);
		purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
		setCoinPrefixes(BTC);
	}
	HD_Wallet(const std::string mnemonicSeed, Prefixes coin_code)
	{
		mnemonic = split(mnemonicSeed);
		seed = to_chunk(wallet::decode_mnemonic(mnemonic));
		//seed = to_chunk(hashSeed);
		purpose44Key = wallet::hd_private(seed).derive_private(0x8000002C);
		setCoinPrefixes(coin_code);
	}
	void setCoin(int bip44coin_code)
	{
		coin_type.bip44_code = bip44coin_code;
		coin = purpose44Key.derive_private(bip44coin_code);
	}
	void setCoinPrefixes(Prefixes coin_code)
	{
		coin_type = coin_code;
		coin = purpose44Key.derive_private(coin_type.bip44_code);
		//to-do scan accounts
		set_account(0x80000000);

	}
	void set_account(int account_num)
	{
		currentAccount = account_num;
		account = coin.derive_private(account_num);
	}
	//display output
	void dumpKeys()
	{
		displayMnemonic();
		displayMasterKey();
		displayChildSecretKey(0);
		displayChildAddress(0);

	}
	void displayMasterKey()
	{
		std::cout << "\nMaster Private Key: " << wallet::hd_private(seed).encoded() << std::endl;
	}

	void displayMnemonic()
	{
		if(wallet::validate_mnemonic(mnemonic))
		{
			std::cout << "\n" << join(mnemonic) << std::endl;

		}else{
			std::cout << "\n" << "Mnemonic Invalid! " << std::endl;
		}
	}

	void displayChildSecretKey(int index)
	{
		std::cout << "\nSecret Key: " << encode_base16(childSecretKey(index)) << std::endl;
	}
	// void displayChildWif(int index)
	// {
	// 	std:cout <<"\n WIF: " << childWif(index).encoded() << std::endl;
	// }

	void displayChildPublicKey(int index)
	{
		std::cout << "\nPublic Key: " << childPublicKey(index).encoded() << std::endl;
	}

	void displayChildAddress(int index)
	{
		std::cout << "\nAddress: " << childAddress(index).encoded() << std::endl;
	}
	std::string getChildKeyPath()
	{

		return "Master / 0x8000002C / " + std::to_string(getCoinPrefixes().bip44_code) + " / " + std::to_string(getCurrentAccount()) + " / 0 / Child Index";
	}
	void addressRange(int start, int end)
	{
		while(start != end)
		{
			displayChildAddress(start);
			start++;
		}
	}

	void getBalance(int index)
	{
		
		client::connection_type connection = {};
		connection.retries = 3;
		connection.timeout_seconds = 8;
		connection.server = config::endpoint("tcp://testnet.libbitcoin.net:19091");

		client::obelisk_client client(connection);


		static const auto on_done = [](const chain::history::list& rows)
		{
			uint64_t unspent_balance = 0;

			for(const auto& row: rows)
			{

			    // spend unconfirmed (or no spend attempted)
			    if (row.spend.hash() == null_hash)
			        unspent_balance += row.value;
			}
			std::cout<< encode_base10(unspent_balance, 8) << std::endl;

		};
		static const auto on_error2 = [](const code ec) {

			std::cout << "Error Code: " << ec.message() << std::endl;

		};


		if(!client.connect(connection))
		{
			std::cout << "Fail" << std::endl;
		} else {
			std::cout << "Connection Succeeded" << std::endl;
		}

		client.blockchain_fetch_history3(on_error2, on_done, childAddress(index));
		client.wait();


	}

	//accesor
	wallet::hd_private getMasterKey()
	{
		return wallet::hd_private(seed);
	}
	
	ec_secret childSecretKey(int index)
	{
		return account.derive_private(0).derive_private(index);
	}
	// wallet::hd_private childWif(int index)
	// {
	// 	return account.derive_private(0).derive_private(index);
	// }

	wallet::ec_public childPublicKey(int index)
	{
	
		return account.derive_public(0).derive_public(index).point();
	}

	wallet::payment_address childAddress(int index)
	{
		return wallet::payment_address((childPublicKey(index).point()), coin_type.P2KH);
	}

	Prefixes getCoinPrefixes(){
		return coin_type;
	}

	int getCurrentAccount()
	{
		return currentAccount;
	}
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