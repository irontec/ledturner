#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/types.h>
#include <termios.h>
#include <signal.h>

void handler (int sig)
{
    printf ("Exiting...(%d)n", sig);
    exit (0);
}


void perror_exit (char *error)
{
    perror(error);
    handler (9);
}

void usage()
{
        printf("LEDTURNER\n");
        printf("\tTurns on|off keyboards LEDs writing directly to device.\n\n");
        printf("USAGE:\n");
        printf("\t./ledturner --input /dev/input/event* [OPTIONS]\n\n");
        printf("OPTIONS:\n");
        printf("\t--num, -n [0|1]    Turn OFF (0) , ON (1) Num Lock LED\n");
        printf("\t--caps, -c [0|1]   Turn OFF (0) , ON (1) Caps Lock LED\n");
        printf("\t--scroll, -s [0|1] Turn OFF (0) , ON (1) Scroll Lock LED\n");
        printf("\n");

}

void processValue(int candidateValue, int *holder)
{
    if (candidateValue == 1 || candidateValue == 0) {
        *holder = candidateValue;
    }
}

void makeEvent(struct input_event* event, int led, int action)
{

    event->type = EV_LED;
    if (action == 1) {
        // Turn LED on
        event->value = MSC_PULSELED;
    } else {
        // Turn LED off
        event->value = !MSC_PULSELED;
    }
    event->code = led;

}


int main (int argc, char *argv[])
{

    char *device = NULL;

    int fd;

    int c;

    struct input_event event;

    int num = -1;
    int caps = -1;
    int scroll = -1;

    int tempValue;

    const struct option long_opts[] = {
      { "input", required_argument, NULL, 'i' },
      { "num", required_argument, NULL, 'n' },
      { "caps" , required_argument, NULL, 'c' },
      { "scroll"  , required_argument, NULL, 's' },
      { NULL, 0, NULL, 0 }
    };


    while ( (c = getopt_long(argc, argv, "i:n:c:s:", long_opts, NULL)) != EOF) {
        switch (c) {
            case 'i':
                device = optarg;
                break;
            case 'n':

                processValue(atoi(optarg),&num);
                break;
            case 'c':
                processValue(atoi(optarg),&caps);
                break;
		    case 's':
                processValue(atoi(optarg),&scroll);
                break;
            case '?':
                usage();
                return 0;

        }
    }


    if (device == NULL) {
        perror_exit("Not a valid input event device found");
    }

    if ((fd = open (device, O_RDWR | O_NONBLOCK)) == -1) {
        perror_exit("Unable to open input event device");
    }


    if (num != -1) {
        makeEvent(&event, LED_NUML, num);
        write(fd, &event, sizeof(struct input_event));
    }


    if (caps != -1) {
        makeEvent(&event, LED_CAPSL, caps);
        write(fd, &event, sizeof(struct input_event));
    }


    if (scroll != -1) {
        makeEvent(&event, LED_SCROLLL, scroll);
        write(fd, &event, sizeof(struct input_event));
    }


    return 0;

}



