TARGET = exe
OUTDIR = out
CC = g++-13
CFLAGS = -g
SRCS = $(filter-out lex.yy.c $(wildcard *_test.c), $(wildcard *.c))
OBJS = $(SRCS:.c=.o)

$(OUTDIR)/$(TARGET): $(addprefix $(OUTDIR)/, lex.yy.o $(OBJS)) 
	$(CC) $(CFLAGS) -o $@ $^ -lfl

$(OUTDIR)/infix_to_postfix_test: $(addprefix $(OUTDIR)/, infix_to_postfix_test.o infix_to_postfix.o)
	$(CC) $(CFLAGS) -o $@ $^

lex.yy.c: parser.l math_exp_enum.h parser_export.h
	lex $< 

$(OUTDIR)/%.o: %.c parser_export.h | $(OUTDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUTDIR):
	mkdir $@

.PHONY: clean run test
clean:
	rm -f lex.yy.c $(addprefix $(OUTDIR)/, $(TARGET) lex.yy.o $(OBJS), infix_to_postfix_test infix_to_postfix_test.o) 

run: $(OUTDIR)/$(TARGET)
	./$(OUTDIR)/$(TARGET)

test: $(OUTDIR)/infix_to_postfix_test
	./$(OUTDIR)/infix_to_postfix_test
