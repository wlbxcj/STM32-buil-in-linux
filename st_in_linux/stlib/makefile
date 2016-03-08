INCS += -I$(shell pwd) -I$(ROOT_DIR)/stlib/inc -I$(ROOT_DIR)/stlib

vpath %.S stlib
vpath %.c stlib platform newlib stlib/src driver/uart
vpath %.h stlib platform stlib/cminc stlib/inc driver/uart

#子目录的Makefile直接读取其子目录就行
SUBDIRS=$(shell ls -l | grep ^d | awk '{print $$9}')


#以下同根目录下的makefile的相同代码的解释
CUR_SOURCE=${wildcard *.c}
CUR_OBJS=${patsubst %.c, %.o, $(CUR_SOURCE)}


all:$(SUBDIRS) $(CUR_OBJS)
$(SUBDIRS):ECHO
	make -C $@
$(CUR_OBJS):%.o:%.c
	@$(CROSS_COMPILE)gcc $(CFLAGS) $(DEFS) $(INCS) -c $< -o $(ROOT_DIR)/$(OBJS_DIR)/$@
ECHO:
	@echo $(SUBDIRS)
	@echo