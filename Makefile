
CFLAGS=`pkg-config --cflags libbitcoin --libs libbitcoin libbitcoin-client`



wallet: wallet.cpp bip44wallet.cpp
	g++ -std=c++11 -o wallet wallet.cpp bip44wallet.cpp $(CFLAGS)
	# ./wallet
bip44wallet.o:bip44wallet.cpp
	g++ -std=c++11 -g $(CFLAGS) -fPIC -O2 -c bip44wallet.cpp
interface.o:interface.cpp
	g++ -std=c++11 -g $(CFLAGS) -fPIC -O2 -c interface.cpp

so: bip44wallet.o interface.o
	g++ $(CFLAGS) bip44wallet.o interface.o -fPIC -shared -o libbip44wallet.so
clean:
	rm wallet *.o

