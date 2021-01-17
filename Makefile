TARGET = j17404.exe

SRCS = main.c ball.c field.c line.c vector.c block.c paddle.c item.c

OBJS = ${SRCS:.c=.o}

HEADERS = line.h vector.h ball.h field.h block.h paddle.h item.h

CC = i686-pc-cygwin-gcc
CCFLAGS = -Wall -I/usr/include/opengl
LD = i686-pc-cygwin-gcc
LDFLAGS = 
LIBS = -lglpng -lglut32 -lglu32 -lopengl32 -lm icon.o

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
