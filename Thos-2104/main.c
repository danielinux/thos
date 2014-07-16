#include "thos.h"
#include "hw.h"

int thos_main(void)
{
	struct thos_task *p;
	unsigned long now;

	thos_puts("The mighty Thos is alive\n");

	for (p = __task_begin; p < __task_end; p++) {
		thos_puts("Task: "); thos_puts(p->name); thos_putc('\n');
		if (p->init) p->init(p->arg);
	}

	now = jiffies;
	for (p = __task_begin; p < __task_end; p++)
		p->release += now + 2;

	while (1) {
		struct thos_task *t;

		for (t = p = __task_begin; p < __task_end; p++)
			if (p->release < t->release)
				t = p;
		while ((signed)(t->release - jiffies) > 0)
			;
		t->arg = t->job(t->arg);
		t->release += t->period;
	}
}
