#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

static gint back_width, back_height;
static GdkPixbuf *bgimage,*bgframe;

GdkPixbuf *load_pixbuf(const char *filename)
{
    GError *error = NULL;
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, &error);

    if (pixbuf == NULL)
    {
        g_print ("Error loading file: %d : %s\n", error->code, error->message);
        g_error_free (error);
        exit (1);
    }
      	back_width = gdk_pixbuf_get_width (pixbuf);
  	back_height = gdk_pixbuf_get_height (pixbuf);
    return pixbuf;
}

static gint draw_cb (GtkWidget *widget,cairo_t   *cr,gpointer   data) {
  	gdk_cairo_set_source_pixbuf (cr, bgframe, 0, 0);
  	cairo_paint (cr);
	return TRUE;
}

int main (int argc, char **argv)
{
    GtkWidget *da, *window = NULL;
        
    gtk_init (&argc, &argv);
    /* Load a non animated gif */
    bgimage = load_pixbuf("./coderain.png");
    bgframe = gdk_pixbuf_new (GDK_COLORSPACE_RGB, TRUE, 8, back_width, back_height);
    gdk_pixbuf_copy_area (bgimage, 0, 0, back_width, back_height,bgframe, 0, 0);
  
    da = gtk_drawing_area_new ();
    g_signal_connect (da, "draw",G_CALLBACK (draw_cb), NULL);

    	
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW(window), "Load Image");
    gtk_widget_set_size_request (window, 600,600);
    gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
    
    gtk_container_add (GTK_CONTAINER (window), da);

    gtk_widget_show_all (window);
    gtk_main ();
    return 0;
}
