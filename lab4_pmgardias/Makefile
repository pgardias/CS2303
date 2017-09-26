#CS-2303 Lab4_Sample
#	Hugh C. Lauer
#	August 26, 2013

#	Updated 01-02-2017. Removed -m32 flag and *.exe

CXXFLAGS = -g -Wall -fmessage-length=0

OBJS =	Lab4_example.o SortedList.o

LIBS =

TARGET =	Lab4_example

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

*.o: *.cpp
	$(CXX) -c $(CXXFLAGS) *.cpp

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
