#include "application.h"
#include "sdl2.h"
#include <stdio.h>

int main() {
    struct Application *application = Application_initialize();
    if (application != NULL) {
        Application_run(application);
    } else {
        fprintf(stderr, "Failed to initialize the application...");
        return -1;
    }
    Application_shutDown(application);
}
