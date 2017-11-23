
CFLAGS=`pkg-config --cflags libbitcoin --libs libbitcoin libbitcoin-client`
FLAGS= -I/root/bitcoin/src -I/root/bitcoin/src/rpc -I/root/bitcoin/src/univalue/include -L/root/bitcoin/src
# libbitcoin_server.a
# LIBBITCOIN_COMMON=libbitcoin_common.a
# LIBBITCOIN_CONSENSUS=libbitcoin_consensus.a
# LIBBITCOIN_CLI=libbitcoin_cli.a
# LIBBITCOIN_UTIL=libbitcoin_util.a
# LIBBITCOIN_CRYPTO=crypto/libbitcoin_crypto.a
# LIBBITCOINQT=qt/libbitcoinqt.a
# LIBSECP256K1=secp256k1/libsecp256k1.la
# xx=/root/bitcoin/src/libbitcoin_server.a /root/bitcoin/src/libbitcoin_util.a /root/bitcoin/src/libbitcoin_consensus.a /root/bitcoin/src/secp256k1/libsecp256k1.la /root/bitcoin/src/libbitcoin_common.a /root/bitcoin/src/libbitcoin_cli.a /root/bitcoin/src/crypto/libbitcoin_crypto.a -UWORDS_BIGENDIAN -UHAVE_BYTESWAP_H -UHAVE_ENDIAN_H
xx=/root/bitcoin/src/libbitcoin_server.a -DWORDS_BIGENDIAN -DHAVE_BYTESWAP_H -DHAVE_ENDIAN_H -DBUILD_BITCOIN_INTERNAL
wallet: wallet.cpp bip44wallet.cpp
	g++ -std=c++11 -o wallet wallet.cpp bip44wallet.cpp $(CFLAGS
	# ./wallet
bip44wallet.o:bip44wallet.cpp
	g++ -std=c++11 -g $(CFLAGS) $(FLAGS)  $(xx) -fPIC -O2 -c bip44wallet.cpp
interface.o:interface.cpp
	g++ -std=c++11 -g $(CFLAGS) $(FLAGS) -fPIC -O2 -c interface.cpp

so: bip44wallet.o interface.o
	g++ $(CFLAGS) $(FLAGS) bip44wallet.o interface.o -fPIC -shared -o libbip44wallet.so
clean:
	rm wallet *.o

