#include <gtk/gtk.h>
#include <iostream>

// 콜백 함수 정의
static void calculate_callback(GtkWidget *button, gpointer data) {
    // 사용자가 입력한 텍스트를 가져오기
    const gchar *text1 = gtk_entry_get_text(GTK_ENTRY(data));

    // 두 번째 입력 상자의 텍스트 가져오기
    GtkWidget *entry2 = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "entry2"));
    const gchar *text2 = gtk_entry_get_text(GTK_ENTRY(entry2));

    // 결과를 표시할 레이블 가져오기
    GtkWidget *result_label = GTK_WIDGET(g_object_get_data(G_OBJECT(button), "result_label"));

    // 두 수를 정수로 변환하여 계산
    int num1 = atoi(text1);
    int num2 = atoi(text2);

    // 계산 종류에 따라 결과 계산
    if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(button)), "+") == 0) {
        // 덧셈
        int result = num1 + num2;
        // 결과를 레이블에 표시
        gtk_label_set_text(GTK_LABEL(result_label), std::to_string(result).c_str());
    } else if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(button)), "-") == 0) {
        // 뺄셈
        int result = num1 - num2;
        gtk_label_set_text(GTK_LABEL(result_label), std::to_string(result).c_str());
    } else if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(button)), "x") == 0) {
        // 곱셈
        int result = num1 * num2;
        gtk_label_set_text(GTK_LABEL(result_label), std::to_string(result).c_str());
    } else if (g_strcmp0(gtk_button_get_label(GTK_BUTTON(button)), "%") == 0) {
        // 나머지
        int result = num1 % num2;
        gtk_label_set_text(GTK_LABEL(result_label), std::to_string(result).c_str());
    }
}

int main(int argc, char *argv[]) {
    // GTK 초기화
    gtk_init(&argc, &argv);

    // 윈도우 생성
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "간단한 계산기");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 300, 150);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // 그리드 생성
    GtkWidget *grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(window), grid);

    // 첫 번째 입력 상자 생성
    GtkWidget *entry1 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry1, 0, 0, 1, 1);

    // 두 번째 입력 상자 생성
    GtkWidget *entry2 = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry2, 1, 0, 1, 1);

    // 레이블 생성 (결과 표시)
    GtkWidget *result_label = gtk_label_new("결과: ");
    gtk_grid_attach(GTK_GRID(grid), result_label, 0, 2, 2, 1);

    // 연산 버튼 생성 (+, -, x, %)
    const gchar *button_labels[] = {"+", "-", "x", "%"};
    for (int i = 0; i < 4; ++i) {
        GtkWidget *button = gtk_button_new_with_label(button_labels[i]);
        gtk_grid_attach(GTK_GRID(grid), button, i, 1, 1, 1);

        // 콜백 함수와 함께 버튼에 데이터 전달
        g_object_set_data(G_OBJECT(button), "entry2", entry2);
        g_object_set_data(G_OBJECT(button), "result_label", result_label);
        g_signal_connect(button, "clicked", G_CALLBACK(calculate_callback), entry1);
    }

    // 윈도우 및 그리드 표시
    gtk_widget_show_all(window);

    // GTK 이벤트 루프 실행
    gtk_main();

    return 0;
}
