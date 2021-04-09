#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

GtkWidget *window, *window2, *input, *symbols[10], *layout1, *layout2, *eq_button, *p_button, *m_button, *change_button;
int op1, op2, result, operacion, change_count;


void num_action(){
    ;
}

void sum_action(){
    operacion = 0;
    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &op1);
    gtk_entry_set_text((GtkEntry *)input, "");
}

void sub_action(){
    operacion = 1;
    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &op1);
    gtk_entry_set_text((GtkEntry *)input, "");
}

void eq_action(){
    char resText[30];

    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &op2);
    
    if(operacion == 0){
        result = op1 + op2;
    }
    else{
        result = op1 - op2;
    }
    
    sprintf(resText, "%i", result);
    gtk_entry_set_text((GtkEntry *)input, resText);
}

void change_action(){
    change_count++;
}

int main(int argc, char **argv){

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora");
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    gtk_window_set_default_size(GTK_WINDOW(window), 280, 300);
    
    /*window2 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window2, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window2), "Calculadora");
    gtk_container_set_border_width(GTK_CONTAINER(window2), 0);
    gtk_window_set_default_size(GTK_WINDOW(window2), 280, 300);*/

    //para decimales
    layout1 = gtk_layout_new(NULL, NULL);
    //para binarios
    layout2 = gtk_layout_new(NULL, NULL);

    //creo el display del input
    input = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(input), 25);
    gtk_entry_set_width_chars(GTK_ENTRY(input), 25);

    //creo botones de 0 a 9
    symbols[0] = gtk_button_new_with_label("0");
    symbols[1] = gtk_button_new_with_label("1");
    symbols[2] = gtk_button_new_with_label("2");
    symbols[3] = gtk_button_new_with_label("3");
    symbols[4] = gtk_button_new_with_label("4");
    symbols[5] = gtk_button_new_with_label("5");
    symbols[6] = gtk_button_new_with_label("6");
    symbols[7] = gtk_button_new_with_label("7");
    symbols[8] = gtk_button_new_with_label("8");
    symbols[9] = gtk_button_new_with_label("9");

    //creo botones +, -, = y de cambio
    eq_button = gtk_button_new_with_label("=");
    p_button = gtk_button_new_with_label("+");
    m_button = gtk_button_new_with_label("-");
    change_button = gtk_button_new_with_label("Bin");

    /************DIBUJO LAYOUT PARA DECIMALES***********/
    //dibujo display input 
    gtk_layout_put(GTK_LAYOUT(layout1), input, 30, 30);

    //dibujo 0, agrego accion
    gtk_layout_put(GTK_LAYOUT(layout1), symbols[0], 30, 250);
    //g_signal_connect(p_button, "clicked", G_CALLBACK(num_action(0)), NULL);
    
    //dibujo 1 a 9, agrego accion
    for (int i = 0; i < 3; i++)
    {
        gtk_layout_put(GTK_LAYOUT(layout1), symbols[i+1], 30+i*50, 100);
        //g_signal_connect(symbols[i+1], "clicked", G_CALLBACK(num_action(i+1)), NULL);
        gtk_layout_put(GTK_LAYOUT(layout1), symbols[i+4], 30+i*50, 150);
        //g_signal_connect(symbols[i+4], "clicked", G_CALLBACK(num_action(i+4)), NULL);
        gtk_layout_put(GTK_LAYOUT(layout1), symbols[i+7], 30+i*50, 200);
        //g_signal_connect(symbols[i+7], "clicked", G_CALLBACK(num_action(i+7)), NULL);
    }

    //dibujo +, -, = y cambio, le pongo acciones
    gtk_layout_put(GTK_LAYOUT(layout1), p_button, 80, 250);
    gtk_layout_put(GTK_LAYOUT(layout1), m_button, 130, 250);
    gtk_layout_put(GTK_LAYOUT(layout1), eq_button, 200, 150);
    gtk_layout_put(GTK_LAYOUT(layout1), change_button, 200, 250);

    g_signal_connect(p_button, "clicked", G_CALLBACK(sum_action), NULL);
    g_signal_connect(m_button, "clicked", G_CALLBACK(sub_action), NULL);
    g_signal_connect(eq_button, "clicked", G_CALLBACK(eq_action), NULL);
    g_signal_connect(change_button, "clicked", G_CALLBACK(change_action), NULL);

    /************DIBUJO LAYOUT PARA BINARIOS***********/
    //dibujo display input 
    /*gtk_layout_put(GTK_LAYOUT(layout2), input, 30, 30);

    //dibujo 0, agrego accion
    gtk_layout_put(GTK_LAYOUT(layout2), symbols[0], 30, 150);
    gtk_layout_put(GTK_LAYOUT(layout2), symbols[1], 30, 250);

    //dibujo +, -, = y cambio, le pongo acciones
    gtk_layout_put(GTK_LAYOUT(layout2), p_button, 80, 250);
    gtk_layout_put(GTK_LAYOUT(layout2), m_button, 130, 250);
    gtk_layout_put(GTK_LAYOUT(layout2), eq_button, 200, 150);
    gtk_layout_put(GTK_LAYOUT(layout2), change_button, 200, 250);*/

    /**************************************************/
    gtk_container_add(GTK_CONTAINER(window), layout1);
    //gtk_container_add(GTK_CONTAINER(window2), layout2);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}