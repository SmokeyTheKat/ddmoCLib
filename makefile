CHEADERS = $(shell find ./* -type f -name '*.h')
all:
	sudo cp $(CHEADERS) /usr/include/
