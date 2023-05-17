#define __STDC_LIMIT_MACROS
#define __STDC_FORMAT_MACROS
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <inttypes.h>
#include <argp.h>

#define barrier() asm volatile ("" : : : "memory")
#define mb() asm volatile ("mfence" : : : "memory")
#define cacheline_aligned __attribute__((aligned(128)))
#define ACCESS_ONCE(x) (*(volatile typeof(x)*)&x)

#define MAX_THREADS 4
int cpus[4] = {-1, -1, -1, -1};
typedef uint64_t Time;

int verbosity = 0;
bool tests_specified = false;
bool run_now_test, run_load_test, run_store_test, run_load3_test;
enum ClockType { RDTSC_DEFAULT, RDTSC, RDTSCP, LFENCE_RDTSC, MFENCE_RDTSC, MONOTONIC };
ClockType clocktype = RDTSC_DEFAULT;

static char doc[] = "Evil clock test -- a program that tries to make the clock fail";

static struct argp_option options[] = {
  {"clock", 'c', "clock-type", 0, "Clock to use"},
  {"cpus", 'p', "cpu-list", 0, "CPUs to use (comma-separated)"},
  {"verbose", 'v', 0, 0, "Increase verbosity"},
  {"now-test", 'N', 0, 0, "Run now test"},
  {"load-3-test", '3', 0, 0, "Run load-3 test (needs three CPUs)"},
  {"store-order-test", 'S', 0, 0, "Run store order test"},
  {"load-order-test", 'L', 0, 0, "Run load order test"},
  {0}
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
  switch(key) {
  case 'v':
    verbosity++;
    break;

  case ARGP_KEY_ARG:
    return ARGP_ERR_UNKNOWN;

  case 'p':
    {
      char *arg_copy = strdup(arg);
      int i = 0;
      while(const char *c = strsep(&arg_copy, ","))
	{
	  if (i >= MAX_THREADS)
	    argp_error(state, "too many cpu entries");

	  char *end;
	  int val = strtol(c, &end, 10);
	  if (*end)
	    argp_error(state, "bogus cpu entry");

	  if (val < 0 || val >= CPU_SETSIZE)
	    argp_error(state, "bad cpu number");
	  
	  cpus[i++] = val;
	}
      free(arg_copy);
    }
    break;

  case 'N':
    tests_specified = true;
    run_now_test = true;
    break;

  case 'L':
    tests_specified = true;
    run_load_test = true;
    break;

  case 'S':
    tests_specified = true;
    run_store_test = true;
    break;

  case '3':
    tests_specified = true;
    run_load3_test = true;
    break;

  case 'c':
    if (!strcmp(arg, "rdtsc_default")) {
      clocktype = RDTSC_DEFAULT;
    } else if (!strcmp(arg, "rdtsc")) {
      clocktype = RDTSC;
    } else if (!strcmp(arg, "rdtscp")) {
      clocktype = RDTSCP;
    } else if (!strcmp(arg, "lfence_rdtsc")) {
      clocktype = LFENCE_RDTSC;
    } else if (!strcmp(arg, "mfence_rdtsc")) {
      clocktype = MFENCE_RDTSC;
    } else if (!strcmp(arg, "monotonic")) {
      clocktype = MONOTONIC;
    } else {
      fprintf(stderr, "Unknown clock type.  Choices are:\n"
	      " rdtsc_default: RDTSC (autodetected for your CPU)\n"
	      " rdtsc:         RDTSC (no barrier)\n"
	      " rdtscp:        RDTSCP\n"
	      " lfence_rdtsc:  LFENCE;RDTSC\n"
	      " mfence_rdtsc:  MFENCE;RDTSC\n"
	      " monotonic:     clock_gettime(CLOCK_MONOTONIC)\n"
	      "\n");
      argp_usage(state);
    }
    break;

  default:
    return ARGP_ERR_UNKNOWN;
  }

  return 0;
}

static struct argp argp = { options, parse_opt, 0, doc };

static inline Time rdtsc_strict()
{
  // This version is ordered wrt previous stores.
  Time ret;
  asm volatile ("mfence\n\t"
		"rdtsc\n\t"
		"shl $0x20,%%rdx\n\t"
		"or %%rdx,%%rax"
		: "=a" (ret) : : "cc", "rdx", "memory");
  return ret;
}

template<int clocktype>
struct Clock;

template<>
struct Clock<(int)RDTSC>
{
  static inline Time read()
  {
    Time ret;
    asm volatile ("rdtsc\n\t"
		  "shl $0x20,%%rdx\n\t"
		  "or %%rdx,%%rax"
		  : "=a" (ret) : : "cc", "rdx", "memory");
    return ret;
  }

  static inline Time read_strict()
  {
    return rdtsc_strict();
  }

  enum { is_strict = 0 };
  static const char *name() { return "rdtsc"; }
};

template<>
struct Clock<(int)RDTSCP>
{
  static inline Time read()
  {
    Time ret;
    asm volatile ("rdtscp\n\t"
		  "shl $0x20,%%rdx\n\t"
		  "or %%rdx,%%rax"
		  : "=a" (ret) : : "cc", "rdx", "rcx", "memory");
    return ret;
  }

  static inline Time read_strict()
  {
    return rdtsc_strict();
  }

  enum { is_strict = 0 };
  static const char *name() { return "rdtscp"; }
};

template<>
struct Clock<(int)LFENCE_RDTSC>
{
  static inline Time read()
  {
    Time ret;
    asm volatile ("lfence\n\t"
		  "rdtsc\n\t"
		  "shl $0x20,%%rdx\n\t"
		  "or %%rdx,%%rax"
		  : "=a" (ret) : : "cc", "rdx", "memory");
    return ret;
  }

  static inline Time read_strict()
  {
    return rdtsc_strict();
  }

  enum { is_strict = 0 };
  static const char *name() { return "lfence;rdtsc"; }
};

template<>
struct Clock<(int)MFENCE_RDTSC>
{
  static inline Time read()
  {
    Time ret;
    asm volatile ("mfence\n\t"
		  "rdtsc\n\t"
		  "shl $0x20,%%rdx\n\t"
		  "or %%rdx,%%rax"
		  : "=a" (ret) : : "cc", "rdx", "memory");
    return ret;
  }

  static inline Time read_strict()
  {
    return rdtsc_strict();
  }

  enum { is_strict = 1 };
  static const char *name() { return "mfence;rdtsc"; }
};

template<>
struct Clock<(int)MONOTONIC>
{
  static inline Time read()
  {
    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return (uint64_t)t.tv_sec * 1000000000ULL + (uint64_t)t.tv_nsec;
  }

  static inline Time read_strict()
  {
    mb();
    return read();
  }

  enum { is_strict = 0 };
  static const char *name() { return "CLOCK_MONOTONIC"; }
};

class TestScorer
{
public:
  TestScorer() : nsamples(0), worst_error(INT64_MIN), nfailures(0) {}

  // Asserts that the first timestamp is <= the second.
  void Compare(int thread1, Time t1, int thread2, Time t2)
  {
    int64_t error = (int64_t)(t1 - t2);  // Negative is good.
    if (error > worst_error)
      worst_error = error;

    if (error > 0)
      nfailures++;
  }

  // Verify that nonzero entries in times1 prior to nonzero entries
  // in times2 have lower or equal values.
  void CompareArrays(int len,
		     int thread1, Time *times1,
		     int thread2, Time *times2)
  {
    Time t1max = 0, t2max = 0;
    bool t1fresh = false;
    for(int i = 0; i < len; i++)
      {
	// Consume one entry from times2
	if (times2[i]) {
	  if (times2[i] < t2max) {
	    printf("  ERROR!  Time2 went back by %" PRIu64 "\n",
		   t2max - times2[i]);
	    worst_error = INT64_MAX;
	  } else {
	    t2max = times2[i];
	  }

	  // Check state
	  if (t1max && t2max && t1fresh) {
	    t1fresh = false;
	    nsamples++;
	    Compare(thread1, t1max, thread2, t2max);
	  }
	}

	// Consume one entry from times1
	if (times1[i]) {
	  if (times1[i] < t1max) {
	    printf("  ERROR!  Time1 went back by %" PRIu64 "\n",
		   t1max - times1[i]);
	    worst_error = INT64_MAX;
	  } else {
	    t1max = times1[i];
	    t1fresh = true;
	  }
	}
      }
  }

  void Print()
  {
    if (nsamples == 0)
      printf("  No data!\n");
    else if (worst_error <= 0)
      printf("  Passed with margin %" PRIi64 " (%" PRIu64 " samples)\n",
	     -worst_error, nsamples);
    else
      printf("  Failed %" PRIu64 "/%" PRIu64 " times with worst error %" PRIi64 "\n",
	     nfailures, nsamples, worst_error);
  }

  uint64_t nsamples;
  int64_t worst_error;

private:
  uint64_t nfailures;
};

class SequenceTest
{
public:
  typedef void (SequenceTest::*ThreadProc)(int);
  unsigned long cacheline_aligned seq;
  volatile bool cacheline_aligned end;

  uint64_t nsamples;
  int64_t worst_error;

  void Stop()
  {
    end = true;
    for(int i = 0; i < nthreads; i++)
      {
	void *retval;
	if (pthread_join(threads[i], &retval) != 0)
	  abort();
      }
  }

  SequenceTest() : seq(1), end(false), nsamples(0), worst_error(INT64_MIN + 1)
  {
    next_start = 0;
    nthreads = 0;
    memset(finished, 0, sizeof(finished));
    memset(last_start, 0, sizeof(last_start));
  }

private:
  struct cacheline_aligned {
    unsigned long next_start;
    int nthreads;
    unsigned long finished[MAX_THREADS];
    unsigned long last_start[MAX_THREADS];
    pthread_t threads[MAX_THREADS];
  };

  int cacheline_aligned padding;

  struct ThreadProcInfo
  {
    SequenceTest *test;
    int threadidx;
    ThreadProc proc;
  };
  static void *RealThreadProc(void *info)
  {
    ThreadProcInfo tpi = *(ThreadProcInfo*)info;
    delete (ThreadProcInfo*)info;
    (tpi.test->*tpi.proc)(tpi.threadidx);
    return 0;
  }

protected:
  void StartThread(ThreadProc proc)
  {
    if (nthreads >= MAX_THREADS)
      abort();

    ThreadProcInfo *info = new ThreadProcInfo;
    info->test = this;
    info->proc = proc;
    info->threadidx = nthreads;

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    if (cpus[nthreads] != -1) {
      cpu_set_t cpuset;
      CPU_ZERO(&cpuset);
      CPU_SET(cpus[nthreads], &cpuset);
      pthread_attr_setaffinity_np(&attr, sizeof(cpuset), &cpuset);
    }

    if (pthread_create(&threads[nthreads], &attr, RealThreadProc, info) != 0) {
      printf("Failed to start thread\n");
      exit(1);
    }

    pthread_attr_destroy(&attr);

    nthreads++;
  }

  unsigned long WaitForStartSignal(int threadidx)
  {
    unsigned long ret;

    // Wait until the start trigger is set.
    while(ACCESS_ONCE(next_start) == last_start[threadidx] && !end)
      ;

    // And wait for the start signal.
    do {
      ret = ACCESS_ONCE(next_start);
    } while (ACCESS_ONCE(seq) < ret && !end);

    last_start[threadidx] = ret;

    barrier();
    return ret;
  }

  void MarkDone(int threadidx)
  {
    ACCESS_ONCE(finished[threadidx]) = last_start[threadidx];
  }

  unsigned long SendStartSignal()
  {
    ACCESS_ONCE(next_start) = ACCESS_ONCE(seq);
    return next_start;
  }

  bool thread_done(int threadidx)
  {
    return ACCESS_ONCE(finished[threadidx]) == next_start;
  }
};

/* Now test */

template<typename ClockType>
class NowTest : public SequenceTest
{
public:
  void Start()
  {
    StartThread((ThreadProc)&NowTest::WriterThread);
    StartThread((ThreadProc)&NowTest::ReaderThread);
  }

private:
  volatile Time cacheline_aligned now;

  void WriterThread(int threadidx)
  {
    while(!end) {
      now = ClockType::read();
      now = ClockType::read();
      now = ClockType::read();
      now = ClockType::read();
      now = ClockType::read();
      now = ClockType::read();
      now = ClockType::read();
      now = ClockType::read();
      nsamples += 8;  // Very approximate
    }
  }

  void ReaderThread(int threadidx)
  {
    while(!end)
      {
	Time other_now = now;
	barrier();
	Time my_now = ClockType::read();

	int64_t error = (int64_t)(other_now - my_now);
	if (error > worst_error)
	  worst_error = error;
      }
  }
};

/* Subsequent load test */

template<typename ClockType>
class Load3Test : public SequenceTest
{
public:
  void Start()
  {
    StartThread((ThreadProc)&Load3Test::LoadBeforeClock);
    StartThread((ThreadProc)&Load3Test::LoadAfterClock);
    StartThread((ThreadProc)&Load3Test::WriterThread);
  }

private:
  enum { results_len = 1048576 };
  Time results_1[results_len], results_2[results_len];

  void WriterThread(int threadidx)
  {
    unsigned long my_seq = 1;
    while(!end)
      {
	/* Clear the initial state */
	memset(results_1, 0, sizeof(results_1));
	memset(results_2, 0, sizeof(results_2));

	/* Start a new run */
	SendStartSignal();

	/* Run until finished */
	while(!end && (!thread_done(0) || !thread_done(1)))
	  {
	    ACCESS_ONCE(seq) = ++my_seq;
	  }

	if (end)
	  return;
	    
	TestScorer checker;
	checker.CompareArrays(results_len, 2, results_2, 1, results_1);
	if (verbosity >= 2)
	  checker.Print();

	nsamples += checker.nsamples;
	if (checker.worst_error > worst_error)
	  worst_error = checker.worst_error;
      }
  }

  void LoadBeforeClock(int threadidx)
  {
    while(true)
      {
	unsigned long start = WaitForStartSignal(threadidx);
	if (end)
	  return;

	/* Go! */
	while(!end) {
	  unsigned long seqval = ACCESS_ONCE(seq);
	  unsigned long clock = ClockType::read();

	  unsigned long idx = seqval - start;
	  if (idx >= results_len)
	    break;

	  results_1[idx] = clock;
	}

	MarkDone(threadidx);
      }
  }

  void LoadAfterClock(int threadidx)
  {
    while(true)
      {
	unsigned long start = WaitForStartSignal(threadidx);
	if (end)
	  return;

	/* Go! */
	while(!end) {
	  unsigned long clock = ClockType::read();
	  unsigned long seqval = ACCESS_ONCE(seq);

	  unsigned long idx = seqval - start;
	  if (idx >= results_len)
	    break;

	  results_2[idx] = clock;
	}

	MarkDone(threadidx);
      }
  }
};

/* Prior store test and load order test */

template<typename ClockType, int is_load>
class LoadStoreTest : public SequenceTest
{
public:
  void Start()
  {
    StartThread((ThreadProc)&LoadStoreTest::WriterThread);
    StartThread((ThreadProc)&LoadStoreTest::ReaderThread);
  }

private:
  template<typename ClockType_, int is_load_>
  struct read_for_store;
  template<typename ClockType_>
  struct read_for_store<ClockType_, 0>
  {
    static inline Time read() { return ClockType::read(); }
  };
  template<typename ClockType_>
  struct read_for_store<ClockType_, 1>
  {
    static inline Time read() { return ClockType::read_strict(); }
  };
  
  enum { results_len = 1048576 };
  uint64_t results_1[results_len], results_2[results_len];

  void WriterThread(int threadidx)
  {
    unsigned long my_seq = 1;

    while(!end)
      {
	/* Clear the initial state */
	memset(results_1, 0, sizeof(results_1));
	memset(results_2, 0, sizeof(results_2));

	/* Start a new run */
	unsigned long start = SendStartSignal();

	/* Run until finished */
	while(my_seq - start < results_len)
	  {
	    unsigned long idx, time;
	    ACCESS_ONCE(seq) = ++my_seq;
	    time = read_for_store<ClockType, is_load>::read();

	    idx = my_seq - start;
	    results_2[idx] = time;
	  }

	/* Wait for other thread */
	while(!thread_done(1) && !end)
	  ACCESS_ONCE(seq) = ++my_seq;

	if (end)
	  return;
	    
	TestScorer checker;
	checker.CompareArrays(results_len, 1, results_1, 2, results_2);
	if (verbosity >= 2)
	  checker.Print();

	nsamples += checker.nsamples;
	if (checker.worst_error > worst_error)
	  worst_error = checker.worst_error;
      }
  }

  void ReaderThread(int threadidx)
  {
    while(!end)
      {
	unsigned long start = WaitForStartSignal(threadidx);
	if (end)
	  return;

	/* Go! */
	while(!end) {
	  unsigned long clock = ClockType::read();
	  unsigned long seqval = ACCESS_ONCE(seq);

	  unsigned long idx = seqval - start;
	  if (idx >= results_len)
	    break;

	  results_1[idx] = clock;
	}

	MarkDone(threadidx);
      }
  }
};

/* End of tests */

template<typename ClockType>
static void run()
{
  printf("Will test the \"%s\" clock.\n", ClockType::name());

  if (run_now_test) {
    if (verbosity >= 1)
      printf("Running now test...\n");

    NowTest<ClockType> *t = new NowTest<ClockType>;
    t->Start();
    usleep(1000000);
    t->Stop();

    if (t->nsamples == 0)
      printf("Now test got no data\n");
    else if (t->worst_error > 0)
      printf("Now test failed  : worst error %" PRIi64 " with %" PRIu64 " samples\n",
	     t->worst_error, t->nsamples);
    else
      printf("Now test passed  : margin %" PRIi64 " with %" PRIu64 " samples\n",
	     -t->worst_error, t->nsamples);

    delete t;
  }

  if (run_load3_test) {
    if (verbosity >= 1)
      printf("Running load3 test...\n");

    Load3Test<ClockType> *t = new Load3Test<ClockType>;
    t->Start();
    usleep(1000000);
    t->Stop();

    if (t->nsamples == 0)
      printf("Load3 test got no data\n");
    else if (t->worst_error > 0)
      printf("Load3 test failed: worst error %" PRIi64 " with %" PRIu64 " samples\n",
	     t->worst_error, t->nsamples);
    else
      printf("Load3 test passed: margin %" PRIi64 " with %" PRIu64 " samples\n",
	     -t->worst_error, t->nsamples);

    delete t;
  }

  if (run_load_test) {
    if (verbosity >= 1)
      printf("Running load test...\n");

    LoadStoreTest<ClockType, 1> *t = new LoadStoreTest<ClockType, 1>;
    t->Start();
    usleep(1000000);
    t->Stop();

    if (t->nsamples == 0) {
      printf("Load test got no data\n");
    } else if (t->worst_error > 0) {
      printf("Load test failed : worst error %" PRIi64 " with %" PRIu64 " samples\n",
	     t->worst_error, t->nsamples);
    } else {
      printf("Load test passed : margin %" PRIi64 " with %" PRIu64 " samples\n",
	     -t->worst_error, t->nsamples);
    }

    delete t;
  }

  if (run_store_test) {
    if (verbosity >= 1)
      printf("Running store test...\n");

    LoadStoreTest<ClockType, 0> *t = new LoadStoreTest<ClockType, 0>;
    t->Start();
    usleep(1000000);
    t->Stop();

    if (t->nsamples == 0) {
      printf("Store test got no data\n");
    } else if (t->worst_error > 0) {
      printf("Store test failed%s: worst error %" PRIi64 " with %" PRIu64 " samples\n",
	     ClockType::is_strict ? "" : " as expected",
	     t->worst_error, t->nsamples);
    } else {
      printf("Store test passed: margin %" PRIi64 " with %" PRIu64 " samples\n",
	     -t->worst_error, t->nsamples);
    }

    delete t;
  }
}

static void parse_cpuinfo()
{
  FILE *f = fopen("/proc/cpuinfo", "r");
  if (!f) {
    perror("/proc/cpuinfo");
    exit(1);
  }

  char vendor[4096] = "", model_name[4096] = "", stepping[4096] = "", flags[4096] = "";

  char buf[4096];
  while(fgets(buf, sizeof(buf), f)) {
    if (!*buf)
      break;  // Done with first cpu

    char name[4096], val[4096];
    if (sscanf(buf, "%[^\t:]\t: %[^\n]", name, val) != 2)
      continue;

    if (!strcmp(name, "vendor_id")) {
      strncpy(vendor, val, sizeof(vendor));
      vendor[sizeof(vendor)-1] = 0;
    }

    if (!strcmp(name, "model name")) {
      strncpy(model_name, val, sizeof(model_name));
      vendor[sizeof(model_name)-1] = 0;
    }

    if (!strcmp(name, "stepping")) {
      strncpy(stepping, val, sizeof(stepping));
      vendor[sizeof(stepping)-1] = 0;
    }

    if (!strcmp(name, "flags")) {
      strncpy(flags, val, sizeof(flags));
      vendor[sizeof(flags)-1] = 0;
    }
  }

  fclose(f);

  if (!*vendor || !*flags) {
    fprintf(stderr, "Couldn't find required info in cpuinfo\n");
    exit(1);
  }

  printf("CPU vendor   : %s\n"
	 "CPU model    : %s\n"
	 "CPU stepping : %s\n",
	 vendor, model_name, stepping);

  char *flagsp = flags;
  printf("TSC flags    :");
  while(const char *f = strsep(&flagsp, " ")) {
    if (strstr(f, "tsc"))
      printf(" %s", f);
  }
  printf("\n");

  if (clocktype == RDTSC_DEFAULT) {
    if (!strcmp(vendor, "GenuineIntel")) {
      printf("Using lfence_rdtsc because you have an Intel CPU\n");
      clocktype = LFENCE_RDTSC;
    } else {
      printf("Using mfence_rdtsc because you don't have an Intel CPU\n");
      clocktype = MFENCE_RDTSC;
    }
  }
}

int main(int argc, char **argv)
{
  argp_parse(&argp, argc, argv, 0, 0, 0);

  if (!tests_specified)
    run_now_test = run_load_test = run_load3_test = run_store_test = true;

  parse_cpuinfo();

  if (clocktype == RDTSC)
    run<Clock<RDTSC> >();
  else if (clocktype == RDTSCP)
    run<Clock<RDTSCP> >();
  else if (clocktype == LFENCE_RDTSC)
    run<Clock<LFENCE_RDTSC> >();
  else if (clocktype == MFENCE_RDTSC)
    run<Clock<MFENCE_RDTSC> >();
  else if (clocktype == MONOTONIC)
    run<Clock<MONOTONIC> >();
  else
    abort();

  return 0;
}
