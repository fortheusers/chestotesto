all:
	@echo " _____ _               _      _____         _        "
	@echo "/  __ \ |             | |    |_   _|       | |       "
	@echo "| /  \/ |__   ___  ___| |_ ___ | | ___  ___| |_ ___  "
	@echo "| |   | '_ \ / _ \/ __| __/ _ \| |/ _ \/ __| __/ _ \ "
	@echo "| \__/\ | | |  __/\__ \ || (_) | |  __/\__ \ || (_) |"
	@echo " \____/_| |_|\___||___/\__\___/\_/\___||___/\__\___/ "
	@echo
	@echo "Hi! See the readme for instructions on how to make this program for different supported platforms."
	@echo "In short, you can add \"-f Makefile.switch\" or \"-f Makefile.wiiu\" to build apps for either of those targets."
	@echo
	@echo "Defaulting to the PC build:"
	make -f Makefile.pc

clean:
	make -f Makefile.pc clean
