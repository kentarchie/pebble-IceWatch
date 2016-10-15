typedef struct {
    int dataVersion;
    char * iceName;
    char * icePhone;
    char * myName;
    int iceBackgroundColor;
    int iceTextColor;
    int meBackgroundColor;
    int meTextColor;
    int hourFormat;
    bool showBT;
    bool showBattery;
} ConfigData;

void fetchConfiguration();
void saveConfiguration();
void loadConfiguration();
void logConfiguration();
void initializeConfiguration();
