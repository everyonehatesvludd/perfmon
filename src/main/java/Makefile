CC = gcc
LDFLAGS = -lws2_32 -lpdh
TARGET = my_program
SRC = Client.c

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)
