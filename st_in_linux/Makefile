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
LFLAGS += -Wl,-Map=$(EXEC_DIR)/$(FNAME).map

DEFS += -DUSE_STDPERIPH_DRIVER -DSTM32F10X_HD

ROOT_DIR	=   $(shell pwd)
SUBDIRS		=	$(shell ls -l | grep ^d | awk '{if($$9 != "debug" && $$9 != "usr") print $$9}')
TARGET_SOURCE  =   stm32f10x_it.c main.c
BUILD_S		= 	startup_stm32f10x_hd.o

OBJS_DIR	=	debug/obj
EXEC_DIR	= 	debug/Exc
CUF_OBJ     =   ${patsubst %.c, %.o, $(TARGET_SOURCE)}
ALL_O		= 	$(ROOT_DIR)/$(OBJS_DIR)/*.o


INCS += -I$(ROOT_DIR)/stlib -I$(ROOT_DIR)/stlib/cminc -I$(ROOT_DIR)/stlib/inc -I$(ROOT_DIR)/platform -I$(ROOT_DIR)/newlib -I$(ROOT_DIR)/driver/uart


CROSS_COMPILE:=~/ST/gcc-arm-none-eabi/bin/arm-none-eabi-
CC := $(CROSS_COMPILE)gcc

export CC CROSS_COMPILE CFLAGS DEFS INCS ROOT_DIR OBJS_DIR

LD   := stm32_flash_hd.ld


#OBJ_FLASH += system_stm32f10x.o #code startup from flash 


#change flash code name and sram code name there!!
FNAME = Project

all:$(FNAME).bin

$(FNAME).bin:$(FNAME).elf
	@$(CROSS_COMPILE)objcopy -O binary -S $(EXEC_DIR)/$< $(EXEC_DIR)/$@
	@$(CROSS_COMPILE)objcopy -O ihex $(EXEC_DIR)/$< $(EXEC_DIR)/$(FNAME).hex
	@echo 
	@echo ouput $(EXEC_DIR)/$@
	@echo ouput $(EXEC_DIR)/$(FNAME).hex
	@echo Finish...

$(FNAME).elf:$(ALL_O)
	@echo $@
	@$(CROSS_COMPILE)gcc $(LFLAGS) $^ -Tstlib/$(LD) -o $(EXEC_DIR)/$@
	@$(CROSS_COMPILE)size $(EXEC_DIR)/$@
		

$(ALL_O) : $(BUILD_S) $(SUBDIRS) $(CUF_OBJ)
#@echo


$(BUILD_S):%.o:stlib/%.s
	@echo cc: $^
	@$(CROSS_COMPILE)gcc $(CFLAGS) $(DEFS) $(INCS) -c $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@

$(SUBDIRS):ECHO
	make -C $@

$(CUF_OBJ):%.o:usr/%.c
	@echo cc: $^
	@$(CROSS_COMPILE)gcc $(CFLAGS) $(DEFS) $(INCS) -c $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@

ECHO:
	@echo $(SUBDIRS)...
	@echo

burn:$(FNAME).bin
	@st-flash write $< 0x08000000


clean:
	@echo rm .o .bin .elf...
	@rm -f $(ROOT_DIR)/$(OBJS_DIR)/*
	@rm -f $(EXEC_DIR)/*
	@echo





