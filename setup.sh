#! /bin/sh
(cd config; gvim -p index.html js/config.js css/config.css ../src/js/app.js ../src/js/defs.js ../src/js/loader.js ../src/js/main.js ../src/js/safe.js ../wscript ../appinfo.json ../README.md)
(cd src; gvim -p IceWatch.c SetupDisplay.c Actions.c Utilities.c ConfigData.c ConfigData.h Constants.h Global.h Actions.h SetupDisplay.h Utilities.h Layers.h)
