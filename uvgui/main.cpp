#include "uv_gui.h"
int main (int argc, char *argv[])
{
    uv_window test (800, 600);
    uv_window sef (456, 243, 300, 300, &test);
    uv_window ssef (130, 50, 0, 0, &sef);
    run ();

    return 0;
};
