What is YuPost?
-------------

YuPost is a decentralized postal network based on Qtum blockchain (https://www.qtum.org).


What is YuPost Core?
------------------

YuPost Core is our primary mainnet wallet. It implements a full node and is capable of storing, validating, and distributing all history of the YuPost network. YuPost Core is considered the reference implementation for the YuPost network. 

YuPost Core currently implements the following:

* Sending/Receiving YPO coins
* Sending/Receiving QRC20 tokens on the YuPost network
* Staking and creating blocks for the YuPost network
* Creating and interacting with smart contracts
* Running a full node for distributing the blockchain to other users
* "Prune" mode, which minimizes disk usage
* Regtest mode, which enables developers to very quickly build their own private YuPost network for Dapp testing
* Testnet mode, using the public YuPost Testnet, with faucet available
* Compatibility with the Bitcoin Core set of RPC commands and APIs
* Full SegWit capability with p2sh-segwit (legacy) and bech32 (native) addresses

Alternative Wallets
-------------------

YuPost Core uses a full node model, and thus requires downloading the entire blockchain. If you do not need the entire blockchain, and do not intend on developing smart contracts, it may be more ideal to use an alternative wallet such as one of our light wallets that can be synchronized in a matter of seconds. 

### YuPost Web Wallet

A browser wallet that supports the Ledger hardware wallet, offline cold wallet, and restoration from mobile wallets.

Web site https://yupostwallet.org

User documentation https://github.com/yupost/documents/tree/master/en/YPO-WebWallet-usage

### YuPost Electrum

A light wallet that supports the Ledger and Trezor hardware wallets and is based on the well-known Electrum wallet software. 

Download: https://github.com/yupost/yupost-electrum/releases

### iOS and Android Wallets

These wallets run on mobile devices and synchronize quickly. 

Android Download: https://play.google.com/store/apps/details?id=org.yupost.newwallet

iOS Download: https://github.com/yupost/yupost-ios (open source, deprecated)

### Ledger Chrome Wallet

This light wallet runs in your Chrome browser as a browser extension. This wallet requires a Ledger device to use.

How to install: https://ledger.zendesk.com/hc/en-us/articles/115003776913-How-to-install-and-use-YuPost-with-Ledger


### Community Resources

Make sure to check out these resources as well for more information and to keep up to date with all the latest news about YuPost. At least 1 developer is always around, so if you're developing on YuPost and need help, we'd love to welcome you to our community.

*	@YuPost on Twitter https://twitter.com/yupost
* YuPost blog https://blog.yupost.org/
*	YuPost Telegram Group https://t.me/yupostofficial, other languages available
* YuPost Discord https://discordapp.com/invite/wRfmkQ9
*	/r/YuPost on Reddit https://www.reddit.com/r/YuPost/
*	YuPost.org https://yupost.org
*	YuPost on Facebook https://www.facebook.com/YuPostOfficial/
*	YuPost Forum https://forum.yupost.org

### YuPost Smart Contract Limitations

*	EVM smart contracts cannot receive coins from or send coins to any address type other than pay-to-pubkeyhash (starts with Q) addresses. This is due to a limitation in the EVM
*	Contracts are not allowed to create contracts with an initial endowment of coins. The contract must first be created, and then be sent coins in a separate transaction. Humans are also not allowed to create contracts with an initial endowment of coins.
*	Although all of the infrastructure is present, YuPost Core does not currently parse Solidity event data. You must parse this yourself using either searchlogs or -record-log-opcodes features.
*	It is not possible to send a contract coins without also executing the contract. This is also the case of Ethereum. This was promised in earlier discussions and technically does work, but due to lack of time for testing this feature was disabled. We hope to reenable this feature with release of the x86 virtual machine in 2020.
*	In YuPost there can be multiple addresses used to create a proof-of-stake block. However, the EVM can only see the first output using the coinbase operation in Solidity (this address is also the one registered for the continuous staker rewards after 500 blocks).

----------

# Building YuPost Core

### Validate and Reproduce Binaries

YuPost uses a tool called Gitian to make reproducible builds that can be verified by anyone. Instructions on setting up a Gitian VM and building YuPost are provided in [Gitan Building](https://github.com/yupost/yupost/blob/master/doc/gitian-building.md)

### Build on Ubuntu

This is a quick start script for compiling YuPost on Ubuntu


    sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils git cmake libboost-all-dev libgmp3-dev
    sudo apt-get install software-properties-common
    sudo add-apt-repository ppa:bitcoin/bitcoin
    sudo apt-get update
    sudo apt-get install libdb4.8-dev libdb4.8++-dev

    # If you want to build the Qt GUI:
    sudo apt-get install libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler qrencode

    git clone https://github.com/yupost/yupost --recursive
    cd yupost

    # Note autogen will prompt to install some more dependencies if needed
    ./autogen.sh
    ./configure 
    make -j2
    
### Build on CentOS

Here is a brief description for compiling YuPost on CentOS, for more details please refer to [the specific document](https://github.com/yupost/yupost/blob/master/doc/build-unix.md)

    # Compiling boost manually
    sudo yum install python-devel bzip2-devel
    git clone https://github.com/boostorg/boost.git
    cd boost
    git checkout boost-1.66.0
    git submodule update --init --recursive
    ./bootstrap.sh --prefix=/usr --libdir=/usr/lib64
    ./b2 headers
    sudo ./b2 -j4 install
    
    # Installing Dependencies for YuPost
    sudo yum install epel-release
    sudo yum install libtool libdb4-cxx-devel openssl-devel libevent-devel gmp-devel
    
    # If you want to build the Qt GUI:
    sudo yum install qt5-qttools-devel protobuf-devel qrencode-devel
    
    # Building YuPost
    git clone --recursive https://github.com/yupost/yupost.git
    cd yupost
    ./autogen.sh
    ./configure
    make -j4

### Build on Mac OS

The commands in this guide should be executed in a Terminal application.
The built-in one is located in `/Applications/Utilities/Terminal.app`.

#### Preparation

Install the Mac OS command line tools:

`xcode-select --install`

When the popup appears, click `Install`.

Then install [Homebrew](https://brew.sh).

#### Dependencies

    brew install cmake automake berkeley-db4 libtool boost miniupnpc openssl pkg-config protobuf qt5 libevent imagemagick librsvg qrencode gmp

NOTE: Building with Qt4 is still supported, however, could result in a broken UI. Building with Qt5 is recommended.

#### Build YuPost Core

1. Clone the yupost source code and cd into `yupost`

        git clone --recursive https://github.com/yupost/yupost.git
        cd yupost

2.  Build yupost-core:

    Configure and build the headless yupost binaries as well as the GUI (if Qt is found).

    You can disable the GUI build by passing `--without-gui` to configure.

        ./autogen.sh
        ./configure
        make

3.  It is recommended to build and run the unit tests:

        make check

### Run

Then you can either run the command-line daemon using `src/yupostd` and `src/yupost-cli`, or you can run the Qt GUI using `src/qt/yupost-qt`

License
-------

YuPost is GPLv3 licensed.

Development Process
-------------------

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/yupost/yupost/tags) are created
regularly to indicate new official, stable release versions of YuPost.

The contribution workflow is described in [CONTRIBUTING.md](https://github.com/yupost/yupost/blob/master/CONTRIBUTING.md)
and useful hints for developers can be found in [doc/developer-notes.md](doc/developer-notes.md).

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test on short notice. Please be patient and help out by testing
other people's pull requests, and remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write [unit tests](src/test/README.md) for new code, and to
submit new unit tests for old code. Unit tests can be compiled and run
(assuming they weren't disabled in configure) with: `make check`. Further details on running
and extending unit tests can be found in [/src/test/README.md](/src/test/README.md).

There are also [regression and integration tests](/test), written
in Python, that are run automatically on the build server.
These tests can be run (if the [test dependencies](/test) are installed) with: `test/functional/test_runner.py`

The Travis CI system makes sure that every pull request is built for Windows, Linux, and macOS, and that unit/sanity tests are run automatically.

### Manual Quality Assurance (QA) Testing

Changes should be tested by somebody other than the developer who wrote the
code. This is especially important for large or high-risk changes. It is useful
to add a test plan to the pull request description if testing the changes is
not straightforward.

