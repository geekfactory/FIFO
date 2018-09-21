test:
	cd test/infrastructure && ceedling test:all

clean-test:
	rm -rf build/test/*

clean-all:
	rm -rf build/*

.PHONY: all test clean