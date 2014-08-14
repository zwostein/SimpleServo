#define _BSD_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <argp.h>

#include <pigpio.h>


static char doc[] = "Simple tool to control servos connected to the Raspberry PI's GPIO.";


static struct argp_option options[] =
{
	{ "pin",      'p', "Pin name",   0, "Interact with servo on this GPIO. For example 25 for GPIO25. See http://elinux.org/RPi_Low-level_peripherals#General_Purpose_Input.2FOutput_.28GPIO.29 for more information." },
	{ "value",    'v', "Value in ms", 0, "Set servo to this value. Usually between 1000 and 2000. This is the pulse length in milliseconds sent to the servo." },
	{ "holdtime", 'h', "Hold time in ms", 0, "Hold servo in this position for the given time in milliseconds, then release servo and exit." },
	{ 0 }
};


struct arguments
{
	unsigned int pin;
	unsigned int value;
	unsigned int holdTime;
};


static error_t parser( int key, char * arg, struct argp_state * state )
{
	struct arguments * arguments = state->input;

	switch( key )
	{
	case 'p':
		arguments->pin = atoi( arg );
		break;
	case 'v':
		arguments->value = atoi( arg );
		break;
	case 'h':
		arguments->holdTime = atoi( arg );
		break;
	case ARGP_KEY_END:
		if( arguments->pin == 0 )
			argp_failure( state, 1, 0, "No GPIO pin number given!" );
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	}
	return 0;
}


static struct argp argp = { options, parser, NULL, doc };


int main( int argc, char ** argv )
{
	struct arguments arguments = {0};
	arguments.holdTime = 500;

	argp_parse( &argp, argc, argv, 0, 0, &arguments );

	printf( "Setting servo on GPIO %d to %d for %d milliseconds.\n", arguments.pin, arguments.value, arguments.holdTime );

	if( gpioInitialise() < 0 )
	{
		fprintf( stderr, "Failed to initialise pigpio!\n" );
		return 1;
	}

	gpioServo( arguments.pin, arguments.value );
	usleep( arguments.holdTime * 1000 );

	gpioTerminate();

	return 0;
}
