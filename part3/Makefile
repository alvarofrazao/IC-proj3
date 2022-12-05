all:
	@(if [ ! -d build ]; then mkdir build; fi; cd build;\
	  if [ ! -d part3-bin ]; then mkdir part3-bin; fi; cmake ..; make)

clean:
	rm -rf build ../part3-bin
