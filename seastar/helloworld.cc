#include <cassert>
#include <iostream>

#include <seastar/core/app-template.hh>
#include <seastar/core/coroutine.hh>
#include <seastar/core/future.hh>
#include <seastar/core/reactor.hh>
#include <seastar/core/sleep.hh>
#include <seastar/coroutine/maybe_yield.hh>

namespace bpo = boost::program_options;

seastar::future<int> fast() {
    return seastar::make_ready_future<int>(1);
}

seastar::future<int> slow() {
    using namespace std::chrono_literals;
    return seastar::sleep(2s).then([] {
        return 3;
    });
}

seastar::future<> f() {
    using namespace std::chrono_literals;
    std::cout << "Sleeping ..." << std::flush;
    (void)fast().then([](int val) { std::cout << "Fast Got " << val << "\n"; });
    (void)seastar::sleep(100ms).then([] { std::cout << "100ms " << std::flush; });
    (void)seastar::sleep(200ms).then([] { std::cout << "200ms " << std::flush; });
    (void)seastar::sleep(1s).then([] { std::cout << "Done.\n"; });
    return slow().then([](int val) { std::cout << "Slow Got " << val << "\n"; });
}

int main(int argc, char **argv) {
    seastar::app_template app;
    std::string run_opt;

    app.add_options()("runopt,o", bpo::value<std::string>(&run_opt)->default_value("default"),
                      "Specify which function you want test");

    try {
        app.run(argc, argv, [&run_opt] {
            if (run_opt == "default") {
                return f();
            } else {
                std::cout << "Invalid option: " << run_opt << "\n";
                return seastar::make_ready_future<>();
            }
        });
    } catch (...) {
        std::cerr << "Couldn't start application: "
                  << std::current_exception()
                  << "\n";
        return 1;
    }
    return 0;
}
