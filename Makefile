
CXXFLAGS= -lmagic -lpthread

main :main.o indexer.o lf.o searcher.o publicutils.o
	@echo linking executable...
	@gcc $(CXXFLAGS) -o main main.o indexer.o lf.o searcher.o publicutils.o

main.o:main.c publicheader.h
	@echo GCC main.o
	@gcc $(CXXFLAGS) -c -o main.o main.c

indexer.o:indexer/indexer.c indexer/indexer.h publicheader.h
	@echo GCC indexer.o
	@gcc $(CXXFLAGS) -c -o indexer.o indexer/indexer.c

lf.o: lf/lf.c lf/lf.h publicheader.h
	@echo GCC lf.o
	@gcc $(CXXFLAGS) -c -o lf.o lf/lf.c

searcher.o: searcher/searcher.c searcher/searcher.h publicheader.h
	@echo GCC searcher.o
	@gcc $(CXXFLAGS) -c -o searcher.o searcher/searcher.c

publicutils.o: publicutils.c publicutils.h publicheader.h
	@echo GCC publicutils.o
	@gcc $(CXXFLAGS) -c -o publicutils.o publicutils.c

clean:
	@echo CLEAN
	@rm *.o
	@rm main
