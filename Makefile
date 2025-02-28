simavr_debug: build
	C:\Users\admin\.platformio\packages\tool-simavr\bin\simavr -m atmega328 -f 16000000 .pio/build/nanoatmega328/firmware.elf
build:
	pio run