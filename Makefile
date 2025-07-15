TARGET = exe
OUTDIR = out
CC = g++-13
CFLAGS = -g
SRCS = $(filter-out lex.yy.c, $(wildcard *.c))
OBJS = $(SRCS:.c=.o)

$(OUTDIR)/$(TARGET): $(addprefix $(OUTDIR)/, lex.yy.o $(OBJS)) 
	$(CC) $(CFLAGS) -o $@ $^ -lfl

lex.yy.c: parser.l math_exp_enum.h parser_export.h
	lex $< 

$(OUTDIR)/%.o: %.c parser_export.h | $(OUTDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUTDIR):
	mkdir $@

.PHONY: clean
clean:
	rm -f lex.yy.c $(addprefix $(OUTDIR)/, $(TARGET) lex.yy.o $(OBJS)) 

run: $(OUTDIR)/$(TARGET)
	./$(OUTDIR)/$(TARGET)
