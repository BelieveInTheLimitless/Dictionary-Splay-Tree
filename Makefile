st: main.o st.o
	cc main.o st.o -o st
main.o: main.c
	cc -c main.c
bst.o: st.h st.c
	cc -c st.c
clean:
	rm *.o st
