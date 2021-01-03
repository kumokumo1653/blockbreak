TARGET = app.exe

SRCS = main.c ball.c field.c flipper.c line.c shape.c vector.c corner.c

OBJS = ${SRCS:.c=.o}

HEADERS = ball.h field.h flipper.h line.h shape.h vector.h corner.h

CC = gcc
CCFLAGS = -Wall -I/usr/include/opengl
LD = gcc
LDFLAGS = 
LIBS =  -lglpng -lglut -lGLU -lGL -lm

#OBJSからTARGETをつくる
$(TARGET) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(TARGET) $(LIBS)

#.cから.oをつくる
.c.o :
	$(CC) $(CCFLAGS) -c $<

#.oはHEAERSとMakefileに依存
$(OBJS) : $(HEADERS) Makefile

#make cleanの定義
clean : 
	rm -f $(TARGET) $(OBJS) core *~
