TARGET = exe
LIB_NAME = libmx.a
OUTDIR = out
LIB = $(OUTDIR)/$(LIB_NAME)
CC = g++-13
CFLAGS = -g
SRCS = $(filter-out lex.yy.c $(wildcard *_test.c), $(wildcard *.c))
SRCS_CPP = $(wildcard *.cpp)
OBJS = $(SRCS:.c=.o)
OBJS_CPP = $(SRCS_CPP:.cpp=.o)
TEST_OBJS = infix_to_postfix_test.o infix_to_postfix.o math_expr_tree.o operator.o dtype.o
LIB_OBJS = math_cfg.o infix_to_postfix.o math_expr_tree.o operator.o dtype.o

all: $(LIB) $(OUTDIR)/$(TARGET) $(OUTDIR)/infix_to_postfix_test

$(LIB): $(addprefix $(OUTDIR)/,  $(LIB_OBJS)) | $(OUTDIR)
	ar -rcs $@ $^

$(OUTDIR)/$(TARGET): $(addprefix $(OUTDIR)/, lex.yy.o $(OBJS) $(OBJS_CPP)) 
	$(CC) $(CFLAGS) -o $@ $^ -lfl

$(OUTDIR)/infix_to_postfix_test: $(addprefix $(OUTDIR)/, $(TEST_OBJS))
	$(CC) $(CFLAGS) -o $@ $^

lex.yy.c: parser.l math_exp_enum.h parser_export.h
	lex $< 

$(OUTDIR)/%.o: %.c parser_export.h | $(OUTDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUTDIR)/%.o: %.cpp parser_export.h | $(OUTDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUTDIR):
	mkdir $@

.PHONY: clean run test
clean:
	rm -f lex.yy.c $(addprefix $(OUTDIR)/, $(TARGET) lex.yy.o $(OBJS) $(OBJS_CPP) $(TEST_OBJS) infix_to_postfix_test) $(LIB)

run: $(OUTDIR)/$(TARGET)
	./$(OUTDIR)/$(TARGET)

test: $(OUTDIR)/infix_to_postfix_test
	./$(OUTDIR)/infix_to_postfix_test
