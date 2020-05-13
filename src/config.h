//random config
#define  RES_DIR "../res"

//#define DEFAULT_TIMETABLE_FILE "res/timetable.json"
#define ADS_FILES_PATH "res/ads/" 
#define WEATHER_ICONS_PATH "res/pictures/weather/" 
#define BASE_FONT_PATH "res/fonts/"
#define BASE_SHADOWS_PATH "res/pictures/shadows/"

//~~~~~~CutyCapt Requests
//RUN_XVFB_SERVER +(INPUT_FILE_DEST+/+INPUT_FILE) +${cutycapt --output-} + (OUTPUT_FILE_DEST +/+OUTPUT_FILE) = html.page transofrmation into png image
//btw realpath returns full path to exe 
#define RUN_XVFB_SERVER "xvfb-run --server-args=\"-screen 0, 1920x1080x24\""
#define INPUT_FILE_DEST "res/tmp/HtmlAd"
#define INPUT_FILE "HtmlAd.html"
//destination from exe file
#define OUTPUT_FILE_DEST "res/tmp"
#define OUTPUT_FILE "temp.png"

//

#define DEFAULT_PIC_PATH "res/pictures/"

#define FONT_PATH(FONT_NAME) ((std::string(BASE_FONT_PATH) + FONT_NAME).c_str())
#define SHADOW_PATH(SHADOW_NAME) ((std::string(BASE_SHADOWS_PATH)+SHADOW_NAME).c_str())

#define PIC_PATH(PIC_NAME) ((std::string(DEFAULT_PIC_PATH) + PIC_NAME).c_str())

//"resources/weather/"