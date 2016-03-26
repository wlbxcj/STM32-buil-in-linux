INCS += -I$(shell pwd)


#子目录的Makefile直接读取其子目录就行
SUBDIRS=$(shell ls -l | grep ^d | awk '{print $$9}')


#以下同根目录下的makefile的相同代码的解释
CUR_SOURCE=${wildcard *.c}
CUR_OBJSB=${patsubst %.c, %.o, $(CUR_SOURCE)}

CUR_OBJS = $(foreach n, $(CUR_OBJSB), $(ROOT_DIR)/$(OBJS_DIR)/$(n))

all:$(SUBDIRS) $(CUR_OBJS)
$(SUBDIRS):ECHO
	make -C $@

$(CUR_OBJS):$(ROOT_DIR)/$(OBJS_DIR)/%.o:%.c
	@echo CC: $^
	@$(CROSS_COMPILE)gcc $(CFLAGS) $(DEFS) $(INCS) -c $< -o $@

ECHO:
	@echo