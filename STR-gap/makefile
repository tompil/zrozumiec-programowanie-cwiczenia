IDIR=include
SDIR=src
CC=g++ 
CFLAGS=-I$(IDIR)

ODIR=obj
LIBS=-lboost_unit_test_framework

_DEPS = gap_buffer.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = gap_buffer_tests.o gap_buffer.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

TEST_BIN=gb_tests.out
$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS) | mkodir
	$(CC) -std=c++11 -c -o $@ $< $(CFLAGS)

$(TEST_BIN): $(OBJ)
	$(CC) -std=c++11 -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean mkodir test

clean:
	rm -rf $(ODIR) *.out

mkodir:
	mkdir -p obj

test: $(TEST_BIN)
	./$(TEST_BIN) --color_output --build_info --log_level=all --result_code=no --report_level=short

