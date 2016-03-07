vpath %.S stlib
vpath %.c stlib platform newlib stlib/src 
vpath %.h stlib platform stlib/cminc stlib/inc

CC   = ~/ST/gcc-arm-none-eabi/bin/arm-none-eabi-


DEFS += -DUSE_STDPERIPH_DRIVER

INCS += -Istlib -Istlib/cminc -Istlib/inc -Iplatform -Inewlib

OBJS += stlib/startup_stm32f30x.o 
OBJS += stlib/src/stm32f30x_rcc.o stlib/src/stm32f30x_gpio.o 
OBJS += stlib/src/stm32f30x_usart.o
OBJS += platform/init.o platform/ringbuffer.o platform/usart.o
OBJS += newlib/syscalls.o newlib/sys_itoa.o
OBJS += main.o

OBJ_FLASH += stlib/system_stm32f30x.o #code startup from flash 
OBJ_SRAM  += stlib/system_stm32f30x_sram.o #code startup from sram 

CFLAGS += -mcpu=cortex-m3 -mthumb -Wall -std=gnu99
CFLAGS += -Wno-unused-variable #don't waring unused variable 
#CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16 #use hard float uint
CFLAGS += -nostartfiles
CFLAGS += -ffunction-sections -fdata-sections -Os
#CFLAGS += -g

LFLAGS += -mcpu=cortex-m3 -mthumb 
LFLAGS += -specs=nano.specs 
#LFLAGS += -u_printf_float #Use this option if you want print float
#LFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
LFLAGS += -Wl,--gc-sections 
LFLAGS += -Wl,-Map=flash_sram.map

#change flash code name and sram code name there!!
FNAME = serial
SNAME = serials

all:$(FNAME).bin
sram:$(SNAME).bin

clean:
	@rm -f $(OBJS) $(OBJ_FLASH) $(OBJ_SRAM)  
	@rm -f $(FNAME).bin $(FNAME).elf $(SNAME).bin $(SNAME).elf
	
$(FNAME).bin:$(FNAME).elf
	@echo Finish...
	@$(CC)objcopy -O binary -S $< $@
	@echo

$(SNAME).bin:$(SNAME).elf
	@$(CC)objcopy -O binary -S $< $@
	
$(FNAME).elf:$(OBJS) $(OBJ_FLASH)
	@echo
	@$(CC)gcc $(LFLAGS) $^ -Tstlib/flash.ld -o $@
	@$(CC)size $@
	
	
$(SNAME).elf:$(OBJS) $(OBJ_SRAM)
	@$(CC)gcc $(LFLAGS) $^ -Tstlib/sram.ld -o $@
	@$(CC)size $@
	
burn:$(FNAME).bin
	@st-flash write $< 0x08000000
burns:$(SNAME).bin
	@st-flash write $< 0x20005000
	
%.o:%.S
	@echo cc: $<
	@$(CC)gcc $(CFLAGS) -c $< -o $@
%.o:%.c
	@echo cc: $<
	@$(CC)gcc $(CFLAGS) $(DEFS) $(INCS) -c $< -o $@

.PHONY: all clean burn burns






