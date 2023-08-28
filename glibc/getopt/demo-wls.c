#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>


#define TRUE 1
#define FALSE 0

typedef struct tagAPP_PARAMS
{
	char *wls_dev_name;
	int  aff_core;
	int  test_id;
	int  rx_id;
	int  tx_id;
	int  n_messages;
	int  max_size;
	int  min_size;
	int  interface_count;
	char   master;
	char   debug;
	char   crc;
	char   trusted;
} APP_PARAMS, *PAPP_PARAMS;

void app_Help(void)
{
	char help_content[] =  \
			"WLS test application\n\n"\
			"Usage: testapp [-c <test>] [-r <rxid>] [-t <txid>] [-n <msgcount>]\n\n"\
			"supports the following parameters:\n\n"
			"-c | --testcase <test number>     0 - default sanity test\n"\
			"                                  1 - misaligned pointers test\n"\
			"                                  2 - aligned 4 pointers test\n"\
			"                                  3 - random pools test\n"\
			"                                  4 - ping-pong (ZBC test)\n"\
			"                                  5 - invalid messages test\n\n"\
			"--trusted                    switches WLS  to trusted mode\n"\
			"-r | --rxid <id>             used to specify RxTypeID\n"\
			"-t | --txid <id>             used to specify TxTypeID\n"\
			"-n | --msgcount <count>      used to specify number of messages per timeframe\n"\
			"-l | --minsize  <size>       specifies MIN message size in bytes\n"\
			"-s | --maxsize  <size>       specifies MAX message size in bytes\n"\
			"--crc                        enables CRC generation and checking\n"\
			"--debug                      increases sleep interval to 1 second\n"\
			"-m | --master                set predefined rxid and txid\n";

	printf("%s", help_content);
}

int app_ParseArgs(int argc, char ** argv, PAPP_PARAMS params)
{
	int c;
	int *pInt;
	int cnt = 0;

	struct option long_options[] = {
		{"wlsdev",   required_argument, 0,  'w' },
		{"affinity", required_argument, 0,  'a' },
		{"testcase", required_argument, 0,  'c' },
		{"rxid",     required_argument, 0,  'r' },
		{"txid",     required_argument, 0,  't' },
		{"msgcount", required_argument, 0,  'n' },
		{"maxsize",  required_argument, 0,  's' },
		{"minsize",  required_argument, 0,  'l' },
		{"master",   no_argument,       0,  'm' },
		{"debug",    no_argument,       0,  'd' }, /* slow down the app cycle from 1ms to 1s*/
		{"icount",   required_argument, 0,  'i' },
		{"crc",      no_argument,       0,  1 },
		{"trusted",  no_argument,       0,  2 },
		{"help",     no_argument,       0,  'h' },
		{0,          0,                 0,  0 }
	};

	memset(params, 0, sizeof (*params));

	/* set default values here */
	params->interface_count = 1;

	while (1) {
		/* int this_option_optind = optind ? optind : 1; */
		int option_index = 0;

		c = getopt_long(argc, argv, "a:w:c:r:t:n:s:l:mdi:h", long_options, &option_index);

		if (c == -1)
			break;

		cnt += 1;
		pInt = NULL;

		switch (c) {
			case 'a': // test Case selection
				pInt = &params->aff_core;
				break;
			case 'c': // test Case selection
				pInt = &params->test_id;
				break;
			case 'r': // rx id selection
				pInt = &params->rx_id;
				break;
			case 't': // tx id selection
				pInt = &params->tx_id;
				break;
			case 's': // select message size
				pInt = &params->max_size;
				break;
			case 'l': // select message size
				pInt = &params->min_size;
				break;
			case 'n': // select number of messages
				pInt = &params->n_messages;
				break;
			case 'i': // select number of interfaces to register
				pInt = &params->interface_count;
				break;
			case 'm':
				params->master = TRUE;
				break;
			case 'd':
				params->debug = TRUE;
				break;
			case 'w':
				params->wls_dev_name = optarg;
				break;
			case 'h':
				app_Help();
				exit(0);
			case 2:
				params->trusted = TRUE;
				break;
			case 1: // crc checking enabled
				params->crc = TRUE;
				break;
		}

		if (pInt && optarg) {
			// get int arg
			if (optarg[0]=='0' && (optarg[1]=='x'||optarg[1]=='X')) {
				sscanf(optarg, "%x", (unsigned *)pInt);
			} else {
				*pInt = atoi(optarg);
			}
		}
	}
	return cnt;
}


int main(int argc, char *argv[])
{
	APP_PARAMS params;
	app_ParseArgs(argc, argv, &params);

#if 1
	printf("wls_dev_name=%s\n", params.wls_dev_name);
	printf("aff_core=%d\n", params.aff_core);
	printf("test_id=%d\n", params.test_id);
	printf("rx_id=%d\n", params.rx_id);
	printf("tx_id=%d\n", params.tx_id);
	printf("n_messages=%d\n", params.n_messages);
	printf("max_size=%d\n", params.max_size);
	printf("min_size=%d\n", params.min_size);
	printf("interface_count=%d\n", params.interface_count);
	printf("master=%d\n", params.master);
	printf("debug=%d\n", params.debug);
	printf("crc=%d\n", params.crc);
	printf("trusted=%d\n", params.trusted);
#endif

	return 0;
}