
%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<
