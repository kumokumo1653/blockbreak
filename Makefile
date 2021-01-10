TARGET = app.exe

SRCS = main.c ball.c field.c line.c shape.c vector.c block.c paddle.c item.c

OBJS = ${SRCS:.c=.o}

HEADERS = line.h shape.h vector.h ball.h field.h block.h paddle.h item.h

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
