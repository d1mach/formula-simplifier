
#include <ostream>
#include <iomanip>
#include "pstatus.h"

#include <sys/times.h>
#include <time.h>
#define CLK_TCK CLOCKS_PER_SEC

using namespace std;

struct tms timebuf;

void Timer::restart(){
  times(&timebuf);
  utime = timebuf.tms_utime - utime*CLK_TCK;
}

void Timer::start(){
  times(&timebuf);
  utime = timebuf.tms_utime;
}

void Timer::stop(){
  times(&timebuf);
  utime = (timebuf.tms_utime - utime )/CLK_TCK;
}

float Timer::read(Times t){
  switch (t){
  case user:
	return utime;
  default:
	return -1;
  }
}

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int vmsize_idx = 23;
const int STATLINE_MAX = 4096;
const char delim[] = " ";

int get_vm_size(pid_t& pid){
  char namebuf[FILENAME_MAX];
  FILE *statfile;
  char stringbuf[STATLINE_MAX];
  char* field;
  int size;
  

  if (pid == 0) pid = getpid();

  sprintf(namebuf,"/%s/%d/%s","proc",pid,"stat");
  statfile = fopen(namebuf, "r");

  if (!statfile) return -1;
  fgets(stringbuf,STATLINE_MAX,statfile);
  strtok_r(stringbuf,delim,&field);
  for(int i=2; (i < vmsize_idx) && (field != 0); 
	  i++, strtok_r(0,delim,&field));
  size = atoi(field);
  fclose(statfile);

  return size;
}

void Timer::output(ostream &stream, Times t){
  int pid = 0;
  switch (t){
  case user:
	stream << "user time: " << 
	  setprecision(3) << utime << " s" << 
	  endl;
	break;
  case vmsize:
	stream << "virtual memory size: " <<
	  get_vm_size(pid)/1024 << " Kbytes" << endl;
  default:
	break;
  }
}

