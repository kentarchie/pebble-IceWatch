typedef struct Layer {
	char * name;
	char * type;
	void * layer;
	int xpos;
	int ypos;
	int width;
	int height;
	char * currentText;
	char * defaultText;
	int backgroundColor;
	int textColor;
	GBitmap * currentImage;
	GBitmap * defaultImage;
	char * font;
	GTextAlignment align;
} Layer;
