#Timing your code
C++11 comes with some functionality in the chrono library to do timing.
```cpp
#include <chrono> // for std::chrono functions
class Timer {
private:
	// type aliases to make accessing nested type easier.
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1>>;
	std::chrono::time_point<clock_t> m_beg;
public:
	Timer() : m_beg(clock_t::now()){}
	void reset() {
		m_beg = clock_t::now();
	}
	double elapsed() const {
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_begin).count();
	}
};
int main() {
	Timer t;
	// code to time goes here
	std::cout << "Time elapsed: " << t.elapsed() << " seconds\n";
	return 0;
}
```
###A few caveats about timing
Timing is straightforward, but your results can be significantly impacted by a number of things, and it's important to be aware of what those things are.

Firstly, make sure you're ***using a release build target***, not a debug build target. Debug build targets typically turn optimization off, and that optimization can have a significant impact on the results.

Second, your timing results will be influenced by other things your system may be doing in the background. For best results, make sure your system isn't doing anything CPU or memory intensive (e.g. playing a game) or hard drive intensive (e.g. searching for a file or running an antirirus scan).

Then measure at least 3 times. If the results are all similar, take teh average. If one or two results are different, run the program a few more times until you get a better sense of which ones are outliers. Note that seemingly innocent things like web browsers, can temporarily spike your CPU to 100% utilization when the site you have stting in the background rotates in a new ad banner and has to parse a bunch of javascripts. Running multiple times helps identify whether your initial run may have been impacted by such an event.

Third, when doing comparasions between two sets of code, be wary of what may change between runs that could impact timing. Your system may have kicked off an antivirus scan in the background, or maybe you're streaming music now when you weren't previously. Randomization can also impact timing. If we'd sorted an array filled with randomization is identical each run. Also, make sure you're not timing waiting for user input, as how long the user take to input something should not be part of your timing considerations.

Finally, note that results are only valid for your machine's architecture, OS, compiler, and system specs. You may get different results on other systems that have different strengths and weaknesses.
