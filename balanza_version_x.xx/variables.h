const int LOADCELL_DOUT_PIN = 12;
const int LOADCELL_SCK_PIN = 13;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

float h;
float t;
float f;
float lectura_balanza;
float factor_palanca = 5.25;

int factor_scale = 54700;

String pagina = "index";
String header;
