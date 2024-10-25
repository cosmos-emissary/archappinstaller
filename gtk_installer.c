#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <glib.h>
#include <gio/gio.h>

#define NUM_APPS 30

const char *apps[NUM_APPS] = {
    "firefox", 
    "gimp", 
    "vlc", 
    "gedit", 
    "gnome-terminal", 
    "code", 
    "qgis", 
    "git", 
    "htop",
    "gparted", 
    "telegram-desktop", 
    "libreoffice",
    "inkscape",
    "filezilla",
    "krita",
    "audacity",
    "virtualbox",
    "steam",
    "remmina",
    "kdenlive",
    "obs-studio",
    "nodejs",
    "mysql",
    "docker",
    "postfix",
    "apache",
    "nginx",
    "vim",
    "emacs",
    "bleachbit",
};

const char *app_descriptions[NUM_APPS] = {
    "Web browser", 
    "Image editor", 
    "Multimedia player", 
    "Text editor", 
    "Terminal emulator", 
    "Code editor", 
    "Geographic Information System", 
    "Version control system", 
    "System monitor",
    "Disk partitioning tool", 
    "Instant messaging application", 
    "Office suite",
    "Vector graphics editor",
    "FTP client",
    "Digital painting software",
    "Audio editor",
    "Virtual machine software",
    "Gaming platform",
    "Remote desktop tool",
    "Video editor",
    "Live streaming and screen recording application",
    "JavaScript runtime environment",
    "Database management system",
    "Container management tool",
    "Email server",
    "Web server",
    "Load balancer and web server",
    "Text editor",
    "Advanced text editor",
    "System cleaning tool",
};

const char *app_icons[NUM_APPS] = {
    "icons/firefox.png",
    "icons/gimp.png",
    "icons/vlc.png",
    "icons/gedit.png",
    "icons/gnome-terminal.png",
    "icons/code.png",
    "icons/qgis.png",
    "icons/git.png",
    "icons/htop.png",
    "icons/gparted.png",
    "icons/telegram.png",
    "icons/libreoffice.png",
    "icons/inkscape.png",
    "icons/filezilla.png",
    "icons/krita.png",
    "icons/audacity.png",
    "icons/virtualbox.png",
    "icons/steam.png",
    "icons/remmina.png",
    "icons/kdenlive.png",
    "icons/obs-studio.png",
    "icons/nodejs.png",
    "icons/mysql.png",
    "icons/docker.png",
    "icons/postfix.png",
    "icons/apache.png",
    "icons/nginx.png",
    "icons/vim.png",
    "icons/emacs.png",
    "icons/bleachbit.png",
};

GtkWidget *check_buttons[NUM_APPS];
GtkWidget *progress_bar;

void show_message(const char *message) {
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_DESTROY_WITH_PARENT,
                                               GTK_MESSAGE_INFO, GTK_BUTTONS_OK,
                                               "%s", message);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

void install_selected_apps() {
    for (int i = 0; i < NUM_APPS; i++) {
        if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(check_buttons[i]))) {
            char command[256];
            snprintf(command, sizeof(command), "pkexec pacman -S --noconfirm %s", apps[i]);

            char terminal_command[512];
            snprintf(terminal_command, sizeof(terminal_command), "foot -e bash -c '%s; echo \"Package installation complete, press enter to close.\"; read'", command);

            // Execute the command
            int result_code = system(terminal_command);
            if (result_code != 0) {
                show_message("Package installation error!");
                return;
            }
            gtk_progress_bar_pulse(GTK_PROGRESS_BAR(progress_bar)); // Update progress bar
        }
    }

    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), 1.0); // Completed
    show_message("Package installation finished!");
    gtk_main_quit(); // Exit when installation is complete
}

void on_install_button_clicked(GtkButton *button, gpointer user_data) {
    install_selected_apps();
}

GdkPixbuf* load_and_scale_icon(const char *icon_path, int width, int height) {
    GdkPixbuf *original = gdk_pixbuf_new_from_file(icon_path, NULL);
    if (original) {
        GdkPixbuf *scaled = gdk_pixbuf_scale_simple(original, width, height, GDK_INTERP_BILINEAR);
        g_object_unref(original);
        return scaled;
    }
    return NULL;
}

void on_continue_button_clicked(GtkButton *button, GtkWidget *window) {
    gtk_widget_destroy(window); // Close welcome window
}

void show_welcome_message(GtkWidget *main_window) {
    GtkWidget *welcome_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(welcome_window), "Welcome");
    gtk_window_set_default_size(GTK_WINDOW(welcome_window), 600, 200);
    gtk_window_set_resizable(GTK_WINDOW(welcome_window), FALSE);

    GtkWidget *label = gtk_label_new("Welcome to the real world. It will take some getting used to. \nSave your time because it is not unlimited. This tool is designed to give you more time. Remember that in the real world you can't make up for your mistakes (especially sudo mistakes).\n\nWe are everywhere\n\n'Cosmos Emissary'");
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);

    GtkWidget *continue_button = gtk_button_new_with_label("Continue");
    gtk_widget_set_size_request(continue_button, 100, 30); // Set button size

    g_signal_connect(continue_button, "clicked", G_CALLBACK(on_continue_button_clicked), welcome_window);

    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), label, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), continue_button, FALSE, FALSE, 0);
    
    gtk_container_add(GTK_CONTAINER(welcome_window), vbox);
    gtk_widget_show_all(welcome_window);
}

int main(int argc, char *argv[]) {
    gtk_init(&argc, &argv);

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Application Installer");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 800);
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Show welcome message
    show_welcome_message(window);
    
    // Create main VBox
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Header
    GtkWidget *label = gtk_label_new("Select the applications you want to install:");
    gtk_widget_set_name(label, "header_label");
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);

    // Scrollable area
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);

    GtkWidget *grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_container_add(GTK_CONTAINER(scrolled_window), grid);

    // Create check buttons, description labels, and image labels
    for (int i = 0; i < NUM_APPS; i++) {
        // Image
        GdkPixbuf *scaled_icon = load_and_scale_icon(app_icons[i], 32, 32);
        if (scaled_icon) {
            GtkWidget *icon_image = gtk_image_new_from_pixbuf(scaled_icon);
            gtk_grid_attach(GTK_GRID(grid), icon_image, (i % 3) * 3, i / 3, 1, 1);
            g_object_unref(scaled_icon);
        }

        // Check button
        check_buttons[i] = gtk_check_button_new_with_label(apps[i]);
        gtk_grid_attach(GTK_GRID(grid), check_buttons[i], (i % 3) * 3 + 1, i / 3, 1, 1);

        // Add description label
        GtkWidget *description_label = gtk_label_new(app_descriptions[i]);
        gtk_grid_attach(GTK_GRID(grid), description_label, (i % 3) * 3 + 2, i / 3, 1, 1);
    }

    // Progress bar
    progress_bar = gtk_progress_bar_new();
    gtk_box_pack_start(GTK_BOX(vbox), progress_bar, FALSE, FALSE, 0);

    // Install button
    GtkWidget *install_button = gtk_button_new_with_label("Install");
    g_signal_connect(install_button, "clicked", G_CALLBACK(on_install_button_clicked), NULL);
    gtk_box_pack_start(GTK_BOX(vbox), install_button, FALSE, FALSE, 0);
    gtk_widget_set_halign(install_button, GTK_ALIGN_CENTER);

    // Margin settings
    gtk_widget_set_margin_top(vbox, 20);
    gtk_widget_set_margin_bottom(vbox, 20);
    gtk_widget_set_margin_start(vbox, 20);
    gtk_widget_set_margin_end(vbox, 20);

    // Style settings
    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider,
        "window {"
        "  background-color: rgba(0, 0, 0, 0.8);"
        "}"
        "#header_label {"
        "  font-size: 24px;"
        "  font-weight: bold;"
        "  margin-bottom: 20px;"
        "  color: #ffffff;"
        "}"
        "button {"
        "  background-color: #007BFF;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 12px;"
        "  padding: 5px;"
        "  font-size: 16px;"
        "  transition: background-color 0.3s;"
        "}"
        "button:hover {"
        "  background-color: #0056b3;"
        "}"
        "checkbutton {"
        "  margin: 5px;"
        "  font-size: 16px;"
        "  color: #ffffff;"
        "  background-color: rgba(255, 255, 255, 0.1);"
        "  border-radius: 6px;"
        "  padding: 10px;"
        "}"
        "label {"
        "  color: #ffffff;"
        "  font-size: 14px;"
        "  margin-left: 10px;"
        "}",
        -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), 
                                              GTK_STYLE_PROVIDER(css_provider), 
                                              GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    gtk_widget_show_all(window);
    gtk_main();

    return 0;
}
