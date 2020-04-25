//random config
#define  RES_DIR "../res"

#define DEFAULT_TIMETABLE_FILE "res/timetable.json"
#define ADS_FILES_PATH "res/ads/" 
#define WEATHER_ICONS_PATH "res/pictures/weather/" 
#define BASE_FONT_PATH "res/fonts/"
#define BASE_SHADOWS_PATH "res/pictures/shadows/"

#define CUTYCAPT_REQUEST "xvfb-run --server-args=\"-screen 0, 1920x1080x24\" cutycapt --url=file:/home/pi/Desktop/Projects/SmartRTU/res/tmp/temp.html --out=/home/pi/Desktop/Projects/SmartRTU/res/tmp/temp.png --min-width=1920 --min-height=1080"

#define DEFAULT_PIC_PATH "res/pictures/"

#define FONT_PATH(FONT_NAME) ((std::string(BASE_FONT_PATH) + FONT_NAME).c_str())
#define SHADOW_PATH(SHADOW_NAME) ((std::string(BASE_SHADOWS_PATH)+SHADOW_NAME).c_str())

#define PIC_PATH(PIC_NAME) ((std::string(DEFAULT_PIC_PATH) + PIC_NAME).c_str())

//"resources/weather/"