
CFLAGS=`pkg-config --cflags libbitcoin --libs libbitcoin libbitcoin-client`



wallet: wallet.cpp bip44wallet.cpp
	g++ -std=c++11 -o wallet wallet.cpp bip44wallet.cpp $(CFLAGS)
	./wallet
clean:
	rm wallet

