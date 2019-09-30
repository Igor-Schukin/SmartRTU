.PHONY : clean

NAME = infoboard

WOBJ = 	obj/IWidget.o \
		obj/WgBackground.o \
		obj/WgClock.o \
		obj/WgCalendar.o \
		obj/WgForecast.o \
		obj/WgAds.o \
		obj/WgSockets.o \
		obj/WgTimetable.o \
		obj/WgWatchdog.o

INCS = 	-I/usr/include/freetype2 
 
HDRS = 	*.h \
		lib/*.h \
		lib/TFont/*.h
		
WHDRS = widgets/*.h

OBJ = 	obj/CPicturesStorage.o \
		obj/CFontStorage.o \
		obj/Timer.o \
		obj/Picture.o \
		obj/ftf.o \
		obj/TFont.o \
		obj/json.o \
		obj/timetable.o \
		obj/board.o \
		obj/Engine.o \
		obj/desktop.o

VGINCS = \
		-I/opt/vc/include \
		-I/opt/vc/include/interface/vmcs_host/linux \
		-I/opt/vc/include/interface/vcos/pthreads

VGLIBS = \
		-L/opt/vc/lib \
		-lbrcmEGL \
		-lbrcmGLESv2

LIBS =	-lshapes \
		-lm  \
		-lpng  \
		-ljpeg \
		-fpermissive `curl-config --libs` \
		-lstdc++ \
		-lfreetype \
		-lwiringPi \
		-lbcm_host \
		-lpthread

FLAGS = -std=c++11 

$(NAME): main.cpp $(OBJ) $(WOBJ)
	@g++ -o $@ $< $(OBJ) $(WOBJ) $(INCS) $(LIBS) $(VGINCS) $(VGLIBS) $(FLAGS)
	@echo -ne '\007'

obj/CFontStorage.o : CFontStorage.cpp CFontStorage.h lib/TFont/TFont.h
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/TFont.o : lib/TFont/TFont.cpp lib/TFont/TFont.h lib/TFont/ftf.h
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/ftf.o : lib/TFont/ftf.cpp lib/TFont/ftf.h
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/json.o : lib/json.cpp lib/json.h
	@g++ -c -o $@ $< $(FLAGS)

obj/Picture.o : lib/Picture.cpp lib/Picture.h
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/CPicturesStorage.o : CPicturesStorage.cpp CPicturesStorage.h lib/Picture.h
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/board.o : board.cpp board.h $(WHDRS) $(HDRS)
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/Engine.o : Engine.cpp Engine.h board.h $(HDRS)
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/Timer.o : Timer.cpp Timer.h
	@g++ -c -o $@ $< $(INCS) $(FLAGS)

obj/IWidget.o : widgets/IWidget.cpp widgets/IWidget.h
	@g++ -c -o $@ $< $(FLAGS)

obj/timetable.o : timetable.cpp timetable.h
	@g++ -c -o $@ $< $(FLAGS)

obj/desktop.o : desktop.cpp desktop.h
	@g++ -c -o $@ $< $(FLAGS)

obj/WgBackground.o : widgets/WgBackground.cpp widgets/WgBackground.h widgets/IWidget.h $(HDRS)
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/WgAds.o : widgets/WgAds.cpp widgets/WgAds.h widgets/WgBackground.h widgets/IWidget.h $(HDRS)
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/WgCalendar.o : widgets/WgCalendar.cpp widgets/WgCalendar.h widgets/WgBackground.h widgets/IWidget.h $(HDRS)
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/WgClock.o : widgets/WgClock.cpp widgets/WgClock.h widgets/WgBackground.h widgets/IWidget.h $(HDRS)
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/WgForecast.o : widgets/WgForecast.cpp widgets/WgForecast.h widgets/WgBackground.h widgets/IWidget.h $(HDRS)
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/WgSockets.o : widgets/WgSockets.cpp widgets/WgSockets.h widgets/IWidget.h $(HDRS)
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/WgTimetable.o : widgets/WgTimetable.cpp widgets/WgTimetable.h widgets/IWidget.h $(HDRS)
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

obj/WgWatchdog.o : widgets/WgWatchdog.cpp widgets/WgWatchdog.h widgets/IWidget.h $(HDRS)
	@g++ -c -o $@ $< $(INCS) $(VGINCS) $(FLAGS)

clean :
	@rm -rf $(NAME) obj/*.o

#test: test.cpp lib/Picture.h obj/Picture.o
test: test.cpp 
#	@g++ -o $@ $< obj/*.o $(VGINCS) $(VGLIBS) $(LIBS) $(FLAGS) -I/home/pi/openvg -lwiringPi
	@g++ -o $@ $(VGINCS) $(VGLIBS) $(LIBS) $(FLAGS)


INCLUDEFLAGS=-I/opt/vc/include -I/opt/vc/include/interface/vmcs_host/linux -I/opt/vc/include/interface/vcos/pthreads
LIBFLAGS=-L/opt/vc/lib -lbrcmGLESv2 -lbrcmEGL -lbcm_host -lpthread  -ljpeg

#VGINCS = \
		-I/opt/vc/include \
		-I/opt/vc/include/interface/vmcs_host/linux \
		-I/opt/vc/include/interface/vcos/pthreads \
		-I/home/pi/smartRTU2/openvg
#LIBS =	-lshapes \
		-lm  \
		-lpng  \
		-ljpeg \
		-fpermissive `curl-config --libs` \
		-lstdc++ \
		-lfreetype \
		-lwiringPi
#VGLIBS = \
		-L/opt/vc/lib \
		-lbrcmEGL \
		-lbrcmGLESv2

hellovg:	hellovg.c #openvg/libshapes.o openvg/oglinit.o
	g++ -Wall $(VGINCS) -o  hellovg hellovg.c  $(LIBS) $(VGLIBS) $(FLAGS) -lbcm_host -lpthread

hellovgcpp:	hellovg.cpp #openvg/libshapes.o openvg/oglinit.o
	g++ -Wall $(VGINCS) -o  hellovg hellovg.cpp  $(LIBS) $(VGLIBS) $(FLAGS) -lbcm_host -lpthread
