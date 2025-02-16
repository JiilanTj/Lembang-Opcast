CC = gcc
CFLAGS = -Wall -Wextra -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 \
         -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/pango-1.0 \
         -I/usr/include/harfbuzz -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 \
         -I/usr/include/atk-1.0 -I/usr/include/libavcodec -I/usr/include/libavformat \
         -I/usr/include/libavutil -I/usr/include/libswscale -I/usr/include/pulse

LDFLAGS = -lX11 -lgtk-3 -lgobject-2.0 -lglib-2.0 -lavcodec -lavformat -lavutil \
          -lswscale -lpulse -lpulse-simple -lrtmp

SRC_DIR = src
BUILD_DIR = build

# List semua source files
SOURCES = $(SRC_DIR)/main.c \
          $(SRC_DIR)/capture/screen_capture.c \
          $(SRC_DIR)/capture/audio_capture.c \
          $(SRC_DIR)/gui/window.c \
          $(SRC_DIR)/utils/logger.c \
          $(SRC_DIR)/encoder/video_encoder.c \
          $(SRC_DIR)/streaming/stream_manager.c

# Generate object files dari source files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

TARGET = $(BUILD_DIR)/lembang-opcast

.PHONY: all clean directories

all: directories $(TARGET)

directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/capture
	@mkdir -p $(BUILD_DIR)/gui
	@mkdir -p $(BUILD_DIR)/utils
	@mkdir -p $(BUILD_DIR)/encoder
	@mkdir -p $(BUILD_DIR)/streaming

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) 