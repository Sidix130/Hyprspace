CXXFLAGS=-shared -fPIC --no-gnu-unique -Wall -g -DWLR_USE_UNSTABLE -std=c++2b -O2 -I${HOME}/Hyprland/src -I${HOME}/Hyprland/subprojects/wlroots/include -I/usr/include/hyprland/protocols -I/usr/include/hyprland/src
INCLUDES = `pkg-config --cflags pixman-1 libdrm pangocairo libinput libudev wayland-server xkbcommon`
SRC = $(wildcard src/*.cpp)
TARGET = Hyprspace.so
PREFIX ?= /usr/local
LIBDIR ?= $(PREFIX)/lib

all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) -o $(TARGET)

install:
	install -D -m 0755 $(TARGET) $(DESTDIR)$(LIBDIR)/$(TARGET)

clean:
	rm -f ./$(TARGET)

withhyprpmheaders: export PKG_CONFIG_PATH = $(XDG_DATA_HOME)/hyprpm/headersRoot/share/pkgconfig
withhyprpmheaders: all
