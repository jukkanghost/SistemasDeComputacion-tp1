#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

GtkWidget *window, *input, *symbols[10], *layout1, *eq_button, *p_button, *m_button, *change_button, *clear_button;
int op1, op2, result, operacion, change_count;
int firstNum = 1;

void appendNumber(int num){
    char inputNum[30] = "";
    int inputInt;
    char numToAppend[5] = "";

    sprintf(numToAppend, "%i", num);

    if(firstNum){
        gtk_entry_set_text((GtkEntry *)input, numToAppend);
        firstNum = 0;
    }
    else{
        sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &inputInt);
        sprintf(inputNum, "%i", inputInt);
        strncat(inputNum, numToAppend, 1);
        gtk_entry_set_text((GtkEntry *)input, inputNum);
    }
}

void scanOperando1(){
    sscanf(gtk_entry_get_text(GTK_ENTRY(input)), "%i", &op1);
    gtk_entry_set_text((GtkEntry *)input, "");
    firstNum = 1;
}

void num0_action(){
    appendNumber(0);
}

void num1_action(){
    appendNumber(1);
}

void num2_action(){
    appendNumber(2);
}

void num3_action(){
    appendNumber(3);
}

void num4_action(){
    appendNumber(4);
}

void num5_action(){
    appendNumber(5);
}

void num6_action(){
    appendNumber(6);
}

void num7_action(){
    appendNumber(7);
}

void num8_action(){
    appendNumber(8);
}

void num9_action(){
    appendNumber(9);
}

void sum_action(){
    operacion = 0;
    scanOperando1();
}

void sub_action(){
    operacion = 1;
    scanOperando1();
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
        
        for(int i=2; i<10; i++){
            gtk_widget_hide(symbols[i]);
        }
        gtk_layout_move(GTK_LAYOUT(layout1), symbols[0], 80, 100);
        gtk_layout_move(GTK_LAYOUT(layout1), symbols[1], 80, 150);
    }
    else{
        gtk_button_set_label ((GtkButton *)change_button, "Bin");

        gtk_layout_move(GTK_LAYOUT(layout1), symbols[0], 30, 250);
        gtk_layout_move(GTK_LAYOUT(layout1), symbols[1], 30, 100);
        for (int i=2; i<10; i++)
        {
            gtk_widget_show(symbols[i]);
        }
    }
    gtk_button_clicked (GTK_BUTTON(clear_button));
    change_count++;
}

void clear_action(){
    op1 = 0;
    op2 = 0;
    result = 0;
    gtk_entry_set_text((GtkEntry *)input, "");
    firstNum = 1;
}

int main(int argc, char **argv){

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_title(GTK_WINDOW(window), "Calculadora");
    gtk_container_set_border_width(GTK_CONTAINER(window), 0);
    gtk_window_set_default_size(GTK_WINDOW(window), 280, 300);
    
    layout1 = gtk_layout_new(NULL, NULL);

    //creo el display del input
    input = gtk_entry_new();
    gtk_entry_set_max_length(GTK_ENTRY(input), 25);
    gtk_entry_set_width_chars(GTK_ENTRY(input), 25);
    
    //creo botones de 0 a 9
    for(int i = 0; i < 10; i++){
        char num[5];
        sprintf(num,"%d",i);
        symbols[i] = gtk_button_new_with_label(num);
    }

    //creo botones +, -, = y de cambio
    eq_button = gtk_button_new_with_label("=");
    p_button = gtk_button_new_with_label("+");
    m_button = gtk_button_new_with_label("-");
    change_button = gtk_button_new_with_label("Bin");
    clear_button = gtk_button_new_with_label("CE");

    /************ DIBUJO LAYOUT ***************/
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