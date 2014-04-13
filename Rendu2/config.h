//
//  config.h
//  Bubbles
//

#ifndef Bubbles_config_h
#define Bubbles_config_h

// utilities
#define str(x)	# x
#define xstr(x) str(x)
#define error(msg) fprintf(stderr,\
						"ERROR: "msg" f.%s l.%d\n", __FILE__, __LINE__);

// windows
#define WINDOW_WIDTH  600
#define WINDOW_HEIGHT 600
#define WINDOW_TITLE "Bubbles"

// disk
#define DISK_RESOLUTION 100
#define DISK_BORDER_WEIGHT 0.5

// forced
#define MAX_PLAYER 2
#define MAX_VAL 10
#define MIN_RADIUS 1.414213562
#define MAX_PSEUDO 8
#define MAX_ENERGY 200
#define MAX_TOUR 20
#define MAX_TIME 10
#define MAX_MODELE 100

// DEBUG
#define PDEBUG true

#endif
