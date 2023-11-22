all: converterArquivoArvoreBinariaParaTxt.o converterArquivoIndexBinariaParaTxt.o converterBinarioDeRegistrosParaTxt.o geraleatorio.o gercrescente.o gerdecrescente.o main.o
	@gcc ./converterArquivoArvoreBinariaParaTxt.o ./converterArquivoIndexBinariaParaTxt.o ./converterBinarioDeRegistrosParaTxt.o \
		./geraleatorio.o ./gercrescente.o ./gerdecrescente.o ./main.o $(LIBS) -o exe
	@rm ./converterArquivoArvoreBinariaParaTxt.o
	@rm ./converterArquivoIndexBinariaParaTxt.o
	@rm ./converterBinarioDeRegistrosParaTxt.o
	@rm ./geraleatorio.o
	@rm ./gercrescente.o
	@rm ./gerdecrescente.o
	@rm ./main.o


converterArquivoArvoreBinariaParaTxt.o: ./converterArquivoArvoreBinariaParaTxt.c
	@gcc ./converterArquivoArvoreBinariaParaTxt.c -c  -std=c11 -Wall
	
converterArquivoIndexBinariaParaTxt.o: ./converterArquivoIndexBinariaParaTxt.c
	@gcc ./converterArquivoIndexBinariaParaTxt.c -c -std=c11 -Wall

converterBinarioDeRegistrosParaTxt.o: ./converterBinarioDeRegistrosParaTxt.c
	@gcc ./converterBinarioDeRegistrosParaTxt.c -c -std=c11 -Wall

geraleatorio.o: ./geraleatorio.c
	@gcc ./geraleatorio.c -c -std=c11 -Wall

gercrescente.o: ./gercrescente.c
	@gcc ./gercrescente.c -c -std=c11 -Wall

gerdecrescente.o: ./gerdecrescente.c
	@gcc ./gerdecrescente.c -c -std=c11 -Wall

position.o: ./position/position.c
	@gcc ./position/position.c -c -std=c11 -Wall

main.o: ./main.c
	@gcc ./main.c -c -std=c11 -Wall

run:
	@./exe
