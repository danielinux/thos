#ifdef PICOTCP
#include <pico_stack.h>
#include "thos.h"
#include "hw.h" /* For HZ */

static int picotcp_init(void *unused)
{
    return pico_stack_init();
}

static void *picotcp_tick(void *arg)
{
    pico_stack_tick();
    return NULL;
}


static struct thos_task __task t_tcpip = {
	.name = "picoTCP", .period = HZ/200,
	.job = picotcp_tick,
	.init = picotcp_init,
	.release = 5
};

#endif
