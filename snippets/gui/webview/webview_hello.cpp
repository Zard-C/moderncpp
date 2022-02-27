//[headers Headers
#include <webview.h>
//]

#include <iostream>

#ifdef _WIN32
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow)
#else
int main()
#endif
{
    //[create Create a webview
    webview::webview w(true, nullptr);
    w.set_title("Example");
    w.set_size(480, 320, WEBVIEW_HINT_NONE);
    w.set_size(180, 120, WEBVIEW_HINT_MIN);
    //]

    //[bind_fn Bind javascript function receiving a string
    w.bind("noop", [](std::string s) -> std::string {
        std::cout << s << std::endl;
        return s;
    });
    //]

    //[bind_fn_ints Bind javascript function receiving two ints
    w.bind("add", [](std::string s) -> std::string {
        auto a = std::stoi(webview::json_parse(s, "", 0));
        auto b = std::stoi(webview::json_parse(s, "", 1));
        return std::to_string(a + b);
    });
    //]

    //[render Render webview
    w.navigate(R"(data:text/html,
    <!doctype html>
    <html>
      <body>hello</body>
      <script>
        window.onload = function() {
          document.body.innerText = `hello, ${navigator.userAgent}`;
          noop('hello').then(function(res) {
            console.log('noop res', res);
          });
          add(1, 2).then(function(res) {
            console.log('add res', res);
          });
        };
      </script>
    </html>
  )");
    //]

    //[run Run application
    w.run();
    //]

    return 0;
}