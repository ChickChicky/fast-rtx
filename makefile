CC = g++
CFLAGS = -Wall -Wextra -O3

CINCLUDE += $(sort $(dir $(wildcard src/**/)))

build: src/**.cpp
	$(CC) -o rtx $(CFLAGS) $(addprefix -I , $(CINCLUDE)) $(addprefix -L , $(CLIB)) $^

exec:
ifneq (,$(wildcard rtx.exe))
	./rtx.exe
else ifneq (,$(wildcard rtx))
	./rtx
endif

run: build exec

clean:
ifneq (,$(wildcard rtx.exe)) 
	rm rtx.exe
else ifneq (,$(wildcard rtx))
	rm rtx
endif