Make:
	gcc ADD_POINT.c -o exeADD `pkg-config --cflags --libs gtk+-3.0` -lgmp