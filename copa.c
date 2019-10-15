#include<stdbool.h>
#include"copa.h"
#include"laberinto.h"
#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#include<math.h>

#define COPA 'C'
#define ESCREGUTO 'E'
#define ACROMANTULA 'A'
#define BOGGART 'B'
#define IMPEDIMENTA 'I'
#define RIDDIKULUS 'R'
#define POCION 'P'
#define ESFINGE 'F'
#define RIVAL 'G'
#define JUGADOR 'J'
#define ARRIBA 'w'
#define ABAJO 's'
#define DERECHA 'd'
#define IZQUIERDA 'a'
#define VIDA_INICIAL 50

/*
 *PRE: Recibe la estructura juego y la posicion de la ayuda.
 *POS: Agrega la ayuda recibida al vector ayuda del JUGADOR (Mochila).
 */
void agregar_ayuda_a_mochila(juego_t* juego,int posicion_ayuda);

/*
 *PRE: Recibe la estructura juego y la posicion de la ayuda en el vector de ayudas del jugador.
 *POS: Borra una ayuda del vector ayudas del jugador en la posicion recibida.
 */
void borrar_ayuda_mochila(juego_t* juego,int posicion);

/*
 *PRE: Recibe la estructura juego y la posicion de la ayuda en el juego.
 *POS: Borra una ayuda del vector ayudas del juego en la posicion recibida.
 */
void borrar_ayuda_laberinto(juego_t* juego,int posicion);

/*
 *PRE: Recibe la estructura juego y la posicion del obstaculo en el juego.
 *POS: Borra un obstaculo del vector obstaculos del juego en la posicion recibida.
 */
void borrar_obstaculo_laberinto(juego_t* juego, int posicion);

/*
 *PRE: Recibe la estructura coordenada de dos posiciones.
 *POS: Devuelve verdadero en caso de ser posiciones iguales , caso contrario false.
 */
bool posiciones_iguales(coordenada_t posicion_1,coordenada_t posicion_2);

/*
 *POS: Recibe la estructura juego.
 *POS: Valida que en la posicion a la que el rival intenta moverse no haya una pared.
 */
bool intentar_mover(juego_t* juego);

/*
 *PRE: Recibe una direccion char.
 *POS: Cambia la direccion en la secuencia derecha, abajo, izquierda, arriba.
 */
void cambiar_direccion(char* direccion);

/*
 *PRE: Recibe dos laberintos TAMANIOXTAMANIO.
 *POS: Copia las paredes del laberinto_original (inicializadas previamente con inicializar_paredes_laberinto) a un laberinto_auxiliar.
 */
void copiar_laberinto_auxiliar(char laberinto_original[TAMANIO][TAMANIO], char laberinto_auxiliar[TAMANIO][TAMANIO]);

/*
 *PRE: Recibe las estructuras copa y el laberinto auxiliar creado en inicializar_laberinto.
 *POS: Devuelve veraz en caso de que la posicion de la copa no haya una PARED.
 */
bool posicion_copa_valida(copa_t copa, char laberinto_auxiliar[TAMANIO][TAMANIO]);

/*
 *PRE: Recibe un vector de obstaculos.
 *POS: Devuelve la veracidad segun si las posiciones de los obstaculos se superponen entre si.
 */
bool posicion_obstaculos_iguales(obstaculo_t obstaculos[TOTAL_OBSTACULOS]);

/*
 *PRE: Recibe la estructura juego.
 *POS: Verifica si no coincide con posición de una pared o la copa.
 */
bool posicion_obstaculo_valida(juego_t juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);

/*
 *PRE: Recibe un vector de obstaculos con una posición.
 *POS: Asigna un un codigo y un daño a un obstaculo de acuerdo a la posicion recibida.
 */
void asignar_codigo_y_danio_obstaculo(obstaculo_t obstaculos[TOTAL_OBSTACULOS],int posicion);

/*
 *PRE: Recibe el vector ayudas con su respectivo tope.
 *pos: Devuelve veraz en caso de que no haya ninguna superposicion de coordenadas.
 */
bool posicion_ayudas_iguales(ayuda_t ayudas[TOTAL_AYUDAS], int tope);

/*
 *PRE: Recibe la estructura juego y el laberinto auxiliar creado en inicializar_laberinto.
 *POS: Devuelve veraz en caso  de que no coincide con posición de una pared o la copa.
 */
bool posicion_ayuda_valida(juego_t juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);

/*
 *PRE: Recibe la estructura ayuda.
 *POS: Asigna los codigos con los que seran mostrados en el laberinto (I, R, P, F).
 */
void asignar_codigo_ayuda(ayuda_t* ayuda, int posicion);

/*
 *PRE: Recibe la estructura juego.
 *POS: Verifica si es igual a la posición de  a la de PARED, COPA, obstaculos y ayudas a traves de una sumatoria de enteros que representan cuantas veces es invalida la posicion en ,caso de ser 0 devuelve veraz.
 */
bool posicion_rival_valida(juego_t juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);

/*
 *PRE: Recibe a las estructuras copa y el laberinto auxiliar creado en inicializar_laberinto.
 *POS: Devuelve veraz si la posicion del jugador no es igual a otro objeto del juego.
*/
bool posicion_jugador_valida(juego_t juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);

/*
 *PRE: Recibe a las estructuras copa y el laberinto auxiliar creado en inicializar_laberinto.
 *POS: Los campos codigo,posición son inicializados correctamente sin superposicion de objetos.
 */
void inicializar_copa(copa_t* copa, char laberinto_auxiliar[TAMANIO][TAMANIO]);

/*
 *PRE: Recibe la estructura juego.
 *POS: Inicializa los obstaculos del juego correctamente sin superposicion entre si.
 */
void inicializar_obstaculos(juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);

/*
 *PRE: Recibe la estructura juego y el laberinto auxiliar creado en inicializar_laberinto.
 *POS: Inicializa las ayudas del juego correctamente sin superposicion entre si.
 */
void inicializar_ayudas(juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);

/*
 *PRE: Recibe la estructura juego y el laberinto auxiliar creado en inicializar_laberinto.
 *POS: Inicializa su codigo,posición,cantidad_pasos del rival.
 */
void inicializar_rival(juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);

/*
 *PRE: Recibe la estructura juego y el laberinto auxiliar creado en inicializar_laberinto.
 *pos: Inicializa su codigo,posición del jugador.
*/
void inicializar_jugador(juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]);

/*
 *PRE: Recibe las estructuras rival, jugador y copa.
 *POS: Valida que las posiciones del jugador y rival inicien a mas de 10 pasos de la copa.
*/
bool distancia_manhattan(rival_t rival, jugador_t jugador, copa_t copa);




						// ** FUNCIONES PUBLICAS ** //

coordenada_t posicion_aleatoria(){
    coordenada_t posicion;
    posicion.fil=rand()%15;
    posicion.col=rand()%15;
    return posicion;
}

void inicializar_laberinto(juego_t* juego){
	juego->tope_obstaculos=3;
	juego->tope_ayudas=0;
	char laberinto_auxiliar[TAMANIO][TAMANIO];
	inicializar_paredes_laberinto(juego->laberinto_original);
	do {
		copiar_laberinto_auxiliar(juego->laberinto_original, laberinto_auxiliar);
		inicializar_copa(&(juego->copa), laberinto_auxiliar);
		inicializar_obstaculos(juego, laberinto_auxiliar);
		inicializar_ayudas(juego, laberinto_auxiliar);
		inicializar_rival(juego,laberinto_auxiliar);
		inicializar_jugador(juego, laberinto_auxiliar);
	} while(!distancia_manhattan(juego->rival, juego->jugador, juego->copa));
}

void actualizar_juego(juego_t* juego){
    juego->jugador.vida-=3;
    for (int i=0; i<juego->tope_ayudas; i++){
       if (posiciones_iguales(juego->ayudas[i].posicion,juego->jugador.posicion)){
         	if (juego->ayudas[i].codigo==ESFINGE){
              	juego->copa.codigo=COPA;
              agregar_ayuda_a_mochila(juego,i);
        	}
         	else if (juego->ayudas[i].codigo==POCION){
         		if (juego->jugador.vida>35){
         			juego->jugador.vida=50;
         		}else if (juego->jugador.vida<3){
              		juego->jugador.vida+=0;
              	} else juego->jugador.vida+=juego->ayudas[i].vida_a_recuperar;
          	} else {
                agregar_ayuda_a_mochila(juego,i);
          	}
         	borrar_ayuda_laberinto(juego,i);
   		}
	}
	int h=0;
    bool ataco=false;
    for (int j=0; j<juego->tope_obstaculos; j++) {
        if (posiciones_iguales(juego->obstaculos[j].posicion,juego->jugador.posicion)){
            while (h<juego->jugador.tope_ayudas){
                if ( (juego->obstaculos[j].codigo==ESCREGUTO) && (juego->jugador.ayudas[h].codigo==IMPEDIMENTA) ){
                	ataco=true;
                	borrar_ayuda_mochila(juego,h);
                    printf("\nGenial! Tenias Impedimenta y el Escreguto no te hizo daño.\n\n");
                }
                else if ( (juego->obstaculos[j].codigo==BOGGART) && (juego->jugador.ayudas[h].codigo==RIDDIKULUS) ){
                    ataco=true;
                    borrar_ayuda_mochila(juego,h);
                    printf("\nGenial! Tenias Riddikulus y el Boggart no te hizo daño.\n\n");
                }
                h++;
            }
            if (!ataco){
                juego->jugador.vida-=juego->obstaculos[j].danio;
            }
            borrar_obstaculo_laberinto(juego,j);
        }
    }
	if (juego->jugador.vida<15){
      juego->copa.codigo=COPA;
    }
    else if ( (juego->jugador.vida>15)&&(juego->jugador.ayudas[0].codigo!=ESFINGE) && (juego->jugador.ayudas[1].codigo!=ESFINGE) && (juego->jugador.ayudas[2].codigo!=ESFINGE) ){
        juego->copa.codigo=' ';
    }
}

bool es_movimiento_valido(juego_t* juego, char tecla){
	bool movimiento_valido;
    switch (tecla){
      	case ARRIBA:
        	if ( (juego->laberinto_original[juego->jugador.posicion.fil-1][juego->jugador.posicion.col]!=PARED) && ((juego->jugador.posicion.fil-1) >= 0)){
            movimiento_valido=true;
          	}
      	break;
      	case ABAJO:
    		if ( (juego->laberinto_original[juego->jugador.posicion.fil+1][juego->jugador.posicion.col]!=PARED) && ((juego->jugador.posicion.fil+1) <= 14) ){
            movimiento_valido=true;
          	}
      	break;
      	case DERECHA:
        	if ( (juego->laberinto_original[juego->jugador.posicion.fil][juego->jugador.posicion.col+1]!=PARED) && ((juego->jugador.posicion.col+1) <= 14) ){
            movimiento_valido=true;
          	}
      	break;
      	case IZQUIERDA:
            if ( (juego->laberinto_original[juego->jugador.posicion.fil][juego->jugador.posicion.col-1]!=PARED) && ((juego->jugador.posicion.col-1) >= 0) ){
            movimiento_valido=true;
         	}
    	break;
      	default:
        movimiento_valido=false;
      	break;
    }
    return movimiento_valido;
}

void mover_jugador(jugador_t* jugador, char direccion){
    switch (direccion) {
      case ARRIBA:
          (jugador->posicion.fil)--;
      break;
      case ABAJO:
          (jugador->posicion.fil)++;
      break;
      case DERECHA:
          (jugador->posicion.col)++;
      break;
      case IZQUIERDA:
              (jugador->posicion.col)--;
      break;
    }
}

void mover_rival(juego_t* juego){
    bool dezplazado=false;
    do {
        if ( (juego->rival.cantidad_pasos%4==0) && (0<juego->rival.cantidad_pasos) ){
            cambiar_direccion(&juego->rival.direccion);
        }
        dezplazado=intentar_mover(juego);
        juego->rival.cantidad_pasos++;
    } while (!dezplazado);
}

void actualizar_laberinto(juego_t juego, char laberinto[TAMANIO][TAMANIO]){
	for (int i=0 ; i<TAMANIO ; i++){
		for (int j=0 ; j<TAMANIO; j++){
			laberinto[i][j]=juego.laberinto_original[i][j];
		}
	}
    laberinto[juego.copa.posicion.fil][juego.copa.posicion.col]=juego.copa.codigo;
    for (int l=0 ; l<juego.tope_obstaculos ; l++){
      laberinto[juego.obstaculos[l].posicion.fil][juego.obstaculos[l].posicion.col]=juego.obstaculos[l].codigo;
    }
    for (int h=0 ; h<juego.tope_ayudas ; h++) {
        laberinto[juego.ayudas[h].posicion.fil][juego.ayudas[h].posicion.col]=juego.ayudas[h].codigo;
    }
    laberinto[juego.rival.posicion.fil][juego.rival.posicion.col]=juego.rival.codigo;
    laberinto[juego.jugador.posicion.fil][juego.jugador.posicion.col]=juego.jugador.codigo;
}

void mostrar_laberinto(char laberinto[TAMANIO][TAMANIO]){
    for (int fila=0; fila<TAMANIO; fila++){
          for (int columna=0; columna<TAMANIO; columna++){
                if (columna==TAMANIO-1) {
                    printf("%c\n",laberinto[fila][columna]);
                }
                else {
                    printf("%c ",laberinto[fila][columna]);
                }
          }
    } 
}

int estado_juego(juego_t juego){
	int estado_juego;
    if ( (juego.jugador.vida<=0) || posiciones_iguales(juego.copa.posicion,juego.rival.posicion) ){
        estado_juego=-1;
    }
    else if (posiciones_iguales(juego.jugador.posicion,juego.copa.posicion)){
        estado_juego=1;
    }
    else estado_juego=0;

    return estado_juego;
}




						// ** FUNCIONES PRIVADAS ** //

void agregar_ayuda_a_mochila(juego_t* juego,int posicion_ayuda){
    juego->jugador.ayudas[juego->jugador.tope_ayudas].codigo=juego->ayudas[posicion_ayuda].codigo;
    (juego->jugador.tope_ayudas)++;
}

void borrar_ayuda_mochila(juego_t* juego,int posicion){
    for (int m=posicion ; m<juego->jugador.tope_ayudas-1 ; m++){
        juego->jugador.ayudas[m]=juego->jugador.ayudas[m+1];
    }
    (juego->jugador.tope_ayudas)--;
}

void borrar_ayuda_laberinto(juego_t* juego,int posicion){
    for (int i=posicion ; i<juego->tope_ayudas-1; i++) {
        juego->ayudas[i]=juego->ayudas[i+1];
    }
    (juego->tope_ayudas)--;
}

void borrar_obstaculo_laberinto(juego_t* juego, int posicion){
    for (int i=posicion ; i<juego->tope_obstaculos-1 ; i++){
        juego->obstaculos[i]=juego->obstaculos[i+1];
    }
    (juego->tope_obstaculos)--;
}

bool posiciones_iguales(coordenada_t posicion_1,coordenada_t posicion_2){
    if ( (posicion_1.fil==posicion_2.fil) && (posicion_1.col==posicion_2.col) ){
    	return true;
    }else{
    	return false;
    }
}

bool intentar_mover(juego_t* juego){
    bool movimiento_valido;
    switch ( juego->rival.direccion){
        case DERECHA:
            if (juego->laberinto_original[juego->rival.posicion.fil][juego->rival.posicion.col+1]!=PARED){
                (juego->rival.posicion.col)++;
                movimiento_valido=true;
            }
        break;
        case ABAJO:
            if (juego->laberinto_original[juego->rival.posicion.fil+1][juego->rival.posicion.col]!=PARED){
                (juego->rival.posicion.fil)++;
                movimiento_valido=true;
            }
        break;
        case IZQUIERDA:
            if (juego->laberinto_original[juego->rival.posicion.fil][juego->rival.posicion.col-1]!=PARED){
                (juego->rival.posicion.col)--;
                movimiento_valido=true;
            }
        break;
        case ARRIBA:
            if (juego->laberinto_original[juego->rival.posicion.fil-1][juego->rival.posicion.col]!=PARED){
                (juego->rival.posicion.fil)--;
                movimiento_valido=true;
            }
        break;
        default: movimiento_valido=false;
    }
    return movimiento_valido;
}

void cambiar_direccion(char* direccion){
    switch (*direccion){
      case DERECHA:
          (*direccion)=ABAJO;
      break;
      case ABAJO:
          (*direccion)=IZQUIERDA;
      break;
      case IZQUIERDA:
          (*direccion)=ARRIBA;
      break;
      case ARRIBA:
          (*direccion)=DERECHA;
      break;
    }
}

void copiar_laberinto_auxiliar(char laberinto_original[TAMANIO][TAMANIO], char laberinto_auxiliar[TAMANIO][TAMANIO]){
	for (int i=0 ; i<TAMANIO ; i++){
		for(int j=0 ; j<TAMANIO ; j++){
			laberinto_auxiliar[i][j]=laberinto_original[i][j];
		}
	}
}

bool posicion_copa_valida(copa_t copa, char laberinto_auxiliar[TAMANIO][TAMANIO]){
    if (laberinto_auxiliar[copa.posicion.fil][copa.posicion.col]==PARED){
        return false;
    }
    else{ 
       	return true;
    }
}

bool posicion_obstaculos_iguales(obstaculo_t obstaculos[TOTAL_OBSTACULOS]){
    int posiciones_invalidas=0;
    if ( (obstaculos[0].posicion.fil==obstaculos[1].posicion.fil) && (obstaculos[0].posicion.col==obstaculos[1].posicion.col) ){
        posiciones_invalidas++;
    }
    if ( (obstaculos[1].posicion.fil==obstaculos[2].posicion.fil) && (obstaculos[1].posicion.col==obstaculos[2].posicion.col) ){
        posiciones_invalidas++;
    }
    if ( (obstaculos[0].posicion.fil==obstaculos[2].posicion.fil) && (obstaculos[0].posicion.col==obstaculos[2].posicion.col) ){
        posiciones_invalidas++;
    }
    if (posiciones_invalidas==0){
        return false;
    }
    else return true;
}

bool posicion_obstaculo_valida(juego_t juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
    bool posicion_valida=true;
    for (int i=0 ; i<juego.tope_obstaculos ; i++){
        if (laberinto_auxiliar[juego.obstaculos[i].posicion.fil][juego.obstaculos[i].posicion.col]==PARED){
            posicion_valida=false;
        }
        else if ( (juego.copa.posicion.fil==juego.obstaculos[i].posicion.fil) && (juego.copa.posicion.col==juego.obstaculos[i].posicion.col) ){
            posicion_valida=false;
        }
    }
    if ( (posicion_obstaculos_iguales(juego.obstaculos)) && (!posicion_valida) ){
        return false;
    }
    return posicion_valida;
}

void asignar_codigo_y_danio_obstaculo(obstaculo_t obstaculos[TOTAL_OBSTACULOS],int posicion){
    switch (posicion){
      case 0:
          obstaculos[posicion].danio=10;
          obstaculos[posicion].codigo=ACROMANTULA;
      break;
      case 1:
          obstaculos[posicion].danio=15;
          obstaculos[posicion].codigo=BOGGART;
      break;
      case 2:
          obstaculos[posicion].danio=20;
          obstaculos[posicion].codigo=ESCREGUTO;
      break;
    }
}

bool posicion_ayudas_iguales(ayuda_t ayudas[TOTAL_AYUDAS] ,int tope){
    int invalidas=0;
    for (int i = 0; i < tope; i++){
        for (int j = 0; j < tope; j++){
           	if ((ayudas[i].posicion.fil==ayudas[j].posicion.fil) && (ayudas[i].posicion.col==ayudas[j].posicion.col) ){
               	invalidas++;
           	}
       	}
    }
    if (invalidas > 4){
    	return false;
    }
    else return true;
}

bool posicion_ayuda_valida(juego_t juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
    int posiciones_iguales=0;
    for (int i=0 ; i<juego.tope_obstaculos ; i++){
        for (int  j=0 ; j<juego.tope_ayudas ; j++){
            if( (juego.obstaculos[i].posicion.fil==juego.ayudas[j].posicion.fil) && (juego.obstaculos[i].posicion.col==juego.ayudas[j].posicion.col) ){
                posiciones_iguales++;
            }
            if (laberinto_auxiliar[juego.ayudas[j].posicion.fil][juego.ayudas[j].posicion.col]==PARED){
                posiciones_iguales++;
            }
            if ( (juego.copa.posicion.fil==juego.ayudas[j].posicion.fil)  && (juego.copa.posicion.col==juego.ayudas[j].posicion.col) ){
                posiciones_iguales++;
            }
        }
    }
    if (posiciones_iguales==0){
       return true;
    }
    else return false;
}

void asignar_codigo_ayuda(ayuda_t* ayuda, int posicion){
    switch (posicion){
      case 0:
            ayuda->codigo=IMPEDIMENTA;
            ayuda->vida_a_recuperar=0;
      break;
      case 1:
            ayuda->codigo=RIDDIKULUS;
            ayuda->vida_a_recuperar=0;
      break;
      case 2:
            ayuda->codigo=POCION;
            ayuda->vida_a_recuperar=15;
      break;
      case 3:
            ayuda->codigo=POCION;
            ayuda->vida_a_recuperar=15;
      break;
      case 4:
            ayuda->codigo=POCION;
            ayuda->vida_a_recuperar=15;
      break;
      case 5:
            ayuda->codigo=ESFINGE;
            ayuda->vida_a_recuperar=0;
      break;
    }
}

bool posicion_rival_valida(juego_t juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
    int posicion_invalida=0;
    if (laberinto_auxiliar[juego.rival.posicion.fil][juego.rival.posicion.col]==PARED){
        posicion_invalida++;
    }
    else if ( (juego.copa.posicion.fil==juego.rival.posicion.fil) && (juego.copa.posicion.col==juego.rival.posicion.col)){
        posicion_invalida++;
    }
    for (int i=0 ; i<juego.tope_obstaculos ; i++){
        if ( (juego.obstaculos[i].posicion.fil==juego.rival.posicion.fil) && (juego.obstaculos[i].posicion.col==juego.rival.posicion.col) ){
            posicion_invalida++;
        }
    }
    for (int j=0 ; j<juego.tope_ayudas ; j++){
        if ( (juego.ayudas[j].posicion.fil==juego.rival.posicion.fil) && (juego.ayudas[j].posicion.col==juego.rival.posicion.col) ){
            posicion_invalida++;
        }
    }
    if (posicion_invalida>0) {
     	return false;
    }
    else return true;
}

bool posicion_jugador_valida(juego_t juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
    int posicion_invalida=0;
    if (laberinto_auxiliar[juego.jugador.posicion.fil][juego.jugador.posicion.col]==PARED) {
        posicion_invalida++;
    }
    for (int i=0 ; i<juego.tope_obstaculos ; i++){
        if ( (juego.obstaculos[i].posicion.fil==juego.jugador.posicion.fil) && (juego.obstaculos[i].posicion.col==juego.jugador.posicion.col) ){
            posicion_invalida++;
        }
    }
    for (int j=0 ; j<juego.tope_ayudas ; j++){
          	if( (juego.ayudas[j].posicion.fil==juego.jugador.posicion.fil) && (juego.ayudas[j].posicion.col==juego.jugador.posicion.col) ){
            	posicion_invalida++;
          	}
    }
    if (posicion_invalida>0){
    	return false;
    }
    else return true;
}

void inicializar_copa(copa_t* copa, char laberinto_auxiliar[TAMANIO][TAMANIO]){
    copa->codigo=' ';
    do {
        copa->posicion=posicion_aleatoria();
    } while (!posicion_copa_valida((*copa),laberinto_auxiliar));
    copa->codigo=' ';
}

void inicializar_obstaculos(juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
    juego->tope_obstaculos=3;
    do {
        for (int i=0 ; i<juego->tope_obstaculos ; i++){
            juego->obstaculos[i].posicion=posicion_aleatoria();
            asignar_codigo_y_danio_obstaculo(juego->obstaculos, i);
        }
    } while (!posicion_obstaculo_valida((*juego), laberinto_auxiliar));
}

void inicializar_ayudas(juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
    juego->tope_ayudas=6;
    do {
        for (int i=0 ; i<juego->tope_ayudas ; i++) {
            juego->ayudas[i].posicion=posicion_aleatoria();
            asignar_codigo_ayuda( &(juego->ayudas[i]),i);
        }
    } while ( (!posicion_ayuda_valida((*juego), laberinto_auxiliar)) || (posicion_ayudas_iguales(juego->ayudas,juego->tope_ayudas)) );
}	

void inicializar_rival(juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
    juego->rival.codigo=RIVAL;
    juego->rival.direccion=DERECHA;
    juego->rival.cantidad_pasos=0;
    do {
        juego->rival.posicion=posicion_aleatoria();
    } while (!posicion_rival_valida((*juego), laberinto_auxiliar));
}

void inicializar_jugador(juego_t* juego, char laberinto_auxiliar[TAMANIO][TAMANIO]){
    juego->jugador.codigo=JUGADOR;
    juego->jugador.vida=VIDA_INICIAL;
    juego->jugador.tope_ayudas=0;
    do {
        juego->jugador.posicion=posicion_aleatoria();
    } while (!posicion_jugador_valida((*juego), laberinto_auxiliar));
}

bool distancia_manhattan(rival_t rival, jugador_t jugador, copa_t copa){
	double distancia_filas_jugador_copa=fabs(jugador.posicion.fil-copa.posicion.fil);
	double distancia_filas_rival_copa=fabs(rival.posicion.fil-copa.posicion.fil);
	double distancia_columnas_jugador_copa=fabs(jugador.posicion.col-copa.posicion.col);
	double distancia_columnas_rival_copa=fabs(rival.posicion.col-copa.posicion.col);
	double distancia_manhattan_jugador=distancia_filas_jugador_copa+distancia_columnas_jugador_copa;
	double distancia_manhattan_rival=distancia_filas_rival_copa+distancia_columnas_rival_copa;
	return( (distancia_manhattan_jugador>10) && (distancia_manhattan_rival>10) );
}