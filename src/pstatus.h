/*

   Timer

   Sat Feb 23 2002

*/

class Timer {
  float utime;
 public:
  enum Times{
	user,
	system,
	wall,
	vmsize
  };
  void start();
  void restart();
  void stop();
  float read(Times);
  void output(std::ostream& ,Times);
};
