/*
instalacion:
sudo apt-get install gtk+-3.0
sudo apt-get upgrade gtk+-3.0
sudo apt-get install libgtk-3-dev

pkg-config --cflags gtk+-3.0 
pkg-config --libs gtk+-3.0

compilacion: 
gcc `pkg-config --cflags gtk+-3.0` -o gui gui_calc.c `pkg-config --libs gtk+-3.0`
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

GtkWidget *window, *input, *symbols[10], *layout1, *eq_button, *p_button, *m_button, *change_button, *clear_button;
int op1, op2, result, operacion, change_count;

void num0_action(){
    char inputNum[30] = "";
    char zero = '0';
    int inputInt;

    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &inputInt);
    sprintf(inputNum, "%i", inputInt);
    strncat(inputNum, &zero, 1);
    gtk_entry_set_text((GtkEntry *)input, inputNum);
}

void num1_action(){
    char inputNum[30] = "";
    char one = '1';
    int inputInt;

    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &inputInt);
    sprintf(inputNum, "%i", inputInt);
    strncat(inputNum, &one, 1);
    gtk_entry_set_text((GtkEntry *)input, inputNum);
}

void num2_action(){
    char inputNum[30] = "";
    char two = '2';
    int inputInt;

    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &inputInt);
    sprintf(inputNum, "%i", inputInt);
    strncat(inputNum, &two, 1);
    gtk_entry_set_text((GtkEntry *)input, inputNum);
}

void num3_action(){
    char inputNum[30] = "";
    char three = '3';
    int inputInt;

    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &inputInt);
    sprintf(inputNum, "%i", inputInt);
    strncat(inputNum, &three, 1);
    gtk_entry_set_text((GtkEntry *)input, inputNum);
}

void num4_action(){
    char inputNum[30] = "";
    char four = '4';
    int inputInt;

    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &inputInt);
    sprintf(inputNum, "%i", inputInt);
    strncat(inputNum, &four, 1);
    gtk_entry_set_text((GtkEntry *)input, inputNum);
}

void num5_action(){
    char inputNum[30] = "";
    char five = '5';
    int inputInt;

    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &inputInt);
    sprintf(inputNum, "%i", inputInt);
    strncat(inputNum, &five, 1);
    gtk_entry_set_text((GtkEntry *)input, inputNum);
}

void num6_action(){
    char inputNum[30] = "";
    char six = '6';
    int inputInt;

    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &inputInt);
    sprintf(inputNum, "%i", inputInt);
    strncat(inputNum, &six, 1);
    gtk_entry_set_text((GtkEntry *)input, inputNum);
}

void num7_action(){
    char inputNum[30] = "";
    char seven = '7';
    int inputInt;

    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &inputInt);
    sprintf(inputNum, "%i", inputInt);
    strncat(inputNum, &seven, 1);
    gtk_entry_set_text((GtkEntry *)input, inputNum);
}

void num8_action(){
    char inputNum[30] = "";
    char eigth = '8';
    int inputInt;

    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &inputInt);
    sprintf(inputNum, "%i", inputInt);
    strncat(inputNum, &eigth, 1);
    gtk_entry_set_text((GtkEntry *)input, inputNum);
}

void num9_action(){
    char inputNum[30] = "";
    char nine = '9';
    int inputInt;

    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &inputInt);
    sprintf(inputNum, "%i", inputInt);
    strncat(inputNum, &nine, 1);
    gtk_entry_set_text((GtkEntry *)input, inputNum);
}

void sum_action(){
    operacion = 0;
    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &op1);
    gtk_entry_set_text((GtkEntry *)input, "0");
}

void sub_action(){
    operacion = 1;
    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &op1);
    gtk_entry_set_text((GtkEntry *)input, "0");
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
    if(change_count%2 == 0){
        gtk_button_set_label ((GtkButton *)change_button, "Dec");
        
        gtk_layout_move(GTK_LAYOUT(layout1), symbols[0], 80, 100);
        gtk_layout_move(GTK_LAYOUT(layout1), symbols[1], 80, 150);
        for(int i=2; i<10; i++){
            gtk_layout_move(GTK_LAYOUT(layout1), symbols[i], -100, -100);
        }
    }
    else{
        gtk_button_set_label ((GtkButton *)change_button, "Bin");

        gtk_layout_move(GTK_LAYOUT(layout1), symbols[0], 30, 250);
        for (int i = 0; i < 3; i++)
        {
            gtk_layout_move(GTK_LAYOUT(layout1), symbols[i+1], 30+i*50, 100);
            gtk_layout_move(GTK_LAYOUT(layout1), symbols[i+4], 30+i*50, 150);
            gtk_layout_move(GTK_LAYOUT(layout1), symbols[i+7], 30+i*50, 200);
        }
    }

    change_count++;
}

void clear_action(){
    op1 = 0;
    op2 = 0;
    result = 0;
    gtk_entry_set_text((GtkEntry *)input, "0");
}

int main(int argc, char **argv){

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora");
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    gtk_window_set_default_size(GTK_WINDOW(window), 280, 300);
    
    //para decimales
    layout1 = gtk_layout_new(NULL, NULL);

    //creo el display del input
    input = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(input), 25);
    gtk_entry_set_width_chars(GTK_ENTRY(input), 25);
    gtk_entry_set_text((GtkEntry *)input, "0");
    
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
    clear_button = gtk_button_new_with_label("CE");

    /************DIBUJO LAYOUT PARA DECIMALES***********/
    //dibujo display input 
    gtk_layout_put(GTK_LAYOUT(layout1), input, 30, 30);

    //dibujo 0, agrego accion
    gtk_layout_put(GTK_LAYOUT(layout1), symbols[0], 30, 250);
    g_signal_connect(symbols[0], "clicked", G_CALLBACK(num0_action), NULL);
    
    //dibujo 1 a 9, agrego accion
    for (int i = 0; i < 3; i++)
    {
        gtk_layout_put(GTK_LAYOUT(layout1), symbols[i+1], 30+i*50, 100);
        gtk_layout_put(GTK_LAYOUT(layout1), symbols[i+4], 30+i*50, 150);
        gtk_layout_put(GTK_LAYOUT(layout1), symbols[i+7], 30+i*50, 200);
    }

    g_signal_connect(symbols[1], "clicked", G_CALLBACK(num1_action), NULL);
    g_signal_connect(symbols[2], "clicked", G_CALLBACK(num2_action), NULL);
    g_signal_connect(symbols[3], "clicked", G_CALLBACK(num3_action), NULL);
    g_signal_connect(symbols[4], "clicked", G_CALLBACK(num4_action), NULL);
    g_signal_connect(symbols[5], "clicked", G_CALLBACK(num5_action), NULL);
    g_signal_connect(symbols[6], "clicked", G_CALLBACK(num6_action), NULL);
    g_signal_connect(symbols[7], "clicked", G_CALLBACK(num7_action), NULL);
    g_signal_connect(symbols[8], "clicked", G_CALLBACK(num8_action), NULL);
    g_signal_connect(symbols[9], "clicked", G_CALLBACK(num9_action), NULL);

    //dibujo +, -, = y cambio, le pongo acciones
    gtk_layout_put(GTK_LAYOUT(layout1), p_button, 80, 250);
    gtk_layout_put(GTK_LAYOUT(layout1), m_button, 130, 250);
    gtk_layout_put(GTK_LAYOUT(layout1), eq_button, 200, 150);
    gtk_layout_put(GTK_LAYOUT(layout1), change_button, 200, 250);
    gtk_layout_put(GTK_LAYOUT(layout1), clear_button, 200, 100);

    g_signal_connect(p_button, "clicked", G_CALLBACK(sum_action), NULL);
    g_signal_connect(m_button, "clicked", G_CALLBACK(sub_action), NULL);
    g_signal_connect(eq_button, "clicked", G_CALLBACK(eq_action), NULL);
    g_signal_connect(change_button, "clicked", G_CALLBACK(change_action), NULL);
    g_signal_connect(clear_button, "clicked", G_CALLBACK(clear_action), NULL);

    //agrego el layout a la ventana y la muestro
    gtk_container_add(GTK_CONTAINER(window), layout1);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}