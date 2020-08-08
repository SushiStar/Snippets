#include <unordered_map>
#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <cpr/cpr.h>

class WebGetter {
 private:
  static std::mutex mtx;  // lock for counter
  static std::unordered_map<int, int> counter;

  static void GetCodefromWeb(const std::string &url,
                             std::unordered_map<int, int> &counter,
                             std::mutex &mtx);

 public:
  WebGetter(){};
  ~WebGetter(){};
  void GetCode(const std::vector<std::string> &weblist);
  void ShowInfo();
};
void WebGetter::GetCodefromWeb(const std::string &url,
                               std::unordered_map<int, int> &counter,
                               std::mutex &mtx) {
  cpr::Response r = cpr::Get(cpr::Url{url});
  mtx.lock();
  counter[r.status_code]++;
  mtx.unlock();
}
void WebGetter::GetCode(const std::vector<std::string> &weblist) {
  std::vector<std::thread *> threads(weblist.size());
  for (int i = 0; i < weblist.size(); ++i) {
    threads[i] =
        std::move(new std::thread(GetCodefromWeb, weblist[i], counter, mtx));
  }
  for (auto t : threads) {
    t->join();
  }
}

void WebGetter::ShowInfo() {
  for (const auto &pr : counter) {
    std::cout << "status_code: " << pr.first << ", number of web: " << pr.second
              << std::endl;
  }
}
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
