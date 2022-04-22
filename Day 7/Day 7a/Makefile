C=g++ -g -Wall --std=c++14 -O3
E=.cpp
O=main.o
P=Day7a
all: $(P)
$(P):$(O)
	$(C) -o $(P) $(O)
$(E).o:
	$(C) -c $< -o $@
clean:
	rm $(O) $(P)

.PHONY: clean all
