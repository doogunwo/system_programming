#include <gtk/gtk.h>

void on_row_activated(GtkTreeView *tree_view, GtkTreePath *path, GtkTreeViewColumn *column, gpointer user_data) {
    GtkTreeModel *model;
    GtkTreeIter iter;

    model = gtk_tree_view_get_model(tree_view);
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        gchar *value;
        gtk_tree_model_get(model, &iter, 0, &value, -1);
        g_print("Selected: %s\n", value);
        g_free(value);
    }
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    
    GtkListStore *list_store = gtk_list_store_new(1, G_TYPE_STRING);
    GtkTreeIter iter;

    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, 0, "Item 1", -1);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, 0, "Item 2", -1);

    GtkWidget *tree_view = gtk_tree_view_new_with_model(GTK_TREE_MODEL(list_store));
    gtk_tree_view_append_column(GTK_TREE_VIEW(tree_view), gtk_tree_view_column_new_with_attributes("Column 1", gtk_cell_renderer_text_new(), "text", 0, NULL));
    g_signal_connect(tree_view, "row-activated", G_CALLBACK(on_row_activated), NULL);

    gtk_container_add(GTK_CONTAINER(window), tree_view);
    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
