gcc data_linked.c -o data_linked && \
	gcc linux_linked.c -o linux_linked && \
	time ./data_linked && \
	time ./linux_linked
