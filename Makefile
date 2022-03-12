LIB_OBJ := cJSON/cJSON_Utils.o \
	cJSON/cJSON.o 
LIB_CFLAGS  = $(CFLAGS) -shared -fPIC
LIB_LDFLAGS = $(LDFLAGS) -Wl,-soname,$(LIB_FILENAME)
LIB_FILENAME = libjson-c.so

# cd demo
# gcc ../cJSON/cJSON.c ../struct2json/src/*.c ./*.c 
#	-I ../cJSON/ 
#	-I ../
#	-lm -DDEBUGS2J  -g -o tests2j

MY_OUTPUT := tests2j 
MY_TARGETS := demo/main.o \
		demo/my_struct_2_json.o \
		struct2json/src/s2j.o \

MY_CFLAGS += $(CFLAGS)  \
		-I struct2json/inc/ \
		-I cJSON/ \
		-I demo/inc/ \
		-I demo/ \

MY_LDFLAGS += $(LDLIBS) -L ./ -lm -ljson-c


#依赖
lib: $(LIB_OBJ)
	$(CC) $(LIB_CFLAGS) $(LIB_LDFLAGS)  -o $(LIB_FILENAME) $(LIB_OBJ) -lc

all: $(MY_OUTPUT)


$(MY_OUTPUT): $(MY_TARGETS)
	$(CC) $(MY_CFLAGS)  -o $@  $^  $(MY_LDFLAGS)

%.o: %.c
	$(CC) $(MY_CFLAGS) $(LIB_CFLAGS) -o $@ -c $^

clean:
	rm -f $(LIB_FILENAME)* $(MY_OUTPUT) *.o  demo/*.o

