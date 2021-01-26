#include <cpr/cpr.h>

#include <iostream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

class WebGetter {
 private:
  std::mutex mtx;  // lock for counter
  std::unordered_map<std::string, int> counter;

  void GetCodefromWeb(const std::string &url);

 public:
  WebGetter(){};
  ~WebGetter(){};
  void GetCode(const std::vector<std::string> &weblist);
  void ShowInfo();
};
void WebGetter::GetCodefromWeb(const std::string &url) {
  auto start = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed{0};
  while (elapsed.count() < 3.0)
    elapsed = std::chrono::high_resolution_clock::now() - start;
  mtx.lock();
  counter[url]++;
  mtx.unlock();
}
void WebGetter::GetCode(const std::vector<std::string> &weblist) {
  std::vector<std::thread *> threads(weblist.size());
  for (int i = 0; i < weblist.size(); ++i) {
    threads[i] = std::move(
        new std::thread(&WebGetter::GetCodefromWeb, this, weblist[i]));
  }
  for (auto t : threads) t->join();
}

void WebGetter::ShowInfo() {}
int main() {
  std::vector<std::string> list_of_webpages{
      "https://bbc.co.uk",   "https://nytimes.com",
      "https://reddit.com",  "https://facebook.com",
      "https://amazon.com",  "https://stackoverflow.com",
      "https://youtube.com", "https://berkeley.edu",
      "https://stanford.edu"};
  WebGetter webgetter;
  auto start = std::chrono::high_resolution_clock::now();
  webgetter.GetCode(list_of_webpages);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "time by GetCode() func: " << elapsed.count() << std::endl;
  webgetter.ShowInfo();
  return 0;
}
