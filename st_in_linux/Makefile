#vpath %.S stlib
#vpath %.c stlib platform newlib stlib/src driver/uart
vpath %.h $(INCS)


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
SUBDIRS		=	$(shell ls -l | grep ^d | awk '{if($$9 != "debug" && $$9 != "user" && $$9 != "CMSIS" \
                && $$9 != "FWlib" && $$9 != "Proj" && $$9 != "Starup" && $$9 != "USER") print $$9}')

TARGET_SOURCE  =   stm32f10x_it.c main.c
BUILD_S		= 	startup_stm32f10x_hd.o
OS_CPU_O    =   os_cpu_a.o

OBJS_DIR	=	debug/obj
EXEC_DIR	= 	debug/Exc
CUF_OBJ     =   ${patsubst %.c, %.o, $(TARGET_SOURCE)}
#ALL_O		= 	$(ROOT_DIR)/$(OBJS_DIR)/*.o
ALL_C		= 	$(notdir $(shell find -name "*.c"))
#ALL_C		-= 	stm32f10x_it.c main.c
ALL_B		= 	${patsubst %.c, %.o, $(ALL_C)}
ALL_B		+= 	$(BUILD_S) $(OS_CPU_O)
ALL_O		= 	$(foreach n, $(ALL_B), $(ROOT_DIR)/$(OBJS_DIR)/$(n))

INCS += -I$(ROOT_DIR) -I$(ROOT_DIR)/stlib -I$(ROOT_DIR)/stlib/cminc -I$(ROOT_DIR)/stlib/inc  -I$(ROOT_DIR)/driver/uart -I$(ROOT_DIR)/driver/led \
		-I$(ROOT_DIR)/App -I$(ROOT_DIR)/BSP -I$(ROOT_DIR)/uCOS_Ports -I$(ROOT_DIR)/uCOS_Source -I$(ROOT_DIR)/user -I$(ROOT_DIR)/driver/uart \
		-I$(ROOT_DIR)/driver/lcd -I$(ROOT_DIR)/driver/font


CROSS_COMPILE:=~/ST/gcc-arm-none-eabi/bin/arm-none-eabi-
CC := $(CROSS_COMPILE)gcc

export CC CROSS_COMPILE CFLAGS DEFS INCS ROOT_DIR OBJS_DIR

LD   := stm32_flash_hd.ld



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
		

$(ALL_O) : $(BUILD_S) $(OS_CPU_O) $(SUBDIRS) $(CUF_OBJ)
#@echo


$(BUILD_S):%.o:stlib/%.s
	@echo cc: $^
	@$(CROSS_COMPILE)gcc $(CFLAGS) $(DEFS) $(INCS) -c $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@


$(OS_CPU_O):%.o:uCOS_Ports/*.s
	@echo cc: $^
	@$(CROSS_COMPILE)gcc -c $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@


$(SUBDIRS):ECHO
	make -C $@

$(CUF_OBJ):%.o:user/%.c
	@echo cc: $^
	@$(CROSS_COMPILE)gcc $(CFLAGS) $(DEFS) $(INCS) -c $^ -o $(ROOT_DIR)/$(OBJS_DIR)/$@

ECHO:
	@echo
    

burn:$(FNAME).bin
	@st-flash write $< 0x08000000


clean:
	@echo rm .o .bin .elf...
	@rm -f $(ROOT_DIR)/$(OBJS_DIR)/*
	@rm -f $(EXEC_DIR)/*
	@echo





