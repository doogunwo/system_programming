#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Content-Type 헤더 출력
    printf("Content-Type: text/html\r\n\r\n");

    // HTML 페이지 출력
    printf("<html><body>\n");

    // CGI 환경 변수 출력
    printf("<h1>CGI Environment Variables</h1>\n");
    printf("<p>QUERY_STRING: %s</p>\n", getenv("QUERY_STRING"));
    printf("<p>REQUEST_METHOD: %s</p>\n", getenv("REQUEST_METHOD"));
    printf("<p>CONTENT_LENGTH: %s</p>\n", getenv("CONTENT_LENGTH") ? getenv("CONTENT_LENGTH") : "N/A");
    printf("<p>CONTENT_TYPE: %s</p>\n", getenv("CONTENT_TYPE") ? getenv("CONTENT_TYPE") : "N/A");
    printf("</body></html>\n");

    return 0;
}
