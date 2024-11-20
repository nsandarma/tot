CXX = g++
CXXFLAGS = -Wall -Wextra 
SRCDIR = src
TARGET = tot

# File source code
SRC = $(wildcard $(SRCDIR)/*cpp)

# Object files yang dihasilkan
OBJ = $(SRC:.cpp=.o)

# Target default, akan dijalankan jika tidak ada target spesifik yang diberikan
all: $(TARGET)

# Proses linking untuk membuat executable
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lm

# Kompilasi file .c menjadi .o
%.o: %.c
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Membersihkan file objek dan executable
clean:
	rm -f $(OBJ) $(TARGET)

# Phony target untuk memastikan clean dan all tidak bentrok dengan file bernama sama
.PHONY: clean all

