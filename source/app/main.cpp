#include <utility.hpp>

using namespace std;
using namespace cxxopts;
namespace cursor
{
    typedef enum {up,down, right, left}cursor_dir;
    const string move(const int & col, const int & line)
    {
	return fmt::format("\033[{};{}f",line, col);
    }

    const string move(const cursor_dir & dir, const int & steps )
    {
	switch(dir)
	{
	case up:
	    return fmt::format("\033[{}A", steps);
	case down:
	    return fmt::format("\033[{}B",steps);
	case right:
	    return fmt::format("\033[{}C",steps);
	case left:
	    return fmt::format("\033[{}D",steps);	         	    
	}
    }

    const string clear_line() { return "\033[K"; }
    const string restore_cursor() { return "\033[u"; }
    const string clear_screen() { return "\033[2J"; }
    
};

struct Timer
{
    string title;
    chrono::hours hours;
    chrono::minutes minutes;
    chrono::seconds seconds;
};

bool timer_zero(const Timer & timer)
{
    return (timer.hours.count() == 0) &&
	(timer.minutes.count() == 0) &&
	(timer.seconds.count() == 0);
}
void print_time(Timer timer) {
    cout << box::heavy::h * 35 << endl;
    cout << timer.title << endl;
    cout << box::heavy::h * 35 << endl;
    cout << endl;
   
    for(; !timer_zero(timer); timer.seconds-- )
    {
	if((timer.seconds.count() == 0)
	   && (timer.minutes.count() >= 1))
	{
	    timer.seconds += 59s;
	    timer.minutes -= 1min;
	}

	if((timer.minutes.count() == 0) &&
	   (timer.hours.count() >= 1))
	{
	    timer.minutes += 59min;
	    timer.hours -= 1h;
	}
	    
		
	std::this_thread::sleep_for(1s);
	cout << fmt::format("{}:{}:{}", timer.hours.count(), timer.minutes.count(), timer.seconds.count()) << endl;	
//	if(timer.seconds.count() > 1)
        cout << cursor::move(cursor::up,1) << cursor::clear_line();
    }
    cout << box::heavy::h * 35 << endl;
}
int main(int argc, char* argv[])
{
    
    Options TimerApp("Timer App", "A commandline timer program");
    TimerApp.add_options()
	("title","Set Timer title", value<string>()->default_value("Timer Task"))
	("m,minutes", "Set Timer Minutes", value<int>()->default_value(0))
	("s,seconds", "Set Timer Seconds", value<int>()->default_value(0))
	("h,hours", "Set Timer Hours", value<int>()->default_value(0))
	("h,help", "Timer usage help", value<bool>()->default_value("false"));	

    auto timer_result = TimerApp.parse(argc, argv);

    chrono::hours h = 0h;
    if(timer_result.count("hours"))
       h = timer_result["hours"].as<chrono::hours>();

    chrono::minutes m = 0min;
    if(timer_result.count("minutes"))
	m = timer_result["minutes"].as<chrono::minutes>();

    chrono::seconds s = 0s;
    if(timer_result.count("seconds"))
	s = timer_result["seconds"].as<chrono::seconds>();

    string title = timer_result["title"].as<string>();

    int timer_seconds = 10;
    Timer timer{title, h, m, s};    
    cout << cursor::clear_screen();
    cout << "Start the Timer: " << endl;
    thread makeEgg(print_time, timer);
    makeEgg.join();
    cout << timer_seconds
	 << " seconds Elapsed" << endl;
}
