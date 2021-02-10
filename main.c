/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * 
 * File:   main.c
 * Author: jucardozo
 *
 * Created on January 29, 2021, 4:20 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>


/*
 * 
 */
enum MYKEYS {
    KEY_W, KEY_S, KEY_A, KEY_D,ESC //enumero mis letras oa q quede mas fachero el arrgelo
};
bool key_pressed[5] = {false, false, false, false,false}; //Estado de teclas, true cuando esta apretada
   
int main() {
    ALLEGRO_DISPLAY * display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }
    if (!al_install_keyboard()) {   //creo teclado, 
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }
    timer = al_create_timer(1.0 / 60.0);    //creo timer que me va generar eventos automaticos
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }
    event_queue = al_create_event_queue();  //creamos cola de eventos
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_timer(timer);
        return -1;
    }
    display = al_create_display(640, 480);      //creo un display creo que es totalmente necesario pal teclaod
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        al_destroy_event_queue(event_queue);
        return -1;
    }
    al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 255,255,255 (blanco)
    al_flip_display(); //Flip del backbuffer, pasa a verse a la pantalla
    al_register_event_source(event_queue, al_get_timer_event_source(timer));//registro eventos del timer
    al_register_event_source(event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO
    
    al_start_timer(timer);
    
    int fin=1;
    while(fin){
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)){ //Toma un evento de la cola.
            if (ev.type == ALLEGRO_EVENT_TIMER) {   //si el timer realiza un evento , me regenera el display
                
                
                al_clear_to_color(al_map_rgb(50, 255, 10)); //Hace clear del backbuffer del diplay al color RGB 255,255,255 (blanco)
                al_flip_display(); //Flip del backbuffer, pasa a verse a la pantalla
            }
            else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {       //pregunta si hay alguna tecla presionada,
                    switch (ev.keyboard.keycode) {         //en el caso de que lo haya marca como true, la presionada
                        case ALLEGRO_KEY_W:
                        case ALLEGRO_KEY_UP:
                            key_pressed[KEY_W] = true;
                            printf("estas apretando W\n");
                            break;

                        case ALLEGRO_KEY_S:
                        case ALLEGRO_KEY_DOWN:
                            key_pressed[KEY_S] = true;
                            printf("estas apretando S\n");
                            break;

                        case ALLEGRO_KEY_A:
                        case ALLEGRO_KEY_LEFT:
                            key_pressed[KEY_A] = true;
                            printf("estas apretando A\n");
                            break;

                        case ALLEGRO_KEY_D:
                        case ALLEGRO_KEY_RIGHT:
                            key_pressed[KEY_D] = true;
                            printf("estas apretando D\n");
                            break;
                            
                        case ALLEGRO_KEY_ESCAPE:
                            key_pressed[ESC]=true;
                            fin=0;
                            break;
                    }
                }
                else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
                    switch (ev.keyboard.keycode) {
                        case ALLEGRO_KEY_W:
                        case ALLEGRO_KEY_UP:
                            key_pressed[KEY_W] = false;
                            printf("ya no estas apretando W\n");
                            break;

                        case ALLEGRO_KEY_S:
                        case ALLEGRO_KEY_DOWN:
                            key_pressed[KEY_S] = false;
                            printf("ya no estas apretando S\n");
                            break;

                        case ALLEGRO_KEY_A:
                        case ALLEGRO_KEY_LEFT:
                            key_pressed[KEY_A] = false;
                            printf("ya no estas apretando A\n");
                            break;

                        case ALLEGRO_KEY_D:
                        case ALLEGRO_KEY_RIGHT:
                            key_pressed[KEY_D] = false;
                            printf("ya no estas apretando D\n");
                            break;

                       /* case ALLEGRO_KEY_ESCAPE:
                            do_exit = true;
                            break;*/
                    }
                }
            }
    }
    al_destroy_display(display); //IMPORTANTE: Destruir recursor empleados
    al_destroy_timer(timer);
    al_destroy_event_queue(event_queue);

    return (0);
}

#include <stdio.h>
#include <allegro5/allegro.h>

#define FPS    60.0
#define SCREEN_W  640
#define SCREEN_H  480
#define CUADRADITO_SIZE 32
#define MOVE_RATE  4.0

enum MYKEYS {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT //arrow keys
};

int main(void) {
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_BITMAP *cuadradito = NULL;

    float cuadradito_x = SCREEN_W/2.0  - CUADRADITO_SIZE / 2.0;         //se centra el cuadradoo
    float cuadradito_y = SCREEN_H / 2.0 - CUADRADITO_SIZE / 2.0;

    bool key_pressed[4] = {false, false, false, false}; //Estado de teclas, true cuando esta apretada
    bool redraw = false;
    bool do_exit = false;

    if (!al_init()) {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    if (!al_install_keyboard()) {
        fprintf(stderr, "failed to initialize the keyboard!\n");
        return -1;
    }

    timer = al_create_timer(1.0 / FPS);
    if (!timer) {
        fprintf(stderr, "failed to create timer!\n");
        return -1;
    }

    cuadradito = al_create_bitmap(CUADRADITO_SIZE, CUADRADITO_SIZE);    //CREA UN CUADRADITO A CHIQUITITO
    if (!cuadradito) {
        fprintf(stderr, "failed to create cuadradito bitmap!\n");
        al_destroy_timer(timer);
        return -1;
    }

    event_queue = al_create_event_queue();
    if (!event_queue) {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_bitmap(cuadradito);
        al_destroy_timer(timer);
        return -1;
    }

    display = al_create_display(SCREEN_W, SCREEN_H);
    if (!display) {
        fprintf(stderr, "failed to create display!\n");
        al_destroy_timer(timer);
        al_destroy_bitmap(cuadradito);
        al_destroy_event_queue(event_queue);
        return -1;
    }

    al_set_target_bitmap(cuadradito);       //se crea un cuadradito que es el que se ira moviendo
    al_clear_to_color(al_map_rgb(100, 0, 255)); //se lo colorea
    al_set_target_bitmap(al_get_backbuffer(display));   //?

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source()); //REGISTRAMOS EL TECLADO

    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_flip_display();
    al_start_timer(timer);

    while (!do_exit) {
        ALLEGRO_EVENT ev;
        if (al_get_next_event(event_queue, &ev)){ //Toma un evento de la cola, VER RETURN EN DOCUMENT.
            if (ev.type == ALLEGRO_EVENT_TIMER) {
                
                if (key_pressed[KEY_UP] && cuadradito_y >= MOVE_RATE)
                    cuadradito_y -= MOVE_RATE;  //MUEVE EL CUADRADITO, SI MODIFICO MOVE_RATE , MODIFICO LA VELOCIDAD DE DESPLAZAMIENTO

                if (key_pressed[KEY_DOWN] && cuadradito_y <= SCREEN_H - CUADRADITO_SIZE - MOVE_RATE)
                    cuadradito_y +=MOVE_RATE;

                if (key_pressed[KEY_LEFT] && cuadradito_x >= MOVE_RATE)
                    cuadradito_x -= MOVE_RATE;

                if (key_pressed[KEY_RIGHT] && cuadradito_x <= SCREEN_W - CUADRADITO_SIZE - MOVE_RATE)
                    cuadradito_x += MOVE_RATE;

                redraw = true;
            }
            else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                do_exit = true;

            else if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {       //CONTROLA SI LAS TECLAS ESTAN PRESIONADAS
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_UP:
                        key_pressed[KEY_UP] = true;
                        printf("estas apretando flecha pa arriba\n");
                        break;

                    case ALLEGRO_KEY_DOWN:
                        key_pressed[KEY_DOWN] = true;
                        break;

                    case ALLEGRO_KEY_LEFT:
                        key_pressed[KEY_LEFT] = true;
                        break;

                    case ALLEGRO_KEY_RIGHT:
                        key_pressed[KEY_RIGHT] = true;
                        break;
                }
            }
            else if (ev.type == ALLEGRO_EVENT_KEY_UP) {     //CONTROLA LAS TECLAS QUE NO ESTAN PRESIONADAS
                switch (ev.keyboard.keycode) {
                    case ALLEGRO_KEY_UP:
                        key_pressed[KEY_UP] = false;
                        printf("ya no la apretas\n");
                        break;

                    case ALLEGRO_KEY_DOWN:
                        key_pressed[KEY_DOWN] = false;
                        break;

                    case ALLEGRO_KEY_LEFT:
                        key_pressed[KEY_LEFT] = false;
                        break;

                    case ALLEGRO_KEY_RIGHT:
                        key_pressed[KEY_RIGHT] = false;
                        break;

                    case ALLEGRO_KEY_ESCAPE:
                        do_exit = true;
                        break;
                }
            }
        }

        if (redraw && al_is_event_queue_empty(event_queue)) {
            redraw = false;
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_bitmap(cuadradito, cuadradito_x, cuadradito_y, 0);  //DIBUJA EL CUADRADITO
            al_flip_display();
        }
    }

    al_destroy_bitmap(cuadradito);
    al_destroy_timer(timer);
    al_destroy_display(display);
    return 0;
}
