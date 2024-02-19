
all: 
	$(MAKE) engine
	$(MAKE) sandbox

engine:
	echo 'Building the engine'
	$(MAKE) -C ./engine all
sandbox:
	echo 'Building the sandbox'
	$(MAKE) -C ./sandbox all
clean:
	echo 'Cleanning the engine build'
	$(MAKE) -C ./engine clean
	echo 'Cleanning the sandbox build'
	$(MAKE) -C ./sandbox clean

.PHONY: clean engine sandbox
