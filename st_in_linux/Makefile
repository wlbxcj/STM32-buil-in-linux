#vpath %.S stlib
#vpath %.c stlib platform newlib stlib/src driver/uart
#vpath %.h stlib platform stlib/cminc stlib/inc driver/uart


CFLAGS += -mcpu=cortex-m3 -mthumb -Wall -std=gnu99
CFLAGS += -Wno-unused-variable					#don't waring unused variable 
#CFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16	#use hard float uint
CFLAGS += -nostartfiles
CFLAGS += -ffunction-sections -fdata-sections -Os
#CFLAGS += -g

LFLAGS += -mcpu=cortex-m3 -mthumb 
LFLAGS += -specs=nano.specs 
#LFLAGS += -u_printf_float 						#Use this option if you want print float
#LFLAGS += -mfloat-abi=hard -mfpu=fpv4-sp-d16
LFLAGS += -Wl,--gc-sections 
LFLAGS += -Wl,-Map=flash_sram.map

DEFS += -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD

ROOT_DIR	=   $(shell pwd)
SUBDIRS		=	$(shell ls -l | grep ^d | awk '{if($$9 != "debug") print $$9}')
CUR_SOURCE  =   $(wildcard *.c)
BUILD_S		= 	startup_stm32f10x_hd.o

OBJS_DIR	=	debug/obj
CUF_OBJ     =   ${patsubst %.c, %.o, $(CUR_SOURCE)}

INCS += -I$(ROOT_DIR)/stlib -I$(ROOT_DIR)/stlib/cminc -I$(ROOT_DIR)/stlib/inc -I$(ROOT_DIR)/platform -I$(ROOT_DIR)/newlib -I$(ROOT_DIR)/driver/uart


CROSS_COMPILE:=~/ST/gcc-arm-none-eabi/bin/arm-none-eabi-
CC := $(CROSS_COMPILE)gcc

export CC CROSS_COMPILE CFLAGS DEFS INCS SOURCES ROOT_DIR OBJS_DIR

LD   := stm32_flash_hd.ld


#OBJ_FLASH += system_stm32f10x.o #code startup from flash 


#change flash code name and sram code name there!!
FNAME = Project

all:$(FNAME).bin

$(FNAME).bin:$(FNAME).elf
	@echo Finish...
	@$(CROSS_COMPILE)objcopy -O binary -S $< $@
	@echo

ALL_O = $(ROOT_DIR)/$(OBJS_DIR)/*.o

$(FNAME).elf:$(ALL_O)
	@echo $@
	@$(CROSS_COMPILE)gcc $(LFLAGS) $^ -Tstlib/$(LD) -o $@
	@$(CROSS_COMPILE)size $@
		

$(ALL_O) : $(BUILD_S) $(SUBDIRS) $(CUF_OBJ)
#@echo


$(BUILD_S):%.o:stlib/%.s
	@echo cc: $^
	@$(CROSS_COMPILE)gcc $(CFLAGS) $(DEFS) $(INCS) -c $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@

$(SUBDIRS):ECHO
	make -C $@

$(CUF_OBJ):%.o:%.c
	@echo cc: $@
	@$(CROSS_COMPILE)gcc $(CFLAGS) $(DEFS) $(INCS) -c $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@

ECHO:
	#@echo $(SUBDIRS)
	@echo
    
.PHONY: all clean burn burns

burn:$(FNAME).bin
	@st-flash write $< 0x08000000


clean:
	@echo rm .o .bin .elf...
	@rm -f $(ROOT_DIR)/$(OBJS_DIR)/*.o $(ROOT_DIR)/$(OBJS_DIR)/*.elf
	@rm -f $(FNAME).bin $(FNAME).elf *.map
	@echo





