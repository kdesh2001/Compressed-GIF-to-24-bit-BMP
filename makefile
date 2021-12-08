DEPS = gif.h bmp.h
all_sources = main.c gif.c bmp.c 
all_objs = $(all_sources:.c=.o)
my_project : $(DEPS) $(all_objs)
	gcc -o my_project main.o gif.o bmp.o $(all_modules) -lm
%.o : %.c $(DEPS)
	gcc -c $<
clean :
	rm destination_image.bmp my_project *.o