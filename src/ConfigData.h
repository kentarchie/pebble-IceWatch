typedef struct {
    int dataVersion;
    char * iceName;
    char * icePhone;
    char * myName;
    int iceBackgroundColor;
    int iceTextColor;
    int meBackgroundColor;
    int meTextColor;
    bool hourFormat;
    bool showBT;
    bool showBattery;
} ConfigData;

bool fetchConfiguration();
bool saveConfiguration();
bool convertConfiguration();
