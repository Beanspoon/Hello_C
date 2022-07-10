PROJECT = helloC

SRCS += \
	main.c

CFLAGS += \
    -mthumb \
    -mcpu=cortex-m4 \
	-mfloat-abi=hard \
	-mfpu=fpv4-sp-d16 \
	-std=c99 \
	-O \
	-g \
	-ffreestanding \
	-ffunction-sections \
	-fdata-sections

LDFLAGS += \
	-specs=nosys.specs \
	-Wl,--print-memory-usage \
	-Wl,-Map=flash.map \
	-Wl,--gc-sections

BUILD_DIR ?= build
OBJ_DIR ?= $(BUILD_DIR)/objs
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

.PHONY: all
all: $(BUILD_DIR)/$(PROJECT).bin

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c $(OBJ_DIR)
	@echo "Compiling $<..."
	@arm-none-eabi-gcc -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/$(PROJECT).elf: $(OBJS)
	@echo "Linking $@..."
	@arm-none-eabi-gcc -o $@ $^ $(CFLAGS) $(LDFLAGS)
	@echo

$(BUILD_DIR)/$(PROJECT).lst: $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)
	@arm-none-eabi-objdump -D $< > $@
	@echo

$(BUILD_DIR)/$(PROJECT).bin: $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).lst
	@arm-none-eabi-objcopy $< $@ -O binary
	@arm-none-eabi-size $<

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: asm
asm: $(BUILD_DIR)/$(PROJECT).asm

$(BUILD_DIR)/$(PROJECT).asm: %.c
	@echo "Compiling $<..."
	@arm-none-eabi-gcc -S -o $@ $< $(CFLAGS)
    
